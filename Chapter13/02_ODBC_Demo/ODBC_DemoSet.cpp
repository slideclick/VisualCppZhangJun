// ODBC_DemoSet.cpp : implementation of the CODBC_DemoSet class
//

#include "stdafx.h"
#include "ODBC_Demo.h"
#include "ODBC_DemoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CODBC_DemoSet implementation

IMPLEMENT_DYNAMIC(CODBC_DemoSet, CRecordset)

CODBC_DemoSet::CODBC_DemoSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CODBC_DemoSet)
	m_StudentID = 0;
	m_StudentName = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}

CString CODBC_DemoSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=MyAccessDB");
}

CString CODBC_DemoSet::GetDefaultSQL()
{
	return _T("[Students]");
}

void CODBC_DemoSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CODBC_DemoSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[StudentID]"), m_StudentID);
	RFX_Text(pFX, _T("[StudentName]"), m_StudentName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CODBC_DemoSet diagnostics

#ifdef _DEBUG
void CODBC_DemoSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CODBC_DemoSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
