/*
 * =====================================================================================
 *
 *       Filename:  ReportWidget.h
 *        Created:  2014/10/29 17:31:00
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  ���浥ģ��
 *
 * =====================================================================================
 */

#ifndef  REPORTWIDGET_INC
#define  REPORTWIDGET_INC


#include <QWidget>
//#include "MyComboBox.h"
#include "ui_reportwidget.h"

class QPrinter;
class QTextEdit;
class MyLabel;
class ReportWidget :
	public QWidget
{
	Q_OBJECT
public:
	ReportWidget(void);
	~ReportWidget(void);

public:
	/* 
	 *����: ������Label����ͼ��
	 *����: pathName in ͼ��ȫ·�� 
	 *����: 
	 */
	void SetLabelLoad(const QString &pathName);
	//������������QScroll��setWidget()����Զ�ɾ������
	//������Ϊ�գ���s_OBJΪ0ʱ��ΪҰָ�룬�����·���ռ�
	static int GetOBJ();

protected:
	//ÿ����ʾ����ֵ
 void timerEvent( QTimerEvent *qevent );

private:
	//��ʼ���ؼ�ֵΪ��
	void initControl();
	//ָ���ؼ��Ƿ�ɱ༭
	void controlEdit();
	//��ʼ����ťֵ
	void initButton(bool b);
	//���ز���ֵ,path����·��
	void controlValue(QString path);

	//��ʼ��labelͼ��
	void initLabel(int index, const QString &fullName);

	//��ʼ��mylabel��
	void initMyLabelUi();

private slots:
	//�رյ�ǰ��ť���źŲ�
	void closeSlot();
	void newSlot();
	void printViewSlot();
	void printPreview(QPrinter *printer);
	void printSlot();
	void contentSlot(QString text);
	void recordSlot();
	void cameraSlot();
	//�����������ı���combox��
	void imageTextSlot(QString text);
	void saveReportSlot();
	void textEmptySlot();
	//ͼ����ť
	void imageSlot();
signals:
	void newSignal();
	void closeSignal();
	void recordSignal();
	void cameraSignal();

	//ͼ�����ź�
	void imageSignal();

private:
	Ui::reportwidget ui;
	//�½�������
	static QString s_mTextName;
	static int s_OBJ;
	QString mCheckTime;

	MyLabel *lb1;
    MyLabel *lb2;
    MyLabel *lb3;
    MyLabel *lb4;
};

#endif   /* ----- #ifndef REPORTWIDGET_INC  ----- */
