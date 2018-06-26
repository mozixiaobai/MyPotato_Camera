// UDSChildAdv.cpp : 实现文件
//

#include "stdafx.h"
#include "UDS SmartCamera v1.0.0.h"
#include "UDSChildAdv.h"
#include "afxdialogex.h"


// CUDSChildAdv 对话框

IMPLEMENT_DYNAMIC(CUDSChildAdv, CDialogEx)

CUDSChildAdv::CUDSChildAdv(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSChildAdv::IDD, pParent)
{

}

CUDSChildAdv::~CUDSChildAdv()
{
}

void CUDSChildAdv::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//-  DDX_Control(pDX, IDC_STA_OCXSUB, m_conStaFramsub);
	DDX_Control(pDX, IDC_CMB_SUBNAME, m_conComScannersub);
	DDX_Control(pDX, IDC_CMB_SUBDPI, m_conComDPIsub);
	DDX_Control(pDX, IDC_CHK_OPEN, m_conChkOpen);
	DDX_Control(pDX, IDC_STA_LCT0, m_conStaLct0);
	DDX_Control(pDX, IDC_BTN_SUBCAP, m_btnSubCap);
}


BEGIN_MESSAGE_MAP(CUDSChildAdv, CDialogEx)
	ON_CBN_SELCHANGE(IDC_CMB_SUBNAME, &CUDSChildAdv::OnSelchangeCmbSubname)
	ON_CBN_SELCHANGE(IDC_CMB_SUBDPI, &CUDSChildAdv::OnSelchangeCmbSubdpi)
	ON_BN_CLICKED(IDC_CHK_OPEN, &CUDSChildAdv::OnClickedChkOpen)
	ON_BN_CLICKED(IDC_CHK_GPS, &CUDSChildAdv::OnClickedChkGps)
	ON_BN_CLICKED(IDC_BTN_SUBCAP, &CUDSChildAdv::OnBnClickedBtnSubcap)
	ON_BN_CLICKED(IDC_CHK_MERGE, &CUDSChildAdv::OnBnClickedChkMerge)
	ON_BN_CLICKED(IDC_CHK_EXMERGER, &CUDSChildAdv::OnBnClickedChkExmerger)
	ON_STN_CLICKED(IDC_STA_LOCATION, &CUDSChildAdv::OnStnClickedStaLocation)
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_STA_LCT1, &CUDSChildAdv::OnStnClickedStaLct1)
	ON_STN_CLICKED(IDC_STA_LCT0, &CUDSChildAdv::OnStnClickedStaLct0)
	ON_STN_CLICKED(IDC_STA_LCT2, &CUDSChildAdv::OnStnClickedStaLct2)
	ON_STN_CLICKED(IDC_STA_LCT3, &CUDSChildAdv::OnStnClickedStaLct3)
	ON_STN_CLICKED(IDC_STA_LCT4, &CUDSChildAdv::OnStnClickedStaLct4)
	ON_STN_CLICKED(IDC_STA_LCT5, &CUDSChildAdv::OnStnClickedStaLct5)
	ON_STN_CLICKED(IDC_STA_LCT6, &CUDSChildAdv::OnStnClickedStaLct6)
	ON_STN_CLICKED(IDC_STA_LCT7, &CUDSChildAdv::OnStnClickedStaLct7)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CUDSChildAdv 消息处理程序


