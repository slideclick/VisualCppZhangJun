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
	//����Ѿ����������ء���ֹ�ظ�����
	if (m_hWnd) 
	{
		return m_hWnd;
	}

	m_hInstance = hInst;
	//���㴰��ߴ�
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
	//����в˵������ز˵�������Ϊ����˵�
	if(nMenuID > 0)
		m_hMenu = LoadMenu(m_hInstance, MAKEINTRESOURCE(nMenuID));
	//��������Ƿ��Ѿ�ע��
	CheckClass(MY_WND_CLASS_NAME);
	//��������
	m_hWnd = CreateWindowEx(dwExStyle, MY_WND_CLASS_NAME, lpText, dwStyle, 
		x, y, nWidth, nHeight, hParent, m_hMenu, m_hInstance, this);
	return m_hWnd;
}

HWND CMyWnd::CreateEx(DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hParent)
{
	//������������غ���
	RECT rc = {x, y, x + nWidth, y + nHeight};
	return CreateEx(NULL, 0, _T("MyWnd"), dwStyle, &rc, hParent, 0);
}

void CMyWnd::Destroy()
{
	//���ٴ���
	if(m_hWnd)
	{
		DestroyWindow(m_hWnd);
		m_hWnd = NULL;
	}
}

BOOL CMyWnd::Show(int nCmd)
{
	//��ʾ�����ش���
	return ShowWindow(m_hWnd, nCmd);
}

HWND CMyWnd::GetHwnd()
{
	//���ش�����
	return m_hWnd;
}

CMyWnd::operator HWND() const
{
	return m_hWnd;
}

BOOL CMyWnd::PreProcessMsg(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp, LRESULT *pResult)
{
	//������Ϣ����ǰ������ô˺�����
	//����TRUE�����������Ӧ��Ϣ��Ӧ���������������ٴ���
	//��Ϣ����ֵ��pResult�з���
	return TRUE;
}

LRESULT CMyWnd::OnCreate(HWND hWnd)
{
	//WM_CREATE��Ϣ����Ӧ����
	return 0;
}

BOOL CMyWnd::OnDestroy()
{
	//WM_DESTROY��Ϣ����Ӧ����
	return TRUE;
}

BOOL CMyWnd::OnCommand(int nCmdID)
{
	//WM_COMMAND��Ϣ����Ӧ����
	return TRUE;
}

BOOL CMyWnd::OnPaint()
{
	//WM_POINT��Ϣ����Ӧ����
	return TRUE;
}

BOOL CMyWnd::OnEraseBk(HDC hDC)
{
	//WM_ERASEBKGRD��Ϣ����Ӧ����
	return TRUE;
}

BOOL CMyWnd::OnTimer(int nID)
{
	//WM_TIMER��Ϣ����Ӧ����
	return TRUE;
}

BOOL CMyWnd::CheckClass(LPCTSTR lpClassName)
{
	//������������û��ע�ᣬע���ࡣ
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
	//��Ϣ����Լ����
	//1�������ദ����ĳ����Ϣ�������������ٵ��û��ദ�����û�����ζ��Ĭ�ϴ���
	//2����Ϣ������������Ϣ�⣬����TRUE����Ҫ����Ĭ�ϴ������򲻵���Ĭ�ϴ���

	LRESULT lResult = 0;
	BOOL bCallDefault = TRUE;
	//ȡ���;�����Ӧ����
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
	//������Ϣ
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
	//������Ϣ������������Ĭ�ϴ�����̣�����ֱ�ӷ��ء�
	if(bCallDefault)
		return DefWindowProc(hWnd, nMsg, wp, lp);
	else
		return lResult;
}