// TimerDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TimerDemo.h"
#include "TimerDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//定时器的回调函数
VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT uID, DWORD dwTime)
{
	//在此闪烁绿色指示灯
	HWND hRed = ::GetDlgItem(hWnd, IDC_GREEN);
	int nShow;
	if(::IsWindowVisible(hRed))
		nShow = SW_HIDE;
	else
		nShow = SW_SHOW;
	::ShowWindow(hRed, nShow);
}
/////////////////////////////////////////////////////////////////////////////
// CTimerDemoDlg dialog

CTimerDemoDlg::CTimerDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimerDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimerDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//初始化成员
	m_nRedID = m_nGreenID = 0;
}

void CTimerDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimerDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTimerDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CTimerDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_RED, OnBtnRed)
	ON_BN_CLICKED(IDC_BTN_GREEN, OnBtnGreen)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimerDemoDlg message handlers

BOOL CTimerDemoDlg::OnInitDialog()
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

void CTimerDemoDlg::OnPaint() 
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
HCURSOR CTimerDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//设置红色指示灯的状态
void CTimerDemoDlg::OnBtnRed() 
{
	if(m_nRedID == 0)
	{
		//如果尚未申请，则申请以消息通知的定时器
		m_nRedID = SetTimer(1, 500, NULL);
	}
	else
	{
		//如果定时器正在运行，则取消定时器
		KillTimer(m_nRedID);
		m_nRedID = 0;
		::ShowWindow(::GetDlgItem(m_hWnd, IDC_RED), SW_HIDE);
	}
}
//设置绿色指示灯的状态
void CTimerDemoDlg::OnBtnGreen() 
{
	if(m_nGreenID == 0)
	{
		//如果尚未申请，则申请调用回调函数的定时器
		m_nGreenID = SetTimer(2, 1000, TimerProc);
	}
	else
	{
		//如果定时器正在运行，则取消定时器
		KillTimer(m_nGreenID);
		m_nGreenID = 0;
		::ShowWindow(::GetDlgItem(m_hWnd, IDC_GREEN), SW_HIDE);
	}
}
//WM_TIMER消息的处理函数
void CTimerDemoDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == m_nRedID)
	{
		//如果是红色指示灯的定时器消息，闪烁指示灯
		HWND hRed = ::GetDlgItem(m_hWnd, IDC_RED);
		int nShow;
		if(::IsWindowVisible(hRed))
			nShow = SW_HIDE;
		else
			nShow = SW_SHOW;
		::ShowWindow(hRed, nShow);
	}
}
