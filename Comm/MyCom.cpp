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
//打开串口，成功返回0，失败返回错误码
ComErr CMyCom::OpenCom(LPCTSTR lpName, UINT nBufferSize, UINT nNotifyMsgID, HWND hHost)
{
	m_hCom = CreateFile(lpName, GENERIC_READ | GENERIC_WRITE, 0, NULL , OPEN_EXISTING, /*FILE_FLAG_OVERLAPPED*/0, NULL);
	if (m_hCom == INVALID_HANDLE_VALUE)
	{
		//打开失败，返回错误代码
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
		//打开成功
		m_hHostWnd = hHost;
		m_nNotifyMsgID = nNotifyMsgID;
		//创建一个缓冲区
		m_pBuffer = new byte[nBufferSize];
		memset(m_pBuffer, 0, nBufferSize);
		m_nBufferSize = nBufferSize;
		//初始化串口
		DCB wdcb = {0};
		GetCommState(m_hCom, &wdcb);
		wdcb.BaudRate = 9600;	//波特率：9600
		wdcb.ByteSize = 8;		//数据位8
		//设置串口参数
		SetCommState(m_hCom, &wdcb);
		//设置串口超时参数
		COMMTIMEOUTS to =// 串口超时控制参数
		{
			50,		// 读字符间隔超时时间
			1,		// 读操作时每字符的时间
			50,		// 基本的(额外的)读超时时间
			1,		// 写操作时每字符的时间
			100		// 基本的(额外的)写超时时间
		}; 
		SetCommTimeouts(m_hCom, &to);
		//设置串口缓冲队列
		SetupComm(m_hCom, 1024, 1024);
		//清空并结束串口当前动作
		PurgeComm(m_hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
		//开始读取线程
		m_bRunning = TRUE;
		UINT nID;
		HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadEntry, this, 0, &nID);
		CloseHandle(hThread);
	}
	return Succeed;
}
//关闭串口，结束线程
void CMyCom::CloseCom()
{
	m_bRunning = FALSE;
	Sleep(100);
	//关闭串口句柄
	CloseHandle(m_hCom);
	m_hCom = NULL;
	//释放缓冲区
	delete []m_pBuffer;
	m_pBuffer = NULL;
}
//向串口写入数据
BOOL CMyCom::WriteData(const byte *pBuffer, DWORD dwLen)
{
	if(!m_bRunning)
		return FALSE;
	//写入数据到串口
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
//读串口线程
UINT WINAPI CMyCom::ThreadEntry(LPVOID lpParam)
{
	//保存参数
	CMyCom *pCom = (CMyCom *)lpParam;
	HWND hWnd = pCom->m_hHostWnd;
	UINT nMsgID = pCom->m_nNotifyMsgID;
	//循环读取
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
		//读取到数据，发消息给程序通知
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