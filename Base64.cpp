//   Base641.cpp:   implementation   of   the   CBase64   class. 
// 
////////////////////////////////////////////////////////////////////// 

#include "stdafx.h"
#include "Base64.h " 

#ifdef _DEBUG 
#undef THIS_FILE 
static char THIS_FILE[]=__FILE__; 
#define new DEBUG_NEW 
#endif 

////////////////////////////////////////////////////////////////////// 
//   Construction/Destruction 
////////////////////////////////////////////////////////////////////// 
const char CBase64::BASE64_ENCODE_TABLE[64] = 
{ 
	65,		66,		67,		68,		69,		70,		71,     72,		//   00   -   07 
	73,     74,     75,     76,     77,     78,     79,     80,		//   08   -   15 
	81,     82,     83,     84,     85,     86,     87,     88,		//   16   -   23 
	89,     90,     97,     98,     99,		100,	101,	102,	//   24   -   31 
	103,	104,	105,	106,	107,	108,	109,	110,	//   32   -   39 
	111,	112,	113,	114,	115,	116,	117,	118,	//   40   -   47 
	119,	120,	121,	122,	48,		49,     50,     51,     //   48   -   55 
	52,		53,     54,     55,     56,     57,     43,     47		//   56   -   63 
};

const UINT CBase64::BASE64_DECODE_TABLE[256] =
{ 
	255,	255,	255,	255,	255,	255,	255,	255,	//     00   -     07 
	255,	255,	255,	255,	255,	255,	255,	255,	//     08   -     15
	255,	255,	255,	255,	255,	255,	255,	255,	//     16   -     23 
	255,	255,	255,	255,	255,	255,	255,	255,	//     24   -     31 
	255,	255,	255,	255,	255,	255,	255,	255,	//     32   -     39 
	255,	255,	255,	62,		255,	255,	255,	63,		//     40   -     47 
	52,     53,     54,     55,     56,     57,     58,     59,		//     48   -     55 
	60,     61,		255,	255,	255,	255,	255,	255,	//     56   -     63 
	255,	0,		1,		2,		3,		4,		5,		6,		//     64   -     71 
	7,		8,		9,		10,		11,		12,		13,		14,		//     72   -     79 
	15,     16,     17,     18,     19,     20,     21,     22,		//     80   -     87 
	23,     24,     25,		255,	255,	255,	255,	255,	//     88   -     95 
	255,	26,     27,     28,     29,     30,     31,     32,		//     96   -   103 
	33,     34,     35,     36,     37,     38,     39,     40,		//   104   -   111 
	41,     42,     43,     44,     45,     46,     47,     48,		//   112   -   119 
	49,     50,     51,		255,	255,	255,	255,	255,	//   120   -   127 
	255,	255,	255,	255,	255,	255,	255,	255, 
	255,	255,	255,	255,	255,	255,	255,	255, 
	255,	255,	255,	255,	255,	255,	255,	255, 
	255,	255,	255,	255,	255,	255,	255,	255, 
	255,	255,	255,	255,	255,	255,	255,	255, 
	255,	255,	255,	255,	255,	255,	255,	255, 
	255,	255,	255,	255,	255,	255,	255,	255, 
	255,	255,	255,	255,	255,	255,	255,	255, 
	255,	255,	255,	255,	255,	255,	255,	255, 
	255,	255,	255,	255,	255,	255,	255,	255, 
	255,	255,	255,	255,	255,	255,	255,	255, 
	255,	255,	255,	255,	255,	255,	255,	255, 
	255,	255,	255,	255,	255,	255,	255,	255, 
	255,	255,	255,	255,	255,	255,	255,	255, 
	255,	255,	255,	255,	255,	255,	255,	255, 
	255,	255,	255,	255,	255,	255,	255,	255   
}; 


CBase64::CBase64() 
{ 

} 


CBase64::~CBase64() 
{ 

} 


