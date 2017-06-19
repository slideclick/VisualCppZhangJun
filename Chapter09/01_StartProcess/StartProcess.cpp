// StartProcess.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <tchar.h>
#include <stdio.h>
#include <commdlg.h>
#include "resource.h"

//启动，并等待进程结束
void StartProcess(HWND hDlg)
{
	//获取输入的文件名
	TCHAR szCmd[MAX_PATH * 2] = {0};
	UINT nLen = GetDlgItemText(
		hDlg, IDC_EDT_APP, szCmd, MAX_PATH);
	//获取参数
	TCHAR szParam[MAX_PATH];
	GetDlgItemText(hDlg, IDC_EDT_PARAM, szParam, MAX_PATH);
	//初始化用来接收进程信息的结构
	PROCESS_INFORMATION pi = {0};
	STARTUPINFO si = {0};
	si.cb = sizeof(si);
	//创建进程
	BOOL bCreate = CreateProcess(
		*szCmd ? szCmd : NULL, 
		szParam, NULL, NULL, FALSE, 
		0, NULL, NULL, &si, &pi);
	if(!bCreate)
	{
		//如果创建失败，显示提示信息后退出
		DWORD dwErr = GetLastError();
		TCHAR szErr[MAX_PATH] = {0};
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 
			NULL, dwErr, LANG_USER_DEFAULT, 
			szErr, MAX_PATH, NULL);
		TCHAR szMsg[MAX_PATH] = {0};
		_stprintf(szMsg, _T("启动进程时发生以下错误：%s"), szErr);
		MessageBox(NULL, szMsg, NULL, 
			MB_OK | MB_ICONERROR | MB_TASKMODAL);
		return;
	}

	//等待进程结束，20秒后超时返回
	DWORD dwWait = WaitForSingleObject(pi.hProcess, 20 * 1000);
	switch(dwWait) 
	{
	case WAIT_OBJECT_0:
		break;
	case WAIT_TIMEOUT:
	default:
		MessageBox(NULL, 
			_T("等待进程超时或错误，将强制结束进程。"), 
			NULL, 
			MB_OK | MB_ICONWARNING | MB_TASKMODAL);
		//强制结束进程
		TerminateProcess(pi.hProcess, 0);
		break;
	}
}

//浏览，并得到文件名
void BrowseFile(HWND hDlg)
{
	TCHAR szFile[MAX_PATH] = {0};
	//初始化打开文件描述结构
	OPENFILENAME op = {0};
	op.lStructSize = sizeof(op);
	op.hwndOwner = hDlg;
	op.lpstrFilter = _T("*.exe\0*.exe\0*.*\0*.*\0");
	op.lpstrFile = szFile;
	op.nMaxFile = MAX_PATH;
	op.Flags = OFN_FILEMUSTEXIST;
	//调用打开对话框选择文件
	if(GetOpenFileName(&op))
		SetDlgItemText(hDlg, IDC_EDT_APP, szFile);
}

//对话框过程函数
INT_PTR CALLBACK MainDlgProc(HWND hDlg,
							UINT uMsg,
							WPARAM wp,
							LPARAM lp)
{
	BOOL bRet = TRUE;
	//消息处理
	switch(uMsg) 
	{
	case WM_CLOSE:
		//结束对话框
		EndDialog(hDlg, 0);
		break;
	case WM_COMMAND:
		{
			switch(LOWORD(wp))
			{
			case IDOK:
				//单击了启动程序按钮
				StartProcess(hDlg);
				break;
			case IDCANCEL:
				//单击了退出按钮
				PostMessage(hDlg, WM_CLOSE, 0, 0);
				break;
			case IDC_BTN_BROWSE:
				//单击了浏览按钮
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

//应用程序入口函数
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//显示主对话框
 	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);
	return 0;
}

