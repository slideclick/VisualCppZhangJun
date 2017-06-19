// RegOCX.h : main header file for the REGOCX application
//

#if !defined(AFX_REGOCX_H__F0A48C3B_E28B_4390_810B_E20AEEDAC6ED__INCLUDED_)
#define AFX_REGOCX_H__F0A48C3B_E28B_4390_810B_E20AEEDAC6ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRegOCXApp:
// See RegOCX.cpp for the implementation of this class
//

class CRegOCXApp : public CWinApp
{
public:
	CRegOCXApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegOCXApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRegOCXApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGOCX_H__F0A48C3B_E28B_4390_810B_E20AEEDAC6ED__INCLUDED_)
