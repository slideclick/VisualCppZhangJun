#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <tchar.h>
#include "resource.h"

//全局变量申明
HINSTANCE	g_hInst;
HWND		g_hDlg;
HWND		g_hEdit;
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
	g_hInst		= hInstance;
	g_hDlg		= NULL;
	g_hEdit		= NULL;
	
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
		g_hEdit = GetDlgItem(hDlg, IDC_EDT_RESULT);
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
//获取合适的大小单位
inline char GetRightUnit(unsigned __int64 &i64Size)
{
	if(i64Size > (ULONGLONG)1024 * 1024 * 1024 * 10)
	{
		i64Size /= (1024 * 1024 * 1024);
		return 'G';
	}
	else if(i64Size > 1024 * 1024 * 10)
	{
		i64Size /= (1024 * 1024);
		return 'M';		
	}
	else if(i64Size > 1024 * 10)
	{
		i64Size /= 1024;
		return 'K';		
	}
	else
		return 'B';
}
//获取按钮
void OnOk()
{
	TCHAR szSpace[2048] = {0};
	TCHAR szTemp[256] = {0};
	TCHAR szDisk[1024] = {0};
	LPTSTR lp = szDisk;

	char chAvail, chTotal, chFree;
	unsigned __int64 i64Avail, i64Total, i64Free;
	//获取本机驱动器列表
	GetLogicalDriveStrings(1024, szDisk);
	UINT uType;
	LPCTSTR lpType;
	//循环获取各个驱动器信息
	while(*lp != 0)
	{
		//判断驱动器类型
		_tcscat(szSpace, lp);
		_tcscat(szSpace, _T("\t"));
		uType = GetDriveType(lp);
		switch(uType)
		{
		case DRIVE_RAMDISK:
			lpType = _T("内存磁盘，\t");
			break;
		case DRIVE_CDROM:
			lpType = _T("光盘驱动器，\t");
			break;
		case DRIVE_REMOTE:
			lpType = _T("网络驱动器，\t");
			break;
		case DRIVE_FIXED:
			lpType = _T("逻辑磁盘，\t");
			break;
		case DRIVE_REMOVABLE:
			lpType = _T("可移动磁盘，\t");
			break;
		case DRIVE_NO_ROOT_DIR:
			lpType = _T("无根目录磁盘，\t");
			break;
		case DRIVE_UNKNOWN:
		default:
			lpType = _T("未知类型，\t");
			break;
		}
		_tcscat(szSpace, lpType);
		//获取磁盘空间情况
		if(!GetDiskFreeSpaceEx(lp, (PULARGE_INTEGER)&i64Avail, (PULARGE_INTEGER)&i64Total, (PULARGE_INTEGER)&i64Free))
		{
			_tcscat(szSpace, _T("无法获取大小。\r\n"));
		}
		else
		{
			chTotal = GetRightUnit(i64Total);
			chFree = GetRightUnit(i64Free);
			chAvail = GetRightUnit(i64Avail);
			_stprintf(szTemp, 
				_T("大小：%d%c，\t空闲：%d%c，\t可用：%d%c\r\n"),
				(int)i64Total, chTotal, (int)i64Free, chFree, (int)i64Avail, chAvail);
			_tcscat(szSpace, szTemp);
		}

		lp += _tcslen(lp) + 1;
	}
	//显示结果
	SetDlgItemText(g_hDlg, IDC_EDT_RESULT, szSpace);
}
//按钮事件响应
BOOL OnCommand(UINT nID)
{
	switch(nID)
	{
	case IDOK:
		OnOk();
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
