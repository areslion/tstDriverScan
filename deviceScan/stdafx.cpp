// stdafx.cpp : source file that includes just the standard includes
// di1_package.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

char *w2c(const wchar_t *pw);

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

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

/***********************************************************************
��������getDeviceDescripton����
���ܣ����������Ϣ��ʼ��
��������
���أ���
���������캯��
***********************************************************************/
getDeviceDescripton::getDeviceDescripton()
{
	hDevInfo = NULL;
	EnumPos = 0;
	hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if (hDevInfo == INVALID_HANDLE_VALUE)
		return;
	DevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
}

/***********************************************************************
��������~getDeviceDescripton����
���ܣ��ͷ�������ڴ�ռ�
���أ���
��������
��������������
***********************************************************************/
getDeviceDescripton::~getDeviceDescripton()
{

}

/***********************************************************************
��������
���ܣ�
���أ�
������
������
***********************************************************************/
DWORD getDeviceDescripton::getDeviceCount()
{
	DWORD DeviceCount;
	hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if (hDevInfo == INVALID_HANDLE_VALUE)
		return 0;
	DevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	for (DeviceCount = 0; SetupDiEnumDeviceInfo(hDevInfo, DeviceCount, &DevInfoData); DeviceCount++)
	{
		//printf("count = %d\n", DeviceCount);
	}
	return DeviceCount;
}

/***********************************************************************
��������getUnknownDeviceInfo()
���ܣ���ȡδ֪�豸��������Ϣ��Ӳ����Ϣ
���أ�std::list<DevicDesc>
��������
��������ȡδ֪�豸����Ϣ����������Ϊ DevicDesc��ʵ�ֽ�WCHAR����ת��string����
***********************************************************************/
std::list<SDevicDesc> getDeviceDescripton::getUnknownDeviceInfo()
{
	std::list<SDevicDesc> devlist;
	SDevicDesc devtemp;
//	char strMsg[1024] = "";
	//ö�����е��豸��Ϣ
	for (EnumPos = 0; SetupDiEnumDeviceInfo(hDevInfo, EnumPos, &DevInfoData); EnumPos++)
	{
		if (!SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_CLASS, NULL, (PBYTE)Buffer, BUFF_SIZE, NULL))
		{
			memset(devtemp.DeviceDescription, NULL, sizeof(devtemp.DeviceDescription));
			memset(devtemp.DeviceHardwareInfo, NULL, sizeof(devtemp.DeviceHardwareInfo));
			if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)Buffer, BUFF_SIZE, NULL))
			{
				//��ȡ�豸��������Ϣ
				char *px = w2c(Buffer);
				strcpy(devtemp.DeviceDescription, px);
			}
			else
			{
				GetLastError();
			}
			if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_HARDWAREID, NULL, (PBYTE)Buffer, BUFF_SIZE, NULL))
			{
				//��ȡ�豸��Ӳ����Ϣ
				char *pm = w2c(Buffer);
				strcpy(devtemp.DeviceHardwareInfo, pm);
			}
			else
			{
				 GetLastError();
			}
			//���µ��豸��Ϣ��������
			devlist.insert(devlist.end(),devtemp);
		}
	}
	if (hDevInfo)
		SetupDiDestroyDeviceInfoList(hDevInfo);
	return devlist;
}

/***********************************************************************
��������getUsableDeviceInfo()
���ܣ���ȡ���п����豸��������Ϣ
���أ�std::list<DevicDesc>
��������
��������ȡ�����豸����Ϣ����������Ϊ DevicDesc��ʵ�ֽ�WCHAR����ת��string����
***********************************************************************/

