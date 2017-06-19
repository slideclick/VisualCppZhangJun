// FlashWndDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FlashWnd.h"
#include "FlashWndDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlashWndDlg dialog

CFlashWndDlg::CFlashWndDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFlashWndDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFlashWndDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFlashWndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlashWndDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFlashWndDlg, CDialog)
	//{{AFX_MSG_MAP(CFlashWndDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlashWndDlg message handlers

BOOL CFlashWndDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//创建控件
	HWND hWnd = ::GetDlgItem(m_hWnd, IDC_FLASH);
	m_flash.Create(hWnd);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFlashWndDlg::OnPaint() 
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
HCURSOR CFlashWndDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//播放
void CFlashWndDlg::OnOK() 
{
	//获取到输入的路径
	CString strPath;
	GetDlgItemText(IDC_EDT_PATH, strPath);
	if(strPath.GetLength() == 0)
	{
		AfxMessageBox(_T("请输入Flash文件路径或URL！"));
		return;
	}
	//将影片加载到控件
	m_flash.LoadMovie(strPath);
}

void CFlashWndDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//销毁控件
	m_flash.Destroy();
}
