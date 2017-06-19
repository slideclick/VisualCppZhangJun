// MyApp.h: interface for the CMyApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYAPP_H__DC022CCE_851A_458A_8D61_1F676C5B6404__INCLUDED_)
#define AFX_MYAPP_H__DC022CCE_851A_458A_8D61_1F676C5B6404__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*-------------------------------
*
* 类CMyApp的申明，此类是一个简单的、可重用的应用程序框架类
*
*-------------------------------*/

#include "stdafx.h"

class CMyApp  
{
public:
	CMyApp();
	virtual ~CMyApp();
	virtual BOOL InitInstance();
	virtual int ExitInstance(int nExitCode);
};

#endif // !defined(AFX_MYAPP_H__DC022CCE_851A_458A_8D61_1F676C5B6404__INCLUDED_)
