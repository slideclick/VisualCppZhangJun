// MainWnd.h: interface for the CMainWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINWND_H__2B791775_5F59_4D38_B13C_24518485F474__INCLUDED_)
#define AFX_MAINWND_H__2B791775_5F59_4D38_B13C_24518485F474__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\comm\MyWnd.h"
#include "childwnd1.h"
#include "childwnd2.h"

class CMainWnd : public CMyWnd  
{
public:
	CMainWnd();
	virtual ~CMainWnd();
protected:
	BOOL OnCommand(int nCmdID);
	BOOL OnDestroy();
private:
	CChildWnd1 m_wndChild1;	//≤‚ ‘¥∞ÃÂ1
	CChildWnd2 m_wndChild2;	//≤‚ ‘¥∞ÃÂ2
};

#endif // !defined(AFX_MAINWND_H__2B791775_5F59_4D38_B13C_24518485F474__INCLUDED_)
