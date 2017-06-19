// RollText.h : main header file for the ROLLTEXT application
//

#if !defined(AFX_ROLLTEXT_H__0C8F14D3_037B_48B0_8A01_F2C88D26CE36__INCLUDED_)
#define AFX_ROLLTEXT_H__0C8F14D3_037B_48B0_8A01_F2C88D26CE36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRollTextApp:
// See RollText.cpp for the implementation of this class
//

class CRollTextApp : public CWinApp
{
public:
	CRollTextApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRollTextApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRollTextApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROLLTEXT_H__0C8F14D3_037B_48B0_8A01_F2C88D26CE36__INCLUDED_)
