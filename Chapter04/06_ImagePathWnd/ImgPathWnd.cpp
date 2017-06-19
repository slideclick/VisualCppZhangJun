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
	//����Դ����λͼ
	m_hBmp = LoadBitmap(MyGetInstance(), MAKEINTRESOURCE(IDB_BK));
	//����һ���ڴ����DC
	HDC hDC = GetDC(m_hWnd);
	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(m_hWnd, hDC);
	//���ڴ�DC��λͼ����
	HBITMAP m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBmp);
	//����λͼ�����������
	m_hRgn = CreateRgn(RGB(255, 0, 255));
	//���������õ�����
	SetWindowRgn(m_hWnd, m_hRgn, TRUE);
	return 0;
}

BOOL CImgPathWnd::OnDestroy()
{
	//�ͷ��������
	if(m_hRgn)
	{
		DeleteObject(m_hRgn);
		m_hRgn = NULL;
	}
	//�ͷ�λͼ��ض���
	if (m_hMemDC)
	{
		SelectObject(m_hMemDC, m_hOldBmp);
		DeleteDC(m_hMemDC);
		m_hMemDC = NULL;
		m_hBmp = m_hOldBmp = NULL;
		DeleteObject(m_hBmp);
	}
	//Ͷ���˳���Ϣ
	PostQuitMessage(0);
	return TRUE;
}

BOOL CImgPathWnd::OnPaint()
{
	RECT rect = {0};
	GetClientRect(m_hWnd, &rect);
	//��λͼ���Ƶ�����
	PAINTSTRUCT ps = {0};
	BeginPaint(m_hWnd, &ps);
	BitBlt(ps.hdc, 0, 0, rect.right, rect.bottom, m_hMemDC, 0, 0, SRCCOPY);
	EndPaint(m_hWnd, &ps);	
	return FALSE;
}

HRGN CImgPathWnd::CreateRgn(COLORREF crTransparent)
{
	//����λͼ�����������
	BITMAP bmp = {0};
	GetObject(m_hBmp, sizeof(bmp), &bmp);
	//ѭ�����õ�����ʱ����
	HRGN hRgn = NULL;
	HRGN hRgnTemp = NULL;
	COLORREF cr;
	//ѭ�����λͼ������͸�������ӵ���������
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
		//�ڴ�������λ�þ�����HTCAPTION���Ա㴰����Ա�����϶�
		*pResult = HTCAPTION;
		return FALSE;
	}
	else
		return TRUE;
}