// SysKeyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SysKey.h"
#include "SysKeyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSysKeyDlg dialog

CSysKeyDlg::CSysKeyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysKeyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSysKeyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSysKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysKeyDlg)
	DDX_Control(pDX, IDC_CMB_VKEY, m_cmb_VKey);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSysKeyDlg, CDialog)
	//{{AFX_MSG_MAP(CSysKeyDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_CMB_VKEY, OnSelchangeCmbVkey)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysKeyDlg message handlers

BOOL CSysKeyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	int nIndex;
	//Ĭ��ѡ��
	nIndex = m_cmb_VKey.AddString(_T("��ѡ��"));
	m_cmb_VKey.SetItemData(nIndex, 0);
	//��Shift��
	nIndex = m_cmb_VKey.AddString(_T("��Shift��"));
	m_cmb_VKey.SetItemData(nIndex, VK_LSHIFT);
	//��Shift��
	nIndex = m_cmb_VKey.AddString(_T("��Shift��"));
	m_cmb_VKey.SetItemData(nIndex, VK_RSHIFT);
	//��Ctrl��
	nIndex = m_cmb_VKey.AddString(_T("��Ctrl��"));
	m_cmb_VKey.SetItemData(nIndex, VK_LCONTROL);
	//��Ctrl��
	nIndex = m_cmb_VKey.AddString(_T("��Ctrl��"));
	m_cmb_VKey.SetItemData(nIndex, VK_RCONTROL);
	//��Alt��
	nIndex = m_cmb_VKey.AddString(_T("��Alt��"));
	m_cmb_VKey.SetItemData(nIndex, VK_LMENU);
	//��Alt��
	nIndex = m_cmb_VKey.AddString(_T("��Alt��"));
	m_cmb_VKey.SetItemData(nIndex, VK_RMENU);
	//Tab��
	nIndex = m_cmb_VKey.AddString(_T("Tab��"));
	m_cmb_VKey.SetItemData(nIndex, VK_TAB);
	//��Win��
	nIndex = m_cmb_VKey.AddString(_T("��Win��"));
	m_cmb_VKey.SetItemData(nIndex, VK_LWIN);
	//��Win��
	nIndex = m_cmb_VKey.AddString(_T("��Win��"));
	m_cmb_VKey.SetItemData(nIndex, VK_RWIN);
	//����Ĭ��ѡ��
	m_cmb_VKey.SetCurSel(0);
	//����DLL
	m_hHookDll = LoadLibrary(_T("KBHookDll.dll"));
	m_proc = (SetVKeyProc)GetProcAddress(m_hHookDll, _T("SetVKey"));
	ASSERT(m_hHookDll && m_proc);
	if(m_proc == NULL || m_hHookDll == NULL)
		AfxMessageBox(_T("���ؼ���HOOKʧ�ܣ�"));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSysKeyDlg::OnPaint() 
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
HCURSOR CSysKeyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//��ѡ�������ĵ��¼�
void CSysKeyDlg::OnSelchangeCmbVkey() 
{
	if(m_proc) 
	{
		//��ȡ��ǰ��ѡ
		int nIndex = m_cmb_VKey.GetCurSel();
		//��ȡ�������
		DWORD dwData = m_cmb_VKey.GetItemData(nIndex);
		//���õ�DLL
		m_proc(dwData);
	}
}

void CSysKeyDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//�ͷ�DLL
	FreeLibrary(m_hHookDll);
}
