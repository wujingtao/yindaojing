/*
 * =====================================================================================
 *
 *       Filename:  FlyCapture.h
 *        Created:  2014/7/8 9:49:42
 *       Compiler:  vs2010 
 *         Author:  
 *
 *    Description:  ��ʼ�������
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
	 *����: ��ʼ���������
	 *����: err out ���ش�����Ϣ 
	 *����: ��ʼ���ɹ�Ϊtrue������false 
	 */
	bool Init(string &err);

	/* 
	 *����: �����ʼ¼��
	 *����: null
	 *����: ��ʼ¼��ɹ�Ϊtrue������false 
	 */
	bool StartCapture(char* err = "");

	/* 
	 *����: ��ȡ�������
	 *����: null
	 *����: ����Camera����
	 */
	FlyCapture2::Camera* GetCamera() const;

	//��ȡSHUTTER
	float GetShutter();
	//�����Զ��ع⣬����ok
	string SetAutoShutter(bool b);
	//�����Զ����棬����ok
	string SetAutoGain(bool b);
	//��ȡgain
	float GetGain();

public:
	//���Ϊ1280
	//const static int ImageWidth = 1280;
	//const static int ImageWidth = 688;
	//���Ϊ1024
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
	//�Ƿ��������
	bool mbLan;

};

#endif // FLYCAPTURE_H
