#include "CameraWidget.h"
#include "FlyCapture.h"
#include "ImageThread.h"
#include "ShowThread.h"
#include "FusionAlg.h"
#include "ViewWidget.h"
#include "FileCentre.h"

//qt
#include <QtWidgets\qmessagebox.h>
#include <QtGui\qevent.h>
#include <qdir.h>
//c++
#include <fstream>
using std::ofstream;
using std::endl;

int CameraWidget::s_OBJ = 0;
CameraWidget::CameraWidget(void)
	:mSerialPort(new QSerialPort(this)),
	mFusionAlg(NULL),mImgTrd(NULL),
	mShowTrd(NULL),mFC(NULL)
{
	s_OBJ++;
	mViewWidget = NULL;
	mfSum = 0;
	ui.setupUi(this);	

	//返回
	connect(ui.pbBack, SIGNAL(clicked()), this, SLOT(backSlot()));
	//保存
	connect(ui.pbSave, SIGNAL(clicked()), this, SLOT(saveSlot()));
	//暂停
	connect(ui.pbPause, SIGNAL(clicked()), this, SLOT(pauseSlot()));
	//录像
	connect(ui.pbVideo, SIGNAL(clicked()), this, SLOT(videoSlot()));
	//全屏
	connect(ui.pbFullScreen, SIGNAL(clicked()), this, SLOT(fullScreenSlot()));
	//自动保存
	connect(ui.cbAutoSave, SIGNAL(clicked()), this, SLOT(autoSaveSlot()));

	//串口
	connect(mSerialPort, SIGNAL(readyRead()), this, SLOT(readData()));


	//根据参数初始化是否自动保存
	/*
	QString autosave = "";
	FileCentre *fc = FileCentre::GetInstance();
	fc->ReadSystemValue("autosave", autosave);
	if("1" == autosave)
	{
		ui.cbAutoSave->setCheckState(Qt::Checked);
		mbAutoSave = true;	
		miAutoSecond = 0;
	}
	else
	{
		ui.cbAutoSave->setCheckState(Qt::Unchecked);	
		mbAutoSave = false;	
	}
	*/

	begin();
	openPort();
}


CameraWidget::~CameraWidget(void)
{
	s_OBJ--;

	//获取图像线程
	if(mImgTrd != NULL)
	{
		if(mImgTrd->isRunning())
		{
			mImgTrd->Stop();	
			mImgTrd->wait(1000);
		}
		delete mImgTrd;
		mImgTrd = NULL;
	}
	//显示图像线程
	if(mShowTrd != NULL)
	{
		if(mShowTrd->isRunning())
		{
			mShowTrd->Stop();	
			mShowTrd->wait(1000);
		}
		delete mShowTrd;
		mShowTrd = NULL;
	}
	//删除算法类
	if(mFusionAlg != NULL)
	{
		delete mFusionAlg;
		mFusionAlg = NULL;
	}
	//删除相机类
	if(mFC != NULL)
	{
		delete mFC;	
		mFC = NULL;
	}

	if(mViewWidget != NULL)
	{
		delete mViewWidget;	
	}
}

int CameraWidget::GetOBJ()
{
	return s_OBJ;
}

void CameraWidget::fullScreenSlot()
{
	QString tmp = ui.lbScreen->text();
	/*
	if(tmp == QStringLiteral("全屏显示"))
	{
		ui.lbScreen->setText(QStringLiteral("屏幕恢复"));	
	}
	else
	{
		ui.lbScreen->setText(QStringLiteral("全屏显示"));	
	}
	*/
	emit fullScreenSignal(tmp);
}

void CameraWidget::autoSaveSlot()
{
	if(ui.cbAutoSave->checkState() == Qt::Checked)
	{
		mbAutoSave = false;	
	}
	else
	{
		mbAutoSave = true;	
		miAutoSecond = 0;
	}
}

void CameraWidget::backSlot()
{
	emit backSignal();
}

void CameraWidget::pauseSlot()
{
	QString str = ui.pbPause->text();
	if(str == QStringLiteral("冻结"))
	{
		ui.pbPause->setText(QStringLiteral("继续"));
		mImgTrd->SetPause(true);
	}
	else if(str == QStringLiteral("继续"))
	{
		ui.pbPause->setText(QStringLiteral("冻结"));
		mImgTrd->SetPause(false);
	}
}

