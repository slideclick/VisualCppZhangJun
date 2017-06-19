// AppSnapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AppSnap.h"
#include "AppSnapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//全局的HOOK回调声明
LRESULT CALLBACK HookProc (int nCode, WPARAM wParam, LPARAM lParam);
//全局变量
HHOOK	g_hHook;		//HOOK句柄
BOOL	g_bSelect;		//是否处于选择状态
POINT	g_ptLeftTop;	//选取的起点
POINT	g_ptRightBottom;//选取的终点
HWND	g_hWnd;			//当前对话框句柄
HBITMAP g_hBmp;			//预览用的位图句柄

/////////////////////////////////////////////////////////////////////////////
// CAppSnapDlg dialog

CAppSnapDlg::CAppSnapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAppSnapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAppSnapDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAppSnapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppSnapDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAppSnapDlg, CDialog)
	//{{AFX_MSG_MAP(CAppSnapDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppSnapDlg message handlers

BOOL CAppSnapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	//变量初始化
	g_hWnd = m_hWnd;
	g_hBmp = NULL;
	g_bSelect = FALSE;
	g_ptLeftTop.x = g_ptLeftTop.y = 0;
	g_ptRightBottom.x = g_ptRightBottom.y = 0;
	//安装鼠标钩子
	g_hHook = SetWindowsHookEx(WH_MOUSE, HookProc, NULL, GetCurrentThreadId());
	if(g_hHook == NULL)
	{
		TCHAR szErr[256];
		_stprintf(szErr, _T("安装HOOK时发生错误：0x%.8X!"), GetLastError());
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAppSnapDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAppSnapDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//鼠标钩子的处理函数
LRESULT CALLBACK HookProc (int nCode, WPARAM wParam, LPARAM lParam)
{
	LPMOUSEHOOKSTRUCT pmst = (LPMOUSEHOOKSTRUCT)lParam;
	switch(wParam) 
	{
	case WM_LBUTTONDOWN:
		//左键按下，开始选择
		g_ptLeftTop = pmst->pt;
		ScreenToClient(g_hWnd, &g_ptLeftTop);
		g_bSelect = TRUE;
		break;
	case WM_MOUSEMOVE:
		//鼠标移动，改变选择范围
		if(g_bSelect)
		{
			RECT rt;
			HDC hDC = ::GetDC(g_hWnd);
			//在原有位置再次绘制，消除选择框
			if(g_ptRightBottom.x > 0 && g_ptRightBottom.y > 0)
			{
				SetRect(&rt, g_ptLeftTop.x, g_ptLeftTop.y, g_ptRightBottom.x, g_ptRightBottom.y);
				DrawFocusRect(hDC, &rt);
			}
			//绘制新的选择框
			g_ptRightBottom = pmst->pt;
			ScreenToClient(g_hWnd, &g_ptRightBottom);
			SetRect(&rt, g_ptLeftTop.x, g_ptLeftTop.y, g_ptRightBottom.x, g_ptRightBottom.y);
			DrawFocusRect(hDC, &rt);
			::ReleaseDC(g_hWnd, hDC);
		}
		break;
	case WM_LBUTTONUP:
		//左键松开
		if(g_bSelect)
		{
			if(g_ptRightBottom.x > 0 && g_ptRightBottom.y > 0 
				&& g_ptLeftTop.x != g_ptRightBottom.x 
				&& g_ptLeftTop.y != g_ptRightBottom.y)
			{
				RECT rt;
				HDC hDC = ::GetDC(g_hWnd);
				//消除选择框
				SetRect(&rt, g_ptLeftTop.x, g_ptLeftTop.y, g_ptRightBottom.x, g_ptRightBottom.y);
				DrawFocusRect(hDC, &rt);
				if(g_hBmp)
				{
					DeleteObject(g_hBmp);	
					g_hBmp = NULL;
				}
				//复制所选图像到内存位图
				g_hBmp = CreateCompatibleBitmap(hDC, rt.right - rt.left, rt.bottom - rt.top);
				HDC hPreviewDC = CreateCompatibleDC(hDC);
				HBITMAP hOld = (HBITMAP)SelectObject(hPreviewDC, g_hBmp);
				BitBlt(hPreviewDC, 0, 0, rt.right - rt.left, rt.bottom - rt.top, hDC, rt.left, rt.top, SRCCOPY);
				SelectObject(hPreviewDC, hOld);
				DeleteDC(hPreviewDC);
				//预览位图
				HWND hPreviewWnd = GetDlgItem(g_hWnd, IDC_PREVIEW);
				CStatic wndPreview ;
				wndPreview.Attach(hPreviewWnd);
				wndPreview.SetBitmap(g_hBmp);
				wndPreview.Detach();
				::ReleaseDC(g_hWnd, hDC);
				MessageBeep(MB_ICONASTERISK);			
			}
			g_ptRightBottom.x = g_ptRightBottom.y = 0;
			g_bSelect = FALSE;
		}
		break;
	default:
		break;
	}
	//传递给下一个钩子
	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

void CAppSnapDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//是否资源
	if(g_hBmp)
	{
		DeleteObject(g_hBmp);	
		g_hBmp = NULL;
	}
	//卸载钩子
	UnhookWindowsHookEx(g_hHook);	
}
