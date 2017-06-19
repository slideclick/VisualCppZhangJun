// RedirectStdioDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RedirectStdio.h"
#include "RedirectStdioDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRedirectStdioDlg dialog

CRedirectStdioDlg::CRedirectStdioDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRedirectStdioDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRedirectStdioDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRedirectStdioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRedirectStdioDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRedirectStdioDlg, CDialog)
	//{{AFX_MSG_MAP(CRedirectStdioDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRedirectStdioDlg message handlers

BOOL CRedirectStdioDlg::OnInitDialog()
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

void CRedirectStdioDlg::OnPaint() 
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
HCURSOR CRedirectStdioDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRedirectStdioDlg::OnBtnStart() 
{
	HANDLE hPWrite, hPRead;
	//创建管道
	SECURITY_ATTRIBUTES sat ={0};
	sat.nLength = sizeof(sat);  
	sat.bInheritHandle = TRUE;  
	sat.lpSecurityDescriptor = NULL;
	BOOL bCreate = CreatePipe(&hPRead, &hPWrite, &sat, 0);
	if(!bCreate)
	{
		MessageBox(_T("创建管道失败！"));
	}
	//初始化进程信息
	PROCESS_INFORMATION pi = {0};
    STARTUPINFO si ={0};
	si.cb = sizeof(si);
	si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	//新进程的输出重定向到管道的写入端
	si.hStdOutput = si.hStdError = hPWrite;
	//新进程不显示界面
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;   
	//启动进程
	TCHAR szCmd[MAX_PATH * 2] = {0};
	GetDlgItemText(IDC_EDT_CMD, szCmd, MAX_PATH * 2);
	bCreate = CreateProcess(NULL, szCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	if(!bCreate)
	{
		//启动进程失败，释放资源
		CloseHandle(hPWrite);
		CloseHandle(hPRead);
		MessageBox(_T("创建进程失败！"));
	}
	else
	{
		//创建成功，释放写入端让进程写入数据
		CString str;
		CloseHandle(hPWrite);
		TCHAR szBuff[1024];
		DWORD dwRead;
		//从管道读取端获取内容
		while(TRUE)  
		{  
			memset(szBuff, 0, sizeof(szBuff));
			if(!ReadFile(hPRead, szBuff, 1024, &dwRead, NULL))  
				break;  
			str += szBuff;
			SetDlgItemText(IDC_EDT_OUTPUT, str);
		}
		//是否读取端
		CloseHandle(hPRead);
	}
}
