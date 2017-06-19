#if !defined(AFX_MYSOCKET_H__6AC22299_071C_4872_947A_6C2437EB8904__INCLUDED_)
#define AFX_MYSOCKET_H__6AC22299_071C_4872_947A_6C2437EB8904__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySocket.h : header file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CMySocket command target

class CMySocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CMySocket();
	virtual ~CMySocket();
	void SetHost(HWND hWnd);
// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySocket)
	public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMySocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	void ErrMsg(int nCode);
	void OutputMsg(LPCTSTR lpMsg);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSOCKET_H__6AC22299_071C_4872_947A_6C2437EB8904__INCLUDED_)
