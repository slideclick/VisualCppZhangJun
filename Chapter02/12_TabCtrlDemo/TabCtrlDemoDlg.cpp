// TabCtrlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TabCtrlDemo.h"
#include "TabCtrlDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlDemoDlg dialog

CTabCtrlDemoDlg::CTabCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTabCtrlDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabCtrlDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTabCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabCtrlDemoDlg)
	DDX_Control(pDX, IDC_TAB, m_tab);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTabCtrlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CTabCtrlDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlDemoDlg message handlers

BOOL CTabCtrlDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//在属性页控件中添加2项
	m_tab.InsertItem(0, _T("第一页"));
	m_tab.InsertItem(1, _T("第二页"));
	//创建子对话框
	m_page1.Create(MAKEINTRESOURCE(IDD_PAGE1), &m_tab);
	m_page2.Create(MAKEINTRESOURCE(IDD_PAGE2), &m_tab);
	//计算对话框的显示位置和大小
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 30;
	rc.left += 8;
	rc.right -= 8;
	rc.bottom -= 8;
	//移动对话框
	m_page1.MoveWindow(rc);
	m_page2.MoveWindow(rc);
	//默认显示第一个页，即第一个对话框
	m_page1.ShowWindow(SW_SHOW);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTabCtrlDemoDlg::OnPaint() 
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
HCURSOR CTabCtrlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//属性页当前所选发生了变化
void CTabCtrlDemoDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//根据当前页的序号，选择要显示的对话框
	switch(m_tab.GetCurSel()) 
	{
	case 0:
		m_page2.ShowWindow(SW_HIDE);
		m_page1.ShowWindow(SW_SHOW);
		break;
	case 1:
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
	*pResult = 0;
}
