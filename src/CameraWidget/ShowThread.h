/*
 * =====================================================================================
 *
 *       Filename:  ShowThread.h
 *        Created:  2014/7/30 10:52:05
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  显示图像
 *
 * =====================================================================================
 */
#ifndef  SHOWTHREAD_INC
#define  SHOWTHREAD_INC

#include <qthread.h>
#include <qobject.h>
#include <qwaitcondition.h>
#include <qmutex.h>
#include <QtGui\qimage.h>

namespace FlyCapture2
{
	class Camera;
}
class FlyCapture;
class FusionAlg;
class ShowThread : public QThread
{
	Q_OBJECT
public:
	ShowThread( FusionAlg *fusion);
	~ShowThread(void);

public:
	//保存当前图像,path文件夹路径,返回文件名路径
	QString SaveImage();
	void SetPath(QString path)
	{
		mSavePath = path;	
		mVideoPath = path+"/video";
	}
	//保存录像
	void SaveVideo();
	//停止当前线程
	void Stop()
	{
		s_mStop = true;	
	}

	void setFlyCapture(FlyCapture *fc)
	{
		mFC = fc;	
	}
	int GetSize() const
	{
		return mSize;	
	}

signals:
	/* 
	 *功能: 当获取到图像后发送该信号.主窗体会接收该信号.
	 *参数: buffer in bmp图像
	        iSize in bmp大小
	 *返回: void
	 */
	void ImageSignal(QImage image);

//继承方法
protected:
	void run();

private:
	FusionAlg *mFusionAlg;
	//当前图像
	//unsigned char* mImage;
	//当前图像
	unsigned char* mBuffer;
	//图像类
	QImage mImage;
	//路径名
	//QString mPath;
	//时间文件名
	//QString mTmpPath;
	//当前时间
	//QString mStrTime;
	int mSize;
	static bool s_mStop;
	//暂停图像，用于保存当前图像
	//QWaitCondition mWaitCondition;
	QMutex mMutex;
	//暂停标志
	bool mbPause;
	FlyCapture *mFC;
	//当前图片路径
	QString mSavePath;
	//录像保存路径
	QString mVideoPath;
};

#endif   /* ----- #ifndef SHOWTHREAD_INC  ----- */
