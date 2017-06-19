// ChildWnd1.h: interface for the CChildWnd1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDWND1_H__17C77530_60AC_433B_9F0E_6DCC24A6FBF2__INCLUDED_)
#define AFX_CHILDWND1_H__17C77530_60AC_433B_9F0E_6DCC24A6FBF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\comm\MyWnd.h"

class CChildWnd1 : public CMyWnd  
{
public:
	CChildWnd1();
	virtual ~CChildWnd1();
	BOOL OnEraseBk(HDC hDC);
};

#endif // !defined(AFX_CHILDWND1_H__17C77530_60AC_433B_9F0E_6DCC24A6FBF2__INCLUDED_)
