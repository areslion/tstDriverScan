#include "driverscan.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DriverScan w;
	w.show();
	return a.exec();
}