void CameraWidget::saveSlot()
{
	ui.pbSave->setEnabled(false);
	if(mShowTrd != NULL)
	{
		//FileCentre *fc = FileCentre::GetInstance();
		//QString path = fc->GetRecordPath();

		QString pathName = mShowTrd->SaveImage();	

		emit imageSignal(pathName);
	}
	ui.pbSave->setEnabled(true);
	ui.pbSave->setFocus();

}

void CameraWidget::videoSlot()
{
	if(ui.lbVideo->text() == QStringLiteral("开始录像"))
	{
		FileCentre *fc = FileCentre::GetInstance();
		QString path = fc->GetRecordPath().append("/video");

		QDir dir(path);
		if(!dir.exists())
		{
			dir.mkpath(path);	
		}

		//锁定曝光增益
		string sMsg = mFC->SetAutoShutter(false);
		if(sMsg != "ok")
		{
			QMessageBox::warning(this, QStringLiteral("自动曝光"), QString::fromStdString(sMsg),QStringLiteral("确定"));
		}
		sMsg = mFC->SetAutoGain(false);
		if(sMsg != "ok")
		{
			QMessageBox::warning(this, QStringLiteral("自动增益"), QString::fromStdString(sMsg),QStringLiteral("确定"));
		}

		//保存gain文档
		QString info = path+"/info.txt";
		QString strTime = QTime::currentTime().toString("hhmmsszzz");
		float shutter = mFC->GetShutter();
		float gain = mFC->GetGain();
		ofstream ofsInfo(info.toStdString(), ofstream::app);
		stringstream ss;
		ss<<strTime.toStdString()<<".bmp"<<"    shutter:"
			<<shutter<<"    gain: "
			<<gain<<endl;
		ofsInfo<<ss.str();

		//
		ui.lbVideo->setText(QStringLiteral("结束录像"));
		mfSum = 0;
		QTime t(0,0,0);
		mTime = t;
		mTimeId = startTimer(1000);

		initButton(false);
	}
	else
	{

		ui.lbVideo->setText(QStringLiteral("开始录像"));
		killTimer(mTimeId);	

		//自动曝光增益
		mFC->SetAutoShutter(true);
		mFC->SetAutoGain(true);
		initButton(true);
	}
}

void CameraWidget::begin()
{
	FileCentre *fc = FileCentre::GetInstance();
	//图像像素
	QString sWidth, sHeight, sMaxWidth, sMaxHeight, sLan;
	fc->ReadSystemValue("camerawidth", sWidth);
	fc->ReadSystemValue("cameraheight", sHeight);
	fc->ReadSystemValue("maxwidth", sMaxWidth);
	fc->ReadSystemValue("maxheight", sMaxHeight);
	//是否网口相机
	fc->ReadSystemValue("lancamera", sLan);
	bool bLan = (sLan == "1") ? true : false;



	int imageWidth = sWidth.toInt();
	int imageHeight = sHeight.toInt();
	//1.初始化算法
	if(mFusionAlg == NULL)
	{
		mFusionAlg = new FusionAlg(imageWidth, imageHeight, 
			imageWidth/2, imageHeight/2, 1, 2);
	}

	//2.初始化相机
	if(mFC == NULL)
	{
		mFC= new FlyCapture(imageWidth, imageHeight, sMaxWidth.toInt(), 
			sMaxHeight.toInt(), bLan);	
	}
	string sMsg="";
	bool fInit = mFC->Init(sMsg);
	if(fInit)
	{
		if(mFC->StartCapture())
		{
			if(mImgTrd == NULL)
			{
				//线程开始获取图像
				mImgTrd = new ImageThread(mFC->GetCamera(), mFusionAlg);
			}
			//connect(imgTrd, SIGNAL(ImageSignal(unsigned char*, int)), this, SLOT(ImageSlot(unsigned char*, int)));
			mImgTrd->start();

			if(mShowTrd == NULL)
			{
				//线程开始显示图像
				mShowTrd = new ShowThread(mFusionAlg);
			}
			connect(mShowTrd, SIGNAL(ImageSignal(QImage)), this, SLOT(ImageSlot(QImage)));
			FileCentre *fc = FileCentre::GetInstance();
			mShowTrd->SetPath(fc->GetRecordPath());
			mShowTrd->setFlyCapture(mFC);
			mShowTrd->start();
		}
	}
	else
	{
		QMessageBox::warning(this, QStringLiteral("相机错误"), QString::fromStdString(sMsg),QStringLiteral("确定"));
		initButton(false);
		ui.pbSave->setEnabled(false);
		ui.pbVideo->setEnabled(false);
		ui.pbBack->setEnabled(true);
	}

	//参数显示窗口
	//mViewWidget = new ViewWidget(this);
	//mViewWidget->show();
}

