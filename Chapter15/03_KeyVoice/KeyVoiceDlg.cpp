// KeyVoiceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KeyVoice.h"
#include "KeyVoiceDlg.h"
#include <Mmsystem.h>

#pragma comment(lib, "Winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//全局的HOOK回调声明
LRESULT CALLBACK HookProc (int nCode, WPARAM wParam, LPARAM lParam);
//全局变量
HHOOK	g_hHook;		//HOOK句柄
BOOL	g_bVoice;		//当前是否发音

/////////////////////////////////////////////////////////////////////////////
// CKeyVoiceDlg dialog

CKeyVoiceDlg::CKeyVoiceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyVoiceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKeyVoiceDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyVoiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeyVoiceDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKeyVoiceDlg, CDialog)
	//{{AFX_MSG_MAP(CKeyVoiceDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHK_VOICE, OnChkVoice)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyVoiceDlg message handlers

BOOL CKeyVoiceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//安装键盘钩子
	g_bVoice = FALSE;
	g_hHook = SetWindowsHookEx(WH_KEYBOARD, HookProc, NULL, GetCurrentThreadId());
	if(g_hHook == NULL)
	{
		TCHAR szErr[256];
		_stprintf(szErr, _T("安装HOOK时发生错误：0x%.8X!"), GetLastError());
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKeyVoiceDlg::OnPaint() 
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
HCURSOR CKeyVoiceDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKeyVoiceDlg::OnChkVoice() 
{
	//根据复选框状态，改变发音标志变量值
	CButton *pBtn = (CButton *)GetDlgItem(IDC_CHK_VOICE);
	g_bVoice = pBtn->GetCheck();
}

void CKeyVoiceDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//卸载HOOK
	UnhookWindowsHookEx(g_hHook);	
}
//钩子回调函数
LRESULT CALLBACK HookProc (int nCode, WPARAM wParam, LPARAM lParam)
{
	if(g_bVoice && nCode == HC_ACTION && (lParam & 0x80000000) == 0)
	{
		if(wParam >= '0' && wParam <= '9')
		{
			//获取按键相对应的声音文件
			static TCHAR szPath[MAX_PATH] = {0};
			if(*szPath == _T('\0'))
			{
				GetModuleFileName(NULL, szPath, MAX_PATH);
				TCHAR *p = _tcsrchr(szPath, _T('\\'));
				ASSERT(p);
				*p = 0;
			}
			TCHAR szFile[MAX_PATH] = {0};
			_stprintf(szFile, _T("%s\\..\\sound\\%c.wav"), szPath, wParam);
			//播放声音
			sndPlaySound(szFile, SND_ASYNC);
		}
	}
	//传递给下一个钩子
	return CallNextHookEx(g_hHook, nCode, wParam, lParam);	
}