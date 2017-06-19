// SendMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SendMsg.h"
#include "SendMsgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendMsgDlg dialog

CSendMsgDlg::CSendMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendMsgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendMsgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hCursor = NULL;
	m_bCapturing = FALSE;
	SetRect(&m_rtCtrl, 0, 0, 0, 0);
	m_hwndDest = NULL;
}

void CSendMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendMsgDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSendMsgDlg, CDialog)
	//{{AFX_MSG_MAP(CSendMsgDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_SETTEXT, OnBtnSettext)
	ON_BN_CLICKED(IDC_BTN_CLOSE, OnBtnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendMsgDlg message handlers

BOOL CSendMsgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//�����϶����
	m_hCursor = LoadCursor(NULL, IDC_SIZEALL);
	//��ȡ�϶��ؼ���λ�úʹ�С
	GetDlgItem(IDC_CAP)->GetWindowRect(&m_rtCtrl);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSendMsgDlg::OnPaint() 
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
HCURSOR CSendMsgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSendMsgDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//�ж�����Ƿ���IDC_CAP�ϣ�����ǣ������ò�����ꡣ
	if (point.x >= m_rtCtrl.left && point.x <= m_rtCtrl.right
		|| point.y >= m_rtCtrl.top && point.y <= m_rtCtrl.bottom) 
	{
		m_bCapturing = TRUE;
		SetCapture();
		SetCursor(m_hCursor);
	}
}

void CSendMsgDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//�������ɿ���������ڲ���״̬������Ӧ����
	if(m_bCapturing)
	{
		//�ָ�״̬
		ReleaseCapture();
		m_bCapturing = FALSE;
		//ȡ�õ�ǰ���λ�õĴ�����
		POINT pt = point;
		ClientToScreen(&pt);
		m_hwndDest = ::WindowFromPoint(pt);
		//��ʾ���
		TCHAR szBuf[MAX_PATH] = {0};
		_stprintf(szBuf, _T("0x%.8X"), m_hwndDest);
		SetDlgItemText(IDC_EDT_HWND, szBuf);
		//ȡ�ò���ʾ����
		GetClassName(m_hwndDest, szBuf, MAX_PATH);
		SetDlgItemText(IDC_EDT_CLASS, szBuf);
		//ȡ�ò���ʾ�ı�
		::SendMessage(m_hwndDest, WM_GETTEXT, MAX_PATH, (LPARAM)szBuf);
		SetDlgItemText(IDC_EDT_TEXT, szBuf);
	}
}

void CSendMsgDlg::OnBtnSettext() 
{
	//����Ŀ�괰����ı�
	CString str;
	GetDlgItemText(IDC_EDT_TEXT, str);
	::SendMessage(m_hwndDest, WM_SETTEXT, 0,  (LPARAM)(LPCTSTR)str);
}

void CSendMsgDlg::OnBtnClose() 
{
	//�ر�Ŀ�괰��
	::SendMessage(m_hwndDest, WM_CLOSE, 0, 0);
}
