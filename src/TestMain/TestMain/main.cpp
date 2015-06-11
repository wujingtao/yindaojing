#include "testmain.h"
#include <QtWidgets/QApplication>
#include "ImageFactory.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QWidget *w = ImageFactory::CreateImage();
	w->show();
	return a.exec();
}
