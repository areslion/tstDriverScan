#ifndef DRIVERSCAN_H
#define DRIVERSCAN_H

#include <QtWidgets/QMainWindow>
#include <windows.h>  
#include <stdio.h>  
#include <conio.h> 

#include "ui_driverscan.h"

class DriverScan : public QMainWindow
{
	Q_OBJECT

public:
	DriverScan(QWidget *parent = 0);
	~DriverScan();

private:
	Ui::DriverScanClass ui;
	QString	m_msg;

	void sltScan();

	void init();
	void scan();
	void scanx();

	void tstWchar();
	QString tmFileToQstr(FILETIME t_ftm);
};

#endif // DRIVERSCAN_H
