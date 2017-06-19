// DlgSkinDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DlgSkinDemo.h"
#include "DlgSkinDemoDlg.h"
#include "dlgskin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSkinDemoApp

BEGIN_MESSAGE_MAP(CDlgSkinDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CDlgSkinDemoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSkinDemoApp construction

CDlgSkinDemoApp::CDlgSkinDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDlgSkinDemoApp object

CDlgSkinDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDlgSkinDemoApp initialization

BOOL CDlgSkinDemoApp::InitInstance()
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
	//����Ƥ��
	CDlgSkin::SetSkin(RGB(188, 197, 230));
	
	CDlgSkinDemoDlg dlg;
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
	//�ͷ�Ƥ��
	CDlgSkin::FreeSkin();		
	return FALSE;
}
