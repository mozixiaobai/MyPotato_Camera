#pragma once

#include "termb.h"

class CTermbReader
{
public:
	CTermbReader(void);
	~CTermbReader(void);
	CString OpenCardPort();
	CString CloseCardPort() ;
	void SetHeadPicPath(CString path) ;
	CString ReadIDCard(CString savepath) ;

	CString GetCardName();

	// ��ȡ���֤�������� [3/2/2018 Leo]
	CString GetCardBirth() ;

	// ��ȡ���֤�Ա� [3/2/2018 Leo]
	CString GetCardSex() ;

	// ��ȡ���֤���� [3/2/2018 Leo]
	CString GetCardNation() ;

	// ��ȡ���֤סַ [3/2/2018 Leo]
	CString GetCardAddress() ;

	// ��ȡ���֤���� [3/2/2018 Leo]
	CString GetCardID() ;

	// ��ȡ��֤���� [3/2/2018 Leo]
	CString GetIssuingOrgan() ;

	// ��ȡ��Ч���� [3/2/2018 Leo]
	CString GetAllottedTime() ;

	BOOL FindFinger();

	CString GetFingerDat();

private:
	int iRet ;	
	unsigned char pucSN[1024];
	unsigned char pucIIN[1024];

	unsigned char pucCHMsg[1024];
	unsigned char pucPHMsg[1024];
	unsigned char pucFPMsg[1024];
	unsigned int iCHMsgLen,iPHMsgLen,puiFPMsgLen;
	
	CString m_ImagePath;
	CString name;
	CString sex;
	CString nation;
	CString birthdate;
	CString addr;
	CString id;
	CString office;
	CString beginDate;
	CString endDate;
	bool findfinger;
	CString GetNationByString(CString str);

};

