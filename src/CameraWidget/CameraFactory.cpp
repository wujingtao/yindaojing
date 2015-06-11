#include "CameraFactory.h"
#include "CameraWidget.h"

CameraWidget* CameraFactory::s_mCW = NULL;
CameraFactory::CameraFactory(void)
{
}


CameraFactory::~CameraFactory(void)
{
}

QWidget* CameraFactory::CreateCamera()
{
	int i = CameraWidget::GetOBJ();
	if(s_mCW == NULL || i==0)
	{
		s_mCW = new CameraWidget();	
	}

	return s_mCW;
}

void CameraFactory::SetLBScreen(QString text)
{
	s_mCW->SetLBScreen(text);
}