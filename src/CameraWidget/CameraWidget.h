/*
 * =====================================================================================
 *
 *       Filename:  CameraWidget.h
 *        Created:  2014-11-19 16:34:09
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  视频窗体
 *
 * =====================================================================================
 */

#ifndef  CAMERAWIDGET_INC
#define  CAMERAWIDGET_INC

#include <QtWidgets/qwidget.h>
#include "ui_camerawidget.h"
#include <QTime>
#include <QtSerialPort/QSerialPort>


class FlyCapture;
class FusionAlg;
class ImageThread;
class ShowThread;
class ViewWidget;
class CameraWidget :
	public QWidget
{
	Q_OBJECT
public:
	CameraWidget(void);
	~CameraWidget(void);

	struct Rec{
	QString freeze, zoomi, zoomd;
	};

public:
	//类对象计数，因setWidget()后会自动删除对象，
	//当对象不为空，且s_OBJ为0时，为野指针，需重新分配空间
	static int GetOBJ();

	//设置label值
	void SetLBScreen(QString text)
	{
		if(text == QStringLiteral("屏幕恢复"))
		{
			ui.pbBack->setEnabled(false);	
		}
		else
		{
			ui.pbBack->setEnabled(true);	
		}
		ui.lbScreen->setText(text);
	}

	//继承
protected:
	//每秒显示数据值
 void timerEvent( QTimerEvent *qevent );
 void keyPressEvent(QKeyEvent *qevent);

private:
	//启动
	void begin();
	//初始化界面按钮 
	void initButton(bool b);
	//打开串口
	void openPort();

private slots:
	//返回
	void backSlot();
	//暂停
	void pauseSlot();
	//保存
	void saveSlot();
	//
	void ImageSlot(QImage image);
	//录像
	void videoSlot();
	//全屏
	void fullScreenSlot();
	//自动保存
	void autoSaveSlot();
	//串口接收消息
	void readData();

signals:
	void backSignal();
	//加载图像到label，pathName全路径名
	void imageSignal(QString pathName);
	//全屏
	void fullScreenSignal(QString text);

private:
	//串口
	QSerialPort *mSerialPort;

	//算法类
	FusionAlg* mFusionAlg;
	//图像处理类
	ImageThread *mImgTrd;
	//图像显示
	ShowThread *mShowTrd;
	//相机类
	FlyCapture *mFC;

	Ui::camerawidget ui;
	static int s_OBJ;

	ViewWidget *mViewWidget;
	int mTimeId;
	//自动录像时间
	QTime mTime;
	//是否自动保存
	bool mbAutoSave;
	int miAutoSecond;
	//总数
	float mfSum;

	Rec mRec;
};

#endif   /* ----- #ifndef CAMERAWIDGET_INC  ----- */
