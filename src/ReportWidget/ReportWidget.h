/*
 * =====================================================================================
 *
 *       Filename:  ReportWidget.h
 *        Created:  2014/10/29 17:31:00
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  报告单模块
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
	 *功能: 报表上Label加载图像
	 *参数: pathName in 图像全路径 
	 *返回: 
	 */
	void SetLabelLoad(const QString &pathName);
	//类对象计数，因QScroll的setWidget()后会自动删除对象，
	//当对象不为空，且s_OBJ为0时，为野指针，需重新分配空间
	static int GetOBJ();

protected:
	//每秒显示数据值
 void timerEvent( QTimerEvent *qevent );

private:
	//初始化控件值为空
	void initControl();
	//指定控件是否可编辑
	void controlEdit();
	//初始化按钮值
	void initButton(bool b);
	//加载病案值,path病案路径
	void controlValue(QString path);

	//初始化label图像
	void initLabel(int index, const QString &fullName);

	//初始化mylabel类
	void initMyLabelUi();

private slots:
	//关闭当前按钮的信号槽
	void closeSlot();
	void newSlot();
	void printViewSlot();
	void printPreview(QPrinter *printer);
	void printSlot();
	void contentSlot(QString text);
	void recordSlot();
	void cameraSlot();
	//阴道镜所见文本，combox槽
	void imageTextSlot(QString text);
	void saveReportSlot();
	void textEmptySlot();
	//图像处理按钮
	void imageSlot();
signals:
	void newSignal();
	void closeSignal();
	void recordSignal();
	void cameraSignal();

	//图像处理信号
	void imageSignal();

private:
	Ui::reportwidget ui;
	//新建报表名
	static QString s_mTextName;
	static int s_OBJ;
	QString mCheckTime;

	MyLabel *lb1;
    MyLabel *lb2;
    MyLabel *lb3;
    MyLabel *lb4;
};

#endif   /* ----- #ifndef REPORTWIDGET_INC  ----- */
