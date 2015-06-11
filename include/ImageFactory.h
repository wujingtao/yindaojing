#ifndef  IMAGEFACTORY_INC
#define  IMAGEFACTORY_INC

class QWidget;
class ImageFactory
{
public:
	ImageFactory(void);
	~ImageFactory(void);

public:
	//获取图像窗体
	static QWidget* CreateImage();
	//发送图像路径
	static void ImageLabelLoad(QString path);
};

#endif   /* ----- #ifndef IMAGEFACTORY_INC  ----- */
