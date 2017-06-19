// MyCompressor.h : main header file for the MYCOMPRESSOR application
//

#if !defined(AFX_MYCOMPRESSOR_H__DE3D6179_497B_41CD_B924_F38BEEC7A745__INCLUDED_)
#define AFX_MYCOMPRESSOR_H__DE3D6179_497B_41CD_B924_F38BEEC7A745__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyCompressorApp:
// See MyCompressor.cpp for the implementation of this class
//

class CMyCompressorApp : public CWinApp
{
public:
	CMyCompressorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCompressorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyCompressorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCOMPRESSOR_H__DE3D6179_497B_41CD_B924_F38BEEC7A745__INCLUDED_)
