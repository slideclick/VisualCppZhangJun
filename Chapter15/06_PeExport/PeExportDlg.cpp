// PeExportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PeExport.h"
#include "PeExportDlg.h"
#include <Dbghelp.h>

#pragma comment(lib, "Dbghelp.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPeExportDlg dialog

CPeExportDlg::CPeExportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPeExportDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPeExportDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPeExportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPeExportDlg)
	DDX_Control(pDX, IDC_LST_FUNCTIONS, m_lst_Functions);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPeExportDlg, CDialog)
	//{{AFX_MSG_MAP(CPeExportDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPeExportDlg message handlers

BOOL CPeExportDlg::OnInitDialog()
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

void CPeExportDlg::OnPaint() 
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
HCURSOR CPeExportDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPeExportDlg::OnOK() 
{
	//获取一个DLL文件路径
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, _T("*.dll|*.dll||"), this);
	if(dlg.DoModal() != IDOK)
		return;
	CString strFile = dlg.GetPathName();
	CFile file;
	//打开文件
	if(!file.Open(strFile, CFile::modeRead))
	{
		AfxMessageBox(_T("打开文件失败！"));
		return;
	}
	//并读取文件至内存缓冲
	DWORD dwLen = file.GetLength();
	byte *pBuf = new byte[dwLen];
	DWORD dwRead, dwCount = 0;
	while(TRUE)
	{
		dwRead = file.Read(pBuf, dwLen - dwCount);
		dwCount += dwRead;
		if(dwRead == 0 || dwRead == dwLen)
			break;
	}
	file.Close();
	ASSERT(dwCount == dwLen);
	//检测是否合法的可执行文件
	PIMAGE_DOS_HEADER pDosHdr = (PIMAGE_DOS_HEADER)pBuf;
	if(*pBuf != 'M' || *(pBuf + 1) != 'Z')
	{
		AfxMessageBox(_T("所选文件不是可执行文件！"));
		delete []pBuf;
		return;
	}
	//通过DOS文件头得到PE文件头
	PIMAGE_NT_HEADERS pNtHdrs = 
		(PIMAGE_NT_HEADERS)((LONG)pDosHdr + (LONG)pDosHdr->e_lfanew);
	if(pNtHdrs->Signature != IMAGE_NT_SIGNATURE)
	{
		AfxMessageBox(_T("不支持的文件格式！"));
		delete []pBuf;
		return;
	}
	//获取输出表
	PIMAGE_EXPORT_DIRECTORY pExport = 
		(PIMAGE_EXPORT_DIRECTORY)pNtHdrs->
		OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	ASSERT(pExport);
	if(pExport == NULL)
	{
		AfxMessageBox(_T("无法识别文件格式！"));
		delete []pBuf;
		return;
	}
	//获取输出表的虚地址所对应的内存地址
	pExport = (PIMAGE_EXPORT_DIRECTORY)ImageRvaToVa(
		pNtHdrs, pDosHdr, (ULONG)pExport, NULL);		
	//获取导出函数个数
	DWORD dwExports = pExport->NumberOfNames;
	//
	TCHAR szNum[128] = {0};
	_stprintf(szNum, _T("共有导出函数:%d个."), dwExports);
	SetDlgItemText(IDC_NUM, szNum);
	//获取导出函数名称
	DWORD **ppdwNames = (DWORD **)pExport->AddressOfNames;	
	ppdwNames = (DWORD **)ImageRvaToVa(
		pNtHdrs, pDosHdr, (ULONG)ppdwNames, 0);
	char *szName;
	for(unsigned i=0; i < dwExports; i++)
	{
		szName = (LPSTR)ImageRvaToVa(pNtHdrs, pDosHdr, (DWORD)*ppdwNames, 0);
		m_lst_Functions.AddString(szName);
		ppdwNames++;
	}
	//释放缓冲内存
	delete []pBuf;
}
