#pragma once
#include "camerawidget_global.h"
class QWidget;
class CameraWidget;
class CAMERAWIDGET_EXPORT CameraFactory
{
public:
	CameraFactory(void);
	~CameraFactory(void);

	static QWidget* CreateCamera();
	static void SetLBScreen(QString text);

private:
	static CameraWidget *s_mCW;
};

