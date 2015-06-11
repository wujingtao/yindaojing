/*
 * =====================================================================================
 *
 *       Filename:  ShowThread.h
 *        Created:  2014/7/30 10:52:05
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  ��ʾͼ��
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
	//���浱ǰͼ��,path�ļ���·��,�����ļ���·��
	QString SaveImage();
	void SetPath(QString path)
	{
		mSavePath = path;	
		mVideoPath = path+"/video";
	}
	//����¼��
	void SaveVideo();
	//ֹͣ��ǰ�߳�
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
	 *����: ����ȡ��ͼ����͸��ź�.���������ո��ź�.
	 *����: buffer in bmpͼ��
	        iSize in bmp��С
	 *����: void
	 */
	void ImageSignal(QImage image);

//�̳з���
protected:
	void run();

private:
	FusionAlg *mFusionAlg;
	//��ǰͼ��
	//unsigned char* mImage;
	//��ǰͼ��
	unsigned char* mBuffer;
	//ͼ����
	QImage mImage;
	//·����
	//QString mPath;
	//ʱ���ļ���
	//QString mTmpPath;
	//��ǰʱ��
	//QString mStrTime;
	int mSize;
	static bool s_mStop;
	//��ͣͼ�����ڱ��浱ǰͼ��
	//QWaitCondition mWaitCondition;
	QMutex mMutex;
	//��ͣ��־
	bool mbPause;
	FlyCapture *mFC;
	//��ǰͼƬ·��
	QString mSavePath;
	//¼�񱣴�·��
	QString mVideoPath;
};

#endif   /* ----- #ifndef SHOWTHREAD_INC  ----- */
