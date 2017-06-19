// ColorStatusBarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ColorStatusBar.h"
#include "ColorStatusBarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorStatusBarDlg dialog

CColorStatusBarDlg::CColorStatusBarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorStatusBarDlg::IDD, pParent), m_nTimerID(0)
{
	//{{AFX_DATA_INIT(CColorStatusBarDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CColorStatusBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorStatusBarDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CColorStatusBarDlg, CDialog)
	//{{AFX_MSG_MAP(CColorStatusBarDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorStatusBarDlg message handlers

BOOL CColorStatusBarDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//创建状态栏，并新建3个子窗格
	m_status.Create(this);
	UINT nID[] = {ID_SEPARATOR, 100, 101};
	m_status.SetIndicators(nID, 3);
	//移动状态栏到合适的位置
	RECT rect = {0};
	GetClientRect(&rect);
	m_status.MoveWindow(0, rect.bottom - 20, rect.right - 10, 20, TRUE);
	//设置格子的宽度
	int nWidth = 200;
	m_status.SetPaneInfo(0, 0, 0, rect.right - 20 - 280);
	m_status.SetPaneInfo(1, 100, 0, 70);
	m_status.SetPaneInfo(2, 101, 0, 200);
	m_status.SetPaneText(1, _T("就绪"), TRUE);
	//创建，并初始化进度条
	m_status.GetItemRect(2, &rect);
	rect.left += 2;
	rect.top += 2;
	rect.right -= 2;
	rect.bottom -= 2;
	m_progress.Create(m_status.GetSafeHwnd(), &rect, RGB(0, 0, 255), RGB(255, 0, 0));
	m_progress.SetVsible(TRUE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CColorStatusBarDlg::OnPaint() 
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
HCURSOR CColorStatusBarDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CColorStatusBarDlg::OnOK() 
{
	//设置定时器，以定时更新进度
	m_nTimerID = SetTimer(1, 50, NULL);
	m_status.SetPaneText(1, _T("进度更新中.."), TRUE);
}

void CColorStatusBarDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//释放资源
	m_progress.Destroy();	
}

void CColorStatusBarDlg::OnTimer(UINT nIDEvent) 
{
	//更新进度，如果已经绘制完成则取消定时器。
	static i = 0;
	i ++;
	if(!m_progress.SetRange(i))
	{
		KillTimer(m_nTimerID);
		m_status.SetPaneText(1, _T("就绪"), TRUE);
		i = 0;
	}
	CDialog::OnTimer(nIDEvent);
}

void CColorStatusBarDlg::OnBtnReset() 
{
	//复位进度条
	m_progress.SetRange(0);	
}
