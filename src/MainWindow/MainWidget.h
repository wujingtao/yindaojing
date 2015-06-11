#pragma once
#include <qwidget.h>
#include "ui_mainwidget.h"

class MainWindow;
class MainWidget :
	public QWidget
{
	Q_OBJECT
public:
	MainWidget(void);
	~MainWidget(void);

private slots:
	void startSlot();
	void recordSlot();

signals:
	void startSignal();
	void recordSignal(QString from);

private:
	Ui::mainwidget ui;	
};

