#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <commctrl.h>
#include "resource.h"

#pragma comment(lib, "comctl32.lib")

//----------------
//函数声明
//----------------
//对话框过程函数
INT_PTR CALLBACK 
DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//对话框初始化消息处理
void OnInitDialog();
//对话框命令响应
void OnCommand(WPARAM wp, LPARAM lp);
//WM_SIZE消息响应
void OnSize(WPARAM wp, LPARAM lp);
//按照指定规则移动某个控件
HDWP MoveCtrl(HDWP hDwp, UINT nID, int x, int y, 
		BOOL bLeft, BOOL bTop, BOOL bRight, BOOL bBottom);
//WM_LBUTTONDOWN消息响应
void OnLButtonDown(UINT nType, int x, int y);
//WM_LBUTTONUP消息响应
void OnLButtonUp(UINT nType, int x, int y);
//树形控件选中项改变消息
void OnTreeSelChanged(LPNMHDR pnmh);
//将屏幕坐标转换为窗体坐标
void ScreenToClientRect(LPRECT prc);
//将窗体坐标转换为屏幕坐标
void ClientToScreenRect(LPRECT prc);
//获取窗口列表
void GetWindowList(HWND hWnd);
//取得进程详细信息并显示到列表控件中
void AddProcessRow(DWORD dwPID);
//打开或关闭当前进程的DEBUG权限
BOOL SetDebugPrivilege(BOOL bEnable); 
void GetListFunc(HWND hWnd, HTREEITEM hItem);
//枚举窗口的回调函数
BOOL CALLBACK EnumFunc(HWND hwnd, LPARAM lParam);
