// UDSCardFront.cpp : 实现文件
//

#include "stdafx.h"
#include "UDSCardFront.h"
#include "afxdialogex.h"



// CUDSCardFront 对话框
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


// CUDSCardFront 消息处理程序


BOOL CUDSCardFront::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CUDSCardFront::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码

	// 不为绘图消息调用 CDialogEx::OnPaint()
}


void CUDSCardFront::OnBnClickedBtnTest()
{
	// TODO: 在此添加控件通知处理程序代码

}
