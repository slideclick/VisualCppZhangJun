// MsgWnd.h: interface for the CMsgWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGWND_H__D70F43C9_C5A6_4B63_9171_6FEFE77A0D13__INCLUDED_)
#define AFX_MSGWND_H__D70F43C9_C5A6_4B63_9171_6FEFE77A0D13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\COMM\MyWnd.h"

class CMsgWnd : public CMyWnd  
{
public:
	//����������Ա
	CMsgWnd();
	virtual ~CMsgWnd();
	BOOL OnIdle();
protected:
	//����������Ա
	BOOL OnDestroy();
	BOOL PreProcessMsg(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp, LRESULT *pResult);
protected:
	//�������ݳ�Ա
	DWORD m_dwTick;
};

#endif // !defined(AFX_MSGWND_H__D70F43C9_C5A6_4B63_9171_6FEFE77A0D13__INCLUDED_)
