// MouseHookDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <tchar.h>

//�������ݶ�
#pragma data_seg("sharedata")
HHOOK		g_hHook		= NULL;
HWND		g_hShowWnd	= NULL;
HWND		g_hPreWnd	= NULL;
HINSTANCE	g_hInstance = NULL;
#pragma data_seg()
//���øö�Ϊ�ɶ���д�ɹ���
#pragma comment(linker, "/SECTION:sharedata,RWS")

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	if(ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		g_hInstance = (HINSTANCE)hModule;
	}
   return TRUE;
}
//HOOK�������
LRESULT WINAPI MouseMessageProc(int nCode, WPARAM wparam, LPARAM lparam)
{
	LPMOUSEHOOKSTRUCT pMouseHook = (MOUSEHOOKSTRUCT FAR *)lparam;
	HWND hWnd = pMouseHook->hwnd;
	//�����һ���µĴ���
	if(hWnd != g_hPreWnd)
	{
		TCHAR szClass[MAX_PATH] = {0};
		GetClassName(hWnd, szClass, MAX_PATH);
		if(_tcsicmp(szClass, _T("edit")) == 0)
		{
			LONG lStyle = GetWindowLong(hWnd, GWL_STYLE);
			//�������������񣬷�����ʾ��
			if((lStyle & ES_PASSWORD) == ES_PASSWORD)
			{
				MessageBeep(MB_ICONASTERISK);
			}
		}
		//��ȡ���ı�
		TCHAR szText[260];
		GetWindowText(hWnd, szText, 265);
		//��ʾ�ı�
		SendMessage(g_hShowWnd, WM_SETTEXT, 0, (LPARAM)szText);
		g_hPreWnd = hWnd;
	}
	return CallNextHookEx(g_hHook, nCode, wparam, lparam);
}
//��װHOOK������0����ɹ���������������
extern "C" 
__declspec(dllexport) DWORD StartHook(HWND hShowWnd)
{
	if(!hShowWnd)
		DebugBreak();
	
	DWORD dwRet = 0;
	g_hShowWnd = hShowWnd;
	g_hHook = SetWindowsHookEx(WH_MOUSE, MouseMessageProc, g_hInstance, 0);
	if(g_hHook == NULL)
		dwRet = GetLastError();
	return dwRet;
}
//ж��HOOK
extern "C" 
__declspec(dllexport) DWORD StopHook()
{
	if(UnhookWindowsHookEx(g_hHook))
	{
		g_hShowWnd = NULL;
		g_hPreWnd = NULL;
		return 0;
	}
	else
	{
		return GetLastError();
	}
}