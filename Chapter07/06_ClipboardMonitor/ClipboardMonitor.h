// ClipboardMonitor.h : main header file for the CLIPBOARDMONITOR application
//

#if !defined(AFX_CLIPBOARDMONITOR_H__0C06D263_AD72_43A9_A2CA_067F8C9E4214__INCLUDED_)
#define AFX_CLIPBOARDMONITOR_H__0C06D263_AD72_43A9_A2CA_067F8C9E4214__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CClipboardMonitorApp:
// See ClipboardMonitor.cpp for the implementation of this class
//

class CClipboardMonitorApp : public CWinApp
{
public:
	CClipboardMonitorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipboardMonitorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClipboardMonitorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPBOARDMONITOR_H__0C06D263_AD72_43A9_A2CA_067F8C9E4214__INCLUDED_)
