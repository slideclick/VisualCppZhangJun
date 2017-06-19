#include "StdAfx.h"
#include ".\pictureex.h"
#include <windows.h>
#include <tchar.h>

/*	--使用此类请先配置 gdi+ ------

(1) 在stdafx.h
	#ifndef ULONG_PTR
	#define ULONG_PTR unsigned long*
	#include "GdiPlus.h"
	using namespace Gdiplus;
	#pragma comment(lib, "gdiplus.lib")
	#endif

(2) 在应用程序类的的头文件中(*App.h)声明以下成员变量：
	GdiplusStartupInput		m_gdiplusStartupInput;
	ULONG_PTR               m_gdiplusToken;

(3) 在InitInstance函数中加入初始化GDI+的函数：
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);

(4) 在ExitInstance函数中加入关闭GDI+的函数
	GdiplusShutdown(m_gdiplusToken);
*/

//宏定义
#define RectWidth(_rc) (_rc.right-_rc.left)
#define RectHeight(_rc) (_rc.bottom-_rc.top)
#define WND_PROP_NAME _T("PicEx_Prop")

CPictureEx::CPictureEx(void)
: m_pImg(NULL),m_hWnd(NULL),m_nHMode(Center),m_nVMode(Center),m_pOldProc(NULL),m_crBg(RGB(0,0,0))
	,m_pImgDimenIDs(NULL),m_nFrameCount(0),m_nActiveFrame(0),m_pImgProp(NULL),m_pResImg(NULL),
	m_bCreated(FALSE), m_dwDelay(0)
{
	SetRect(&m_rcClient, 0, 0, 0, 0);
}
CPictureEx::~CPictureEx(void)
{
	Detach();
}
// 类和控件绑定
BOOL CPictureEx::Attach(HWND hWnd)
{
	if(hWnd == NULL || m_hWnd != NULL)
	{
		DebugBreak();
		return FALSE;
	}
	m_hWnd = hWnd;
	//将本类指针保存到窗体属性中
	SetProp(hWnd, WND_PROP_NAME, this);
	GetClientRect(hWnd, &m_rcClient);
	//替换窗体过程
	m_pOldProc = (WNDPROC)SetWindowLong(hWnd, GWL_WNDPROC, (LONG)NewWndProc);
	return TRUE;
}
// 和已经绑定的控件分离
HWND CPictureEx::Detach(void)
{
	HWND hWnd = m_hWnd;
	if(m_hWnd != NULL) //已经绑定
	{
		//移除窗体属性
		RemoveProp(hWnd, WND_PROP_NAME);
		//恢复窗体过程
		SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)m_pOldProc);
		m_hWnd = NULL;
		//释放gdi资源
		FreeImage();											
	}
	return hWnd;
}

// 获取已绑定控件的windows句柄
HWND CPictureEx::GetSafeHwnd(void)
{
	return this == NULL ? NULL:m_hWnd;
}