BOOL CUDSChildAdv::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/********************************************
	*
	*0、 变量初始化
	*1、 OCX控件初始化
	*2、CheckBox初始化
	*
	*4、副头打开前前控件初始化
	*5、画刷初始化
	*
	**********************************************/
	//0、--------------------------------------------
	m_pWndSub  = GetParentOwner();
	m_hWndSub  = m_pWndSub->m_hWnd;
	m_BExMerge = FALSE;
	m_BSubDownBk = FALSE;    //FALSE说明，没有使用OnPaint中的CImage类添加背景

	//1、--------------------------------------------

	//2、--------------------------------------------
	((CButton*)GetDlgItem(IDC_CHK_OPEN))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHK_MERGE))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHK_GPS))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHK_EXMERGER))->SetCheck(0);

	//3、---------------------------------------------

	//4、---------------------------------------------
	GetDlgItem(IDC_CHK_MERGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHK_GPS)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHK_EXMERGER)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SUBCAP)->EnableWindow(FALSE);
	GetDlgItem(IDC_CMB_SUBNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_CMB_SUBDPI)->EnableWindow(FALSE);
	

	//5、---------------------------------------------
	m_ColorBig   = RGB(214, 201, 201); 
	m_ColorLct0  = RGB(186, 198, 214);
	m_ColorLct1  = RGB(186, 198, 214);
	m_ColorLct2  = RGB(186, 198, 214);
	m_ColorLct3  = RGB(186, 198, 214);
	m_ColorLct4  = RGB(186, 198, 214);
	m_ColorLct5  = RGB(186, 198, 214);
	m_ColorLct6  = RGB(186, 198, 214);
	m_ColorLct7  = RGB(186, 198, 214);

	//6、----------------------------------------------
	//方法二：设置背景颜色,这种方法控件的背景色也会根据界面背景色发生改变
	CDialogEx::SetBackgroundColor(RGB(72,77,91));

	m_btnSubCap.Init(IDB_PNG_SUBCAP, BTN_IMG_1, BTN_TYPE_NORMAL);

	m_btnTipsSub.Create(this);
	m_btnTipsSub.AddTool(GetDlgItem(IDC_BTN_SUBCAP), _T("副头拍照"));
	m_btnTipsSub.SetDelayTime(200);   //设置延迟
	m_btnTipsSub.SetTipTextColor(RGB(0, 0, 0));//设置字体颜色
	m_btnTipsSub.SetTipBkColor(RGB(255, 255, 255));//设置提示框背景颜色
	m_btnTipsSub.Activate(TRUE); //启用提示功能


	SetWindowTheme(GetDlgItem(IDC_STA_GRPSC)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_GROUP_SUB_CAP)->GetSafeHwnd(), _T(""), _T(""));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CUDSChildAdv::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	//方法一：修改背景色
// 	CRect   rect;    
// 	GetClientRect(rect);    
// 	dc.FillSolidRect(rect,RGB(72,77,91));
	// 不为绘图消息调用 CDialogEx::OnPaint()
	if (m_BSubDownBk)
	{
		//加载图像背景
		CImage Image;
		CDC *pDC = GetDC();		
		Image.Load(_T("..\\Release\\res\\BK.png"));
		if (Image.IsNull())
		{
			CDialogEx::OnPaint();
			return;
		}
		if (Image.GetBPP() == 32) //确认该图像包含Alpha通道
		{
			int i;
			int j;
			for (i = 0; i < Image.GetWidth(); i++)
			{
				for (j = 0; j < Image.GetHeight(); j++)
				{
					byte *pByte = (byte *)Image.GetPixelAddress(i, j);
					pByte[0] = pByte[0] * pByte[3] / 255;
					pByte[1] = pByte[1] * pByte[3] / 255;
					pByte[2] = pByte[2] * pByte[3] / 255;
				}
			}
		}
		Image.Draw(pDC->m_hDC, 0, 0);
		Image.Destroy();
		ReleaseDC(pDC);
		m_BSubDownBk = FALSE;
	}
}


HBRUSH CUDSChildAdv::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	CBrush   m_brBrush;
	if (pWnd->GetDlgCtrlID() == IDC_STA_LOCATION)
	{
		m_brBrush.CreateSolidBrush(m_ColorBig);
		pDC->SetBkMode(OPAQUE);
		pDC->SetBkColor(m_ColorBig);
		return (HBRUSH)m_brBrush;
	}
	if (pWnd->GetDlgCtrlID()==IDC_STA_LCT0)
	{
		m_brBrush.CreateSolidBrush(m_ColorLct0);
		pDC->SetBkMode(OPAQUE);
		pDC->SetBkColor(m_ColorLct0);
		return (HBRUSH)m_brBrush;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STA_LCT1)
	{
		m_brBrush.CreateSolidBrush(m_ColorLct1);
		pDC->SetBkMode(OPAQUE);
		pDC->SetBkColor(m_ColorLct1);
		return (HBRUSH)m_brBrush;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STA_LCT2)
	{
		m_brBrush.CreateSolidBrush(m_ColorLct2);
		pDC->SetBkMode(OPAQUE);
		pDC->SetBkColor(m_ColorLct2);
		return (HBRUSH)m_brBrush;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STA_LCT3)
	{
		m_brBrush.CreateSolidBrush(m_ColorLct3);
		pDC->SetBkMode(OPAQUE);
		pDC->SetBkColor(m_ColorLct3);
		return (HBRUSH)m_brBrush;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STA_LCT4)
	{
		m_brBrush.CreateSolidBrush(m_ColorLct4);
		pDC->SetBkMode(OPAQUE);
		pDC->SetBkColor(m_ColorLct4);
		return (HBRUSH)m_brBrush;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STA_LCT5)
	{
		m_brBrush.CreateSolidBrush(m_ColorLct5);
		pDC->SetBkMode(OPAQUE);
		pDC->SetBkColor(m_ColorLct5);
		return (HBRUSH)m_brBrush;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STA_LCT6)
	{
		m_brBrush.CreateSolidBrush(m_ColorLct6);
		pDC->SetBkMode(OPAQUE);
		pDC->SetBkColor(m_ColorLct6);
		return (HBRUSH)m_brBrush;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STA_LCT7)
	{
		m_brBrush.CreateSolidBrush(m_ColorLct7);
		pDC->SetBkMode(OPAQUE);
		pDC->SetBkColor(m_ColorLct7);
		return (HBRUSH)m_brBrush;
	}

	//Static控件
	if (pWnd->GetDlgCtrlID()==IDC_STA_SUBNAME || pWnd->GetDlgCtrlID()==IDC_STA_SUBDPI ||pWnd->GetDlgCtrlID()==IDC_STACHK_OPEN ||
		pWnd->GetDlgCtrlID()==IDC_STACHK_GPS || pWnd->GetDlgCtrlID()==IDC_STACHK_EXMERGE)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		CFont   tem_Font;
		tem_Font.CreatePointFont(100, _T("宋体"));
		pDC->SelectObject(&tem_Font);
	}
	//CheckBox控件
