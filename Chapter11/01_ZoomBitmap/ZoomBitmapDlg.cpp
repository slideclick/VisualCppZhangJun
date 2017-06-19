// ZoomBitmapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZoomBitmap.h"
#include "ZoomBitmapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoomBitmapDlg dialog

CZoomBitmapDlg::CZoomBitmapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZoomBitmapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZoomBitmapDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pOldBmp = NULL;
	m_nZoomPercent = 100;
	m_nBltMode = COLORONCOLOR;
}

void CZoomBitmapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZoomBitmapDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CZoomBitmapDlg, CDialog)
	//{{AFX_MSG_MAP(CZoomBitmapDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_COMMAND(IDR_OPEN, OnOpen)
	ON_COMMAND(IDR_ZOOMIN, OnZoomin)
	ON_COMMAND(IDR_ZOOMOUT, OnZoomout)
	ON_COMMAND(IDR_BALCKONWHITE, OnBalckonwhite)
	ON_COMMAND(IDR_WHITEONBLACK, OnWhiteonblack)
	ON_COMMAND(IDR_COLORONCOLOR, OnColoroncolor)
	ON_COMMAND(IDR_HALFTONE, OnHalftone)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoomBitmapDlg message handlers

BOOL CZoomBitmapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CZoomBitmapDlg::OnPaint() 
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
		//如果没有打开图片，默认绘制
		if(m_dc.GetSafeHdc() == NULL)
		{
			CDialog::OnPaint();
		}
		else
		{
			//获取绘制信息
			CPaintDC dc(this);
			CRect rect;
			//用白色填充客户区
			GetClientRect(&rect);			
			::FillRect(dc.GetSafeHdc(), rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
			//获得图片大小
			BITMAP bm;
			m_bmp.GetBitmap(&bm);
			//设置缩放模式
			int nMode = dc.SetStretchBltMode(m_nBltMode);
			//设置文本背景透明
			int nBk = dc.SetBkMode(TRANSPARENT);
			LPCTSTR lpMode;
			switch(m_nBltMode) 
			{
			case BLACKONWHITE:
				lpMode = _T("BlackOnWhite");
				break;
			case WHITEONBLACK:
				lpMode = _T("WhiteOnBlack");
				break;
			case COLORONCOLOR:
				lpMode = _T("ColorOnColor");
				break;
			default:
				lpMode = _T("Halftone");
				break;
			}
			CString str;
			str.Format(_T("%d%%, %s"), m_nZoomPercent, lpMode);
			//缩放复制位图
			dc.StretchBlt(
				0, 0, 
				bm.bmWidth * m_nZoomPercent / 100, 
				bm.bmHeight * m_nZoomPercent / 100, 
				&m_dc, 
				0, 0, bm.bmWidth, bm.bmHeight, 
				SRCCOPY);
			//绘制文本
			rect.top = rect.bottom - 20;
			dc.DrawText(str, rect, DT_LEFT);
			//恢复dc原始模式
			dc.SetStretchBltMode(nMode);
			dc.SetBkMode(nBk);
		}
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CZoomBitmapDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CZoomBitmapDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	FreeObjects();
}

void CZoomBitmapDlg::FreeObjects()
{
	if(m_dc.GetSafeHdc() != NULL)
	{
		m_dc.SelectObject(m_pOldBmp);
		m_dc.DeleteDC();
		m_bmp.DeleteObject();
	}
}
//打开图片文件
void CZoomBitmapDlg::OnOpen() 
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, _T("*.bmp|*.bmp|"), this);
	if(dlg.DoModal() == IDOK)
	{
		HBITMAP hbmp = (HBITMAP)LoadImage(NULL, dlg.GetPathName(), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE|LR_LOADFROMFILE);
		if(hbmp == NULL)
		{
			AfxMessageBox(_T("加载位图错误！"));
			return;
		}
		FreeObjects();

		m_bmp.Attach(hbmp);
		CDC *pDC = GetDC();
		m_dc.CreateCompatibleDC(pDC);
		ReleaseDC(pDC);
		m_pOldBmp = m_dc.SelectObject(&m_bmp);
		Invalidate(FALSE);
	}	
}
//放大显示
void CZoomBitmapDlg::OnZoomin() 
{
	m_nZoomPercent += 10;
	Invalidate(FALSE);
}
//缩小
void CZoomBitmapDlg::OnZoomout() 
{
	if(m_nZoomPercent > 10)
	{
		m_nZoomPercent -= 10;
		Invalidate(FALSE);
	}
}
//设置图片缩放模式为BLACKONWHITE
void CZoomBitmapDlg::OnBalckonwhite() 
{
	m_nBltMode = BLACKONWHITE;
	Invalidate(FALSE);
}
//设置图片缩放模式为WHITEONBLACK
void CZoomBitmapDlg::OnWhiteonblack() 
{
	m_nBltMode = WHITEONBLACK;
	Invalidate(FALSE);
}
//设置图片缩放模式为COLORONCOLOR
void CZoomBitmapDlg::OnColoroncolor() 
{
	m_nBltMode = COLORONCOLOR;
	Invalidate(FALSE);
}
//设置图片缩放模式为HALFTONE
void CZoomBitmapDlg::OnHalftone() 
{
	m_nBltMode = HALFTONE;
	Invalidate(FALSE);
}

void CZoomBitmapDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	Invalidate(FALSE);
}
