// UDSChildNor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDS SmartCamera v1.0.0.h"
#include "UDSChildNor.h"
#include "afxdialogex.h"
#include "PngButton.h"


// CUDSChildNor �Ի���

IMPLEMENT_DYNAMIC(CUDSChildNor, CDialogEx)

CUDSChildNor::CUDSChildNor(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSChildNor::IDD, pParent)
{

	//  m_conStaBright = 0;
	//  m_conStaBrt = 0;
	m_conStaExp = 0;
	m_conStaBrg = 0;
	m_conStaExpStr = _T("");
}

CUDSChildNor::~CUDSChildNor()
{
}

void CUDSChildNor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_SCANNERS, m_conComScanner);
	DDX_Control(pDX, IDC_CMB_DPI, m_conComReso);
	DDX_Control(pDX, IDC_CMB_FILEMODE, m_conComFilemode);
	DDX_Control(pDX, IDC_CMB_COLORMODE, m_conComColormode);
	//  DDX_Control(pDX, IDC_SLID_BRIGHT, m_conSlidBright);
	DDX_Control(pDX, IDC_SLID_EXPOSURE, m_conSlidExpos);
	//  DDX_Text(pDX, IDC_STA_BRIGHT, m_conStaBright);
	//  DDX_Text(pDX, IDC_STA_BRT, m_conStaBrt);
	DDX_Text(pDX, IDC_STA_EXP, m_conStaExp);
	DDX_Control(pDX, IDC_CHK_AUTOEXP, m_conChkExp);
	//  DDX_Control(pDX, IDC_RICHEDIT2_INCIDENT, m_conRichEdit);
	DDX_Control(pDX, IDC_RICHEDIT2_INCIDENT, m_conRichEdit);
	DDX_Control(pDX, IDC_STA_GRP_SM, m_groupScanMain1);
	DDX_Control(pDX, IDC_BTN_TEST, m_btnStart);
	DDX_Control(pDX, IDC_BTN_END, m_btnEnd);
	DDX_Control(pDX, IDC_STA_TIMER, m_staTimer);
	DDX_Control(pDX, IDC_CHK_AUTOCRT, m_chkAutoCrt);
	DDX_Control(pDX, IDC_SLID_BRIGHT, m_conSlidBright);
	DDX_Text(pDX, IDC_STA_BRG, m_conStaBrg);
	DDX_Text(pDX, IDC_STA_EXP, m_conStaExpStr);
	DDX_Control(pDX, IDC_CMB_AUDEO, m_conAudio);
	DDX_Control(pDX, IDC_CMB_AUDEOFORMAT, m_conAudioFmt);
}


BEGIN_MESSAGE_MAP(CUDSChildNor, CDialogEx)
//	ON_STN_CLICKED(IDC_STA_EXP, &CUDSChildNor::OnStnClickedStaExp)
	ON_BN_CLICKED(IDC_BTN_TEST, &CUDSChildNor::OnBnClickedBtnTest)
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_BRIGHT, &CUDSChildNor::OnNMCustomdrawSlidBright)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_EXPOSURE, &CUDSChildNor::OnNMCustomdrawSlidExposure)
	ON_CBN_SELCHANGE(IDC_CMB_SCANNERS, &CUDSChildNor::OnSelchangeCmbScanners)
	ON_CBN_SELCHANGE(IDC_CMB_FILEMODE, &CUDSChildNor::OnSelchangeCmbFilemode)
	ON_CBN_SELCHANGE(IDC_CMB_COLORMODE, &CUDSChildNor::OnSelchangeCmbColormode)
	ON_CBN_SELCHANGE(IDC_CMB_DPI, &CUDSChildNor::OnSelchangeCmbDpi)
	ON_BN_CLICKED(IDC_CHK_AUTOCRT, &CUDSChildNor::OnBnClickedChkAutocrt)
	ON_BN_CLICKED(IDC_CHK_AUTOEXP, &CUDSChildNor::OnBnClickedChkAutoexp)
	ON_BN_CLICKED(IDC_BTN_END, &CUDSChildNor::OnBnClickedBtnEnd)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_BRIGHT, &CUDSChildNor::OnCustomdrawSlidBright)
	ON_CBN_SELCHANGE(IDC_CMB_AUDEO, &CUDSChildNor::OnSelchangeCmbAudeo)
	ON_CBN_SELCHANGE(IDC_CMB_AUDEOFORMAT, &CUDSChildNor::OnSelchangeCmbAudeoformat)
	ON_BN_CLICKED(IDC_CHK_AUTROTATE, &CUDSChildNor::OnClickedChkAutrotate)
	ON_BN_CLICKED(IDC_CHK_OPTIMIZE, &CUDSChildNor::OnClickedChkOptimize)
