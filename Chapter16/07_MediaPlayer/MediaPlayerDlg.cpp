// MediaPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MediaPlayer.h"
#include "MediaPlayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//视频事件通知消息
#define WM_USER_VIDEONOTIFY (WM_USER+150)

/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerDlg dialog

CMediaPlayerDlg::CMediaPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMediaPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMediaPlayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMediaPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMediaPlayerDlg)
	DDX_Control(pDX, IDC_SLIDER, m_slider);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMediaPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CMediaPlayerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDR_OPEN, OnOpen)
	ON_WM_TIMER()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER, OnReleasedcaptureSlider)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER_VIDEONOTIFY, OnVideoNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerDlg message handlers

BOOL CMediaPlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMediaPlayerDlg::OnPaint() 
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
HCURSOR CMediaPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMediaPlayerDlg::OnOpen() 
{
	//浏览视频文件
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, 
		_T("*.mpg;*.avi;|*.mpg;*.avi;|*.*|*.*||"), this);
	if(dlg.DoModal() != IDOK)
		return;
	m_slider.EnableWindow(FALSE);
	//释放之前的对象
	m_video.Release();
	//创建对象
	if(!m_video.Create(m_hWnd, WM_USER_VIDEONOTIFY))
	{
		AfxMessageBox(m_video.GetErrMsg());
		return;
	}
	//加载视频
	if(!m_video.LoadFile(dlg.GetPathName()))
	{
		AfxMessageBox(m_video.GetErrMsg());
	}
	else
	{
		m_slider.EnableWindow(TRUE);
		//设置视频窗口父窗口
		if(!m_video.SetOwner(m_hWnd))
			AfxMessageBox(m_video.GetErrMsg());
		//设置视频窗口大小和位置
		RECT rcClient = {0};
		::GetClientRect(m_hWnd, &rcClient);
		rcClient.bottom -= 40;
		rcClient.left += 4;
		rcClient.right -= 4;
		rcClient.top += 4;
		m_video.MoveVideoWnd(&rcClient);
		//获取视频总时间
		__int64 nDuration = 0;
		if(m_video.GetDuration(&nDuration))
		{
			//更新滑块控件
			m_slider.SetRange(0, nDuration);
		}
		//开始播放
		m_video.Run();
		SetTimer(1, 500, NULL);
	}
}
//定时器消息处理
void CMediaPlayerDlg::OnTimer(UINT nIDEvent) 
{
	//获取视频当前进度，并更新滑块控件
	__int64 nPos = 0;
	if(m_video.GetPosition(&nPos))
		m_slider.SetPos(nPos);
	CDialog::OnTimer(nIDEvent);
}
//滑块位置改变消息
void CMediaPlayerDlg::OnReleasedcaptureSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//获得当前滑块位置
	int nPos = m_slider.GetPos();
	//设置视频进度
	m_video.SetPosition(nPos);
	*pResult = 0;
}
//处理视频事件
void CMediaPlayerDlg::OnVideoNotify()
{
    long lCode, lp1, lp2;
    while (m_video.GetEvent(&lCode, &lp1, &lp2))
    {
        switch(lCode)
        {
		case EC_USERABORT:
		case EC_ERRORABORT:
		case EC_COMPLETE:
			//播放结束
			KillTimer(1);
			m_video.Stop();
			m_slider.SetPos(0);
			break;
        }
    }
}
