// BinDataDlg.h : header file
//

#if !defined(AFX_BINDATADLG_H__8918BA78_3D8B_47F1_A666_4CB9976E2AC4__INCLUDED_)
#define AFX_BINDATADLG_H__8918BA78_3D8B_47F1_A666_4CB9976E2AC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//引入ADO类型库。
//注意，不同的计算机环境，ado类型库所在位置可能不同，请酌情修改本行代码
#import "d:\Program files\common files\system\ado\msado15.dll"  no_namespace rename ("EOF", "adoEOF")

/////////////////////////////////////////////////////////////////////////////
// CBinDataDlg dialog

class CBinDataDlg : public CDialog
{
// Construction
public:
	CBinDataDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBinDataDlg)
	enum { IDD = IDD_BINDATA_DIALOG };
	CListCtrl	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBinDataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	//将图片显示在图片控件上
	void ShowImage(LPCTSTR lpFilename);
	//获取某个路径的上层路径
	void GetPathParent(LPTSTR lpPath, int nCount);
	//从数据库获取数据，并显示在列表控件
	void GetDataset();
	//释放程序运行中创建的GDI对象
	void FreeGdiObject();
	//从数据库读取某条记录
	void ReadRecordPhoto(int nID);
	//将数据保存到数据库
	void SaveRecordPhoto(int nID);
// Implementation
protected:
	//数据库连接对象
	_ConnectionPtr	m_pConnection;	
	//保存当前图片路径
	TCHAR m_szPhoto[MAX_PATH];
	//图片临时存放路径
	TCHAR m_szTempPath[MAX_PATH];
	//当前预览的图片句柄
	HBITMAP m_hPhoto;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBinDataDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnEdit();
	afx_msg void OnBtnBrowse();
	afx_msg void OnDestroy();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BINDATADLG_H__8918BA78_3D8B_47F1_A666_4CB9976E2AC4__INCLUDED_)
