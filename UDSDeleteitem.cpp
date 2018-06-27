// UDSDeleteitem.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDSDeleteitem.h"
#include "afxdialogex.h"



// CUDSDeleteitem �Ի���

IMPLEMENT_DYNAMIC(CUDSDeleteitem, CDialogEx)

CUDSDeleteitem::CUDSDeleteitem(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSDeleteitem::IDD, pParent)
{

}

CUDSDeleteitem::~CUDSDeleteitem()
{
}

void CUDSDeleteitem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CUDSDeleteitem, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &CUDSDeleteitem::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUDSDeleteitem::OnBnClickedCancel)
END_MESSAGE_MAP()


// CUDSDeleteitem ��Ϣ�������


BOOL CUDSDeleteitem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_BDeleteIt = FALSE;
	CDialogEx::SetBackgroundColor(RGB(134, 130, 167));
	m_btnOK.Init(IDB_PNG_OK, BTN_IMG_1, BTN_TYPE_NORMAL);
	m_btnCancel.Init(IDB_PNG_CANCEL, BTN_IMG_1, BTN_TYPE_NORMAL);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CUDSDeleteitem::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID()==IDC_STA_DELETEIT)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(245, 250, 6));
		CFont   tem_Font;
		tem_Font.CreatePointFont(200, _T("����"));
		pDC->SelectObject(&tem_Font);
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CUDSDeleteitem::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_BDeleteIt = TRUE;
	CDialogEx::OnOK();
}


void CUDSDeleteitem::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_BDeleteIt = FALSE;
	CDialogEx::OnCancel();
}
