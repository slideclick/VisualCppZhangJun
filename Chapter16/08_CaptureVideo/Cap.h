#pragma once

#include "stdafx.h"
#include "samplecb.h"

class CCap
{
public:
	CCap(void);
	~CCap(void);
	//枚举设备列表
	int EnumDevices(HWND hList);
	//初始化对象
	HRESULT Init(int iDeviceID);
	//释放对象资源
	void Release();
	//开始
	HRESULT Run();
	//暂停
	HRESULT Pause();
	//停止
	HRESULT Stop();
	//获取ISampleGrabberCB
	CSampleCB *GetSampleCB();
	//根据设备名查找设备序号，如果返回-1代表没有找到设备
	int FindDeviceByName(LPCTSTR lpName);	
	//获取该序号的设备名称
	LPCTSTR GetDeviceName(int nIndex);
	//获取设备总数
	int GetDeviceCount();
protected:
	void FreeMediaType(AM_MEDIA_TYPE& mt); 
	//连接Filter
	BOOL BindFilter(int nDeviceId, IBaseFilter **pFilter); 
	//设置视频窗口
	HRESULT SetupVideoWindow(); 
	//初始化GraphBuilder
	HRESULT InitCaptureGraphBuilder();
protected:
	IGraphBuilder	*m_pGB; 
	ICaptureGraphBuilder2* m_pCapture; 
	IBaseFilter		*m_pBF; 
	IMediaControl	*m_pMC; 
	IVideoWindow	*m_pVW; 
	LPTSTR			*m_pDevice;
	int 			m_nDeviceCount;
	BOOL			m_bRunning;
	HWND			m_hWnd;
	CSampleCB		m_cb;
	CComPtr<ISampleGrabber> m_pGrabber; 
};