END_MESSAGE_MAP()


// CUDSChildNor ��Ϣ�������


BOOL CUDSChildNor::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	/***************************************
	*
	*0.0��ȡ�����ļ�
	*0�� ������ʼ��
	*1�� Combox�ؼ���ʼ��
	*2�� Slider��CheckBox��ʼ��
	*
	*
	***************************************/
	//0.0--------------------------------------
	/*
	TCHAR        tem_tcFilepath[MAX_PATH+1] = {0};
	CString      tem_strIniPath;
	CString      tem_strRead;
	GetModuleFileName(NULL, tem_tcFilepath, MAX_PATH);
	(_tcsrchr(tem_tcFilepath, _T('\\')))[1] = 0;

	tem_strIniPath    = tem_tcFilepath;


	int tem_nDirIndex = tem_strIniPath.ReverseFind('\\');
	tem_strIniPath = tem_strIniPath.Mid(0, tem_nDirIndex);

	tem_nDirIndex = tem_strIniPath.ReverseFind('\\');
	tem_strIniPath = tem_strIniPath.Mid(0, tem_nDirIndex+1);

	tem_strIniPath   += _T("config.ini");   //�����ļ�·��
	tem_strIniPath.Replace(_T("\\"), _T("\\\\"));
	*/

	CString      tem_strIniPath;
	CString      tem_strRead;

	TCHAR          tem_cMyDocument[MAX_PATH] = {0};
	LPITEMIDLIST   tem_Pid = NULL;
	SHGetSpecialFolderLocation(NULL, CSIDL_PERSONAL, &tem_Pid);
	if (tem_Pid && SHGetPathFromIDList(tem_Pid, tem_cMyDocument))
	{
		tem_strIniPath = tem_cMyDocument;
		tem_strIniPath   += _T("\\");
		tem_strIniPath   += _T("UDSData\\");
		tem_strIniPath   += _T("config.ini");   //�����ļ�·��
		m_strIniPath      = tem_strIniPath;
//		tem_strIniPath.Replace(_T("\\"), _T("\\\\"));
	}
	
	


	int          tem_nAutoCrop;                     //��ʼ���Զ����к��Զ��ع�
	int          tem_nAutoExp;
	
	//0��---------------------------------------

	m_nIndexScanner = 0;
	m_nIndexDPI     = 0;
