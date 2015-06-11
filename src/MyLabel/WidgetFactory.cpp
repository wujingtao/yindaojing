#include "WidgetFactory.h"
#include "MyLabel.h"


WidgetFactory::WidgetFactory(void)
{
}


WidgetFactory::~WidgetFactory(void)
{
}


QLabel* WidgetFactory::GetLabel(QWidget* parent, QString name)
{
	MyLabel *lab = new MyLabel(parent, name);
	return lab;
}

void WidgetFactory::SetCurrentWidget(int nw)
{
	MyLabel::SetCurrentWidget(nw);
}