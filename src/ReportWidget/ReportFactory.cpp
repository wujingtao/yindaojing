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
		//��ֹҰָ��
		//TODO:��������ָ��
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