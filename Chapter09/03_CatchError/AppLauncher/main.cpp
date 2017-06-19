#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "resource.h"

//全局变量申明
HWND g_hDlg;
//全局函数申明
INT_PTR CALLBACK MainDlgProc(HWND hDlg,
							 UINT uMsg,
							 WPARAM wp,
							 LPARAM lp);
void StartApp();
void OutputMsg(LPCTSTR lpMsg, ...);


//----------------------
// 函数实现
//----------------------

//应用程序入口函数
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//弹出主对话框
	DialogBox(hInstance, 
		MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);
	return 0;
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
	case WM_INITDIALOG:
		g_hDlg = hDlg;
		break;
	case WM_CLOSE:
		//结束对话框
		EndDialog(hDlg, 0);
		break;
	case WM_COMMAND:
		switch(LOWORD(wp))
		{
		case IDOK:
			//按下了OK按钮，启动目标程序
			StartApp();
			break;
		case IDCANCEL:
			//按下了Cancel按钮，关闭本对话框
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

//启动目标程序，并等待其结束
void StartApp()
{
	//获取程序名称
	TCHAR szFile[MAX_PATH] = {0};
	GetDlgItemText(g_hDlg, IDC_EDT_FILE, szFile, MAX_PATH);
	if(*szFile == 0)
	{
		OutputMsg(_T("请先输入一个文件名。"));
		return;
	}
	//启动进程
	STARTUPINFO st = {0};  
	PROCESS_INFORMATION pi = {0};  
	st.cb = sizeof(st);  
	BOOL bCreate = CreateProcess(
		NULL, szFile, NULL, NULL, FALSE,  
		DEBUG_ONLY_THIS_PROCESS,  NULL, NULL, &st, &pi);  
	
	if(!bCreate)
	{
		OutputMsg(_T("启动进程时发生错误: %d。"), GetLastError());
		return ;
	}
	//成功启动了进程
	OutputMsg(_T("进程%d启动了。。。"), pi.dwProcessId);
	//释放句柄
	CloseHandle(pi.hThread);  
	CloseHandle(pi.hProcess);  
	//等待调试事件
	DEBUG_EVENT dbe;  
	while(WaitForDebugEvent(&dbe, INFINITE))  
	{  
		switch(dbe.dwDebugEventCode)
		{
		case EXIT_PROCESS_DEBUG_EVENT:
			//目标程序退出，结束循环
			OutputMsg(_T("目标程序结束了。。。"));
			return ;
			break; 
		case EXCEPTION_DEBUG_EVENT:
			//发生调试事件，如果是断点中断，继续执行程序
			if(dbe.u.Exception.ExceptionRecord.ExceptionCode 
				!= EXCEPTION_BREAKPOINT)
			{
				//目标程序发生错误
				switch(dbe.u.Exception.ExceptionRecord.ExceptionCode)
				{
				case EXCEPTION_ACCESS_VIOLATION: 
					//访问违例错误
					OutputMsg(_T("目标程序发生访问违例错误。。。"));
					break;
				case EXCEPTION_FLT_DIVIDE_BY_ZERO: 
				case EXCEPTION_INT_DIVIDE_BY_ZERO:
					//被零除错误
					OutputMsg(_T("目标程序发生被零除错误。。。"));
					break;
				default:
					//其它错误
					OutputMsg(_T("目标程序发生意外错误。。。"));
					break;		
				}
				//让系统处理异常
				ContinueDebugEvent(dbe.dwProcessId , dbe.dwThreadId , 
					DBG_EXCEPTION_NOT_HANDLED); 
				continue;
			}
			break;
		default:
			break;
		}
		//继续调试
		ContinueDebugEvent(dbe.dwProcessId , 
			dbe.dwThreadId , DBG_CONTINUE );  
	}
	return ;
}

//输出信息
void OutputMsg(LPCTSTR lpMsg, ...)
{
	TCHAR szBuf[1024] = {0};
	//获取并格式化当前时间
	SYSTEMTIME time = {0};
	GetLocalTime(&time);
	_stprintf(szBuf, _T("%.2d:%.2d:%.2d "), 
		time.wHour, time.wMinute, time.wSecond);
	//格式化输出信息中的参数
	va_list vl;
	va_start(vl, lpMsg);
	wvsprintf(szBuf + _tcslen(szBuf), lpMsg, vl);
	va_end(vl);
	//添加回车换行符
	_tcscat(szBuf, _T("\r\n"));
	//输出文字到文本框
	HWND hEdit = GetDlgItem(g_hDlg, IDC_EDT_RESULT);
	int nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
	SendMessage(hEdit, EM_SETSEL, nLen, nLen);
	SendMessage(hEdit, EM_REPLACESEL, FALSE, (LPARAM)szBuf);
	//输出文字到控制台
	OutputDebugString(szBuf);
}