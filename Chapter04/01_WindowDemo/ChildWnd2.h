// ChildWnd2.h: interface for the CChildWnd2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDWND2_H__38379ACD_846D_46FA_848C_60104C2F3881__INCLUDED_)
#define AFX_CHILDWND2_H__38379ACD_846D_46FA_848C_60104C2F3881__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\comm\MyWnd.h"

class CChildWnd2 : public CMyWnd  
{
public:
	CChildWnd2();
	virtual ~CChildWnd2();
	BOOL OnEraseBk(HDC hDC);
};

#endif // !defined(AFX_CHILDWND2_H__38379ACD_846D_46FA_848C_60104C2F3881__INCLUDED_)
