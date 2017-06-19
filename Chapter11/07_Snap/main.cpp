#include <windows.h>
#include <tchar.h>
#include <gdiplus.h>

#include "GdiPlus.h"
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

GdiplusStartupInput		m_gdiplusStartupInput;
ULONG_PTR               m_gdiplusToken;

//得到指定图片格式的编码值 
int GetImageCLSID(const WCHAR* format, CLSID* pCLSID) 
{
	UINT nNum = 0; 
	UINT nSize = 0; 
	ImageCodecInfo* pImageCodecInfo = NULL; 
	//获取系统所支持的图片格式总数
	GetImageEncodersSize(&nNum, &nSize); 
	if(nSize == 0) 
		return FALSE; 
	//分配内存 
	pImageCodecInfo = (ImageCodecInfo*)(malloc(nSize)); 
	if(pImageCodecInfo == NULL) 
		return FALSE; 
	//获得系统中可用的编码方式的所有信息 
	GetImageEncoders(nNum, nSize, pImageCodecInfo); 
	//在可用编码信息中查找格式是否被支持 
	for(UINT i = 0; i < nNum; ++i) 
	{ 
		//MimeType：编码方式的具体描述 
		if( wcscmp(pImageCodecInfo[i].MimeType, format) == 0 ) 
		{ 
			*pCLSID = pImageCodecInfo[i].Clsid; 
			free(pImageCodecInfo); 
			return TRUE; 
		} 
	} 
	free(pImageCodecInfo); 
	return FALSE; 
} 
//应用程序入口
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//初始化GDI+
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);
	{
		//获取桌面句柄
		HWND hDesk = GetDesktopWindow();
		//获取桌面大小
		RECT rc = {0};
		GetWindowRect(hDesk, &rc);
		//获取桌面DC
		HDC hDeskDC = GetDC(hDesk);
		//建立内存位图
		Bitmap bmp(rc.right, rc.bottom);
		//复制桌面DC到内存位图
		Graphics g(&bmp);
		HDC hDC = g.GetHDC();
		BitBlt(hDC, 0, 0, rc.right, rc.bottom,
			hDeskDC, 0, 0, SRCCOPY);
		g.ReleaseHDC(hDC);
		//释放桌面DC
		ReleaseDC(hDesk, hDeskDC);
		//保存内存位图到磁盘
		TCHAR szPath[MAX_PATH];
		GetModuleFileName(NULL, szPath, MAX_PATH);
		_tcscat(szPath, _T("_snap.bmp"));
		
		WCHAR szSave[MAX_PATH] = {0};
#ifdef UNICODE
		_tcscpy(szSave, szPath);
#else
		MultiByteToWideChar(CP_ACP, 0, szPath, -1, szSave, sizeof(szSave)/sizeof(szSave[0])); 
#endif
		CLSID fmt;
		GetImageCLSID(L"image/bmp", &fmt);
		bmp.Save(szSave, &fmt);
	}
	//卸载GDI+
	GdiplusShutdown(m_gdiplusToken);
	MessageBeep(MB_OK);
	return 0;
}