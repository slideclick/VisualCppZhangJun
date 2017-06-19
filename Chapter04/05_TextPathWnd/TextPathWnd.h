// TextPathWnd.h : main header file for the TEXTPATHWND application
//

#if !defined(AFX_TEXTPATHWND_H__A2A8E549_6C33_4FBA_93C6_41271F648495__INCLUDED_)
#define AFX_TEXTPATHWND_H__A2A8E549_6C33_4FBA_93C6_41271F648495__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTextPathWndApp:
// See TextPathWnd.cpp for the implementation of this class
//

class CTextPathWndApp : public CWinApp
{
public:
	CTextPathWndApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextPathWndApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTextPathWndApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTPATHWND_H__A2A8E549_6C33_4FBA_93C6_41271F648495__INCLUDED_)
