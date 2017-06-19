// MultiLanguage.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MultiLanguage.h"
#include "MultiLanguageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiLanguageApp

BEGIN_MESSAGE_MAP(CMultiLanguageApp, CWinApp)
	//{{AFX_MSG_MAP(CMultiLanguageApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiLanguageApp construction

CMultiLanguageApp::CMultiLanguageApp()
{
	//得到INI文件的路径
	TCHAR szIni[MAX_PATH] = {0};
	GetModuleFileName(NULL, szIni, MAX_PATH);
	_tcscat(szIni, _T(".ini"));
	//获取语言设置
	UINT nLastID = GetPrivateProfileInt(_T("Language"), _T("LangID"), 0, szIni);
	//如果指定了语言，修改当前线程的区域
	if(nLastID > 0)
		SetThreadLocale(MAKELCID(MAKELANGID(nLastID, SUBLANG_DEFAULT), SORT_DEFAULT)); //LANG_ENGLISH=0x09;LANG_CHINESE=0x04;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMultiLanguageApp object

CMultiLanguageApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMultiLanguageApp initialization

BOOL CMultiLanguageApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CMultiLanguageDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
