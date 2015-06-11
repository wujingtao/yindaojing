#pragma once
#include "imagewidget_global.h"
#include "ImageWidget.h"

class IMAGEWIDGET_EXPORT ImageFactory
{
public:
	ImageFactory(void);
	~ImageFactory(void);

	//����ͼ���嵥��
	static QWidget* CreateImage();
	//����ͼ��
	static void ImageLabelLoad(QString path);

private:
	static ImageWidget* s_mImage;
};

