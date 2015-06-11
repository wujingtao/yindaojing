#include "RWBmp.h"
#include <assert.h>
#include <stdio.h>



unsigned char* RWBmp::bmpBuffer = NULL;

RWBmp::RWBmp(void)
{
}


RWBmp::~RWBmp(void)
{
	if(bmpBuffer != NULL)
	{
		delete[] bmpBuffer;	
		bmpBuffer = NULL;
	}
}

unsigned char* RWBmp::Get8BitBmp(unsigned char* cBuffer, int iWidth, int iHeight, int &iSize)
{
	int iBitCount = 8;   
    int iColorSize= 1024;  
    int iLineByte = (iWidth * iBitCount / 8 + 3) / 4 * 4;

    BITMAPFILEHEADER fileHead;  
    fileHead.bfType = 0x4D42;   
    fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + iColorSize + iLineByte*iHeight;  
    fileHead.bfReserved1 = 0;  
    fileHead.bfReserved2 = 0;  
    fileHead.bfOffBits = 54 + iColorSize;  

    BITMAPINFOHEADER infoHead;  
    infoHead.biSize = 40;    //���ṹ�ĳ���  
    infoHead.biWidth = iWidth; //λͼ�Ŀ�ȣ�������Ϊ��λ  
    infoHead.biHeight  = iHeight; //λͼ�Ŀ�ȣ�������Ϊ��λ  
    infoHead.biPlanes  = 1; //Ŀ���豸�ļ��𣬱�����1  
    infoHead.biBitCount = 8; //ÿ��������ռ��λ��(bit)����ֵ����Ϊ1���ڰ�ͼ�񣩣�4��16ɫͼ����8��256ɫ����24�����ɫͼ��  
    infoHead.biCompression = BI_RGB; //λͼѹ�����ͣ���Ч��ֵΪBI_RGB��δ��ѹ������BI_RLE4��BI_RLE8��BI_BITFIEDS����ΪWindows���峣������  
    infoHead.biSizeImage  = iLineByte*iHeight;  //ʵ�ʵ�λͼ����ռ�õ��ֽ���  
    infoHead.biXPelsPerMeter = 0; //ָ��Ŀ�����ݵ�ˮƽ�ֱ��ʣ���λ������/�ס�  
    infoHead.biYPelsPerMeter = 0; //ָ��Ŀ�����ݵĴ�ֱ�ֱ��ʣ���λ������/�ס�  
    infoHead.biClrUsed = 0; //λͼʵ���õ�����ɫ���������ֵΪ�㣬���õ�����ɫ��Ϊ2��biBitCount����  
    infoHead.biClrImportant  = 0; //λͼ��ʾ��������Ҫ����ɫ���������ֵΪ�㣬����Ϊ���е���ɫ������Ҫ�ġ�  

    RGBQUAD *pColorTable = new RGBQUAD[256];  
    for (int i=0; i<256; i++)  
    {  
        pColorTable[i].rgbRed = i;  
        pColorTable[i].rgbGreen = i;  
        pColorTable[i].rgbBlue = i;  
        pColorTable[i].rgbReserved = 0;  
    }  

	iSize = fileHead.bfSize;

	static int s_iSize = 0;
	unsigned int curSize = iWidth * iHeight;
	if(s_iSize != curSize)
	{
		s_iSize = curSize;
		if(bmpBuffer != NULL)
		{
			delete[] bmpBuffer;	
			bmpBuffer = NULL;
		}
		bmpBuffer = new unsigned char[iSize];
	}
	int iFileHeadSize = sizeof(BITMAPFILEHEADER);
	memcpy(bmpBuffer, (char*)&fileHead, iFileHeadSize);
	int iInfoHead = sizeof(BITMAPINFOHEADER);
	memcpy(bmpBuffer+iFileHeadSize, (char*)&infoHead, iInfoHead);
	int iRgbGuad = sizeof(RGBQUAD);
	memcpy(bmpBuffer+iFileHeadSize+iInfoHead, (char*)pColorTable, iRgbGuad);
	memcpy(bmpBuffer+iFileHeadSize+iInfoHead+iRgbGuad, cBuffer, iLineByte*iHeight);
	

    delete pColorTable;  

	return bmpBuffer;
}

