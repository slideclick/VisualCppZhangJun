#pragma once

#include <process.h>

//串口打开返回值枚举
enum ComErr
{
	Succeed			= 0,
	Err_NotExists	= 1,
	Err_OpenFailed	= 2,
	Err_Unknow		= 10
};

class CMyCom
{
public:
	CMyCom(void);
	~CMyCom(void);
public:
	ComErr OpenCom(LPCTSTR lpName, UINT nBufferSize, UINT nNotifyMsgID, HWND hHost); 
	void CloseCom();
	BOOL WriteData(const byte *pBuffer, DWORD dwLen);
protected:
	static UINT WINAPI ThreadEntry(LPVOID lpParam);
protected:
	HWND m_hHostWnd;
	byte *m_pBuffer;
	int m_nBufferSize;
	volatile BOOL m_bRunning;
	HANDLE m_hCom;
	UINT m_nNotifyMsgID;
};
