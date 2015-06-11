#ifndef  REPORTFACTORY_INC
#define  REPORTFACTORY_INC

class QWidget;
class ReportFactory
{
public:
	ReportFactory(void);
	~ReportFactory(void);

public:
	static QWidget* CreateReport();
	static void ReportLabelLoad(QString pathName);
};

#endif   /* ----- #ifndef REPORTFACTORY_INC  ----- */
