#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "resource.h"

//ȫ�ֱ�������
HWND g_hDlg;
//ȫ�ֺ�������
INT_PTR CALLBACK MainDlgProc(HWND hDlg,
							 UINT uMsg,
							 WPARAM wp,
							 LPARAM lp);
void StartApp();
void OutputMsg(LPCTSTR lpMsg, ...);


//----------------------
// ����ʵ��
//----------------------

//Ӧ�ó�����ں���
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//�������Ի���
	DialogBox(hInstance, 
		MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);
	return 0;
}

//�Ի�����̺���
INT_PTR CALLBACK MainDlgProc(HWND hDlg,
							 UINT uMsg,
							 WPARAM wp,
							 LPARAM lp)
{
	BOOL bRet = TRUE;
	//��Ϣ����
	switch(uMsg) 
	{
	case WM_INITDIALOG:
		g_hDlg = hDlg;
		break;
	case WM_CLOSE:
		//�����Ի���
		EndDialog(hDlg, 0);
		break;
	case WM_COMMAND:
		switch(LOWORD(wp))
		{
		case IDOK:
			//������OK��ť������Ŀ�����
			StartApp();
			break;
		case IDCANCEL:
			//������Cancel��ť���رձ��Ի���
			PostMessage(hDlg, WM_CLOSE, 0, 0);
			break;
		default:
			bRet = FALSE;
			break;
		}
		break;
	default:
		bRet = FALSE;
		break;
	}
	return bRet;
}

//����Ŀ����򣬲��ȴ������
void StartApp()
{
	//��ȡ��������
	TCHAR szFile[MAX_PATH] = {0};
	GetDlgItemText(g_hDlg, IDC_EDT_FILE, szFile, MAX_PATH);
	if(*szFile == 0)
	{
		OutputMsg(_T("��������һ���ļ�����"));
		return;
	}
	//��������
	STARTUPINFO st = {0};  
	PROCESS_INFORMATION pi = {0};  
	st.cb = sizeof(st);  
	BOOL bCreate = CreateProcess(
		NULL, szFile, NULL, NULL, FALSE,  
		DEBUG_ONLY_THIS_PROCESS,  NULL, NULL, &st, &pi);  
	
	if(!bCreate)
	{
		OutputMsg(_T("��������ʱ��������: %d��"), GetLastError());
		return ;
	}
	//�ɹ������˽���
	OutputMsg(_T("����%d�����ˡ�����"), pi.dwProcessId);
	//�ͷž��
	CloseHandle(pi.hThread);  
	CloseHandle(pi.hProcess);  
	//�ȴ������¼�
	DEBUG_EVENT dbe;  
	while(WaitForDebugEvent(&dbe, INFINITE))  
	{  
		switch(dbe.dwDebugEventCode)
		{
		case EXIT_PROCESS_DEBUG_EVENT:
			//Ŀ������˳�������ѭ��
			OutputMsg(_T("Ŀ���������ˡ�����"));
			return ;
			break; 
		case EXCEPTION_DEBUG_EVENT:
			//���������¼�������Ƕϵ��жϣ�����ִ�г���
			if(dbe.u.Exception.ExceptionRecord.ExceptionCode 
				!= EXCEPTION_BREAKPOINT)
			{
				//Ŀ�����������
				switch(dbe.u.Exception.ExceptionRecord.ExceptionCode)
				{
				case EXCEPTION_ACCESS_VIOLATION: 
					//����Υ������
					OutputMsg(_T("Ŀ�����������Υ�����󡣡���"));
					break;
				case EXCEPTION_FLT_DIVIDE_BY_ZERO: 
				case EXCEPTION_INT_DIVIDE_BY_ZERO:
					//���������
					OutputMsg(_T("Ŀ���������������󡣡���"));
					break;
				default:
					//��������
					OutputMsg(_T("Ŀ�������������󡣡���"));
					break;		
				}
				//��ϵͳ�����쳣
				ContinueDebugEvent(dbe.dwProcessId , dbe.dwThreadId , 
					DBG_EXCEPTION_NOT_HANDLED); 
				continue;
			}
			break;
		default:
			break;
		}
		//��������
		ContinueDebugEvent(dbe.dwProcessId , 
			dbe.dwThreadId , DBG_CONTINUE );  
	}
	return ;
}

//�����Ϣ
void OutputMsg(LPCTSTR lpMsg, ...)
{
	TCHAR szBuf[1024] = {0};
	//��ȡ����ʽ����ǰʱ��
	SYSTEMTIME time = {0};
	GetLocalTime(&time);
	_stprintf(szBuf, _T("%.2d:%.2d:%.2d "), 
		time.wHour, time.wMinute, time.wSecond);
	//��ʽ�������Ϣ�еĲ���
	va_list vl;
	va_start(vl, lpMsg);
	wvsprintf(szBuf + _tcslen(szBuf), lpMsg, vl);
	va_end(vl);
	//��ӻس����з�
	_tcscat(szBuf, _T("\r\n"));
	//������ֵ��ı���
	HWND hEdit = GetDlgItem(g_hDlg, IDC_EDT_RESULT);
	int nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
	SendMessage(hEdit, EM_SETSEL, nLen, nLen);
	SendMessage(hEdit, EM_REPLACESEL, FALSE, (LPARAM)szBuf);
	//������ֵ�����̨
	OutputDebugString(szBuf);
}