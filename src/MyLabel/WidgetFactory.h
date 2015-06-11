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
	//如果是Report,Image窗体则响应label单击事件
	static void SetCurrentWidget(int nw);

	static QLabel* GetLabel(QWidget *parent, QString name = "c");
};