// 	if (pWnd->GetDlgCtrlID() == IDC_CHK_OPEN || pWnd->GetDlgCtrlID() == IDC_CHK_GPS ||pWnd->GetDlgCtrlID()==IDC_CHK_EXMERGER)
// 	{
// 		pDC->SetTextColor(RGB(255, 255, 255));
// 
// 	}

	if (pWnd->GetDlgCtrlID()==IDC_STA_GRPSC || pWnd->GetDlgCtrlID()==IDC_GROUP_SUB_CAP)
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
	}
	
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


BOOL CUDSChildAdv::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_MOUSEMOVE)
	{
		m_btnTipsSub.RelayEvent(pMsg);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


//打开副头
void CUDSChildAdv::OnClickedChkOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_OPEN))
	{
		GetDlgItem(IDC_CHK_MERGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_GPS)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_EXMERGER)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SUBCAP)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_SUBNAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_SUBDPI)->EnableWindow(TRUE);
		::SendMessage(m_hWndSub, WM_SUBSWITCH, 1, 0);  //打开副头
	}
	else
	{
		::SendMessage(m_hWndSub, WM_SUBSWITCH, 0, 0);  //关闭副头
		((CButton*)GetDlgItem(IDC_CHK_MERGE))->SetCheck(0);
		GetDlgItem(IDC_CHK_MERGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_GPS)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_EXMERGER)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SUBCAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_SUBNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_SUBDPI)->EnableWindow(FALSE);
		
	}

}


//选择副头
void CUDSChildAdv::OnSelchangeCmbSubname()
{
	// TODO: 在此添加控件通知处理程序代码
	//Combo索引和Camera索引的对应问题
	int   tem_nSubNameIndex = m_conComScannersub.GetCurSel();
	::SendMessage(m_hWndSub, WM_SUBSWITCH, tem_nSubNameIndex, 1);  //发送选中的索引信息
}


//选择分辨率
void CUDSChildAdv::OnSelchangeCmbSubdpi()
{
	// TODO: 在此添加控件通知处理程序代码
	int  tem_nSubDpiIndex = m_conComDPIsub.GetCurSel();
	::SendMessage(m_hWndSub, WM_SUBSWITCH, tem_nSubDpiIndex, 2);
}

//废弃——————直接通过合并方式解决
//是否画面合并
void CUDSChildAdv::OnBnClickedChkMerge()
{

}


//内部合并
void CUDSChildAdv::OnClickedChkGps()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_EXMERGER))
	{
		((CButton*)GetDlgItem(IDC_CHK_EXMERGER))->SetCheck(0);
		m_BExMerge = FALSE;
	}
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_GPS))
	{
		//内部合并
		::SendMessage(m_hWndSub, WM_SUBSWITCH, 1, 3);
		m_ColorLct0  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT0)->InvalidateRect(NULL);
		m_ColorLct1  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT1)->InvalidateRect(NULL);
		m_ColorLct2  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT2)->InvalidateRect(NULL);
		m_ColorLct3  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT3)->InvalidateRect(NULL);
		m_ColorLct4  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT4)->InvalidateRect(NULL);
		m_ColorLct5  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT5)->InvalidateRect(NULL);
		m_ColorLct6  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT6)->InvalidateRect(NULL);
		m_ColorLct7  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT7)->InvalidateRect(NULL);
	}
	else
	{
		//关闭合并
		::SendMessage(m_hWndSub, WM_SUBSWITCH, 2, 3);
	}
}


