#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include "ui_imagewidget.h"

#include "MyLabelImage.h"
#include "qevent.h"

class ImageWidget : public QWidget
{
	Q_OBJECT
public:
	ImageWidget();
	~ImageWidget();

protected:
	void mouseMoveEvent(QMouseEvent *qevent);

public:
	static int GetOBJ();

	//labelͼ�����
	void SetLabelLoad(QString path);

private:
	//����ͼ��
	void scaleImage(double factor);
	//������λ��
	void adjustScrollBar(QScrollBar *scrollBar, double factor);
	//���°�ť
	void updateButton(bool s);
	//ת��ͼ��
	void turnImage(int val);

private slots:
	//����
	void backSlot();
	//ͼƬ�Ŵ�
	void inSlot();
	//ͼƬ��С
	void outSlot();
	//������С
	void normalSlot();
	//��ͼ��С
	void windowSlot();
	//��
	void leftSlot();
	//�ҷ�
	void rightSlot();
	void saveSlot();

signals:
	void backSignal();

private:
	Ui::imagewidget ui;	

	static int s_OBJ;

	MyLabelImage *mLbImage;
	QScrollArea *mSaArea;
	QImage mImage;

	//ͼƬ·��
	QString mPath;

	//���ű���
	double mFactor;
	//��ת����
	int miCycle;
};

#endif // IMAGEWIDGET_H
