#include "MyLineEdit.h"
#include "FileCentre.h"

MyLineEdit::MyLineEdit(QWidget *parent) : QLineEdit(parent)
{
}


MyLineEdit::~MyLineEdit(void)
{
}

void MyLineEdit::focusOutEvent(QFocusEvent *e)
{
	//如果值改变，则保存当前值
	static QString tmp = "";
	QString name = this->objectName();
	if(tmp != name)
	{
		QString str = this->text();
		FileCentre *fc = FileCentre::GetInstance();	
		fc->SaveNameValue(name, str);
	}
	QLineEdit::focusOutEvent(e);
}