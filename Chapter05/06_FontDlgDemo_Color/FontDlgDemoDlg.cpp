// FontDlgDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FontDlgDemo.h"
#include "FontDlgDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFontDlgDemoDlg dialog

CFontDlgDemoDlg::CFontDlgDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFontDlgDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFontDlgDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFontDlgDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFontDlgDemoDlg)
	DDX_Control(pDX, IDC_EDT_CONTENT, m_edtContent);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFontDlgDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CFontDlgDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_COLOR, OnBtnColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontDlgDemoDlg message handlers

BOOL CFontDlgDemoDlg::OnInitDialog()
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

void CFontDlgDemoDlg::OnPaint() 
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
HCURSOR CFontDlgDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFontDlgDemoDlg::OnOK() 
{
	//定义并初始化文字格式结构
	CHARFORMAT cf = {0};
	cf.cbSize = sizeof(cf);
	//取得文本框当前文字的格式
	m_edtContent.GetSelectionCharFormat(cf);
	//创建字体对话框，并用取得的文字格式初始化对话框。
	CFontDialog dlg(cf);
	//显示对话框，选择字体信息
	if(dlg.DoModal() == IDOK)
	{
		//取得用户所选字体信息
		dlg.GetCharFormat(cf);
		//将文本格式信息设置到文本框当前文本
		m_edtContent.SetSelectionCharFormat(cf);
	}
}

void CFontDlgDemoDlg::OnBtnColor() 
{
	//定义并初始化文字格式结构
	CHARFORMAT cf = {0};
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFM_COLOR;
	//取得文本框当前文字的格式
	m_edtContent.GetSelectionCharFormat(cf);
	
	CColorDialog dlg(cf.crTextColor);
	//显示对话框，选择字体信息
	if(dlg.DoModal() == IDOK)
	{
		//取得用户所选字颜色
		cf.crTextColor = dlg.GetColor();
		//将颜色设置到文本框当前文本
		cf.dwEffects = 0;
		m_edtContent.SetSelectionCharFormat(cf);
	}
}
