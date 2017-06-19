// MultiLanguageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MultiLanguage.h"
#include "MultiLanguageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiLanguageDlg dialog

CMultiLanguageDlg::CMultiLanguageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMultiLanguageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMultiLanguageDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMultiLanguageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMultiLanguageDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMultiLanguageDlg, CDialog)
	//{{AFX_MSG_MAP(CMultiLanguageDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDR_CHS, OnChs)
	ON_COMMAND(IDR_EN, OnEn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiLanguageDlg message handlers

BOOL CMultiLanguageDlg::OnInitDialog()
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

void CMultiLanguageDlg::OnPaint() 
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
HCURSOR CMultiLanguageDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//设置语言为中文
void CMultiLanguageDlg::OnChs() 
{
	//取得INI文件的路径
	TCHAR szIni[MAX_PATH] = {0};
	GetModuleFileName(NULL, szIni, MAX_PATH);
	_tcscat(szIni, _T(".ini"));
	//将语言设置写入INI文件
	TCHAR szBuf[16] = {0};
	_stprintf(szBuf, _T("%d"), 0x804);
	WritePrivateProfileString(_T("Language"), _T("LangID"), szBuf, szIni);	
	AfxMessageBox(_T("请重新启动应用程序。"));
}
//设置语言为英文
void CMultiLanguageDlg::OnEn() 
{
	//取得INI文件的路径
	TCHAR szIni[MAX_PATH] = {0};
	GetModuleFileName(NULL, szIni, MAX_PATH);
	_tcscat(szIni, _T(".ini"));
	//将语言设置写入INI文件
	TCHAR szBuf[16] = {0};
	_stprintf(szBuf, _T("%d"), 0x409);
	WritePrivateProfileString(_T("Language"), _T("LangID"), szBuf, szIni);	
	AfxMessageBox(_T("请重新启动应用程序。"));
}