//外部合并
void CUDSChildAdv::OnBnClickedChkExmerger()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_GPS))
	{
		((CButton*)GetDlgItem(IDC_CHK_GPS))->SetCheck(0);
	} 
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_EXMERGER))
	{
		//外部合并
		::SendMessage(m_hWndSub, WM_SUBSWITCH, 0, 3);
		m_BExMerge = TRUE;
		m_ColorLct0  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT0)->InvalidateRect(NULL);
		m_ColorLct1  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT1)->InvalidateRect(NULL);
		m_ColorLct2  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT2)->InvalidateRect(NULL);
		m_ColorLct3  = RGB(244,  31,  31);
		GetDlgItem(IDC_STA_LCT3)->InvalidateRect(NULL);
		m_ColorLct4  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT4)->InvalidateRect(NULL);
		m_ColorLct5  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT5)->InvalidateRect(NULL);
		m_ColorLct6  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT6)->InvalidateRect(NULL);
		m_ColorLct7  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT7)->InvalidateRect(NULL);
	}
	else
	{
		//关闭合并
		::SendMessage(m_hWndSub, WM_SUBSWITCH, 2, 3);
		m_BExMerge = FALSE;
		m_ColorLct0  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT0)->InvalidateRect(NULL);
		m_ColorLct1  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT1)->InvalidateRect(NULL);
		m_ColorLct2  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT2)->InvalidateRect(NULL);
		m_ColorLct3  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT3)->InvalidateRect(NULL);
		m_ColorLct4  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT4)->InvalidateRect(NULL);
		m_ColorLct5  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT5)->InvalidateRect(NULL);
		m_ColorLct6  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT6)->InvalidateRect(NULL);
		m_ColorLct7  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT7)->InvalidateRect(NULL);
	}

}


//副头拍照
void CUDSChildAdv::OnBnClickedBtnSubcap()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hWndSub, WM_SUBSWITCH, 0, 6);
}


//选择定位区域------------------------------------------------------------------
void CUDSChildAdv::OnStnClickedStaLocation()
{
	// TODO: 在此添加控件通知处理程序代码

}


void CUDSChildAdv::OnStnClickedStaLct0()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_BExMerge)
	{
		m_ColorLct0  = RGB(244,  31,  31);
		GetDlgItem(IDC_STA_LCT0)->InvalidateRect(NULL);
		m_ColorLct1  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT1)->InvalidateRect(NULL);
		m_ColorLct2  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT2)->InvalidateRect(NULL);
		m_ColorLct3  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT3)->InvalidateRect(NULL);
		m_ColorLct4  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT4)->InvalidateRect(NULL);
		m_ColorLct5  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT5)->InvalidateRect(NULL);
		m_ColorLct6  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT6)->InvalidateRect(NULL);
		m_ColorLct7  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT7)->InvalidateRect(NULL);

		::SendMessage(m_hWndSub, WM_SUBSWITCH, 0, 4);
	}
}


void CUDSChildAdv::OnStnClickedStaLct1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_BExMerge)
	{
		m_ColorLct0  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT0)->InvalidateRect(NULL);
		m_ColorLct1  = RGB(244,  31,  31);
		GetDlgItem(IDC_STA_LCT1)->InvalidateRect(NULL);
		m_ColorLct2  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT2)->InvalidateRect(NULL);
		m_ColorLct3  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT3)->InvalidateRect(NULL);
		m_ColorLct4  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT4)->InvalidateRect(NULL);
		m_ColorLct5  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT5)->InvalidateRect(NULL);
		m_ColorLct6  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT6)->InvalidateRect(NULL);
		m_ColorLct7  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT7)->InvalidateRect(NULL);

		::SendMessage(m_hWndSub, WM_SUBSWITCH, 1, 4);
	}	
}



void CUDSChildAdv::OnStnClickedStaLct2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_BExMerge)
	{
		m_ColorLct0  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT0)->InvalidateRect(NULL);
		m_ColorLct1  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT1)->InvalidateRect(NULL);
		m_ColorLct2  = RGB(244,  31,  31);
		GetDlgItem(IDC_STA_LCT2)->InvalidateRect(NULL);
		m_ColorLct3  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT3)->InvalidateRect(NULL);
		m_ColorLct4  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT4)->InvalidateRect(NULL);
		m_ColorLct5  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT5)->InvalidateRect(NULL);
		m_ColorLct6  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT6)->InvalidateRect(NULL);
		m_ColorLct7  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT7)->InvalidateRect(NULL);

		::SendMessage(m_hWndSub, WM_SUBSWITCH, 2, 4);
	}
}


