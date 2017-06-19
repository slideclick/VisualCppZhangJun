// MouseHookDll.cpp : Defines the entry point for the DLL application.
//

#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <tchar.h>

//�������ݶ�
#pragma data_seg("sharedata")
HHOOK		g_hHook		= NULL;
HINSTANCE	g_hInstance = NULL;
DWORD		g_dwVKey	= 0;
#pragma data_seg()
//���øö�Ϊ�ɶ���д�ɹ���
#pragma comment(linker, "/SECTION:sharedata,RWS")

//HOOK�������
LRESULT WINAPI HookProc(int nCode, WPARAM wparam, LPARAM lparam)
{
	if(g_dwVKey != 0 && nCode == HC_ACTION)
	{
		LPKBDLLHOOKSTRUCT pkh = (LPKBDLLHOOKSTRUCT)lparam;
		//�������ָ������ֱ�ӷ���
		if(pkh->vkCode == g_dwVKey)
		{
			if (wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN) 
			{
				MessageBeep(MB_ICONASTERISK);
			}
			return TRUE;
		}
	}
	//����������Ϣ
	return CallNextHookEx(g_hHook, nCode, wparam, lparam);
}
//DLL��ں���
BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved)
{
	switch(ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//��ʼ������װ����
		g_hInstance = (HINSTANCE)hModule;
		g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, HookProc, g_hInstance, 0);
		if(g_hHook == NULL)
			DebugBreak();
		break;
	case DLL_PROCESS_DETACH:
		//ж�ع���
		UnhookWindowsHookEx(g_hHook);
		g_hHook = NULL;
		g_dwVKey = 0;
		break;
	}
	return TRUE;
}
//����Ҫ���εİ���
extern "C" 
__declspec(dllexport) void SetVKey(DWORD dwVKey)
{
	g_dwVKey = dwVKey;
}