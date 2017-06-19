// VideoRender.h: interface for the CVideoRender class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIDEORENDER_H__1EDB4C90_1331_4106_B740_00BE357278F4__INCLUDED_)
#define AFX_VIDEORENDER_H__1EDB4C90_1331_4106_B740_00BE357278F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <dshow.h>
#pragma comment(lib, "strmiids.lib")

class CVideoRender  
{
public:
	CVideoRender();
	virtual ~CVideoRender();
	//建立对象
	BOOL Create(HWND hNotifyHost, UINT nNotifyMsg);
	//释放对象
	void Release();
	//加载视频文件
	BOOL LoadFile(LPCTSTR lpFile);
	//设置视频父窗口
	BOOL SetOwner(HWND hWnd);
	//设置视频窗口大小
	BOOL MoveVideoWnd(LPRECT lpRect);
	//开始播放
	BOOL Run();
	//暂停播放
	BOOL Pause();
	//停止播放
	BOOL Stop();
	//获取视频总长度
	BOOL GetDuration(__int64 *pDuration);
	//设置播放进度
	BOOL SetPosition(__int64 iPosition);
	//获取当前进度
	BOOL GetPosition(__int64 *pPosition);
	//获取错误信息
	LPCTSTR GetErrMsg();
	//获取事件
	BOOL GetEvent(LONG *plCode, LONG *plParam1, LONG *plParam2);
protected:
	//设置错误信息
	void SetErrMsg(LPCTSTR lpMsg);
protected:
	HRESULT			 m_hr;
	TCHAR			 m_szErrMsg[1024];
	IMediaSeeking   *m_pMediaSeeking;
	IMediaEventEx   *m_pMediaEventEx;
	IVideoWindow    *m_pVideoWnd;
	IMediaControl   *m_pMediaCtrl;
	IGraphBuilder   *m_pGraph;
};

#endif // !defined(AFX_VIDEORENDER_H__1EDB4C90_1331_4106_B740_00BE357278F4__INCLUDED_)
