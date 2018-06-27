// UDSChildSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDS SmartCamera v1.0.0.h"
#include "UDSChildSet.h"
#include "afxdialogex.h"


// CUDSChildSet �Ի���

IMPLEMENT_DYNAMIC(CUDSChildSet, CDialogEx)

CUDSChildSet::CUDSChildSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSChildSet::IDD, pParent)
{

	m_conImgQ = 0;
	m_conAutoS = 0;
}

CUDSChildSet::~CUDSChildSet()
{
}

void CUDSChildSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLID_IMGQULITY, m_conSlidImgQ);
	DDX_Text(pDX, IDC_STA_IMGQULITYSHOW, m_conImgQ);
	DDX_Text(pDX, IDC_STA_AUTOSENSSHOW, m_conAutoS);
	//  DDX_Control(pDX, IDC_STA_AUTOSENS, m_conSlidAutoS);
	DDX_Control(pDX, IDC_SLID_AUTOSENS, m_conSlidAutoS);
	DDX_Control(pDX, IDC_EDIT_PRENAME, m_conEditPre);
	DDX_Control(pDX, IDC_EDIT_HTTP, m_conEditHttp);
	//  DDX_Control(pDX, IDC_BTN_UPLOAD, m_btnUpload);
	DDX_Control(pDX, IDC_BTN_UPLOAD, m_btnShangchuan);
	//  DDX_Control(pDX, IDC_BTN_SHANGCHUAN, m_btnShangchuan2);
	DDX_Control(pDX, IDC_BTN_CAMREM, m_btnMaincam);
}


BEGIN_MESSAGE_MAP(CUDSChildSet, CDialogEx)
	ON_BN_CLICKED(IDC_CHK_VEDIOINFO, &CUDSChildSet::OnBnClickedChkVedioinfo)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_IMGQULITY, &CUDSChildSet::OnCustomdrawSlidImgqulity)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_AUTOSENS, &CUDSChildSet::OnNMCustomdrawSlidAutosens)
	ON_BN_CLICKED(IDC_CHK_TIME, &CUDSChildSet::OnBnClickedChkTime)
	ON_BN_CLICKED(IDC_CHK_CAPODER, &CUDSChildSet::OnBnClickedChkCapoder)
	ON_BN_CLICKED(IDC_CHK_PRENAME, &CUDSChildSet::OnBnClickedChkPrename)
	ON_BN_CLICKED(IDC_BTN_SETPATH, &CUDSChildSet::OnBnClickedBtnSetpath)
	ON_BN_CLICKED(IDC_CHK_HTTP, &CUDSChildSet::OnBnClickedChkHttp)
	ON_BN_CLICKED(IDC_BTN_UPLOAD, &CUDSChildSet::OnBnClickedBtnUpload)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_CAMRES, &CUDSChildSet::OnBnClickedBtnCamres)
	ON_BN_CLICKED(IDC_BTN_CAMREM, &CUDSChildSet::OnBnClickedBtnCamrem)
	ON_EN_CHANGE(IDC_EDIT_PRENAME, &CUDSChildSet::OnChangeEditPrename)
	ON_BN_CLICKED(IDC_RADIO_HTTP, &CUDSChildSet::OnBnClickedRadioHttp)
	ON_BN_CLICKED(IDC_RADIO_FTP, &CUDSChildSet::OnBnClickedRadioFtp)
	ON_COMMAND(IDC_RADIO_MAINCAM, &CUDSChildSet::OnRadioMaincam)
	ON_COMMAND(IDC_RADIO_SUBCAM, &CUDSChildSet::OnRadioSubcam)
	ON_COMMAND(IDC_RADIO_VEDIO, &CUDSChildSet::OnRadioVedio)
	ON_COMMAND(IDC_RADIO_VEDIO2, &CUDSChildSet::OnRadioVedio2)
	ON_BN_CLICKED(IDC_BTN_VIDEO1, &CUDSChildSet::OnBnClickedBtnVideo1)
	ON_BN_CLICKED(IDC_BTN_VIDEO2, &CUDSChildSet::OnBnClickedBtnVideo2)
