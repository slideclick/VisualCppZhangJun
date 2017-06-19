// DrawLineDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DrawLine.h"
#include "DrawLineDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawLineDlg dialog

CDrawLineDlg::CDrawLineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawLineDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDrawLineDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrawLineDlg)
	DDX_Control(pDX, IDC_PREVIEW, m_preview);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDrawLineDlg, CDialog)
	//{{AFX_MSG_MAP(CDrawLineDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawLineDlg message handlers

BOOL CDrawLineDlg::OnInitDialog()
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

void CDrawLineDlg::OnPaint() 
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
HCURSOR CDrawLineDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDrawLineDlg::GetNextValue(double &i, BOOL &bInc)
{
	//������һ����ɫ
	const double seed = 255*2/360.0;
	if(bInc)
	{
		i += seed;
		if(i > 255)
		{
			i = 255 - seed;
			bInc = FALSE;
		}
	}
	else
	{
		i -= seed;
		if(i < 0)
		{
			i = seed;
			bInc = TRUE;
		}
	}
}

void CDrawLineDlg::OnOK() 
{
	//��ȡ�߿�
	int nWidth = GetDlgItemInt(IDC_WIDTH, NULL, FALSE);
	//ȡ�ó�ʼ��ɫ
	CColorDialog dlg;
	if(dlg.DoModal() != IDOK)
		return;
	COLORREF cr = dlg.GetColor();
	//ȡ�ó�ʼ��ɫ������ɫ����
	double r, g, b;
	r = GetRValue(cr);
	g = GetGValue(cr);
	b = GetBValue(cr);

	BOOL bRInc = TRUE, bGInc = TRUE, bBInc = TRUE;

	//��ȡ�ؼ���С
	RECT rc;
	m_preview.GetClientRect(&rc);
	CDC *pDC = m_preview.GetDC();
	//�ͷžɵ�λͼ
	if(m_bmp.GetSafeHandle())
		m_bmp.DeleteObject();
	//��������λͼ�ͼ���DC
	m_bmp.CreateCompatibleBitmap(pDC, rc.right, rc.bottom);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	//�ͷſؼ�dc
	m_preview.ReleaseDC(pDC);
	//�����ڴ�DC���ڴ�λͼ
	CBitmap *pOldBmp = dc.SelectObject(&m_bmp);
	//���λͼ
	FillRect(dc.GetSafeHdc(), &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
	
	//�ı�dc����ϵ
	int nOldMapMode = SetMapMode(dc, MM_ANISOTROPIC);
	
	POINT ptViewOrg = {0};
	SIZE siViewExt = {0};
	SetViewportOrgEx(dc, rc.right/2, rc.bottom/2, &ptViewOrg);
	SetViewportExtEx(dc, rc.right, rc.bottom, &siViewExt);
	
	POINT ptWndOrg = {0};
	SIZE siWndExt ={0};
	SetWindowOrgEx(dc, 0, 0, &ptWndOrg);
	SetWindowExtEx(dc, rc.right, -rc.bottom, &siWndExt);
	
	//��ͼ�뾶
	double rd;
	if(rc.right <= rc.bottom)
		rd = rc.right/2.0;
	else
		rd = rc.bottom/2.0;
	//���ʶ���
	CPen pen ;
	CPen *pOldPen;
	//�Ƕ�
	double ra = 3.1415926 / 180.0;
	//ѭ��360��
	for(int i=0; i<360; i++)
	{
		//�õ����ε���ɫ
		GetNextValue(r, bRInc);
		GetNextValue(g, bGInc);
		GetNextValue(b, bBInc);
		//����һ�����ʲ�ѡ��DC
		pen.CreatePen(PS_SOLID, nWidth, RGB(r + 0.5, g + 0.5, b + 0.5));
		pOldPen = dc.SelectObject(&pen);
		//����
		dc.MoveTo(0, 0);
		dc.LineTo(sin(i * ra) * rd + 0.5, cos(i * ra) * rd + 0.5);
		//���ٻ��ʶ���
		dc.SelectObject(pOldPen);
		pen.DeleteObject();
	}
	//�ָ�����ϵ
	SetMapMode(dc, nOldMapMode);
	SetViewportOrgEx(dc, ptViewOrg.x, ptViewOrg.y, NULL);
	SetViewportExtEx(dc, siViewExt.cx, siViewExt.cy, NULL);
	SetWindowOrgEx(dc, ptWndOrg.x, ptWndOrg.y, NULL);
	SetWindowExtEx(dc, siWndExt.cx, siWndExt.cy, NULL);
	//�ͷ�DC����
	dc.SelectObject(pOldBmp);
	dc.DeleteDC();
	//�ڿؼ�����ʾλͼ
	HBITMAP hbmp = m_preview.SetBitmap(m_bmp);
	if(hbmp)
		DeleteObject(hbmp);
}

void CDrawLineDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//�ͷ�λͼ
	if(m_bmp.GetSafeHandle())
		m_bmp.DeleteObject();	
}
