// SysKeyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SysKey.h"
#include "SysKeyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSysKeyDlg dialog

CSysKeyDlg::CSysKeyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysKeyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSysKeyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSysKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysKeyDlg)
	DDX_Control(pDX, IDC_CMB_VKEY, m_cmb_VKey);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSysKeyDlg, CDialog)
	//{{AFX_MSG_MAP(CSysKeyDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_CMB_VKEY, OnSelchangeCmbVkey)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysKeyDlg message handlers

BOOL CSysKeyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	int nIndex;
	//默认选项
	nIndex = m_cmb_VKey.AddString(_T("请选择"));
	m_cmb_VKey.SetItemData(nIndex, 0);
	//左Shift键
	nIndex = m_cmb_VKey.AddString(_T("左Shift键"));
	m_cmb_VKey.SetItemData(nIndex, VK_LSHIFT);
	//右Shift键
	nIndex = m_cmb_VKey.AddString(_T("右Shift键"));
	m_cmb_VKey.SetItemData(nIndex, VK_RSHIFT);
	//左Ctrl键
	nIndex = m_cmb_VKey.AddString(_T("左Ctrl键"));
	m_cmb_VKey.SetItemData(nIndex, VK_LCONTROL);
	//右Ctrl键
	nIndex = m_cmb_VKey.AddString(_T("右Ctrl键"));
	m_cmb_VKey.SetItemData(nIndex, VK_RCONTROL);
	//左Alt键
	nIndex = m_cmb_VKey.AddString(_T("左Alt键"));
	m_cmb_VKey.SetItemData(nIndex, VK_LMENU);
	//右Alt键
	nIndex = m_cmb_VKey.AddString(_T("右Alt键"));
	m_cmb_VKey.SetItemData(nIndex, VK_RMENU);
	//Tab键
	nIndex = m_cmb_VKey.AddString(_T("Tab键"));
	m_cmb_VKey.SetItemData(nIndex, VK_TAB);
	//左Win键
	nIndex = m_cmb_VKey.AddString(_T("左Win键"));
	m_cmb_VKey.SetItemData(nIndex, VK_LWIN);
	//右Win键
	nIndex = m_cmb_VKey.AddString(_T("右Win键"));
	m_cmb_VKey.SetItemData(nIndex, VK_RWIN);
	//设置默认选项
	m_cmb_VKey.SetCurSel(0);
	//加载DLL
	m_hHookDll = LoadLibrary(_T("KBHookDll.dll"));
	m_proc = (SetVKeyProc)GetProcAddress(m_hHookDll, _T("SetVKey"));
	ASSERT(m_hHookDll && m_proc);
	if(m_proc == NULL || m_hHookDll == NULL)
		AfxMessageBox(_T("加载键盘HOOK失败！"));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSysKeyDlg::OnPaint() 
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
HCURSOR CSysKeyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//所选按键更改的事件
void CSysKeyDlg::OnSelchangeCmbVkey() 
{
	if(m_proc) 
	{
		//获取当前所选
		int nIndex = m_cmb_VKey.GetCurSel();
		//获取虚拟键码
		DWORD dwData = m_cmb_VKey.GetItemData(nIndex);
		//设置到DLL
		m_proc(dwData);
	}
}

void CSysKeyDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//释放DLL
	FreeLibrary(m_hHookDll);
}
