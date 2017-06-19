// MyPing.h: interface for the CMyPing class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPING_H__62EDAA06_16DD_4FA5_A154_785BE326907E__INCLUDED_)
#define AFX_MYPING_H__62EDAA06_16DD_4FA5_A154_785BE326907E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

//ICMPͷ
typedef struct tagICMP_HEADER
{
	//��Ϣ����
	unsigned char  icmp_type;
	//��Ϣ����
	unsigned char  icmp_code;
	//�����
	unsigned short icmp_checksum;
	//����Ωһ��ʶ�������ID��
	unsigned short icmp_id;
	//���к�
	unsigned short icmp_sequence;
	//ʱ���
	unsigned long  imcp_timestamp;
} ICMP_HDR , *PICMP_HDR;
//IP����ͷ
typedef struct tagIP_HEADER
{
	unsigned char iphdr[20]; 
} IP_HDR , *PIP_HDR;

class CMyPing  
{
public:
	CMyPing();
	virtual ~CMyPing();
	//��ʼ������
	BOOL StartPing(HWND hHost, LPCTSTR lpDestHost, 
		UINT nMsgID, DWORD dwInterval, DWORD dwTimeout);
	//�ͷŶ��󴴽�����Դ
	void  Release();
protected:
	//����У���
	static WORD GetCheckSum(char *pBuf, int nLen);
	//���������Ϣ
	static void DebugPrint(LPCTSTR lpMsg, ...);
	//Ping�̺߳���
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
