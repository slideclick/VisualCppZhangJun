// ComboBoxDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ComboBoxDemo.h"
#include "ComboBoxDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboBoxDemoDlg dialog

CComboBoxDemoDlg::CComboBoxDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComboBoxDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComboBoxDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComboBoxDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComboBoxDemoDlg)
	DDX_Control(pDX, IDC_LST_DEMO, m_lst_demo);
	DDX_Control(pDX, IDC_CMB_DEMO, m_cmb_demo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CComboBoxDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CComboBoxDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboBoxDemoDlg message handlers

BOOL CComboBoxDemoDlg::OnInitDialog()
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

void CComboBoxDemoDlg::OnPaint() 
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
HCURSOR CComboBoxDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//“添加”按钮的响应函数
void CComboBoxDemoDlg::OnBtnAdd() 
{
	CString strText;
	//取得用户输入
	GetDlgItemText(IDC_EDT_TEXT, strText);
	if(strText.GetLength() > 0)
	{
		//向组合框添加字符串
		m_cmb_demo.AddString(strText);
		//选中刚刚添加的项
		m_cmb_demo.SetCurSel(m_cmb_demo.GetCount() - 1);
		//向列表框添加字符串
		m_lst_demo.AddString(strText);
		//选中刚刚添加的项
		m_lst_demo.SetCurSel(m_lst_demo.GetCount() - 1);
	}
}
//“删除”按钮的响应函数
void CComboBoxDemoDlg::OnBtnDelete() 
{
	int nIndex;
	//取得组合框的当前所选，如果nIndex等于-1，代表没有选中项
	nIndex = m_cmb_demo.GetCurSel();
	if(nIndex > -1)
	{
		//如果有选中项，删除该项
		m_cmb_demo.DeleteString(nIndex);
		//让控件选中下一项
		if(nIndex < m_cmb_demo.GetCount())
			m_cmb_demo.SetCurSel(nIndex);
		else
			m_cmb_demo.SetCurSel(0);
	}
	//取得列表框的当前所选
	nIndex = m_lst_demo.GetCurSel();
	if(nIndex > -1)
	{
		//如果有选中项，删除该项
		m_lst_demo.DeleteString(nIndex);
		//让控件选中下一项
		if(nIndex < m_lst_demo.GetCount())
			m_lst_demo.SetCurSel(nIndex);
		else
			m_lst_demo.SetCurSel(0);
	}
}
