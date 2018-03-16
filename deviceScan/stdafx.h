// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

/*
vs����ʹ��C��׼��������ʱ����
eg��scanf(), ���󱨸��Ƽ�ʹ��scanf_s()���లȫ����;
����취��
1. ��Ԥ����ͷ�ļ�stdafx.h�ע�⣺һ��Ҫ��û��include�κ�ͷ�ļ�֮ǰ����������ĺ꣺
#define _CRT_SECURE_NO_DEPRECATE
2. ������ 
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
	//��ȡδ֪�豸��Ϣ
	std::list<SDevicDesc> getUnknownDeviceInfo();
	//��ȡ�����豸��Ϣ
	std::list<SDevicDesc> getUsableDeviceInfo();
	//ö�������豸��Ϣ
	std::list<SDevicDesc> getAllDeviceInfo();
	//����t_cls��ֵѡ���Ե�ö���豸��Ϣ
	std::list<SDevicDesc> CheckDeviceInfo(EhwCls t_cls = EhwCls_all);
	
//	int xxxxxxx;

private:
	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA DevInfoData;
	DWORD EnumPos;
	WCHAR Buffer[BUFF_SIZE];

};

// TODO: reference additional headers your program requires here
