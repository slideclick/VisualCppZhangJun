// FontDlgDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FontDlgDemo.h"
#include "FontDlgDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFontDlgDemoDlg dialog

CFontDlgDemoDlg::CFontDlgDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFontDlgDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFontDlgDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFontDlgDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFontDlgDemoDlg)
	DDX_Control(pDX, IDC_EDT_CONTENT, m_edtContent);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFontDlgDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CFontDlgDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_COLOR, OnBtnColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontDlgDemoDlg message handlers

BOOL CFontDlgDemoDlg::OnInitDialog()
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

void CFontDlgDemoDlg::OnPaint() 
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
HCURSOR CFontDlgDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFontDlgDemoDlg::OnOK() 
{
	//���岢��ʼ�����ָ�ʽ�ṹ
	CHARFORMAT cf = {0};
	cf.cbSize = sizeof(cf);
	//ȡ���ı���ǰ���ֵĸ�ʽ
	m_edtContent.GetSelectionCharFormat(cf);
	//��������Ի��򣬲���ȡ�õ����ָ�ʽ��ʼ���Ի���
	CFontDialog dlg(cf);
	//��ʾ�Ի���ѡ��������Ϣ
	if(dlg.DoModal() == IDOK)
	{
		//ȡ���û���ѡ������Ϣ
		dlg.GetCharFormat(cf);
		//���ı���ʽ��Ϣ���õ��ı���ǰ�ı�
		m_edtContent.SetSelectionCharFormat(cf);
	}
}

void CFontDlgDemoDlg::OnBtnColor() 
{
	//���岢��ʼ�����ָ�ʽ�ṹ
	CHARFORMAT cf = {0};
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFM_COLOR;
	//ȡ���ı���ǰ���ֵĸ�ʽ
	m_edtContent.GetSelectionCharFormat(cf);
	
	CColorDialog dlg(cf.crTextColor);
	//��ʾ�Ի���ѡ��������Ϣ
	if(dlg.DoModal() == IDOK)
	{
		//ȡ���û���ѡ����ɫ
		cf.crTextColor = dlg.GetColor();
		//����ɫ���õ��ı���ǰ�ı�
		cf.dwEffects = 0;
		m_edtContent.SetSelectionCharFormat(cf);
	}
}
