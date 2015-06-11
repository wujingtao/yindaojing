#include "RecordFactory.h"

#include "RecordWidget.h"

QWidget* RecordFactory::s_mRecord = NULL;
RecordFactory::RecordFactory(void)
{
}


RecordFactory::~RecordFactory(void)
{
}


QWidget* RecordFactory::CreateRecord(QString from)
{
	int i = RecordWidget::GetOBJ();
	if(s_mRecord== NULL || i== 0)
	{
		s_mRecord= new RecordWidget(from);	
	}
	return s_mRecord;
	
}