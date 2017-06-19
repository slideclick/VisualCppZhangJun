// MySocket.cpp : implementation file
//

#include "stdafx.h"
#include "MfcSock.h"
#include "MySocket.h"
#include "mfcsockdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//���Ի���ָ��
CMfcSockDlg *g_pDlg = 0;

/////////////////////////////////////////////////////////////////////////////
// CMySocket

CMySocket::CMySocket()
{	
}
CMySocket::~CMySocket()
{
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CMySocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CMySocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CMySocket member functions
//�����¼�
void CMySocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(nErrorCode != 0)
	{
		ErrMsg(nErrorCode);
	}
	else
	{
		OutputMsg(_T("�����ӵ�������\n"));
	}
	CAsyncSocket::OnConnect(nErrorCode);
}
//�����¼�
void CMySocket::OnReceive(int nErrorCode) 
{
	if(nErrorCode != 0)
	{
		ErrMsg(nErrorCode);
	}
	else
	{
		TCHAR szBuf[1024] = {0};
		int nRecv = Receive((char *)szBuf, 1024 * sizeof(TCHAR), 0);
		if(nRecv > 0)
		{
			OutputMsg(szBuf);
		}
		else
		{
			ErrMsg(this->GetLastError());
		}
	}
	CAsyncSocket::OnReceive(nErrorCode);
}
//�ر��¼�
void CMySocket::OnClose(int nErrorCode) 
{
	OutputMsg(_T("�����ѹرա�\n"));
	CAsyncSocket::OnClose(nErrorCode);
}
//���ݴ������ô�����Ϣ
void CMySocket::ErrMsg(int nCode)
{
	TCHAR szErr[1024] = {0};
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 
		NULL, nCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
		szErr, 1024, NULL);
	strcat(szErr, "\n");
	OutputMsg(szErr);
}
//�����Ի��������Ϣ
void CMySocket::OutputMsg(LPCTSTR lpMsg)
{
	if(g_pDlg == NULL)
		g_pDlg = (CMfcSockDlg *)AfxGetMainWnd();
	g_pDlg->OutputMsg(lpMsg);		
}