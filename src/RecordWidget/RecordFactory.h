#pragma once
#include "recordwidget_global.h"
#include <qstring.h>
class QWidget;
class RECORDWIDGET_EXPORT RecordFactory
{
public:
	RecordFactory(void);
	~RecordFactory(void);

	static QWidget* CreateRecord(QString from = "");

private:
	static QWidget* s_mRecord;
};

