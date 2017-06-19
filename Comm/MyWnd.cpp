// MyWnd.cpp: implementation of the CMyWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyWnd.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyWnd::CMyWnd(): m_hWnd(NULL), m_hMenu(NULL), m_hInstance(NULL)
{
}

CMyWnd::~CMyWnd()
{
	if (m_hWnd)
	{
		Destroy();
	}
}

HWND CMyWnd::CreateEx(HINSTANCE hInst, DWORD dwExStyle, LPCTSTR lpText, DWORD dwStyle, 
	LPRECT lprcWnd, HWND hParent, int nMenuID)
{
	//如果已经创建，返回。防止重复创建
	if (m_hWnd) 
	{
		return m_hWnd;
	}

	m_hInstance = hInst;
	//计算窗体尺寸
	int x, y, nWidth, nHeight;
	if (lprcWnd == NULL)
	{
		x = y = nWidth = nHeight = CW_USEDEFAULT;
	}
	else
	{
		x = lprcWnd->left;
		y = lprcWnd->top;
		nWidth = lprcWnd->right - lprcWnd->left;
		nHeight = lprcWnd->bottom - lprcWnd->top;
	}
	//如果有菜单，加载菜单，并作为窗体菜单
	if(nMenuID > 0)
		m_hMenu = LoadMenu(m_hInstance, MAKEINTRESOURCE(nMenuID));
	//检测类名是否已经注册
	CheckClass(MY_WND_CLASS_NAME);
	//创建窗体
	m_hWnd = CreateWindowEx(dwExStyle, MY_WND_CLASS_NAME, lpText, dwStyle, 
		x, y, nWidth, nHeight, hParent, m_hMenu, m_hInstance, this);
	return m_hWnd;
}

HWND CMyWnd::CreateEx(DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hParent)
{
	//创建窗体的重载函数
	RECT rc = {x, y, x + nWidth, y + nHeight};
	return CreateEx(NULL, 0, _T("MyWnd"), dwStyle, &rc, hParent, 0);
}

void CMyWnd::Destroy()
{
	//销毁窗体
	if(m_hWnd)
	{
		DestroyWindow(m_hWnd);
		m_hWnd = NULL;
	}
}

BOOL CMyWnd::Show(int nCmd)
{
	//显示或隐藏窗体
	return ShowWindow(m_hWnd, nCmd);
}

HWND CMyWnd::GetHwnd()
{
	//返回窗体句柄
	return m_hWnd;
}

CMyWnd::operator HWND() const
{
	return m_hWnd;
}

BOOL CMyWnd::PreProcessMsg(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp, LRESULT *pResult)
{
	//所有消息处理前，会调用此函数。
	//返回TRUE代表继续由相应消息响应函数处理，否则不用再处理
	//消息返回值由pResult中返回
	return TRUE;
}

LRESULT CMyWnd::OnCreate(HWND hWnd)
{
	//WM_CREATE消息的响应函数
	return 0;
}

BOOL CMyWnd::OnDestroy()
{
	//WM_DESTROY消息的响应函数
	return TRUE;
}

BOOL CMyWnd::OnCommand(int nCmdID)
{
	//WM_COMMAND消息的响应函数
	return TRUE;
}

BOOL CMyWnd::OnPaint()
{
	//WM_POINT消息的响应函数
	return TRUE;
}

BOOL CMyWnd::OnEraseBk(HDC hDC)
{
	//WM_ERASEBKGRD消息的响应函数
	return TRUE;
}

BOOL CMyWnd::OnTimer(int nID)
{
	//WM_TIMER消息的响应函数
	return TRUE;
}

BOOL CMyWnd::CheckClass(LPCTSTR lpClassName)
{
	//检测类名，如果没有注册，注册类。
	WNDCLASS ws = {0};
	if(!GetClassInfo(m_hInstance, lpClassName, &ws))
	{
		ws.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
		ws.lpfnWndProc = WndProc;
		ws.lpszClassName = lpClassName;
		return RegisterClass(&ws);
	}
	return TRUE;
}

LRESULT CALLBACK CMyWnd::WndProc(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp)
{
	//消息处理约定：
	//1，派生类处理了某个消息处理函数后，无需再调用基类处理。调用基类意味着默认处理。
	//2，消息处理，除特殊消息外，返回TRUE代表要调用默认处理，否则不调用默认处理

	LRESULT lResult = 0;
	BOOL bCallDefault = TRUE;
	//取出和句柄相对应的类
	CMyWnd *pWnd = (CMyWnd *)GetProp(hWnd, MY_WND_PROP_NAME);;
	if (pWnd == NULL)
	{
		if (nMsg != WM_CREATE) 
		{
			return DefWindowProc(hWnd, nMsg, wp, lp);
		}
		else
		{
			LPCREATESTRUCT pSt = (LPCREATESTRUCT)lp;
			pWnd = (CMyWnd *)pSt->lpCreateParams;
			SetProp(hWnd, MY_WND_PROP_NAME, pWnd);
		}
	}
	if(!pWnd->PreProcessMsg(hWnd, nMsg, wp, lp, &lResult))
		return lResult;
	//处理消息
	switch(nMsg) 
	{
	case WM_CREATE:
		{
			pWnd->m_hWnd = hWnd;
			lResult = pWnd->OnCreate(hWnd);
			bCallDefault = FALSE;
			break;
		}
	case WM_DESTROY:
		bCallDefault = pWnd->OnDestroy();
		break;
	case WM_COMMAND:
		bCallDefault = pWnd->OnCommand(LOWORD(wp));
		break;
	case WM_PAINT:
		bCallDefault = pWnd->OnPaint();
		break;
	case WM_ERASEBKGND:
		bCallDefault = pWnd->OnEraseBk((HDC)wp);
		break;
	case WM_CLOSE:
		pWnd->Destroy();
		bCallDefault = FALSE;
		break;
	case WM_TIMER:
		bCallDefault = pWnd->OnTimer((int)wp);
		break;
	default:
		break;
	}
	//根据消息处理结果，调用默认处理过程，或者直接返回。
	if(bCallDefault)
		return DefWindowProc(hWnd, nMsg, wp, lp);
	else
		return lResult;
}