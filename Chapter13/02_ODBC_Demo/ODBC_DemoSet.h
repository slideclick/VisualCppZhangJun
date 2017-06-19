// ODBC_DemoSet.h : interface of the CODBC_DemoSet class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODBC_DEMOSET_H__AB5704FE_0524_4933_9DF5_2FAC0D97DB10__INCLUDED_)
#define AFX_ODBC_DEMOSET_H__AB5704FE_0524_4933_9DF5_2FAC0D97DB10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CODBC_DemoSet : public CRecordset
{
public:
	CODBC_DemoSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CODBC_DemoSet)

// Field/Param Data
	//{{AFX_FIELD(CODBC_DemoSet, CRecordset)
	long	m_StudentID;
	CString	m_StudentName;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CODBC_DemoSet)
	public:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ODBC_DEMOSET_H__AB5704FE_0524_4933_9DF5_2FAC0D97DB10__INCLUDED_)

