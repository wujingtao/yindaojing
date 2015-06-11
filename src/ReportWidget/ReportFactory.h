#ifndef  REPORTFACTORY_INC
#define  REPORTFACTORY_INC

#include "reportwidget_global.h"

class QWidget;
class ReportWidget;
class REPORTWIDGET_EXPORT ReportFactory
{
public:
	explicit ReportFactory(void);
	~ReportFactory(void);

public:
	//创建报表
	static QWidget* CreateReport();

		//报表窗体函数调用
	//static void ReportLabelOn(QString path, int index);
	//static void ReportLabelOff(int index);
	static void ReportLabelLoad(QString pathName);

private:
	static ReportWidget *s_mReport;
};

#endif   /* ----- #ifndef REPORTFACTORY_INC  ----- */