// 从文件加载图片
BOOL CPictureEx::LoadImage(LPCTSTR lpFilename)
{
	FreeImage();
#ifndef UNICODE
	WCHAR szFile[MAX_PATH] = {0};
	MultiByteToWideChar(CP_ACP, 0, lpFilename, -1, szFile, MAX_PATH);
	m_pImg = new Gdiplus::Image(szFile, TRUE);
#else
	m_pImg = new Gdiplus::Image(lpFilename, TRUE);
#endif
	if(m_pImg == NULL)
	{
		return FALSE;
	}
	if(m_pImg->GetLastStatus() == Gdiplus::Ok)
	{
		return InitImage();
	}
	else
	{
		m_pImg = NULL;
		return FALSE;
	}
}
//从资源加载图片
BOOL CPictureEx::LoadImage(HINSTANCE hInst, LPCTSTR lpResType, LPCTSTR lpResName)
{	
	HRSRC hResInfo = FindResource(hInst , lpResName, lpResType);
	if (hResInfo == NULL) 
		return FALSE;
	//加载资源
	HGLOBAL hRes = LoadResource(hInst , hResInfo);
	if (hRes == NULL) 
		return FALSE;
	//释放之前的图片
	FreeImage();
	BOOL bRet = TRUE;
	//锁定并读取资源
	BYTE *pResData = (BYTE *)LockResource(hRes);
	if (pResData != NULL)
	{ 
		DWORD dwSize = SizeofResource(hInst , hResInfo);
		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwSize);
		LPVOID pBuf = GlobalLock(hGlobal);
		if(pBuf != NULL)
		{
			memcpy(pBuf, pResData, dwSize);
			GlobalUnlock(hGlobal);
			//创建一个流
			if(S_OK == CreateStreamOnHGlobal(hGlobal, TRUE, &m_pResImg))
			{
				//从流创建图片对象
				m_pImg = Gdiplus::Image::FromStream(m_pResImg, TRUE);
				bRet = (m_pImg->GetLastStatus() == Gdiplus::Ok);
			}
			else
				bRet = FALSE;
		}
		else
			bRet = FALSE;
		//释放资源
		UnlockResource(hRes);  
		FreeResource(hRes);
	}
	if(bRet)
		bRet = InitImage();
	return bRet;
}
// 设置图片绘制模式
void CPictureEx::SetImageMode(ImageMode nHMode, ImageMode nVMode)
{
	m_nHMode = nHMode;
	m_nVMode = nVMode;
	Invalidata();
}
// 设置控件的背景色
void CPictureEx::SetBgColor(COLORREF crBg)
{
	m_crBg = crBg;
	Invalidata();
}
// 控件的新proc
LRESULT CPictureEx::NewWndProc(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp)
{
	//通过窗体属性获取对应的类
	CPictureEx *pPic = (CPictureEx *)GetProp(hWnd, WND_PROP_NAME);
	if(pPic == NULL)
		return DefWindowProc(hWnd, nMsg, wp, lp);
	//消息处理
	LRESULT lRet = 0;
	switch(nMsg)
	{
	case WM_PAINT:
		if(pPic->m_pImg != NULL)
		{
			PAINTSTRUCT ps = {0};
			HDC hDC = BeginPaint(hWnd, &ps);
			pPic->DrawImage(ps.hdc);
			EndPaint(hWnd, &ps);
		}
		else
		{
			lRet = CallWindowProc(pPic->m_pOldProc, hWnd, nMsg, wp, lp);
		}
		break;
	case WM_SIZE:
		pPic->OnSize(wp, LOWORD(lp), HIWORD(lp));
		break;
	case WM_DESTROY:
		pPic->Detach();
		lRet = CallWindowProc(pPic->m_pOldProc, hWnd, nMsg, wp, lp);
		break;
	case WM_TIMER:
		pPic->OnTimer();
		break;
	default:
		lRet = CallWindowProc(pPic->m_pOldProc, hWnd, nMsg, wp, lp);
		break;
	}
	return lRet;
}
// 在指定dc上绘制图片的当前帧
void CPictureEx::DrawImage(HDC hDC)
{
	int w,h;
	w = m_pImg->GetWidth();
	h = m_pImg->GetHeight();
	//水平或垂直方向，有一个为平铺时，整个图片以平铺模式绘制
	if(m_nHMode == Tile || m_nVMode == Tile)
	{
		//创建临时位图和DC
		HBITMAP hTempBmp = CreateCompatibleBitmap(hDC, w, h);
		HDC hTempDC = CreateCompatibleDC(hDC);
		//绘制图片到临时位图
		HBITMAP hOldBmp = (HBITMAP)SelectObject(hTempDC, hTempBmp);
		{
			Gdiplus::Graphics g(hTempDC);
			g.DrawImage(m_pImg, 0, 0);
		}
		//释放临时DC
		SelectObject(hTempDC, hOldBmp);
		DeleteDC(hTempDC);
		//通过临时位图创建一个画刷
		HBRUSH hb = CreatePatternBrush(hTempBmp);
		//用该画刷填充目标DC
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hb);
		FillRect(hDC, &m_rcClient, hb);
		//释放临时资源
		SelectObject(hDC, hOldBrush);
		DeleteObject(hb);
		DeleteObject(hTempBmp);
		return;
	}
	//非平铺模式，按照指定模式绘制
	Gdiplus::RectF rf;
	//确定水平范围
	int i;
	switch(m_nHMode)
	{
	case Center:
		i = (m_rcClient.right - w) / 2;
		rf.X = i;
		rf.Width = w;
		break;
	case LeftTop:
		rf.X = 0;
		rf.Width = w;
		break;
	case RightBottom:
		rf.X = m_rcClient.right - w;
		rf.Width = w;
		break;
	case Stretch:
	default:
		rf.X = 0;
		rf.Width = m_rcClient.right;
		break;
	}
	//确定垂直范围
	switch(m_nVMode)
	{
	case Center:
		i = (m_rcClient.bottom - h) / 2;
		rf.Y = i;
		rf.Height = h;
		break;
	case LeftTop:
		rf.Y = 0;
		rf.Height = h;
		break;
	case RightBottom:
		rf.Y = m_rcClient.bottom - h;
		rf.Height = h;
		break;
	case Stretch:
	default:
		rf.Y = 0;
		rf.Height = m_rcClient.bottom;
		break;
	}
	//绘制背景
	//内存dc动态创建，可节约内存但快速绘制时效率低下
	HDC hMemDC = CreateCompatibleDC(hDC);
	HBITMAP hMemBmp = CreateCompatibleBitmap(hDC, m_rcClient.right, m_rcClient.bottom);
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hMemDC, hMemBmp);
	//填充背景
	HBRUSH hb = CreateSolidBrush(m_crBg);
	FillRect(hMemDC, &m_rcClient, hb);
	DeleteObject(hb);
	//绘制图片
	{
		Gdiplus::Graphics g(hMemDC);
		Gdiplus::Status s = g.DrawImage(m_pImg, rf, 0, 0, m_pImg->GetWidth(), m_pImg->GetHeight(), Gdiplus::UnitPixel);
	}
	//内存DC到真实DC
	BOOL bret = BitBlt(hDC, 0, 0, m_rcClient.right, m_rcClient.bottom, hMemDC, 0, 0, SRCCOPY);
	//释放内存DC
	SelectObject(hMemDC, hOldBmp);
	DeleteObject(hMemBmp);
	DeleteDC(hMemDC);
}
// 绘制下一帧
void CPictureEx::DrawNextFrame(void)
{
	if(m_pImg == NULL || m_hWnd == NULL)
		return;
	//得到下一帧的序号
	++m_nActiveFrame;
	if(m_nActiveFrame >= m_nFrameCount)
		m_nActiveFrame = 0;
	//设置为活动帧
	m_pImg->SelectActiveFrame(&m_pImgDimenIDs[0], m_nActiveFrame);
	//让控件重绘
	Invalidata();
}
//控件大小改变的消息处理
void CPictureEx::OnSize(UINT nType, int cx, int cy)
{
	switch(nType)
	{
	case SIZE_RESTORED:
	case SIZE_MAXSHOW:
	case SIZE_MAXIMIZED:
		SetRect(&m_rcClient, 0, 0, cx, cy);
		break;
	}
}
//使控件无效而重绘
void CPictureEx::Invalidata()
{
	if(m_hWnd == NULL)
		return;
	InvalidateRect(m_hWnd, NULL, FALSE);
}
// 加载图片成功后的一系列准备工作
BOOL CPictureEx::InitImage()
{
	Invalidata();
	//获取帧数
	UINT nCount = 0;
	nCount = m_pImg->GetFrameDimensionsCount();
	m_pImgDimenIDs=(GUID*)new GUID[nCount];
	m_pImg->GetFrameDimensionsList(m_pImgDimenIDs, nCount);
	//初始化帧变量
	m_nActiveFrame = 0;
	m_nFrameCount = m_pImg->GetFrameCount(&m_pImgDimenIDs[0]);
	//如果是多帧图片，启动定时器
	if(m_nFrameCount > 1)
	{
		//获取帧延时信息
		int size = m_pImg->GetPropertyItemSize(PropertyTagFrameDelay);
		m_pImgProp = (PropertyItem *)malloc(size);
		m_pImg->GetPropertyItem(PropertyTagFrameDelay, size, m_pImgProp);
		//设置定时器
		SetTimer(m_hWnd, 1, 20, NULL);
		m_dwDelay = GetTickCount();
	}
	return TRUE;
}
// 释放gdi资源
void CPictureEx::FreeImage(void)
{
	if(m_pImg == NULL)
		return;
	//取消定时器
	KillTimer(m_hWnd, 1);
	//是否图片对象
	if(m_pImg != NULL)
	{
		Gdiplus::Image *pImg = m_pImg;
		m_pImg = NULL;
		delete pImg ;
	}
	//释放图片帧信息
	if(m_pImgDimenIDs != NULL)
	{
		delete []m_pImgDimenIDs;
		m_pImgDimenIDs = NULL;
	}
	if(m_pImgProp != NULL)
	{
		free(m_pImgProp);
		m_pImgProp = NULL;
	}
	m_nActiveFrame = 0;
	m_nFrameCount = 0;
	//释放资源对象
	if(m_pResImg != NULL)
	{
		m_pResImg->Release();
		m_pResImg = NULL;
	}
}
//定时器消息处理
void CPictureEx::OnTimer()
{
	if(m_nFrameCount <= 0)
	{
		DebugBreak();
		return;
	}
	//获取当前帧延时
	DWORD dwFrameDelay = ((DWORD *)m_pImgProp->value)[m_nActiveFrame]*10;
	//看看目前延时是否已经达到帧延时
	DWORD dwTick = GetTickCount();
	if(dwTick - m_dwDelay >= dwFrameDelay)
	{
		//如果已经达到，则绘制下一帧
		m_dwDelay = dwTick;
		DrawNextFrame();
	}
}