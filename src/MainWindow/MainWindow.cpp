#include "MainWindow.h"
#include "MainWidget.h"
#include <qdir.h>
#include "WidgetFactory.h"

#include "ReportFactory.h"
#include "RecordFactory.h"
#include "CameraFactory.h"
#include "FileCentre.h"
#include "ImageFactory.h"

#include <fstream>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	ui.pbClose->setToolTip(QStringLiteral("关闭软件"));
	sa = NULL;

	//加载界面窗体
	homeSlot();

	//关闭
	connect(ui.pbClose, SIGNAL(clicked()), this, SLOT(close()));
	//视频窗体全屏信号
	connect(this, SIGNAL(fullScreen(QString)), this, SLOT(callSlot(QString)));

	QString hint = "";
	FileCentre *fc = FileCentre::GetInstance();
	fc->ReadSystemValue("windowhint", hint);
	if(hint == "1")
	{
		setWindowState(Qt::WindowFullScreen);
	}
	else
	{
		setWindowState( Qt::WindowMaximized );
	}
}


MainWindow::~MainWindow(void)
{
}

void MainWindow::homeSlot()
{
	MainWidget *mw = new MainWidget();
	ui.scrollArea->setWidget(mw);
	WidgetFactory::SetCurrentWidget(WidgetFactory::Home);

	connect(mw, SIGNAL(startSignal()), this, SLOT(reportSlot()));
	connect(mw, SIGNAL(recordSignal(QString)), this, SLOT(recordSlot(QString)));

	changeSlot("");
}

void MainWindow::reportSlot()
{
	//ReportFactory *rf = new ReportFactory();	
	//QWidget *report = rf->CreateReport();
	QWidget *report = ReportFactory::CreateReport();
	ui.scrollArea->setWidget(report);
	WidgetFactory::SetCurrentWidget(WidgetFactory::Report);

	//关闭报表
	connect(report, SIGNAL(closeSignal()), this, SLOT(homeSlot()));
	//病案库
	connect(report, SIGNAL(recordSignal()), this, SLOT(recordSlot()));
	//采集图像
	connect(report, SIGNAL(cameraSignal()), this, SLOT(cameraSlot()));
	//处理图像
	connect(report, SIGNAL(imageSignal()), this, SLOT(imageSlot()));
	//新建清空图片label
	connect(report, SIGNAL(newSignal()), this, SLOT(changeSlot()));

	FileCentre *fc = FileCentre::GetInstance();
	QString path = fc->GetRecordPath();
	changeSlot(path);
}

void MainWindow::recordSlot(QString from)
{
	QWidget* record = RecordFactory::CreateRecord(from);
	ui.scrollArea->setWidget(record);	
	WidgetFactory::SetCurrentWidget(WidgetFactory::Record);

	connect(record, SIGNAL(closeSignal()), this, SLOT(homeSlot()));
	connect(record, SIGNAL(reportSignal()), this, SLOT(reportSlot()));
	connect(record, SIGNAL(changeSignal(QString)), this, SLOT(changeSlot(QString)));

}

void MainWindow::cameraSlot()
{

	QWidget* camera = CameraFactory::CreateCamera();	
	ui.scrollArea->setWidget(camera);
	WidgetFactory::SetCurrentWidget(WidgetFactory::Camera);
	camera->setFocus();

	connect(camera, SIGNAL(backSignal()), this, SLOT(reportSlot()));
	connect(camera, SIGNAL(imageSignal(QString)), this, SLOT(loadNewImage(QString)));
	connect(camera, SIGNAL(fullScreenSignal(QString)), this, SLOT(fullScreenSlot(QString)));
}

void MainWindow::imageSlot()
{
	QWidget* image = ImageFactory::CreateImage();	
	ui.scrollArea->setWidget(image);
	WidgetFactory::SetCurrentWidget(WidgetFactory::Image);

	connect(image, SIGNAL(backSignal()), this, SLOT(reportSlot()));
}

