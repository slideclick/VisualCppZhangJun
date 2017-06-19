// ClipboardDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClipboardDemo.h"
#include "ClipboardDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef UNICODE
  #define CT_TCHAR CF_UNICODETEXT
#else
  #define CT_TCHAR CF_TEXT
#endif //#ifdef UNICODE

/////////////////////////////////////////////////////////////////////////////
// CClipboardDemoDlg dialog

CClipboardDemoDlg::CClipboardDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClipboardDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClipboardDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClipboardDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClipboardDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClipboardDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CClipboardDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_EMPTY, OnBtnEmpty)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipboardDemoDlg message handlers

BOOL CClipboardDemoDlg::OnInitDialog()
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

void CClipboardDemoDlg::OnPaint() 
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
HCURSOR CClipboardDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//����а�д���ı�
void CClipboardDemoDlg::OnBtnSet() 
{
	//��ȡ������ı�
	CString str;
	GetDlgItemText(IDC_EDT_INPUT, str);
	if(str.GetLength() == 0)
	{
		SetDlgItemText(IDC_STATUS, _T("��������һЩ�ַ���"));
		return;
	}
	//�򿪼��а�
	if(OpenClipboard())
	{
		//����һ��ɿ���̷��ʵ��ڴ�
		int nLen = (str.GetLength() + 1) * sizeof(TCHAR);
		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, nLen);
		//�����ڴ沢����ڴ����ֽ�ָ��
		LPTSTR pText = (LPTSTR)GlobalLock(hGlobal);
		//���ı����Ƶ����ڴ�
		_tcscpy(pText, str);
		//�����ڴ�
		GlobalUnlock(hGlobal);
		//�������ڴ�ָ����õ����а�
		SetClipboardData(CT_TCHAR, hGlobal);
		//�رռ��а�
		CloseClipboard();
		SetDlgItemText(IDC_STATUS, _T("�ı��ѳɹ�д����а塣"));
	}
	else
	{
		SetDlgItemText(IDC_STATUS, _T("�򿪼��а�ʧ�ܡ�"));
	}
}
//��ȡ���а��ϵ��ı�
void CClipboardDemoDlg::OnBtnGet() 
{
	SetDlgItemText(IDC_EDT_INPUT, NULL);
	//�򿪼��а�
	if(OpenClipboard())
	{
		//���ԴӼ��а��ȡ�ı��͵�����
		HGLOBAL hGlobal = GetClipboardData(CT_TCHAR);
		//�����ڴ�
		LPCSTR lpText = (LPCSTR)GlobalLock(hGlobal);
		if(lpText)
		{
			//���ı�����ʾ
			SetDlgItemText(IDC_EDT_INPUT, lpText);
			SetDlgItemText(IDC_STATUS, _T("�ɹ���ȡ���ı���"));
		}
		else
		{
			//���ı�����
			SetDlgItemText(IDC_STATUS, _T("���а������ı����ݡ�"));
		}
		GlobalUnlock(hGlobal);
		//�رռ��а�
		CloseClipboard();
	}
	else
	{
		SetDlgItemText(IDC_STATUS, _T("�򿪼��а�ʧ�ܡ�"));
	}
}

void CClipboardDemoDlg::OnBtnEmpty() 
{
	//�򿪼��а�
	if(OpenClipboard())
	{
		//��գ����رռ��а�
		EmptyClipboard();
		CloseClipboard();
		SetDlgItemText(IDC_STATUS, _T("���а�����ա�"));
	}
	else
	{
		SetDlgItemText(IDC_STATUS, _T("�򿪼��а�ʧ�ܡ�"));
	}
}

void CClipboardDemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
}
