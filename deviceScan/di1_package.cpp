// di1_package.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	using std::cout;
	using std::endl;
	using std::cin;
	setlocale(LC_CTYPE, "");
	getDeviceDescripton p1;
//	p1.getUnknownDeviceInfo();

	DWORD count = p1.getDeviceCount();
//	p1.getUnknownDeviceInfo();
//	p1.getUsableDeviceInfo();
//	p1.getAllDeviceInfo();
//	p1.CheckDeviceInfo(EhwCls_all);
	//��ȡ�豸��Ϣ ��list�ݴ�
	std::list<SDevicDesc> devlist = p1.CheckDeviceInfo(EhwCls_all);;
	//���������  ��ӡ�豸��Ϣ
	std::list<SDevicDesc>::iterator iter = devlist.begin();
	
	for (iter = devlist.begin(); iter != devlist.end(); iter++)
	{
		printf("�豸����= ");
		printf("%s\n", iter->DeviceDescription);
		printf("Ӳ��ID= ");
		printf("%s\n", iter->DeviceHardwareInfo);
		printf("---------------------------------------------------------------------\n");
	}
	printf("count = %d \n", count);	//215
	
	getchar();
	return 0;
}

