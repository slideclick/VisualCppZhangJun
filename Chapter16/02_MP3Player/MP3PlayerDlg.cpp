// MP3PlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MP3Player.h"
#include "MP3PlayerDlg.h"
#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMP3PlayerDlg dialog

CMP3PlayerDlg::CMP3PlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMP3PlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMP3PlayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMP3PlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMP3PlayerDlg)
	DDX_Control(pDX, IDC_SLIDER, m_slider);
	DDX_Control(pDX, IDC_LIT_MUSIC, m_list_music);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMP3PlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CMP3PlayerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_REMOVE, OnBtnRemove)
	ON_BN_CLICKED(IDC_BTN_PLAY, OnBtnPlay)
	ON_LBN_DBLCLK(IDC_LIT_MUSIC, OnDblclkLitMusic)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMP3PlayerDlg message handlers

BOOL CMP3PlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	//变量初始化
	m_bPlaying = FALSE;	
	m_nTotalLen = 0;
	*m_szShortName = _T('\0');
	*m_szFullName = _T('\0');	
	//设置定时器
	SetTimer(1, 50, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMP3PlayerDlg::OnPaint() 
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
HCURSOR CMP3PlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//添加按钮的响应函数
void CMP3PlayerDlg::OnBtnAdd() 
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, _T("音乐文件(*.mp3;*.wma;*.wav)|*.mp3;*.wma;*.wav|所有文件(*.*)|*.*||"), this);
	//重新分配缓冲区，允许最多一次选择50个文件
	TCHAR * pBuf = new TCHAR[MAX_PATH * 50];
	*pBuf = 0;
	dlg.m_ofn.lpstrFile = pBuf;
	dlg.m_ofn.nMaxFile = MAX_PATH * 50;
	//显示对话框，并获取所选文件
	if(dlg.DoModal() == IDOK)
	{
		POSITION pos = dlg.GetStartPosition();	
		CString strFile;
		while(pos != NULL)
		{
			//将所选文件添加到列表框控件
			strFile = dlg.GetNextPathName(pos);
			m_list_music.AddString(strFile);
		}
	}
	//释放临时内存
	delete []pBuf;
}
//移除按钮的响应函数
void CMP3PlayerDlg::OnBtnRemove() 
{
	//获取当前所选序号
	int nIndex = m_list_music.GetCurSel();
	if(nIndex < 0)
		return;
	//移除当前项
	m_list_music.DeleteString(nIndex);
}
//播放按钮的响应函数
void CMP3PlayerDlg::OnBtnPlay() 
{
	//如果正在播放，则停止 播放
	if(m_bPlaying)
	{
		StopPlay();
	}
	else
	{
		//获取当前所选项
		CString strCmd;
		DWORD dwErr;
		int nIndex = m_list_music.GetCurSel();
		if(nIndex < 0)
			return;
		//获取文件名，并转换为8.3格式
		m_list_music.GetText(nIndex, m_szFullName);
		GetShortPathName(m_szFullName, m_szShortName, MAX_PATH);
		//打开文件
		strCmd.Format(_T("open %s"), m_szShortName);
		dwErr = mciSendString(strCmd, NULL, 0, NULL);
		if(dwErr != 0)
		{
			ErrBox(dwErr);
			return;
		}
		//播放文件
		strCmd.Format(_T("play %s"), m_szShortName);
		dwErr = mciSendString(strCmd, NULL, 0, NULL); 
		if(dwErr != 0)
		{
			ErrBox(dwErr);
			return;
		}
		else
		{
			//获取音乐长度
			TCHAR szReturn[MAX_PATH] = {0};
			strCmd.Format(_T("status %s length"), m_szShortName);
			dwErr = mciSendString(strCmd, szReturn, MAX_PATH, NULL);
			if(dwErr != 0)
			{
				ErrBox(dwErr);
				return;
			}
			else
			{
				//设置到SLIDER控件
				m_nTotalLen = _ttoi(szReturn);
				m_slider.SetRange(0, m_nTotalLen, TRUE);
			}
			m_bPlaying = TRUE;
		}
	}
	//更新播放按钮的状态
	if(m_bPlaying)
		SetDlgItemText(IDC_BTN_PLAY, _T("停止"));
}
//列表控件的双击事件响应
void CMP3PlayerDlg::OnDblclkLitMusic() 
{
	if(StopPlay())
		OnBtnPlay();
}
//定时器事件响应函数
void CMP3PlayerDlg::OnTimer(UINT nIDEvent) 
{
	if(m_bPlaying)
	{
		CString strCmd;
		DWORD dwErr;
		TCHAR szReturn[MAX_PATH] = {0};
		//获取到当前播放进度
		strCmd.Format(_T("status %s position"), m_szShortName);
		dwErr = mciSendString(strCmd, szReturn, MAX_PATH, NULL);
		if(dwErr != 0)
		{
			ErrBox(dwErr);
		}
		else
		{
			//更新进度到SLIDER控件上
			UINT nPosition = _ttoi(szReturn);
			m_slider.SetPos(nPosition);
			//如果已经播放结束，播放下一首
			if(nPosition == m_nTotalLen)
			{
				StopPlay();
				int nIndex = m_list_music.FindString(-1, m_szFullName);
				if(nIndex < 0)
					nIndex = 0;
				else
				{
					nIndex ++;
					if(nIndex >= m_list_music.GetCount())
						nIndex = 0;
				}
				m_list_music.SetCurSel(nIndex);
				OnBtnPlay();
			}
			
		}
	}
	CDialog::OnTimer(nIDEvent);
}
//根据MCI的错误代码显示错误信息
void CMP3PlayerDlg::ErrBox(DWORD dwErr)
{
	TCHAR szBuf[MAX_PATH] = {0};
	mciGetErrorString(dwErr, szBuf, MAX_PATH);
	AfxMessageBox(szBuf);
}
//停止播放
BOOL CMP3PlayerDlg::StopPlay()
{
	if(!m_bPlaying)
		return TRUE;
	CString strCmd;
	DWORD dwErr;
	//发送停止播放命令
	strCmd.Format(_T("stop all"), m_szShortName);
	dwErr = mciSendString(strCmd, NULL, 0, NULL); 
	if(dwErr != 0)
	{
		ErrBox(dwErr);
		return FALSE;
	}
	//发送关闭命令
	dwErr = mciSendString(_T("close all"), NULL, 0, NULL);
	if(dwErr != 0)
	{
		ErrBox(dwErr);
		return FALSE;
	}
	else
	{
		//更新控件和变量状态
		SetDlgItemText(IDC_BTN_PLAY, _T("播放"));		
		m_slider.SetPos(0);
		m_bPlaying = FALSE;
		return TRUE;
	}
}
//窗体销毁消息响应函数
void CMP3PlayerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//关闭定时器，结束播放
	KillTimer(1);	
	StopPlay();
}
