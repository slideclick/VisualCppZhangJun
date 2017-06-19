#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <commctrl.h>
#include "resource.h"

#pragma comment(lib, "comctl32.lib")

//----------------
//��������
//----------------
//�Ի�����̺���
INT_PTR CALLBACK 
DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//�Ի����ʼ����Ϣ����
void OnInitDialog();
//�Ի���������Ӧ
void OnCommand(WPARAM wp, LPARAM lp);
//WM_SIZE��Ϣ��Ӧ
void OnSize(WPARAM wp, LPARAM lp);
//����ָ�������ƶ�ĳ���ؼ�
HDWP MoveCtrl(HDWP hDwp, UINT nID, int x, int y, 
		BOOL bLeft, BOOL bTop, BOOL bRight, BOOL bBottom);
//WM_LBUTTONDOWN��Ϣ��Ӧ
void OnLButtonDown(UINT nType, int x, int y);
//WM_LBUTTONUP��Ϣ��Ӧ
void OnLButtonUp(UINT nType, int x, int y);
//���οؼ�ѡ����ı���Ϣ
void OnTreeSelChanged(LPNMHDR pnmh);
//����Ļ����ת��Ϊ��������
void ScreenToClientRect(LPRECT prc);
//����������ת��Ϊ��Ļ����
void ClientToScreenRect(LPRECT prc);
//��ȡ�����б�
void GetWindowList(HWND hWnd);
//ȡ�ý�����ϸ��Ϣ����ʾ���б�ؼ���
void AddProcessRow(DWORD dwPID);
//�򿪻�رյ�ǰ���̵�DEBUGȨ��
BOOL SetDebugPrivilege(BOOL bEnable); 
void GetListFunc(HWND hWnd, HTREEITEM hItem);
//ö�ٴ��ڵĻص�����
BOOL CALLBACK EnumFunc(HWND hwnd, LPARAM lParam);
