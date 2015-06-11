#include "MainWidget.h"
#include "MainWindow.h"

MainWidget::MainWidget(void)
{
	ui.setupUi(this);

	connect(ui.pbStart, SIGNAL(clicked()), this, SLOT(startSlot()));
	connect(ui.pbRecord, SIGNAL(clicked()), this, SLOT(recordSlot()));
}


MainWidget::~MainWidget(void)
{
}

void MainWidget::startSlot()
{
	emit startSignal();
}

void MainWidget::recordSlot()
{
	emit recordSignal("home");
}
