#include "StdAfx.h"
#include "CTermbReader.h"


CTermbReader::CTermbReader(void)
{
	iRet = 0;
	m_ImagePath = L"";
	name;
	sex = L"";
	nation = L"";
	birthdate = L"";
	addr = L"";
	id = L"";
	office = L"";
	beginDate = L"";
	endDate = L"";
	findfinger=false;
	
}


CTermbReader::~CTermbReader(void)
{
	iRet = 0;
	m_ImagePath = L"";
	name=L"";
	sex = L"";
	nation = L"";
	birthdate = L"";
	addr = L"";
	id = L"";
	office = L"";
	beginDate = L"";
	endDate = L"";
	findfinger=false;
	
}


CString CTermbReader::OpenCardPort()
{
LoadTermbDll();
	int iRet=InitComm(1001);
	if (iRet==1)
	{
		return L"";
	}
	return L"�򿪶˿�ʧ��";
}

CString CTermbReader::CloseCardPort()
{
	CloseComm();
FreeTermbDll();
	return L"";

}

void CTermbReader::SetHeadPicPath(CString path)
{
	m_ImagePath = path;
}

CString CTermbReader::ReadIDCard(CString savepath)
{
	iRet=Authenticate();
	//if (iRet!=1)
	//{
	//	return L"��֤ʧ��";
	//}
//	TCHAR szbuf[MAX_PATH] = {0};
//	GetModuleFileName(AfxGetStaticModuleState()->m_hCurrentInstanceHandle,szbuf,MAX_PATH);
//	CString _dllPath = CString(szbuf);
//	_dllPath = _dllPath.Left(_dllPath.ReverseFind('\\'))+TEXT("\\"); 


	CString _dllPath = savepath;
	 USES_CONVERSION;
	 char * pFileName = T2A(_dllPath);   
	int haves=Read_Content_Path(pFileName,1);
	//int haves=Read_Content(1);
	 if (haves != 1 && haves != 3)
		 return L"����ʧ��";
	 if (haves==3)
		 findfinger=true;
	 else
		 findfinger=false;
	//CString havs;
	//havs.Format(TEXT("%d"),haves);//==3��ָ��
	//AfxMessageBox(havs);
	CFile file;
	CString txtFile,msg;
	msg.Empty();
	txtFile = _dllPath+TEXT("\\wz.txt");
	//д���ܺ���ļ�
	file.Open(txtFile,CFile::modeRead);
	TCHAR* temp=new TCHAR[file.GetLength()/2+1];  
	file.Read(temp,file.GetLength());  
	temp[file.GetLength()/2]=0;  
	msg=temp;  
	delete temp; 
	file.Close();
	//���֤��Ϣ
	name = msg.Left(15).Trim();
	sex = msg.Mid(15,1).Trim();
	nation = GetNationByString(msg.Mid(16,2)).Trim();
	birthdate = msg.Mid(18,8).Trim();
	addr = msg.Mid(26,35).Trim();
	id = msg.Mid(61,18).Trim();
	office = msg.Mid(79,15).Trim();
	beginDate = msg.Mid(94,8).Trim();
	endDate = msg.Mid(102,8).Trim();
	DeleteFile(txtFile);
	MoveFile(_dllPath+TEXT("\\zp.bmp"),m_ImagePath);
	return L"";



}

