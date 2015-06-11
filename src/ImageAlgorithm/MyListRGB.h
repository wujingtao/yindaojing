#pragma once
#include "MyList.h"
//qt
#include <qmutex.h>

class MyListRGB
{
public:
	~MyListRGB(void);

	//��ȡ����
	static MyListRGB* GetInstance();

private:
	explicit MyListRGB(void);

public:
	void AddRGB(unsigned char* r, unsigned char* g, unsigned char* b);
	bool GetRGB(unsigned char** r, unsigned char** g, unsigned char** b);
	void ReleaseRGB();

	void AddGaussianRGB(unsigned char* r, unsigned char* g, unsigned char* b);
	bool GetGaussianRGB(unsigned char** r, unsigned char** g, unsigned char** b);
	void ReleaseGaussianRGB();

	void AddImage(unsigned char* r);
	bool GetImage(unsigned char** r);
	void ReleaseImage();

	//��ӵ�ֱ���㷨����
	void AddClaheRGB(unsigned char* r,unsigned char* g,unsigned char* b);
	//��ȡֱ��ͼ������RGB
	bool GetClaheRGB(unsigned char** r, unsigned char** g, unsigned char** b);
	//�ͷ�
	void ReleaseClaheRGB();
private:
	MyList<unsigned char*> mLstR;
	MyList<unsigned char*> mLstG;
	MyList<unsigned char*> mLstB;

	MyList<unsigned char*> mLstGaussianR;
	MyList<unsigned char*> mLstGaussianG;
	MyList<unsigned char*> mLstGaussianB;

	MyList<unsigned char*> mLstClaheR;
	MyList<unsigned char*> mLstClaheG;
	MyList<unsigned char*> mLstClaheB;

	MyList<unsigned char*> mLstImage;

	static QMutex mMutex;

	static MyListRGB *s_myListRGB;
};

