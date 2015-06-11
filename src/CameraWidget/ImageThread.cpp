#include "ImageThread.h"

#include "RWBmp.h"

//#include "Fusion.h"
#include "FusionAlg.h"
#include "FlyCapture.h"
#include "ViewWidget.h"
#include <QTime>
//flycapture
#include "Camera.h"
#include "Image.h"

#include <fstream>
#include <sstream>
using std::ofstream;
using std::stringstream;
using std::endl;

int GlobalArgs::g_radio = 0;
unsigned int ImageThread::s_mCurrentMode = 0;
bool ImageThread::s_mStop = true;
ImageThread::ImageThread(FlyCapture2::Camera *pCamera, FusionAlg *fusionAlg) : 
									mpCamera(pCamera),mFusionAlg(fusionAlg)
{

	mpImageR = NULL;
	mpImageG = NULL;
	mpImageB = NULL;

	mbR = false;
	mbG = false;
	mbB = false;

	mbPause = false;
}


ImageThread::~ImageThread(void)
{
	if(mpImageR != NULL)
	{
		delete[] mpImageR;
		mpImageR = NULL;
	}
	if(mpImageG != NULL)
	{
		delete[] mpImageG;
		mpImageG = NULL;
	}
	if(mpImageB != NULL)
	{
		delete[] mpImageB;
		mpImageB = NULL;
	}
}

void ImageThread::run()
{
	showCamImage();
	//showImage24();
}

void ImageThread::showImage24()
{
	FlyCapture2::Image processedImage, convertedImage;

	//ͼ���С����
	const int iWidth = FlyCapture::GetImageWidth();
	const int iHeight = FlyCapture::GetImageHeight();
	const int iImageSize = iWidth * iHeight;

	QWaitCondition pauseWaitCondition;

	//�㷨�߳�
	//mFusionAlg->fusioning();
	mFusionAlg->fusioningS();

	//gpio��ƽ����
	unsigned int gpio3Add = 0;
	unsigned int gpio4Add = 0;
	unsigned int cColor = 0;

	//��ʼ��rgb����
	if(mpImageR == NULL)
	{
		mpImageR = new unsigned char[iImageSize];
	}
	if(mpImageG == NULL)
	{
		mpImageG = new unsigned char[iImageSize];
	}
	if(mpImageB == NULL)
	{
		mpImageB = new unsigned char[iImageSize];
	}

	//TODO:���ڼ�¼����
	QTime t;
	t.start();
	
#ifdef DEF_ImageThread
	ofstream ofs("imageThread");
#endif

	while(true)	
	{
		t.restart();
		//��ȡ����
		mErr = mpCamera->RetrieveBuffer( &processedImage);
		if(mErr != FlyCapture2::PGRERROR_OK)
		{
			break;
		}

#ifdef DEF_ImageThread
		int ttime = t.elapsed();
		stringstream sstr;
		sstr<<ttime<<endl;
		ofs<<sstr.str();
#endif
		/*
		//��ȡ��ƽ
		mpCamera->ReadRegister(OPGPIO::GPIO3_ADD, &gpio3Add);
		mpCamera->ReadRegister(OPGPIO::GPIO4_ADD, &gpio4Add);
		int iL = gpio3Add & 0x0001;
		int iH = gpio4Add & 0x0001;
		cColor = (iH<<1) + iL;	
		*/
		if(cColor == 3)
		{
			cColor = 1;	
		}
		else
		{
			++cColor;	
		}	




		//TODO: ��ǰģʽ���޸�
		int mode = s_mCurrentMode;
		if(mode == OPGPIO::RGB)
		{
			switch(cColor)	
			{
			case OPGPIO::RColor:
				memcpy(mpImageR, processedImage.GetData(), iImageSize);
				mbR = true;
				++GlobalArgs::g_radio;
				break;
			case OPGPIO::GColor:
				memcpy(mpImageG, processedImage.GetData(), iImageSize);
				mbG= true;
				++GlobalArgs::g_radio;
				break;
			case OPGPIO::BColor:
				memcpy(mpImageB, processedImage.GetData(), iImageSize);
				mbB= true;
				++GlobalArgs::g_radio;
				break;
			}
		}

		//if(mbR && mbB && mbG)
		{
			switch(mode)
			{
			case OPGPIO::RGB:
				/*
				unsigned int ttime = t.elapsed();
				if(ttime < 30)
				{
					msleep(30 - ttime);	
				}
				*/

				mFusionAlg->AddRGB(mpImageR, mpImageG, mpImageB);
				break;
			}

			/*
			//��д��ͣ�߳�
			while(mbPause)
			{
				msleep(1000);
				continue;
			}
			*/

			if(mbPause)
			{
				mMutex.lock();
				mWaitCondition.wait(&mMutex);	
				mMutex.unlock();
			}
		}


	}
}

void ImageThread::showCamImage()
{
	s_mStop = false;

	const int iWidth = FlyCapture::GetImageWidth();
	const int iHeight = FlyCapture::GetImageHeight();
	const int iImageSize = iWidth * iHeight;

	FlyCapture2::Image rawImage,processedImage;
	QTime t;
	t.start();

	//������ʱ��
	unsigned int ttime = 0;
	while(!s_mStop)
	{
		t.restart();

		//��ȡͼ��
		mErr = mpCamera->RetrieveBuffer(&rawImage);
		if(mErr != FlyCapture2::PGRERROR_OK)
		{
			//string str = mErr.GetDescription();
			continue;
		}

		//mErr = rawImage.Convert( FlyCapture2::PIXEL_FORMAT_RAW8, &processedImage );
		mErr = rawImage.Convert( FlyCapture2::PIXEL_FORMAT_BGR, &processedImage );
		if(mErr != FlyCapture2::PGRERROR_OK)
		{
			//string str = mErr.GetDescription();
			continue;
		}
		//int size = processedImage.GetDataSize();
		//����ͼ�񵽶���
		mFusionAlg->AddImage(processedImage.GetData());

		if(mbPause)
		{
			mMutex.lock();
			mWaitCondition.wait(&mMutex);	
			mMutex.unlock();
		}

		//30ms��ȡ1֡
		ttime = t.elapsed();
		if(ttime < 30)
		{
			msleep(30 - ttime);	
		}
	}

}

void ImageThread::SetPause(bool pause)
{
	mbPause = pause;
	if(mbPause == false)
	{
		mWaitCondition.wakeAll();
	}
}

bool ImageThread::GetRGB(unsigned char** r, unsigned char** g, unsigned char** b)
{
	if(mpImageR == NULL || mpImageG == NULL || mpImageB == NULL)
	{
		return false;	
	}
	*r = mpImageR;
	*g = mpImageR;
	*b = mpImageR;

	return true;
}