//	m_nIndexFile    = 1;
//	m_nIndexColor   = 2;
	m_nAudioIndex   = 0;
	//�������ļ���
	::GetPrivateProfileString(_T("ParentCamera"), _T("FileMode"), _T("û���ҵ�FileMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nIndexFile    = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
	::GetPrivateProfileString(_T("ParentCamera"), _T("ColorMode"), _T("û���ҵ�ColorMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nIndexColor   = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
	::GetPrivateProfileString(_T("ParentCamera"), _T("AutoCrop"), _T("û���ҵ�AutoCrop��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nAutoCrop   = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
	::GetPrivateProfileString(_T("ParentCamera"), _T("AutoExp"), _T("û���ҵ�AutoExp��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nAutoExp    = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	m_BBegin        = FALSE;
	m_BEnd          =TRUE;
	m_pWnd = GetParentOwner();
	m_hWnd = m_pWnd->m_hWnd;
	m_BAutoExp      = TRUE;
	m_BMainDownBk   = FALSE;    //FALSE˵����û��ʹ��OnPaint�е�CImage����ӱ���
    
	//1��---------------------------------------
	m_conComFilemode.InsertString(0, _T("bmp"));
	m_conComFilemode.InsertString(1, _T("jpg"));
	m_conComFilemode.InsertString(2, _T("tif"));
	m_conComFilemode.InsertString(3, _T("png"));
	m_conComFilemode.InsertString(4, _T("pdf"));
	m_conComFilemode.InsertString(5, _T("base64"));
	m_conComFilemode.InsertString(6, _T("dcm"));
	m_conComFilemode.InsertString(7, _T("ofd"));
	m_conComFilemode.InsertString(8, _T("tga"));
	m_conComFilemode.InsertString(9, _T("pcx"));
	m_conComFilemode.InsertString(10, _T("ras"));

	m_conComFilemode.SetCurSel(m_nIndexFile);

	m_conComColormode.InsertString(0, _T("�ڰ�"));
	m_conComColormode.InsertString(1, _T("�Ҷ�"));
	m_conComColormode.InsertString(2, _T("��ɫ"));
	m_conComColormode.SetCurSel(m_nIndexColor);

	m_conAudioFmt.InsertString(0, _T("mp4"));
	m_conAudioFmt.InsertString(1, _T("wmv"));
	m_conAudioFmt.InsertString(2, _T("avi"));
	m_conAudioFmt.SetCurSel(0);

	//2��---------------------------------------
	((CButton*)GetDlgItem(IDC_CHK_AUTOCRT))->SetCheck(tem_nAutoCrop);
//	((CButton*)GetDlgItem(IDC_CHK_AUTOEXP))->SetCheck(tem_nAutoExp);
	((CButton*)GetDlgItem(IDC_CHK_AUTOEXP))->SetCheck(TRUE);
	m_conSlidExpos.EnableWindow(FALSE);
	

	//3��---------------------------------------
	//�����������ñ�����ɫ,���ַ����ؼ��ı���ɫҲ����ݽ��汳��ɫ�����ı�
//	LoadPicture(m_img, IDB_PNG_BK);
	CDialogEx::SetBackgroundColor(RGB(72,77,91));
	
	m_btnStart.Init(IDB_PNG_BEGIN, BTN_IMG_1, BTN_TYPE_NORMAL);
	m_btnEnd.Init(IDB_PNG_END, BTN_IMG_1, BTN_TYPE_NORMAL);

	m_btnTipsMain.Create(this);
	m_btnTipsMain.AddTool(GetDlgItem(IDC_BTN_TEST), _T("��ʼ¼��"));
	m_btnTipsMain.AddTool(GetDlgItem(IDC_BTN_END), _T("����¼��"));
	m_btnTipsMain.SetDelayTime(200);   //�����ӳ�
	m_btnTipsMain.SetTipTextColor(RGB(0, 0, 0));//����������ɫ
	m_btnTipsMain.SetTipBkColor(RGB(255, 255, 255));//������ʾ�򱳾���ɫ
	m_btnTipsMain.Activate(TRUE); //������ʾ����

	//RichEditControl�Ż�
	//���ñ���ɫ-----
	m_conRichEdit.SetBackgroundColor(FALSE, RGB(72,77,91));
	
	//����һ���������壬������������ɫ
// 	CFont  tem_fontRichEdit;
// 	tem_fontRichEdit.CreateFont(12, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, 0, 1, OUT_DEFAULT_PRECIS,
// 		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_SWISS, _T("����"));
// 	m_conRichEdit.SetFont(&tem_fontRichEdit);

	//�����������������Լ�������ɫ
	
	ZeroMemory(&tem_fontRichEdit, sizeof(CHARFORMAT));
// 	tem_RichEdit.dwMask|=CFM_BOLD;
// 	tem_RichEdit.dwEffects|=CFE_BOLD; //���壬ȡ����cf.dwEffects&=~CFE_BOLD;
// 	tem_RichEdit.dwMask|=CFM_ITALIC;
// 	tem_RichEdit.dwEffects|=CFE_ITALIC; //б�壬ȡ����cf.dwEffects&=~CFE_ITALIC;
// 	tem_RichEdit.dwMask|=CFM_UNDERLINE;
// 	tem_RichEdit.dwEffects|=CFE_UNDERLINE; //б�壬ȡ����cf.dwEffects&=~CFE_UNDERLINE;
	tem_fontRichEdit.dwMask|=CFM_COLOR;
	tem_fontRichEdit.crTextColor = RGB(255, 255, 255); //������ɫ
	tem_fontRichEdit.dwMask|=CFM_SIZE;
	tem_fontRichEdit.yHeight =200; //���ø߶�
	tem_fontRichEdit.dwMask|=CFM_FACE;
//	strcpy(tem_RichEdit.szFaceName ,_T("����")); //��������, ���ֽ���ʹ��
	wcscpy(tem_fontRichEdit.szFaceName ,_T("����")); //�������壬Unicode��ʹ��
	m_conRichEdit.SetSelectionCharFormat(tem_fontRichEdit);

	
//	SetWindowTheme(GetDlgItem(IDC_STA_GRP_SM)->GetSafeHwnd(), L"", L"");
	SetWindowTheme(GetDlgItem(IDC_STA_GROUPNEW)->GetSafeHwnd(), _T(""), _T(""));  //����GroupBox������������ɫ
	SetWindowTheme(GetDlgItem(IDC_STA_GRPIS)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_GROUPVIDEO)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_GROUP_INCIDENT)->GetSafeHwnd(), _T(""), _T(""));

	int tem_nRead = 0;
	::GetPrivateProfileString(_T("Resource"), _T("AutoRotate"), _T("û���ҵ�AutoRotate��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead    = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
	if (tem_nRead == 0)
	{
		((CButton*)GetDlgItem(IDC_CHK_AUTROTATE))->SetCheck(FALSE);
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_AUTROTATE))->SetCheck(TRUE);
	}
	
	tem_nRead = 0;
	::GetPrivateProfileString(_T("Resource"), _T("AutoOptimize"), _T("û���ҵ�AutoOptimize��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nRead    = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
	if (tem_nRead == 0)
	{
		((CButton*)GetDlgItem(IDC_CHK_OPTIMIZE))->SetCheck(FALSE);
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_OPTIMIZE))->SetCheck(TRUE);
	}


	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CUDSChildNor::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	//����1�����ñ�����ɫ
// 	CRect   rect;    
// 	GetClientRect(rect);    
// 	dc.FillSolidRect(rect,RGB(72,77,91));  
	if (m_BMainDownBk)
	{
		//����һ��
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
		m_BMainDownBk = FALSE;
		

		 	
		//��������
		/*
		CPaintDC dc(this);
		CDC* pDC = &dc;

		CDC dcMem;
		dcMem.CreateCompatibleDC(pDC);

		CRect rcClient;
		GetClientRect(rcClient);

		CBitmap memBitmap;
		memBitmap.CreateCompatibleBitmap(pDC, rcClient.Width(), rcClient.Height());
		dcMem.SelectObject(memBitmap);

		dcMem.FillSolidRect(rcClient, RGB(255, 255, 255));	//���û�����ɫ

		if (!m_img.IsNull())
		{
			CRect rcImg = CRect(0, 0, m_img.GetWidth(), m_img.GetHeight());
			m_img.Draw(dcMem.m_hDC, rcImg, rcImg);
		}

		pDC->BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &dcMem, 0, 0, SRCCOPY);
		memBitmap.DeleteObject();
		*/
	}

	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


HBRUSH CUDSChildNor::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO:  �ڴ˸��� DC ���κ�����
	//����������---------------------
	if (pWnd->GetDlgCtrlID() == IDC_SLID_EXPOSURE || pWnd->GetDlgCtrlID() == IDC_SLID_BRIGHT)
	{
		return (HBRUSH) CreateSolidBrush(RGB(72,77,91));   //������ˢCBrush��CreateSolidBrush������ͬ���������
	}
	//Static��̬�ؼ�-----------------
	if (pWnd->GetDlgCtrlID()==IDC_STA_NAME || pWnd->GetDlgCtrlID()==IDC_STA_DPI || pWnd->GetDlgCtrlID()==IDC_STA_FILEMODE ||
		pWnd->GetDlgCtrlID()==IDC_STA_COLORMODE || pWnd->GetDlgCtrlID()==IDC_STA_EXPOSURE || pWnd->GetDlgCtrlID()==IDC_STACHK_AUTOCRT||
		pWnd->GetDlgCtrlID()==IDC_STACHK_AUTOEXP|| pWnd->GetDlgCtrlID()==IDC_STA_BRIGHT || pWnd->GetDlgCtrlID()==IDC_STA_AUDIO ||
		pWnd->GetDlgCtrlID()==IDC_STA_AUDIOFORMAT || pWnd->GetDlgCtrlID()==IDC_STACHK_AUTOTOTATE || pWnd->GetDlgCtrlID()==IDC_STACHK_OPTIMIZE)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		CFont   tem_Font;
		tem_Font.CreatePointFont(100, _T("����"));
		pDC->SelectObject(&tem_Font);
	}
	if (pWnd->GetDlgCtrlID()==IDC_STA_TIMER)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(246, 246, 11));
		CFont   tem_Font;
		tem_Font.CreatePointFont(100, _T("����"));
		pDC->SelectObject(&tem_Font);
	}
	//static��̬��ʾ-------------------
	if (pWnd->GetDlgCtrlID() == IDC_STA_EXP || pWnd->GetDlgCtrlID() == IDC_STA_BRG)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		CFont   tem_Font;
		tem_Font.CreatePointFont(100, _T("����"));
		pDC->SelectObject(&tem_Font);
	}
	//CheckBox����----------------------
	if (pWnd->GetDlgCtrlID() == IDC_CHK_AUTOEXP || pWnd->GetDlgCtrlID() == IDC_CHK_AUTOCRT)
	{
		pDC->SetTextColor(RGB(255, 255, 255));

	}
	
	
	if (pWnd->GetDlgCtrlID() == IDC_STA_GROUPNEW || pWnd->GetDlgCtrlID() == IDC_STA_GRPIS || pWnd->GetDlgCtrlID() == IDC_GROUPVIDEO || pWnd->GetDlgCtrlID() == IDC_GROUP_INCIDENT)
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
	}

	
	


	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

BOOL CUDSChildNor::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_MOUSEMOVE)
	{
		m_btnTipsMain.RelayEvent(pMsg);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


//��ʱ����������¼���ʱ
void CUDSChildNor::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString tem_strTime;
	switch(nIDEvent)
	{
	case 1:
		mss++;
		if (mss == 100)
		{
			mss = 0;
			ss++;
		}
		if (ss == 60)
		{
			ss = 0;
			mm++;
		}
		tem_strTime.Format(_T("%02i m:%02i s:%02i^"), mm, ss, mss);
		m_staTimer.SetWindowTextW(tem_strTime);

		CRect tem_rcTime; 
		GetDlgItem(IDC_STA_TIMER)->GetWindowRect(&tem_rcTime); 
		ScreenToClient(&tem_rcTime); //ת���ͻ��˽���
		InvalidateRect(&tem_rcTime);//���ˢ�¶Ի��򱳾� 
		UpdateWindow();

		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CUDSChildNor::OnSelchangeCmbAudeo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nAudioIndex = m_conAudio.GetCurSel();
}


void CUDSChildNor::OnBnClickedBtnTest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʼ¼����Ƶ
	if (m_BEnd)
	{
		mm  = 0;
		ss  = 0;
		mss = 0;
		::SendMessage(m_hWnd, WM_SWITCH, m_nAudioIndex, 7);
		m_BBegin = TRUE;
		m_BEnd   = FALSE;

		CRect tem_rcTime; 
		GetDlgItem(IDC_STA_TIMER)->GetWindowRect(&tem_rcTime); 
		ScreenToClient(&tem_rcTime); //ת���ͻ��˽���
		InvalidateRect(&tem_rcTime);//���ˢ�¶Ի��򱳾� 
		UpdateWindow();
	} 
}