END_MESSAGE_MAP()


// CUDSChildSet ��Ϣ�������


BOOL CUDSChildSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	/*********************************************
	*
	*0���ؼ���ʼ����ر���
	*1�� ������ʼ��
	*2�� SliderBar��ʼ��
	*3�� CheckBox��ʼ��
	*4�� ���ý�����س�ʼ��
	*5�� Radio�ؼ���ʼ��
	*
	**********************************************/
	
	//0��----------------------------------------
	/*
	TCHAR        tem_tcFilepath[MAX_PATH+1] = {0};
	CString      tem_strIniPath;
	CString      tem_strRead;
	GetModuleFileName(NULL, tem_tcFilepath, MAX_PATH);
	(_tcsrchr(tem_tcFilepath, _T('\\')))[1] = 0;
	tem_strIniPath    = tem_tcFilepath;
//	tem_strIniPath   += _T("UDSSmartCamera.ini");   //�����ļ�·��
	int tem_nDirIndex = tem_strIniPath.ReverseFind('\\');
	tem_strIniPath = tem_strIniPath.Mid(0, tem_nDirIndex);
	tem_nDirIndex = tem_strIniPath.ReverseFind('\\');
	tem_strIniPath = tem_strIniPath.Mid(0, tem_nDirIndex+1);

	tem_strIniPath   += _T("config.ini");   //�����ļ�·��
	tem_strIniPath.Replace(_T("\\"), _T("\\\\"));
	*/
	m_nSoundOpen = 1;

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
//		tem_strIniPath.Replace(_T("\\"), _T("\\\\"));
	}


	int     tem_nShowInfo;
	int     tem_nNamingMode;
	int     tem_nJpegQuality;
	int     tem_nAutoSense;
	::GetPrivateProfileString(_T("AdvanceSet"), _T("ShowInfo"), _T("û���ҵ�ShowInfo��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nShowInfo = _ttoi(tem_strRead);
	::GetPrivateProfileString(_T("AdvanceSet"), _T("NamingMode"), _T("û���ҵ�NamingMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nNamingMode = _ttoi(tem_strRead);
	switch(tem_nNamingMode)
	{
	case 0:
		//˳������
		((CButton*)GetDlgItem(IDC_CHK_CAPODER))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_CHK_PRENAME))->SetCheck(0);
		m_conEditPre.EnableWindow(FALSE);
		break;
	case 1:
		//ʱ������
		((CButton*)GetDlgItem(IDC_CHK_CAPODER))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_CHK_PRENAME))->SetCheck(0);
		m_conEditPre.EnableWindow(FALSE);
		break;
	case 2:
		//ǰ׺����
		((CButton*)GetDlgItem(IDC_CHK_CAPODER))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_CHK_PRENAME))->SetCheck(1);
		m_conEditPre.EnableWindow(TRUE);
		::GetPrivateProfileString(_T("AdvanceSet"), _T("PreName"), _T("û���ҵ�PreName��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	    m_conEditPre.SetWindowText(tem_strRead);
        //�ļ�ǰ׺���ݸ�Main��
		break;
	default:
		//˳������
		((CButton*)GetDlgItem(IDC_CHK_CAPODER))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_CHK_PRENAME))->SetCheck(0);
		m_conEditPre.EnableWindow(FALSE);
		break;
	}

	::GetPrivateProfileString(_T("AdvanceSet"), _T("JPEGQuality"), _T("û���ҵ�JPEGQuality ��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nJpegQuality = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
	

	::GetPrivateProfileString(_T("AdvanceSet"), _T("AutoCaptureSense"), _T("û���ҵ�AutoCaptureSense��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nAutoSense = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("AdvanceSet"), _T("HTTP"), _T("û���ҵ�HTTP��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strURL = tem_strRead;
	tem_strRead.ReleaseBuffer();
	m_conEditHttp.SetWindowText(m_strURL);

	::GetPrivateProfileString(_T("AdvanceSet"), _T("FTP"), _T("û���ҵ�FTP��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strFtp = tem_strRead;
	tem_strRead.ReleaseBuffer();
	
	//1��----------------------------------------
	m_pWndSet = GetParentOwner();
	m_hWndSet = m_pWndSet->m_hWnd;
	m_strDefaultDoc = "";
	m_BHttp   = TRUE;

	//2��----------------------------------------
	m_conSlidImgQ.SetRange(10, 100);
	m_conSlidImgQ.SetPos(tem_nJpegQuality);
	
	m_conImgQ = tem_nJpegQuality;     //ͨ����ȡ�����ļ�����Ĭ������
	UpdateData(FALSE);

	m_conSlidAutoS.SetRange(1, 20);
	m_conSlidAutoS.SetPos(tem_nAutoSense);
	
	m_conAutoS = tem_nAutoSense;
	UpdateData(FALSE);

	//3��------------------------------------------
	((CButton*)GetDlgItem(IDC_CHK_VEDIOINFO))->SetCheck(tem_nShowInfo);
	((CButton*)GetDlgItem(IDC_CHK_HTTP))->SetCheck(0);

	//4��------------------------------------------
	//�����������ñ�����ɫ,���ַ����ؼ��ı���ɫҲ����ݽ��汳��ɫ�����ı�
	
	
	CDialogEx::SetBackgroundColor(RGB(72,77,91));
	m_btnShangchuan.Init(IDB_PNG_SC, BTN_IMG_1, BTN_TYPE_NORMAL);
	m_btnMaincam.Init(IDB_PNG_SETSET, BTN_IMG_3, BTN_TYPE_NORMAL);
	

	m_btnTipsSet.Create(this);
	m_btnTipsSet.AddTool(GetDlgItem(IDC_BTN_UPLOAD), _T("�ϴ���ǰ�ļ�"));
	m_btnTipsSet.AddTool(GetDlgItem(IDC_BTN_CAMREM), _T("����"));
	m_btnTipsSet.SetDelayTime(200);   //�����ӳ�
	m_btnTipsSet.SetTipTextColor(RGB(0, 0, 0));//����������ɫ
	m_btnTipsSet.SetTipBkColor(RGB(255, 255, 255));//������ʾ�򱳾���ɫ
	m_btnTipsSet.Activate(TRUE); //������ʾ����

	//5��---------------------------------------------
	((CButton*)GetDlgItem(IDC_RADIO_MAINCAM))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_SUBCAM))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_VEDIO))->SetCheck(FALSE);

	((CButton*)GetDlgItem(IDC_RADIO_HTTP))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_FTP))->SetCheck(FALSE);

	::GetPrivateProfileString(_T("OtherSet"), _T("SoundOpen"), _T("û���ҵ�SoundOpen��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_nSoundOpen = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
	if (m_nSoundOpen==1)
	{
		((CButton*)GetDlgItem(IDC_CHK_HTTP))->SetCheck(TRUE);
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_HTTP))->SetCheck(FALSE);
	}


	m_BUpLoadFiles  = FALSE;

	SetWindowTheme(GetDlgItem(IDC_GRP_SETONE)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_GRP_SETTWO)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STA_UPLOAD)->GetSafeHwnd(), _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STA_GROUNEW2)->GetSafeHwnd(), _T(""), _T(""));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CUDSChildSet::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

}


