#include "StdAfx.h"
#include ".\pictureex.h"
#include <windows.h>
#include <tchar.h>

/*	--ʹ�ô����������� gdi+ ------

(1) ��stdafx.h
	#ifndef ULONG_PTR
	#define ULONG_PTR unsigned long*
	#include "GdiPlus.h"
	using namespace Gdiplus;
	#pragma comment(lib, "gdiplus.lib")
	#endif

(2) ��Ӧ�ó�����ĵ�ͷ�ļ���(*App.h)�������³�Ա������
	GdiplusStartupInput		m_gdiplusStartupInput;
	ULONG_PTR               m_gdiplusToken;

(3) ��InitInstance�����м����ʼ��GDI+�ĺ�����
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);

(4) ��ExitInstance�����м���ر�GDI+�ĺ���
	GdiplusShutdown(m_gdiplusToken);
*/

//�궨��
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
// ��Ϳؼ���
BOOL CPictureEx::Attach(HWND hWnd)
{
	if(hWnd == NULL || m_hWnd != NULL)
	{
		DebugBreak();
		return FALSE;
	}
	m_hWnd = hWnd;
	//������ָ�뱣�浽����������
	SetProp(hWnd, WND_PROP_NAME, this);
	GetClientRect(hWnd, &m_rcClient);
	//�滻�������
	m_pOldProc = (WNDPROC)SetWindowLong(hWnd, GWL_WNDPROC, (LONG)NewWndProc);
	return TRUE;
}
// ���Ѿ��󶨵Ŀؼ�����
HWND CPictureEx::Detach(void)
{
	HWND hWnd = m_hWnd;
	if(m_hWnd != NULL) //�Ѿ���
	{
		//�Ƴ���������
		RemoveProp(hWnd, WND_PROP_NAME);
		//�ָ��������
		SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)m_pOldProc);
		m_hWnd = NULL;
		//�ͷ�gdi��Դ
		FreeImage();											
	}
	return hWnd;
}

// ��ȡ�Ѱ󶨿ؼ���windows���
HWND CPictureEx::GetSafeHwnd(void)
{
	return this == NULL ? NULL:m_hWnd;
}

