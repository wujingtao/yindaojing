/*
 * =====================================================================================
 *
 *       Filename:  ImageThread.h
 *        Created:  2014/7/8 10:07:37
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  �߳��࣬����ͼ��
 *
 * =====================================================================================
 */

#ifndef  IMAGETHREAD_INC
#define  IMAGETHREAD_INC


#include "OpDefs.h"
//qt
#include <qthread.h>
#include <qwaitcondition.h>
#include <qmutex.h>

//flycapture
#include "Error.h"
namespace FlyCapture2
{
	class Camera;
}

//class Fusion;
class FusionAlg;
class ImageThread :
	public QThread
{
public:
	ImageThread(FlyCapture2::Camera *pCamera, FusionAlg *fusionAlg);
	~ImageThread(void);

public:
	//�����߳���ͣ��־
	void SetPause(bool pause);

	//��ȡ��ǰrgb,���ڱ���ͼƬ
	bool GetRGB(unsigned char** r, unsigned char** g, unsigned char** b);

	//ֹͣ�߳�
	void Stop()
	{
		s_mStop = true;	
	}

private:

	/* 
	 *����: ��ʾ���ͼ��
	 *����: null
	 *����: void
	 */
	void showCamImage();

	/* 
	 *����: ��ʾ�ϳɵ�24λͼ��
	 *����: null
	 *����: void
	 */
	void showImage24();


	//�̳з���
protected:
	void run();

private:
	FlyCapture2::Camera* mpCamera;
	FusionAlg* mFusionAlg;
	unsigned char *mpImageR;
	unsigned char *mpImageG;
	unsigned char *mpImageB;

	FlyCapture2::Error mErr;
	//��ͣͼ���߳�
	QWaitCondition mWaitCondition;
	QMutex mMutex;
	//Ĭ��Ϊ0,3��Ϊ1Ϊһ����
	bool mbR;
	bool mbB;
	bool mbG;


	bool mbPause;

	//��ǰͼ��ϳ�ģʽ
	static unsigned int s_mCurrentMode;

	//�Ƿ�ֹͣ�߳�
	static bool s_mStop;
};

#endif   /* ----- #ifndef IMAGETHREAD_INC  ----- */
