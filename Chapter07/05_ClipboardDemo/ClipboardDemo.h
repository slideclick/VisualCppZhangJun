// ClipboardDemo.h : main header file for the CLIPBOARDDEMO application
//

#if !defined(AFX_CLIPBOARDDEMO_H__D7A68D34_B89B_47B5_BF4E_3D489269A12F__INCLUDED_)
#define AFX_CLIPBOARDDEMO_H__D7A68D34_B89B_47B5_BF4E_3D489269A12F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CClipboardDemoApp:
// See ClipboardDemo.cpp for the implementation of this class
//

class CClipboardDemoApp : public CWinApp
{
public:
	CClipboardDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipboardDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClipboardDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPBOARDDEMO_H__D7A68D34_B89B_47B5_BF4E_3D489269A12F__INCLUDED_)
