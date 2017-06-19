// StatusBarDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StatusBarDemo.h"
#include "StatusBarDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusBarDemoDlg dialog

CStatusBarDemoDlg::CStatusBarDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatusBarDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatusBarDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStatusBarDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatusBarDemoDlg)
	DDX_Control(pDX, IDC_EDT_INPUT, m_edt_input);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStatusBarDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CStatusBarDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDT_INPUT, OnChangeEdtInput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusBarDemoDlg message handlers

BOOL CStatusBarDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	 
	// TODO: Add extra initialization here
	//创建状态栏，并新建2个子窗格
	m_status.Create(this);
	UINT nID[] = {ID_SEPARATOR, 100};
	m_status.SetIndicators(nID, 2);
	//移动状态栏到合适的位置
	RECT rect = {0};
	GetClientRect(&rect);
	m_status.MoveWindow(0, rect.bottom - 20, rect.right - 10, 20, TRUE);
	//将第二个格子的宽度设置为80 
	m_status.SetPaneInfo(0, 0, 0, rect.right - 10 - 80);
	m_status.SetPaneInfo(1, 100, 0, 80);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStatusBarDemoDlg::OnPaint() 
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
HCURSOR CStatusBarDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CStatusBarDemoDlg::OnChangeEdtInput() 
{
	//获取文本长度，并显示到状态栏
	int nLen = m_edt_input.GetWindowTextLength();
	CString str;
	str.Format(_T("字节：%d"), nLen);
	m_status.SetPaneText(1, str, TRUE);
}
