#ifndef  IMAGEFACTORY_INC
#define  IMAGEFACTORY_INC

class QWidget;
class ImageFactory
{
public:
	ImageFactory(void);
	~ImageFactory(void);

public:
	//��ȡͼ����
	static QWidget* CreateImage();
	//����ͼ��·��
	static void ImageLabelLoad(QString path);
};

#endif   /* ----- #ifndef IMAGEFACTORY_INC  ----- */
