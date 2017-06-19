// PreviewFileDlg_Demo.h : main header file for the PREVIEWFILEDLG_DEMO application
//

#if !defined(AFX_PREVIEWFILEDLG_DEMO_H__C1DD97D1_2750_4BB8_BA78_22DD30213BD3__INCLUDED_)
#define AFX_PREVIEWFILEDLG_DEMO_H__C1DD97D1_2750_4BB8_BA78_22DD30213BD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPreviewFileDlg_DemoApp:
// See PreviewFileDlg_Demo.cpp for the implementation of this class
//

class CPreviewFileDlg_DemoApp : public CWinApp
{
protected:
	ULONG_PTR gdiplusToken; 
public:
	CPreviewFileDlg_DemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreviewFileDlg_DemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPreviewFileDlg_DemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREVIEWFILEDLG_DEMO_H__C1DD97D1_2750_4BB8_BA78_22DD30213BD3__INCLUDED_)
