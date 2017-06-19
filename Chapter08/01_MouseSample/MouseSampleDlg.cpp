// MouseSampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MouseSample.h"
#include "MouseSampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMouseSampleDlg dialog

CMouseSampleDlg::CMouseSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMouseSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMouseSampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMouseSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMouseSampleDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMouseSampleDlg, CDialog)
	//{{AFX_MSG_MAP(CMouseSampleDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMouseSampleDlg message handlers

BOOL CMouseSampleDlg::OnInitDialog()
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

void CMouseSampleDlg::OnPaint() 
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
HCURSOR CMouseSampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMouseSampleDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	//鼠标左键双击的处理
	ProcessMouseMessage(_T("双击"), _T("左键"), point);
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CMouseSampleDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//鼠标左键按下的处理
	ProcessMouseMessage(_T("按下"), _T("左键"), point);
	CDialog::OnLButtonDown(nFlags, point);
}

void CMouseSampleDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//鼠标左键松开的处理
	ProcessMouseMessage(_T("松开"), _T("左键"), point);
	CDialog::OnLButtonUp(nFlags, point);
}

void CMouseSampleDlg::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	//鼠标右键双击的处理
	ProcessMouseMessage(_T("双击"), _T("右键"), point);
	CDialog::OnRButtonDblClk(nFlags, point);
}

void CMouseSampleDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	//鼠标右键按下的处理
	ProcessMouseMessage(_T("按下"), _T("右键"), point);
	CDialog::OnRButtonDown(nFlags, point);
}

void CMouseSampleDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	//鼠标右键松开的处理
	ProcessMouseMessage(_T("松开"), _T("右键"), point);
	CDialog::OnRButtonUp(nFlags, point);
}

void CMouseSampleDlg::OnMButtonDblClk(UINT nFlags, CPoint point) 
{
	//鼠标中键双击的处理
	ProcessMouseMessage(_T("双击"), _T("中键"), point);
	CDialog::OnMButtonDblClk(nFlags, point);
}

void CMouseSampleDlg::OnMButtonDown(UINT nFlags, CPoint point) 
{
	//鼠标中键按下的处理
	ProcessMouseMessage(_T("按下"), _T("中键"), point);
	CDialog::OnMButtonDown(nFlags, point);
}

void CMouseSampleDlg::OnMButtonUp(UINT nFlags, CPoint point) 
{
	//鼠标中键松开的处理
	ProcessMouseMessage(_T("松开"), _T("中键"), point);
	CDialog::OnMButtonUp(nFlags, point);
}

BOOL CMouseSampleDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	//鼠标滚轮滚动的处理
	if(zDelta < 0)
		ProcessMouseMessage(_T("向下移动"), _T("滚轮"), pt);
	else
		ProcessMouseMessage(_T("向上移动"), _T("滚轮"), pt);
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void CMouseSampleDlg::ProcessMouseMessage(LPCTSTR lpszEvent, LPCTSTR lpszKey, const CPoint &point)
{
	//将消息显示到界面上
	CString strMsg;
	strMsg.Format(_T("%s了鼠标%s，坐标为：%d,%d"), lpszEvent, lpszKey, point.x, point.y);
	SetDlgItemText(IDC_MOUSE_MESSAGE, strMsg);
}
