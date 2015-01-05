#include "mainwindow.h"
#include <QApplication>
#include <QTime>
#include <qmetatype.h>
#include "cfactory.h"
int main(int argc, char *argv[])
{
	CFactory::InitFactory();

	QTime t;
	t = QTime::currentTime();
	qsrand(t.msec() + t.second() * 1000);
	QApplication a(argc, argv);
	MainWindow *w = new MainWindow;

	w->show();
	return a.exec();
}