CString CTermbReader::GetNationByString(CString str)
{
	CString nation;
	int i = _ttoi(str);
	switch (i)
	{
	case 1:
		nation = L"��";
		break;
	case 2:
		nation = L"�ɹ�";
		break;
	case 3:
		nation = L"��";
		break;
	case 4:
		nation = L"��";
		break;
	case 5:
		nation = L"ά���";
		break;
	case 6:
		nation = L"��";
		break;
	case 7:
		nation = L"��";
		break;
	case 8:
		nation = L"׳";
		break;
	case 9:
		nation = L"����";
		break;
	case 10:
		nation = L"����";
		break;
	case 11:
		nation = L"��";
		break;
	case 12:
		nation = L"��";
		break;
	case 13:
		nation = L"��";
		break;
	case 14:
		nation = L"��";
		break;
	case 15:
		nation = L"����";
		break;
	case 16:
		nation = L"����";
		break;
	case 17:
		nation = L"������";
		break;
	case 18:
		nation = L"��";
		break;
	case 19:
		nation = L"��";
		break;
	case 20:
		nation = L"����";
		break;
	case 21:
		nation = L"��";
		break;
	case 22:
		nation = L"�";
		break;
	case 23:
		nation = L"��ɽ";
		break;
	case 24:
		nation = L"����";
		break;
	case 25:
		nation = L"ˮ";
		break;
	case 26:
		nation = L"����";
		break;
	case 27:
		nation = L"����";
		break;
	case 28:
		nation = L"����";
		break;
	case 29:
		nation = L"�¶�����";
		break;
	case 30:
		nation = L"��";
		break;
	case 31:
		nation = L"�ﺲ��";
		break;
	case 32:
		nation = L"����";
		break;
	case 33:
		nation = L"Ǽ";
		break;
	case 34:
		nation = L"����";
		break;
	case 35:
		nation = L"����";
		break;
	case 36:
		nation = L"ë��";
		break;
	case 37:
		nation = L"����";
		break;
	case 38:
		nation = L"����";
		break;
	case 39:
		nation = L"����";
		break;
	case 40:
		nation = L"����";
		break;
	case 41:
		nation = L"������";
		break;
	case 42:
		nation = L"ŭ";
		break;
	case 43:
		nation = L"���α��";
		break;
	case 44:
		nation = L"����˹";
		break;
	case 45:
		nation = L"���¿�";
		break;
	case 46:
		nation = L"�°�";
		break;
	case 47:
		nation = L"����";
		break;
	case 48:
		nation = L"ԣ��";
		break;
	case 49:
		nation = L"��";
		break;
	case 50:
		nation = L"������";
		break;
	case 51:
		nation = L"����";
		break;
	case 52:
		nation = L"���״�";
		break;
	case 53:
		nation = L"����";
		break;
	case 54:
		nation = L"�Ű�";
		break;
	case 55:
		nation = L"���";
		break;
	case 56:
		nation = L"��ŵ";
		break;
	case 57:
		nation = L"����";
		break;
	case 98:
		nation = L"������뼮";
		break;
	}
	return nation;
}

CString CTermbReader::GetCardName()
{
	return name;
}

// ��ȡ���֤�������� [3/2/2018 Leo]
CString CTermbReader::GetCardBirth() 
{
	CString year = birthdate.Left(4);
	CString month = birthdate.Mid(4,2);
	CString day = birthdate.Mid(6,2);
	return year + L"��" + month + L"��" + day + L"��";
}

// ��ȡ���֤�Ա� [3/2/2018 Leo]
CString CTermbReader::GetCardSex()
{
	if (sex == L"1")
	{
		return L"��";
	}
	else
	{
		return L"Ů";
	}
}

// ��ȡ���֤���� [3/2/2018 Leo]
CString CTermbReader::GetCardNation()
{
	return nation;
}

// ��ȡ���֤סַ [3/2/2018 Leo]
CString CTermbReader::GetCardAddress()
{
	return addr;
}

// ��ȡ���֤���� [3/2/2018 Leo]
CString CTermbReader::GetCardID() 
{
	return id;
}

// ��ȡ��֤���� [3/2/2018 Leo]
CString CTermbReader::GetIssuingOrgan() 
{
	return office;
}

// ��ȡ��Ч���� [3/2/2018 Leo]
CString CTermbReader::GetAllottedTime() 
{
	beginDate.Insert(4,L".");
	beginDate.Insert(7,L".");
	endDate.Insert(4,L".");
	endDate.Insert(7,L".");
	return beginDate + L"-" + endDate;
}


BOOL CTermbReader::FindFinger()
{
	if (findfinger==true)
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}

}


CString CTermbReader::GetFingerDat()
{
	TCHAR szbuf[MAX_PATH] = {0};
	GetModuleFileName(AfxGetStaticModuleState()->m_hCurrentInstanceHandle,szbuf,MAX_PATH);
	CString _dllPath = CString(szbuf);
	_dllPath = _dllPath.Left(_dllPath.ReverseFind('\\'))+TEXT("\\fp.dat"); 
	return _dllPath;
}