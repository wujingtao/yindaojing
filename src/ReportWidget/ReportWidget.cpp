#include "ReportWidget.h"
#include <qdir.h>
#include <qstringlist.h>
#include <qscrollarea.h>
#include <qprinter.h>
#include <qprintdialog.h>
#include <qprintpreviewdialog.h>
#include <qtextedit.h>
#include <qdatetime.h>
#include <qtextcodec.h>
#include <qmessagebox.h>
#include <qsettings.h>
#include <qtextcodec.h>
#include <qpainter.h>

#include "FileCentre.h"
#include "ControlName.h"
#include "Report_a.h"
#include "MyLabel.h"

#include <fstream>
#include <string>
using std::ifstream;
using std::string;

int ReportWidget::s_OBJ = 0;
QString ReportWidget::s_mTextName = "";
ReportWidget::ReportWidget(void)
{
	//初始化成员
	s_OBJ++;
	mCheckTime = "";
	//mTextEdit = new QTextEdit();

	//ui
	ui.setupUi(this);
	initMyLabelUi();

	//新建
	connect(ui.pbNew, SIGNAL(clicked()), this, SLOT(newSlot()));
	//关闭窗体
	connect(ui.pbClose, SIGNAL(clicked()), this, SLOT(closeSlot()));
	//打印预览
	connect(ui.pbPrintView, SIGNAL(clicked()), this, SLOT(printViewSlot()));
	//打印
	connect(ui.pbPrint, SIGNAL(clicked()), this, SLOT(printSlot()));
	//病案库
	connect(ui.pbRecord, SIGNAL(clicked()), this, SLOT(recordSlot()));
	//采集图像
	connect(ui.pbCamera, SIGNAL(clicked()), this, SLOT(cameraSlot()));
	//保存报表
	connect(ui.pbSaveReport, SIGNAL(clicked()), this, SLOT(saveReportSlot()));
	//处理图像
	connect(ui.pbImage, SIGNAL(clicked()), this, SLOT(imageSlot()));

		
	//诊断替换
	connect(ui.cbContent, SIGNAL(currentIndexChanged(QString)), 
		this, SLOT(contentSlot(QString)));
	connect(ui.teContent, SIGNAL(textEmptySignal()), 
		this, SLOT(textEmptySlot()));
	//阴道镜所见替换
	connect(ui.cbImageText, SIGNAL(currentIndexChanged(QString)), 
		this, SLOT(imageTextSlot(QString)));
	connect(ui.teImageText, SIGNAL(textEmptySignal()), 
		this, SLOT(textEmptySlot()));

	controlEdit();

	FileCentre *fc = FileCentre::GetInstance();
	//参数设置
	QString lbCompany, lbHospital; 
	fc->ReadSystemValue("companyname", lbCompany);
	fc->ReadSystemValue("hospitalname", lbHospital);
	ui.lbCompany->setText(lbCompany);	

	QString path = fc->GetRecordPath();
	if(path != "")
	{
		controlValue(path);	
	}

	QDate date = QDate::currentDate();
	ui.lbDate->setText(date.toString("yyyy-MM-dd"));
	startTimer(1000);

	QPalette tmpPal(QColor(255, 255, 255));
	ui.wgReport->setPalette(tmpPal);
}


ReportWidget::~ReportWidget(void)
{
	s_OBJ--;
}

int ReportWidget::GetOBJ()
{
	return s_OBJ;
}

void ReportWidget::initMyLabelUi()
{
        lb1 = new MyLabel(ui.wgReport);
        lb1->setObjectName(QStringLiteral("lb1"));
        lb1->setMinimumSize(QSize(160, 100));
        lb1->setMaximumSize(QSize(160, 100));
        lb1->setScaledContents(true);

        ui.gridLayout->addWidget(lb1, 0, 0, 1, 1);

        lb2 = new MyLabel(ui.wgReport);
        lb2->setObjectName(QStringLiteral("lb2"));
        lb2->setMinimumSize(QSize(160, 100));
        lb2->setMaximumSize(QSize(160, 100));
        lb2->setScaledContents(true);

        ui.gridLayout->addWidget(lb2, 0, 1, 1, 1);

        lb3 = new MyLabel(ui.wgReport);
        lb3->setObjectName(QStringLiteral("lb3"));
        lb3->setMinimumSize(QSize(160, 100));
        lb3->setMaximumSize(QSize(160, 100));
        lb3->setScaledContents(true);

        ui.gridLayout->addWidget(lb3, 1, 0, 1, 1);

        lb4 = new MyLabel(ui.wgReport);
        lb4->setObjectName(QStringLiteral("lb4"));
        lb4->setMinimumSize(QSize(160, 100));
        lb4->setMaximumSize(QSize(160, 100));
        lb4->setScaledContents(true);

        ui.gridLayout->addWidget(lb4, 1, 1, 1, 1);
}

