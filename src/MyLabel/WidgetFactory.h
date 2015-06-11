#pragma once

#include "mylabel_global.h"
#include <qstring.h>
class QWidget;
class QLabel;
class QString;
class MYLABEL_EXPORT WidgetFactory
{
public:
	WidgetFactory(void);
	~WidgetFactory(void);

	static enum {Home=0, Report, Record, Camera, Image};
	//�����Report,Image��������Ӧlabel�����¼�
	static void SetCurrentWidget(int nw);

	static QLabel* GetLabel(QWidget *parent, QString name = "c");
};