unsigned char* RWBmp::Get24BitBmp(unsigned char* cBuffer, int iWidth, int iHeight, int &iSize)
{
	int iBitCount = 24;
	int iColorSize = 0;
	//������4�ı���
	int iLineByte = (iWidth * iBitCount /8 + 3) /4 * 4;

	//ͼ���ļ�ͷ
    BITMAPFILEHEADER fileHead;  
    fileHead.bfType = 0x4D42;   
    fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + iColorSize + iLineByte*iHeight;  
    fileHead.bfReserved1 = 0;  
    fileHead.bfReserved2 = 0;  
    fileHead.bfOffBits = 54 + iColorSize;  

	//ͼ��ṹͼ
    BITMAPINFOHEADER infoHead;  
    infoHead.biSize = 40;    //���ṹ�ĳ���  
    infoHead.biWidth = iWidth; //λͼ�Ŀ�ȣ�������Ϊ��λ  
    infoHead.biHeight  = -iHeight; //λͼ�Ŀ�ȣ�������Ϊ��λ  
    infoHead.biPlanes  = 1; //Ŀ���豸�ļ��𣬱�����1  
    infoHead.biBitCount = iBitCount; //ÿ��������ռ��λ��(bit)����ֵ����Ϊ1���ڰ�ͼ�񣩣�4��16ɫͼ����8��256ɫ����24�����ɫͼ��  
    infoHead.biCompression = BI_RGB; //λͼѹ�����ͣ���Ч��ֵΪBI_RGB��δ��ѹ������BI_RLE4��BI_RLE8��BI_BITFIEDS����ΪWindows���峣������  
    infoHead.biSizeImage  = iLineByte*iHeight;  //ʵ�ʵ�λͼ����ռ�õ��ֽ���  
    infoHead.biXPelsPerMeter = 0; //ָ��Ŀ�����ݵ�ˮƽ�ֱ��ʣ���λ������/�ס�  
    infoHead.biYPelsPerMeter = 0; //ָ��Ŀ�����ݵĴ�ֱ�ֱ��ʣ���λ������/�ס�  
    infoHead.biClrUsed = 0; //λͼʵ���õ�����ɫ���������ֵΪ�㣬���õ�����ɫ��Ϊ2��biBitCount����  
    infoHead.biClrImportant  = 0; //λͼ��ʾ��������Ҫ����ɫ���������ֵΪ�㣬����Ϊ���е���ɫ������Ҫ�ġ�  

	iSize = fileHead.bfSize;

	static int s_iSize = 0;
	unsigned int curSize = iWidth * iHeight;
	if(s_iSize != curSize)
	{
		s_iSize = curSize;
		if(bmpBuffer != NULL)
		{
			delete[] bmpBuffer;	
			bmpBuffer = NULL;
		}
		bmpBuffer = new unsigned char[iSize];
	}
	int iFileHeadSize = sizeof(BITMAPFILEHEADER);
	memcpy(bmpBuffer, (char*)&fileHead, iFileHeadSize);
	int iInfoHead = sizeof(BITMAPINFOHEADER);
	memcpy(bmpBuffer+iFileHeadSize, (char*)&infoHead, iInfoHead);
	memcpy(bmpBuffer+iFileHeadSize+iInfoHead, cBuffer, iLineByte*iHeight);
	
	return bmpBuffer;
}

bool RWBmp::Write8BitBmp(unsigned char *cBuffer, int iWidth, int iHeight, const char *cName)   
{  
    //�Բ�������Ч�Խ��м��  
    assert((cBuffer != NULL) && (iWidth > 0) && (iHeight > 0) && (cName != NULL));  
  
    //ÿ��������ռ��λ��(bit)  
    int biBitCount = 8;   
  
    //��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ����ɫ��Ϊ1024�ֽ�  
    int colorTablesize = 1024;  
  
    //���洢ͼ������ÿ���ֽ���Ϊ4�ı���  
    int lineByte = (iWidth * biBitCount / 8 + 3) / 4 * 4;  
  
    //�Զ�����д�ķ�ʽ���ļ�  
    FILE *fp = fopen(cName, "wb");  
    if(fp == NULL)  
    {  
        return false;  
    }  
  
    //����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ  
    BITMAPFILEHEADER fileHead;  
    fileHead.bfType = 0x4D42;   //bmp����  
  
    //bfSize��ͼ���ļ�4����ɲ���֮��  
    fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte*iHeight;  
    fileHead.bfReserved1 = 0;  
    fileHead.bfReserved2 = 0;  
  
    //bfOffBits��ͼ���ļ�ǰ3����������ռ�֮��  
    fileHead.bfOffBits = 54 + colorTablesize;  
  
    //д�ļ�ͷ���ļ�  
    fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);  
  
    //����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ  
    BITMAPINFOHEADER head;  
    head.biSize = 40;    //���ṹ�ĳ���  
    head.biWidth = iWidth; //λͼ�Ŀ�ȣ�������Ϊ��λ  
    head.biHeight  = -iHeight; //λͼ�Ŀ�ȣ�������Ϊ��λ  
    head.biPlanes  = 1; //Ŀ���豸�ļ��𣬱�����1  
    head.biBitCount = 8; //ÿ��������ռ��λ��(bit)����ֵ����Ϊ1���ڰ�ͼ�񣩣�4��16ɫͼ����8��256ɫ����24�����ɫͼ��  
    head.biCompression = BI_RGB; //λͼѹ�����ͣ���Ч��ֵΪBI_RGB��δ��ѹ������BI_RLE4��BI_RLE8��BI_BITFIEDS����ΪWindows���峣������  
    head.biSizeImage  = lineByte*iHeight;  //ʵ�ʵ�λͼ����ռ�õ��ֽ���  
    head.biXPelsPerMeter = 0; //ָ��Ŀ�����ݵ�ˮƽ�ֱ��ʣ���λ������/�ס�  
    head.biYPelsPerMeter = 0; //ָ��Ŀ�����ݵĴ�ֱ�ֱ��ʣ���λ������/�ס�  
    head.biClrUsed = 0; //λͼʵ���õ�����ɫ���������ֵΪ�㣬���õ�����ɫ��Ϊ2��biBitCount����  
    head.biClrImportant  = 0; //λͼ��ʾ��������Ҫ����ɫ���������ֵΪ�㣬����Ϊ���е���ɫ������Ҫ�ġ�  
  
    //дλͼ��Ϣͷ���ڴ�  
    fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp);  
  
    //������ɫ������Ҫ�Ŀռ䣬д��ɫ����ļ�  
    RGBQUAD *pColorTable = new RGBQUAD[256];  
    for (int i=0; i<256; i++)  
    {  
        pColorTable[i].rgbRed = i;  
        pColorTable[i].rgbGreen = i;  
        pColorTable[i].rgbBlue = i;  
        pColorTable[i].rgbReserved = 0;  
    }  
    fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);  
    delete pColorTable;  
  
    //д��ʽͼ������д���ļ�  
    fwrite(cBuffer, iHeight*lineByte, 1, fp);  
  
    //�ر��ļ�  
    fclose(fp);   
  
    return true;  
}

