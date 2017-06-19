// EllipticalWindowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EllipticalWindow.h"
#include "EllipticalWindowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEllipticalWindowDlg dialog

CEllipticalWindowDlg::CEllipticalWindowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEllipticalWindowDlg::IDD, pParent), m_hRgn(NULL)
{
	//{{AFX_DATA_INIT(CEllipticalWindowDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEllipticalWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEllipticalWindowDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEllipticalWindowDlg, CDialog)
	//{{AFX_MSG_MAP(CEllipticalWindowDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEllipticalWindowDlg message handlers

BOOL CEllipticalWindowDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//得到窗体客户区范围
	RECT rect = {0};
	GetClientRect(&rect);
	//用窗体客户区矩形尺寸创建一个椭圆区域
	m_hRgn = CreateEllipticRgn(rect.left, rect.top, rect.right, rect.bottom);
	//将椭圆区域设置到窗体
	SetWindowRgn(m_hRgn, TRUE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEllipticalWindowDlg::OnPaint() 
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
HCURSOR CEllipticalWindowDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEllipticalWindowDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if(m_hRgn)	
	{
		DeleteObject(m_hRgn);
		m_hRgn = NULL;
	}
}

void CEllipticalWindowDlg::OnOK() 
{
	//取消椭圆效果
	SetWindowRgn(NULL, TRUE);	
}
