// KeyTestWnd.h: interface for the CKeyTestWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEYTESTWND_H__6BA470EE_53C3_4E10_999E_5864E1FEBED8__INCLUDED_)
#define AFX_KEYTESTWND_H__6BA470EE_53C3_4E10_999E_5864E1FEBED8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\COMM\MyWnd.h"

class CKeyTestWnd : public CMyWnd  
{
public:
	CKeyTestWnd();
	virtual ~CKeyTestWnd();
protected:
	BOOL OnDestroy();
};

#endif // !defined(AFX_KEYTESTWND_H__6BA470EE_53C3_4E10_999E_5864E1FEBED8__INCLUDED_)
