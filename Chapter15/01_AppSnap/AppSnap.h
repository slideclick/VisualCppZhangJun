// AppSnap.h : main header file for the APPSNAP application
//

#if !defined(AFX_APPSNAP_H__DB78DFED_DF0B_46A2_8550_10F6FAF9827F__INCLUDED_)
#define AFX_APPSNAP_H__DB78DFED_DF0B_46A2_8550_10F6FAF9827F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAppSnapApp:
// See AppSnap.cpp for the implementation of this class
//

class CAppSnapApp : public CWinApp
{
public:
	CAppSnapApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppSnapApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAppSnapApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPSNAP_H__DB78DFED_DF0B_46A2_8550_10F6FAF9827F__INCLUDED_)
