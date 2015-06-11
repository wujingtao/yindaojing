#include "MyComboBox.h"
#include "EditDialog.h"
#include "FileCentre.h"

#include <string>
#include <vector>
using std::vector;
using std::string;

MyComboBox::MyComboBox(QWidget *parent) : QComboBox(parent)
{
	mFlag = 0;
	setContextMenuPolicy(Qt::NoContextMenu);
}


MyComboBox::~MyComboBox(void)
{
}

void MyComboBox::mouseDoubleClickEvent ( QMouseEvent *e) 
{
	//��ȡ�ÿؼ����������ô���
	QString name = this->objectName();
	EditDialog dialog(this, name);
	dialog.exec();

	mFlag = 0;
}

void MyComboBox::mousePressEvent(QMouseEvent *e) 
{
	//����һ�μ��� 
	if(mFlag == 0)
	{
		//����������ݣ�������ֵ
		clear();

		QString s = this->objectName();
		vector<string> vecValue;
		FileCentre *fc = FileCentre::GetInstance();
		fc->readFile(s.toStdString(), vecValue);

		for(int i=0; i<vecValue.size(); i++)
		{
			addItem(QString::fromStdString(vecValue[i]));	
		}
		this->setCurrentIndex(-1);

		mFlag=1;
	}

	QComboBox::mousePressEvent(e);
}

void MyComboBox::focusOutEvent(QFocusEvent *e)
{
	//���ֵ�ı䣬�򱣴浱ǰֵ
	static QString tmp = "";
	QString name = this->objectName();
	if(tmp != name)
	{
		QString str = this->currentText();
		FileCentre *fc = FileCentre::GetInstance();
		fc->SaveNameValue(name, str);
	}

	QComboBox::focusOutEvent(e);
}

void MyComboBox::clear()
{
	mFlag = 0;
	QComboBox::clear();
}