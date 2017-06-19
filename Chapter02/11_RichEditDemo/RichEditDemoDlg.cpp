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
//“颜色”按钮的响应函数
void CRichEditDemoDlg::OnBtnColor() 
{
	//定义并初始化文字格式结构
	CHARFORMAT cf = {0};
	cf.cbSize = sizeof(cf);
	//取得文本框当前文字的格式
	m_edit.GetSelectionCharFormat(cf);
	//创建颜色对话框，并用取得的文字格式初始化对话框。
	CColorDialog dlg(cf.crTextColor, CC_FULLOPEN, this);
	//显示对话框，选择颜色
	if(dlg.DoModal() == IDOK)
	{
		//取得用户所选颜色
		cf.crTextColor = dlg.GetColor();
		//将文本格式信息设置到文本框当前文本
		cf.dwMask = CFM_COLOR;
		cf.dwEffects = 0;
		m_edit.SetSelectionCharFormat(cf);
	}
}
//“字体”按钮的响应函数
void CRichEditDemoDlg::OnBtnFont() 
{
	//定义并初始化文字格式结构
	CHARFORMAT cf = {0};
	cf.cbSize = sizeof(cf);
	//取得文本框当前文字的格式
	m_edit.GetSelectionCharFormat(cf);
	//创建字体对话框，并用取得的文字格式初始化对话框。
	CFontDialog dlg(cf);
	//显示对话框，选择字体信息
	if(dlg.DoModal() == IDOK)
	{
		//取得用户所选字体信息
		dlg.GetCharFormat(cf);
		//将文本格式信息设置到文本框当前文本
		cf.dwMask &= ~CFM_COLOR;
		m_edit.SetSelectionCharFormat(cf);
	}
}
//“保存”按钮的响应函数
void CRichEditDemoDlg::OnBtnSave() 
{
	//显示一个保存文件对话框，以获取文件名
	CFileDialog dlg(FALSE, _T("rtf"), NULL, 
		OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, 
		_T("*.rtf|*.rtf|*.*|*.*||"), this);
	if(dlg.DoModal() != IDOK)
		return;
	//打开或创建文件
	CString strFile = dlg.GetPathName();
	CFile file;
	if(!file.Open(strFile, CFile::modeCreate | CFile::modeWrite))
	{
		AfxMessageBox(_T("打开或创建文件失败！"));
		return;
	}
	//生成回调数据
	EDITSTREAM es = {0};
	es.dwCookie = (DWORD)&file;
	es.pfnCallback = StreamOutProc;
	//根据文件后缀，判断要保存RTF格式还是纯文本格式
	int nFormat ;
	if(_tcsicmp(dlg.GetFileExt(), _T("rtf")) == 0)
		nFormat = SF_RTF;
	else
		nFormat = SF_TEXT;
	//从控件获取数据
	m_edit.StreamOut(nFormat, es);
	//关闭文件
	file.Close();
}
//“打开”按钮的响应函数
void CRichEditDemoDlg::OnBtnLoad() 
{
	//显示一个打开文件对话框，以选择要打开的文件
	CFileDialog dlg(TRUE, NULL, NULL, 
		OFN_FILEMUSTEXIST, _T("*.rtf|*.rtf|*.*|*.*||"), this);
	if(dlg.DoModal() != IDOK)
		return;
	//打开文件
	CString strFile = dlg.GetPathName();
	CFile file;
	if(!file.Open(strFile, CFile::modeRead))
	{
		AfxMessageBox(_T("打开文件失败！"));
		return;
	}
	//清空文本框
	m_edit.SetWindowText(_T(""));
	//生成回调数据
	EDITSTREAM es = {0};
	es.dwCookie = (DWORD)&file;
	es.pfnCallback = StreamInProc;
	//判断文件后缀，以决定是否加载RTF格式文本
	int nFormat;
	if(_tcsicmp(dlg.GetFileExt(), _T("rtf")) == 0)
		nFormat = SF_RTF;
	else
		nFormat = SF_TEXT;
	//向控件传输数据
	m_edit.StreamIn(nFormat, es);
	//关闭文件
	file.Close();
}
//向控件传输数据的回调函数
DWORD CALLBACK CRichEditDemoDlg::StreamInProc(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	//取得传进来的文件指针
	CFile *pFile = (CFile *)dwCookie;
	//从文件读取数据到缓冲
	*pcb = pFile->Read(pbBuff, cb);
	return 0;
}
//从控件传输数据的回调函数
DWORD CALLBACK CRichEditDemoDlg::StreamOutProc(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	//取得传进来的文件指针
	CFile *pFile = (CFile *)dwCookie;
	//向文件中写入数据
	pFile->Write(pbBuff, cb);
	*pcb = cb;
	return 0;
}