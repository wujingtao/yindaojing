#include "MyLabel.h"
#include "ReportWidget.h"

MyLabel::MyLabel(QWidget *parent) 
	: QLabel(parent)
{
}


MyLabel::~MyLabel(void)
{
}

void MyLabel::mousePressEvent(QMouseEvent *e)
{
	//如果当前窗体为报表窗体,则响应单击事件
		//单击lb1-4，图片取消
	clear();
	/*
	QString lb = this->objectName();
	int i = lb.mid(2).toInt();
	ReportWidget::SetLabelIndex(i);	
	*/
}

void MyLabel::setMyPixmap(const QString &fullName)
{
	QPixmap pixmap;
	if(pixmap.load(fullName))
	{
		this->setPixmap(pixmap);	
	}
}