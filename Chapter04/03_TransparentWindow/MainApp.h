// MainApp.h: interface for the CMainApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINAPP_H__D1A93B02_C44A_4493_8AAB_C53332AB2543__INCLUDED_)
#define AFX_MAINAPP_H__D1A93B02_C44A_4493_8AAB_C53332AB2543__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\comm\MyApp.h"
#include "mainWnd.h"

//应用程序框架类
class CMainApp : public CMyApp  
{
public:
	CMainApp();
	virtual ~CMainApp();
protected:
	BOOL InitInstance();
protected:
	CMainWnd m_wnd;
};

#endif // !defined(AFX_MAINAPP_H__D1A93B02_C44A_4493_8AAB_C53332AB2543__INCLUDED_)
