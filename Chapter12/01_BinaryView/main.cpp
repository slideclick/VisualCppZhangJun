#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "resource.h"

//支持文件的尺寸上限
#define SIZE_LIMIT (1024*1024)

//全局变量申明
HINSTANCE	g_hInst;
HWND		g_hDlg;
TCHAR		g_szFile[MAX_PATH];

//函数申明
BOOL WINAPI MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wp, LPARAM lp);
BOOL OnCommand(UINT nID);
void OnBtnOpen();
void OnBtnSave();
void ErrorBox(LPCTSTR lpMsg, DWORD dwErr);
void AppendText(HWND hEdit, LPCTSTR lpText);
inline BOOL IsHex(TCHAR ch);

//应用程序入口
int WINAPI WinMain(
		HINSTANCE hInstance, 
		HINSTANCE hPrevInstance, 
		LPSTR lpCmdLine, 
		int nShowCmd)
{
	//初始化全局变量
	g_hInst		= hInstance;
	g_hDlg		= NULL;
	*g_szFile	= _T('\0');
	//显示对话框
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);
	return 0;
}
//对话框过程
BOOL WINAPI MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wp, LPARAM lp)
{
	BOOL bRet = TRUE;
	switch(uMsg)
	{
	case WM_INITDIALOG:
		g_hDlg = hDlg;
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	case WM_COMMAND:
		bRet = OnCommand(LOWORD(wp));
	default:
		bRet = FALSE;
	}
	return bRet;
}
//按钮事件处理
BOOL OnCommand(UINT nID)
{
	switch(nID)
	{
	case IDC_BTN_OPEN:
		OnBtnOpen();
		break;
	case IDC_BTN_SAVE:
		OnBtnSave();
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
//打开文件
void OnBtnOpen()
{
	//初始化打开文件描述结构
	OPENFILENAME of = {0};
	of.lStructSize = sizeof(of);
	of.hwndOwner = g_hDlg;
	of.lpstrFilter = _T("*.*\0*.*\0");
	of.lpstrFile = g_szFile;
	of.nMaxFile = MAX_PATH;
	of.Flags = OFN_FILEMUSTEXIST;
	//调用打开对话框选择文件
	if(!GetOpenFileName(&of))
		return;
	
	//打开文件准备读取内容
	HANDLE hFile = CreateFile(
		g_szFile, 
		GENERIC_READ,		//只需要读取权限
		FILE_SHARE_READ,	//允许外部程序读取文件
		NULL, 
		OPEN_EXISTING,		//只打开已存在的文件
		0, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		ErrorBox(_T("读取文件时发生错误："), GetLastError());
		return;
	}
	//清空文本框内容
	SetDlgItemText(g_hDlg, IDC_EDT_BIN, NULL);
	SetDlgItemText(g_hDlg, IDC_EDT_CHAR, NULL);
	//获取文件大小
	DWORD dwHi = 0;
	DWORD dwLo = GetFileSize(hFile, &dwHi);
	if(dwHi > 0 || dwLo > SIZE_LIMIT)
	{
		CloseHandle(hFile);
		ErrorBox(_T("所选文件太大！"), 0);
		return;
	}
	DWORD dwFileSize = dwLo;
	//创建缓冲区
	byte *pBuffer = new byte[dwLo];
	//读取文件到缓冲区
	DWORD dwRead = 0;
	byte *p = pBuffer;
	while(dwLo > 0 && ReadFile(hFile, p, dwLo, &dwRead, NULL))
	{
		if(dwRead == 0)
			break;
		p += dwRead;
		dwLo -= dwRead;
	}
	//获取文本框句柄
	HWND hBin = GetDlgItem(g_hDlg, IDC_EDT_BIN);
	HWND hChar = GetDlgItem(g_hDlg, IDC_EDT_CHAR);
	//设置文本框最大容纳字符数为不限制
	SendMessage(hBin, EM_LIMITTEXT, 0, 0);
	SendMessage(hChar, EM_LIMITTEXT, 0, 0);
	//禁止文本框重绘，提高速度
	SendMessage(hBin, WM_SETREDRAW, 0, 0);
	SendMessage(hChar, WM_SETREDRAW, 0, 0);
	//循环格式化缓冲区
	TCHAR szTemp[4096 + 10];
	LPTSTR lpTemp = szTemp;
	TCHAR szChar[4096];
	ZeroMemory(szChar, sizeof(szChar));
	int nChar = 0;
	for(UINT i=0; i<dwFileSize; i++)
	{
		//只显示可见ascii字符
		if(pBuffer[i] <= 20 || pBuffer[i] > 127)
			szChar[nChar] = _T('.');
		else
			szChar[nChar] = pBuffer[i];
		nChar ++;
		//格式化缓冲字节
		_stprintf(lpTemp, _T("%.2X "), pBuffer[i]);
		lpTemp += 3;
		if(lpTemp - szTemp >= 4096)
		{
			//发送临时文本到文本框
			AppendText(hBin, szTemp);
			lpTemp = szTemp;
			*szTemp = _T('\0');

			AppendText(hChar, szChar);
			ZeroMemory(szChar, sizeof(szChar));		
			nChar = 0;
		}
		//每16个字符换行
		if((i+1) % 16 == 0)
		{
			_tcscat(szChar, _T("\r\n"));
			nChar += 2;
			_tcscat(lpTemp, _T("\r\n"));
			lpTemp += 2;
		}
		
	}
	//释放缓冲区
	delete []pBuffer;
	//添加最后的文本到文本框
	AppendText(hBin, szTemp);
	AppendText(hChar, szChar);
	//允许文本框重绘，让其显示内容
	SendMessage(hBin, WM_SETREDRAW, 1, 0);
	SendMessage(hChar, WM_SETREDRAW, 1, 0);
	//关闭文件
	CloseHandle(hFile);
}
//保存文件
void OnBtnSave()
{
	//得到二进制文本框句柄
	HWND hEdit = GetDlgItem(g_hDlg, IDC_EDT_BIN);
	//获取文本长度
	int nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
	if(nLen == 0)
		return;
	//得到要保存的文件
	OPENFILENAME of = {0};
	of.lStructSize = sizeof(of);
	of.hwndOwner = g_hDlg;
	of.lpstrFilter = _T("*.*\0*.*\0");
	of.lpstrFile = g_szFile;
	of.lpstrDefExt = _T("*.txt");
	of.nMaxFile = MAX_PATH;
	of.Flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	if(!GetSaveFileName(&of))
		return;
	//创建文件，如果文件存在，则覆盖
	HANDLE hFile = CreateFile(
		g_szFile, 
		GENERIC_WRITE,	//需要写入权限
		0, NULL, 
		CREATE_ALWAYS,	//强制创建文件
		0, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		ErrorBox(_T("创建文件时发生错误："), GetLastError());
		return;
	}
	//将文本保存到缓冲
	TCHAR *pBuf = new TCHAR[nLen + 1];
	int nGet = SendMessage(hEdit, WM_GETTEXT, nLen, (LPARAM)pBuf);
	if(nGet != nLen - 1)
		DebugBreak();
	pBuf[nGet] = _T('\0');
	//循环将缓冲区文本格式化为二进制字节
	TCHAR szChar[3];
	TCHAR *pTemp = pBuf;
	szChar[2] = _T('\0');
	TCHAR *pEnd = &szChar[2];
	byte nTemp;
	int i=0;
	DWORD dwWrite;
	while(pTemp - pBuf < nLen)
	{
		szChar[0] = *pTemp;
		pTemp ++;
		szChar[1] = *pTemp;
		pTemp ++;
		if(IsHex(szChar[0]) && IsHex(szChar[1]))
			nTemp = (byte)strtol(szChar, &pEnd, 16);
		dwWrite = 0;
		//将字节写入文件
		if(!WriteFile(hFile, &nTemp, sizeof(byte), &dwWrite, NULL))
		{
			break;
		}
		while((!IsHex(*pTemp)) && pTemp - pBuf < nLen )
			pTemp ++;
	}
	//释放缓冲区
	delete []pBuf;
	//关闭文件
	CloseHandle(hFile);
}
//格式化错误，并弹出错误对话框
void ErrorBox(LPCTSTR lpMsg, DWORD dwErr)
{
	if(dwErr > 0)
	{
		TCHAR szErr[1024] = {0};
		_tcscpy(szErr, lpMsg);
		int nLen = _tcslen(szErr);
		LPTSTR lpBuf = szErr + nLen;
		//将错误代码格式化为描述
		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM, 
			NULL, dwErr, LANG_SYSTEM_DEFAULT, 
			lpBuf, sizeof(szErr)/sizeof(*szErr) - nLen, 
			NULL);
		MessageBox(g_hDlg, szErr, _T("错误"), MB_OK | MB_ICONWARNING);
	}
	else
	{
		MessageBox(g_hDlg, lpMsg, _T("错误"), MB_OK | MB_ICONWARNING);
	}
}
//向文本框追加字符
void AppendText(HWND hEdit, LPCTSTR lpText)
{
	int nTotleLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
	SendMessage(hEdit, EM_SETSEL, nTotleLen, nTotleLen + 1);
	SendMessage(hEdit, EM_REPLACESEL, FALSE, (LPARAM)lpText);
}
//判断一个字符是否为16进制字符
inline BOOL IsHex(TCHAR ch)
{
	return (ch >= _T('0') && ch <= _T('9')) 
		|| (ch >= _T('A') && ch <= _T('F')) ;
}