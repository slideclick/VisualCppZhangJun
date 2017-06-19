// OpenFileDemo.h : main header file for the OPENFILEDEMO application
//

#if !defined(AFX_OPENFILEDEMO_H__A12BBF24_15E4_4A08_BB11_29D80681AA23__INCLUDED_)
#define AFX_OPENFILEDEMO_H__A12BBF24_15E4_4A08_BB11_29D80681AA23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COpenFileDemoApp:
// See OpenFileDemo.cpp for the implementation of this class
//

class COpenFileDemoApp : public CWinApp
{
public:
	COpenFileDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenFileDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COpenFileDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENFILEDEMO_H__A12BBF24_15E4_4A08_BB11_29D80681AA23__INCLUDED_)