void ReportWidget::imageTextSlot(QString text)
{
	ui.teImageText->clear();
	ui.teImageText->setFocus();
	ui.teImageText->textCursor().insertText(text);
}

void ReportWidget::contentSlot(QString text)
{
	ui.teContent->clear();
	ui.teContent->setFocus();
	ui.teContent->textCursor().insertText(text);
}

void ReportWidget::controlEdit()
{
	QString value("");
	FileCentre *fc = FileCentre::GetInstance();	
	fc->ReadSystemValue("editable", value);

	int iVal = 0;
	if(value != "")
	{
		iVal = value.toInt();
	}

	ui.cbCheck->setEditable(iVal);
	ui.cbExamine->setEditable(iVal);
	ui.cbRoom->setEditable(iVal);
	ui.cbMoon->setEditable(iVal);
	ui.cbMarry->setEditable(iVal);
	ui.cbPatient->setEditable(iVal);
	ui.cbContra->setEditable(iVal);
	ui.cbBed->setEditable(iVal);
	ui.cbResult->setEditable(iVal);
	ui.cbConfine->setEditable(iVal);
	ui.cbColor->setEditable(iVal);
	ui.cbBlood->setEditable(iVal);
	ui.cbIodine->setEditable(iVal);
	ui.cbS1->setEditable(iVal);
	ui.cbS2->setEditable(iVal);
	ui.cbS3->setEditable(iVal);
	ui.cbS4->setEditable(iVal);
	ui.cbS5->setEditable(iVal);
	//ui.cbContent->setEditable(iVal);
	ui.cbApply->setEditable(iVal);
	ui.cbDiag->setEditable(iVal);
}

void  ReportWidget::controlValue(QString path)
{
	path.append("/report.ini");
	ControlName cn;
	FileCentre *fc = FileCentre::GetInstance();
	fc->ReadAllValue(path, cn);	

	if(ui.cbCheck->isEditable())
	{
	ui.cbCheck->setEditText(cn.cbCheck);
	ui.cbExamine->setEditText(cn.cbExamine);
	ui.cbRoom->setEditText(cn.cbRoom);
	ui.cbMoon->setEditText(cn.cbMoon);
	ui.cbMarry->setEditText(cn.cbMarry);
	ui.cbContra->setEditText(cn.cbContra);
	ui.cbPatient->setEditText(cn.cbPatient);
	ui.cbBed->setEditText(cn.cbBed);
	ui.cbResult->setEditText(cn.cbResult);
	ui.cbConfine->setEditText(cn.cbConfine);
	ui.cbS1->setEditText(cn.cbS1);
	ui.cbColor->setEditText(cn.cbColor);
	ui.cbS2->setEditText(cn.cbS2);
	ui.cbBlood->setEditText(cn.cbBlood);
	ui.cbS3->setEditText(cn.cbS3);
	ui.cbIodine->setEditText(cn.cbIodine);
	ui.cbS4->setEditText(cn.cbS4);
	ui.cbS5->setEditText(cn.cbS5);
	ui.cbApply->setEditText(cn.cbApply);
	ui.cbDiag->setEditText(cn.cbDiag);
	}
	else
	{
	ui.cbCheck->addItem(cn.cbCheck);
	ui.cbExamine->addItem(cn.cbExamine);
	ui.cbRoom->addItem(cn.cbRoom);
	ui.cbMoon->addItem(cn.cbMoon);
	ui.cbMarry->addItem(cn.cbMarry);
	ui.cbContra->addItem(cn.cbContra);
	ui.cbPatient->addItem(cn.cbPatient);
	ui.cbBed->addItem(cn.cbBed);
	ui.cbResult->addItem(cn.cbResult);
	ui.cbConfine->addItem(cn.cbConfine);
	ui.cbS1->addItem(cn.cbS1);
	ui.cbColor->addItem(cn.cbColor);
	ui.cbS2->addItem(cn.cbS2);
	ui.cbBlood->addItem(cn.cbBlood);
	ui.cbS3->addItem(cn.cbS3);
	ui.cbIodine->addItem(cn.cbIodine);
	ui.cbS4->addItem(cn.cbS4);
	ui.cbS5->addItem(cn.cbS5);
	ui.cbApply->addItem(cn.cbApply);
	ui.cbDiag->addItem(cn.cbDiag);
	}
	ui.leTime->setText(cn.createtime.left(16));
	ui.leName->setText(cn.leName);
	ui.sbAge->setValue(cn.sbAge);

	ui.sbCheckNo->setValue(cn.sbCheckNo);
	ui.sbPatientNo->setValue(cn.sbPatientNo);
	ui.sbHospitalNo->setValue(cn.sbHospitalNo);
	ui.sbAreaNo->setValue(cn.sbAreaNo);
	ui.sbBedNo->setValue(cn.sbBedNo);
	ui.sbPreg->setValue(cn.sbPreg);
	ui.sbBirth->setValue(cn.sbBirth);
	ui.teContent->setPlainText(cn.teContent);
	ui.teImageText->setPlainText(cn.teImageText);

	lb1->setMyPixmap(cn.lb1);
	lb2->setMyPixmap(cn.lb2);
	lb3->setMyPixmap(cn.lb3);
	lb4->setMyPixmap(cn.lb4);

	mCheckTime = cn.createtime;
	s_mTextName = cn.reportname;

	initButton(true);
}

