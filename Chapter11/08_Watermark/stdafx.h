#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <Richedit.h>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
//GDI+相关
#ifndef ULONG_PTR
#define ULONG_PTR unsigned long*
#include <GdiPlus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")
#endif

//函数申明
HINSTANCE GetInstance();
void DoEvents();