void CameraWidget::openPort()
{
	QString portName, baudRate, dataBits, stopBits;
	FileCentre *fc = FileCentre::GetInstance();
	fc->ReadSystemValue("portname", portName, "port");
	fc->ReadSystemValue("baudRate", baudRate, "port");
	fc->ReadSystemValue("dataBits", dataBits, "port");
	fc->ReadSystemValue("stopBits", stopBits, "port");

	mSerialPort->setPortName(portName);
	mSerialPort->setBaudRate(baudRate.toInt());
	mSerialPort->setDataBits(static_cast<QSerialPort::DataBits>(dataBits.toInt()));
	mSerialPort->setParity(QSerialPort::NoParity);
	mSerialPort->setStopBits(static_cast<QSerialPort::StopBits>(stopBits.toInt()));
	mSerialPort->setFlowControl(QSerialPort::NoFlowControl);

	if(!mSerialPort->open(QIODevice::ReadWrite))
	{
		QMessageBox::critical(this, tr("Error"), mSerialPort->errorString());
	}


	fc->ReadSystemValue("freeze", mRec.freeze, "recive");
	fc->ReadSystemValue("zoomd", mRec.zoomd, "recive");
	fc->ReadSystemValue("zoomi", mRec.zoomi, "recive");
}

void CameraWidget::ImageSlot(QImage image)
{
	QSize qsize = ui.lbImage->size();
	image = image.scaled(qsize, Qt::KeepAspectRatio);
	QPixmap pixmap = QPixmap::fromImage(image);
	ui.lbImage->setPixmap(pixmap);
	/*
	if(iSize != 0 && cBuffer != NULL)
	{
		QImage image;
		image.loadFromData(cBuffer, iSize);
		
		//默认大小
		//ui.lbImage->resize(image.size());
		QSize qsize = ui.lbImage->size();
		image = image.scaled(qsize, Qt::KeepAspectRatio);

		QPixmap pixmap = QPixmap::fromImage(image);
		
		ui.lbImage->setPixmap(pixmap);
	}
	*/
}


 void CameraWidget::keyPressEvent(QKeyEvent *qevent)
 {
	 if(qevent->key() == Qt::Key_S)
	 {
		saveSlot();
	 }
 }

 void CameraWidget::timerEvent( QTimerEvent *qevent )
 {
	 //保存图片
	 mShowTrd->SaveVideo();
	 mShowTrd->SaveVideo();

	 float size = mShowTrd->GetSize();
	 mfSum += size/(1024.0*512.0);
	 ui.lbVideoSize->setText(QString("%1 MB").arg(mfSum));
	 mTime = mTime.addSecs(1);
	 ui.lbVideoTime->setText(mTime.toString("hh:mm:ss"));


	 if(mbAutoSave)
	 {
		 miAutoSecond++;
		 if(miAutoSecond==30)
		 {
			 saveSlot();
			 miAutoSecond = 0;
		 }
	 }
 }

 void CameraWidget::initButton(bool b)
 {
	 ui.pbPause->setEnabled(b);
	 ui.pbBack->setEnabled(b); 
	 //ui.pbSave->setEnabled(b); 
	 ui.pbFullScreen->setEnabled(b); 
	 ui.lbScreen->setEnabled(b);
 }

 void CameraWidget::readData()
 {
	QByteArray data = mSerialPort->readAll();
	QString str(data.toHex());
	

	if(QString(data.toHex())== mRec.freeze)
	{
		pauseSlot();
	}
	else if(str == mRec.zoomd)
	{
	
	}
	else if(str == mRec.zoomi)
	{
	
	}
 }