HBRUSH CUDSChildSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	//Slider�ؼ�����
	if (pWnd->GetDlgCtrlID() == IDC_SLID_IMGQULITY)
	{
		return (HBRUSH) CreateSolidBrush(RGB(72,77,91));
	}
	if (pWnd->GetDlgCtrlID() == IDC_SLID_AUTOSENS)
	{
		return (HBRUSH) CreateSolidBrush(RGB(72,77,91));
	}

	//Static�ؼ�����
	if (pWnd->GetDlgCtrlID()==IDC_STA_IMGQUALITY || pWnd->GetDlgCtrlID()==IDC_STA_PRENAME || pWnd->GetDlgCtrlID()==IDC_STA_HTTP || 
		pWnd->GetDlgCtrlID()==IDC_STACHK_PRENAME || pWnd->GetDlgCtrlID()==IDC_STACHK_CAPODER || pWnd->GetDlgCtrlID()==IDC_STACHK_TIME || 
		pWnd->GetDlgCtrlID()==IDC_STA_AUTOSENS ||pWnd->GetDlgCtrlID()==IDC_STACHK_VIDINFO || pWnd->GetDlgCtrlID() == IDC_STA_IMGQULITYSHOW||
		pWnd->GetDlgCtrlID()==IDC_STA_AUTOSENSSHOW || pWnd->GetDlgCtrlID()==IDC_STA_RADIOM || pWnd->GetDlgCtrlID()==IDC_STA_RADIOS||
		pWnd->GetDlgCtrlID()==IDC_STA_HIGH || pWnd->GetDlgCtrlID()==IDC_STA_LOW || pWnd->GetDlgCtrlID()==IDC_STA_FAST || 
		pWnd->GetDlgCtrlID()==IDC_STA_SLOW || pWnd->GetDlgCtrlID()==IDC_STA_FTP || pWnd->GetDlgCtrlID()==IDC_STA_VIEO || 
		pWnd->GetDlgCtrlID()==IDC_STA_VIEO2 || pWnd->GetDlgCtrlID()==IDC_STA_SOUND)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		CFont   tem_Font;
		tem_Font.CreatePointFont(100, _T("����"));
		pDC->SelectObject(&tem_Font);
	}

	if (pWnd->GetDlgCtrlID()==IDC_GRP_SETONE || pWnd->GetDlgCtrlID()==IDC_GRP_SETTWO || pWnd->GetDlgCtrlID()==IDC_STA_UPLOAD || pWnd->GetDlgCtrlID()==IDC_STA_GROUNEW2)
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
	}


	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


