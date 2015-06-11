/*
 * =====================================================================================
 *
 *       Filename:  MainWindow.h
 *        Created:  2015/3/11 14:06:27
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  主窗体
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
	//加载新保存图片
	void loadNewImage(QString pathName);
	//全屏信号槽
	void fullScreenSlot(QString text);
	//响应fullScreen槽
	void callSlot(QString text);
	//处理图像窗体
	void imageSlot();

signals:
	//视频窗体全屏信号
	void fullScreen(QString text);

private:
	void initImage();

private:
	Ui::mainwindow ui;
	QScrollArea *sa;
	QWidget *mLW;
	QWidget *mCamera;
};