void ReportWidget::closeSlot()
{
	//关闭窗体设置病案库路径为空
	FileCentre *fc = FileCentre::GetInstance();
	fc->SetRecordPath("");
	s_mTextName = "";
	//发射信号，主窗体响应
	emit closeSignal();
}

void ReportWidget::newSlot()
{
	//判断是否创建报表
	QString reportName = ui.lwReport->currentItem()->text();
	reportName.append(".html");
	if(s_mTextName != "")
	{
		if(QMessageBox::information(NULL, QStringLiteral("创建报表"), QStringLiteral("当前报表已存在，是否新建报表？"), 
			QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::No)
		{
			return;				
		}
	}
	initControl();

	//获取参数文件路径
	QString imagePath;
	FileCentre *fc = FileCentre::GetInstance();	
	fc->ReadSystemValue("filepath", imagePath);

	//以时间创建文件
	QDateTime dateTime = QDateTime::currentDateTime();
	QString sDate= dateTime.toString("yyMMddhhmmss");
	imagePath.append("/").append(sDate);

	QDir dir(imagePath);
	if(!dir.exists())
	{
		if(!dir.mkpath(imagePath))
		{
			QMessageBox::warning(NULL, QStringLiteral("创建文件夹"), QStringLiteral("创建文件夹失败！"));
			return;				
		}
	}

	fc->SetRecordPath(imagePath);
	QFile file(imagePath.append("/report.ini"));
	if(!file.exists())
	{
		if(!file.open( QIODevice::ReadWrite | QIODevice::Text ))  
		{
			QMessageBox::warning(NULL, QStringLiteral("创建文件"), QStringLiteral("创建文件失败！"));
			return;				

		}
		file.close(); 	
	}
	emit newSignal();

	//保存当前报表类型
	mCheckTime = dateTime.toString("yyyy-MM-dd hh:mm:ss");
	s_mTextName = reportName;

	fc->SaveNameValue("createtime", mCheckTime);
	fc->SaveNameValue("reportname", s_mTextName);

	ui.leTime->setText(dateTime.toString("yyyy-MM-dd hh:mm"));
	initButton(true);
}

void ReportWidget::initButton(bool b)
{
	ui.wgReport->setEnabled(b);
	ui.pbRecord->setEnabled(b);
	ui.pbCamera->setEnabled(b);
	ui.pbImage->setEnabled(b);
	ui.pbReplay->setEnabled(b);
	ui.pbPrint->setEnabled(b);
	ui.pbPrintView->setEnabled(b);
}

void ReportWidget::initControl()
{
	//ui.cbCheck->clear();
	ui.leName->clear();
	ui.sbAge->setValue(0);
	ui.cbExamine->setEditText("");
	ui.cbRoom->setEditText("");
	ui.sbCheckNo->setValue(0);
	ui.sbPatientNo->setValue(0);
	ui.sbHospitalNo->setValue(0);
	ui.sbAreaNo->setValue(0);
	ui.sbBedNo->setValue(0);
	ui.cbMoon->setEditText("");
	ui.cbMarry->setEditText("");
	ui.sbPreg->setValue(0);
	ui.sbBirth->setValue(0);
	ui.cbContra->setEditText("");
	ui.cbPatient->setEditText("");
	ui.cbBed->setEditText("");
	ui.cbResult->setEditText("");
	ui.cbConfine->setEditText("");
	ui.cbS1->setEditText("");
	ui.cbColor->setEditText("");
	ui.cbS2->setEditText("");
	ui.cbBlood->setEditText("");
	ui.cbS3->setEditText("");
	ui.cbIodine->setEditText("");
	ui.cbS4->setEditText("");
	ui.teContent->clear();
	ui.teImageText->clear();
}

void ReportWidget::SetLabelLoad(const QString &pathName)
{
	int index = 0;
	if(lb1->pixmap() == 0)
	{
		lb1->setPixmap(pathName);
		index = 1;
	}
	else if(lb2->pixmap() == 0)
	{
		lb2->setPixmap(pathName);
		index = 2;
	}
	else if(lb3->pixmap() == NULL)
	{
		lb3->setPixmap(pathName);
		index = 3;
	}
	else if(lb4->pixmap() == 0)
	{
		lb4->setPixmap(pathName);
		index = 4;
	}

	initLabel(index, pathName);

	/*
		if(s_mLabel1 == "")	
		{
			s_mLabel1 = pathName;
			ui.lb1->setPixmap(pathName);	
			initLabel(1);
		}
		else if(s_mLabel2 == "")	
		{
			s_mLabel2 = pathName;
			ui.lb2->setPixmap(pathName);	
			initLabel(2);
		}
		else if(s_mLabel3 == "")	
		{
			s_mLabel3 = pathName;
			ui.lb3->setPixmap(pathName);	
			initLabel(3);
		}
		else if(s_mLabel4 == "")	
		{
			s_mLabel4 = pathName;
			ui.lb4->setPixmap(pathName);	
			initLabel(4);
		}
		*/
}



void ReportWidget::initLabel(int index, const QString &fullName)
{
	FileCentre *fc = FileCentre::GetInstance();


	fc->SaveNameValue(  QString("lb%1").arg(index), fullName);
	/*
	switch(index)	
	{
	case 1:	
		fc->SaveNameValue( ui.lb1->objectName(), s_mLabel1);
		break;
	case 2:
		fc->SaveNameValue(ui.lb2->objectName(), s_mLabel2);
		break;
	case 3:
		fc->SaveNameValue(ui.lb3->objectName(), s_mLabel3);
		break;
	case 4:
		fc->SaveNameValue(ui.lb4->objectName(), s_mLabel4);
		break;
	}
	*/
}

void ReportWidget::printViewSlot()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
	//设置预览窗体位置大小
	//preview.setGeometry(QRect(50, 50, 1024, 700));
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(printPreview(QPrinter*)));
	//显示预览对话框
	preview.setWindowFlags(Qt::Dialog | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
	preview.resize(1024,768);
    preview.exec();
}

