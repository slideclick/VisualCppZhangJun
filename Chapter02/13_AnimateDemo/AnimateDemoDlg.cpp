// AnimateDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AnimateDemo.h"
#include "AnimateDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimateDemoDlg dialog

CAnimateDemoDlg::CAnimateDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnimateDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnimateDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAnimateDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnimateDemoDlg)
	DDX_Control(pDX, IDC_ANIMATE, m_animate);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAnimateDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CAnimateDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_PLAYFILE, OnBtnPlayfile)
	ON_BN_CLICKED(IDC_BTN_PLAYRES, OnBtnPlayres)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimateDemoDlg message handlers

BOOL CAnimateDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//m_animate.Open()
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAnimateDemoDlg::OnPaint() 
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
HCURSOR CAnimateDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//“浏览”按钮的响应函数
void CAnimateDemoDlg::OnBtnBrowse() 
{
	//显示打开文件对话框，并取得文件路径
	CFileDialog dlg(TRUE, NULL, NULL, 
		OFN_FILEMUSTEXIST, _T("*.avi|*.avi"), this);
	if(dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_EDT_FILENAME, dlg.GetPathName());
}
//“播放文件”按钮的响应函数
void CAnimateDemoDlg::OnBtnPlayfile() 
{
	//获取输入的文件名
	CString strFile;
	GetDlgItemText(IDC_EDT_FILENAME, strFile);
	//打开文件
	if(m_animate.Open(strFile))
		//播放文件
		m_animate.Play(0, -1, -1);
	else
		AfxMessageBox(_T("无法加载文件！"));
}
//“播放资源”按钮的响应函数
void CAnimateDemoDlg::OnBtnPlayres() 
{
	//打开资源中的视频
	m_animate.Open(IDR_VIDEO);
	//播放视频
	m_animate.Play(0, -1, -1);
}
