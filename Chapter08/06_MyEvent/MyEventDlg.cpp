// MyEventDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyEvent.h"
#include "MyEventDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyEventDlg dialog

CMyEventDlg::CMyEventDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyEventDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyEventDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyEventDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyEventDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyEventDlg, CDialog)
	//{{AFX_MSG_MAP(CMyEventDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyEventDlg message handlers

BOOL CMyEventDlg::OnInitDialog()
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

void CMyEventDlg::OnPaint() 
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
HCURSOR CMyEventDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*
--一个典型的指令串：
S|2000
K|10|1
K|56|1
K|56|0
K|43|1
K|43|0
K|10|0
K|66|1
K|66|0
S|1000
M|1|0,0|0
M|8|0,0|0
M|10|0,0|0
*/

void CMyEventDlg::OnOK() 
{
	CString strCmd;
	GetDlgItemText(IDC_EDT_CMD, strCmd);
	//去掉多余字符
	strCmd.Replace(_T("\r"), _T(""));
	LPCTSTR lpCmd = strCmd;

	GetDlgItem(IDOK)->EnableWindow(FALSE);
	//循环执行每行指令
	BOOL bRun = TRUE;
	while(lpCmd && bRun)
	{
		switch(*lpCmd)
		{
		case _T('K'):
			ProcessKeybdEvent(&lpCmd);
			break;
		case _T('M'):
			ProcessMouseEvent(&lpCmd);
			break;
		case _T('S'):
			ProcessSleep(&lpCmd);
			break;
		default:
			bRun = FALSE;
			break;
		}
	}
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}

void CMyEventDlg::ProcessKeybdEvent(LPCTSTR *ppszCmd)
{
	//键盘：K|虚拟键|是否按下(1/0)
	int nVKey;
	BOOL bIsDown;
	int nCount = _stscanf(*ppszCmd, _T("K|%x|%d"), &nVKey, &bIsDown);
	//如果输入不是预期的格式，退出
	if(nCount != 2)		
	{
		*ppszCmd = NULL;
		return;
	}
	//产生消息
	keybd_event((BYTE)nVKey, 0, bIsDown ? 0 : KEYEVENTF_KEYUP, 0);
	*ppszCmd = FindNext(*ppszCmd);
}

void CMyEventDlg::ProcessMouseEvent(LPCTSTR *ppszCmd)
{
	//鼠标：M|动作(Hex)|x,y|Data
	int nEvent, x, y, nExData;
	int nCount = _stscanf(*ppszCmd, _T("M|%x|%d,%d|%d"), &nEvent, &x, &y, &nExData);
	//如果输入不是预期的格式，退出
	if(nCount != 4)		
	{
		*ppszCmd = NULL;
		return;
	}
	//固定使用绝对坐标
	nEvent |= MOUSEEVENTF_ABSOLUTE; 
	//产生消息
	mouse_event(nEvent, x, y, nExData, 0);
	*ppszCmd = FindNext(*ppszCmd);
}

void CMyEventDlg::ProcessSleep(LPCTSTR *ppszCmd)
{
	//等待：S|毫秒数
	int nSleep;
	int nCount = _stscanf(*ppszCmd, _T("S|%d"), &nSleep);
	//如果输入不是预期的格式，退出
	if(nCount != 1)			
	{
		*ppszCmd = NULL;
		return;
	}
	//睡眠
	Sleep(nSleep);
	*ppszCmd = FindNext(*ppszCmd);
}

LPCTSTR CMyEventDlg::FindNext(LPCTSTR lpBuffer)
{
	//定位下一个指令
	TCHAR * p = _tcschr(lpBuffer, _T('\n'));
	if(p == NULL)
		return NULL;
	else
		return (p + 1);
}
