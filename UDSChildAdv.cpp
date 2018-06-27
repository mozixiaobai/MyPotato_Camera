// UDSChildAdv.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDS SmartCamera v1.0.0.h"
#include "UDSChildAdv.h"
#include "afxdialogex.h"


// CUDSChildAdv �Ի���

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


// CUDSChildAdv ��Ϣ�������


BOOL CUDSChildAdv::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	/********************************************
	*
	*0�� ������ʼ��
	*1�� OCX�ؼ���ʼ��
	*2��CheckBox��ʼ��
	*
	*4����ͷ��ǰǰ�ؼ���ʼ��
	*5����ˢ��ʼ��
	*
	**********************************************/
	//0��--------------------------------------------
	m_pWndSub  = GetParentOwner();
	m_hWndSub  = m_pWndSub->m_hWnd;
	m_BExMerge = FALSE;
	m_BSubDownBk = FALSE;    //FALSE˵����û��ʹ��OnPaint�е�CImage����ӱ���

	//1��--------------------------------------------

	//2��--------------------------------------------
	((CButton*)GetDlgItem(IDC_CHK_OPEN))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHK_MERGE))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHK_GPS))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHK_EXMERGER))->SetCheck(0);

	//3��---------------------------------------------

	//4��---------------------------------------------
	GetDlgItem(IDC_CHK_MERGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHK_GPS)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHK_EXMERGER)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SUBCAP)->EnableWindow(FALSE);
	GetDlgItem(IDC_CMB_SUBNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_CMB_SUBDPI)->EnableWindow(FALSE);
	

	//5��---------------------------------------------
	m_ColorBig   = RGB(214, 201, 201); 
	m_ColorLct0  = RGB(186, 198, 214);
	m_ColorLct1  = RGB(186, 198, 214);
	m_ColorLct2  = RGB(186, 198, 214);
	m_ColorLct3  = RGB(186, 198, 214);
	m_ColorLct4  = RGB(186, 198, 214);
	m_ColorLct5  = RGB(186, 198, 214);
	m_ColorLct6  = RGB(186, 198, 214);
	m_ColorLct7  = RGB(186, 198, 214);

	//6��----------------------------------------------
	//�����������ñ�����ɫ,���ַ����ؼ��ı���ɫҲ����ݽ��汳��ɫ�����ı�
	CDialogEx::SetBackgroundColor(RGB(72,77,91));

	m_btnSubCap.Init(IDB_PNG_SUBCAP, BTN_IMG_1, BTN_TYPE_NORMAL);

	m_btnTipsSub.Create(this);
	m_btnTipsSub.AddTool(GetDlgItem(IDC_BTN_SUBCAP), _T("��ͷ����"));
	m_btnTipsSub.SetDelayTime(200);   //�����ӳ�
	m_btnTipsSub.SetTipTextColor(RGB(0, 0, 0));//����������ɫ
	m_btnTipsSub.SetTipBkColor(RGB(255, 255, 255));//������ʾ�򱳾���ɫ
	m_btnTipsSub.Activate(TRUE); //������ʾ����


	SetWindowTheme(GetDlgItem(IDC_STA_GRPSC)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_GROUP_SUB_CAP)->GetSafeHwnd(), _T(""), _T(""));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CUDSChildAdv::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	//����һ���޸ı���ɫ
// 	CRect   rect;    
// 	GetClientRect(rect);    
// 	dc.FillSolidRect(rect,RGB(72,77,91));
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	if (m_BSubDownBk)
	{
		//����ͼ�񱳾�
		CImage Image;
		CDC *pDC = GetDC();		
		Image.Load(_T("..\\Release\\res\\BK.png"));
		if (Image.IsNull())
		{
			CDialogEx::OnPaint();
			return;
		}
		if (Image.GetBPP() == 32) //ȷ�ϸ�ͼ�����Alphaͨ��
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

	// TODO:  �ڴ˸��� DC ���κ�����
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

	//Static�ؼ�
	if (pWnd->GetDlgCtrlID()==IDC_STA_SUBNAME || pWnd->GetDlgCtrlID()==IDC_STA_SUBDPI ||pWnd->GetDlgCtrlID()==IDC_STACHK_OPEN ||
		pWnd->GetDlgCtrlID()==IDC_STACHK_GPS || pWnd->GetDlgCtrlID()==IDC_STACHK_EXMERGE)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		CFont   tem_Font;
		tem_Font.CreatePointFont(100, _T("����"));
		pDC->SelectObject(&tem_Font);
	}
	//CheckBox�ؼ�
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
	
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


BOOL CUDSChildAdv::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_MOUSEMOVE)
	{
		m_btnTipsSub.RelayEvent(pMsg);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


//�򿪸�ͷ
void CUDSChildAdv::OnClickedChkOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_OPEN))
	{
		GetDlgItem(IDC_CHK_MERGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_GPS)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_EXMERGER)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SUBCAP)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_SUBNAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_SUBDPI)->EnableWindow(TRUE);
		::SendMessage(m_hWndSub, WM_SUBSWITCH, 1, 0);  //�򿪸�ͷ
	}
	else
	{
		::SendMessage(m_hWndSub, WM_SUBSWITCH, 0, 0);  //�رո�ͷ
		((CButton*)GetDlgItem(IDC_CHK_MERGE))->SetCheck(0);
		GetDlgItem(IDC_CHK_MERGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_GPS)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_EXMERGER)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SUBCAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_SUBNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_SUBDPI)->EnableWindow(FALSE);
		
	}

}


//ѡ��ͷ
void CUDSChildAdv::OnSelchangeCmbSubname()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//Combo������Camera�����Ķ�Ӧ����
	int   tem_nSubNameIndex = m_conComScannersub.GetCurSel();
	::SendMessage(m_hWndSub, WM_SUBSWITCH, tem_nSubNameIndex, 1);  //����ѡ�е�������Ϣ
}


//ѡ��ֱ���
void CUDSChildAdv::OnSelchangeCmbSubdpi()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int  tem_nSubDpiIndex = m_conComDPIsub.GetCurSel();
	::SendMessage(m_hWndSub, WM_SUBSWITCH, tem_nSubDpiIndex, 2);
}

//����������������ֱ��ͨ���ϲ���ʽ���
//�Ƿ���ϲ�
void CUDSChildAdv::OnBnClickedChkMerge()
{

}


//�ڲ��ϲ�
void CUDSChildAdv::OnClickedChkGps()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_EXMERGER))
	{
		((CButton*)GetDlgItem(IDC_CHK_EXMERGER))->SetCheck(0);
		m_BExMerge = FALSE;
	}
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_GPS))
	{
		//�ڲ��ϲ�
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
		//�رպϲ�
		::SendMessage(m_hWndSub, WM_SUBSWITCH, 2, 3);
	}
}


//�ⲿ�ϲ�
void CUDSChildAdv::OnBnClickedChkExmerger()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_GPS))
	{
		((CButton*)GetDlgItem(IDC_CHK_GPS))->SetCheck(0);
	} 
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_EXMERGER))
	{
		//�ⲿ�ϲ�
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
		//�رպϲ�
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


//��ͷ����
void CUDSChildAdv::OnBnClickedBtnSubcap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(m_hWndSub, WM_SUBSWITCH, 0, 6);
}


//ѡ��λ����------------------------------------------------------------------
void CUDSChildAdv::OnStnClickedStaLocation()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}


void CUDSChildAdv::OnStnClickedStaLct0()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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