BOOL CUDSChildSet::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_MOUSEMOVE)
	{
		m_btnTipsSet.RelayEvent(pMsg);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


//�Ƿ���ʾ��Ƶ��Ϣ
void CUDSChildSet::OnBnClickedChkVedioinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_VEDIOINFO))
	{
		::SendMessage(m_hWndSet, WM_ADVCESET, 1, 0);
	} 
	else
	{
		::SendMessage(m_hWndSet, WM_ADVCESET, 0, 0);
	}

}


//����JPEGͼ������
void CUDSChildSet::OnCustomdrawSlidImgqulity(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(FALSE);
	m_conImgQ = m_conSlidImgQ.GetPos();

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_IMGQULITYSHOW)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); //ת���ͻ��˽���
	InvalidateRect(&tem_rcRect);//���ˢ�¶Ի��򱳾�

	::SendMessage(m_hWndSet, WM_ADVCESET, m_conImgQ, 1);
	
	*pResult = 0;
}


//����������������
void CUDSChildSet::OnNMCustomdrawSlidAutosens(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(FALSE);
	m_conAutoS = m_conSlidAutoS.GetPos();

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_AUTOSENSSHOW)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); //ת���ͻ��˽���
	InvalidateRect(&tem_rcRect);//���ˢ�¶Ի��򱳾� 

	::SendMessage(m_hWndSet, WM_ADVCESET, m_conAutoS, 2);

	*pResult = 0;
}


//����ʱ������
void CUDSChildSet::OnBnClickedChkTime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CButton*)GetDlgItem(IDC_CHK_CAPODER))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHK_PRENAME))->SetCheck(0);
	m_conEditPre.SetWindowText(_T(""));
	m_conEditPre.EnableWindow(FALSE);
	::SendMessage(m_hWndSet, WM_ADVCESET, 1, 3);

}


