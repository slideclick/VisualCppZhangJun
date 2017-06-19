// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__E68EB77E_9FCC_4EE5_BA25_490FD083EA69__INCLUDED_)
#define AFX_STDAFX_H__E68EB77E_9FCC_4EE5_BA25_490FD083EA69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//使用WinSock所需的头文件
#include <WINSOCK.H>
//使用WinSock所需的库文件
#pragma comment(lib, "WSOCK32.LIB")
//宏定义
#define SOCK_VER 2
#define WM_USER_SOCKACCEPT (WM_USER+201)
#define WM_USER_SOCKMSG (WM_USER+202)

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E68EB77E_9FCC_4EE5_BA25_490FD083EA69__INCLUDED_)
