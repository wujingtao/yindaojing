/*
 * =====================================================================================
 *
 *       Filename:  FusionAlg.h
 *        Created:  2014/8/7 11:10:42
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  ͼ���㷨��,ÿ���㷨debug���30ms��CLAHES��δȷ��
 *
 * =====================================================================================
 */

#include "OpHelp.h"


#include <qmutex.h>
#include <qwaitcondition.h>

class FusionAlg
{
public:
	FusionAlg(int width, int height, int circleX, int circleY, float gainR, float gainB);
	~FusionAlg(void);

public:
	//ͨ��
	//���R,G,Bͼ�񵽶���
	void AddRGB(unsigned char* r, unsigned char* g, unsigned char* b);
	//�ж϶����Ƿ���R,G,Bͼ��,�����浽��Ա����
	bool IsRGB();
	//���ͼ�񵽶���
	void AddImage(unsigned char* img);
	//��ȡ�����е�����ͼ��
	bool GetImage(unsigned char** img);
	//�ͷŶ��е�ǰͼ��
	void ReleaseImage();

	//����ͼ���㷨�߳�
	void fusioning();
	void fusioningS();

	//1.��˹+��Ե�㷨
	//��˹�㷨:ȥ�룬�˲�
	void gaussianFilter(BGRbmp rgbBmp);  
	//��Ե�㷨:��ǿ��Ե��ʾ
	void EdgeE(BGRbmp bgrBmp);

	//�ж��Ƿ��и�˹�㷨�Ķ���
	bool IsGaussianRGB();
	void MallocGaussian();
	void MallocImage();

	//2.ֱ��ͼ+��˹�㷨
	//ֱ��ͼ:�Աȶ���ǿ
	void CLAHES(BGRbmp bgrBmp);
	//��˹�㷨
	void gaussianFilterS(BGRbmp rgbBmp);  

	//�Ƿ���ֱ��ͼ����
	bool IsClaheRGBS();
	//�����㷨����ڴ�
	void MallocClaheS();
	void MallocImageS();

private:
	//ͼ���С
	unsigned int ImageSize()
	{
		return miWidth*miHeight;	
	}

	//start ֱ�����㷨
	void MakeLut (unsigned char * pLUT, unsigned char Min, unsigned char Max, unsigned int uiNrBins);
	void ClipHistogram (unsigned long* pulHistogram, unsigned int   
                    uiNrGreylevels, unsigned long ulClipLimit);
	void MakeHistogram (unsigned char* pImage, unsigned int uiXRes,   
		                unsigned int uiSizeX, unsigned int uiSizeY,   
			            unsigned long* pulHistogram,   
				        unsigned int uiNrGreylevels, unsigned char* pLookupTable);
	void MapHistogram (unsigned long* pulHistogram, unsigned char Min, unsigned char Max,   
		               unsigned int uiNrGreylevels, unsigned long ulNrOfPixels);
	void Interpolate (unsigned char * pImage, int uiXRes, unsigned long * pulMapLU,   
		             unsigned long * pulMapRU, unsigned long * pulMapLB,  unsigned long * pulMapRB,   
			          unsigned int uiXSize, unsigned int uiYSize, unsigned char * pLUT); 
	//-end

private:
	//����ͼ��
	unsigned char* mImage;

	//����R,G,Bͼ��
	unsigned char* mR;
	unsigned char* mG;
	unsigned char* mB;

	//1��˹�ͱ�Ե
	unsigned char* mGaussianR;
	unsigned char* mGaussianG;
	unsigned char* mGaussianB;

	unsigned char* mEdgeeR;
	unsigned char* mEdgeeG;
	unsigned char* mEdgeeB;

	//2ֱ���͸�˹
	unsigned char* mClaheRS;
	unsigned char* mClaheGS;
	unsigned char* mClaheBS;

	unsigned char* mGaussianRS;
	unsigned char* mGaussianGS;
	unsigned char* mGaussianBS;

	//�����С
	unsigned int miWidth;
	unsigned int miHeight;
	int miCircleX;	
	int miCircleY;	
	float mfGainR;
	float mfGainB;

	enum {uiMAX_REG_X=16, uiMAX_REG_Y = 16, uiNR_OF_GREY = 256 };
};
