// DlgSkin.cpp: implementation of the CDlgSkin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DlgSkinDemo.h"
#include "DlgSkin.h"
#include <afxtempl.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//����Ƥ�����ݵ���������
#define SKIN_PROP_NAME _T("_Dlg_Skin_Prop_")
//
typedef CArray <SkinData *, SkinData*> SkinDlgArray;
SkinDlgArray g_arWnds;
HBRUSH		g_hbBg;
HHOOK		g_hHook = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//����Ƥ��
int CDlgSkin::SetSkin(COLORREF crBg)
{
	ASSERT(g_hHook == NULL);
	if(g_hHook)
		return -1;
	//��װHOOK
	g_hHook = SetWindowsHookEx(WH_CALLWNDPROC, CallWndProc, NULL, GetCurrentThreadId());
	if(g_hHook == NULL)
		return GetLastError();
	else
	{
		//����������ˢ
		g_hbBg = CreateSolidBrush(crBg);
		return 0;
	}
}
//�ͷ�Ƥ��
int CDlgSkin::FreeSkin()
{
	ASSERT(g_hHook);
	if(g_hHook == NULL)
		return -1;
	//ж��HOOK
	if(UnhookWindowsHookEx(g_hHook))
	{
		//ɾ��������ˢ
		DeleteObject(g_hbBg);
		g_hHook = NULL;
		g_hbBg = NULL;
		//ɾ��Ƥ������
		for(int i=0; i<g_arWnds.GetSize(); i++)
		{
			SkinData *pData = (SkinData *)g_arWnds.GetAt(i);
			if (pData != NULL) 
			{
				SetWindowLong(pData->hWnd , GWL_WNDPROC, (LONG)pData->procOld);
				RemoveProp(pData->hWnd, SKIN_PROP_NAME);
				delete pData;
			}
		}
		g_arWnds.RemoveAll();
		return 0;
	}
	else
		return GetLastError();
}
//�µĶԻ������
LRESULT CALLBACK CDlgSkin::NewDlgProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	//��ȡƤ������
	SkinData *pData = (SkinData *)GetProp(hWnd, SKIN_PROP_NAME);
	if (pData == NULL) 
	{
		return DefWindowProc(hWnd, uMsg, wp, lp);
	}
	//����Ի�����Ϣ���ı䱳��
	switch(uMsg) 
	{
	case WM_CTLCOLORDLG:
		return (LRESULT)g_hbBg;
	case WM_CTLCOLORSTATIC:
		SetBkMode((HDC)wp, TRANSPARENT);
		return (LRESULT)g_hbBg;
	default:
		break;
	}
	//���ô���ԭ���Ĵ������
	return CallWindowProc(pData->procOld, hWnd, uMsg, wp, lp);
}
//HOOK�������
LRESULT CALLBACK CDlgSkin::CallWndProc(int nCode, WPARAM wp, LPARAM lp)
{
	do{
		if(nCode != HC_ACTION) 
			break;
		CWPSTRUCT* pCWP = (CWPSTRUCT*)lp;
		if(pCWP->message != WM_CREATE)
			break;
		HWND hWnd = pCWP->hwnd;
		if(GetProp(hWnd, SKIN_PROP_NAME) != NULL)
			break;
		//��ȡ�����ֻ࣬����Ի���
		TCHAR szClass[MAX_PATH + 1] = {0};
		GetClassName(hWnd, szClass, MAX_PATH);
		if (_tcsicmp(_T("#32770"), szClass) != 0) 
			break;
		//����Ƥ������
		SkinData *pData = new SkinData;
		pData->hWnd = hWnd;
		//�޸Ĵ��ڴ�����̣���ʵ�����໯�Ի���
		pData->procOld = (WNDPROC)SetWindowLong(hWnd, GWL_WNDPROC, (LONG)NewDlgProc);
		g_arWnds.Add(pData);
		//��Ƥ�����ݱ��浽����������
		SetProp(hWnd, SKIN_PROP_NAME, pData);			
	}while (FALSE) ;
	//������һ��HOOK
	return CallNextHookEx(g_hHook, nCode, wp, lp);
}
