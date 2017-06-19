// RichEditDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RichEditDemo.h"
#include "RichEditDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRichEditDemoDlg dialog

CRichEditDemoDlg::CRichEditDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRichEditDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRichEditDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRichEditDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRichEditDemoDlg)
	DDX_Control(pDX, IDC_EDIT, m_edit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRichEditDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CRichEditDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_COLOR, OnBtnColor)
	ON_BN_CLICKED(IDC_BTN_FONT, OnBtnFont)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_LOAD, OnBtnLoad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRichEditDemoDlg message handlers

BOOL CRichEditDemoDlg::OnInitDialog()
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

void CRichEditDemoDlg::OnPaint() 
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
HCURSOR CRichEditDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//����ɫ����ť����Ӧ����
void CRichEditDemoDlg::OnBtnColor() 
{
	//���岢��ʼ�����ָ�ʽ�ṹ
	CHARFORMAT cf = {0};
	cf.cbSize = sizeof(cf);
	//ȡ���ı���ǰ���ֵĸ�ʽ
	m_edit.GetSelectionCharFormat(cf);
	//������ɫ�Ի��򣬲���ȡ�õ����ָ�ʽ��ʼ���Ի���
	CColorDialog dlg(cf.crTextColor, CC_FULLOPEN, this);
	//��ʾ�Ի���ѡ����ɫ
	if(dlg.DoModal() == IDOK)
	{
		//ȡ���û���ѡ��ɫ
		cf.crTextColor = dlg.GetColor();
		//���ı���ʽ��Ϣ���õ��ı���ǰ�ı�
		cf.dwMask = CFM_COLOR;
		cf.dwEffects = 0;
		m_edit.SetSelectionCharFormat(cf);
	}
}
//�����塱��ť����Ӧ����
void CRichEditDemoDlg::OnBtnFont() 
{
	//���岢��ʼ�����ָ�ʽ�ṹ
	CHARFORMAT cf = {0};
	cf.cbSize = sizeof(cf);
	//ȡ���ı���ǰ���ֵĸ�ʽ
	m_edit.GetSelectionCharFormat(cf);
	//��������Ի��򣬲���ȡ�õ����ָ�ʽ��ʼ���Ի���
	CFontDialog dlg(cf);
	//��ʾ�Ի���ѡ��������Ϣ
	if(dlg.DoModal() == IDOK)
	{
		//ȡ���û���ѡ������Ϣ
		dlg.GetCharFormat(cf);
		//���ı���ʽ��Ϣ���õ��ı���ǰ�ı�
		cf.dwMask &= ~CFM_COLOR;
		m_edit.SetSelectionCharFormat(cf);
	}
}
//�����桱��ť����Ӧ����
void CRichEditDemoDlg::OnBtnSave() 
{
	//��ʾһ�������ļ��Ի����Ի�ȡ�ļ���
	CFileDialog dlg(FALSE, _T("rtf"), NULL, 
		OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, 
		_T("*.rtf|*.rtf|*.*|*.*||"), this);
	if(dlg.DoModal() != IDOK)
		return;
	//�򿪻򴴽��ļ�
	CString strFile = dlg.GetPathName();
	CFile file;
	if(!file.Open(strFile, CFile::modeCreate | CFile::modeWrite))
	{
		AfxMessageBox(_T("�򿪻򴴽��ļ�ʧ�ܣ�"));
		return;
	}
	//���ɻص�����
	EDITSTREAM es = {0};
	es.dwCookie = (DWORD)&file;
	es.pfnCallback = StreamOutProc;
	//�����ļ���׺���ж�Ҫ����RTF��ʽ���Ǵ��ı���ʽ
	int nFormat ;
	if(_tcsicmp(dlg.GetFileExt(), _T("rtf")) == 0)
		nFormat = SF_RTF;
	else
		nFormat = SF_TEXT;
	//�ӿؼ���ȡ����
	m_edit.StreamOut(nFormat, es);
	//�ر��ļ�
	file.Close();
}
//���򿪡���ť����Ӧ����
void CRichEditDemoDlg::OnBtnLoad() 
{
	//��ʾһ�����ļ��Ի�����ѡ��Ҫ�򿪵��ļ�
	CFileDialog dlg(TRUE, NULL, NULL, 
		OFN_FILEMUSTEXIST, _T("*.rtf|*.rtf|*.*|*.*||"), this);
	if(dlg.DoModal() != IDOK)
		return;
	//���ļ�
	CString strFile = dlg.GetPathName();
	CFile file;
	if(!file.Open(strFile, CFile::modeRead))
	{
		AfxMessageBox(_T("���ļ�ʧ�ܣ�"));
		return;
	}
	//����ı���
	m_edit.SetWindowText(_T(""));
	//���ɻص�����
	EDITSTREAM es = {0};
	es.dwCookie = (DWORD)&file;
	es.pfnCallback = StreamInProc;
	//�ж��ļ���׺���Ծ����Ƿ����RTF��ʽ�ı�
	int nFormat;
	if(_tcsicmp(dlg.GetFileExt(), _T("rtf")) == 0)
		nFormat = SF_RTF;
	else
		nFormat = SF_TEXT;
	//��ؼ���������
	m_edit.StreamIn(nFormat, es);
	//�ر��ļ�
	file.Close();
}
//��ؼ��������ݵĻص�����
DWORD CALLBACK CRichEditDemoDlg::StreamInProc(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	//ȡ�ô��������ļ�ָ��
	CFile *pFile = (CFile *)dwCookie;
	//���ļ���ȡ���ݵ�����
	*pcb = pFile->Read(pbBuff, cb);
	return 0;
}
//�ӿؼ��������ݵĻص�����
DWORD CALLBACK CRichEditDemoDlg::StreamOutProc(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	//ȡ�ô��������ļ�ָ��
	CFile *pFile = (CFile *)dwCookie;
	//���ļ���д������
	pFile->Write(pbBuff, cb);
	*pcb = cb;
	return 0;
}