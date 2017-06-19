// MainWnd.h: interface for the CMainWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINWND_H__DBAB6247_21C8_4657_875D_32ADD9C7833E__INCLUDED_)
#define AFX_MAINWND_H__DBAB6247_21C8_4657_875D_32ADD9C7833E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\comm\MyWnd.h"

class CMainWnd : public CMyWnd  
{
public:
	CMainWnd();
	virtual ~CMainWnd();
protected:
	LRESULT OnCreate(HWND hWnd);
	BOOL OnDestroy();
	BOOL OnTimer(int nID);
};

#endif // !defined(AFX_MAINWND_H__DBAB6247_21C8_4657_875D_32ADD9C7833E__INCLUDED_)
