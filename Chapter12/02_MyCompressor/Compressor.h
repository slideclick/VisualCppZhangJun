// Compressor.h: interface for the CCompressor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPRESSOR_H__52745B8B_A6BE_48F1_AD5B_945A66A3D42F__INCLUDED_)
#define AFX_COMPRESSOR_H__52745B8B_A6BE_48F1_AD5B_945A66A3D42F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//ѹ���ļ��ṹ��
/*
-MCF			3�ֽڱ�־
-����չ��		��0��β
-��������		���ַ�0xFF��Ϊ��־��ѹ���ֽھ���3�ֽڣ�
				��0xFF��ͷ+ԭ���ַ�+�ظ�������
				����ظ���������255���ֶ�δ洢��
*/
class CCompressor  
{
public:
	CCompressor();
	virtual ~CCompressor();
	BOOL CompressFile(LPCTSTR lpFile);
	BOOL DecompressFile(LPCTSTR lpFile);
protected:
	void GetDestFilename(LPCTSTR lpSrc, LPTSTR lpDest);
};

#endif // !defined(AFX_COMPRESSOR_H__52745B8B_A6BE_48F1_AD5B_945A66A3D42F__INCLUDED_)
