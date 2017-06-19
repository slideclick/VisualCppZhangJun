// PicShow.h : main header file for the PICSHOW application
//

#if !defined(AFX_PICSHOW_H__95D414BE_C1A4_4ED8_B0EC_829FE28DA6DC__INCLUDED_)
#define AFX_PICSHOW_H__95D414BE_C1A4_4ED8_B0EC_829FE28DA6DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPicShowApp:
// See PicShow.cpp for the implementation of this class
//

class CPicShowApp : public CWinApp
{
public:
	CPicShowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicShowApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPicShowApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	GdiplusStartupInput		m_gdiplusStartupInput;
	ULONG_PTR               m_gdiplusToken;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICSHOW_H__95D414BE_C1A4_4ED8_B0EC_829FE28DA6DC__INCLUDED_)
