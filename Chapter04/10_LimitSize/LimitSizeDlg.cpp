// LimitSizeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LimitSize.h"
#include "LimitSizeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLimitSizeDlg dialog

CLimitSizeDlg::CLimitSizeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLimitSizeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLimitSizeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLimitSizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLimitSizeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLimitSizeDlg, CDialog)
	//{{AFX_MSG_MAP(CLimitSizeDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLimitSizeDlg message handlers

BOOL CLimitSizeDlg::OnInitDialog()
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

void CLimitSizeDlg::OnPaint() 
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
HCURSOR CLimitSizeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//WM_GETMINMAXINFO消息的响应函数
void CLimitSizeDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	CButton *pBtn = (CButton *)GetDlgItem(IDC_CHK_LIMIT);
	if(pBtn != NULL && pBtn->GetCheck())
	{
		//设置允许的最小值
		lpMMI->ptMinTrackSize.x = 300;
		lpMMI->ptMinTrackSize.y = 200;
		//设置允许的最大值
		lpMMI->ptMaxTrackSize.x = 600;
		lpMMI->ptMaxTrackSize.y = 400;
	}
	else
	{
		//控件没有选中使，不限制窗口大小
		CDialog::OnGetMinMaxInfo(lpMMI);
	}
}
