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
函数名：getDeviceDescripton（）
功能：所需基本信息初始化
参数：无
返回：无
描述：构造函数
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
函数名：~getDeviceDescripton（）
功能：释放申请的内存空间
返回：无
参数：无
描述：析构函数
***********************************************************************/
getDeviceDescripton::~getDeviceDescripton()
{

}

/***********************************************************************
函数名：
功能：
返回：
参数：
描述：
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
函数名：getUnknownDeviceInfo()
功能：获取未知设备的描述信息和硬件信息
返回：std::list<DevicDesc>
参数：无
描述：获取未知设备的信息，数据类型为 DevicDesc，实现将WCHAR类型转成string类型
***********************************************************************/
std::list<SDevicDesc> getDeviceDescripton::getUnknownDeviceInfo()
{
	std::list<SDevicDesc> devlist;
	SDevicDesc devtemp;
//	char strMsg[1024] = "";
	//枚举所有的设备信息
	for (EnumPos = 0; SetupDiEnumDeviceInfo(hDevInfo, EnumPos, &DevInfoData); EnumPos++)
	{
		if (!SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_CLASS, NULL, (PBYTE)Buffer, BUFF_SIZE, NULL))
		{
			memset(devtemp.DeviceDescription, NULL, sizeof(devtemp.DeviceDescription));
			memset(devtemp.DeviceHardwareInfo, NULL, sizeof(devtemp.DeviceHardwareInfo));
			if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)Buffer, BUFF_SIZE, NULL))
			{
				//获取设备的描述信息
				char *px = w2c(Buffer);
				strcpy(devtemp.DeviceDescription, px);
			}
			else
			{
				GetLastError();
			}
			if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_HARDWAREID, NULL, (PBYTE)Buffer, BUFF_SIZE, NULL))
			{
				//获取设备的硬件信息
				char *pm = w2c(Buffer);
				strcpy(devtemp.DeviceHardwareInfo, pm);
			}
			else
			{
				 GetLastError();
			}
			//将新的设备信息插入链表
			devlist.insert(devlist.end(),devtemp);
		}
	}
	if (hDevInfo)
		SetupDiDestroyDeviceInfoList(hDevInfo);
	return devlist;
}

/***********************************************************************
函数名：getUsableDeviceInfo()
功能：获取所有可用设备的描述信息
返回：std::list<DevicDesc>
参数：无
描述：获取可用设备的信息，数据类型为 DevicDesc，实现将WCHAR类型转成string类型
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
				//获取设备的描述信息
				char *px = w2c(Buffer);
				strcpy(devtemp.DeviceDescription, px);
			}
			else
			{
				GetLastError();
			}
			if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_HARDWAREID, NULL, (PBYTE)Buffer, BUFF_SIZE, NULL))
			{
				//获取设备的硬件信息
				char *pm = w2c(Buffer);
				strcpy(devtemp.DeviceHardwareInfo, pm);
			}
			else
			{
				GetLastError();
			}
			//将新的设备信息插入链表
			devlist.insert(devlist.end(), devtemp);
		}
	}

	if (hDevInfo)
		SetupDiDestroyDeviceInfoList(hDevInfo);
	return devlist;
}

/***********************************************************************
函数名：CheckDeviceInfo()
功能：选择性获取所有设备信息
返回：std::list<DevicDesc>
参数：无
描述：获取可用设备的信息，数据类型为 DevicDesc，实现将WCHAR类型转成string类型
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
			//获取设备的描述信息
			char *px = w2c(Buffer);
			strcpy(devtemp.DeviceDescription, px);
		}
		else
		{
			 GetLastError();
		}
		if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DevInfoData, SPDRP_HARDWAREID, NULL, (PBYTE)Buffer, BUFF_SIZE, NULL))
		{
			//获取设备的硬件信息
			char *pm = w2c(Buffer);
			strcpy(devtemp.DeviceHardwareInfo, pm);
		}
		else
		{
			GetLastError();
		}
		//将新的设备信息插入链表
		devlist.insert(devlist.end(), devtemp);
	}
	if (hDevInfo)
		SetupDiDestroyDeviceInfoList(hDevInfo);
	return devlist;
}

/***********************************************************************
函数名：CheckDeviceInfo()
功能：选择性获取设备信息
返回：std::list<DevicDesc>
参数：EhwCls t_cls
描述：获取可用设备的信息，数据类型为 DevicDesc，实现将WCHAR类型转成string类型
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

