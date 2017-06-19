// MouseMovingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MouseMoving.h"
#include "MouseMovingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMouseMovingDlg dialog

CMouseMovingDlg::CMouseMovingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMouseMovingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMouseMovingDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//初始化成员变量
	m_ptMouse.x = m_ptMouse.y = 0;
	m_bMoving = FALSE;
}

void CMouseMovingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMouseMovingDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMouseMovingDlg, CDialog)
	//{{AFX_MSG_MAP(CMouseMovingDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMouseMovingDlg message handlers

BOOL CMouseMovingDlg::OnInitDialog()
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

void CMouseMovingDlg::OnPaint() 
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
HCURSOR CMouseMovingDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMouseMovingDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//鼠标左键按下，开始移动
	m_bMoving = TRUE;
	//捕获鼠标
	SetCapture();
	//保存当前鼠标位置
	m_ptMouse = point;
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CMouseMovingDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//鼠标左键松开，结束移动
	if(m_bMoving)
	{
		m_bMoving = FALSE;
		ReleaseCapture();
	}
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CMouseMovingDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	//鼠标移动，如果鼠标在按下状态，移动窗体
	if(m_bMoving)
	{
		//获得当前鼠标位置和起始位置之间的偏移
		int x, y;
		x = point.x - m_ptMouse.x;
		y = point.y - m_ptMouse.y;
		//为减少闪烁，每2像素移动窗体一次
		if(abs(x) >= 2 || abs(y) >= 2)
		{
			//获取窗体当前位置
			RECT rc = {0};
			GetWindowRect(&rc);
			//计算新位置
			OffsetRect(&rc, x, y);
			//移动窗体到新位置
			MoveWindow(&rc, TRUE);
		}
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CMouseMovingDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);
	//窗体失去焦点，应结束移动
	if(nState == WA_INACTIVE && m_bMoving)
	{
		m_bMoving = FALSE;
		ReleaseCapture();
	}
}
