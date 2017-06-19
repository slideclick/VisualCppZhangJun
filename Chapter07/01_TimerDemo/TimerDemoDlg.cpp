// TimerDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TimerDemo.h"
#include "TimerDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//��ʱ���Ļص�����
VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT uID, DWORD dwTime)
{
	//�ڴ���˸��ɫָʾ��
	HWND hRed = ::GetDlgItem(hWnd, IDC_GREEN);
	int nShow;
	if(::IsWindowVisible(hRed))
		nShow = SW_HIDE;
	else
		nShow = SW_SHOW;
	::ShowWindow(hRed, nShow);
}
/////////////////////////////////////////////////////////////////////////////
// CTimerDemoDlg dialog

CTimerDemoDlg::CTimerDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimerDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimerDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//��ʼ����Ա
	m_nRedID = m_nGreenID = 0;
}

void CTimerDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimerDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTimerDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CTimerDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_RED, OnBtnRed)
	ON_BN_CLICKED(IDC_BTN_GREEN, OnBtnGreen)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimerDemoDlg message handlers

BOOL CTimerDemoDlg::OnInitDialog()
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

void CTimerDemoDlg::OnPaint() 
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
HCURSOR CTimerDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//���ú�ɫָʾ�Ƶ�״̬
void CTimerDemoDlg::OnBtnRed() 
{
	if(m_nRedID == 0)
	{
		//�����δ���룬����������Ϣ֪ͨ�Ķ�ʱ��
		m_nRedID = SetTimer(1, 500, NULL);
	}
	else
	{
		//�����ʱ���������У���ȡ����ʱ��
		KillTimer(m_nRedID);
		m_nRedID = 0;
		::ShowWindow(::GetDlgItem(m_hWnd, IDC_RED), SW_HIDE);
	}
}
//������ɫָʾ�Ƶ�״̬
void CTimerDemoDlg::OnBtnGreen() 
{
	if(m_nGreenID == 0)
	{
		//�����δ���룬��������ûص������Ķ�ʱ��
		m_nGreenID = SetTimer(2, 1000, TimerProc);
	}
	else
	{
		//�����ʱ���������У���ȡ����ʱ��
		KillTimer(m_nGreenID);
		m_nGreenID = 0;
		::ShowWindow(::GetDlgItem(m_hWnd, IDC_GREEN), SW_HIDE);
	}
}
//WM_TIMER��Ϣ�Ĵ�����
void CTimerDemoDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == m_nRedID)
	{
		//����Ǻ�ɫָʾ�ƵĶ�ʱ����Ϣ����˸ָʾ��
		HWND hRed = ::GetDlgItem(m_hWnd, IDC_RED);
		int nShow;
		if(::IsWindowVisible(hRed))
			nShow = SW_HIDE;
		else
			nShow = SW_SHOW;
		::ShowWindow(hRed, nShow);
	}
}