// ���ļ�����ͼƬ
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
//����Դ����ͼƬ
BOOL CPictureEx::LoadImage(HINSTANCE hInst, LPCTSTR lpResType, LPCTSTR lpResName)
{	
	HRSRC hResInfo = FindResource(hInst , lpResName, lpResType);
	if (hResInfo == NULL) 
		return FALSE;
	//������Դ
	HGLOBAL hRes = LoadResource(hInst , hResInfo);
	if (hRes == NULL) 
		return FALSE;
	//�ͷ�֮ǰ��ͼƬ
	FreeImage();
	BOOL bRet = TRUE;
	//��������ȡ��Դ
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
			//����һ����
			if(S_OK == CreateStreamOnHGlobal(hGlobal, TRUE, &m_pResImg))
			{
				//��������ͼƬ����
				m_pImg = Gdiplus::Image::FromStream(m_pResImg, TRUE);
				bRet = (m_pImg->GetLastStatus() == Gdiplus::Ok);
			}
			else
				bRet = FALSE;
		}
		else
			bRet = FALSE;
		//�ͷ���Դ
		UnlockResource(hRes);  
		FreeResource(hRes);
	}
	if(bRet)
		bRet = InitImage();
	return bRet;
}
// ����ͼƬ����ģʽ
void CPictureEx::SetImageMode(ImageMode nHMode, ImageMode nVMode)
{
	m_nHMode = nHMode;
	m_nVMode = nVMode;
	Invalidata();
}
// ���ÿؼ��ı���ɫ
void CPictureEx::SetBgColor(COLORREF crBg)
{
	m_crBg = crBg;
	Invalidata();
}
// �ؼ�����proc
LRESULT CPictureEx::NewWndProc(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp)
{
	//ͨ���������Ի�ȡ��Ӧ����
	CPictureEx *pPic = (CPictureEx *)GetProp(hWnd, WND_PROP_NAME);
	if(pPic == NULL)
		return DefWindowProc(hWnd, nMsg, wp, lp);
	//��Ϣ����
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
// ��ָ��dc�ϻ���ͼƬ�ĵ�ǰ֡
void CPictureEx::DrawImage(HDC hDC)
{
	int w,h;
	w = m_pImg->GetWidth();
	h = m_pImg->GetHeight();
	//ˮƽ��ֱ������һ��Ϊƽ��ʱ������ͼƬ��ƽ��ģʽ����
	if(m_nHMode == Tile || m_nVMode == Tile)
	{
		//������ʱλͼ��DC
		HBITMAP hTempBmp = CreateCompatibleBitmap(hDC, w, h);
		HDC hTempDC = CreateCompatibleDC(hDC);
		//����ͼƬ����ʱλͼ
		HBITMAP hOldBmp = (HBITMAP)SelectObject(hTempDC, hTempBmp);
		{
			Gdiplus::Graphics g(hTempDC);
			g.DrawImage(m_pImg, 0, 0);
		}
		//�ͷ���ʱDC
		SelectObject(hTempDC, hOldBmp);
		DeleteDC(hTempDC);
		//ͨ����ʱλͼ����һ����ˢ
		HBRUSH hb = CreatePatternBrush(hTempBmp);
		//�øû�ˢ���Ŀ��DC
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hb);
		FillRect(hDC, &m_rcClient, hb);
		//�ͷ���ʱ��Դ
		SelectObject(hDC, hOldBrush);
		DeleteObject(hb);
		DeleteObject(hTempBmp);
		return;
	}
	//��ƽ��ģʽ������ָ��ģʽ����
	Gdiplus::RectF rf;
	//ȷ��ˮƽ��Χ
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
	//ȷ����ֱ��Χ
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
	//���Ʊ���
	//�ڴ�dc��̬�������ɽ�Լ�ڴ浫���ٻ���ʱЧ�ʵ���
	HDC hMemDC = CreateCompatibleDC(hDC);
	HBITMAP hMemBmp = CreateCompatibleBitmap(hDC, m_rcClient.right, m_rcClient.bottom);
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hMemDC, hMemBmp);
	//��䱳��
	HBRUSH hb = CreateSolidBrush(m_crBg);
	FillRect(hMemDC, &m_rcClient, hb);
	DeleteObject(hb);
	//����ͼƬ
	{
		Gdiplus::Graphics g(hMemDC);
		Gdiplus::Status s = g.DrawImage(m_pImg, rf, 0, 0, m_pImg->GetWidth(), m_pImg->GetHeight(), Gdiplus::UnitPixel);
	}
	//�ڴ�DC����ʵDC
	BOOL bret = BitBlt(hDC, 0, 0, m_rcClient.right, m_rcClient.bottom, hMemDC, 0, 0, SRCCOPY);
	//�ͷ��ڴ�DC
	SelectObject(hMemDC, hOldBmp);
	DeleteObject(hMemBmp);
	DeleteDC(hMemDC);
}
// ������һ֡
void CPictureEx::DrawNextFrame(void)
{
	if(m_pImg == NULL || m_hWnd == NULL)
		return;
	//�õ���һ֡�����
	++m_nActiveFrame;
	if(m_nActiveFrame >= m_nFrameCount)
		m_nActiveFrame = 0;
	//����Ϊ�֡
	m_pImg->SelectActiveFrame(&m_pImgDimenIDs[0], m_nActiveFrame);
	//�ÿؼ��ػ�
	Invalidata();
}
//�ؼ���С�ı����Ϣ����
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
//ʹ�ؼ���Ч���ػ�
void CPictureEx::Invalidata()
{
	if(m_hWnd == NULL)
		return;
	InvalidateRect(m_hWnd, NULL, FALSE);
}
// ����ͼƬ�ɹ����һϵ��׼������
BOOL CPictureEx::InitImage()
{
	Invalidata();
	//��ȡ֡��
	UINT nCount = 0;
	nCount = m_pImg->GetFrameDimensionsCount();
	m_pImgDimenIDs=(GUID*)new GUID[nCount];
	m_pImg->GetFrameDimensionsList(m_pImgDimenIDs, nCount);
	//��ʼ��֡����
	m_nActiveFrame = 0;
	m_nFrameCount = m_pImg->GetFrameCount(&m_pImgDimenIDs[0]);
	//����Ƕ�֡ͼƬ��������ʱ��
	if(m_nFrameCount > 1)
	{
		//��ȡ֡��ʱ��Ϣ
		int size = m_pImg->GetPropertyItemSize(PropertyTagFrameDelay);
		m_pImgProp = (PropertyItem *)malloc(size);
		m_pImg->GetPropertyItem(PropertyTagFrameDelay, size, m_pImgProp);
		//���ö�ʱ��
		SetTimer(m_hWnd, 1, 20, NULL);
		m_dwDelay = GetTickCount();
	}
	return TRUE;
}
// �ͷ�gdi��Դ
void CPictureEx::FreeImage(void)
{
	if(m_pImg == NULL)
		return;
	//ȡ����ʱ��
	KillTimer(m_hWnd, 1);
	//�Ƿ�ͼƬ����
	if(m_pImg != NULL)
	{
		Gdiplus::Image *pImg = m_pImg;
		m_pImg = NULL;
		delete pImg ;
	}
	//�ͷ�ͼƬ֡��Ϣ
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
	//�ͷ���Դ����
	if(m_pResImg != NULL)
	{
		m_pResImg->Release();
		m_pResImg = NULL;
	}
}
//��ʱ����Ϣ����
void CPictureEx::OnTimer()
{
	if(m_nFrameCount <= 0)
	{
		DebugBreak();
		return;
	}
	//��ȡ��ǰ֡��ʱ
	DWORD dwFrameDelay = ((DWORD *)m_pImgProp->value)[m_nActiveFrame]*10;
	//����Ŀǰ��ʱ�Ƿ��Ѿ��ﵽ֡��ʱ
	DWORD dwTick = GetTickCount();
	if(dwTick - m_dwDelay >= dwFrameDelay)
	{
		//����Ѿ��ﵽ���������һ֡
		m_dwDelay = dwTick;
		DrawNextFrame();
	}
}