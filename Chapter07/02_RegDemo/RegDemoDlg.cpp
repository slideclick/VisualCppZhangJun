// RegDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RegDemo.h"
#include "RegDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegDemoDlg dialog

CRegDemoDlg::CRegDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRegDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRegDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CRegDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegDemoDlg message handlers

BOOL CRegDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//打开注册表键
	HKEY hSubKey;
	LONG lRet = RegCreateKeyEx(HKEY_CURRENT_USER, 
		_T("Software\\MyTestApp"), 0, NULL, REG_OPTION_NON_VOLATILE, 
		KEY_READ | KEY_WRITE, NULL, &hSubKey, NULL);
	if(lRet != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("打开注册表键失败。"));
		return TRUE;
	}
	//读取注册表数据
	DWORD dwType = 0, dwRunCount = 0, dwLen = sizeof(DWORD);
	lRet = RegQueryValueEx(hSubKey, _T("RunCount"), 
		0, &dwType, (PBYTE)&dwRunCount, &dwLen);
	if(ERROR_SUCCESS != lRet 
		|| dwLen != sizeof(DWORD) 
		|| dwType != REG_DWORD)
		dwRunCount = 0;

	SYSTEMTIME time = {0};
	dwLen = sizeof(SYSTEMTIME);
	lRet = RegQueryValueEx(hSubKey, _T("LastRunTime"), 
		0, &dwType, (PBYTE)&time, &dwLen);
	//显示数据
	if(dwRunCount == 0)
	{
		SetDlgItemText(IDC_MSG, _T("程序首次运行！"));
	}
	else
	{
		TCHAR szMsg[256] = {0};
		_stprintf(szMsg, 
			_T("程序已经运行了%d次。\n上次运行时间是%d月%d日 %.2d:%.2d:%.2d。"), 
			dwRunCount, time.wMonth, time.wDay, time.wHour, 
			time.wMinute, time.wSecond);
		SetDlgItemText(IDC_MSG, szMsg);
	}
	//更新注册表数据
	dwRunCount ++;
	GetLocalTime(&time);
	lRet = RegSetValueEx(hSubKey, _T("RunCount"), 0, 
		REG_DWORD, (PBYTE)&dwRunCount, sizeof(DWORD));
	lRet = RegSetValueEx(hSubKey, _T("LastRunTime"), 0, 
		REG_BINARY, (PBYTE)&time, sizeof(SYSTEMTIME));
	//关闭注册表
	RegCloseKey(hSubKey);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRegDemoDlg::OnPaint() 
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
HCURSOR CRegDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
