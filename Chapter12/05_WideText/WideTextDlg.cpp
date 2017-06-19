// WideTextDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WideText.h"
#include "WideTextDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWideTextDlg dialog

CWideTextDlg::CWideTextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWideTextDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWideTextDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWideTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWideTextDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWideTextDlg, CDialog)
	//{{AFX_MSG_MAP(CWideTextDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWideTextDlg message handlers

BOOL CWideTextDlg::OnInitDialog()
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

void CWideTextDlg::OnPaint() 
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
HCURSOR CWideTextDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWideTextDlg::OnOpen() 
{
	//ѡ��Ҫ�򿪵��ļ�
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, _T("*.txt|*.txt||"), this);
	if(dlg.DoModal() != IDOK)
		return;
	//���ļ�
	CFile file;	
	if(!file.Open(dlg.GetPathName(), CFile::modeRead))
		return;
	//����һ������������ΪUnicodeһ���ַ�ռ2���ֽڣ�
	//Ϊ��ȷ���ַ�������һ����ȷ�Ľ�β�ַ�0������Ҫ�����2���ֽ�
	DWORD dwLen = file.GetLength();
	byte *pBuf = new byte[dwLen + 2];
	byte *pTemp = pBuf;
	ZeroMemory(pBuf, dwLen + 2);
	//���ļ����ݶ�ȡ��������
	file.ReadHuge(pBuf, dwLen);
	//�ж��Ƿ���Unicode��־
	BOOL bWide = FALSE;
	if(dwLen > 2 && pBuf[0] == 0xFF && pBuf[1] == 0xFE)
	{
		//�����Unicode��־����ȷ����Unicode�ַ�
		bWide = TRUE;
		//���ַ������ų���־����Ϊ��2���ֽڲ����ַ�����Ա
		pTemp += 2;
	}
	else
	{
		//���û����ȷ�ı�־����API�������в²��жϣ���������ȷ����ȷ
		bWide = IsTextUnicode(pBuf, dwLen, NULL);
	}

	//���û�ж���UNICODE�꣬�ı���ֻ����Ansi�ַ���
#ifndef UNICODE
	//����ı���Unicode�ַ�������Ҫ��ת��ΪAnsi�ַ���
	if(bWide)
	{
		//����һ��Ansi�ַ���������
		char *pBufA = new char[dwLen + 1];
		ZeroMemory(pBufA, dwLen + 1);
		//Unicode�ַ�����Ansi�ַ���ת��
		WideCharToMultiByte(CP_ACP, 0, (WCHAR *)pTemp, -1, pBufA, dwLen, NULL, NULL);
		//������ʾ���ı���
		SetDlgItemText(IDC_TEXT, pBufA);
		//�ͷŻ�����
		delete []pBufA;
	}
	//����ı�����Unicode�ַ�������ֱ����ʾ
	else
	{
		SetDlgItemText(IDC_TEXT, (char *)pBuf);
	}
	//���������UNICODE�꣬�ı���ֻ����Unicode�ַ���
#else
	//����ı���Unicode�ַ�������ֱ����ʾ
	if(bWide)
	{
		SetDlgItemText(IDC_TEXT, (WCHAR *)pBuf);
	}
	//����ı�����Unicode��Ҫ��ת��ΪUnicode�ַ���
	else
	{
		//����һ��������
		WCHAR *pBufW = new WCHAR[dwLen + 1];
		ZeroMemory(pBufW, (dwLen + 1) * sizeof(WCHAR));
		//Ansi�ַ���ת��ΪUnicode�ַ���
		MultiByteToWideChar(CP_ACP, 0, (char *)pBuf, -1, pBufW, dwLen + 1);
		//��ʾ�ı�
		SetDlgItemText(IDC_TEXT, pBufW);
		//�ͷŻ�����
		delete []pBufW;
	}
#endif
	delete []pBuf;
	file.Close();
}

void CWideTextDlg::OnSave() 
{
	//�õ��ļ���
	CFileDialog dlg(TRUE, _T("txt"), NULL, OFN_OVERWRITEPROMPT, _T("*.txt|*.txt||"), this);
	if(dlg.DoModal() != IDOK)
		return;
	//�����ļ�
	CFile file;	
	if(!file.Open(dlg.GetPathName(), CFile::modeWrite | CFile::modeCreate))
		return;
	//���ļ�д��Unicode��־
	byte pFlags[2] = {0xFF, 0xFE};
	file.Write(pFlags, 2);
	//ȡ���ı����е��ַ�
	CString str;
	GetDlgItemText(IDC_TEXT, str);
	//�õ��ı��򳤶�
	int nLen = str.GetLength();
	//���û�ж���UNICODE�꣬��str�е��ַ�ΪAnsi�ַ���
	//�Ƚ�str�е��ַ�ת��ΪUNICODE
#ifndef UNICODE
	//����һ�黺����
	WCHAR *pBufW = new WCHAR[nLen + 1];
	//��������ʵ���ֽ���
	int nBytes = (nLen + 1) * sizeof(WCHAR);
	//��ʼ��������
	ZeroMemory(pBufW, nBytes);
	//Ansi�ַ���ת��ΪUnicode�ַ���
	MultiByteToWideChar(CP_ACP, 0, str, -1, pBufW, nLen + 1);
	//��Unicode�ı�д���ļ�
	file.WriteHuge(pBufW, wcslen(pBufW)*sizeof(WCHAR));
	//�ͷŻ�����
	delete []pBufW;
#else
	//���������UNICODE�꣬��str�е��ַ�ΪUnicode�ַ���
	//str�е��ַ�����ת��ΪUNICODE��ֱ�ӱ���
	file.WriteHuge((LPCTSTR)str, str.GetLength()*sizeof(WCHAR));	
#endif
	file.Close();
}
