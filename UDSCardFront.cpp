// UDSCardFront.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDSCardFront.h"
#include "afxdialogex.h"



// CUDSCardFront �Ի���
extern CString    g_strFrontImg;

IMPLEMENT_DYNAMIC(CUDSCardFront, CDialogEx)

CUDSCardFront::CUDSCardFront(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSCardFront::IDD, pParent)
{

}

CUDSCardFront::~CUDSCardFront()
{
}

void CUDSCardFront::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STA_FRONT, m_conPicCtrl);
}


BEGIN_MESSAGE_MAP(CUDSCardFront, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_TEST, &CUDSCardFront::OnBnClickedBtnTest)
END_MESSAGE_MAP()


// CUDSCardFront ��Ϣ�������


BOOL CUDSCardFront::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CUDSCardFront::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������

	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


void CUDSCardFront::OnBnClickedBtnTest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}
