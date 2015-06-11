#pragma once
#include <qwidget.h>
#include <qdiriterator.h>
#include "ui_recordwidget.h"

class RecordWidget :
	public QWidget
{
	Q_OBJECT
public:
	RecordWidget(QString from);
	~RecordWidget(void);

	//当对象不为空，且s_OBJ为0时，为野指针，需重新分配空间
	static int GetOBJ();

private slots:
	void closeSlot();
	void reportSlot();
	//获取当前行的值
	void changeSlot(int r, int c);
	//
	void todaySlot();
	void weekSlot();
	void monthSlot();
	void yearSlot();
	void allSlot();
	//搜索
	void searchSlot();

	//滚动条
	void sliderMovedSlot(int value);

signals:
	void closeSignal();
	void reportSignal();
	void changeSignal(QString path);

private:
	void loadRecord();
	//tablewidget当前页显示
	void currentPage();
	//查询页
	void searchPage();

private:
	Ui::recordwidget ui;
	static int s_OBJ;
	//当前选择的病案库路径
	QString mPath;
	//病案库目录
	QString mFilePath;

	//总文件
	QFileInfoList mFolderList;
	//当前页
	int miPage;
	//
	bool bLeName;
	bool bSbAge;
	//QDirIterator *mDirIterator;
};