void CUDSChildNor::OnBnClickedBtnEnd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����¼����Ƶ
	if (m_BBegin)
	{
		::SendMessage(m_hWnd, WM_SWITCH, 1, 8);
		m_staTimer.SetWindowTextW(_T("00 m:00 s:00^"));
		m_BBegin = FALSE;
		m_BEnd   = TRUE;
	}

}


void CUDSChildNor::OnNMCustomdrawSlidExposure(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_BAutoExp)
	{
		UpdateData(FALSE);
		m_conStaExp = m_conSlidExpos.GetPos();
		m_conStaExpStr.Format(_T("%d"), m_conStaExp);
		
		m_conStaExp = m_conStaExp;                //����slider��ʾ��ǰֵ
		CRect  tem_rcRect;; 
		GetDlgItem(IDC_STA_EXP)->GetWindowRect(&tem_rcRect); 
		ScreenToClient(&tem_rcRect); //ת���ͻ��˽���
		InvalidateRect(&tem_rcRect);//���ˢ�¶Ի��򱳾� 

		::SendMessage(m_hWnd, WM_SWITCH, m_conStaExp, 6);  //�����ֶ��ع�ֵ
	} 	
	
	*pResult = 0;
}


void CUDSChildNor::OnCustomdrawSlidBright(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(FALSE);
	m_conStaBrg = m_conSlidBright.GetPos();
	m_conStaBrg = m_conStaBrg;

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_BRG)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); //ת���ͻ��˽���
	InvalidateRect(&tem_rcRect);//���ˢ�¶Ի��򱳾� 

	::SendMessage(m_hWnd, WM_SWITCH, m_conStaBrg, 9);  //�����ֶ��ع�ֵ

	*pResult = 0;
}


