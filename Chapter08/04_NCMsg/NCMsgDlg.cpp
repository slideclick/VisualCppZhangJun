// NCMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NCMsg.h"
#include "NCMsgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNCMsgDlg dialog

CNCMsgDlg::CNCMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNCMsgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNCMsgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNCMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNCMsgDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNCMsgDlg, CDialog)
	//{{AFX_MSG_MAP(CNCMsgDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNCMsgDlg message handlers

BOOL CNCMsgDlg::OnInitDialog()
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

void CNCMsgDlg::OnPaint() 
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
HCURSOR CNCMsgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

UINT CNCMsgDlg::OnNcHitTest(CPoint point) 
{
	UINT nTest;
	RECT rect;
	GetWindowRect(&rect);
	
	//������ָ�봦�ڴ���߽�5�������ڣ������϶��ı䴰���С��
	//������ָ�봦�ڴ����ϲ�20�������ڣ�����������������ƶ����塣
	if(point.x >= rect.left && point.x < rect.left + 4)			//���X�����ڴ�����߽�
	{
		if(point.y >= rect.top && point.y <= rect.top + 4)	
			nTest = HTTOPLEFT;									//����ڴ������Ͻ�
		else if(point.y >= rect.bottom-4 && point.y <= rect.bottom)	
			nTest = HTBOTTOMLEFT;								//����ڴ������½�
		else
			nTest = HTLEFT;										//����ڴ�����߽�����λ��
	}
	else if(point.x <= rect.right && point.x >= rect.right - 4)	//���X�����ڴ����ұ߽�
	{
		if(point.y >= rect.top && point.y <= rect.top + 4)	
			nTest = HTTOPRIGHT;									//����ڴ������Ͻ�
		else if(point.y >= rect.bottom-4 && point.y <= rect.bottom)	
			nTest = HTBOTTOMRIGHT;								//����ڴ������½�
		else
			nTest = HTRIGHT;									//����ڴ����ұ߽�����λ��
	}
	else if(point.y >= rect.top && point.y <= rect.top + 4)
	{
		nTest = HTTOP;											//����ڴ����ϱ߽�
	}
	else if(point.y >= rect.bottom - 4 && point.y < rect.bottom)
	{
		nTest = HTBOTTOM;										//���
	}
	else if(point.y < rect.top + 20)
	{
		nTest = HTCAPTION;							//��괦�ڡ���������
	}
	else
	{
		nTest = HTCLIENT;							//Ĭ������������⴦��
	}
	return nTest;
}
