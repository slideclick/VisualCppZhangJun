// LockMouseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LockMouse.h"
#include "LockMouseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLockMouseDlg dialog

CLockMouseDlg::CLockMouseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLockMouseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLockMouseDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//初始化数据成员
	m_bClipping = FALSE;
	SetRect(&m_rcClipOld, 0, 0, 0, 0);
}

void CLockMouseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLockMouseDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLockMouseDlg, CDialog)
	//{{AFX_MSG_MAP(CLockMouseDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLockMouseDlg message handlers

BOOL CLockMouseDlg::OnInitDialog()
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

void CLockMouseDlg::OnPaint() 
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
HCURSOR CLockMouseDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLockMouseDlg::OnOK() 
{
	//如果已经进入限制模式，释放鼠标，否则限制鼠标
	if(!m_bClipping)
	{
		//保存旧的范围
		GetClipCursor(&m_rcClipOld);
		RECT rc = {0};
		//获取本窗体范围
		GetWindowRect(&rc);
		//设置鼠标限制
		m_bClipping = ClipCursor(&rc);
		if(m_bClipping)
			SetDlgItemText(IDOK, _T("释放鼠标"));
	}
	else
	{
		//恢复旧的范围
		if(ClipCursor(&m_rcClipOld))
		{
			m_bClipping = FALSE;
			SetDlgItemText(IDOK, _T("限制鼠标"));
		}
	}
}
