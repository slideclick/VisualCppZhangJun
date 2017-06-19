// IPCtrlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IPCtrlDemo.h"
#include "IPCtrlDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIPCtrlDemoDlg dialog

CIPCtrlDemoDlg::CIPCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPCtrlDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIPCtrlDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIPCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPCtrlDemoDlg)
	DDX_Control(pDX, IDC_IP, m_ip);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIPCtrlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CIPCtrlDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPCtrlDemoDlg message handlers

BOOL CIPCtrlDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_ip.SetAddress(192, 168, 0, 1);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIPCtrlDemoDlg::OnPaint() 
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
HCURSOR CIPCtrlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//“发送消息”按钮的响应函数
void CIPCtrlDemoDlg::OnBtnSend() 
{
	//取得输入的文本
	CString strMsg;
	GetDlgItemText(IDC_EDT_MSG, strMsg);
	//取得输入的IP地址
	BYTE nField0, nField1, nField2, nField3;
	m_ip.GetAddress(nField0, nField1, nField2, nField3);
	//生成命令参数
	CString strCmd;
	strCmd.Format(_T("send %d.%d.%d.%d %s"), nField0, nField1, nField2, nField3, strMsg);
	//执行命令
	ShellExecute(NULL, _T("open"), _T("net"), strCmd, NULL, SW_HIDE);
}
