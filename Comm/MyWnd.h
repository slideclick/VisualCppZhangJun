// MyWnd.h: interface for the CMyWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYWND_H__A7864307_0985_4432_B8D0_3650ED3B0EA3__INCLUDED_)
#define AFX_MYWND_H__A7864307_0985_4432_B8D0_3650ED3B0EA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

/*-------------------------------
*
* ��CMyWnd��������������һ���򵥷�װ�ġ������õĴ�����
*
*-------------------------------*/

#define MY_WND_PROP_NAME _T("_My_Wnd_Prop_Name_")
#define MY_WND_CLASS_NAME _T("_My_Wnd_Class_Name_")

class CMyWnd  
{
public:
	CMyWnd();
	virtual ~CMyWnd();
	//��������
	HWND CreateEx(HINSTANCE hInst, DWORD dwExStyle, LPCTSTR lpText, DWORD dwStyle, 
		LPRECT lprcWnd, HWND hParent, int nMenuID);
	HWND CreateEx(DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hParent);
	//���ٴ���
	void Destroy();
	//��ʾ�����ش���
	BOOL Show(int nCmd);
	//��ȡ������
	HWND GetHwnd();
	//��ֱ�ӷ��ش������Ĳ�����
	operator HWND() const;
protected:	
	//����ǰ����������û���
	virtual BOOL PreProcessMsg(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp, LRESULT *pResult);
	//���崴����Ϣ
	virtual LRESULT OnCreate(HWND hWnd);
	//����������Ϣ
	virtual BOOL OnDestroy();
	//�������ť��Ϣ
	virtual BOOL OnCommand(int nCmdID);
	//���ƴ���
	virtual BOOL OnPaint();
	//���Ʊ���
	virtual BOOL OnEraseBk(HDC hDC);
	//Timer��Ϣ
	virtual BOOL OnTimer(int nID);
protected:
	//������Ƿ�ע�ᣬ���û��ע����ע��
	BOOL CheckClass(LPCTSTR lpClassName);
	//�������
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp);
protected:
	HWND m_hWnd;
	HMENU m_hMenu;
	HINSTANCE m_hInstance;
};

#endif // !defined(AFX_MYWND_H__A7864307_0985_4432_B8D0_3650ED3B0EA3__INCLUDED_)
