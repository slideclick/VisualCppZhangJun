#define UNICODE
#define _UNICODE
#define _WIN32_WINNT   0x0400 

#include <windows.h>
#include <process.h>
#include <tchar.h>
#include <shlobj.h>
#include "resource.h"

//宏定义
#define FILE_NOTIFY_CHANGE_ALL (FILE_NOTIFY_CHANGE_FILE_NAME|\
								FILE_NOTIFY_CHANGE_DIR_NAME|\
								FILE_NOTIFY_CHANGE_ATTRIBUTES|\
								FILE_NOTIFY_CHANGE_SIZE|\
								FILE_NOTIFY_CHANGE_LAST_WRITE|\
								FILE_NOTIFY_CHANGE_LAST_ACCESS|\
								FILE_NOTIFY_CHANGE_CREATION|\
								FILE_NOTIFY_CHANGE_SECURITY)
#define FNI FILE_NOTIFY_INFORMATION
//全局变量申明
HINSTANCE	g_hInst;
HWND		g_hDlg;
HWND		g_hEdit;
TCHAR		g_szDir[MAX_PATH];
//函数申明
BOOL WINAPI MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wp, LPARAM lp);
BOOL OnCommand(UINT nID);
void WatchThread(LPVOID);
void AppendNotify(LPCTSTR lpChange, LPCTSTR lpFile);

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
	g_hEdit		= NULL;
	*g_szDir	= _T('\0');
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
		g_hEdit = GetDlgItem(hDlg, IDC_EDT_LOG);
		SendMessage(g_hEdit, EM_LIMITTEXT, 0, 0);
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
//按钮命令响应
BOOL OnCommand(UINT nID)
{
	switch(nID)
	{
	case IDC_BTN_BEGIN:
		{
			//浏览，并获得一个目录以监控
			BROWSEINFO bi = {0};
			LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
			if(pidl != NULL)
			{
				SHGetPathFromIDList(pidl, g_szDir);
				EnableWindow(GetDlgItem(g_hDlg, IDC_BTN_BEGIN), FALSE);
				//开始监控
				_beginthread(WatchThread, 0, NULL);
			}
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
//监控线程
void WatchThread(LPVOID)
{
	//打开目录以便监控
	HANDLE hDir = CreateFile(
		g_szDir, 
		FILE_LIST_DIRECTORY,		//必须的权限
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, 
		NULL, 
		OPEN_EXISTING, 
		FILE_FLAG_BACKUP_SEMANTICS, //必须的选项
		NULL);
	if(INVALID_HANDLE_VALUE != hDir)
	{
		char buf[5*(sizeof(FNI) + sizeof(WCHAR)*MAX_PATH)];
		
		DWORD dwRead;
		FNI *pNotify;
		LPCTSTR lpChange;
		WCHAR szFile[MAX_PATH];
		while(TRUE)
		{
			//同步方式获得变化通知
			if( ReadDirectoryChangesW(hDir, buf, 
				sizeof(buf), 
				TRUE,					//包括子目录
				FILE_NOTIFY_CHANGE_ALL, //监控所有变化
				&dwRead,
				NULL,
				NULL))
			{ 
				//分析变化内容
				pNotify = (FNI *)buf;
				while(TRUE) 
				{
					switch(pNotify->Action) 
					{
					case FILE_ACTION_ADDED:
						lpChange = _T("追加");
						break;
					case FILE_ACTION_REMOVED:
						lpChange = _T("删除");
						break;
					case FILE_ACTION_MODIFIED:
						lpChange = _T("修改");
						break;
					case FILE_ACTION_RENAMED_OLD_NAME:
					case FILE_ACTION_RENAMED_NEW_NAME:
						lpChange = _T("改名");
						break;
					default:
						lpChange = _T("未知");
						break;
					}
					_tcsncpy(szFile, pNotify->FileName, pNotify->FileNameLength/sizeof(WCHAR));
					szFile[pNotify->FileNameLength/sizeof(WCHAR)] = _T('\0');
					//显示变化到界面
					AppendNotify(lpChange, szFile);
					//继续下一条通知
					if(!pNotify->NextEntryOffset)
						break;
					pNotify = (FNI *)((char *)pNotify + pNotify->NextEntryOffset);
				} 
			}
			else
			{
				break;
			}
		}
	}
}
//向文本框追加内容
void AppendNotify(LPCTSTR lpChange, LPCTSTR lpFile)
{
	TCHAR szText[MAX_PATH * 2] = {0};
	SYSTEMTIME time = {0};
	GetLocalTime(&time);
	_stprintf(szText, _T("%.2d:%.2d%.2d %s %s\r\n"), 
		time.wHour, time.wMinute, time.wSecond, lpChange, lpFile);
	int nTotleLen = SendMessage(g_hEdit, WM_GETTEXTLENGTH, 0, 0);
	SendMessage(g_hEdit, EM_SETSEL, nTotleLen, nTotleLen + 1);
	SendMessage(g_hEdit, EM_REPLACESEL, FALSE, (LPARAM)szText);
}