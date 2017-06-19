// Ado_Demo.h : main header file for the ADO_DEMO application
//

#if !defined(AFX_ADO_DEMO_H__8C01EEB1_3D49_4B00_AFBE_608C7FDE9E28__INCLUDED_)
#define AFX_ADO_DEMO_H__8C01EEB1_3D49_4B00_AFBE_608C7FDE9E28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAdo_DemoApp:
// See Ado_Demo.cpp for the implementation of this class
//

class CAdo_DemoApp : public CWinApp
{
public:
	CAdo_DemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdo_DemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAdo_DemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADO_DEMO_H__8C01EEB1_3D49_4B00_AFBE_608C7FDE9E28__INCLUDED_)
