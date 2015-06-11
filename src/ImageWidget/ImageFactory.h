#pragma once
#include "imagewidget_global.h"
#include "ImageWidget.h"

class IMAGEWIDGET_EXPORT ImageFactory
{
public:
	ImageFactory(void);
	~ImageFactory(void);

	//创建图像窗体单例
	static QWidget* CreateImage();
	//加载图像
	static void ImageLabelLoad(QString path);

private:
	static ImageWidget* s_mImage;
};

