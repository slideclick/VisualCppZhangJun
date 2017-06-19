// ShellOpenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShellOpen.h"
#include "ShellOpenDlg.h"
#include "..\..\comm\inputdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShellOpenDlg dialog

CShellOpenDlg::CShellOpenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShellOpenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShellOpenDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShellOpenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShellOpenDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShellOpenDlg, CDialog)
	//{{AFX_MSG_MAP(CShellOpenDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_TXT, OnBtnTxt)
	ON_BN_CLICKED(IDC_BTN_URL, OnBtnUrl)
	ON_BN_CLICKED(IDC_BTN_MAIL, OnBtnMail)
	ON_BN_CLICKED(IDC_BTN_BMP, OnBtnBmp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShellOpenDlg message handlers

BOOL CShellOpenDlg::OnInitDialog()
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

void CShellOpenDlg::OnPaint() 
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
HCURSOR CShellOpenDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CShellOpenDlg::OnBtnTxt() 
{
	//打开文本文件
	CFileDialog dlg(TRUE, NULL, NULL, 
		0, _T("*.txt|*.txt||"), this);
	if(dlg.DoModal() == IDOK)
		OpenTheFile(dlg.GetPathName());
}

void CShellOpenDlg::OnBtnBmp() 
{
	//打开图片文件
	CFileDialog dlg(TRUE, NULL, NULL, 
		0, _T("*.bmp|*.bmp|*.jpg|*.jpg||"), this);
	if(dlg.DoModal() == IDOK)
		OpenTheFile(dlg.GetPathName());
}

void CShellOpenDlg::OnBtnUrl() 
{
	//打开网址
	CInputDlg dlg(this, _T("输入"), _T("请输入一个网址："), 
		_T("http://www.WanMeiTech.com"));
	if(dlg.DoModal() == IDOK)
	{
		OpenTheFile(dlg.GetInputText());
	}
}

void CShellOpenDlg::OnBtnMail() 
{
	//打开邮件编辑器
	CInputDlg dlg(this, _T("输入"), _T("请输入一个邮件地址："), 
		_T("WanMeiTech@163.com"));
	if(dlg.DoModal() == IDOK)
	{
		CString str;
		str.Format(
			_T("mailto:%s?subject=测试邮件&body=测试ShellOpen程序。"), 
			dlg.GetInputText());
		OpenTheFile(str);
	}
}

void CShellOpenDlg::OpenTheFile(LPCTSTR lpFilename)
{
	//利用系统命令打开文档
	ShellExecute(m_hWnd, _T("open"), lpFilename, 
		NULL, NULL, SW_SHOWNORMAL);
}
