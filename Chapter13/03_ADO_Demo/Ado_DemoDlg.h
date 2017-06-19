// Ado_DemoDlg.h : header file
//

#if !defined(AFX_ADO_DEMODLG_H__C65C8FAF_A9B2_4588_8533_BB09C720467B__INCLUDED_)
#define AFX_ADO_DEMODLG_H__C65C8FAF_A9B2_4588_8533_BB09C720467B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//����ADO���Ϳ�
#import "d:\Program files\common files\system\ado\msado15.dll"  no_namespace rename ("EOF", "adoEOF") 


/////////////////////////////////////////////////////////////////////////////
// CAdo_DemoDlg dialog

class CAdo_DemoDlg : public CDialog
{
// Construction
public:
	CAdo_DemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAdo_DemoDlg)
	enum { IDD = IDD_ADO_DEMO_DIALOG };
	CListCtrl	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdo_DemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	//��ȡĳ��·�����ϲ�·��
	void GetPathParent(LPTSTR lpPath, int nCount);
	//�����ݿ��ȡ���ݣ�����ʾ���б�ؼ�
	void GetDataset();
	//ִ�����践��ֵ��SQL����
	void ExecuteSql(LPCTSTR lpSql);
// Implementation
protected:
	_ConnectionPtr	m_pConnection;	//���ݿ����Ӷ���
	_RecordsetPtr	m_pRecordset;	//��¼������
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAdo_DemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnEdit();
	afx_msg void OnBtnDelete();
	afx_msg void OnDestroy();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADO_DEMODLG_H__C65C8FAF_A9B2_4588_8533_BB09C720467B__INCLUDED_)
