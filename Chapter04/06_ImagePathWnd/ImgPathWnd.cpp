// ImgPathWnd.cpp: implementation of the CImgPathWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "ImgPathWnd.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImgPathWnd::CImgPathWnd(): m_hRgn(NULL), m_hMemDC(NULL), m_hBmp(NULL), m_hOldBmp(NULL)
{
}

CImgPathWnd::~CImgPathWnd()
{
}

LRESULT CImgPathWnd::OnCreate(HWND hWnd)
{
	//从资源加载位图
	m_hBmp = LoadBitmap(MyGetInstance(), MAKEINTRESOURCE(IDB_BK));
	//创建一个内存兼容DC
	HDC hDC = GetDC(m_hWnd);
	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(m_hWnd, hDC);
	//将内存DC和位图关联
	HBITMAP m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBmp);
	//根据位图建立区域对象
	m_hRgn = CreateRgn(RGB(255, 0, 255));
	//将区域设置到窗体
	SetWindowRgn(m_hWnd, m_hRgn, TRUE);
	return 0;
}

BOOL CImgPathWnd::OnDestroy()
{
	//释放区域对象
	if(m_hRgn)
	{
		DeleteObject(m_hRgn);
		m_hRgn = NULL;
	}
	//释放位图相关对象
	if (m_hMemDC)
	{
		SelectObject(m_hMemDC, m_hOldBmp);
		DeleteDC(m_hMemDC);
		m_hMemDC = NULL;
		m_hBmp = m_hOldBmp = NULL;
		DeleteObject(m_hBmp);
	}
	//投递退出消息
	PostQuitMessage(0);
	return TRUE;
}

BOOL CImgPathWnd::OnPaint()
{
	RECT rect = {0};
	GetClientRect(m_hWnd, &rect);
	//将位图绘制到窗体
	PAINTSTRUCT ps = {0};
	BeginPaint(m_hWnd, &ps);
	BitBlt(ps.hdc, 0, 0, rect.right, rect.bottom, m_hMemDC, 0, 0, SRCCOPY);
	EndPaint(m_hWnd, &ps);	
	return FALSE;
}

HRGN CImgPathWnd::CreateRgn(COLORREF crTransparent)
{
	//根据位图生成区域对象
	BITMAP bmp = {0};
	GetObject(m_hBmp, sizeof(bmp), &bmp);
	//循环中用到的临时变量
	HRGN hRgn = NULL;
	HRGN hRgnTemp = NULL;
	COLORREF cr;
	//循环检测位图，将非透明点增加到最终区域。
	for(int x=0; x<bmp.bmWidth; x++)
	{
		for(int y=0; y<bmp.bmHeight; y++)
		{
			cr = GetPixel(m_hMemDC, x, y);
			if (cr != crTransparent)
			{
				hRgnTemp = CreateRectRgn(x, y, x+1, y+1);
				if (hRgn)
				{
					CombineRgn(hRgn, hRgn, hRgnTemp, RGN_OR);
					DeleteObject(hRgnTemp);
				}
				else
					hRgn = hRgnTemp;
			}
		}
	}
	return hRgn;
}

BOOL CImgPathWnd::PreProcessMsg(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp, LRESULT *pResult)
{
	if (nMsg == WM_NCHITTEST) 
	{
		//在窗体任意位置均返回HTCAPTION，以便窗体可以被鼠标拖动
		*pResult = HTCAPTION;
		return FALSE;
	}
	else
		return TRUE;
}