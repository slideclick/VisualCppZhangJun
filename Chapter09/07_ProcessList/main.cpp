#include <windows.h>
#include <commctrl.h>
#include <tchar.h>
#include <stdio.h>
#include <Psapi.h>
#include "resource.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "Psapi.lib")

//----------------
//全局变量声明
//-----------------
//主对话框的窗口句柄
HWND g_hDlg = NULL;
//列表控件的句柄
HWND g_hList = NULL;
//对话框改变之前的大小
SIZE g_siDlg = {0};
//对话框原始大小
SIZE g_siOrig = {0};
//列表框排序时的列索引
int g_nSortCol = -1;
//列表控件排序时记录顺序
BOOL g_bSortAsc = TRUE;

//----------------
//函数声明
//----------------
//对话框过程函数
INT_PTR CALLBACK 
DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//对话框初始化消息处理
void OnInitDialog();
//初始化列表控件
void InitList();
//对话框命令响应
void OnCommand(WPARAM wp, LPARAM lp);
//WM_SIZE消息响应
void OnSize(WPARAM wp, LPARAM lp);
//定时器消息响应
void OnTimer();
//按照指定规则移动某个控件
HDWP MoveCtrl(HDWP hDwp, UINT nID, int x, int y, 
		BOOL bLeft, BOOL bTop, BOOL bRight, BOOL bBottom);
