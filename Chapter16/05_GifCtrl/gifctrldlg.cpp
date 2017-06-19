// GifCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GifCtrl.h"
#include "GifCtrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGifCtrlDlg dialog

CGifCtrlDlg::CGifCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGifCtrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGifCtrlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGifCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGifCtrlDlg)
	DDX_Control(pDX, IDC_CMB_VMODE, m_cmb_vmode);
	DDX_Control(pDX, IDC_CMB_HMODE, m_cmb_hmode);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGifCtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CGifCtrlDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGifCtrlDlg message handlers

BOOL CGifCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	//添加水平绘制方式选项
	m_cmb_hmode.AddString(_T("居中"));
	m_cmb_hmode.AddString(_T("居左"));
	m_cmb_hmode.AddString(_T("居右"));
	m_cmb_hmode.AddString(_T("缩放"));
	m_cmb_hmode.AddString(_T("平铺"));
	m_cmb_hmode.SetCurSel(0);
	//添加垂直绘制方式选项
	m_cmb_vmode.AddString(_T("居中"));
	m_cmb_vmode.AddString(_T("居上"));
	m_cmb_vmode.AddString(_T("居下"));
	m_cmb_vmode.AddString(_T("缩放"));
	m_cmb_vmode.AddString(_T("平铺"));
	m_cmb_vmode.SetCurSel(0);
	//控件绑定
	m_pic.SetBgColor(RGB(0, 0, 0));
	m_pic.Attach(::GetDlgItem(m_hWnd, IDC_GIF));
	return TRUE; 
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGifCtrlDlg::OnPaint() 
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
HCURSOR CGifCtrlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//浏览按钮的响应函数
void CGifCtrlDlg::OnBtnBrowse() 
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, _T("*.gif|*.gif||"), this);
	if(dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_EDT_FILE, dlg.GetPathName());
}
//设置按钮的响应函数
void CGifCtrlDlg::OnBtnSet() 
{
	//更新绘制模式
	int nHMode = m_cmb_hmode.GetCurSel();
	int nVMode = m_cmb_vmode.GetCurSel();
	m_pic.SetImageMode((CPictureEx::ImageMode)nHMode, (CPictureEx::ImageMode)nVMode);
	//加载图片
	CString strFile;
	GetDlgItemText(IDC_EDT_FILE, strFile);
	if(strFile.GetLength() > 0)
	{
		if(!m_pic.LoadImage(strFile))
			AfxMessageBox(_T("加载图片失败！"));
	}
	else
	{
		AfxMessageBox(_T("请先选择图片路径！"));
	}
}

void CGifCtrlDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m_pic.Detach();
}
