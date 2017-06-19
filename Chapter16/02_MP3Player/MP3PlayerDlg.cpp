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
	//������ʼ��
	m_bPlaying = FALSE;	
	m_nTotalLen = 0;
	*m_szShortName = _T('\0');
	*m_szFullName = _T('\0');	
	//���ö�ʱ��
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
//��Ӱ�ť����Ӧ����
void CMP3PlayerDlg::OnBtnAdd() 
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, _T("�����ļ�(*.mp3;*.wma;*.wav)|*.mp3;*.wma;*.wav|�����ļ�(*.*)|*.*||"), this);
	//���·��仺�������������һ��ѡ��50���ļ�
	TCHAR * pBuf = new TCHAR[MAX_PATH * 50];
	*pBuf = 0;
	dlg.m_ofn.lpstrFile = pBuf;
	dlg.m_ofn.nMaxFile = MAX_PATH * 50;
	//��ʾ�Ի��򣬲���ȡ��ѡ�ļ�
	if(dlg.DoModal() == IDOK)
	{
		POSITION pos = dlg.GetStartPosition();	
		CString strFile;
		while(pos != NULL)
		{
			//����ѡ�ļ���ӵ��б��ؼ�
			strFile = dlg.GetNextPathName(pos);
			m_list_music.AddString(strFile);
		}
	}
	//�ͷ���ʱ�ڴ�
	delete []pBuf;
}
//�Ƴ���ť����Ӧ����
void CMP3PlayerDlg::OnBtnRemove() 
{
	//��ȡ��ǰ��ѡ���
	int nIndex = m_list_music.GetCurSel();
	if(nIndex < 0)
		return;
	//�Ƴ���ǰ��
	m_list_music.DeleteString(nIndex);
}
//���Ű�ť����Ӧ����
void CMP3PlayerDlg::OnBtnPlay() 
{
	//������ڲ��ţ���ֹͣ ����
	if(m_bPlaying)
	{
		StopPlay();
	}
	else
	{
		//��ȡ��ǰ��ѡ��
		CString strCmd;
		DWORD dwErr;
		int nIndex = m_list_music.GetCurSel();
		if(nIndex < 0)
			return;
		//��ȡ�ļ�������ת��Ϊ8.3��ʽ
		m_list_music.GetText(nIndex, m_szFullName);
		GetShortPathName(m_szFullName, m_szShortName, MAX_PATH);
		//���ļ�
		strCmd.Format(_T("open %s"), m_szShortName);
		dwErr = mciSendString(strCmd, NULL, 0, NULL);
		if(dwErr != 0)
		{
			ErrBox(dwErr);
			return;
		}
		//�����ļ�
		strCmd.Format(_T("play %s"), m_szShortName);
		dwErr = mciSendString(strCmd, NULL, 0, NULL); 
		if(dwErr != 0)
		{
			ErrBox(dwErr);
			return;
		}
		else
		{
			//��ȡ���ֳ���
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
				//���õ�SLIDER�ؼ�
				m_nTotalLen = _ttoi(szReturn);
				m_slider.SetRange(0, m_nTotalLen, TRUE);
			}
			m_bPlaying = TRUE;
		}
	}
	//���²��Ű�ť��״̬
	if(m_bPlaying)
		SetDlgItemText(IDC_BTN_PLAY, _T("ֹͣ"));
}
//�б�ؼ���˫���¼���Ӧ
void CMP3PlayerDlg::OnDblclkLitMusic() 
{
	if(StopPlay())
		OnBtnPlay();
}
//��ʱ���¼���Ӧ����
void CMP3PlayerDlg::OnTimer(UINT nIDEvent) 
{
	if(m_bPlaying)
	{
		CString strCmd;
		DWORD dwErr;
		TCHAR szReturn[MAX_PATH] = {0};
		//��ȡ����ǰ���Ž���
		strCmd.Format(_T("status %s position"), m_szShortName);
		dwErr = mciSendString(strCmd, szReturn, MAX_PATH, NULL);
		if(dwErr != 0)
		{
			ErrBox(dwErr);
		}
		else
		{
			//���½��ȵ�SLIDER�ؼ���
			UINT nPosition = _ttoi(szReturn);
			m_slider.SetPos(nPosition);
			//����Ѿ����Ž�����������һ��
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
//����MCI�Ĵ��������ʾ������Ϣ
void CMP3PlayerDlg::ErrBox(DWORD dwErr)
{
	TCHAR szBuf[MAX_PATH] = {0};
	mciGetErrorString(dwErr, szBuf, MAX_PATH);
	AfxMessageBox(szBuf);
}
//ֹͣ����
BOOL CMP3PlayerDlg::StopPlay()
{
	if(!m_bPlaying)
		return TRUE;
	CString strCmd;
	DWORD dwErr;
	//����ֹͣ��������
	strCmd.Format(_T("stop all"), m_szShortName);
	dwErr = mciSendString(strCmd, NULL, 0, NULL); 
	if(dwErr != 0)
	{
		ErrBox(dwErr);
		return FALSE;
	}
	//���͹ر�����
	dwErr = mciSendString(_T("close all"), NULL, 0, NULL);
	if(dwErr != 0)
	{
		ErrBox(dwErr);
		return FALSE;
	}
	else
	{
		//���¿ؼ��ͱ���״̬
		SetDlgItemText(IDC_BTN_PLAY, _T("����"));		
		m_slider.SetPos(0);
		m_bPlaying = FALSE;
		return TRUE;
	}
}
//����������Ϣ��Ӧ����
void CMP3PlayerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//�رն�ʱ������������
	KillTimer(1);	
	StopPlay();
}
