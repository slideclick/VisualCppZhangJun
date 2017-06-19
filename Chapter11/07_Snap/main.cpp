#include <windows.h>
#include <tchar.h>
#include <gdiplus.h>

#include "GdiPlus.h"
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

GdiplusStartupInput		m_gdiplusStartupInput;
ULONG_PTR               m_gdiplusToken;

//�õ�ָ��ͼƬ��ʽ�ı���ֵ 
int GetImageCLSID(const WCHAR* format, CLSID* pCLSID) 
{
	UINT nNum = 0; 
	UINT nSize = 0; 
	ImageCodecInfo* pImageCodecInfo = NULL; 
	//��ȡϵͳ��֧�ֵ�ͼƬ��ʽ����
	GetImageEncodersSize(&nNum, &nSize); 
	if(nSize == 0) 
		return FALSE; 
	//�����ڴ� 
	pImageCodecInfo = (ImageCodecInfo*)(malloc(nSize)); 
	if(pImageCodecInfo == NULL) 
		return FALSE; 
	//���ϵͳ�п��õı��뷽ʽ��������Ϣ 
	GetImageEncoders(nNum, nSize, pImageCodecInfo); 
	//�ڿ��ñ�����Ϣ�в��Ҹ�ʽ�Ƿ�֧�� 
	for(UINT i = 0; i < nNum; ++i) 
	{ 
		//MimeType�����뷽ʽ�ľ������� 
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
//Ӧ�ó������
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//��ʼ��GDI+
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);
	{
		//��ȡ������
		HWND hDesk = GetDesktopWindow();
		//��ȡ�����С
		RECT rc = {0};
		GetWindowRect(hDesk, &rc);
		//��ȡ����DC
		HDC hDeskDC = GetDC(hDesk);
		//�����ڴ�λͼ
		Bitmap bmp(rc.right, rc.bottom);
		//��������DC���ڴ�λͼ
		Graphics g(&bmp);
		HDC hDC = g.GetHDC();
		BitBlt(hDC, 0, 0, rc.right, rc.bottom,
			hDeskDC, 0, 0, SRCCOPY);
		g.ReleaseHDC(hDC);
		//�ͷ�����DC
		ReleaseDC(hDesk, hDeskDC);
		//�����ڴ�λͼ������
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
	//ж��GDI+
	GdiplusShutdown(m_gdiplusToken);
	MessageBeep(MB_OK);
	return 0;
}