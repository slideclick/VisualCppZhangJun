// RollTextDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RollText.h"
#include "RollTextDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRollTextDlg dialog

CRollTextDlg::CRollTextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRollTextDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRollTextDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_crText = RGB(255, 255, 255);
	m_crBk = RGB(0, 0, 0);
}

void CRollTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRollTextDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRollTextDlg, CDialog)
	//{{AFX_MSG_MAP(CRollTextDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_COLOR, OnBtnColor)
	ON_BN_CLICKED(IDC_BTN_BK, OnBtnBk)
	ON_BN_CLICKED(IDC_BTN_FONT, OnBtnFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRollTextDlg message handlers

BOOL CRollTextDlg::OnInitDialog()
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

void CRollTextDlg::OnPaint() 
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
HCURSOR CRollTextDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRollTextDlg::OnOK() 
{
	//��ʼ������Ļ���������Ϊɳ©
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	//��ȡ����ؼ���λ�úʹ�С
	RECT rc = {0};
	CWnd *pWnd = GetDlgItem(IDC_CANVAS);
	pWnd->GetClientRect(&rc);
	//��ȡ����ؼ���DC
	CDC *pDC = pWnd->GetDC();
	//��ȡҪ��ʾ���ı�
	CString str;
	GetDlgItemText(IDC_EDT_TEXT, str);
	//����һ���ڴ�DC��λͼ���ڻ����ı�
	CDC mdc;
	mdc.CreateCompatibleDC(pDC);
	CBitmap mbmp;
	mbmp.CreateCompatibleBitmap(pDC, rc.right, rc.bottom);
	CBitmap *pOldBmp = mdc.SelectObject(&mbmp);
	//����������ɫ
	mdc.SetTextColor(m_crText);
	//��������û�б���
	mdc.SetBkMode(TRANSPARENT);
	//�������ֻ��ƺ�ĳߴ�
	RECT rcText = {0};
	mdc.DrawText(str, &rcText, DT_LEFT | DT_SINGLELINE | DT_CALCRECT);
	int y = (rc.bottom - rcText.bottom)/2;
	//������ˢ
	CBrush brush;
	brush.CreateSolidBrush(m_crBk);
	//ѭ���������
	for(int i=rc.right; i>-rcText.right; i--)
	{
		//���DC
		mdc.FillRect(&rc, &brush);
		//�����ı�����λ��
		mdc.TextOut(i, y, str);
		//���ڴ�λͼ���Ƶ�����ؼ�
		pDC->BitBlt(0, 0, rc.right, rc.bottom, &mdc, 0, 0, SRCCOPY);
		Sleep(100);
	}
	//�ͷű�����ˢ
	brush.DeleteObject();
	//�ͷſؼ�DC
	pWnd->ReleaseDC(pDC);
	//�ͷ��ڴ�DC��λͼ
	mdc.SelectObject(pOldBmp);
	mdc.DeleteDC();
	mbmp.DeleteObject();
	//�ָ����ָ��
	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

void CRollTextDlg::OnBtnColor() 
{
	//�����ı���ɫ
	CColorDialog dlg(m_crText);
	if(dlg.DoModal() == IDOK)
	{
		m_crText = dlg.GetColor();
	}
}

void CRollTextDlg::OnBtnBk() 
{
	//���ñ�����ɫ
	CColorDialog dlg(m_crBk);
	if(dlg.DoModal() == IDOK)
	{
		m_crBk = dlg.GetColor();
	}
}

void CRollTextDlg::OnBtnFont() 
{
	//��������
	LOGFONT lf = {0};
	if(m_font.GetSafeHandle())
		m_font.GetLogFont(&lf);
	CFontDialog dlg(&lf);
	if(dlg.DoModal() == IDOK)
	{
		dlg.GetCurrentFont(&lf);
		if(m_font.GetSafeHandle())
			m_font.DeleteObject();
		m_font.CreateFontIndirect(&lf);
	}
	
}
