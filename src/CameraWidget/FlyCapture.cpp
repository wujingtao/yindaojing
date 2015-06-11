#include "FlyCapture.h"

#include "OpDefs.h"

//FlyCapture2
#include "BusManager.h"
#include "Camera.h"

//测试
#include <QTime>
#include <fstream>
#include <sstream>
using std::ofstream;
using std::stringstream;
using std::endl;
 
#include "FlyCapture2Defs.h"

int FlyCapture::s_ImageWidth = 0;
int FlyCapture::s_ImageHeight = 0;
int FlyCapture::s_ImageMaxWidth = 0;
int FlyCapture::s_ImageMaxHeight = 0;

FlyCapture::FlyCapture(int wImage, int hImage, int wMax, int hMax, bool bLan) 
	: mpCamera(NULL)
{
	s_ImageWidth = wImage;
	s_ImageHeight = hImage;
	s_ImageMaxWidth = wMax;
	s_ImageMaxHeight = hMax;
	mbLan = bLan;
}

FlyCapture::~FlyCapture()
{
	if(mpCamera != NULL)
	{
		mpCamera->StopCapture();	
		delete mpCamera;
		mpCamera = NULL;
	}
}


bool FlyCapture::Init(string &sMsg)
{
	FlyCapture2::BusManager busMangager;

	int ImageWidth = s_ImageWidth;
	int ImageHeight = s_ImageHeight;
	int MaxWidth = s_ImageMaxWidth;
	int MaxHeight = s_ImageMaxHeight;



	if(mbLan)
	{ 
		FlyCapture2::CameraInfo camInfo[1];
		unsigned int numCamInfo = 1;
		mErr = FlyCapture2::BusManager::DiscoverGigECameras( camInfo, &numCamInfo );
		if (mErr != FlyCapture2::PGRERROR_OK)
		{
			return false;
		}

		mErr = FlyCapture2::BusManager::ForceAllIPAddressesAutomatically();
		if(mErr != FlyCapture2::PGRERROR_OK)
		{
			return false;
		}

		busMangager.RescanBus();
	}

	//1.获取已连接相机的数量
	unsigned int iNumCamera = 0;
	mErr = busMangager.GetNumOfCameras(&iNumCamera);

	if (mErr != FlyCapture2::PGRERROR_OK)
	{
		sMsg = "GetNumOfCameras error:";

		return false;
	}
	
	if (iNumCamera < 1)
	{
		sMsg = "iNumCamera < 1";
		return false;
	}
	
	//2.获取连接相机的标识
	FlyCapture2::PGRGuid pgrGuid;
	mErr = busMangager.GetCameraFromIndex(0, &pgrGuid);
	if (mErr != FlyCapture2::PGRERROR_OK)
	{
		sMsg = "GetCameraFromIndex error:";
		return false;
	}

	//3.根据相机标识连接相机
	mpCamera = new FlyCapture2::Camera();
	mErr = mpCamera->Connect(&pgrGuid);
	if (mErr != FlyCapture2::PGRERROR_OK)
	{
		sMsg = "Connect camera error:";
		return false;
	}

	//OPGPIO::VIEWIMAGE image = OPGPIO::Twenty;

	//4.设置GPIO
	mpCamera->SetGPIOPinDirection(OPGPIO::GPIO3, 0);
	mpCamera->SetGPIOPinDirection(OPGPIO::GPIO4, 0);

	//5.设置触发模式
	FlyCapture2::TriggerMode triggerMode;
	mErr = mpCamera->GetTriggerMode( &triggerMode );
	// Set camera to trigger mode 0
	triggerMode.onOff = false;
	triggerMode.polarity=1;
	triggerMode.source=0;
	triggerMode.mode = 1;
	triggerMode.parameter = 0;
	mErr = mpCamera->SetTriggerMode( &triggerMode );
	if (mErr != FlyCapture2::PGRERROR_OK)
	{
		sMsg = "triggerMode error:";
		return false;
	}

	//6.图像设置
	FlyCapture2::Format7ImageSettings fmt7ImageSettings;
	fmt7ImageSettings.mode = FlyCapture2::MODE_0;
	fmt7ImageSettings.offsetX=(MaxWidth - s_ImageWidth) / 2;
	fmt7ImageSettings.offsetY =(MaxHeight - s_ImageHeight) / 2;
	fmt7ImageSettings.width =s_ImageWidth;;
	fmt7ImageSettings.height = s_ImageHeight;
	//原始数据格式
	fmt7ImageSettings.pixelFormat = FlyCapture2::PIXEL_FORMAT_RAW8;
	//黑白模式
	//fmt7ImageSettings.pixelFormat = FlyCapture2::PIXEL_FORMAT_MONO8;

	bool valid;
	FlyCapture2::Format7PacketInfo fmt7PacketInfo;

	mErr = mpCamera->ValidateFormat7Settings(
		&fmt7ImageSettings,
		&valid,
		&fmt7PacketInfo );

	if (mErr != FlyCapture2::PGRERROR_OK)
	{
		sMsg = "ValidateFormat7Settings error:";
		return false;
	}

	// 7.Set the settings to the camera
	mErr = mpCamera->SetFormat7Configuration(
		&fmt7ImageSettings,
		fmt7PacketInfo.recommendedBytesPerPacket );
	if (mErr != FlyCapture2::PGRERROR_OK)
	{
		sMsg = "SetFormat7Configuration error:";
		return false;
	}

	//设置白平衡值
	if(mbLan)
	{
	FlyCapture2::Property prop;
	prop.type = FlyCapture2::WHITE_BALANCE;
	mErr = mpCamera->GetProperty( &prop );

	prop.onOff = true;
	prop.autoManualMode = false;
	prop.valueA = 290;
	prop.valueB = 1023;
	mErr = mpCamera->SetProperty( &prop );
	if (mErr != FlyCapture2::PGRERROR_OK)
	{
		sMsg = "GetProperty error:";
		return false;
	}
	}
	/*
	//8.Declare a Property struct.
	FlyCapture2::Property prop;

	mpCamera->GetProperty( &prop );
	prop.onOff = true;

	//Set the absolute value of gamma to 1.5
	prop.absValue = 1.2;


	prop.type =  FlyCapture2::GAIN;
	mErr = mpCamera->GetProperty(&prop);
	//Ensure auto-adjust mode is off.
	prop.autoManualMode = false;
	//Ensure the property is set up to use absolute value control.
	prop.absControl = true;
	//Set the absolute value of gain to 10.5 dB.
//	prop.absValue = 10;
	//Set the property.
	mErr = mpCamera->SetProperty( &prop );
	if (mErr != FlyCapture2::PGRERROR_OK)
	{
		sMsg = "SetProperty";
		return false;
	}
	*/



	//8.设置获取图像时间
	FlyCapture2::FC2Config fc2Config;
	mpCamera->GetConfiguration(&fc2Config);
	fc2Config.grabMode = FlyCapture2::DROP_FRAMES;
	fc2Config.grabTimeout=2000;
	mErr =mpCamera->SetConfiguration(&fc2Config);
	if (mErr!= FlyCapture2::PGRERROR_OK)
	{
		sMsg = "SetConfiguration error:";
		return false;
	}


	/*
	//获取相机信息
	CameraInfo camInfo;
	error = cam.GetCameraInfo(&camInfo);
	if (error != PGRERROR_OK)
	{
		//PrintError( error );
		//return FALSE;
		return "GetCameraInfo";
	}
	*/

	return true;
}

