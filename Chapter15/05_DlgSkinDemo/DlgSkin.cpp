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
//保存皮肤数据的属性名称
#define SKIN_PROP_NAME _T("_Dlg_Skin_Prop_")
//
typedef CArray <SkinData *, SkinData*> SkinDlgArray;
SkinDlgArray g_arWnds;
HBRUSH		g_hbBg;
HHOOK		g_hHook = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//设置皮肤
int CDlgSkin::SetSkin(COLORREF crBg)
{
	ASSERT(g_hHook == NULL);
	if(g_hHook)
		return -1;
	//安装HOOK
	g_hHook = SetWindowsHookEx(WH_CALLWNDPROC, CallWndProc, NULL, GetCurrentThreadId());
	if(g_hHook == NULL)
		return GetLastError();
	else
	{
		//创建背景画刷
		g_hbBg = CreateSolidBrush(crBg);
		return 0;
	}
}
//释放皮肤
int CDlgSkin::FreeSkin()
{
	ASSERT(g_hHook);
	if(g_hHook == NULL)
		return -1;
	//卸载HOOK
	if(UnhookWindowsHookEx(g_hHook))
	{
		//删除背景画刷
		DeleteObject(g_hbBg);
		g_hHook = NULL;
		g_hbBg = NULL;
		//删除皮肤数据
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
//新的对话框过程
LRESULT CALLBACK CDlgSkin::NewDlgProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	//获取皮肤数据
	SkinData *pData = (SkinData *)GetProp(hWnd, SKIN_PROP_NAME);
	if (pData == NULL) 
	{
		return DefWindowProc(hWnd, uMsg, wp, lp);
	}
	//处理对话框消息，改变背景
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
	//调用窗口原来的处理过程
	return CallWindowProc(pData->procOld, hWnd, uMsg, wp, lp);
}
//HOOK处理过程
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
		//获取窗口类，只处理对话框
		TCHAR szClass[MAX_PATH + 1] = {0};
		GetClassName(hWnd, szClass, MAX_PATH);
		if (_tcsicmp(_T("#32770"), szClass) != 0) 
			break;
		//建立皮肤数据
		SkinData *pData = new SkinData;
		pData->hWnd = hWnd;
		//修改窗口处理过程，以实现子类化对话框
		pData->procOld = (WNDPROC)SetWindowLong(hWnd, GWL_WNDPROC, (LONG)NewDlgProc);
		g_arWnds.Add(pData);
		//将皮肤数据保存到窗口属性中
		SetProp(hWnd, SKIN_PROP_NAME, pData);			
	}while (FALSE) ;
	//调用下一个HOOK
	return CallNextHookEx(g_hHook, nCode, wp, lp);
}
