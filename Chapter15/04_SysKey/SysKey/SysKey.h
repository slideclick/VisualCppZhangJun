// SysKey.h : main header file for the SYSKEY application
//

#if !defined(AFX_SYSKEY_H__054C7793_6507_45A9_97A3_1F953D1A1225__INCLUDED_)
#define AFX_SYSKEY_H__054C7793_6507_45A9_97A3_1F953D1A1225__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSysKeyApp:
// See SysKey.cpp for the implementation of this class
//

class CSysKeyApp : public CWinApp
{
public:
	CSysKeyApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysKeyApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSysKeyApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSKEY_H__054C7793_6507_45A9_97A3_1F953D1A1225__INCLUDED_)
