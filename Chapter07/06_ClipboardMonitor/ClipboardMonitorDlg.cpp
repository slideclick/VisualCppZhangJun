// ClipboardMonitorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClipboardMonitor.h"
#include "ClipboardMonitorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClipboardMonitorDlg dialog

CClipboardMonitorDlg::CClipboardMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClipboardMonitorDlg::IDD, pParent), m_hwndNextViewer(NULL)
{
	//{{AFX_DATA_INIT(CClipboardMonitorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClipboardMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClipboardMonitorDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClipboardMonitorDlg, CDialog)
	//{{AFX_MSG_MAP(CClipboardMonitorDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_CHANGECBCHAIN()
	ON_WM_DRAWCLIPBOARD()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipboardMonitorDlg message handlers

BOOL CClipboardMonitorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//�������������а������Ϣ��
	m_hwndNextViewer = SetClipboardViewer(); 
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClipboardMonitorDlg::OnPaint() 
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
		//��ʾ���а�������
		DrawClipboard();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClipboardMonitorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClipboardMonitorDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//����Ϣ���Ƴ�������
	ChangeClipboardChain(m_hwndNextViewer); 
}

//���а���Ϣ�������仯
void CClipboardMonitorDlg::OnChangeCbChain(HWND hWndRemove, HWND hWndAfter) 
{
	CDialog::OnChangeCbChain(hWndRemove, hWndAfter);
	
	if (hWndRemove == m_hwndNextViewer) 
		m_hwndNextViewer = hWndAfter; 
	else if (m_hwndNextViewer != NULL) 
		::SendMessage(m_hwndNextViewer, WM_CHANGECBCHAIN, 
			(WPARAM)hWndRemove, (LPARAM)hWndAfter); 
	
}
//���а����ݷ����仯
void CClipboardMonitorDlg::OnDrawClipboard() 
{
	CDialog::OnDrawClipboard();
	//ˢ�±�����
	InvalidateRect(NULL, TRUE);
	//����Ϣת������Ϣ���е���һ������
	::SendMessage(m_hwndNextViewer, WM_DRAWCLIPBOARD, 0, 0); 
}

void CClipboardMonitorDlg::DrawClipboard()
{
	PAINTSTRUCT ps;
	HDC hdc = ::BeginPaint(m_hWnd, &ps); 
	RECT rc = {0};
	GetClientRect(&rc);
	//�������Ȥ�ĸ�ʽ�б�
	static UINT auPriorityList[] = 
	{ 
        CF_OWNERDISPLAY, 
		CF_TEXT, 
		CF_ENHMETAFILE, 
		CF_BITMAP 
    }; 
	//��ȡ���а����ݸ�ʽ
    int nFmt = GetPriorityClipboardFormat(auPriorityList, 4); 
	//��ʾ����
	switch (nFmt) 
	{ 
	//�Ի����ͣ�������ӵ���ߴ�����ʾ
	case CF_OWNERDISPLAY: 
		{
			//ȡ�ü��а�����������
			HWND hwndOwner = ::GetClipboardOwner(); 
			HGLOBAL hgbPs = GlobalAlloc(GMEM_MOVEABLE, sizeof(PAINTSTRUCT)); 
			LPPAINTSTRUCT pps = (LPPAINTSTRUCT)GlobalLock(hgbPs);
			memcpy(pps, &ps, sizeof(PAINTSTRUCT)); 
			GlobalUnlock(hgbPs); 
			//���ͻ�����Ϣ
			::SendMessage(hwndOwner, WM_PAINTCLIPBOARD, 
				(WPARAM)m_hWnd, (LPARAM)hgbPs); 
			//�ͷ�����
			GlobalFree(hgbPs); 
		}
		break; 
	//λͼ��ֱ�ӻ��Ƶ�����
	case CF_BITMAP: 
		{
			//��������DC
			HDC hdcMem = CreateCompatibleDC(hdc); 
			if (hdcMem != NULL) 
			{ 
				//�򿪼��а�
				if (OpenClipboard()) 
				{ 
					//�õ�λͼ
					HBITMAP hBmp = (HBITMAP) GetClipboardData(nFmt); 
					HBITMAP hOld = (HBITMAP)SelectObject(hdcMem, hBmp); 
					//����λͼ
					BitBlt(hdc, 0, 0, rc.right, rc.bottom, 
						hdcMem, 0, 0, SRCCOPY); 
					SelectObject(hdcMem, hOld);
					//�رռ��а�
					CloseClipboard(); 
				} 
				DeleteDC(hdcMem); 
			} 
		}
		break; 
	//�ı�����
	case CF_TEXT: 
		//�򿪼��а�
		if (OpenClipboard()) 
		{ 
			//�õ��ı�
			HGLOBAL hgbText = GetClipboardData(nFmt); 
			LPCSTR lpstr = (LPCSTR)GlobalLock(hgbText); 
			//�����ı�������
			DrawText(hdc, lpstr, -1, &rc, DT_LEFT); 
			//�ر�����
			GlobalUnlock(hgbText); 
			CloseClipboard(); 
		} 
		break; 
	//��ǿ��ͼԪ�ļ�
	case CF_ENHMETAFILE: 
		//�򿪼��а�
		if (OpenClipboard()) 
		{ 
			//�õ�����
			HENHMETAFILE hemf = (HENHMETAFILE)GetClipboardData(nFmt); 
			//��ʾ�ļ�����
			PlayEnhMetaFile(hdc, hemf, &rc); 
			//�رռ��а�
			CloseClipboard(); 
		} 
		break; 
	//û��ȡ������
	case 0: 
		DrawText(hdc, _T("*���а���Ŀǰ�����ݡ�"), -1, 
			&rc, DT_CENTER | DT_SINGLELINE | 
			DT_VCENTER); 
		break; 
	//��������
	default: 
		DrawText(hdc, _T("*���а��ϵ����ݲ�����ʾ��"), -1, 
			&rc, 
			DT_CENTER | DT_SINGLELINE | DT_VCENTER); 
	} 
	EndPaint(&ps); 
}