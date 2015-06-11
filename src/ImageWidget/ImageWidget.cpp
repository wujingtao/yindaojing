#include "ImageWidget.h"
#include <qscrollbar.h>
#include <qpainter.h>

int ImageWidget::s_OBJ = 0;
ImageWidget::ImageWidget()
{
	s_OBJ++;
	mPath = "";
	mFactor=1.0;
	miCycle = 0;
	ui.setupUi(this);	

	mLbImage = new MyLabelImage;
    mLbImage->setBackgroundRole(QPalette::Base);
    mLbImage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    mLbImage->setScaledContents(true);
	ui.saArea->setWidget(mLbImage);

		mLbImage->setPixmap(tr("image.jpg"));
	mLbImage->adjustSize();

	connect(ui.pbBack, SIGNAL(clicked()), this, SLOT(backSlot()));
	//·Å´ó
	connect(ui.pbIn, SIGNAL(clicked()), this, SLOT(inSlot()));
	//ËõÐ¡
	connect(ui.pbOut, SIGNAL(clicked()), this, SLOT(outSlot()));
	//Ô­Ê¼³ß´ç
	connect(ui.pbNormal, SIGNAL(clicked()), this, SLOT(normalSlot()));
	//ÏÔÊ¾³ß´ç
	connect(ui.pbWindow, SIGNAL(clicked()), this, SLOT(windowSlot()));
	//×ó·­
	connect(ui.pbLeft, SIGNAL(clicked()), this, SLOT(leftSlot()));
	//ÓÒ·­
	connect(ui.pbRight, SIGNAL(clicked()), this, SLOT(rightSlot()));
	connect(ui.pbSave, SIGNAL(clicked()), this, SLOT(saveSlot()));
	
}

ImageWidget::~ImageWidget()
{
	s_OBJ--;
}

int ImageWidget::GetOBJ()
{
	return s_OBJ;
}

void ImageWidget::backSlot()
{
	emit backSignal();
}


void ImageWidget::inSlot()
{
	scaleImage(1.25);
}

void ImageWidget::outSlot()
{
	scaleImage(0.8);
}

void ImageWidget::normalSlot()
{
	ui.saArea->setWidgetResizable(false);
	mLbImage->adjustSize();
	mFactor = 1.0;

	updateButton(true);
}

void ImageWidget::windowSlot()
{
	ui.saArea->setWidgetResizable(true);
	updateButton(false);
}

void ImageWidget::updateButton(bool s)
{
	ui.pbIn->setEnabled(s);	
	ui.pbOut->setEnabled(s);
}

void ImageWidget::leftSlot()
{
	miCycle -= 90;
	miCycle = miCycle==-360 ? 0 : miCycle;
	turnImage(miCycle);
}

void ImageWidget::rightSlot()
{
	miCycle += 90;
	miCycle = miCycle==360 ? 0 : miCycle;
	turnImage(miCycle);
}

void ImageWidget::turnImage(int val)
{
	QImage img(tr("image.jpg"));
	QMatrix matrix;
	matrix.rotate(val);
	img = img.transformed(matrix);
	mLbImage->setPixmap(QPixmap::fromImage(img));
}

void ImageWidget::saveSlot()
{
	mLbImage->pixmap()->save(tr("d:/test.jpg"));
}

void ImageWidget::scaleImage(double factor)
{
	mFactor *= factor;	
	mLbImage->resize(mLbImage->pixmap()->size() * mFactor);	

	//adjustScrollBar(ui.saArea->horizontalScrollBar(), factor);
	//adjustScrollBar(ui.saArea->verticalScrollBar(), factor);
	
	ui.pbIn->setEnabled(mFactor < 3.0);
	ui.pbOut->setEnabled(mFactor > 0.3);
}

void ImageWidget::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}


void ImageWidget::SetLabelLoad(QString path)
{
	mLbImage->setPixmap(path);
	mLbImage->adjustSize();
}

void ImageWidget::mouseMoveEvent(QMouseEvent *qevent)
{
	ui.lbPos->setText(QString("X: %1 Y: %2").arg(qevent->globalPos().x()).arg(qevent->globalPos().y()));
}
