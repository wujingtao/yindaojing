/*
 * =====================================================================================
 *
 *       Filename:  FlyCapture.h
 *        Created:  2014/7/8 9:49:42
 *       Compiler:  vs2010 
 *         Author:  
 *
 *    Description:  初始化相机类
 *
 * =====================================================================================
 */

#ifndef FLYCAPTURE_H
#define FLYCAPTURE_H

//FlyCapture
#include "Error.h"

#include <string>
using std::string;

namespace FlyCapture2
{
	class Camera;
}

class CaptureWindow;
class FlyCapture
{
public:
	FlyCapture(int wImage, int hImage, int wMax, int hMax, bool bLan = false);
	virtual ~FlyCapture();

public:

	/* 
	 *功能: 初始化相机参数
	 *参数: err out 返回错误信息 
	 *返回: 初始化成功为true，否则false 
	 */
	bool Init(string &err);

	/* 
	 *功能: 相机开始录像
	 *参数: null
	 *返回: 开始录像成功为true，否则false 
	 */
	bool StartCapture(char* err = "");

	/* 
	 *功能: 获取相机对象
	 *参数: null
	 *返回: 返回Camera类型
	 */
	FlyCapture2::Camera* GetCamera() const;

	//获取SHUTTER
	float GetShutter();
	//设置自动曝光，返回ok
	string SetAutoShutter(bool b);
	//设置自动增益，返回ok
	string SetAutoGain(bool b);
	//获取gain
	float GetGain();

public:
	//最大为1280
	//const static int ImageWidth = 1280;
	//const static int ImageWidth = 688;
	//最大为1024
	//const static int ImageHeight= 964;
	static int GetImageWidth()
	{
		return s_ImageWidth;	
	}

	static int GetImageHeight()
	{
		return s_ImageHeight;	
	}

	static int GetImageMaxWidget()
	{
		return s_ImageMaxWidth;	
	}

	static int GetImageMaxHeight()
	{
		return s_ImageMaxHeight;	
	}

private:
	FlyCapture2::Camera* mpCamera;
	FlyCapture2::Error mErr;
	static int s_ImageWidth;
	static int s_ImageHeight;
	static int s_ImageMaxWidth;
	static int s_ImageMaxHeight;
	//是否网口相机
	bool mbLan;

};

#endif // FLYCAPTURE_H
