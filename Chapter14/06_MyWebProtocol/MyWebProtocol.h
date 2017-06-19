// MyWebProtocol.h : main header file for the MYWEBPROTOCOL application
//

#if !defined(AFX_MYWEBPROTOCOL_H__9C021280_62A7_46DD_B4DE_93DF310DA6A7__INCLUDED_)
#define AFX_MYWEBPROTOCOL_H__9C021280_62A7_46DD_B4DE_93DF310DA6A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyWebProtocolApp:
// See MyWebProtocol.cpp for the implementation of this class
//

class CMyWebProtocolApp : public CWinApp
{
public:
	CMyWebProtocolApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyWebProtocolApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyWebProtocolApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYWEBPROTOCOL_H__9C021280_62A7_46DD_B4DE_93DF310DA6A7__INCLUDED_)
