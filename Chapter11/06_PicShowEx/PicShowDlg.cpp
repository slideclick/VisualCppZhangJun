// PicShowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PicShow.h"
#include "PicShowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicShowDlg dialog

CPicShowDlg::CPicShowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPicShowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPicShowDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	*m_szFile = _T('\0');
}

void CPicShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPicShowDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPicShowDlg, CDialog)
	//{{AFX_MSG_MAP(CPicShowDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDR_OPEN, OnOpen)
	ON_COMMAND(IDR_SAVE, OnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicShowDlg message handlers

BOOL CPicShowDlg::OnInitDialog()
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

void CPicShowDlg::OnPaint() 
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
		if(m_dc.GetDC())
		{
			//���򿪵�ͼƬ���Ƶ�����
			CRect rect;
			GetClientRect(&rect);
			CPaintDC dc(this);
			int nMode = SetStretchBltMode(dc, COLORONCOLOR);
			::StretchBlt(dc, 0, 0, rect.right, rect.bottom, 
				m_dc, 0, 0, m_dc.GetWidth(), m_dc.GetHeight(), SRCCOPY);
			SetStretchBltMode(dc, nMode);
		}
		else
			CDialog::OnPaint();

	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPicShowDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPicShowDlg::OnOpen() 
{
	//��ͼƬ�ļ�
	LPCTSTR lpFilter = _T("*.bmp;*.jpg;*.gif;*.png;*.tiff;|*.bmp;*.jpg;*.gif;*.png;*.tiff;||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, lpFilter, this);
	if(dlg.DoModal() == IDOK)
	{
		_tcscpy(m_szFile, dlg.GetPathName());
		//��gdi+��ͼƬ���������ڴ�dc
		if(m_dc.GetDC())
			m_dc.DeleteObj();
		m_dc.CreateFromFile(m_szFile);
		//ˢ�´���
		Invalidate(FALSE);
	}
}

//�õ�ָ��ͼƬ��ʽ�ı���ֵ 
int CPicShowDlg::GetImageCLSID(const WCHAR* format, CLSID* pCLSID) 
{
	UINT nNum = 0; 
	UINT nSize = 0; 
	ImageCodecInfo* pImageCodecInfo = NULL; 
	//��ȡϵͳ��֧�ֵ�ͼƬ��ʽ����
	GetImageEncodersSize(&nNum, &nSize); 
	if(nSize == 0) 
		return FALSE; 
	//�����ڴ� 
	pImageCodecInfo = (ImageCodecInfo*)(malloc(nSize)); 
	if(pImageCodecInfo == NULL) 
		return FALSE; 
	//���ϵͳ�п��õı��뷽ʽ��������Ϣ 
	GetImageEncoders(nNum, nSize, pImageCodecInfo); 
	//�ڿ��ñ�����Ϣ�в��Ҹ�ʽ�Ƿ�֧�� 
	for(UINT i = 0; i < nNum; ++i) 
	{ 
		//MimeType�����뷽ʽ�ľ������� 
		if( wcscmp(pImageCodecInfo[i].MimeType, format) == 0 ) 
		{ 
			*pCLSID = pImageCodecInfo[i].Clsid; 
			free(pImageCodecInfo); 
			return TRUE; 
		} 
	} 
	free(pImageCodecInfo); 
	return FALSE; 
} 

void CPicShowDlg::OnSave() 
{
	if(*m_szFile == _T('\0'))
		return;

	//��ȡҪ������ļ���
	LPCTSTR lpFilter = _T("*.bmp|*.bmp|*.jpg|*.jpg|*.gif|*.gif||");
	CFileDialog dlg(FALSE, NULL, NULL, OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, lpFilter, this);
	if(dlg.DoModal() == IDOK)
	{
		WCHAR szOrig[MAX_PATH] = {0};
		WCHAR szSave[MAX_PATH] = {0};
#ifdef UNICODE
		_tcscpy(szOrig, m_szFile);
		_tcscpy(szSave, dlg.GetPathName());
#else
		MultiByteToWideChar(CP_ACP, 0, m_szFile, -1, szOrig, sizeof(szOrig)/sizeof(szOrig[0])); 
		MultiByteToWideChar(CP_ACP, 0, dlg.GetPathName(), -1, szSave, sizeof(szSave)/sizeof(szSave[0])); 
#endif
		//ȡ��Ҫ������ļ�����
		CLSID fmt = {0};
		int nFilter = dlg.m_ofn.nFilterIndex;
		switch(nFilter) 
		{
		case 3:
			wcscat(szSave, L".gif");
			GetImageCLSID(L"image/gif", &fmt);
			break;
		case 2:
			wcscat(szSave, L".jpg");
			GetImageCLSID(L"image/jpeg", &fmt);
			break;
		default:
			wcscat(szSave, L".bmp");
			GetImageCLSID(L"image/bmp", &fmt);
			break;
		}
		//���ļ�
		Image img(szOrig);
		//���ļ�����Ϊ�¸�ʽ��
		img.Save(szSave, &fmt);
	}	
}
