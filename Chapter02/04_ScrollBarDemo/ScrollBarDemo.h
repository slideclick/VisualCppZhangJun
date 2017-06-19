// ScrollBarDemo.h : main header file for the SCROLLBARDEMO application
//

#if !defined(AFX_SCROLLBARDEMO_H__B39BB8F7_DF12_42A7_8A4B_FA25D8F7B986__INCLUDED_)
#define AFX_SCROLLBARDEMO_H__B39BB8F7_DF12_42A7_8A4B_FA25D8F7B986__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CScrollBarDemoApp:
// See ScrollBarDemo.cpp for the implementation of this class
//

class CScrollBarDemoApp : public CWinApp
{
public:
	CScrollBarDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrollBarDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CScrollBarDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCROLLBARDEMO_H__B39BB8F7_DF12_42A7_8A4B_FA25D8F7B986__INCLUDED_)
