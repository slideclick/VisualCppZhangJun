// RecorderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Recorder.h"
#include "RecorderDlg.h"
#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib")

#define MCI_ALIAS _T("MyWave")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CRecorderDlg dialog

CRecorderDlg::CRecorderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecorderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRecorderDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bRecording = FALSE;
}

void CRecorderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecorderDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRecorderDlg, CDialog)
	//{{AFX_MSG_MAP(CRecorderDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_RECORD, OnBtnRecord)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecorderDlg message handlers

BOOL CRecorderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	((CComboBox *)GetDlgItem(IDC_CMB_BITS))->SetCurSel(0);
	((CComboBox *)GetDlgItem(IDC_CMB_SAMPLES))->SetCurSel(0);
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

void CRecorderDlg::OnPaint() 
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
HCURSOR CRecorderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//开始按钮的响应函数
void CRecorderDlg::OnBtnRecord() 
{
	CString strCmd;
	DWORD dwErr;
	if(m_bRecording)
	{
		strCmd = _T("stop ");
		strCmd += MCI_ALIAS;
		dwErr = mciSendString(strCmd, NULL, 0, NULL);
		if(dwErr != 0)
		{
			ErrBox(dwErr);
			return;
		}
		m_bRecording = TRUE;
		SetDlgItemText(IDC_BTN_RECORD, _T("开始"));
		GetDlgItem(IDC_BTN_SAVE)->EnableWindow(TRUE);
	}
	else
	{
		//关闭所有打开的设备
		mciSendString(_T("close all"), NULL, 0, NULL);
		//新建
		strCmd = _T("open new type waveaudio alias ");
		strCmd += MCI_ALIAS;
		dwErr = mciSendString(strCmd, NULL, 0, NULL);
		if(dwErr != 0)
		{
			ErrBox(dwErr);
			return;
		}
		//设置采样位数
		CString strTemp;
		GetDlgItemText(IDC_CMB_BITS, strTemp);
		strCmd.Format(_T("set %s bitspersample  %s"), MCI_ALIAS, (LPCTSTR)strTemp);
		dwErr = mciSendString(strCmd, NULL, 0, NULL);
		if(dwErr != 0)
		{
			ErrBox(dwErr);
			return;
		}
		//设置采样频率
		GetDlgItemText(IDC_CMB_SAMPLES, strTemp);
		strCmd.Format(_T("set %s samplespersec %s"), MCI_ALIAS, (LPCTSTR)strTemp);
		dwErr = mciSendString(strCmd, NULL, 0, NULL);
		if(dwErr != 0)
		{
			ErrBox(dwErr);
			return;
		}
		//开始录音
		strCmd = _T("record ");
		strCmd += MCI_ALIAS;
		dwErr = mciSendString(strCmd, NULL, 0, NULL);
		if(dwErr != 0)
		{
			ErrBox(dwErr);
			return;
		}
		m_bRecording = TRUE;
		SetDlgItemText(IDC_BTN_RECORD, _T("停止"));
		GetDlgItem(IDC_BTN_SAVE)->EnableWindow(FALSE);
	}

}
//保存按钮的响应函数
void CRecorderDlg::OnBtnSave() 
{
	//获取文件名
	CFileDialog dlg(FALSE, _T("wav"), NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, 
		_T("*.wav|*.wav||"), this);
	if(dlg.DoModal() != IDOK)
		return;
	CString strFile = dlg.GetPathName();
	//发送保存命令
	CString strCmd;
	DWORD dwErr;
	strCmd.Format(_T("save %s \"%s\""), MCI_ALIAS, strFile);
	dwErr = mciSendString(strCmd, NULL, 0, NULL);
	if(dwErr != 0)
	{
		ErrBox(dwErr);
	}
}

//根据MCI的错误代码显示错误信息
void CRecorderDlg::ErrBox(DWORD dwErr)
{
	TCHAR szBuf[MAX_PATH] = {0};
	mciGetErrorString(dwErr, szBuf, MAX_PATH);
	AfxMessageBox(szBuf);
}

void CRecorderDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//在应用程序退出前关闭所有设备
	mciSendString(_T("close all"), NULL, 0, NULL);
}
