// TextPathWndDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TextPathWnd.h"
#include "TextPathWndDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextPathWndDlg dialog

CTextPathWndDlg::CTextPathWndDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTextPathWndDlg::IDD, pParent), m_hFont(NULL)
{
	//{{AFX_DATA_INIT(CTextPathWndDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTextPathWndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextPathWndDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTextPathWndDlg, CDialog)
	//{{AFX_MSG_MAP(CTextPathWndDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextPathWndDlg message handlers

BOOL CTextPathWndDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//��������
	m_wndLayered.Create();
	m_wndPath.Create();
	//��������
	m_hFont = CreateFont(64, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
		DEFAULT_PITCH, _T("����"));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTextPathWndDlg::OnPaint() 
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
HCURSOR CTextPathWndDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTextPathWndDlg::OnOK() 
{
	//ȡ�������ı�
	GetDlgItemText(IDC_EDT_INPUT, m_str);
	//�ô���ˢ��
	m_wndPath.UpdateText(m_str, m_hFont);
	m_wndLayered.UpdateText(m_str, m_hFont);
}

void CTextPathWndDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//���ٴ���
	if(m_wndPath.GetHwnd())
		m_wndPath.Destroy();
	if(m_wndLayered)
		m_wndLayered.Destroy();
	//ɾ�������ͷ���Դ
	if (m_hFont)
	{
		DeleteObject(m_hFont);
		m_hFont = NULL;
	}
}