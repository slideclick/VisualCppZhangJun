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
* 类CMyWnd的申明，此类是一个简单封装的、可重用的窗体类
*
*-------------------------------*/

#define MY_WND_PROP_NAME _T("_My_Wnd_Prop_Name_")
#define MY_WND_CLASS_NAME _T("_My_Wnd_Class_Name_")

class CMyWnd  
{
public:
	CMyWnd();
	virtual ~CMyWnd();
	//创建窗体
	HWND CreateEx(HINSTANCE hInst, DWORD dwExStyle, LPCTSTR lpText, DWORD dwStyle, 
		LPRECT lprcWnd, HWND hParent, int nMenuID);
	HWND CreateEx(DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hParent);
	//销毁窗体
	void Destroy();
	//显示或隐藏窗体
	BOOL Show(int nCmd);
	//获取窗体句柄
	HWND GetHwnd();
	//可直接返回窗体句柄的操作符
	operator HWND() const;
protected:	
	//处理前的派生类调用机会
	virtual BOOL PreProcessMsg(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp, LRESULT *pResult);
	//窗体创建消息
	virtual LRESULT OnCreate(HWND hWnd);
	//窗体销毁消息
	virtual BOOL OnDestroy();
	//处理命令按钮消息
	virtual BOOL OnCommand(int nCmdID);
	//绘制窗体
	virtual BOOL OnPaint();
	//绘制背景
	virtual BOOL OnEraseBk(HDC hDC);
	//Timer消息
	virtual BOOL OnTimer(int nID);
protected:
	//检测类是否注册，如果没有注册则注册
	BOOL CheckClass(LPCTSTR lpClassName);
	//窗体过程
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp);
protected:
	HWND m_hWnd;
	HMENU m_hMenu;
	HINSTANCE m_hInstance;
};

#endif // !defined(AFX_MYWND_H__A7864307_0985_4432_B8D0_3650ED3B0EA3__INCLUDED_)
