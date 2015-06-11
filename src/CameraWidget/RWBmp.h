#ifndef  RWBMP_INC
#define  RWBMP_INC

#include <windows.h>  

class RWBmp
{
public:
	RWBmp(void);
	~RWBmp(void);

public:
	/* 
	 *����: ��ȡ8λbmpͼ
	 *����: cBuffer in ͼ���ֽ�
	        iWidth in ���
					iHeight in �߶�
					iSize out bmpͼ���С
	 *����: bmp��ʽ���ֽڴ�С
	 */
	static unsigned char* Get8BitBmp(unsigned char* cBuffer, int iWidth, int iHeight, int &iSize);

	/* 
	 *����: ��ȡ24λbmpͼ
	 *����: cBuffer in ͼ���ֽ�
	        iWidth in ���
					iHeight in �߶�
					iSize out bmpͼ���С
	 *����: bmp��ʽ���ֽڴ�С
	 */
	static unsigned char* Get24BitBmp(unsigned char* cBuffer, int iWidth, int iHeight, int &iSize);


	//д8λ
	static bool Write8BitBmp(unsigned char *cBuffer, int iWidth, int iHeight, const char *cName);
	//д24λ
	static bool Write24BitBmp(unsigned char *cBuffer, int iWidth, int iHeight, const char *cName);

private:
	static unsigned char* bmpBuffer;
};

#endif   /* ----- #ifndef RWBMP_INC  ----- */
