// TcpServer.h : main header file for the TCPSERVER application
//

#if !defined(AFX_TCPSERVER_H__70BB5707_6AFF_4385_872C_9511ED4E7579__INCLUDED_)
#define AFX_TCPSERVER_H__70BB5707_6AFF_4385_872C_9511ED4E7579__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTcpServerApp:
// See TcpServer.cpp for the implementation of this class
//

class CTcpServerApp : public CWinApp
{
public:
	CTcpServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTcpServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTcpServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCPSERVER_H__70BB5707_6AFF_4385_872C_9511ED4E7579__INCLUDED_)
