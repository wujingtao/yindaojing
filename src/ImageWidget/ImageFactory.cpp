#include "ImageFactory.h"


ImageWidget* ImageFactory::s_mImage = NULL;

ImageFactory::ImageFactory(void)
{
}


ImageFactory::~ImageFactory(void)
{
}

QWidget* ImageFactory::CreateImage()
{
		//��ֹҰָ��
		//TODO:��������ָ��
	int i = ImageWidget::GetOBJ();
	if(s_mImage== NULL || i== 0)
	{
		s_mImage= new ImageWidget();	
	}
	return s_mImage;
}

void ImageFactory::ImageLabelLoad(QString path)
{
	if(s_mImage != NULL)
	{
		s_mImage->SetLabelLoad(path);
	}
}