std::list<SDevicDesc> getDeviceDescripton::getUsableDeviceInfo()
{
	std::list<SDevicDesc> devlist;
	SDevicDesc devtemp;
	for (EnumPos = 0; SetupDiEnumDeviceInfo(hDevInfo, EnumPos, &DevInfoData); EnumPos++)
	{
		if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_CLASS, NULL, (PBYTE)Buffer, BUFF_SIZE, NULL))
		{
			memset(devtemp.DeviceDescription, NULL, sizeof(devtemp.DeviceDescription));
			memset(devtemp.DeviceHardwareInfo, NULL, sizeof(devtemp.DeviceHardwareInfo));
			if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)Buffer, BUFF_SIZE, NULL))
			{
				//��ȡ�豸��������Ϣ
				char *px = w2c(Buffer);
				strcpy(devtemp.DeviceDescription, px);
			}
			else
			{
				GetLastError();
			}
			if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_HARDWAREID, NULL, (PBYTE)Buffer, BUFF_SIZE, NULL))
			{
				//��ȡ�豸��Ӳ����Ϣ
				char *pm = w2c(Buffer);
				strcpy(devtemp.DeviceHardwareInfo, pm);
			}
			else
			{
				GetLastError();
			}
			//���µ��豸��Ϣ��������
			devlist.insert(devlist.end(), devtemp);
		}
	}

	if (hDevInfo)
		SetupDiDestroyDeviceInfoList(hDevInfo);
	return devlist;
}

/***********************************************************************
��������CheckDeviceInfo()
���ܣ�ѡ���Ի�ȡ�����豸��Ϣ
���أ�std::list<DevicDesc>
��������
��������ȡ�����豸����Ϣ����������Ϊ DevicDesc��ʵ�ֽ�WCHAR����ת��string����
***********************************************************************/

std::list<SDevicDesc> getDeviceDescripton::getAllDeviceInfo()
{
	std::list<SDevicDesc> devlist;
	SDevicDesc devtemp;
	for (EnumPos = 0; SetupDiEnumDeviceInfo(hDevInfo, EnumPos, &DevInfoData); EnumPos++)
	{
		SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_CLASS, NULL, (PBYTE)Buffer, BUFF_SIZE, NULL);
		memset(devtemp.DeviceDescription, NULL, sizeof(devtemp.DeviceDescription));
		memset(devtemp.DeviceHardwareInfo, NULL, sizeof(devtemp.DeviceHardwareInfo));
		if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)Buffer, BUFF_SIZE, NULL))
		{
			//��ȡ�豸��������Ϣ
			char *px = w2c(Buffer);
			strcpy(devtemp.DeviceDescription, px);
		}
		else
		{
			 GetLastError();
		}
		if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_HARDWAREID, NULL, (PBYTE)Buffer, BUFF_SIZE, NULL))
		{
			//��ȡ�豸��Ӳ����Ϣ
			char *pm = w2c(Buffer);
			strcpy(devtemp.DeviceHardwareInfo, pm);
		}
		else
		{
			GetLastError();
		}
		//���µ��豸��Ϣ��������
		devlist.insert(devlist.end(), devtemp);
	}
	if (hDevInfo)
		SetupDiDestroyDeviceInfoList(hDevInfo);
	return devlist;
}

/***********************************************************************
��������CheckDeviceInfo()
���ܣ�ѡ���Ի�ȡ�豸��Ϣ
���أ�std::list<DevicDesc>
������EhwCls t_cls
��������ȡ�����豸����Ϣ����������Ϊ DevicDesc��ʵ�ֽ�WCHAR����ת��string����
***********************************************************************/

std::list<SDevicDesc> getDeviceDescripton::CheckDeviceInfo(EhwCls t_cls)
{
	std::list<SDevicDesc> devlist;

	if (EhwCls_null == t_cls)
	{
		exit(0);
	} 
	if (EhwCls_uninstall == t_cls)
	{
		devlist = getUnknownDeviceInfo();
	}
	if (EhwCls_installed == t_cls)
	{
		devlist = getUsableDeviceInfo();
	}
	if (EhwCls_all == t_cls)
	{
		devlist = getAllDeviceInfo();
	}
	return devlist;
}

