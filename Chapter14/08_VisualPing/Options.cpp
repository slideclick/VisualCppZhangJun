// Options.cpp: implementation of the COptions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Options.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COptions::COptions()
{
	//生成INI文件路径
	TCHAR szIni[MAX_PATH] = {0};
	GetModuleFileName(NULL, szIni, MAX_PATH);
	_tcscat(szIni, _T(".ini"));
	//从INI读取数据
	dwPingInterval = GetPrivateProfileInt(
		_T("APP"), _T("PingInterval"), 0, szIni);
	dwTime2	=	GetPrivateProfileInt(
		_T("APP"), _T("Time2"), 0, szIni);
	dwTime3	=	GetPrivateProfileInt(
		_T("APP"), _T("Time3"), 0, szIni);
	dwTime4	=	GetPrivateProfileInt(
		_T("APP"), _T("Time4"), 0, szIni);
	dwTimeout	=	GetPrivateProfileInt(
		_T("APP"), _T("Timeout"), 0, szIni);
	*szTargetName = _T('\0');
	GetPrivateProfileString(_T("APP"), 
		_T("TargetName"), _T(""), szTargetName, 
		sizeof(szTargetName)/sizeof(*szTargetName), szIni);
	//校验数据
	if(dwPingInterval < 1000)
		dwPingInterval = 1000;
	if(dwTime2 == 0)
		dwTime2 = 400;
	if(dwTime3 == 0)
		dwTime3 = 100;
	if(dwTime4 == 0)
		dwTime4 = 20;
	if(dwTimeout == 0)
		dwTimeout = 2000;
}
COptions::~COptions()
{
}
