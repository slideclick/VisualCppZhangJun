// MappingClient.h : main header file for the MAPPINGCLIENT application
//

#if !defined(AFX_MAPPINGCLIENT_H__9DB1B6C6_8E1A_4B45_B1F9_8EA9030AE866__INCLUDED_)
#define AFX_MAPPINGCLIENT_H__9DB1B6C6_8E1A_4B45_B1F9_8EA9030AE866__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMappingClientApp:
// See MappingClient.cpp for the implementation of this class
//

class CMappingClientApp : public CWinApp
{
public:
	CMappingClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMappingClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMappingClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPPINGCLIENT_H__9DB1B6C6_8E1A_4B45_B1F9_8EA9030AE866__INCLUDED_)
