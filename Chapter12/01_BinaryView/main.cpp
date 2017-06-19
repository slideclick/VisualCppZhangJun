#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "resource.h"

//֧���ļ��ĳߴ�����
#define SIZE_LIMIT (1024*1024)

//ȫ�ֱ�������
HINSTANCE	g_hInst;
HWND		g_hDlg;
TCHAR		g_szFile[MAX_PATH];

//��������
BOOL WINAPI MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wp, LPARAM lp);
BOOL OnCommand(UINT nID);
void OnBtnOpen();
void OnBtnSave();
void ErrorBox(LPCTSTR lpMsg, DWORD dwErr);
void AppendText(HWND hEdit, LPCTSTR lpText);
inline BOOL IsHex(TCHAR ch);

//Ӧ�ó������
int WINAPI WinMain(
		HINSTANCE hInstance, 
		HINSTANCE hPrevInstance, 
		LPSTR lpCmdLine, 
		int nShowCmd)
{
	//��ʼ��ȫ�ֱ���
	g_hInst		= hInstance;
	g_hDlg		= NULL;
	*g_szFile	= _T('\0');
	//��ʾ�Ի���
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);
	return 0;
}
//�Ի������
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
//��ť�¼�����
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
//���ļ�
void OnBtnOpen()
{
	//��ʼ�����ļ������ṹ
	OPENFILENAME of = {0};
	of.lStructSize = sizeof(of);
	of.hwndOwner = g_hDlg;
	of.lpstrFilter = _T("*.*\0*.*\0");
	of.lpstrFile = g_szFile;
	of.nMaxFile = MAX_PATH;
	of.Flags = OFN_FILEMUSTEXIST;
	//���ô򿪶Ի���ѡ���ļ�
	if(!GetOpenFileName(&of))
		return;
	
	//���ļ�׼����ȡ����
	HANDLE hFile = CreateFile(
		g_szFile, 
		GENERIC_READ,		//ֻ��Ҫ��ȡȨ��
		FILE_SHARE_READ,	//�����ⲿ�����ȡ�ļ�
		NULL, 
		OPEN_EXISTING,		//ֻ���Ѵ��ڵ��ļ�
		0, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		ErrorBox(_T("��ȡ�ļ�ʱ��������"), GetLastError());
		return;
	}
	//����ı�������
	SetDlgItemText(g_hDlg, IDC_EDT_BIN, NULL);
	SetDlgItemText(g_hDlg, IDC_EDT_CHAR, NULL);
	//��ȡ�ļ���С
	DWORD dwHi = 0;
	DWORD dwLo = GetFileSize(hFile, &dwHi);
	if(dwHi > 0 || dwLo > SIZE_LIMIT)
	{
		CloseHandle(hFile);
		ErrorBox(_T("��ѡ�ļ�̫��"), 0);
		return;
	}
	DWORD dwFileSize = dwLo;
	//����������
	byte *pBuffer = new byte[dwLo];
	//��ȡ�ļ���������
	DWORD dwRead = 0;
	byte *p = pBuffer;
	while(dwLo > 0 && ReadFile(hFile, p, dwLo, &dwRead, NULL))
	{
		if(dwRead == 0)
			break;
		p += dwRead;
		dwLo -= dwRead;
	}
	//��ȡ�ı�����
	HWND hBin = GetDlgItem(g_hDlg, IDC_EDT_BIN);
	HWND hChar = GetDlgItem(g_hDlg, IDC_EDT_CHAR);
	//�����ı�����������ַ���Ϊ������
	SendMessage(hBin, EM_LIMITTEXT, 0, 0);
	SendMessage(hChar, EM_LIMITTEXT, 0, 0);
	//��ֹ�ı����ػ棬����ٶ�
	SendMessage(hBin, WM_SETREDRAW, 0, 0);
	SendMessage(hChar, WM_SETREDRAW, 0, 0);
	//ѭ����ʽ��������
	TCHAR szTemp[4096 + 10];
	LPTSTR lpTemp = szTemp;
	TCHAR szChar[4096];
	ZeroMemory(szChar, sizeof(szChar));
	int nChar = 0;
	for(UINT i=0; i<dwFileSize; i++)
	{
		//ֻ��ʾ�ɼ�ascii�ַ�
		if(pBuffer[i] <= 20 || pBuffer[i] > 127)
			szChar[nChar] = _T('.');
		else
			szChar[nChar] = pBuffer[i];
		nChar ++;
		//��ʽ�������ֽ�
		_stprintf(lpTemp, _T("%.2X "), pBuffer[i]);
		lpTemp += 3;
		if(lpTemp - szTemp >= 4096)
		{
			//������ʱ�ı����ı���
			AppendText(hBin, szTemp);
			lpTemp = szTemp;
			*szTemp = _T('\0');

			AppendText(hChar, szChar);
			ZeroMemory(szChar, sizeof(szChar));		
			nChar = 0;
		}
		//ÿ16���ַ�����
		if((i+1) % 16 == 0)
		{
			_tcscat(szChar, _T("\r\n"));
			nChar += 2;
			_tcscat(lpTemp, _T("\r\n"));
			lpTemp += 2;
		}
		
	}
	//�ͷŻ�����
	delete []pBuffer;
	//��������ı����ı���
	AppendText(hBin, szTemp);
	AppendText(hChar, szChar);
	//�����ı����ػ棬������ʾ����
	SendMessage(hBin, WM_SETREDRAW, 1, 0);
	SendMessage(hChar, WM_SETREDRAW, 1, 0);
	//�ر��ļ�
	CloseHandle(hFile);
}
//�����ļ�
void OnBtnSave()
{
	//�õ��������ı�����
	HWND hEdit = GetDlgItem(g_hDlg, IDC_EDT_BIN);
	//��ȡ�ı�����
	int nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
	if(nLen == 0)
		return;
	//�õ�Ҫ������ļ�
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
	//�����ļ�������ļ����ڣ��򸲸�
	HANDLE hFile = CreateFile(
		g_szFile, 
		GENERIC_WRITE,	//��Ҫд��Ȩ��
		0, NULL, 
		CREATE_ALWAYS,	//ǿ�ƴ����ļ�
		0, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		ErrorBox(_T("�����ļ�ʱ��������"), GetLastError());
		return;
	}
	//���ı����浽����
	TCHAR *pBuf = new TCHAR[nLen + 1];
	int nGet = SendMessage(hEdit, WM_GETTEXT, nLen, (LPARAM)pBuf);
	if(nGet != nLen - 1)
		DebugBreak();
	pBuf[nGet] = _T('\0');
	//ѭ�����������ı���ʽ��Ϊ�������ֽ�
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
		//���ֽ�д���ļ�
		if(!WriteFile(hFile, &nTemp, sizeof(byte), &dwWrite, NULL))
		{
			break;
		}
		while((!IsHex(*pTemp)) && pTemp - pBuf < nLen )
			pTemp ++;
	}
	//�ͷŻ�����
	delete []pBuf;
	//�ر��ļ�
	CloseHandle(hFile);
}
//��ʽ�����󣬲���������Ի���
void ErrorBox(LPCTSTR lpMsg, DWORD dwErr)
{
	if(dwErr > 0)
	{
		TCHAR szErr[1024] = {0};
		_tcscpy(szErr, lpMsg);
		int nLen = _tcslen(szErr);
		LPTSTR lpBuf = szErr + nLen;
		//����������ʽ��Ϊ����
		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM, 
			NULL, dwErr, LANG_SYSTEM_DEFAULT, 
			lpBuf, sizeof(szErr)/sizeof(*szErr) - nLen, 
			NULL);
		MessageBox(g_hDlg, szErr, _T("����"), MB_OK | MB_ICONWARNING);
	}
	else
	{
		MessageBox(g_hDlg, lpMsg, _T("����"), MB_OK | MB_ICONWARNING);
	}
}
//���ı���׷���ַ�
void AppendText(HWND hEdit, LPCTSTR lpText)
{
	int nTotleLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
	SendMessage(hEdit, EM_SETSEL, nTotleLen, nTotleLen + 1);
	SendMessage(hEdit, EM_REPLACESEL, FALSE, (LPARAM)lpText);
}
//�ж�һ���ַ��Ƿ�Ϊ16�����ַ�
inline BOOL IsHex(TCHAR ch)
{
	return (ch >= _T('0') && ch <= _T('9')) 
		|| (ch >= _T('A') && ch <= _T('F')) ;
}