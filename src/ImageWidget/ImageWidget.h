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

	//label图像加载
	void SetLabelLoad(QString path);

private:
	//缩放图像
	void scaleImage(double factor);
	//滚动条位置
	void adjustScrollBar(QScrollBar *scrollBar, double factor);
	//更新按钮
	void updateButton(bool s);
	//转动图像
	void turnImage(int val);

private slots:
	//返回
	void backSlot();
	//图片放大
	void inSlot();
	//图片缩小
	void outSlot();
	//正常大小
	void normalSlot();
	//视图大小
	void windowSlot();
	//左翻
	void leftSlot();
	//右翻
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

	//图片路径
	QString mPath;

	//缩放比率
	double mFactor;
	//旋转周期
	int miCycle;
};

#endif // IMAGEWIDGET_H
