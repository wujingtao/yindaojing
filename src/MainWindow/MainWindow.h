/*
 * =====================================================================================
 *
 *       Filename:  MainWindow.h
 *        Created:  2015/3/11 14:06:27
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  ������
 *
 * =====================================================================================
 */

#pragma once
#include <QWidget>
#include "ui_mainwindow.h"

class MainWindow :
	public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow(void);

private slots:
	void reportSlot();
	void homeSlot();
	void recordSlot(QString from = "");
	void changeSlot(QString path="");
	void cameraSlot();
	//�����±���ͼƬ
	void loadNewImage(QString pathName);
	//ȫ���źŲ�
	void fullScreenSlot(QString text);
	//��ӦfullScreen��
	void callSlot(QString text);
	//����ͼ����
	void imageSlot();

signals:
	//��Ƶ����ȫ���ź�
	void fullScreen(QString text);

private:
	void initImage();

private:
	Ui::mainwindow ui;
	QScrollArea *sa;
	QWidget *mLW;
	QWidget *mCamera;
};