//��ȡѡ��������������ͨ�������Ӵ�����������Ӧ������ͷ
//SendMessage();������������һ����Ϊ���������������һ����Ϊѡ�����
//0-Scanner; 1-DPI; 2-FileMode; 3-ColorMode
void CUDSChildNor::OnSelchangeCmbScanners()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nIndexScanner = m_conComScanner.GetCurSel();	
	::SendMessage(m_hWnd, WM_SWITCH, m_nIndexScanner, 0);
}


void CUDSChildNor::OnSelchangeCmbDpi()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nIndexDPI = m_conComReso.GetCurSel();
	CString  str;
	str.Format(_T("%d"), m_nIndexDPI);
	
	::SendMessage(m_hWnd, WM_SWITCH, m_nIndexDPI, 1);
}


void CUDSChildNor::OnSelchangeCmbFilemode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nIndexFile = m_conComFilemode.GetCurSel();
	::SendMessage(m_hWnd, WM_SWITCH, m_nIndexFile, 2);
}


void CUDSChildNor::OnSelchangeCmbColormode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nIndexColor = m_conComColormode.GetCurSel();
	::SendMessage(m_hWnd, WM_SWITCH, m_nIndexColor, 3);
}


void CUDSChildNor::OnBnClickedChkAutocrt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_AUTOCRT))
	{
		::SendMessage(m_hWnd, WM_SWITCH, 1, 4); //�Զ����д�
	}
	else
	{
		::SendMessage(m_hWnd, WM_SWITCH, 0, 4);  //�Զ����йر�
	}
}


