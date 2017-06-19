// SaveFileDemo.h : main header file for the SAVEFILEDEMO application
//

#if !defined(AFX_SAVEFILEDEMO_H__2A6FF4A7_4884_41DF_AF6D_3288674FAF11__INCLUDED_)
#define AFX_SAVEFILEDEMO_H__2A6FF4A7_4884_41DF_AF6D_3288674FAF11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSaveFileDemoApp:
// See SaveFileDemo.cpp for the implementation of this class
//

class CSaveFileDemoApp : public CWinApp
{
public:
	CSaveFileDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveFileDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSaveFileDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEFILEDEMO_H__2A6FF4A7_4884_41DF_AF6D_3288674FAF11__INCLUDED_)
