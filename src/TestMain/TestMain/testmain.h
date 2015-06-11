#ifndef TESTMAIN_H
#define TESTMAIN_H

#include <QtWidgets/QMainWindow>
#include "ui_testmain.h"

class TestMain : public QMainWindow
{
	Q_OBJECT

public:
	TestMain(QWidget *parent = 0);
	~TestMain();

private:
	Ui::TestMainClass ui;
};

#endif // TESTMAIN_H