void CUDSChildNor::OnBnClickedChkAutoexp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_AUTOEXP))
	{
		m_BAutoExp = TRUE;
		m_conSlidExpos.EnableWindow(FALSE);
		::SendMessage(m_hWnd, WM_SWITCH, 1, 5); //�Զ��ع⿪��
	}
	else
	{
		m_BAutoExp =FALSE;
		m_conSlidExpos.EnableWindow(TRUE);
		::SendMessage(m_hWnd, WM_SWITCH, 0, 5);  //�Զ��ع����
	}
	
}


void CUDSChildNor::LoadIniFile(void)
{
}




void CUDSChildNor::OnSelchangeCmbAudeoformat()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int tem_nCurSel = m_conAudioFmt.GetCurSel();
	::SendMessage(m_hWnd, WM_SWITCH, tem_nCurSel, 10);

}


void CUDSChildNor::OnClickedChkAutrotate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int  tem_nRotate = 0;
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_AUTROTATE))
	{
		tem_nRotate = 1;
		::WritePrivateProfileString(_T("Resource"), _T("AutoRotate"), _T("1"), m_strIniPath);
	} 
	else
	{
		tem_nRotate = 0;
		::WritePrivateProfileString(_T("Resource"), _T("AutoRotate"), _T("0"), m_strIniPath);
	}
	::SendMessage(m_hWnd, WM_SWITCH, tem_nRotate, 11);
}


void CUDSChildNor::OnClickedChkOptimize()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int tem_nOptimize = 0;
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_OPTIMIZE))
	{
		tem_nOptimize = 1;
		::WritePrivateProfileString(_T("Resource"), _T("AutoOptimize"), _T("1"), m_strIniPath);
	} 
	else
	{
		tem_nOptimize = 0;
		::WritePrivateProfileString(_T("Resource"), _T("AutoOptimize"), _T("0"), m_strIniPath);
	}
	::SendMessage(m_hWnd, WM_SWITCH, tem_nOptimize, 12);
}
