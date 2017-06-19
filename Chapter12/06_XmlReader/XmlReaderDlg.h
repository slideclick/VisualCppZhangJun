// XmlReaderDlg.h : header file
//

#if !defined(AFX_XMLREADERDLG_H__9107235F_8D04_408A_AE0B_2FEE0C622454__INCLUDED_)
#define AFX_XMLREADERDLG_H__9107235F_8D04_408A_AE0B_2FEE0C622454__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXmlReaderDlg dialog

class CXmlReaderDlg : public CDialog
{
// Construction
public:
	CXmlReaderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXmlReaderDlg)
	enum { IDD = IDD_XMLREADER_DIALOG };
	CTreeCtrl	m_tree;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXmlReaderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXmlReaderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnSave();
	afx_msg void OnAdd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void AddTreeNodes(IXMLDOMNodePtr pXmlNode, HTREEITEM hTreeItem);
	void AddXmlNodes(IXMLDOMElementPtr pXmlNode, HTREEITEM hTreeItem);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMLREADERDLG_H__9107235F_8D04_408A_AE0B_2FEE0C622454__INCLUDED_)
