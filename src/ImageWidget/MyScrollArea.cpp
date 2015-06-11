#include "MyScrollArea.h"

MyScrollArea::MyScrollArea(QWidget *parent):QScrollArea(parent)
{
	//¹Ø±Õ¹ö¶¯Ìõ
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  
	mHbar = horizontalScrollBar();
	mVbar = verticalScrollBar();
}


MyScrollArea::~MyScrollArea(void)
{
}

void MyScrollArea::mousePressEvent(QMouseEvent *qevent)
{
	mCurPos=qevent->pos();
}


void MyScrollArea::mouseMoveEvent(QMouseEvent *qevent)
{
	QPoint pos = mCurPos - qevent->pos();
	mCurPos = qevent->pos();

	int x = mHbar->value() + pos.x(); 
	int y = mVbar->value() + pos.y();
	mHbar->setValue(x);
	mVbar->setValue(y);
}
