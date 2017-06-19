// MyRealDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyReal.h"
#include "MyRealDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyRealDlg dialog

CMyRealDlg::CMyRealDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyRealDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyRealDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyRealDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyRealDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyRealDlg, CDialog)
	//{{AFX_MSG_MAP(CMyRealDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyRealDlg message handlers

BOOL CMyRealDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//将变量和控件关联
	m_pReal = (CRealAudio *)GetDlgItem(IDC_REALPLAYER);
	//提示，添加如下2行代码，即可让控件显示图片窗口。
	//CString str = _T("IMAGEWINDOW,CONTROLPANEL,STATUSBAR");
    //m_pReal->SetControls(str);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyRealDlg::OnPaint() 
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
HCURSOR CMyRealDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyRealDlg::OnOK() 
{
	//浏览并打开一个文件
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, _T("*.rm|*.rm|*.*|*.*||"), this);
	if(dlg.DoModal() == IDOK)
	{
		//播放文件
		m_pReal->SetSource(dlg.GetPathName());	
	}
}
