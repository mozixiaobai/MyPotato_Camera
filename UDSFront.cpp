// UDSFront.cpp : 实现文件
//

#include "stdafx.h"
#include "UDSFront.h"
#include "afxdialogex.h"


// CUDSFront 对话框

extern CString    g_strFrontImg;   //身份证正面图像路径

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


// CUDSFront 消息处理程序


BOOL CUDSFront::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/********************************
	*         目录
	* 1、变量初始化
	* 2、picture控件初始化
	* 3、绘图
	*
	*
	*
	*
	**********************************/
    //1、变量初始化-------------------
	m_nOffsetX    = 0;
	m_nOffsetY    = 0;
	m_nImgWidth   = 0;
	m_nImgHeight  = 0;
	m_strTips     = _T("");
	

	//2、picture控件初始化-----------
	GetDlgItem(IDC_PIC_FRONT)->MoveWindow(0, 0, 220, 160, TRUE);
	GetDlgItem(IDC_STA_BACK)->MoveWindow(230, 30, 200, 130, TRUE);

	m_strTips = _T("请翻转至背面，并再点击拍照！");
	GetDlgItem(IDC_STA_BACK)->SetWindowText(m_strTips);
	m_TipFont.CreatePointFont(200, _T("隶书"));
	GetDlgItem(IDC_STA_BACK)->SetFont(&m_TipFont);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CUDSFront::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	
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

	

	// 不为绘图消息调用 CDialogEx::OnPaint()
}




BOOL CUDSFront::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
