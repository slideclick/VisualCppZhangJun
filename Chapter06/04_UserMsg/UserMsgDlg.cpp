// UserMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UserMsg.h"
#include "UserMsgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//直接定义的自定义消息ID
#define WM_MY_DEFINED_MSG (WM_USER + 101)
//注册新消息所用的字符串
#define MY_REGISTERED_MSG_STR _T("MY_MSG_STRING")
//存储新消息ID的变量
UINT WM_MY_REGISTERED_MSG;

/////////////////////////////////////////////////////////////////////////////
// CUserMsgDlg dialog

CUserMsgDlg::CUserMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserMsgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserMsgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	WM_MY_REGISTERED_MSG = RegisterWindowMessage(MY_REGISTERED_MSG_STR);
}

void CUserMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserMsgDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUserMsgDlg, CDialog)
	//{{AFX_MSG_MAP(CUserMsgDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_MYMSG, OnBtnMymsg)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MY_DEFINED_MSG, OnMyDefinedMsg)	
	ON_REGISTERED_MESSAGE(WM_MY_REGISTERED_MSG, OnMyRegisteredMsg)	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserMsgDlg message handlers

BOOL CUserMsgDlg::OnInitDialog()
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

void CUserMsgDlg::OnPaint() 
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
HCURSOR CUserMsgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUserMsgDlg::OnOK() 
{
	//投递新注册的自定义消息
	PostMessage(WM_MY_REGISTERED_MSG, 0, 0);
}

void CUserMsgDlg::OnBtnMymsg() 
{	
	//投递直接定义的自定义消息
	PostMessage(WM_MY_DEFINED_MSG, 0, 0);
}

void CUserMsgDlg::OnMyRegisteredMsg()
{
	//WM_MY_REGISTERED_MSG消息的响应函数
	TCHAR szBuf[128] = {0};
	_stprintf(szBuf, _T("收到了用RegisterWindowsMessage注册的消息：WM_MY_REGISTERED_MSG，ID=0x%X。"), WM_MY_REGISTERED_MSG);
	SetDlgItemText(IDC_OUTPUT, szBuf);
}

void CUserMsgDlg::OnMyDefinedMsg()
{
	//WM_MY_DEFINED_MSG消息的响应函数
	TCHAR szBuf[128] = {0};
	_stprintf(szBuf, _T("收到了自定义消息：WM_MY_DEFINED_MSG，ID=0x%X。"), WM_MY_DEFINED_MSG);	
	SetDlgItemText(IDC_OUTPUT, szBuf);
}
