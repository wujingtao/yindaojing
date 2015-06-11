#ifndef  CAMERAFACTORY_INC
#define  CAMERAFACTORY_INC

class QWidget;
class CameraWidget;
class CameraFactory
{
public:
	CameraFactory(void);
	~CameraFactory(void);

	//��ȡ�������
	static QWidget* CreateCamera();
	//���ô���labelֵ
	static void SetLBScreen(QString text);
};

#endif   /* ----- #ifndef CAMERAFACTORY_INC  ----- */
