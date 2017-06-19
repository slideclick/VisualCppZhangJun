#if !defined(AFX_INPUTDLG1_H__B6BA4318_62C5_46C6_9503_7A9770E0A8EF__INCLUDED_)
#define AFX_INPUTDLG1_H__B6BA4318_62C5_46C6_9503_7A9770E0A8EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputDlg1.h : header file
//

#include "DlgTemplet.h"
/////////////////////////////////////////////////////////////////////////////
// CInputDlg dialog

class CInputDlg : public CDialog
{
// Construction
public:
	CInputDlg(CWnd* pParent, LPCTSTR lpTitle, LPCTSTR lpTip, LPCTSTR lpDef = NULL);   // standard constructor
	LPCTSTR GetInputText();

// Implementation
protected:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//DECLARE_MESSAGE_MAP()
protected:
	enum{IDC_EDT_INPUT = 100, IDC_STATIC_ICON};
	CDlgTemplet m_templet;
	CString m_strInput;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTDLG1_H__B6BA4318_62C5_46C6_9503_7A9770E0A8EF__INCLUDED_)
