// UDSFront.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDSFront.h"
#include "afxdialogex.h"


// CUDSFront �Ի���

extern CString    g_strFrontImg;   //���֤����ͼ��·��

IMPLEMENT_DYNAMIC(CUDSFront, CDialogEx)

CUDSFront::CUDSFront(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSFront::IDD, pParent)
{

}

CUDSFront::~CUDSFront()
{
}

void CUDSFront::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUDSFront, CDialogEx)
	ON_WM_PAINT()
//	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CUDSFront ��Ϣ�������


BOOL CUDSFront::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	/********************************
	*         Ŀ¼
	* 1��������ʼ��
	* 2��picture�ؼ���ʼ��
	* 3����ͼ
	*
	*
	*
	*
	**********************************/
    //1��������ʼ��-------------------
	m_nOffsetX    = 0;
	m_nOffsetY    = 0;
	m_nImgWidth   = 0;
	m_nImgHeight  = 0;
	m_strTips     = _T("");
	

	//2��picture�ؼ���ʼ��-----------
	GetDlgItem(IDC_PIC_FRONT)->MoveWindow(0, 0, 220, 160, TRUE);
	GetDlgItem(IDC_STA_BACK)->MoveWindow(230, 30, 200, 130, TRUE);

	m_strTips = _T("�뷭ת�����棬���ٵ�����գ�");
	GetDlgItem(IDC_STA_BACK)->SetWindowText(m_strTips);
	m_TipFont.CreatePointFont(200, _T("����"));
	GetDlgItem(IDC_STA_BACK)->SetFont(&m_TipFont);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CUDSFront::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	
	m_pImage.Load(g_strFrontImg);
	m_nImgWidth = m_pImage.GetWidth();
	m_nImgHeight= m_pImage.GetHeight();

	GetDlgItem(IDC_PIC_FRONT)->GetWindowRect(&m_rcPicRect);
	ScreenToClient(&m_rcPicRect);
	m_pImage.Resample(m_rcPicRect.Width(), m_rcPicRect.Height());

	CWnd* pWnd = NULL;
	pWnd = GetDlgItem(IDC_PIC_FRONT);
	m_pDC=pWnd->GetDC();
	m_ImageDC.CreateCompatibleDC(m_pDC);
	HBITMAP   tem_hBitmap;
	tem_hBitmap = m_pImage.MakeBitmap(m_ImageDC);
	CBitmap   tem_bBmp;
	tem_bBmp.Attach(tem_hBitmap);
	m_ImageDC.SelectObject(&tem_bBmp);
	m_nOffsetX = m_rcPicRect.left;
	m_nOffsetY = m_rcPicRect.top;
	m_pDC->BitBlt(0, 0, m_rcPicRect.right-m_nOffsetX, m_rcPicRect.bottom-m_nOffsetY, &m_ImageDC, 0, 0, SRCCOPY);	

	

	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}




BOOL CUDSFront::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN)
	{
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
