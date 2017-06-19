// BgMusic.h : main header file for the BGMUSIC application
//

#if !defined(AFX_BGMUSIC_H__28304B53_DB4F_479B_B62B_0366B41D6656__INCLUDED_)
#define AFX_BGMUSIC_H__28304B53_DB4F_479B_B62B_0366B41D6656__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBgMusicApp:
// See BgMusic.cpp for the implementation of this class
//

class CBgMusicApp : public CWinApp
{
public:
	CBgMusicApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBgMusicApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBgMusicApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BGMUSIC_H__28304B53_DB4F_479B_B62B_0366B41D6656__INCLUDED_)
