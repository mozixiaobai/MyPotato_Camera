
// UDS SmartCamera v1.0.0.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "UDS SmartCamera v1.0.0.h"
#include "UDS SmartCamera v1.0.0Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUDSSmartCamerav100App

BEGIN_MESSAGE_MAP(CUDSSmartCamerav100App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CUDSSmartCamerav100App ����

CUDSSmartCamerav100App::CUDSSmartCamerav100App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CUDSSmartCamerav100App ����

CUDSSmartCamerav100App theApp;


// CUDSSmartCamerav100App ��ʼ��

BOOL CUDSSmartCamerav100App::InitInstance()
{
	//��������������ֻ֤��һ��ʵ������
	m_hMutex = CreateMutex(NULL,TRUE,_T("UDSCameraToolMutualExclusion"));
	if (m_hMutex == NULL)
	{
		return FALSE;
	}
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(m_hMutex);
		m_hMutex = NULL;
		return FALSE;
	}


	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinApp::InitInstance();
	AfxInitRichEdit();   //û�иþ䣬���RichEdit�������ռ佫��ʾ�쳣
	AfxEnableControlContainer();
	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	CUDSSmartCamerav100Dlg dlg;
	m_pMainWnd = &dlg;
	dlg.m_BCardDlg = FALSE;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



int CUDSSmartCamerav100App::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	if(m_hMutex != NULL)
	{
		CloseHandle(m_hMutex);	//�رվ��
	}

	return CWinApp::ExitInstance();
}
