// MyPing.h: interface for the CMyPing class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPING_H__62EDAA06_16DD_4FA5_A154_785BE326907E__INCLUDED_)
#define AFX_MYPING_H__62EDAA06_16DD_4FA5_A154_785BE326907E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

//ICMP头
typedef struct tagICMP_HEADER
{
	//消息类型
	unsigned char  icmp_type;
	//消息代码
	unsigned char  icmp_code;
	//检验和
	unsigned short icmp_checksum;
	//用来惟一标识此请求的ID号
	unsigned short icmp_id;
	//序列号
	unsigned short icmp_sequence;
	//时间戳
	unsigned long  imcp_timestamp;
} ICMP_HDR , *PICMP_HDR;
//IP报文头
typedef struct tagIP_HEADER
{
	unsigned char iphdr[20]; 
} IP_HDR , *PIP_HDR;

class CMyPing  
{
public:
	CMyPing();
	virtual ~CMyPing();
	//初始化对象
	BOOL StartPing(HWND hHost, LPCTSTR lpDestHost, 
		UINT nMsgID, DWORD dwInterval, DWORD dwTimeout);
	//释放对象创建的资源
	void  Release();
protected:
	//计算校验和
	static WORD GetCheckSum(char *pBuf, int nLen);
	//输出调试信息
	static void DebugPrint(LPCTSTR lpMsg, ...);
	//Ping线程函数
	static UINT CALLBACK WorkProc(LPVOID p);
protected:
	HWND	m_hHost;
	DWORD	m_dwDestIP;
	UINT	m_nMsgID;
	DWORD	m_dwInterval;
	DWORD	m_dwTimeout;
	SOCKET	m_socket;
	HANDLE	m_hRunEvent;
	HANDLE  m_hThread;
};

#endif // !defined(AFX_MYPING_H__62EDAA06_16DD_4FA5_A154_785BE326907E__INCLUDED_)
