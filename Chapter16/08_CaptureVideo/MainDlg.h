// MainDlg.h: interface for the CMainDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINDLG_H__0909FF99_73C7_4524_9F62_302DA853D0FF__INCLUDED_)
#define AFX_MAINDLG_H__0909FF99_73C7_4524_9F62_302DA853D0FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cap.h"

class CMainDlg: public IMediaReceiver
{
public:
	CMainDlg();
	virtual ~CMainDlg();
	int DoModal();
public: //IMediaReceiver实现
	//更新视频图像
	void OnUpdateVideo(const BITMAPINFO *pBmi, const BYTE *pBuf);
protected:
	//对话框过程
	static int CALLBACK 
		DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	//初始化对话框
	BOOL OnInitDialog(HWND hWnd);
	//销毁前消息
	void OnDestroy();
	//WM_COMMAND消息响应
	BOOL OnCommand(WPARAM wp, LPARAM lp);
	//“刷新设备”按钮响应函数
	void OnGetDevices();
	//“开始”按钮响应函数
	void OnOk();
	//“截图”按钮响应函数
	void OnSnapshot();
	//WM_SIZE消息响应
	void OnSize(WPARAM wp, LPARAM lp);
	//将屏幕坐标转换为窗体坐标
	void ScreenToClientRect(LPRECT prc);
	//保存截图文件
	void SaveSnapshotImage(const BITMAPINFOHEADER *pbih, const BYTE *pBuf);
	//禁止或允许对话框上的控件
	void EnableDlgItem(UINT nID, BOOL bEnable);
protected:
	//视频采集对象
	CCap  m_cap;
	//对话框句柄
	HWND  m_hDlg;
	//视频显示控件句柄
	HWND  m_hVideo;
	//视频设备列表句柄
	HWND  m_hDeviceList;
	//对话框原始尺寸
	SIZE  m_siDlg;
	//当前已截图数量
	int   m_nSnapshotNum;
	//总的截图数量
	int   m_nSnapshotCount;
	//最后截图时间
	DWORD m_dwLastSnapshot;
	//截图间隔
	DWORD m_dwSnapshotInterval;
	//截图保存路径
	TCHAR m_szSnapshotPath[MAX_PATH];
	//应用程序图标
	HICON m_hAppIcon;
};

#endif // !defined(AFX_MAINDLG_H__0909FF99_73C7_4524_9F62_302DA853D0FF__INCLUDED_)
