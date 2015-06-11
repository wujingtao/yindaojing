#include "MyLabel.h"

#include "ReportFactory.h"
#include "ImageFactory.h"
#include "WidgetFactory.h"

#include "qmessagebox.h"

int MyLabel::mNameWidget = WidgetFactory::Home;
//QString MyLabel::mStrImage[] = {""};
MyLabel::MyLabel(QWidget *parent, QString path) : QLabel(parent)
{
	mPathName = path;
}


void MyLabel::mousePressEvent(QMouseEvent *e)
{
	//报表窗体,响应单击事件
	if(mNameWidget == WidgetFactory::Report)
	{
		ReportFactory::ReportLabelLoad(mPathName);
	}
	//图像窗体,响应单击事件
	else if(mNameWidget == WidgetFactory::Image)
	{
		ImageFactory::ImageLabelLoad(mPathName);
	
	}
}


void MyLabel::SetCurrentWidget(int nw)
{
	mNameWidget = nw;
}