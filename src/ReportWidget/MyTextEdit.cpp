#include "MyTextEdit.h"
#include "FileCentre.h"

MyTextEdit::MyTextEdit(QWidget *parent) : QTextEdit(parent)
{
}


MyTextEdit::~MyTextEdit(void)
{
}

void MyTextEdit::focusOutEvent(QFocusEvent *e)
{
	//���ֵ�ı䣬�򱣴浱ǰֵ
	static QString tmp = "";
	QString name = this->objectName();
	QString str = this->toPlainText();
	if(tmp != name)
	{
		FileCentre *fc = FileCentre::GetInstance();	
		fc->SaveNameValue(name, str);
	}

	if(str == "")
	{
		emit textEmptySignal();	
	}

	QTextEdit::focusOutEvent(e);
}