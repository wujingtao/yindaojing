#include "ShowThread.h"

//#include "Fusion.h"
#include "FusionAlg.h"
#include "RWBmp.h"
#include "FlyCapture.h"
#include "ViewWidget.h"
#include "Camera.h"


//#include "Log.h"
//qt
#include <qdir.h>
#include <qbuffer.h>

#include <QTime>
#include <fstream>
#include <sstream>
using std::ofstream;
using std::stringstream;
using std::endl;

#include <assert.h>

int GlobalArgs::g_frame = 0;
bool ShowThread::s_mStop = true;
ShowThread::ShowThread(FusionAlg *fusion)
	:mFusionAlg(fusion)
{
	mFC = NULL;

	//mImage = NULL;
	mbPause = false;
}


ShowThread::~ShowThread(void)
{
	/*
	if(mImage != NULL)
	{
		delete mImage;	
		mImage = NULL;
	}
	*/

}

void ShowThread::run()
{
	s_mStop = false;

	const int iWidth = FlyCapture::GetImageWidth();
	const int iHeight = FlyCapture::GetImageHeight();

	unsigned char* pImage = 0;

#ifdef QTEST
	ofstream ofs("ShowImage");
#endif

	QTime t;
	t.start();

	unsigned int ttime = 0;
	while(!s_mStop)	
	{
		if(!mFusionAlg->GetImage(&pImage))	
		{
			continue;	
		}
		t.restart();

		ttime = t.elapsed();
		if(ttime < 30)
		{
			msleep(30 - ttime);	
		}

		#ifdef QTEST
		if(ofs.is_open())
		{
			stringstream ss;	
			ss<<t.elapsed();
			ofs<<ss.str()<<endl;
		}
		#endif

		mSize = 0;
		if(pImage != 0)
		{
			mBuffer = RWBmp::Get24BitBmp(pImage, iWidth, iHeight, mSize);

		}


		mFusionAlg->ReleaseImage();

		if(mBuffer != NULL)
		{
			++GlobalArgs::g_frame;

			//用于保存图片
			mMutex.lock();
			mImage.loadFromData(mBuffer, mSize);
			mMutex.unlock();
			emit ImageSignal(mImage);	
		}


	}
}


QString ShowThread::SaveImage()
{
	QString strTime = QTime::currentTime().toString("hhmmsszzz");
	QString tmpPath = mSavePath+"/"+strTime+".bmp";

	mMutex.lock();
	mImage.save(tmpPath, "BMP");
	float shutter = mFC->GetShutter();
	float gain = mFC->GetGain();
	mMutex.unlock();

	//创建文件夹
	QDir dir;
	if(!dir.exists(tmpPath))
	{
		dir.mkpath(tmpPath);	
	}

	QString info = mSavePath+"/info.txt";

	ofstream ofsInfo(info.toStdString(), ofstream::app);
	stringstream ss;
	ss<<strTime.toStdString()<<".bmp"<<"    shutter:"
		<<shutter<<"    gain: "
		<<gain<<endl;
	ofsInfo<<ss.str();

	return tmpPath;
}

void ShowThread::SaveVideo()
{
	QString strTime = QTime::currentTime().toString("hhmmsszzz");
	QString tmpPath = mVideoPath+"/"+strTime+".bmp";

	mMutex.lock();
	mImage.save(tmpPath, "BMP");
	//float shutter = mFC->GetShutter();
	//float gain = mFC->GetGain();
	mMutex.unlock();

	/*
	//创建文件夹
	QDir dir;
	if(!dir.exists(tmpPath))
	{
		dir.mkpath(tmpPath);	
	}

	QString info = pa+"/info.txt";

	ofstream ofsInfo(info.toStdString(), ofstream::app);
	stringstream ss;
	ss<<strTime.toStdString()<<".bmp"<<"    shutter:"
		<<shutter<<"    gain: "
		<<gain<<endl;
	ofsInfo<<ss.str();
	*/
}