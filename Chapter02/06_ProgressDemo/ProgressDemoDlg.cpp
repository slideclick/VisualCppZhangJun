// ProgressDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProgressDemo.h"
#include "ProgressDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressDemoDlg dialog

CProgressDemoDlg::CProgressDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProgressDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressDemoDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProgressDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CProgressDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressDemoDlg message handlers

BOOL CProgressDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//设置进度条控件的范围
	m_progress.SetRange32(0, 100);
	//修改进度条控件的进度条颜色
	::SendMessage(m_progress.GetSafeHwnd(), PBM_SETBARCOLOR, 0, RGB(255, 0, 255));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProgressDemoDlg::OnPaint() 
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
HCURSOR CProgressDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//“开始”按钮的响应函数
void CProgressDemoDlg::OnBtnStart() 
{
	//开启定时器
	SetTimer(1, 100, NULL);
	//禁用“开始”按钮，防止重复按下
	GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
}
//WM_TIMER消息的响应函数
void CProgressDemoDlg::OnTimer(UINT nIDEvent) 
{
	int nMin, nMax, nPos;
	//取得进度条控件的范围
	m_progress.GetRange(nMin, nMax);
	//取得当前进度值
	nPos = m_progress.GetPos();
	//增加进度值
	nPos ++;
	//如果达到上限，结束定时器，恢复控件原状
	if(nPos >= nMax)
	{
		KillTimer(1);
		nPos = 0;
		GetDlgItem(IDC_BTN_START)->EnableWindow();
	}
	//更新进度值
	m_progress.SetPos(nPos);
	CDialog::OnTimer(nIDEvent);
}