UINT CBase64::Encode(const char* pSrc, UINT nSize, char* pDest) 
{ 
	ASSERT(pSrc != NULL); 
	if((pSrc == NULL) || (nSize <= 0)) 
		return 0; 
	
	unsigned int iB, iInMax3, Len; 
	const char* pInPtr, *pInLimitPtr; 
	char* OutPtr; 
	
	pInPtr = pSrc;
	iInMax3 = nSize / 3 * 3; 
	OutPtr = pDest;
	pInLimitPtr = pInPtr + iInMax3; 
	
	while(pInPtr != pInLimitPtr)
	{ 
		Len = 0;
		while((Len < 76) && (pInPtr != pInLimitPtr))//   每行编码后的字符长度必须小于等于76 
		{ 
			__asm 
			{ 
				mov	ebx, pInPtr 
				mov eax, dword ptr [ebx]
				add pInPtr, 3 
				bswap eax 
				shr eax, 8 
				mov iB, eax 
			} 
			//以4   byte倒序写入输出缓冲 
			OutPtr[3] = BASE64_ENCODE_TABLE[iB & 0x3F]; 
			iB = iB >> 6; 
			OutPtr[2] = BASE64_ENCODE_TABLE[iB & 0x3F]; 
			iB = iB >> 6; 
			OutPtr[1] = BASE64_ENCODE_TABLE[iB & 0x3F]; 
			iB = iB >> 6; 
			OutPtr[0] = BASE64_ENCODE_TABLE[iB]; 
			OutPtr += 4; 
			Len += 4;
		} 
		if(Len >= 76) 
		{ 
			*OutPtr++ = '\r ';   //加上回车换行符 
			*OutPtr++ = '\n '; 
		}
	} 
	return (unsigned int)(OutPtr - pDest); 
} 


UINT CBase64::EncodedSize(UINT nSize) 
{ 
	nSize = (nSize + 2) / 3 * 4 ; //计算回车数量 
	nSize += (nSize / 76) * 2; 
	return nSize; 
} 


UINT CBase64::Decode(const char *pSrc, UINT nSize,char *pDest) 
{ 
	if ((pSrc == NULL)||(pDest == NULL)||(nSize <= 0))
		return   0; 

	unsigned int lByteBuffer,lByteBufferSpace; 
	unsigned int C;   //临时阅读变量 
	int reallen; 
	const char *InPtr,*InLimitPtr; 
	char *OutPtr; 

	lByteBuffer = 0; 
	lByteBufferSpace = 4; 

	InPtr = pSrc; 
	InLimitPtr= InPtr + nSize; 
	OutPtr = pDest; 

	while(InPtr != InLimitPtr) 
	{ 
		C = BASE64_DECODE_TABLE[*InPtr];   //   Read   from   InputBuffer. 
		InPtr++; 
		if(C == 0xFF) //读到255非法字符
			continue;    
		lByteBuffer = lByteBuffer << 6   ; 
		lByteBuffer = lByteBuffer | C   ; 
		lByteBufferSpace--; 
		if (lByteBufferSpace != 0) //一次读入4个字节 
			continue;  
		//到序写入3个字节到缓冲 
		OutPtr[2] = lByteBuffer; 
		lByteBuffer = lByteBuffer >> 8; 
		OutPtr[1] = lByteBuffer; 
		lByteBuffer = lByteBuffer >> 8; 
		OutPtr[0] = lByteBuffer; 
		//准备写入后3位 
		OutPtr+= 3;
		lByteBuffer = 0;
		lByteBufferSpace = 4; 
	} 
	reallen = (unsigned int)OutPtr - (unsigned int)pDest; 
	//处理尾部   返回实际长度 
	switch(lByteBufferSpace) 
	{ 
	case 1: 
		lByteBuffer = lByteBuffer >> 2; 
		OutPtr[1] = lByteBuffer; 
		lByteBuffer = lByteBuffer >> 8; 
		OutPtr[0] = lByteBuffer; 
		return reallen + 2; 
	case 2: 
		lByteBuffer = lByteBuffer >> 4; 
		OutPtr[0] = lByteBuffer; 
		return reallen + 1; 
	default: 
		return reallen; 
	} 

} 


UINT CBase64::DecodedSize(UINT nSize) 
{ 
	return (nSize + 3) / 4 * 3; 
} 
