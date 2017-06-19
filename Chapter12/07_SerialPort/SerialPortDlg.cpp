// SerialPortDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SerialPort.h"
#include "SerialPortDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_COMM_NOTIFY (WM_USER + 110)
/////////////////////////////////////////////////////////////////////////////
// CSerialPortDlg dialog

CSerialPortDlg::CSerialPortDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSerialPortDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSerialPortDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSerialPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSerialPortDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSerialPortDlg, CDialog)
	//{{AFX_MSG_MAP(CSerialPortDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_OPEN, OnBtnOpen)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_COMM_NOTIFY, OnCommNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialPortDlg message handlers

BOOL CSerialPortDlg::OnInitDialog()
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

void CSerialPortDlg::OnPaint() 
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
HCURSOR CSerialPortDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//写入数据
void CSerialPortDlg::OnBtnWrite() 
{
	//得到输入的文本
	CString str;
	GetDlgItemText(IDC_EDT_WRITE, str);
	//将数据写入串口
	int nLen = (str.GetLength() + 1) * sizeof(TCHAR)
	m_com.WriteData((byte *)(LPCTSTR)str, nLen);
}
//打开串口
void CSerialPortDlg::OnBtnOpen() 
{
	//得到所选串口号
	CComboBox *pCom = (CComboBox *)GetDlgItem(IDC_CMB_COM);
	CString strCom;
	pCom->GetWindowText(strCom);
	//打开串口
	int nResult = m_com.OpenCom(strCom, 64, WM_COMM_NOTIFY, m_hWnd);
	if(nResult != Succeed)
	{
		AfxMessageBox(_T("打开串口错误。"));
	}
	else
	{
		GetDlgItem(IDC_BTN_WRITE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_OPEN)->EnableWindow(FALSE);
	}
}
//串口数据接收事件
void CSerialPortDlg::OnCommNotify(WPARAM wp, LPARAM lp)
{
	//得到文本内容
	LPCTSTR pBuf = (LPCTSTR)wp;
	//将文本写入文本框
	CString str;
	GetDlgItemText(IDC_EDT_READ, str);
	str += pBuf;
	SetDlgItemText(IDC_EDT_READ, str);
}

void CSerialPortDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//关闭串口
	m_com.CloseCom();	
}
