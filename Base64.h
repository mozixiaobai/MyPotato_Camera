//   Base641.h:   interface   for   the   CBase64   class. 
// 
////////////////////////////////////////////////////////////////////// 

#if !defined(AFX_BASE64_H__E9CCF836_F3A3_4BA8_91B1_764BC3BBE20E__INCLUDED_) 
#define AFX_BASE64_H__E9CCF836_F3A3_4BA8_91B1_764BC3BBE20E__INCLUDED_ 

#if _MSC_VER > 1000 
#pragma once 
#endif

class CBase64     
{ 
public: 
	CBase64(); 
	virtual ~CBase64(); 

	UINT DecodedSize(UINT nSize); 
	UINT Decode(const char* pSrc, UINT nSize, char* pDest); 
	UINT EncodedSize(UINT nSize); 
	UINT Encode(const char* pSrc, UINT nSize, char* pDest); 
protected: 
	static const char BASE64_ENCODE_TABLE[64]; 
	static const UINT BASE64_DECODE_TABLE[256]; 
}; 

#endif