bool FlyCapture::StartCapture(char *sMsg)
{
	//开始录像
	mErr = mpCamera->StartCapture();
	if (mErr != FlyCapture2::PGRERROR_OK)
	{
		sMsg = "StartCapture error:";
		return false;
	}

	/*
	//start测试
	unsigned int gpio3Add = 0;
	unsigned int gpio4Add = 0;
	unsigned int cColor = 0;

	QTime t;
	ofstream ofs("flycapture");
	while(true)
	{
		t.restart();

		mpCamera->ReadRegister(OPGPIO::GPIO3_ADD, &gpio3Add);
		mpCamera->ReadRegister(OPGPIO::GPIO4_ADD, &gpio4Add);
		int iL = gpio3Add & 0x0001;
		int iH = gpio4Add & 0x0001;
		cColor = (iH<<1) + iL;		

		int ttime = t.elapsed();
		stringstream ss;
		ss<<cColor<<":"<<ttime<<endl;
		ofs<<ss.str();
	}
	//end
	*/

	return true;
}


FlyCapture2::Camera* FlyCapture::GetCamera() const
{
	return mpCamera;
}

float FlyCapture::GetShutter()
{
	FlyCapture2::Property prop;
	prop.type = FlyCapture2::SHUTTER;
	mpCamera->GetProperty(&prop);
	return prop.absValue;
}

string FlyCapture::SetAutoShutter(bool b)
{
	FlyCapture2::Property prop;
	prop.type = FlyCapture2::SHUTTER;

	mErr= mpCamera->GetProperty(&prop);
	if (mErr!=FlyCapture2::PGRERROR_OK)
	{
		return mErr.GetDescription();
	}
	prop.autoManualMode = b;
	prop.absControl=!b;
	mErr= mpCamera->SetProperty( &prop );
	if (mErr!=FlyCapture2::PGRERROR_OK)
	{
		return mErr.GetDescription();
	}
	
	return "ok";
}

string FlyCapture::SetAutoGain(bool b)
{
	FlyCapture2::Property prop;
	prop.type = FlyCapture2::GAIN;
	mErr=mpCamera->GetProperty(&prop);
	if (mErr!=FlyCapture2::PGRERROR_OK)
	{
		return mErr.GetDescription();
	}
	prop.autoManualMode = b;
	prop.absControl=!b;
	mErr= mpCamera->SetProperty( &prop );
	if (mErr!=FlyCapture2::PGRERROR_OK)
	{
		return mErr.GetDescription();
	}

	return "ok";
}

float FlyCapture::GetGain()
{
	FlyCapture2::Property prop;
	prop.type = FlyCapture2::GAIN;
	mpCamera->GetProperty(&prop);
	return prop.absValue;
}
