// RegOCXDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RegOCX.h"
#include "RegOCXDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegOCXDlg dialog

CRegOCXDlg::CRegOCXDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegOCXDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegOCXDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRegOCXDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegOCXDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRegOCXDlg, CDialog)
	//{{AFX_MSG_MAP(CRegOCXDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_REG, OnBtnReg)
	ON_BN_CLICKED(IDC_BTN_UNREG, OnBtnUnreg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegOCXDlg message handlers

BOOL CRegOCXDlg::OnInitDialog()
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

void CRegOCXDlg::OnPaint() 
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
HCURSOR CRegOCXDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//���������ť����Ӧ����
void CRegOCXDlg::OnBtnBrowse() 
{
	//��ʾһ�����ļ��Ի���������ļ�
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, 
		_T("*.ocx|*.ocx|*.dll|*.dll|*.*||*.*||"), this);
	if (dlg.DoModal() == IDOK) 
	{
		//����ѡ�ļ�·���������ı�����
		SetDlgItemText(IDC_EDT_FILENAME, dlg.GetPathName());
	}
}
//��ע�ᡱ��ť����Ӧ����
void CRegOCXDlg::OnBtnReg() 
{
	RegProc(TRUE);
}
//��ע������ť����Ӧ����
void CRegOCXDlg::OnBtnUnreg() 
{
	RegProc(FALSE);
}
//ʵ�ʵ�ע�����
BOOL CRegOCXDlg::RegProc(BOOL bReg)
{
	//��ȡ�û�������ļ���
	TCHAR szFilename[MAX_PATH] = {0};
	GetDlgItemText(IDC_EDT_FILENAME, szFilename, MAX_PATH);
	if(*szFilename == _T('\0'))
	{
		AfxMessageBox(_T("�������ļ�����"));
		return FALSE;
	}
	//�����ļ�
	BOOL bRet = FALSE;
	TCHAR szErrMsg[256] = {0};
	HINSTANCE hMod = LoadLibrary(szFilename);
	if(hMod != NULL)
	{
		//�ļ����سɹ���ȡ����ע���ע�������ĵ�ַ
		FARPROC lpDllEntryPoint; 
		lpDllEntryPoint = GetProcAddress(hMod, 
			bReg?_T("DllRegisterServer"):_T("DllUnregisterServer"));	
		if(lpDllEntryPoint != NULL)
		{
			//���ú���
			HRESULT hr = ( (*lpDllEntryPoint)() );
			if(hr != S_OK)
			{
				_stprintf(szErrMsg, _T("ע��/ע���ļ�ʧ�ܣ�0x%.8X"), hr);
				AfxMessageBox(szErrMsg);
			}
			else
			{
				AfxMessageBox(_T("ע��/ע���ļ��ɹ���"));
				bRet = TRUE;
			}
		}
		else
		{
			AfxMessageBox(_T("�޷��ڸ��ļ����ҵ�ע�ắ����"));
		}
		//�ͷż��ص�ģ��
		FreeLibrary(hMod);
	}
	else
	{
		DWORD dwErr = GetLastError();
		_stprintf(szErrMsg, _T("�����ļ�ʧ��:%d."), dwErr);
		AfxMessageBox(szErrMsg);
	}
	return bRet;
}