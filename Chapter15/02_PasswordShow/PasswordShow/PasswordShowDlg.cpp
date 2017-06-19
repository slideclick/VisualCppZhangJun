// PasswordShowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PasswordShow.h"
#include "PasswordShowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPasswordShowDlg dialog

CPasswordShowDlg::CPasswordShowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPasswordShowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPasswordShowDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPasswordShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPasswordShowDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPasswordShowDlg, CDialog)
	//{{AFX_MSG_MAP(CPasswordShowDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPasswordShowDlg message handlers

BOOL CPasswordShowDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//加载HOOK回调函数所在DLL文件
	m_hHookDll = LoadLibrary(_T("MouseHookDll.dll"));
	//得到DLL中函数地址
	m_procStart = (StartProc)GetProcAddress(m_hHookDll, _T("StartHook"));
	m_procStop = (StopProc)GetProcAddress(m_hHookDll, _T("StopHook"));
	ASSERT(m_hHookDll && m_procStart && m_procStop);
	//用于输出文本的控件句柄
	HWND hShow = ::GetDlgItem(m_hWnd, IDC_EDT_RESULT);
	//调用DLL中的函数安装HOOK
	DWORD dwRet = m_procStart(hShow);
	ASSERT(dwRet == 0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPasswordShowDlg::OnPaint() 
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
HCURSOR CPasswordShowDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPasswordShowDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//卸载HOOK
	m_procStop();
	//释放HOOK所在的DLL
	FreeLibrary	(m_hHookDll);
}
