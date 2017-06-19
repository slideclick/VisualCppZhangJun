#pragma once

class CPictureEx
{
public:
	//ͼƬ����ģʽ��ö��
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
	// ��Ϳؼ���
	BOOL Attach(HWND hWnd);
	// ���Ѿ��󶨵Ŀؼ�����
	HWND Detach(void);
	// ��ȡ�Ѱ󶨿ؼ���windows���
	HWND GetSafeHwnd(void);
	// ���ļ�����ͼƬ
	BOOL LoadImage(LPCTSTR lpFilename);
	//����Դ����ͼƬ
	BOOL LoadImage(HINSTANCE hInst, LPCTSTR lpResType, LPCTSTR lpResName);
	// ����ͼƬ����ģʽ
	void SetImageMode(ImageMode nHMode, ImageMode nVMode);
	// ���ÿؼ��ı�����ɫ
	void SetBgColor(COLORREF crBg);
	//��ʱ����Ϣ����
	void OnTimer();
protected:
	// �ؼ�����
	HWND m_hWnd;
	WNDPROC m_pOldProc;
	RECT m_rcClient;
	BOOL m_bCreated;
	// ��ȡ������ͼƬ
	Gdiplus::Image *m_pImg;			
	//��ͼ����
	ImageMode m_nHMode, m_nVMode;
	COLORREF m_crBg;
	LPSTREAM m_pResImg;
	//��ʾ������Ҫ����Ϣ
	UINT m_nActiveFrame;
	GUID *m_pImgDimenIDs;
	UINT m_nFrameCount;
	Gdiplus::PropertyItem* m_pImgProp;
	//��������
	DWORD m_dwDelay;
protected:
	// �ؼ�����proc
	static LRESULT NewWndProc(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp);
	// ��ָ��dc�ϻ���ͼƬ�ĵ�ǰ֡
	void DrawImage(HDC hDC);
	// ������һ֡
	void DrawNextFrame(void);
	//�ؼ���С�ı����Ϣ����
	void OnSize(UINT nType, int cx, int cy);
	//ʹ�ؼ���Ч���ػ�
	void Invalidata();
	// ����ͼƬ�ɹ����һϵ��׼������
	BOOL InitImage();
	// �ͷ�gdi��Դ
	void FreeImage(void);
};
