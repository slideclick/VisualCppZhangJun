// MsgSrcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MsgSrc.h"
#include "MsgSrcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//注册自定义消息
#define MY_COUNTER_MSG _T("My_Counter_Msg_Name")
UINT WM_USER_COUNTER = RegisterWindowMessage(MY_COUNTER_MSG);

/////////////////////////////////////////////////////////////////////////////
// CMsgSrcDlg dialog

CMsgSrcDlg::CMsgSrcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMsgSrcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMsgSrcDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMsgSrcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgSrcDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMsgSrcDlg, CDialog)
	//{{AFX_MSG_MAP(CMsgSrcDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(WM_USER_COUNTER, OnUserCounter)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgSrcDlg message handlers

BOOL CMsgSrcDlg::OnInitDialog()
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

void CMsgSrcDlg::OnPaint() 
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
HCURSOR CMsgSrcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMsgSrcDlg::OnOK() 
{
	//取得输入的数字
	UINT nAddend = GetDlgItemInt(IDC_EDT_ADDEND, NULL, FALSE);
	UINT nSummand = GetDlgItemInt(IDC_EDT_SUMMAND, NULL, FALSE);
	//找到目标窗体
	CWnd *pWnd = FindWindow(NULL, _T("进程计算器"));
	if(pWnd)
	{
		//初始化数据块
		UINT nCopy[2] = {nAddend, nSummand};
		COPYDATASTRUCT cs = {0};
		cs.cbData = sizeof(cs);
		cs.dwData = sizeof(nCopy);
		cs.lpData = nCopy;
		//发送消息，进行计算
		pWnd->SendMessage(WM_COPYDATA, (WPARAM)m_hWnd, (LPARAM)&cs);
	}
	else
		AfxMessageBox(_T("‘进程计算器’没有启动！"));
}

void CMsgSrcDlg::OnUserCounter(WPARAM wp, LPARAM lp)
{
	//自定义消息，在此显示结果
	SetDlgItemInt(IDC_EDT_SUM, wp, FALSE);
}
