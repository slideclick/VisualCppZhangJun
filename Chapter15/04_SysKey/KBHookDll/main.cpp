// MouseHookDll.cpp : Defines the entry point for the DLL application.
//

#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <tchar.h>

//建立数据段
#pragma data_seg("sharedata")
HHOOK		g_hHook		= NULL;
HINSTANCE	g_hInstance = NULL;
DWORD		g_dwVKey	= 0;
#pragma data_seg()
//设置该段为可读可写可共享
#pragma comment(linker, "/SECTION:sharedata,RWS")

//HOOK处理过程
LRESULT WINAPI HookProc(int nCode, WPARAM wparam, LPARAM lparam)
{
	if(g_dwVKey != 0 && nCode == HC_ACTION)
	{
		LPKBDLLHOOKSTRUCT pkh = (LPKBDLLHOOKSTRUCT)lparam;
		//如果按下指定键，直接返回
		if(pkh->vkCode == g_dwVKey)
		{
			if (wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN) 
			{
				MessageBeep(MB_ICONASTERISK);
			}
			return TRUE;
		}
	}
	//继续传递消息
	return CallNextHookEx(g_hHook, nCode, wparam, lparam);
}
//DLL入口函数
BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved)
{
	switch(ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//初始化并安装钩子
		g_hInstance = (HINSTANCE)hModule;
		g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, HookProc, g_hInstance, 0);
		if(g_hHook == NULL)
			DebugBreak();
		break;
	case DLL_PROCESS_DETACH:
		//卸载钩子
		UnhookWindowsHookEx(g_hHook);
		g_hHook = NULL;
		g_dwVKey = 0;
		break;
	}
	return TRUE;
}
//更改要屏蔽的按键
extern "C" 
__declspec(dllexport) void SetVKey(DWORD dwVKey)
{
	g_dwVKey = dwVKey;
}