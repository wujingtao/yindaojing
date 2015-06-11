#ifndef  CAMERAFACTORY_INC
#define  CAMERAFACTORY_INC

class QWidget;
class CameraWidget;
class CameraFactory
{
public:
	CameraFactory(void);
	~CameraFactory(void);

	//获取相机窗体
	static QWidget* CreateCamera();
	//设置窗体label值
	static void SetLBScreen(QString text);
};

#endif   /* ----- #ifndef CAMERAFACTORY_INC  ----- */
