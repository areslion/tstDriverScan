// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

/*
vs里面使用C标准函数运行时出错
eg：scanf(), 错误报告推荐使用scanf_s()这类安全函数;
解决办法：
1. 在预编译头文件stdafx.h里（注意：一定要在没有include任何头文件之前）定义下面的宏：
#define _CRT_SECURE_NO_DEPRECATE
2. 或声明 
#param warning(disable:4996)
*/

#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <list>
#include <string>
#include <iostream>

#include"stdio.h" 
#include"windows.h" 
#include"setupapi.h"   

#pragma comment(lib, "Setupapi.lib")
#define BUFF_SIZE 1024

struct SDevicDesc
{
#if 1
	char DeviceDescription[BUFF_SIZE];
	char DeviceHardwareInfo[BUFF_SIZE];
#endif
};

enum EhwCls
{
	EhwCls_null = 0x00,
	EhwCls_uninstall = 0x01,
	EhwCls_installed = 0x02,
	EhwCls_all = EhwCls_uninstall | EhwCls_installed,
	EhwCls_Max
};

class getDeviceDescripton
{
public:
	getDeviceDescripton();
	~getDeviceDescripton(); 
	DWORD getDeviceCount();
	//获取未知设备信息
	std::list<SDevicDesc> getUnknownDeviceInfo();
	//获取可用设备信息
	std::list<SDevicDesc> getUsableDeviceInfo();
	//枚举所有设备信息
	std::list<SDevicDesc> getAllDeviceInfo();
	//根据t_cls的值选择性的枚举设备信息
	std::list<SDevicDesc> CheckDeviceInfo(EhwCls t_cls = EhwCls_all);
	
//	int xxxxxxx;

private:
	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA DevInfoData;
	DWORD EnumPos;
	WCHAR Buffer[BUFF_SIZE];

};

// TODO: reference additional headers your program requires here
