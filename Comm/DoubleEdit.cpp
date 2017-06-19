// DoubleEdit.cpp: implementation of the CDoubleEdit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DoubleEdit.h"

//��ſؼ���ָ�������ֵ
#define DOUBLE_EDIT_PROP_NAME _T("Double_Edit_Prop_Name")

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDoubleEdit::CDoubleEdit(): m_hWnd(NULL), m_lOldProc(0)
{
}

CDoubleEdit::~CDoubleEdit()
{
	Detach();
}

BOOL CDoubleEdit::Attach(HWND hWnd)
{
	//����Ϳؼ�����
	if(m_hWnd != NULL)
	{
		DebugBreak();
		return FALSE;
	}

	m_hWnd = hWnd;
	SetProp(hWnd, DOUBLE_EDIT_PROP_NAME, this);
	//�޸Ŀؼ�����Ϊ�µĴ������
	m_lOldProc = SetWindowLong(hWnd, GWL_WNDPROC, (long)NewEditProc);
	if (m_lOldProc == 0)
	{
		m_hWnd = NULL;
		return FALSE;
	}
	else
		return TRUE;
}

void CDoubleEdit::Detach()
{
	//�ָ��ؼ�Ĭ�ϴ�����̣�ȡ����Ϳؼ��Ĺ���
	if(m_hWnd == NULL)
		return;
	SetWindowLong(m_hWnd, GWL_WNDPROC, m_lOldProc);
	m_hWnd = NULL;
	m_lOldProc = 0;
}

BOOL CDoubleEdit::GetDoubleValue(double *pValue)
{
	//��ȡ�������doubleֵ
	TCHAR szBuf[32];
	if(GetStringValue(szBuf, 32))
	{
		*pValue = atof(szBuf);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CDoubleEdit::GetStringValue(LPTSTR lpBuffer, int nLen)
{
	//��ȡ��������ı�ֵ
	return GetWindowText(m_hWnd, lpBuffer, nLen);
}

LRESULT APIENTRY CDoubleEdit::NewEditProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp) 
{
	//�µĴ������
	CDoubleEdit *pEdit = (CDoubleEdit *)GetProp(hWnd, DOUBLE_EDIT_PROP_NAME);
	if (pEdit == NULL)
	{
		return DefWindowProc(hWnd, uMsg, wp, lp);
	}

	//��������Ϣ�����Բ�����Ҫ��İ���
	BOOL bCanceled = FALSE;
	if (uMsg == WM_CHAR) 
	{
		TCHAR szBuf[32] = {0};
		pEdit->GetStringValue(szBuf, 32);
		switch(wp)
		{
		case '.':
			//����ֻ������һ��С����
			if(_tcschr(szBuf, '.'))
			{
				bCanceled = TRUE;
			}
			break;
		case '-':
			//����ֻ������һ�����ţ�����ֻ���ǵ�һ���ַ�
			if(_tcschr(szBuf, '-'))
			{
				bCanceled = TRUE;
			}
			else if (LOWORD(SendMessage(hWnd, EM_GETSEL, 0, 0)) != 0)
			{
				bCanceled = TRUE;
			}
			break;
		default:
			//����ֻ������0-9֮����ַ�
			if ((wp > '9' || wp < '0') && wp != VK_BACK)
			{
				bCanceled = TRUE;
			}
			break;
		}
		if (bCanceled) 
		{
			//���ڲ�����Ҫ����ַ����룬ֱ�ӷ���
			MessageBeep(-1);
			return 0;
		}
	}
	//������Ϣ������Ĭ�ϴ���
	return CallWindowProc((WNDPROC)pEdit->m_lOldProc, hWnd, uMsg, wp, lp); 
}
