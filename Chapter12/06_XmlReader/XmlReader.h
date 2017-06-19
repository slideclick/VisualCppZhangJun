// XmlReader.h : main header file for the XMLREADER application
//

#if !defined(AFX_XMLREADER_H__05172B8C_01E6_4C66_9E83_775A4F239B33__INCLUDED_)
#define AFX_XMLREADER_H__05172B8C_01E6_4C66_9E83_775A4F239B33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXmlReaderApp:
// See XmlReader.cpp for the implementation of this class
//

class CXmlReaderApp : public CWinApp
{
public:
	CXmlReaderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXmlReaderApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXmlReaderApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMLREADER_H__05172B8C_01E6_4C66_9E83_775A4F239B33__INCLUDED_)