void MainWindow::fullScreenSlot(QString text)
{
	emit fullScreen(text);
	/*
	QWidget* camera = CameraFactory::CreateCamera();	

	if(text != QStringLiteral("全屏显示"))
	{
		camera->setParent(this);
		//camera->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
		camera->setWindowFlags(Qt::Window);
		camera->showFullScreen();
		//camera->move(400,400);
		//camera->showMaximized();
		//camera->setFocus();
	}	
	else
	{
		camera->setParent(ui.scrollArea);
		camera->show();
		camera->setFocus();
	}
	*/
}

void MainWindow::callSlot(QString text)
{
	ui.scrollArea->setWidget(new QWidget());
	QWidget* camera = CameraFactory::CreateCamera();	

	if(text == QStringLiteral("全屏显示"))
	{
		CameraFactory::SetLBScreen(QStringLiteral("屏幕恢复"));

		camera->setParent(this);
		camera->setWindowFlags(Qt::Window);
		camera->showFullScreen();
		camera->setFocus();
	}	
	else
	{
		CameraFactory::SetLBScreen(QStringLiteral("全屏显示"));
		ui.scrollArea->setWidget(camera);
		camera->setFocus();
		//camera->setParent(ui.scrollArea);
		//camera->show();
		//camera->setFocus();
	}

	connect(camera, SIGNAL(backSignal()), this, SLOT(reportSlot()));
	connect(camera, SIGNAL(imageSignal(QString)), this, SLOT(loadNewImage(QString)));
	connect(camera, SIGNAL(fullScreenSignal(QString)), this, SLOT(fullScreenSlot(QString)));
}


void MainWindow::changeSlot(QString path)
{
	//TODO:路径需动态修改
	//if(path == "")
	//{
	//	path = "f:/img";
	//}
	

	//文件路径过滤
	QDir dir(path);
	QStringList filter;
	filter<<"*.png"<<"*.jpg"<<"*.bmp";
	dir.setNameFilters(filter);
	int imageNum = dir.count();
	QFileInfoList fileInfo = dir.entryInfoList();
	
	//加载图片和滚动区域
	if(sa != NULL)
	{
		delete sa;
		sa = NULL;
	}

	sa = new QScrollArea(ui.wgImage);
	sa->setFrameShape(QFrame::NoFrame);

	
	mLW = new QWidget(sa);
	for(int i=0; i<imageNum; i++)
	{
		//获取文件全路径
		QString s = fileInfo.at(i).filePath();

		//MyLabel *lb = new MyLabel(mLW,s);	
		QLabel *lb = WidgetFactory::GetLabel(mLW, s);
        lb->setGeometry(QRect(10, i*190, 180, 180));

		lb->setPixmap(s);
		lb->setScaledContents(true);

	}
	//设置大小后有滚动区域
	sa->setWidget(mLW);
	sa->setGeometry(0,0, 210, 820);
	mLW->setGeometry(0,0,190,190*(imageNum+1));

	sa->show();

}

void MainWindow::loadNewImage(QString pathName)
{
	if(sa == NULL)
	{return;}

	FileCentre *fc = FileCentre::GetInstance();
	QString path = fc->GetRecordPath();

	QDir dir(path);
	QStringList filter;
	filter<<"*.png"<<"*.jpg"<<"*.bmp";
	dir.setNameFilters(filter);
	int iNum = dir.count();
	if(iNum < 1)
	{return;}

	//MyLabel *lb = new MyLabel(mLW, pathName);
	QLabel *lb = WidgetFactory::GetLabel(mLW, pathName);
	lb->setGeometry(QRect(10, (iNum-1)*190, 180, 180));
	lb->setPixmap(pathName);
	lb->setScaledContents(true);
	lb->show();
	/*
	sa->setWidget(mLW);
	sa->setGeometry(0,0, 210, 820);
	mLW->setGeometry(0,0,190,190*(iNum+1));
	mLW->show();
	sa->show();
	*/
	mLW->setGeometry(0,0,190,190*(iNum+1));
}