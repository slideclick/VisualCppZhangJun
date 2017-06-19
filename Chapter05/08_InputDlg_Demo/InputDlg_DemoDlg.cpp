// InputDlg_DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InputDlg_Demo.h"
#include "InputDlg_DemoDlg.h"
#include "..\..\comm\inputdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputDlg_DemoDlg dialog

CInputDlg_DemoDlg::CInputDlg_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputDlg_DemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputDlg_DemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInputDlg_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputDlg_DemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInputDlg_DemoDlg, CDialog)
	//{{AFX_MSG_MAP(CInputDlg_DemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputDlg_DemoDlg message handlers

BOOL CInputDlg_DemoDlg::OnInitDialog()
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

void CInputDlg_DemoDlg::OnPaint() 
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
HCURSOR CInputDlg_DemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CInputDlg_DemoDlg::OnOK() 
{
	//创建输入对话框
	CInputDlg dlg(this, _T("输入"), _T("请输入要显示的内容："));
	//弹出对话框
	dlg.DoModal();
	//取得输入内容
	CString strInput = "输入的内容是：";
	strInput += dlg.GetInputText();
	//显示输入内容
	SetDlgItemText(IDC_INPUT, strInput);
}