bool RWBmp::Write24BitBmp(unsigned char *cBuffer, int iWidth, int iHeight, const char *cName)
{
	assert((cBuffer != NULL) && (iWidth > 0) && (iHeight > 0) && (cName != NULL));  
	
	//�Զ�����д�ķ�ʽ���ļ�  
    FILE *fp = fopen(cName, "wb");  
    if(fp == NULL)  
    {  
		fclose(fp);
        return false;  
    }  
	//ofstream ofs(cName, ofstream::trunc | ofstream::binary);
	//if(!ofs)
	//{
	//	return false;	
	//}

    int iBitCount = 24;   
    int iColorSize= 0;  
    int iLineByte = (iWidth * iBitCount / 8 + 3) / 4 * 4;  

    BITMAPFILEHEADER fileHead;  
    fileHead.bfType = 0x4D42;   
    //bfSize��ͼ���ļ�4����ɲ���֮��  
    fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + iColorSize + iLineByte*iHeight;  
    fileHead.bfReserved1 = 0;  
    fileHead.bfReserved2 = 0;  
    //bfOffBits��ͼ���ļ�ǰ3����������ռ�֮��  
    fileHead.bfOffBits = 54 + iColorSize;  

	//ofs.write((char*)&fileHead, sizeof(BITMAPFILEHEADER));
	//ofs.flush();
	//д�ļ�ͷ���ļ�  
    fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);  

    BITMAPINFOHEADER infoHead;  
    infoHead.biSize = 40;    //���ṹ�ĳ���  
    infoHead.biWidth = iWidth; //λͼ�Ŀ�ȣ�������Ϊ��λ  
    infoHead.biHeight  = -iHeight; //λͼ�Ŀ�ȣ�������Ϊ��λ  
    infoHead.biPlanes  = 1; //Ŀ���豸�ļ��𣬱�����1  
    infoHead.biBitCount = iBitCount; //ÿ��������ռ��λ��(bit)����ֵ����Ϊ1���ڰ�ͼ�񣩣�4��16ɫͼ����8��256ɫ����24�����ɫͼ��  
    infoHead.biCompression = BI_RGB; //λͼѹ�����ͣ���Ч��ֵΪBI_RGB��δ��ѹ������BI_RLE4��BI_RLE8��BI_BITFIEDS����ΪWindows���峣������  
    infoHead.biSizeImage  = iLineByte*iHeight;  //ʵ�ʵ�λͼ����ռ�õ��ֽ���  
    infoHead.biXPelsPerMeter = 0; //ָ��Ŀ�����ݵ�ˮƽ�ֱ��ʣ���λ������/�ס�  
    infoHead.biYPelsPerMeter = 0; //ָ��Ŀ�����ݵĴ�ֱ�ֱ��ʣ���λ������/�ס�  
    infoHead.biClrUsed = 0; //λͼʵ���õ�����ɫ���������ֵΪ�㣬���õ�����ɫ��Ϊ2��biBitCount����  
    infoHead.biClrImportant  = 0; //λͼ��ʾ��������Ҫ����ɫ���������ֵΪ�㣬����Ϊ���е���ɫ������Ҫ�ġ�  

	//дλͼ��Ϣͷ���ڴ�  
    fwrite(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);  

	//ofs.write((char*)&infoHead, sizeof(BITMAPINFOHEADER));
	//ofs.flush();


	//ofs.write((char*)cBuffer, iLineByte*iHeight);
	//ofs.flush();
	//ofs.close();

	//д��ʽͼ������д���ļ�  
    fwrite(cBuffer, iHeight*iLineByte, 1, fp);  
  
    //�ر��ļ�  
    fclose(fp);   

	return true;
}