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
	//�����ǰ����Ϊ������,����Ӧ�����¼�
		//����lb1-4��ͼƬȡ��
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