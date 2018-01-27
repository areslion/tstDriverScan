#include "driverscan.h"
#include "QTextCodec"
#include <QDateTime>

#include <locale.h>

#include <stdio.h>
#include <windows.h>
#include <psapi.h>
#include <tchar.h>
#include <stdio.h>
#include <Setupapi.h>


#define ARRAY_SIZE 1024

char *w2c(const wchar_t *pw);
DriverScan::DriverScan(QWidget *parent)
	: QMainWindow(parent)
{
// 	QTextCodec *codec = QTextCodec::codecForName("UTF8");
// 
// 	QTextCodec::setCodecForLocale(codec);


	ui.setupUi(this);
	init();
}

DriverScan::~DriverScan()
{

}

void DriverScan::init()
{
	char strMsg[] = "\xE6\xB5\x8B\xE8\xAF\x95";

	tstWchar();

	//ok
	//QString strTst = QString::fromLocal8Bit("²âÊÔ");// (strMsg);
	//ui.txtMsg->setText(strTst);
	
	char strTst[] = "²âÊÔ";
	QByteArray bta = QByteArray(strTst);
	//bta = strTst.toLatin1();
	ui.txtMsg->setText(QString::fromLocal8Bit(bta));


	//strTst = "²âÊÔ";
	//ui.txtMsg->setText(strTst.toUtf8());
	//ui.txtMsg->setText(QString::fromLocal8Bit(strTst.toStdString().c_str()));
	//ui.txtMsg->setText(QString::fromWCharArray(strTst));
	ui.cbxItem->addItem("EnumDeviceDrivers"); 
	ui.cbxItem->addItem("SetupDiEnumDriverInfo"); 

	connect(ui.btScan, &QPushButton::clicked, this, &DriverScan::sltScan);
}

void DriverScan::sltScan()
{
	m_msg = "";
	int nindex = ui.cbxItem->currentIndex();
	switch (nindex)
	{
	case 0:
		scan();
		break;
	case 1:
		scanx();
		break;
	}

	ui.txtMsg->setText(m_msg);
}



void DriverScan::scan()
{
	LPVOID drivers[ARRAY_SIZE];
	DWORD cbNeeded;
	int cDrivers, i,nret =0;
	m_msg = "";


	char strMsg[1024] = "";
	if (EnumDeviceDrivers(drivers, sizeof(drivers), &cbNeeded) && cbNeeded < sizeof(drivers))
	{
		TCHAR szDriver[ARRAY_SIZE];
		

		cDrivers = cbNeeded / sizeof(drivers[0]);
		//_tprintf(TEXT("There are %d drivers:\n"), cDrivers);
		sprintf_s(strMsg, "There are %d drivers:\n", cDrivers);
		m_msg += QString(strMsg);
		for (i = 0; i < cDrivers; i++)
		{
			if (GetDeviceDriverBaseName(drivers[i], szDriver, sizeof(szDriver) / sizeof(szDriver[0])))
			{
				//_tprintf(TEXT("%d: %s\n"), i + 1, szDriver);
				sprintf_s(strMsg, "%d: ", i + 1);
				QString strDriv = QString::fromWCharArray(szDriver);
				m_msg += QString(strMsg) + strDriv+"\n";
			}
		}
	}
	else
	{
		//_tprintf(TEXT("EnumDeviceDrivers failed; array size needed is %d\n"), cbNeeded / sizeof(LPVOID));
		sprintf_s(strMsg, "EnumDeviceDrivers failed; array size needed is %d\n", cbNeeded / sizeof(LPVOID));
		m_msg += QString(strMsg);
		nret = 1;
	}
}

void DriverScan::scanx()
{
	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA   DeviceInfoData;
	SP_DRVINFO_DATA   DriverInfoData;

	DWORD  MemberIndex = 0;
	char strMsg[1024] = "";

	hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		printf("SetupDiGetClassDevs %d %s\r\n",GetLastError(),strerror(GetLastError()));
		return;
	}

	for (MemberIndex = 0;; MemberIndex++)
	{
		SP_DEVINFO_DATA devInfo;
		devInfo.cbSize = sizeof(SP_DEVINFO_DATA);
		if (!SetupDiEnumDeviceInfo(hDevInfo, MemberIndex, &devInfo))	break;

		// Build a list of driver info items that we will retrieve below
		if (!SetupDiBuildDriverInfoList(hDevInfo, &devInfo, SPDIT_COMPATDRIVER)) break;;

		// Get all the info items for this driver 
		// (I don't understand why there is more than one)
		for (int j = 0;; j++)
		{
			SP_DRVINFO_DATA drvInfo;
			drvInfo.cbSize = sizeof(SP_DRVINFO_DATA);
			if (!SetupDiEnumDriverInfo(hDevInfo, &devInfo, SPDIT_COMPATDRIVER, j, &drvInfo)) break;

			char *px = w2c(drvInfo.Description);
			char *py = w2c(drvInfo.MfgName);
			char *pz = w2c(drvInfo.ProviderName);
			sprintf(strMsg,"%d %d Driver %s \r\n \tversion is %08x %08x\r\n\tMfgName:%s\r\n\tProviderName:%s\r\n\tDriverDate:%s\r\n\r\n", 
				MemberIndex,j,px,
				(unsigned)(drvInfo.DriverVersion >> 32),
				(unsigned)(drvInfo.DriverVersion & 0xffffffffULL),py,pz,tmFileToQstr(drvInfo.DriverDate).toStdString().c_str());

			printf(strMsg);

			if (px) free(px);
			if (py) free(py);
			if (pz) free(pz);

			m_msg += QString::fromLocal8Bit(QByteArray(strMsg));
			ui.txtMsg->setText(m_msg);
		}
	}
		
	if(hDevInfo) SetupDiDestroyDeviceInfoList(hDevInfo);
}


char *w2c(const wchar_t *pw)
{
	if (!pw)
		return NULL;

	size_t size = wcslen(pw)*sizeof(wchar_t);
	char *pc;
	if (!(pc = (char*)malloc(size)))
	{
		printf("malloc fail");
		return NULL;
	}
	memset(pc, 0x00, size);
	wcstombs(pc, pw, size);
	return pc;

}

void DriverScan::tstWchar()
{
	setlocale(LC_ALL, "");
	char *px = NULL;

	WCHAR strMsg[] = L"A*¿í×Ö·û²âÊÔ*B\r\n";
	wprintf(L"%ls",strMsg);
	px = w2c(strMsg);
	printf("1 %s",px);
	if (px) free(px);
}

QString DriverScan::tmFileToQstr(FILETIME t_ftm)
{
	char strTmx[512] = "";
	FILETIME localft;
	FileTimeToLocalFileTime(&t_ftm, &localft);
	SYSTEMTIME st;
	FileTimeToSystemTime(&localft, &st);

	sprintf(strTmx, "%d-%d-%d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	return QString(strTmx);
}


