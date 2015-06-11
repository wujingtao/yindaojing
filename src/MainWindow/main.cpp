#include "mainwindow.h"
#include <QApplication>


//#include <qtextcodec.h>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
	//QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    //QTextCodec::setCodecForTr(codec);
    //QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

	MainWindow w;
	w.show();
	return a.exec();
}
