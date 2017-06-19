// HotkeyDemo.h : main header file for the HOTKEYDEMO application
//

#if !defined(AFX_HOTKEYDEMO_H__AA22DC74_86C9_4F07_9EA8_F4D021769C14__INCLUDED_)
#define AFX_HOTKEYDEMO_H__AA22DC74_86C9_4F07_9EA8_F4D021769C14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHotkeyDemoApp:
// See HotkeyDemo.cpp for the implementation of this class
//

class CHotkeyDemoApp : public CWinApp
{
public:
	CHotkeyDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHotkeyDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHotkeyDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOTKEYDEMO_H__AA22DC74_86C9_4F07_9EA8_F4D021769C14__INCLUDED_)
