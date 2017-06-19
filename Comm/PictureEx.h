#pragma once

class CPictureEx
{
public:
	//图片绘制模式的枚举
	enum ImageMode
	{
		Center = 0,
		LeftTop = 1,
		RightBottom = 2,
		Stretch = 3,
		Tile = 4,
	};
public:
	CPictureEx(void);
	virtual ~CPictureEx(void);
	// 类和控件绑定
	BOOL Attach(HWND hWnd);
	// 和已经绑定的控件分离
	HWND Detach(void);
	// 获取已绑定控件的windows句柄
	HWND GetSafeHwnd(void);
	// 从文件加载图片
	BOOL LoadImage(LPCTSTR lpFilename);
	//从资源加载图片
	BOOL LoadImage(HINSTANCE hInst, LPCTSTR lpResType, LPCTSTR lpResName);
	// 设置图片绘制模式
	void SetImageMode(ImageMode nHMode, ImageMode nVMode);
	// 设置控件的背景颜色
	void SetBgColor(COLORREF crBg);
	//定时器消息处理
	void OnTimer();
protected:
	// 控件控制
	HWND m_hWnd;
	WNDPROC m_pOldProc;
	RECT m_rcClient;
	BOOL m_bCreated;
	// 读取出来的图片
	Gdiplus::Image *m_pImg;			
	//绘图参数
	ImageMode m_nHMode, m_nVMode;
	COLORREF m_crBg;
	LPSTREAM m_pResImg;
	//显示动画需要的信息
	UINT m_nActiveFrame;
	GUID *m_pImgDimenIDs;
	UINT m_nFrameCount;
	Gdiplus::PropertyItem* m_pImgProp;
	//动画控制
	DWORD m_dwDelay;
protected:
	// 控件的新proc
	static LRESULT NewWndProc(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp);
	// 在指定dc上绘制图片的当前帧
	void DrawImage(HDC hDC);
	// 绘制下一帧
	void DrawNextFrame(void);
	//控件大小改变的消息处理
	void OnSize(UINT nType, int cx, int cy);
	//使控件无效而重绘
	void Invalidata();
	// 加载图片成功后的一系列准备工作
	BOOL InitImage();
	// 释放gdi资源
	void FreeImage(void);
};
