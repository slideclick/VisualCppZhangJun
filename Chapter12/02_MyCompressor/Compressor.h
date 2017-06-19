// Compressor.h: interface for the CCompressor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPRESSOR_H__52745B8B_A6BE_48F1_AD5B_945A66A3D42F__INCLUDED_)
#define AFX_COMPRESSOR_H__52745B8B_A6BE_48F1_AD5B_945A66A3D42F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//压缩文件结构：
/*
-MCF			3字节标志
-旧扩展名		以0结尾
-主体内容		以字符0xFF作为标志，压缩字节均长3字节，
				以0xFF开头+原本字符+重复数量。
				如果重复数量大于255，分多段存储。
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