void CUDSChildAdv::OnStnClickedStaLct3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_BExMerge)
	{
		m_ColorLct0  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT0)->InvalidateRect(NULL);
		m_ColorLct1  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT1)->InvalidateRect(NULL);
		m_ColorLct2  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT2)->InvalidateRect(NULL);
		m_ColorLct3  = RGB(244,  31,  31);
		GetDlgItem(IDC_STA_LCT3)->InvalidateRect(NULL);
		m_ColorLct4  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT4)->InvalidateRect(NULL);
		m_ColorLct5  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT5)->InvalidateRect(NULL);
		m_ColorLct6  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT6)->InvalidateRect(NULL);
		m_ColorLct7  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT7)->InvalidateRect(NULL);

		::SendMessage(m_hWndSub, WM_SUBSWITCH, 3, 4);
	}	
}


void CUDSChildAdv::OnStnClickedStaLct4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_BExMerge)
	{
		m_ColorLct0  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT0)->InvalidateRect(NULL);
		m_ColorLct1  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT1)->InvalidateRect(NULL);
		m_ColorLct2  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT2)->InvalidateRect(NULL);
		m_ColorLct3  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT3)->InvalidateRect(NULL);
		m_ColorLct4  = RGB(244,  31,  31);
		GetDlgItem(IDC_STA_LCT4)->InvalidateRect(NULL);
		m_ColorLct5  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT5)->InvalidateRect(NULL);
		m_ColorLct6  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT6)->InvalidateRect(NULL);
		m_ColorLct7  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT7)->InvalidateRect(NULL);

		::SendMessage(m_hWndSub, WM_SUBSWITCH, 4, 4);
	}	
}


void CUDSChildAdv::OnStnClickedStaLct5()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_BExMerge)
	{
		m_ColorLct0  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT0)->InvalidateRect(NULL);
		m_ColorLct1  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT1)->InvalidateRect(NULL);
		m_ColorLct2  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT2)->InvalidateRect(NULL);
		m_ColorLct3  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT3)->InvalidateRect(NULL);
		m_ColorLct4  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT4)->InvalidateRect(NULL);
		m_ColorLct5  = RGB(244,  31,  31);
		GetDlgItem(IDC_STA_LCT5)->InvalidateRect(NULL);
		m_ColorLct6  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT6)->InvalidateRect(NULL);
		m_ColorLct7  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT7)->InvalidateRect(NULL);

		::SendMessage(m_hWndSub, WM_SUBSWITCH, 5, 4);
	}
}


void CUDSChildAdv::OnStnClickedStaLct6()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_BExMerge)
	{
		m_ColorLct0  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT0)->InvalidateRect(NULL);
		m_ColorLct1  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT1)->InvalidateRect(NULL);
		m_ColorLct2  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT2)->InvalidateRect(NULL);
		m_ColorLct3  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT3)->InvalidateRect(NULL);
		m_ColorLct4  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT4)->InvalidateRect(NULL);
		m_ColorLct5  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT5)->InvalidateRect(NULL);
		m_ColorLct6  = RGB(244,  31,  31);
		GetDlgItem(IDC_STA_LCT6)->InvalidateRect(NULL);
		m_ColorLct7  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT7)->InvalidateRect(NULL);

		::SendMessage(m_hWndSub, WM_SUBSWITCH, 6, 4);
	}
}


void CUDSChildAdv::OnStnClickedStaLct7()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_BExMerge)
	{
		m_ColorLct0  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT0)->InvalidateRect(NULL);
		m_ColorLct1  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT1)->InvalidateRect(NULL);
		m_ColorLct2  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT2)->InvalidateRect(NULL);
		m_ColorLct3  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT3)->InvalidateRect(NULL);
		m_ColorLct4  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT4)->InvalidateRect(NULL);
		m_ColorLct5  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT5)->InvalidateRect(NULL);
		m_ColorLct6  = RGB(186, 198, 214);
		GetDlgItem(IDC_STA_LCT6)->InvalidateRect(NULL);
		m_ColorLct7  = RGB(244,  31,  31);
		GetDlgItem(IDC_STA_LCT7)->InvalidateRect(NULL);

		::SendMessage(m_hWndSub, WM_SUBSWITCH, 7, 4);
	}
}
//---------------------------------------------------


