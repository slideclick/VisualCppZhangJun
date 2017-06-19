#if !defined(AFX_MYACTIVEX_H__2C2AFADB_3172_4D1F_AA41_0EF9F221FD9C__INCLUDED_)
#define AFX_MYACTIVEX_H__2C2AFADB_3172_4D1F_AA41_0EF9F221FD9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// MyActiveX.h : main header file for MYACTIVEX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyActiveXApp : See MyActiveX.cpp for implementation.

class CMyActiveXApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYACTIVEX_H__2C2AFADB_3172_4D1F_AA41_0EF9F221FD9C__INCLUDED)