void ReportWidget::printPreview(QPrinter *printer)
{
	QPainter painter(printer);
	Report_a widget;
	QPixmap pixmap = QPixmap::grabWidget(&widget);

	QRect rect = painter.viewport();
    QSize size = pixmap.size();
    size.scale(rect.size(), Qt::KeepAspectRatio); //此处保证图片显示完整
    painter.setViewport(rect.x(), rect.y(),size.width(), size.height());
    painter.setWindow(pixmap.rect());
    painter.drawPixmap(0,0,pixmap); 
	/*
	if(!loadHtml())
	{return;}
	mTextEdit->print(printer);
	*/

	//保存报表窗体为图片
	FileCentre *fc = FileCentre::GetInstance();
	QString sPath = fc->GetRecordPath();
	pixmap.save(sPath.append("/report.jpg"), "JPG");

}

void ReportWidget::printSlot()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
	/*
	if (mTextEdit->textCursor().hasSelection())
	{
        dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
	}
	*/
    dlg->setWindowTitle(tr("Print Document"));
    if (dlg->exec() == QDialog::Accepted) 
	{
		//mTextEdit->print(&printer);
		printPreview(&printer);	
    }
	delete dlg;
}

void ReportWidget::recordSlot()
{
	emit recordSignal();
}

void ReportWidget::cameraSlot()
{
	emit cameraSignal();
}

void ReportWidget::imageSlot()
{
	emit imageSignal();
}

void ReportWidget::saveReportSlot()
{
	Report_a widget;
	QPixmap pixmap = QPixmap::grabWidget(&widget);

	FileCentre *fc = FileCentre::GetInstance();
	QString sPath = fc->GetRecordPath();
	pixmap.save(sPath.append("/report.jpg"), "JPG");
}

 void ReportWidget::timerEvent( QTimerEvent *qevent )
 {
	 QTime time = QTime::currentTime();
	 ui.lbTime->setText(time.toString("hh:mm:ss"));
 }

void ReportWidget::textEmptySlot()
{
	QString sImageText = ui.teImageText->toPlainText();
	QString sContent = ui.teContent->toPlainText();
	if(sImageText == "")
	{
		ui.cbImageText->setCurrentIndex(-1);	
	}
	if(sContent == "")
	{
		ui.cbContent->setCurrentIndex(-1);	
	}
}

