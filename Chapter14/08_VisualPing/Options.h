// Options.h: interface for the COptions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTIONS_H__296CAB6B_AD7C_4F99_9263_614D41DEA8F5__INCLUDED_)
#define AFX_OPTIONS_H__296CAB6B_AD7C_4F99_9263_614D41DEA8F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COptions  
{
public:
	COptions();
	virtual ~COptions();
public:		//������Ա����
	//ÿ��Ping�ļ��
	DWORD dwPingInterval;
	//����Pingֵ
	DWORD dwTime2;
	DWORD dwTime3;
	DWORD dwTime4;
	//��ʱʱ��
	DWORD dwTimeout;
	//Ŀ������IP������
	TCHAR szTargetName[512];
};

#endif // !defined(AFX_OPTIONS_H__296CAB6B_AD7C_4F99_9263_614D41DEA8F5__INCLUDED_)
