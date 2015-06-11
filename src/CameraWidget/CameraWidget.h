/*
 * =====================================================================================
 *
 *       Filename:  CameraWidget.h
 *        Created:  2014-11-19 16:34:09
 *       Compiler:  vs2010 
 *         Author:  jingtao.wu
 *
 *    Description:  ��Ƶ����
 *
 * =====================================================================================
 */

#ifndef  CAMERAWIDGET_INC
#define  CAMERAWIDGET_INC

#include <QtWidgets/qwidget.h>
#include "ui_camerawidget.h"
#include <QTime>
#include <QtSerialPort/QSerialPort>


class FlyCapture;
class FusionAlg;
class ImageThread;
class ShowThread;
class ViewWidget;
class CameraWidget :
	public QWidget
{
	Q_OBJECT
public:
	CameraWidget(void);
	~CameraWidget(void);

	struct Rec{
	QString freeze, zoomi, zoomd;
	};

public:
	//������������setWidget()����Զ�ɾ������
	//������Ϊ�գ���s_OBJΪ0ʱ��ΪҰָ�룬�����·���ռ�
	static int GetOBJ();

	//����labelֵ
	void SetLBScreen(QString text)
	{
		if(text == QStringLiteral("��Ļ�ָ�"))
		{
			ui.pbBack->setEnabled(false);	
		}
		else
		{
			ui.pbBack->setEnabled(true);	
		}
		ui.lbScreen->setText(text);
	}

	//�̳�
protected:
	//ÿ����ʾ����ֵ
 void timerEvent( QTimerEvent *qevent );
 void keyPressEvent(QKeyEvent *qevent);

private:
	//����
	void begin();
	//��ʼ�����水ť 
	void initButton(bool b);
	//�򿪴���
	void openPort();

private slots:
	//����
	void backSlot();
	//��ͣ
	void pauseSlot();
	//����
	void saveSlot();
	//
	void ImageSlot(QImage image);
	//¼��
	void videoSlot();
	//ȫ��
	void fullScreenSlot();
	//�Զ�����
	void autoSaveSlot();
	//���ڽ�����Ϣ
	void readData();

signals:
	void backSignal();
	//����ͼ��label��pathNameȫ·����
	void imageSignal(QString pathName);
	//ȫ��
	void fullScreenSignal(QString text);

private:
	//����
	QSerialPort *mSerialPort;

	//�㷨��
	FusionAlg* mFusionAlg;
	//ͼ������
	ImageThread *mImgTrd;
	//ͼ����ʾ
	ShowThread *mShowTrd;
	//�����
	FlyCapture *mFC;

	Ui::camerawidget ui;
	static int s_OBJ;

	ViewWidget *mViewWidget;
	int mTimeId;
	//�Զ�¼��ʱ��
	QTime mTime;
	//�Ƿ��Զ�����
	bool mbAutoSave;
	int miAutoSecond;
	//����
	float mfSum;

	Rec mRec;
};

#endif   /* ----- #ifndef CAMERAWIDGET_INC  ----- */
