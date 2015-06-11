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

	//������Ϊ�գ���s_OBJΪ0ʱ��ΪҰָ�룬�����·���ռ�
	static int GetOBJ();

private slots:
	void closeSlot();
	void reportSlot();
	//��ȡ��ǰ�е�ֵ
	void changeSlot(int r, int c);
	//
	void todaySlot();
	void weekSlot();
	void monthSlot();
	void yearSlot();
	void allSlot();
	//����
	void searchSlot();

	//������
	void sliderMovedSlot(int value);

signals:
	void closeSignal();
	void reportSignal();
	void changeSignal(QString path);

private:
	void loadRecord();
	//tablewidget��ǰҳ��ʾ
	void currentPage();
	//��ѯҳ
	void searchPage();

private:
	Ui::recordwidget ui;
	static int s_OBJ;
	//��ǰѡ��Ĳ�����·��
	QString mPath;
	//������Ŀ¼
	QString mFilePath;

	//���ļ�
	QFileInfoList mFolderList;
	//��ǰҳ
	int miPage;
	//
	bool bLeName;
	bool bSbAge;
	//QDirIterator *mDirIterator;
};

