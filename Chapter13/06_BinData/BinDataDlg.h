// BinDataDlg.h : header file
//

#if !defined(AFX_BINDATADLG_H__8918BA78_3D8B_47F1_A666_4CB9976E2AC4__INCLUDED_)
#define AFX_BINDATADLG_H__8918BA78_3D8B_47F1_A666_4CB9976E2AC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//����ADO���Ϳ⡣
//ע�⣬��ͬ�ļ����������ado���Ϳ�����λ�ÿ��ܲ�ͬ���������޸ı��д���
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
	//��ͼƬ��ʾ��ͼƬ�ؼ���
	void ShowImage(LPCTSTR lpFilename);
	//��ȡĳ��·�����ϲ�·��
	void GetPathParent(LPTSTR lpPath, int nCount);
	//�����ݿ��ȡ���ݣ�����ʾ���б�ؼ�
	void GetDataset();
	//�ͷų��������д�����GDI����
	void FreeGdiObject();
	//�����ݿ��ȡĳ����¼
	void ReadRecordPhoto(int nID);
	//�����ݱ��浽���ݿ�
	void SaveRecordPhoto(int nID);
// Implementation
protected:
	//���ݿ����Ӷ���
	_ConnectionPtr	m_pConnection;	
	//���浱ǰͼƬ·��
	TCHAR m_szPhoto[MAX_PATH];
	//ͼƬ��ʱ���·��
	TCHAR m_szTempPath[MAX_PATH];
	//��ǰԤ����ͼƬ���
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