//���ô�������
void CUDSChildSet::OnBnClickedChkCapoder()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CButton*)GetDlgItem(IDC_CHK_CAPODER))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHK_PRENAME))->SetCheck(0);
	m_conEditPre.SetWindowText(_T(""));
	m_conEditPre.EnableWindow(FALSE);
	::SendMessage(m_hWndSet, WM_ADVCESET, 1, 4);
}


//ָ��ǰ׺����
void CUDSChildSet::OnBnClickedChkPrename()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ָ��ǰ׺����ǰ���ȼ��༭��ǰ׺�Ƿ�Ϊ�գ�Ϊ����Ҫ������ʾ
	((CButton*)GetDlgItem(IDC_CHK_CAPODER))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHK_PRENAME))->SetCheck(1);
	m_conEditPre.EnableWindow(TRUE);
	m_conEditPre.GetWindowText(m_strPreName);
	::SendMessage(m_hWndSet, WM_ADVCESET, 1, 5);

	/*
	m_conEditPre.GetWindowText(m_strPreName);
	if (m_strPreName.IsEmpty())
	{
		MessageBox(_T("������ǰ׺����"));
		((CButton*)GetDlgItem(IDC_CHK_CAPODER))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_CHK_PRENAME))->SetCheck(0);
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_CAPODER))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_CHK_PRENAME))->SetCheck(1);
		m_conEditPre.EnableWindow(TRUE);
		//����tem_strPreName�ַ���
		::SendMessage(m_hWndSet, WM_ADVCESET, 1, 5);
	}
	*/
}


void CUDSChildSet::OnBnClickedChkHttp()
{
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_HTTP))
	{
		::SendMessage(m_hWndSet, WM_ADVCESET, 1, 12);     //��������Ϣ
	} 
	else
	{
		::SendMessage(m_hWndSet, WM_ADVCESET, 0, 12);     //�ر�������Ϣ
	}
}

//HTTP�ϴ�
void CUDSChildSet::OnBnClickedBtnUpload()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_BUpLoadFiles)
	{
		m_BUpLoadFiles = TRUE;   //�ϴ���ɺ���ΪFALSE
		/*������*/
		//���̼򻯽�������Ӧ��Ϣ
		if (m_BHttp)
		{
			::SendMessage(m_hWndSet, WM_ADVCESET, 0, 7);     //http�ϴ���Ϣ
		} 
		else
		{
			::SendMessage(m_hWndSet, WM_ADVCESET, 1, 7);     //ftp�ϴ���Ϣ
		}

		/*ԭ����
		//��ȡ�����HTTP-URL
		CString  tem_strHttp = _T("");
		m_conEditHttp.GetWindowText(tem_strHttp);
		m_strURL = tem_strHttp;

		//����HTTP�ϴ��������ϴ���ǰ�����ļ�
		::SendMessage(m_hWndSet, WM_ADVCESET, 0, 7);     //http�ϴ���Ϣ

		::SendMessage(m_hWndSet, WM_ADVCESET, 1, 7);     //ftp�ϴ���Ϣ

		//�ж�HTTP����FTP��д��ini�����ļ�
		//д��ini�ļ�
		TCHAR        tem_tcFilepath[MAX_PATH+1] = {0};
		CString      tem_strIniPath;
		CString      tem_strRead;
		GetModuleFileName(NULL, tem_tcFilepath, MAX_PATH);
		(_tcsrchr(tem_tcFilepath, _T('\\')))[1] = 0;
		tem_strIniPath    = tem_tcFilepath;
		tem_strIniPath   += _T("UDSSmartCamera.ini");   //�����ļ�·��
		::WritePrivateProfileString(_T("AdvanceSet"), _T("HTTP"), tem_strHttp, tem_strIniPath); 
		*/
	}
	
}


