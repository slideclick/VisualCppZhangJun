#pragma once

//用于接收视频图像的对象定义
class IMediaReceiver
{
public:
	virtual void OnUpdateVideo(
		const BITMAPINFO *, const BYTE *) = 0;
};
//视频回调接口实现
class CSampleCB :
	public ISampleGrabberCB
{
public:
	CSampleCB(void);
	~CSampleCB(void);
	STDMETHODIMP_(ULONG) AddRef() { return 2; } 
	STDMETHODIMP_(ULONG) Release() { return 1; } 
	STDMETHODIMP QueryInterface(REFIID riid, void ** ppv)
	{ 
		if( riid == IID_ISampleGrabberCB || riid == IID_IUnknown )
		{
			*ppv = (void *) static_cast<ISampleGrabberCB*>(this); 
			return NOERROR; 
		} 
		return E_NOINTERFACE; 
	} 
	//回调函数，任意一个均可获得图像
	STDMETHODIMP SampleCB(double SampleTime, IMediaSample *pSample);
	STDMETHODIMP BufferCB(
		double dblSampleTime, BYTE *pBuffer, long lBufferSize);
	//设置图像接收者
	void SetReceiver(IMediaReceiver * pObj);
	//保存图像尺寸
	void SetImageInfo(LONG nWidth, LONG nHeight);
protected:
	IMediaReceiver * m_pReceiver;
	BITMAPINFO m_bmi;
};
