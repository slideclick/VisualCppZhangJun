// BgMusicDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BgMusic.h"
#include "BgMusicDlg.h"
#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBgMusicDlg dialog

CBgMusicDlg::CBgMusicDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBgMusicDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBgMusicDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBgMusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBgMusicDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBgMusicDlg, CDialog)
	//{{AFX_MSG_MAP(CBgMusicDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHK_PLAY, OnChkPlay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBgMusicDlg message handlers

BOOL CBgMusicDlg::OnInitDialog()
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

void CBgMusicDlg::OnPaint() 
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
HCURSOR CBgMusicDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBgMusicDlg::OnChkPlay() 
{
	CButton *pBtn = (CButton *)GetDlgItem(IDC_CHK_PLAY);
	//“背景声音”复选框选中时，播放声音，非选中时，停止播放
	if(pBtn->GetCheck())
	{
		//播放资源中的声音
		BOOL bPlay = PlaySound(
			MAKEINTRESOURCE(IDR_BG), AfxGetResourceHandle(), 
			SND_ASYNC | SND_RESOURCE | SND_LOOP);
		if(!bPlay)
		{
			//播放失败时显示错误
			DWORD dwErr = GetLastError();
			CString strErr;
			strErr.Format(_T("播放声音时错误：0x%.8X!"), dwErr);
			AfxMessageBox(strErr);
		}
	}
	else
	{
		//停止播放
		PlaySound(NULL, NULL, SND_PURGE);
	}
}