void CUDSChildSet::OnBnClickedBtnCamrem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_MAINCAM))
	{
		::SendMessage(m_hWndSet, WM_ADVCESET, 0, 8);
	} 
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_SUBCAM))
	{
		::SendMessage(m_hWndSet, WM_ADVCESET, 0, 9);
	}
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_VEDIO))
	{
		::SendMessage(m_hWndSet, WM_ADVCESET, 0, 10);
	}
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_VEDIO2))
	{
		::SendMessage(m_hWndSet, WM_ADVCESET, 0, 11);
	}
}


//��ͷ����
void CUDSChildSet::OnBnClickedBtnSetpath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	::SendMessage(m_hWndSet, WM_ADVCESET, 0, 8);
}

//��ͷ����
void CUDSChildSet::OnBnClickedBtnCamres()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(m_hWndSet, WM_ADVCESET, 0, 9);
}

//��ͷ��Ƶ����
void CUDSChildSet::OnBnClickedBtnVideo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(m_hWndSet, WM_ADVCESET, 0, 10);
}

//��ͷ��Ƶ����
void CUDSChildSet::OnBnClickedBtnVideo2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(m_hWndSet, WM_ADVCESET, 0, 11);
}


void CUDSChildSet::OnChangeEditPrename()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//Edit�ؼ����ݷ����ı䣬���ַ�����Ϣ����
	m_conEditPre.GetWindowText(m_strPreName);
	//����tem_strPreName�ַ���
	::SendMessage(m_hWndSet, WM_ADVCESET, 1, 5);

}


void CUDSChildSet::OnBnClickedRadioHttp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_HTTP))
	{
		m_BHttp = TRUE;
		((CButton*)GetDlgItem(IDC_RADIO_HTTP))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_FTP))->SetCheck(FALSE);
		m_conEditHttp.SetWindowText(m_strURL);
	}
	else
	{
		m_BHttp = FALSE;
		((CButton*)GetDlgItem(IDC_RADIO_HTTP))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_FTP))->SetCheck(TRUE);
	}
}


void CUDSChildSet::OnBnClickedRadioFtp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_FTP))
	{
		m_BHttp = FALSE;
		((CButton*)GetDlgItem(IDC_RADIO_HTTP))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_FTP))->SetCheck(TRUE);
		m_conEditHttp.SetWindowText(m_strFtp);
	}
	else
	{
		m_BHttp = TRUE;
		((CButton*)GetDlgItem(IDC_RADIO_HTTP))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_FTP))->SetCheck(FALSE);
	}
	
}


void CUDSChildSet::OnRadioMaincam()
{
	// TODO: �ڴ���������������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_MAINCAM))
	{
		((CButton*)GetDlgItem(IDC_RADIO_SUBCAM))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_VEDIO))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_VEDIO2))->SetCheck(FALSE);
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_SUBCAM))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_VEDIO))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_VEDIO2))->SetCheck(FALSE);
	}
}


void CUDSChildSet::OnRadioSubcam()
{
	// TODO: �ڴ���������������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_SUBCAM))
	{
		((CButton*)GetDlgItem(IDC_RADIO_MAINCAM))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_VEDIO))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_VEDIO2))->SetCheck(FALSE);
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_MAINCAM))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_VEDIO))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_VEDIO2))->SetCheck(FALSE);
	}
}


void CUDSChildSet::OnRadioVedio()
{
	// TODO: �ڴ���������������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_VEDIO))
	{
		((CButton*)GetDlgItem(IDC_RADIO_MAINCAM))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_SUBCAM))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_VEDIO2))->SetCheck(FALSE);
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_MAINCAM))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_SUBCAM))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_VEDIO2))->SetCheck(TRUE);
	}
}


void CUDSChildSet::OnRadioVedio2()
{
	// TODO: �ڴ���������������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_VEDIO2))
	{
		((CButton*)GetDlgItem(IDC_RADIO_MAINCAM))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_SUBCAM))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_VEDIO))->SetCheck(FALSE);
	} 
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_MAINCAM))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_SUBCAM))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_VEDIO))->SetCheck(FALSE);
	}
}

