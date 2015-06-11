#pragma once
#include "qscrollarea.h"
#include <qevent.h>
#include <qscrollbar.h>

class MyScrollArea :
	public QScrollArea
{
public:
	MyScrollArea(QWidget *parent=0);
	~MyScrollArea(void);

protected:
	void mousePressEvent(QMouseEvent *qevent);
	void mouseMoveEvent(QMouseEvent *qevent);

private:
	QScrollBar *mHbar;
	QScrollBar *mVbar;
	QPoint mCurPos;

};

