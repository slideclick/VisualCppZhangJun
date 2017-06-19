#include "StdAfx.h"
#include ".\samplecb.h"

CSampleCB::CSampleCB(void)
{
	//初始化变量
	m_pReceiver = NULL;
	memset(&m_bmi, 0, sizeof(m_bmi));
	m_bmi.bmiHeader.biSize = sizeof(m_bmi.bmiHeader);
	m_bmi.bmiHeader.biPlanes = 1;
	m_bmi.bmiHeader.biBitCount = 24;
}
CSampleCB::~CSampleCB(void)
{
}
STDMETHODIMP CSampleCB::SampleCB(
	double SampleTime, IMediaSample *pSample)
{   
	return   0;   
}  
//每次采样调用的函数
STDMETHODIMP CSampleCB::BufferCB(
	double dblSampleTime, BYTE *pBuffer, long lBufferSize)
{   
	if(!pBuffer)
		return E_POINTER;  
	//保存数据大小
	m_bmi.bmiHeader.biSizeImage = lBufferSize;
	//调用接收者方法
	if(m_pReceiver)
		m_pReceiver->OnUpdateVideo(&m_bmi, pBuffer);
	return 0;
}
//设置图像接收者
void CSampleCB::SetReceiver(IMediaReceiver * pObj)
{
	m_pReceiver = pObj;
}
//保存图像大小
void CSampleCB::SetImageInfo(LONG nWidth, LONG nHeight)
{
	m_bmi.bmiHeader.biWidth = nWidth;
	m_bmi.bmiHeader.biHeight = nHeight;
}