//将屏幕坐标转换为窗体坐标
void ScreenToClientRect(LPRECT prc);
//获取进程列表
BOOL GetProcessList();
//取得进程详细信息并显示到列表控件中
void AddProcessRow(DWORD dwPID);
//打开或关闭当前进程的DEBUG权限
BOOL SetDebugPrivilege(BOOL bEnable); 
//列表控件排序回调函数
int CALLBACK ListSortFunc(
		LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

//------------------
//函数实现
//------------------
//应用程序的入口函数
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//初始化公共控件
	InitCommonControls();
	//弹出一个模式对话框，并等待对话框结束
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc);
	return 0;
}
//对话框过程函数
INT_PTR CALLBACK 
DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg) 
	{
	case WM_INITDIALOG:		//对话框初始化
		//保存窗口句柄
		g_hDlg = hwndDlg;		
		OnInitDialog();
		return 1;
	case WM_COMMAND:		//发生命令
		OnCommand(wParam, lParam);
		return 1;
	case WM_CLOSE:			//关闭对话框
		EndDialog(hwndDlg, 0);
		return 1;
	case WM_SIZE:			//对话框大小改变
		OnSize(wParam, lParam);
		return 1;
	case WM_NOTIFY:			//控件通知消息
		if(wParam == IDC_LIST)
		{
			LPNMHDR pnmh = (LPNMHDR)lParam;
			//响应列表框标题单击消息
			if(pnmh->code == LVN_COLUMNCLICK)
			{
				//取得消息数据
				LPNMLISTVIEW pnmv = (LPNMLISTVIEW)lParam;
				//如果单击的列序号和上次不同
				if(g_nSortCol != pnmv->iSubItem)
				{
					//新列第一次排序按照正序
					g_bSortAsc = TRUE;
					//记录列序号
					g_nSortCol = pnmv->iSubItem;
				}
				else
				{
					//再次单击时，按照和上次相反的顺序排序
					g_bSortAsc = (!g_bSortAsc);
				}
				//发送排序消息
				ListView_SortItems(g_hList, ListSortFunc, pnmv->iSubItem);
				return 1;
			}
		}
		break;
	case WM_GETMINMAXINFO:
		{
			//限制窗体最小尺寸
			LPMINMAXINFO lpmm = (LPMINMAXINFO)lParam;
			lpmm->ptMinTrackSize.x = g_siOrig.cx;
			lpmm->ptMinTrackSize.y = g_siOrig.cy;
		}
		return 1;
	case WM_TIMER:
		OnTimer();
		return 1;
	default:
		break;
	}
	//默认返回0
	return 0;
}
//初始化对话框
void OnInitDialog()
{
	//保存窗口原始尺寸
	RECT rc = {0};
	GetWindowRect(g_hDlg, &rc);
	g_siOrig.cx = rc.right - rc.left;
	g_siOrig.cy = rc.bottom - rc.top;
	//保存窗口客户区大小
	GetClientRect(g_hDlg, &rc);
	g_siDlg.cx = rc.right - rc.left;
	g_siDlg.cy = rc.bottom - rc.top;
	//保存列表控件句柄
	g_hList = GetDlgItem(g_hDlg, IDC_LIST);
	//初始化列表控件
	InitList();
	//得到“自动刷新”复选框控件句柄
	HWND hCtrl = GetDlgItem(g_hDlg, IDC_CHK_AUTO);
	//让控件默认选中
	SendMessage(hCtrl, BM_SETCHECK, BST_CHECKED, 0);
	//更新列表
	GetProcessList();
	//开启定时器
	SetTimer(g_hDlg, 1, 4000, NULL);
}
//初始化列表控件
void InitList()
{
	//控件的列数
	const int nCount = 4;
	//每列的宽度
	int pWidth[nCount] = {50, 100, 50, 400};
	//每列的标题
	LPTSTR pName[nCount] = 
		{_T("PID"), _T("进程名称"), _T("优先级"), _T("EXE路径")};
	//循环插入列
	LVCOLUMN col = {0};
	col.mask = LVCF_TEXT | LVCF_WIDTH;
	for(int i=0; i<nCount; i++)
	{
		col.cx = pWidth[i];
		col.pszText = pName[i];
		ListView_InsertColumn(g_hList, i, &col);
	}
	//更改列表控件风格，使其“整行”选取
	SendMessage(g_hList, LVM_SETEXTENDEDLISTVIEWSTYLE, 
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT );
}
//对话框命令响应
void OnCommand(WPARAM wp, LPARAM lp)
{
	int nID = LOWORD(wp);
	switch(nID)
	{
	//单击“刷新”按钮更新列表
	case IDOK:
		GetProcessList();
		break;
	//单击“关闭”按钮时结束对话框
	case IDCANCEL:
		SendMessage(g_hDlg, WM_CLOSE, 0, 0);
		break;
	}
}
//WM_SIZE消息响应
void OnSize(WPARAM wp, LPARAM lp)
{
	//只处理必要的消息，对于非必要消息直接返回
	switch(wp)
	{
	case SIZE_MAXHIDE:
	case SIZE_MAXSHOW:
	case SIZE_MINIMIZED:
		return;
	}
	//取得对话框的新大小
	int nWidth = LOWORD(lp);
	int nHeight = HIWORD(lp);
	//获得改变的差值
	int x, y;
	x = nWidth - g_siDlg.cx;
	y = nHeight - g_siDlg.cy;
	//开始移动控件，做相应的初始化
	HDWP hDwp = BeginDeferWindowPos(5);
	if(hDwp == NULL)
		return;
	//移动“刷新”按钮
	hDwp = MoveCtrl(hDwp, IDOK, x, y, TRUE, FALSE, TRUE, FALSE);
	//移动“关闭”按钮
	hDwp = MoveCtrl(hDwp, IDCANCEL, x, y, TRUE, FALSE, TRUE, FALSE);
	//移动“定时刷新”复选框
	hDwp = MoveCtrl(hDwp, IDC_CHK_AUTO, x, y, TRUE, TRUE, TRUE, TRUE);
	//移动文本框
	hDwp = MoveCtrl(hDwp, IDC_LIST, x, y, FALSE, FALSE, TRUE, TRUE);
	//移动文本框控件
	hDwp = MoveCtrl(hDwp, IDC_EDT_MSG, x, y, FALSE, TRUE, TRUE, TRUE);
	//结束移动，使所有控件一次性完成移动
	EndDeferWindowPos(hDwp);
	//保存当前大小
	g_siDlg.cx = nWidth;
	g_siDlg.cy = nHeight;
}
//按照指定规则移动某个控件
HDWP MoveCtrl(HDWP hDwp, UINT nID, int x, int y, 
		BOOL bLeft, BOOL bTop, BOOL bRight, BOOL bBottom)
{
	//获取控件句柄
	HWND hCtrl = GetDlgItem(g_hDlg, nID);
	//取得控件位置和大小
	RECT rc = {0};
	GetWindowRect(hCtrl, &rc);
	//将屏幕坐标转换为窗口坐标
	ScreenToClientRect(&rc);
	//根据选项改变位置和大小
	if(bLeft)
		rc.left += x;
	if(bTop)
		rc.top += y;
	if(bRight)
		rc.right += x;
	if(bBottom)
		rc.bottom += y;
	//移动控件
	return DeferWindowPos(hDwp, hCtrl, 0, rc.left, rc.top, 
		rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);
}
//将屏幕坐标转换为窗体坐标
void ScreenToClientRect(LPRECT prc)
{
	ScreenToClient(g_hDlg, (LPPOINT)prc);
	ScreenToClient(g_hDlg, ((LPPOINT)prc) + 1);	
}
//定时器消息响应
void OnTimer()
{
	HWND hCtrl = GetDlgItem(g_hDlg, IDC_CHK_AUTO);
	UINT nCheck = SendMessage(hCtrl, BM_GETCHECK, 0, 0);
	if(nCheck)
	{
		GetProcessList();
	}
}
//取得当前系统进程列表
BOOL GetProcessList()
{
	//清空列表控件
	ListView_DeleteAllItems(g_hList);
	//初始缓冲区数组大小
	int nLenArray = 32;
	//缓冲区大小的字节数
	int nLenBytes = nLenArray * sizeof(DWORD);;
	//申请缓冲区
	DWORD *pdwPID = new DWORD[nLenArray];
	DWORD dwNeeded = 0;
	//获取进程列表
	BOOL bRet = EnumProcesses(pdwPID, nLenBytes, &dwNeeded);
	//如果缓冲区不够大，增大缓冲区并重新得到进程列表
	while(bRet && dwNeeded == nLenBytes)
	{
		delete []pdwPID;
		pdwPID = NULL;
		nLenArray += 32;
		nLenBytes = nLenArray * sizeof(DWORD);
		pdwPID = new DWORD[nLenArray];
		bRet = EnumProcesses(pdwPID, nLenBytes, &dwNeeded);
	}
	//得到进程个数
	int nCount = dwNeeded / sizeof(DWORD);
	//将进程数显示到界面上
	TCHAR szCount[128];
	_stprintf(szCount, _T("进程数：%d"), nCount);
	SetDlgItemText(g_hDlg, IDC_EDT_MSG, szCount);
	//取得DEBUG权限
	SetDebugPrivilege(TRUE);
	//循环获取每个进程信息
	DWORD dwPID;
	for(int i=0; i<nCount; i++)
	{
		dwPID = pdwPID[i];
		AddProcessRow(dwPID);
	}
	//释放缓冲区
	delete []pdwPID;
	//关闭DEBUG权限
	SetDebugPrivilege(FALSE);
	//重新排序
	ListView_SortItems(g_hList, ListSortFunc, g_nSortCol < 0 ? 0 : g_nSortCol);
	return TRUE;
}
//取得进程详细信息并显示到列表控件中
void AddProcessRow(DWORD dwPID)
{
	HANDLE	hProcess;
	HMODULE hModule;
	DWORD	dwPriority;
	TCHAR	szPID[32] = {0};
	TCHAR	szPriority[32] = {0};
	TCHAR	szBaseName[MAX_PATH] = {0};
	TCHAR	szFileName[MAX_PATH] = {0};
	int		nIndex;
	
	//向列表控件插入一行
	LVITEM item = {0};
	item.mask	= LVIF_TEXT | LVIF_PARAM;
	item.iItem	= ListView_GetItemCount(g_hList);
	item.lParam	= dwPID;
	_stprintf(szPID, _T("%d"), dwPID);
	item.pszText = szPID;
	nIndex = ListView_InsertItem(g_hList, &item);
	if(nIndex < 0)
		DebugBreak();
	//打开进程	
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwPID);
	if(hProcess != NULL)
	{
		//得到进程的第一个模块
		BOOL	bRet;
		DWORD	dwNeeded;
		bRet =  EnumProcessModules(hProcess, &hModule, sizeof(HMODULE), &dwNeeded);
		if(bRet)
		{
			//取得进程优先级
			dwPriority = GetPriorityClass (hProcess); 
			_stprintf(szPriority, _T("%d"), dwPriority);
			//取得模块映像名称
			GetModuleBaseName(hProcess, hModule, szBaseName, MAX_PATH);
			//取得模块文件名
			GetModuleFileNameEx(hProcess, hModule, szFileName, MAX_PATH);
			//显示到列表控件
			ListView_SetItemText(g_hList, nIndex, 1, szBaseName);
			ListView_SetItemText(g_hList, nIndex, 2, szPriority);
			ListView_SetItemText(g_hList, nIndex, 3, szFileName);
		}
		//关闭打开的进程句柄
		CloseHandle(hProcess);
	}	
}
//打开或关闭当前进程的DEBUG权限
BOOL SetDebugPrivilege(BOOL bEnable) 
{ 
	HANDLE hToken; 
	BOOL bRet;
	//获得进程访问令牌句柄
	bRet = OpenProcessToken(GetCurrentProcess(),
		TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken);
	if(bRet)
	{ 
		TOKEN_PRIVILEGES TokenPrivileges; 
		TokenPrivileges.PrivilegeCount = 1; 
		//取得DEBUG权限的LUID
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &TokenPrivileges.Privileges[0].Luid); 
		//根据参数，打开或关闭相应权限
		TokenPrivileges.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0; 
		//调整权限
		bRet = AdjustTokenPrivileges(hToken,FALSE,&TokenPrivileges,sizeof(TOKEN_PRIVILEGES),NULL,NULL); 
		//关闭句柄
		CloseHandle(hToken); 
	} 
	return bRet; 
}
//列表控件排序回调函数
int CALLBACK ListSortFunc(
		LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	int iFlag = g_bSortAsc ? 1 : -1;
	//如果对第一列排序，由于PID是数字类型，直接比较并返回
	if(lParamSort == 0)
	{
		return (lParam1 - lParam2) * iFlag;
	}
	int nIndex1, nIndex2;
	TCHAR szText1[MAX_PATH] = {0};
	TCHAR szText2[MAX_PATH] = {0};
	//初始化搜索列表所需结构
	LVFINDINFO lv = {0};
	lv.flags = LVFI_PARAM;
	//根据第一个排序项的数据找到其索引
	lv.lParam = lParam1;
	nIndex1 = ListView_FindItem(g_hList, -1, &lv);
	//根据第二个项的数据找到其索引
	lv.lParam = lParam2;
	nIndex2 = ListView_FindItem(g_hList, -1, &lv);
	//取得第一项的文本
	ListView_GetItemText(g_hList, nIndex1, lParamSort, szText1, MAX_PATH);
	//取得第二项的文本
	ListView_GetItemText(g_hList, nIndex2, lParamSort, szText2, MAX_PATH);
	//比较字符串
	int iCmp = _tcsicmp(szText1, szText2);
	return iCmp * iFlag;
}
