// GetHttpStr.h : main header file for the GETHTTPSTR application
//

#if !defined(AFX_GETHTTPSTR_H__05C6DDEA_517B_496B_A810_33DFE316EB80__INCLUDED_)
#define AFX_GETHTTPSTR_H__05C6DDEA_517B_496B_A810_33DFE316EB80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGetHttpStrApp:
// See GetHttpStr.cpp for the implementation of this class
//

class CGetHttpStrApp : public CWinApp
{
public:
	CGetHttpStrApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetHttpStrApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGetHttpStrApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETHTTPSTR_H__05C6DDEA_517B_496B_A810_33DFE316EB80__INCLUDED_)
