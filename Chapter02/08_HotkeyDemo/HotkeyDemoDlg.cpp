// HotkeyDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HotkeyDemo.h"
#include "HotkeyDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHotkeyDemoDlg dialog

CHotkeyDemoDlg::CHotkeyDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHotkeyDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHotkeyDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHotkeyDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHotkeyDemoDlg)
	DDX_Control(pDX, IDC_HOTKEY, m_hotkey);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHotkeyDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CHotkeyDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_REGISTER, OnBtnRegister)
	//}}AFX_MSG_MAP
	//手动添加的消息映射代码
	ON_MESSAGE(WM_HOTKEY, OnHotkey)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHotkeyDemoDlg message handlers

BOOL CHotkeyDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHotkeyDemoDlg::OnPaint() 
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
HCURSOR CHotkeyDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//“设置”按钮的响应函数
void CHotkeyDemoDlg::OnBtnRegister() 
{
	//取得热键控件的输入
	WORD wVK = 0, wMod = 0;
	m_hotkey.GetHotKey(wVK, wMod);
	//将热键控件返回的控制键转换为标准控制键代码
	int nNewMod = 0;
	if(wMod & HOTKEYF_ALT)
		nNewMod |= MOD_ALT;
	if(wMod & HOTKEYF_CONTROL)
		nNewMod |= MOD_CONTROL;
	if(wMod & HOTKEYF_SHIFT)
		nNewMod |= MOD_SHIFT;
	//如果没有正确的输入，退出函数
	if(wVK == 0 || nNewMod == 0)
	{
		AfxMessageBox(_T("请输入热键！"));
		return;
	}
	//注册热键，如果注册成功，隐藏窗体
	if(RegisterHotKey(m_hWnd, 1, nNewMod, wVK))
		this->ShowWindow(SW_HIDE);
	else
		AfxMessageBox(_T("注册热键失败！"));
}
//WM_HOTKEY消息的响应函数
void CHotkeyDemoDlg::OnHotkey(WPARAM wp, LPARAM lp)
{
	if (wp == 1) 
	{
		//显示窗体
		this->ShowWindow(SW_SHOW);
		//释放热键
		UnregisterHotKey(m_hWnd, 1);
	}
}