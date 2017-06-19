#include "StdAfx.h"
#include ".\mycom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMyCom::CMyCom(void): m_hHostWnd(NULL), m_pBuffer(NULL), m_bRunning(0), m_hCom(NULL), m_nNotifyMsgID(0), m_nBufferSize(0)
{
}

CMyCom::~CMyCom(void)
{
}
//�򿪴��ڣ��ɹ�����0��ʧ�ܷ��ش�����
ComErr CMyCom::OpenCom(LPCTSTR lpName, UINT nBufferSize, UINT nNotifyMsgID, HWND hHost)
{
	m_hCom = CreateFile(lpName, GENERIC_READ | GENERIC_WRITE, 0, NULL , OPEN_EXISTING, /*FILE_FLAG_OVERLAPPED*/0, NULL);
	if (m_hCom == INVALID_HANDLE_VALUE)
	{
		//��ʧ�ܣ����ش������
		DWORD dwErr = GetLastError();
		switch(dwErr)
		{
		case ERROR_FILE_NOT_FOUND:
			return Err_NotExists;
		case ERROR_ACCESS_DENIED:
			return Err_OpenFailed;
		default:
			return Err_Unknow;
		}
	}
	else
	{
		//�򿪳ɹ�
		m_hHostWnd = hHost;
		m_nNotifyMsgID = nNotifyMsgID;
		//����һ��������
		m_pBuffer = new byte[nBufferSize];
		memset(m_pBuffer, 0, nBufferSize);
		m_nBufferSize = nBufferSize;
		//��ʼ������
		DCB wdcb = {0};
		GetCommState(m_hCom, &wdcb);
		wdcb.BaudRate = 9600;	//�����ʣ�9600
		wdcb.ByteSize = 8;		//����λ8
		//���ô��ڲ���
		SetCommState(m_hCom, &wdcb);
		//���ô��ڳ�ʱ����
		COMMTIMEOUTS to =// ���ڳ�ʱ���Ʋ���
		{
			50,		// ���ַ������ʱʱ��
			1,		// ������ʱÿ�ַ���ʱ��
			50,		// ������(�����)����ʱʱ��
			1,		// д����ʱÿ�ַ���ʱ��
			100		// ������(�����)д��ʱʱ��
		}; 
		SetCommTimeouts(m_hCom, &to);
		//���ô��ڻ������
		SetupComm(m_hCom, 1024, 1024);
		//��ղ��������ڵ�ǰ����
		PurgeComm(m_hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
		//��ʼ��ȡ�߳�
		m_bRunning = TRUE;
		UINT nID;
		HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadEntry, this, 0, &nID);
		CloseHandle(hThread);
	}
	return Succeed;
}
//�رմ��ڣ������߳�
void CMyCom::CloseCom()
{
	m_bRunning = FALSE;
	Sleep(100);
	//�رմ��ھ��
	CloseHandle(m_hCom);
	m_hCom = NULL;
	//�ͷŻ�����
	delete []m_pBuffer;
	m_pBuffer = NULL;
}
//�򴮿�д������
BOOL CMyCom::WriteData(const byte *pBuffer, DWORD dwLen)
{
	if(!m_bRunning)
		return FALSE;
	//д�����ݵ�����
	DWORD dwWritten;
	while(dwLen > 0)
	{
		dwWritten = 0;
		if(!WriteFile(m_hCom, pBuffer, dwLen, &dwWritten, NULL))
			return FALSE;
		dwLen -= dwWritten;
		pBuffer += dwWritten;
	}

	return TRUE;
}
//�������߳�
UINT WINAPI CMyCom::ThreadEntry(LPVOID lpParam)
{
	//�������
	CMyCom *pCom = (CMyCom *)lpParam;
	HWND hWnd = pCom->m_hHostWnd;
	UINT nMsgID = pCom->m_nNotifyMsgID;
	//ѭ����ȡ
	DWORD dwRead ;
	DWORD dwErr;
	while(pCom->m_bRunning)
	{
		dwRead = 0;
		memset(pCom->m_pBuffer, 0, pCom->m_nBufferSize);
		if(!ReadFile(pCom->m_hCom, pCom->m_pBuffer, pCom->m_nBufferSize, &dwRead, NULL))
		{
			dwErr = GetLastError();
		}
		//��ȡ�����ݣ�����Ϣ������֪ͨ
		if(dwRead > 0)
		{
			SendMessage(hWnd, nMsgID, (WPARAM)pCom->m_pBuffer, dwRead);
		}
		else
		{
			Sleep(5);
		}
	}
	return 0;
}