// ToolTipDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ToolTipDemo.h"
#include "ToolTipDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolTipDemoDlg dialog

CToolTipDemoDlg::CToolTipDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CToolTipDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CToolTipDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CToolTipDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolTipDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CToolTipDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CToolTipDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTipDemoDlg message handlers

BOOL CToolTipDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//建立ToolTip
	m_tooltip.Create(this, 0);
	//为按钮添加提示
	m_tooltip.AddTool(GetDlgItem(IDOK), _T(""));
	m_tooltip.AddTool(GetDlgItem(IDCANCEL), _T("这里是Cancel按钮，单击将关闭对话框。"));
	//初始化状态
	m_bTooltipActived = FALSE;
	OnOK();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CToolTipDemoDlg::OnPaint() 
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
HCURSOR CToolTipDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CToolTipDemoDlg::PreTranslateMessage(MSG* pMsg) 
{
	//向ToolTip控件传送鼠标消息
	if(m_tooltip.GetSafeHwnd()!=NULL)  
		m_tooltip.RelayEvent(pMsg);  	
	return CDialog::PreTranslateMessage(pMsg);
}

void CToolTipDemoDlg::OnOK() 
{
	//如果ToolTip已经禁用，则开启，否则禁用。
	if(m_bTooltipActived)
	{
		m_tooltip.Activate(FALSE);
		GetDlgItem(IDOK)->SetWindowText(_T("启动ToolTip"));
	}
	else
	{
		m_tooltip.Activate(TRUE);
		m_tooltip.UpdateTipText(_T("这里是OK按钮，单击将禁用ToolTip。"), GetDlgItem(IDOK));
		GetDlgItem(IDOK)->SetWindowText(_T("禁用ToolTip"));
	}
	m_bTooltipActived = (!m_bTooltipActived);
}
