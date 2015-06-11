#include "ReportFactory.h"
#include "ReportWidget.h"


ReportWidget* ReportFactory::s_mReport = NULL;
ReportFactory::ReportFactory(void)
{
}


ReportFactory::~ReportFactory(void)
{
}


QWidget* ReportFactory::CreateReport()
{
		//防止野指针
		//TODO:可用智能指针
	int i = ReportWidget::GetOBJ();
	if(s_mReport == NULL || i== 0)
	{
		s_mReport = new ReportWidget();	
	}
	return s_mReport;
}

void ReportFactory::ReportLabelLoad(QString pathName)
{
	if(s_mReport!=NULL)
	{
		s_mReport->SetLabelLoad(pathName);
	}
}