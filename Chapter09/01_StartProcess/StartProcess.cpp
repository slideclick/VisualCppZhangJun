// StartProcess.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <tchar.h>
#include <stdio.h>
#include <commdlg.h>
#include "resource.h"

//���������ȴ����̽���
void StartProcess(HWND hDlg)
{
	//��ȡ������ļ���
	TCHAR szCmd[MAX_PATH * 2] = {0};
	UINT nLen = GetDlgItemText(
		hDlg, IDC_EDT_APP, szCmd, MAX_PATH);
	//��ȡ����
	TCHAR szParam[MAX_PATH];
	GetDlgItemText(hDlg, IDC_EDT_PARAM, szParam, MAX_PATH);
	//��ʼ���������ս�����Ϣ�Ľṹ
	PROCESS_INFORMATION pi = {0};
	STARTUPINFO si = {0};
	si.cb = sizeof(si);
	//��������
	BOOL bCreate = CreateProcess(
		*szCmd ? szCmd : NULL, 
		szParam, NULL, NULL, FALSE, 
		0, NULL, NULL, &si, &pi);
	if(!bCreate)
	{
		//�������ʧ�ܣ���ʾ��ʾ��Ϣ���˳�
		DWORD dwErr = GetLastError();
		TCHAR szErr[MAX_PATH] = {0};
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 
			NULL, dwErr, LANG_USER_DEFAULT, 
			szErr, MAX_PATH, NULL);
		TCHAR szMsg[MAX_PATH] = {0};
		_stprintf(szMsg, _T("��������ʱ�������´���%s"), szErr);
		MessageBox(NULL, szMsg, NULL, 
			MB_OK | MB_ICONERROR | MB_TASKMODAL);
		return;
	}

	//�ȴ����̽�����20���ʱ����
	DWORD dwWait = WaitForSingleObject(pi.hProcess, 20 * 1000);
	switch(dwWait) 
	{
	case WAIT_OBJECT_0:
		break;
	case WAIT_TIMEOUT:
	default:
		MessageBox(NULL, 
			_T("�ȴ����̳�ʱ����󣬽�ǿ�ƽ������̡�"), 
			NULL, 
			MB_OK | MB_ICONWARNING | MB_TASKMODAL);
		//ǿ�ƽ�������
		TerminateProcess(pi.hProcess, 0);
		break;
	}
}

//��������õ��ļ���
void BrowseFile(HWND hDlg)
{
	TCHAR szFile[MAX_PATH] = {0};
	//��ʼ�����ļ������ṹ
	OPENFILENAME op = {0};
	op.lStructSize = sizeof(op);
	op.hwndOwner = hDlg;
	op.lpstrFilter = _T("*.exe\0*.exe\0*.*\0*.*\0");
	op.lpstrFile = szFile;
	op.nMaxFile = MAX_PATH;
	op.Flags = OFN_FILEMUSTEXIST;
	//���ô򿪶Ի���ѡ���ļ�
	if(GetOpenFileName(&op))
		SetDlgItemText(hDlg, IDC_EDT_APP, szFile);
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
	case WM_CLOSE:
		//�����Ի���
		EndDialog(hDlg, 0);
		break;
	case WM_COMMAND:
		{
			switch(LOWORD(wp))
			{
			case IDOK:
				//��������������ť
				StartProcess(hDlg);
				break;
			case IDCANCEL:
				//�������˳���ť
				PostMessage(hDlg, WM_CLOSE, 0, 0);
				break;
			case IDC_BTN_BROWSE:
				//�����������ť
				BrowseFile(hDlg);
				break;
			default:
				bRet = FALSE;
				break;
			}
		}
		break;
	default:
		bRet = FALSE;
		break;
	}
	return bRet;
}

//Ӧ�ó�����ں���
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//��ʾ���Ի���
 	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);
	return 0;
}

