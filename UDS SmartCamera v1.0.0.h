
// UDS SmartCamera v1.0.0.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUDSSmartCamerav100App:
// �йش����ʵ�֣������ UDS SmartCamera v1.0.0.cpp
//

class CUDSSmartCamerav100App : public CWinApp
{
public:
	CUDSSmartCamerav100App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
	HANDLE    m_hMutex;  //������ע��������
};

extern CUDSSmartCamerav100App theApp;