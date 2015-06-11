#include "MySpinBox.h"
#include "FileCentre.h"

MySpinBox::MySpinBox(QWidget *parent) : QSpinBox(parent)
{
}


MySpinBox::~MySpinBox(void)
{
}
void MySpinBox::focusOutEvent(QFocusEvent *e)
{
	//���ֵ�ı䣬�򱣴浱ǰֵ
	static QString tmp = "";
	QString name = this->objectName();
	if(tmp != name)
	{
		int iv = this->value();
		FileCentre *fc = FileCentre::GetInstance();	
		fc->SaveNameValue(name, QString("%1").arg(iv));
	}
	QSpinBox::focusOutEvent(e);
}