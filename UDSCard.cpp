// UDSCard.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDSCard.h"
#include "afxdialogex.h"
#include "ID_Fpr.h"        //ָ��ʶ��
#include "ID_FprCap_Protocol.h"
#include "Common.h"

#include<iostream>



// CUDSCard �Ի���
extern CString    m_strDefaultPath;   //Ĭ��·��

IMPLEMENT_DYNAMIC(CUDSCard, CDialogEx)

CUDSCard::CUDSCard(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSCard::IDD, pParent)
{

	m_editName = _T("");
	m_editSex = _T("");
	m_editNation = _T("");
	m_editBirth = _T("");
	m_editCardnum = _T("");
	m_editOffice = _T("");
	m_editValidity = _T("");
	m_editAddress = _T("");
	m_StaInfo = _T("");

	m_nOriX   = 0;
	m_nOriY   = 0;
	m_nWidth  = 0;
	m_nHeight = 0;
}

CUDSCard::~CUDSCard()
{
}

void CUDSCard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
	DDX_Control(pDX, IDOK, m_btnRecard);
	DDX_Control(pDX, IDCANCEL, m_btnExit);
	DDX_Text(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Text(pDX, IDC_EDIT_SEX, m_editSex);
	DDX_Text(pDX, IDC_EDIT_NATION, m_editNation);
	DDX_Text(pDX, IDC_EDIT_BIRTH, m_editBirth);
	DDX_Text(pDX, IDC_EDIT_ID, m_editCardnum);
	DDX_Text(pDX, IDC_EDIT_OFFICE, m_editOffice);
	DDX_Text(pDX, IDC_EDIT_VALIDITY, m_editValidity);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_editAddress);
	DDX_Text(pDX, IDC_STA_INFO, m_StaInfo);
	DDX_Control(pDX, IDC_STA_COPYIMG, m_conCopyImg);
	DDX_Control(pDX, IDC_STA_PIC, m_conCardImg);
	DDX_Control(pDX, IDC_SLID_PERIOD, m_conPeriod);
	DDX_Control(pDX, IDC_BTN_FINGER, m_btnReadFinger);
	DDX_Control(pDX, IDC_BTN_PRINTDOC, m_btnPrint);
}


BEGIN_MESSAGE_MAP(CUDSCard, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CUDSCard::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDOK, &CUDSCard::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUDSCard::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_CARDSAVE, &CUDSCard::OnBnClickedBtnCardsave)
	ON_BN_CLICKED(IDC_CHK_AUTOCARD, &CUDSCard::OnClickedChkAutocard)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHK_SAVE, &CUDSCard::OnBnClickedChkSave)
	ON_STN_DBLCLK(IDC_STA_COPYIMG, &CUDSCard::OnDblclkStaCopyimg)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLID_PERIOD, &CUDSCard::OnCustomdrawSlidPeriod)
	ON_BN_CLICKED(IDC_BTN_FINGER, &CUDSCard::OnBnClickedBtnFinger)
	ON_BN_CLICKED(IDC_BTN_PRINTDOC, &CUDSCard::OnBnClickedBtnPrintdoc)
END_MESSAGE_MAP()


// CUDSCard ��Ϣ�������


BOOL CUDSCard::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/*************************
	*         ����Ŀ¼
	* 1��������ʼ��
	* 2����黺��Ŀ¼
	* 3�������ʼ��
	* 4���״ζ���
	* 5��CheckBox
	*
	*
	*
	*
	*************************/

	/*1��������ʼ��*/
//	m_iSubCard = new CCardReader;
	m_iSubCard = new CTermbReader;

	m_strName     = _T("");
	m_strSex      = _T("");
	m_strNation   = _T("");
	m_strBirth    = _T("");
	m_strAddress  = _T("");
	m_strID       = _T("");
	m_strOffice   = _T("");
	m_strValidity = _T("");
	m_strFilePath = _T("");

	m_editName    = _T("");
	m_editSex     = _T("");
	m_editNation  = _T("");
	m_editBirth   = _T("");
	m_editCardnum = _T("");
	m_editOffice  = _T("");
	m_editValidity= _T("");
	m_editAddress = _T("");
	m_StaInfo     = _T("");
	m_strCopyImg  = _T("");

	m_strResultImg = _T("");
	m_strQRCode    = _T("");
	m_strQRImgInfo = _T("");
	m_strVerifyTime= _T("");
	m_strScore     = _T("");
	m_strResult    = _T("");
	m_strFingerImg = _T("");
	
	m_BFirst      = TRUE;
	m_BSaveCopy   = TRUE;
	m_BAutoRead   = FALSE;
	UpdateData(FALSE);
	m_nFingerNum     = 0;
	m_strFingerIndex = _T("");
	m_nFigerIndex    = -1;

	/*2������Ŀ¼*/
	TCHAR     tem_tcExepath[MAX_PATH+1] = {0};
	GetModuleFileName(NULL, tem_tcExepath, MAX_PATH);
	(_tcsrchr(tem_tcExepath, _T('\\')))[1] = 0;

	m_strProntImg   = tem_tcExepath;
	m_strBackImg    = tem_tcExepath;
	m_strProntImg  += _T("res\\");
	m_strBackImg   += _T("res\\");
	m_strProntImg  += _T("PrintFront.jpg");
	m_strBackImg   += _T("PrintBack.jpg");

	CString   tem_strScanTemp = SubGetMyDocument();
	tem_strScanTemp += _T("\\");
	tem_strScanTemp += _T("UDSData");
	CFileFind  tem_fFileFind;
	if (!tem_fFileFind.FindFile(tem_strScanTemp))
	{
		CreateDirectory(tem_strScanTemp, NULL);
	}
	//ָ�ƴ��·��
	m_strFingerPath  = tem_strScanTemp;
	m_strFingerPath += _T("\\���֤��Ϣ\\Finger\\");

	//�ж������ļ��Ƿ����
	m_strCardIniPath  = tem_strScanTemp + _T("\\");
	m_strCardIniPath += _T("PersonInfo.INI");

	CString tem_strSoftIniPath;
	tem_strSoftIniPath  = tem_strScanTemp + _T("\\");
	tem_strSoftIniPath += _T("config.ini");
	m_strIniPath2        = tem_strSoftIniPath;

	CString  tem_strReadTime = _T("");
	::GetPrivateProfileString(_T("Resource"), _T("ReadSens"), _T("û���ҵ�ReadSens��Ϣ"), tem_strReadTime.GetBuffer(MAX_PATH), MAX_PATH, tem_strSoftIniPath);
	tem_strReadTime.ReleaseBuffer();
	m_nReadTime = _ttoi(tem_strReadTime);
	if (m_nReadTime<1000 || m_nReadTime>10000)
	{
		m_nReadTime = 3000;
	}

	::GetPrivateProfileString(_T("Resource"), _T("FingerPassvalue"), _T("û���ҵ�FingerPassvalue��Ϣ"), tem_strReadTime.GetBuffer(MAX_PATH), MAX_PATH, tem_strSoftIniPath);
	tem_strReadTime.ReleaseBuffer();
	m_fPassValue = _tstof(tem_strReadTime);

	if (m_fPassValue>100)
	{
		m_fPassValue = 100.0;
	}
	else if (m_fPassValue<0)
	{
		m_fPassValue = 0.0;
	}
	m_fPassValue = m_fPassValue/100*1.0;

	BOOL     tem_BFileFind = PathFileExists(m_strCardIniPath);
	if (!tem_BFileFind)
	{
		CString   tem_strExePath = _T("");
		//�ļ������ڣ���ԭ�����ļ����Ƶ�ָ��Ŀ¼
		TCHAR        tem_tcFilepath[MAX_PATH+1] = {0};
		GetModuleFileName(NULL, tem_tcFilepath, MAX_PATH);
		(_tcsrchr(tem_tcFilepath, _T('\\')))[1] = 0;
		tem_strExePath   = tem_tcFilepath;
		tem_strExePath  += _T("PersonInfo.INI");
		CopyFile(tem_strExePath, m_strCardIniPath, TRUE);
	}

	m_strInfoBuffer  = tem_strScanTemp;
	m_strInfoBuffer += _T("\\���֤��Ϣ");
	if (!tem_fFileFind.FindFile(m_strInfoBuffer))
	{
		CreateDirectory(m_strInfoBuffer, NULL);
	}

	m_strPicBuffer  = m_strInfoBuffer;
	m_strPicBuffer += _T("\\Image");
	if (!tem_fFileFind.FindFile(m_strPicBuffer))
	{
		CreateDirectory(m_strPicBuffer, NULL);
	}
	
	/*3�������ʼ��*/
	CDialogEx::SetBackgroundColor(RGB(72, 77, 91));

	m_btnSave.Init(IDB_PNG_CARDSAVE, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_btnRecard.Init(IDB_PNG_CARDRE, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_btnExit.Init(IDB_PNG_CARDEXIT, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_btnReadFinger.Init(IDB_PNG_FINGER, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnPrint.Init(IDB_PNG_PRINT, BTN_IMG_4, BTN_TYPE_NORMAL);

	m_tipCardInfo.Create(this);
	m_tipCardInfo.AddTool(GetDlgItem(IDC_BTN_CARDSAVE), _T("����"));
	m_tipCardInfo.AddTool(GetDlgItem(IDOK), _T("��Ŀ¼"));
	m_tipCardInfo.AddTool(GetDlgItem(IDCANCEL), _T("�˳�"));
	m_tipCardInfo.AddTool(GetDlgItem(IDB_PNG_FINGER), _T("�ɼ�ָ��"));
	m_tipCardInfo.SetDelayTime(200);
	m_tipCardInfo.Activate(TRUE);

	/*4���״ζ���*/
	//OnPaint��

	//5��---------------------------------
	((CButton*)GetDlgItem(IDC_CHK_SAVE))->SetCheck(m_BSaveCopy);

	//6���Զ�����ʱ����------------------
	m_conPeriod.SetRange(1000, 10000, TRUE);
	m_conPeriod.SetPos(m_nReadTime);
	m_conPeriod.SetPageSize(500);

	float    tem_fPeriod   = (float)m_nReadTime*1.0/1000;
	CString  tem_strPeriod = _T("");
	tem_strPeriod.Format(_T("%.1f"), tem_fPeriod);
	GetDlgItem(IDC_STA_PERIODV)->SetWindowText(tem_strPeriod);
	CRect    tem_rcRect;; 
	GetDlgItem(IDC_STA_PERIODV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);









	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	/*ԭ���̣����������л�ȡ��ȡ���ݣ��ӽ�����ʾ����

	m_BFirst = TRUE;
	GetDlgItem(IDC_EDIT_NAME)->SetWindowText(m_strName);
	GetDlgItem(IDC_EDIT_SEX)->SetWindowText(m_strSex);
	GetDlgItem(IDC_EDIT_NATION)->SetWindowText(m_strNation);
	GetDlgItem(IDC_EDIT_BIRTH)->SetWindowText(m_strBirth);
	GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText(m_strAddress);
	GetDlgItem(IDC_EDIT_ID)->SetWindowText(m_strID);
	GetDlgItem(IDC_EDIT_OFFICE)->SetWindowText(m_strOffice);
	GetDlgItem(IDC_EDIT_VALIDITY)->SetWindowText(m_strValidity);
	
	//ȥ�������еĺ���
	m_strBirth.Replace(_T("��"), _T(""));
	m_strBirth.Replace(_T("��"), _T(""));
	m_strBirth.Replace(_T("��"), _T(""));

	//ȥ����Ч���еĵ�
	m_strValidity.Replace(_T("."), _T(""));
	*/

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CUDSCard::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
    if (m_BFirst)
    {
		m_BFirst = FALSE;
		CString  tem_strPicPath = Self_GetSystemTime(m_strPicBuffer);
		tem_strPicPath = Self_ReadCard(tem_strPicPath);
		if (!tem_strPicPath.IsEmpty())
		{
			ShowPicture(tem_strPicPath);
		}
		Self_ShowFingerImg(_T("res\\FingerPrint.bmp"));

    }
}


HBRUSH CUDSCard::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	//����������---------------------
	if (pWnd->GetDlgCtrlID() == IDC_SLID_PERIOD)
	{
		return (HBRUSH) CreateSolidBrush(RGB(72,77,91));   //������ˢCBrush��CreateSolidBrush������ͬ���������
	}

	if (pWnd->GetDlgCtrlID()==IDC_STA_NAME || pWnd->GetDlgCtrlID()==IDC_STA_SEX || 
		pWnd->GetDlgCtrlID()==IDC_STA_NATION||pWnd->GetDlgCtrlID()==IDC_STA_BIRTH||
		pWnd->GetDlgCtrlID()==IDC_STA_ADDRESS||pWnd->GetDlgCtrlID()==IDC_STA_VALIDITY||
		pWnd->GetDlgCtrlID()==IDC_STA_ID||pWnd->GetDlgCtrlID()==IDC_STA_OFFICE||
		pWnd->GetDlgCtrlID()==IDC_STA_INFO || pWnd->GetDlgCtrlID()==IDC_STA_SAVE||
		pWnd->GetDlgCtrlID()==IDC_STA_AUTO || pWnd->GetDlgCtrlID()==IDC_STA_FINGERINDEX ||
		pWnd->GetDlgCtrlID()==IDC_STA_MATCHV)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		CFont   tem_Font;
		tem_Font.CreatePointFont(100, _T("����"));
		pDC->SelectObject(&tem_Font);
	}
	else if (pWnd->GetDlgCtrlID() == IDC_STA_CARDINFO)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		CFont   tem_Font;
		tem_Font.CreatePointFont(200, _T("����"));
		pDC->SelectObject(&tem_Font);
	}
	else if (pWnd->GetDlgCtrlID()==IDC_STA_PATHINFO)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		CFont   tem_Font;
		tem_Font.CreatePointFont(100, _T("����"));
		pDC->SelectObject(&tem_Font);
	}
	else if (pWnd->GetDlgCtrlID()==IDC_STA_PERIOD || pWnd->GetDlgCtrlID()==IDC_STA_PERIODV)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		if (m_BAutoRead)
		{
			pDC->SetTextColor(RGB(191, 191, 191));
		}
		else
		{
			pDC->SetTextColor(RGB(255, 255, 255));
		}
		CFont   tem_Font;
		tem_Font.CreatePointFont(100, _T("����"));
		pDC->SelectObject(&tem_Font);
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


BOOL CUDSCard::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_MOUSEMOVE)
	{
		m_tipCardInfo.RelayEvent(pMsg);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


int CUDSCard::Write2Excel(CString inipath)
{
	/*
	CString      tem_strExlPath;   //���Excel·��
	CString      tem_strPath;      //ini+excel����·������

	CString      tem_strExePath;

 	TCHAR        tem_tcFilepath[MAX_PATH+1] = {0};
 	GetModuleFileName(NULL, tem_tcFilepath, MAX_PATH);
 	(_tcsrchr(tem_tcFilepath, _T('\\')))[1] = 0;

	tem_strExePath    = tem_tcFilepath;
	tem_strExePath   += _T("TxtToExcel.exe");   //�����ļ�·��
//	tem_strExePath.Replace(_T("\\"), _T("\\\\"));
	
    //����·�������ո�ķ��� \"·��1\" \"·��2"\
	//��ʽһ��-----------------------------------
//	tem_strPath.Format(_T("\"%s\" \"%s\""),_T("C:\\SmartScan temp\\PersonInfo.INI"),_T("C:\\SmartScan temp\\PersonInfo.xls"));
	//��ʽ����-----------------------------------
//	inipath.Format(_T("%s"), _T("C:\\SmartScan temp\\PersonInfo.INI"));      
//	tem_strExlPath.Format(_T("%s"), _T("C:\\SmartScan temp\\PersonInfo.xls"));
//	tem_strPath.Format(_T("\"%s\" \"%s\""),inipath, tem_strExlPath);


	//����ѡ��·���Ի���
//	tem_strExlPath = SelectPath();
//	tem_strExlPath = Save2File();
//	tem_strExlPath = _T("C:\\UDSScanTemp");
	tem_strExlPath = SubGetMyDocument();
	tem_strExlPath+= _T("\\");
	tem_strExlPath+= _T("UDSData");
	//�жϸ�Ŀ¼�Ƿ����
	CFileFind    tem_fFileFind;
	if (!tem_fFileFind.FindFile(tem_strExlPath))
	{
		CreateDirectory(tem_strExlPath, NULL);
	}
	tem_strExlPath += _T("\\���֤��Ϣ") ;
	if (!tem_fFileFind.FindFile(tem_strExlPath))
	{
		CreateDirectory(tem_strExlPath, NULL);
	}

	tem_strExlPath += _T("\\");
	tem_strExlPath += _T("���֤��Ϣ��.xls");
//	tem_strExlPath.Replace(_T("\\"), _T("\\\\"));


	
// 	if (!tem_strExlPath.IsEmpty())
// 	{
// 		tem_strExlPath += m_strName;
// 		tem_strExlPath += m_strID;
// 		tem_strExlPath += _T(".xls");
// 	}
// 	else
// 	{
// 		return -1;
// 	}

	tem_strPath.Format(_T("\"%s\" \"%s\""),inipath, tem_strExlPath);   //\"ת���ַ���\"=".������˫����֮�䣬�������ŵ�������������������

	SHELLEXECUTEINFO  tem_shellIt;
	memset(&tem_shellIt, 0, sizeof(SHELLEXECUTEINFO));
	tem_shellIt.cbSize       = sizeof(SHELLEXECUTEINFO);
	tem_shellIt.fMask        = SEE_MASK_NOCLOSEPROCESS;
	tem_shellIt.lpVerb       = _T("open");
	tem_shellIt.lpFile       = tem_strExePath;
	tem_shellIt.lpParameters = tem_strPath;
	tem_shellIt.nShow        = SW_SHOW;
	tem_shellIt.hwnd         = m_hWnd;
	ShellExecuteEx(&tem_shellIt);

	*/
	return 0;
}


CString CUDSCard::SelectPath(void)
{
	TCHAR     m_selectpath[MAX_PATH];
	CString   m_goalpath;
	//	CString *p_goalpath;
	ZeroMemory(m_selectpath, sizeof(m_selectpath));
	BROWSEINFO   m_broseinfo;
	m_broseinfo.hwndOwner = m_hWnd;
	m_broseinfo.pidlRoot  = NULL;
	m_broseinfo.pszDisplayName = m_selectpath;
	m_broseinfo.lpszTitle = _T("��ѡ��Ŀ¼"); 
	m_broseinfo.ulFlags   = 0;
	m_broseinfo.lpfn      = NULL;
	m_broseinfo.lParam    = 0;
	m_broseinfo.iImage    = 0;
	LPITEMIDLIST   lp = SHBrowseForFolder(&m_broseinfo);
	if (lp&&SHGetPathFromIDList(lp, m_selectpath))
	{
		m_goalpath.Format(_T("%s"), m_selectpath);
//		m_goalpath.Replace(_T("\\"), _T("\\\\"));
		//C�̻����4��\�������������������һλΪ\�����
		if (m_goalpath.Right(1) != _T("\\"))
		{
			m_goalpath =m_goalpath+_T("\\\\");
		}
		else
		{
			m_goalpath =m_goalpath+_T("\\\\");
			m_goalpath = m_goalpath.Left(m_goalpath.GetLength()-2);
		}
		return m_goalpath;
	} 
	return _T("");
}


CString CUDSCard::Save2File(void)
{
	//��ȡ����·��
	/*
	TCHAR DeskDir[_MAX_PATH];  
	SHGetSpecialFolderPath(this->GetSafeHwnd(),DeskDir,CSIDL_DESKTOP,0);


	BOOL      isOpen = FALSE;        //�Ƿ��(����Ϊ����)  
	CString   tem_strDefaultDir = DeskDir;
//	CString   tem_strDefaultDir = _T("D:)"
	CString   tem_strFileName   = _T("���֤��Ϣ��.xls");
	CString   tem_strFilter     = _T("�ļ� (*.xls)|*.xls||");   //�ļ����ǵ�����  
	CString   tem_strFilepath   = tem_strDefaultDir + _T("\\");
	tem_strFilepath            += tem_strFileName;

	CFileDialog openFileDlg(isOpen, tem_strDefaultDir, tem_strFileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, tem_strFilter, NULL);  
	openFileDlg.GetOFN().lpstrInitialDir = tem_strFilepath;  
	INT_PTR result = openFileDlg.DoModal();  
	 
	if(result == IDOK) {  
		tem_strFilepath = openFileDlg.GetPathName();  
	}  
	
	return tem_strFilepath;
	*/
	return _T("");
}


void CUDSCard::OnBnClickedBtnCardsave()
{
}


/********************************
*      ����Ŀ¼
* 1����ȡ�ҵ��ĵ�
* 2������
* 3��д��Excel
* 4����ȡϵͳʱ��
* 5����ʾͷ��
*
*
********************************/

CString CUDSCard::SubGetMyDocument(void)
{
	CString        tem_strMyDocument = _T("");
	TCHAR          tem_cMyDocument[MAX_PATH] = {0};
	LPITEMIDLIST   tem_Pid = NULL;
	SHGetSpecialFolderLocation(NULL, CSIDL_PERSONAL, &tem_Pid);
	if (tem_Pid && SHGetPathFromIDList(tem_Pid, tem_cMyDocument))
	{
		tem_strMyDocument = tem_cMyDocument;
		return tem_strMyDocument;
	}
	return tem_strMyDocument;
}


CString CUDSCard::Self_ReadCard(CString picpath)
{
	//1����Ϣ��ʾ�ռ��ʼ��
	m_strResultImg = _T("");
	m_strQRCode    = _T("");
	m_strQRImgInfo = _T("");
	m_strVerifyTime= _T("");
	m_strFingerImg = _T("");

	m_editName     = _T("");
	m_editSex      = _T("");
	m_editNation   = _T("");
	m_editBirth    = _T("");
	m_editAddress  = _T("");
	m_editCardnum  = _T("");
	m_editOffice   = _T("");
	m_editValidity = _T("");
	m_StaInfo      = _T("");
	UpdateData(FALSE);

	m_stcIdInfo.imgpath  = _T("");
	m_stcIdInfo.name     = _T("");
	m_stcIdInfo.sex      = _T("");
	m_stcIdInfo.nation   = _T("");
	m_stcIdInfo.birth    = _T("");
	m_stcIdInfo.address  = _T("");
	m_stcIdInfo.IDnumber = _T("");
	m_stcIdInfo.office   = _T("");
	m_stcIdInfo.validate = _T("");

	m_nFingerNum         = 0;

	CRect   tem_rcStaInfo;
	GetDlgItem(IDC_STA_INFO)->SetWindowText(_T(""));
	GetDlgItem(IDC_STA_INFO)->GetWindowRect(&tem_rcStaInfo); 
	ScreenToClient(&tem_rcStaInfo);        
	InvalidateRect(&tem_rcStaInfo);
	UpdateWindow();	

	CString    tem_strPicName    = picpath;
	CString    tem_strNewPicName = m_strPicBuffer;
//	CString    tem_strIDCopyPath = m_strPicBuffer;
	CString    tem_strIDCopyPath = m_strDefaultPath;
	CString    tem_strRC         = _T("");
	CString    tem_strRecardDate = _T("");
	CString    tem_strFinger     = _T("");

	CString    tem_strOriDat     = m_strFingerPath;
	CString    tem_strOriWlt     = m_strFingerPath;
	CString    tem_strDatPath    = m_strFingerPath;     //ָ��dat�ļ�·��
	CString    tem_strWltPath    = m_strFingerPath;     //ָ��wlt�ļ�·��

	//��ȡ����ʱ��
	SYSTEMTIME  tem_stDateTime;
	GetLocalTime(&tem_stDateTime);
	tem_strRecardDate.Format(_T("%d%02d%02d %02d:%02d:%02d"), tem_stDateTime.wYear, tem_stDateTime.wMonth, tem_stDateTime.wDay,
		                                                      tem_stDateTime.wHour, tem_stDateTime.wMinute, tem_stDateTime.wSecond);
	

	tem_strRC = m_iSubCard->OpenCardPort();
	if (tem_strRC != _T("�򿪶˿�ʧ��"))
	{
		m_iSubCard->SetHeadPicPath(tem_strPicName);
		tem_strRC = m_iSubCard->ReadIDCard(m_strFingerPath);
		if (tem_strRC == _T(""))
		{
			//�����ɹ�
			m_editName     = m_iSubCard->GetCardName();
			m_editSex      = m_iSubCard->GetCardSex();
			m_editNation   = m_iSubCard->GetCardNation();
			m_editBirth    = m_iSubCard->GetCardBirth();
			m_editAddress  = m_iSubCard->GetCardAddress();
			m_editCardnum  = m_iSubCard->GetCardID();
			m_editOffice   = m_iSubCard->GetIssuingOrgan();
			m_editValidity = m_iSubCard->GetAllottedTime();
			
			m_iSubCard->CloseCardPort();


			tem_strNewPicName += _T("\\");
			tem_strNewPicName += m_editName;
			tem_strNewPicName += m_editCardnum;
			tem_strNewPicName += _T(".bmp");

			tem_strIDCopyPath += _T("\\~");
			tem_strIDCopyPath += m_editName;
			tem_strIDCopyPath += m_editCardnum;
			tem_strIDCopyPath += _T(".jpg");

			m_strResultImg     = m_strDefaultPath;
			m_strResultImg    += m_editName;
			m_strResultImg    += m_editCardnum;
			m_strResultImg    += _T(".jpg");

			m_strQRCode        = m_strPicBuffer;
			m_strQRCode       += _T("\\QR");
			m_strQRCode       += m_editName;
			m_strQRCode       += m_editCardnum;
			m_strQRCode       += _T(".png");

			//�ɵ�Ŀ���ļ�����
			tem_strOriDat     += _T("fp.dat");
			tem_strOriWlt     += _T("xp.wlt");

			//�µ�Ŀ���ļ�����
			tem_strDatPath    += m_editName;
			tem_strDatPath    += m_editCardnum;
			tem_strDatPath    += _T(".dat");

			tem_strWltPath    += m_editName;
			tem_strWltPath    += m_editCardnum;
			tem_strWltPath    += _T(".wlt");

			m_strCopyImg = tem_strIDCopyPath;

			m_stcIdInfo.imgpath  = tem_strNewPicName;
			m_stcIdInfo.name     = m_editName;
			m_stcIdInfo.sex      = m_editSex;
			m_stcIdInfo.nation   = m_editNation;
			m_stcIdInfo.birth    = m_editBirth;
			m_stcIdInfo.address  = m_editAddress;
			m_stcIdInfo.IDnumber = m_editCardnum;
			m_stcIdInfo.office   = m_editOffice;
			m_stcIdInfo.validate = m_editValidity;

			//�ж�m_strNewPicName�Ƿ���ڣ�������ɾ�����α���ͼ����������������Ϊ��ͼ��
			BOOL   tem_BIsFinded = FALSE;
			CFileFind  tem_find;
			tem_BIsFinded = tem_find.FindFile(tem_strNewPicName);
			if (tem_BIsFinded)
			{
				//�ļ��Ѵ���
				DeleteFile(tem_strPicName);
			}
			else
			{
				//�ļ�������
				tem_BIsFinded = tem_find.FindFile(tem_strPicName);
				if (tem_BIsFinded)
				{
					CFile::Rename(tem_strPicName, tem_strNewPicName);
				}
			}

			m_vcFaceImg.push_back(tem_strNewPicName);

//			if (tem_find.FindFile(tem_strOriDat))
			if (m_iSubCard->FindFinger())
			{
				//���֤����ָ����Ϣ***************************************
				m_btnReadFinger.SetFourState();
				GetDlgItem(IDC_BTN_FINGER)->EnableWindow(TRUE);

				m_btnPrint.SetFourState();
				GetDlgItem(IDC_BTN_PRINTDOC)->EnableWindow(TRUE);
				//ÿ����ֻ����һ��dat�ļ�--------------------------
				tem_BIsFinded = tem_find.FindFile(tem_strDatPath);
				if (tem_BIsFinded)
				{
					//��ָ���Ѵ���
					DeleteFile(tem_strDatPath);
					CFile::Rename(tem_strOriDat, tem_strDatPath);
				} 
				else
				{
					//��ָ�Ʋ�����
					CFile::Rename(tem_strOriDat, tem_strDatPath);
				}


				//ÿ����ֻ����һ��wlt�ļ�--------------------------
				tem_BIsFinded = tem_find.FindFile(tem_strWltPath);
				if (tem_BIsFinded)
				{
					//��ָ���Ѵ���
					DeleteFile(tem_strWltPath);
					CFile::Rename(tem_strOriWlt, tem_strWltPath);
				} 
				else
				{
					//��ָ�Ʋ�����
					CFile::Rename(tem_strOriWlt, tem_strWltPath);
				}


				//�ж�ָ�Ƹ���------------------------------------
				int  tem_nFileSize = 0;
				USES_CONVERSION;
				char* tem_cDatPath = T2A(tem_strDatPath);
				tem_strDatPath.ReleaseBuffer();

				FILE* tem_fileDat;
				if ((tem_fileDat = fopen(tem_cDatPath, "rb")))
				{
					fseek(tem_fileDat, 0, SEEK_END);
					tem_nFileSize = ftell(tem_fileDat);				
					fclose(tem_fileDat);
					m_nFingerNum = tem_nFileSize/512;
				}	
			}
			else
			{
				//���֤������ָ����Ϣ***************************************
				//ָ�Ƹ���Ϊ0-------------------------------------
				GetDlgItem(IDC_BTN_FINGER)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_PRINTDOC)->EnableWindow(FALSE);
				m_nFingerNum = 0;
			}
			
			UpdateData(FALSE);
			//д��ini�ļ�
			::WritePrivateProfileString(_T("PersonInfo"), _T("cardname"), m_editName, m_strCardIniPath); 
			::WritePrivateProfileString(_T("PersonInfo"), _T("cardsex"), m_editSex, m_strCardIniPath); 
			::WritePrivateProfileString(_T("PersonInfo"), _T("cardnation"), m_editNation, m_strCardIniPath); 
			::WritePrivateProfileString(_T("PersonInfo"), _T("cardbirthdate"), m_editBirth, m_strCardIniPath); 
			::WritePrivateProfileString(_T("PersonInfo"), _T("cardaddress"), m_editAddress, m_strCardIniPath); 
			::WritePrivateProfileString(_T("PersonInfo"), _T("cardid"), m_editCardnum, m_strCardIniPath); 
			::WritePrivateProfileString(_T("PersonInfo"), _T("cardissueo"), m_editOffice, m_strCardIniPath); 
			::WritePrivateProfileString(_T("PersonInfo"), _T("cardvaliddate"), m_editValidity, m_strCardIniPath); 
			::WritePrivateProfileString(_T("PersonInfo"), _T("cardimage"), tem_strNewPicName, m_strCardIniPath);
			::WritePrivateProfileString(_T("PersonInfo"), _T("carddate"), tem_strRecardDate, m_strCardIniPath);

			m_strVerifyTime = tem_strRecardDate;

			//д��excel
			Self_Write2Excel(m_strCardIniPath, m_strInfoBuffer);
			//�������֤��ӡ��
			tem_BIsFinded = tem_find.FindFile(tem_strIDCopyPath);
			if (!tem_BIsFinded)
			{
				Self_SaveCardCopy(m_stcIdInfo, m_strProntImg, m_strBackImg, tem_strIDCopyPath);				
			}
			if (m_BSaveCopy)
			{
				Self_ShowCopyImg(tem_strIDCopyPath);
			}

			//�����ɹ���ʾ
			CString     tem_strShowInfo = _T("");
			tem_strShowInfo.Format(_T("�����ɹ��������֤���� %d ��ָ�ƣ�"), m_nFingerNum);
			GetDlgItem(IDC_STA_INFO)->SetWindowText(tem_strShowInfo);
			CRect   tem_rcStaInfo;
			GetDlgItem(IDC_STA_INFO)->GetWindowRect(&tem_rcStaInfo); 
			ScreenToClient(&tem_rcStaInfo);        
			InvalidateRect(&tem_rcStaInfo);
			UpdateWindow();	

			return tem_strNewPicName;
		}
		else
		{
			GetDlgItem(IDC_BTN_FINGER)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_PRINTDOC)->EnableWindow(FALSE);

			m_iSubCard->CloseCardPort();
			GetDlgItem(IDC_STA_INFO)->SetWindowText(_T("����ʧ�ܣ����¶�����"));
			CRect   tem_rcStaInfo;
			GetDlgItem(IDC_STA_INFO)->GetWindowRect(&tem_rcStaInfo); 
			ScreenToClient(&tem_rcStaInfo);        
			InvalidateRect(&tem_rcStaInfo);
			UpdateWindow();	

			//���picture�ؼ�
			m_strCopyImg = _T("");
			Self_ClearImg();

			return _T("");
		}
			
	}
	else
	{
		GetDlgItem(IDC_BTN_FINGER)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_PRINTDOC)->EnableWindow(FALSE);
//		m_iSubCard->CloseCardPort();
		m_strCopyImg = _T("");
		Self_ClearImg();
		return _T("");
	}
	return tem_strNewPicName;
}


int CUDSCard::Self_Write2Excel(CString inipath, CString xlsdir)
{
	CString      tem_strExlPath = xlsdir;   //���Excel·��
	CString      tem_strPath;               //ini+excel����·������

	CString      tem_strExePath;
	TCHAR        tem_tcFilepath[MAX_PATH+1] = {0};
	GetModuleFileName(NULL, tem_tcFilepath, MAX_PATH);
	(_tcsrchr(tem_tcFilepath, _T('\\')))[1] = 0;

	tem_strExePath    = tem_tcFilepath;
	tem_strExePath   += _T("TxtToExcel.exe");   //�����ļ�·��


	tem_strExlPath += _T("\\");
	tem_strExlPath += _T("���֤��Ϣ��.xls");


	tem_strPath.Format(_T("\"%s\" \"%s\""),inipath, tem_strExlPath);   //\"ת���ַ���\"=".������˫����֮�䣬�������ŵ�������������������

	SHELLEXECUTEINFO  tem_shellIt;
	memset(&tem_shellIt, 0, sizeof(SHELLEXECUTEINFO));
	tem_shellIt.cbSize       = sizeof(SHELLEXECUTEINFO);
	tem_shellIt.fMask        = SEE_MASK_NOCLOSEPROCESS;
	tem_shellIt.lpVerb       = _T("open");
	tem_shellIt.lpFile       = tem_strExePath;
	tem_shellIt.lpParameters = tem_strPath;
	tem_shellIt.nShow        = SW_SHOW;
	tem_shellIt.hwnd         = m_hWnd;
	ShellExecuteEx(&tem_shellIt);
	return 0;
}


CString CUDSCard::Self_GetSystemTime(CString dir)
{
	CString       tem_strPicName = dir;   //���֤ͷ����
	SYSTEMTIME    tem_st;
	CString       tem_strDate, tem_strTime;

	GetLocalTime(&tem_st);
	tem_strDate.Format(_T("%d%02d%02d_"), tem_st.wYear, tem_st.wMonth, tem_st.wDay);
	tem_strTime.Format(_T("%02d%02d%02d"), tem_st.wHour, tem_st.wMinute, tem_st.wSecond);

	tem_strPicName += _T("\\");
	tem_strPicName += tem_strDate;
	tem_strPicName += tem_strTime;
	tem_strPicName += _T(".bmp");
	return tem_strPicName;
}


void CUDSCard::ShowPicture(CString imgpath)
{
	CWnd*  pWnd = NULL;
	pWnd = GetDlgItem(IDC_STA_PIC);
	pDc = pWnd->GetDC();

	int     cx, cy;    //ͼ����
	CxImage* pImage;
	pImage = new CxImage; 
	CRect    tem_rectChildPic;

	pImage->Load(imgpath);
	cx = pImage->GetWidth();
	cy = pImage->GetHeight();

	GetDlgItem(IDC_STA_PIC)->GetWindowRect(&tem_rectChildPic);
	ScreenToClient(&tem_rectChildPic);

	int   m_neww = 0;
	int   m_newh = 0;
	float m_picw = (float)(tem_rectChildPic.right-tem_rectChildPic.left);
	float m_pich = (float)(tem_rectChildPic.bottom-tem_rectChildPic.top);
	float m_pic_ratio = m_picw/m_pich;
	float m_imgw = (float)cx;
	float m_imgh = (float)cy;
	float m_img_ratio = m_imgw/m_imgh;
	if (m_img_ratio>m_pic_ratio)
	{
		m_neww = (int)m_picw;
		m_newh = (int)((m_picw/m_imgw)*m_imgh);
		pImage->Resample(m_neww, m_newh);
	}
	else
	{
		m_newh = (int)m_pich;
		m_neww = (int)((m_pich/m_imgh)*m_imgw);
		pImage->Resample(m_neww, m_newh);
	}
	imageDC.CreateCompatibleDC(pDc);
	HBITMAP   m_hBitmap;
	m_hBitmap = pImage->MakeBitmap(imageDC);
	CBitmap m_bmp;
	m_bmp.Attach(m_hBitmap);
	imageDC.SelectObject(&m_bmp);
	pDc->BitBlt(0,0,tem_rectChildPic.right,tem_rectChildPic.bottom,&imageDC,0,0,SRCCOPY);

	::delete pImage;	
}


/***************************
*     ����Ŀ¼
* 1������
* 2���˳�
* 3����Ŀ¼
* 4���Զ�����
* 5�������߳�
*
*
***************************/

void CUDSCard::OnBnClickedBtnSave()
{
	CString  tem_strPicPath = Self_GetSystemTime(m_strPicBuffer);
	tem_strPicPath = Self_ReadCard(tem_strPicPath);
	if (!tem_strPicPath.IsEmpty())
	{
		ShowPicture(tem_strPicPath);
	}
	Self_ShowFingerImg(_T("res\\FingerPrint.bmp"));
	GetDlgItem(IDC_STA_MATCHV)->SetWindowText(_T(""));
	GetDlgItem(IDC_STA_FINGERINDEX)->SetWindowText(_T(""));

	CRect   tem_rcStaInfo;
	GetDlgItem(IDC_STA_MATCHV)->GetWindowRect(&tem_rcStaInfo); 
	ScreenToClient(&tem_rcStaInfo);        
	InvalidateRect(&tem_rcStaInfo);

	GetDlgItem(IDC_STA_FINGERINDEX)->GetWindowRect(&tem_rcStaInfo); 
	ScreenToClient(&tem_rcStaInfo);        
	InvalidateRect(&tem_rcStaInfo);
	UpdateWindow();	
}


void CUDSCard::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����߳��Ƿ�رգ����߳�δ�رգ��ر��߳�
	DWORD dwExitCode = 0;  
	GetExitCodeThread(hThreadHandle, &dwExitCode);
	if (dwExitCode == STILL_ACTIVE)  
	{  
		KillTimer(1);
		TerminateThread(hThreadHandle,0);
	}  
	delete m_iSubCard;

	//���Finger�ļ����ڳ�bmp������ͼ��
	BOOL        bGetRc      = NULL;
	CFileFind   temFinder   = NULL;
	CString     strFileName = NULL;
	CString     strSubDoc   = NULL;
	CString     strFilePath = NULL;

	bGetRc = temFinder.FindFile(m_strFingerPath + "*.*");
	while (bGetRc)
	{
		bGetRc = temFinder.FindNextFile();
		if (temFinder.IsDots())
		{
			//ΪȱʡĿ¼
			continue;
		}
		else if (temFinder.IsDirectory())
		{
			//���Ϊ���ļ��У����汸��
			continue;
		} 
		else if (temFinder.IsCompressed())
		{
			//ѹ���ļ�
			continue;
		}
		else if (temFinder.IsSystem())
		{
			//ϵͳ�ļ�
			continue;
		}
		else
		{
			//���Ϊ�ļ������й���
			strFileName = temFinder.GetFileName();				
			CString  strMiddle = strFileName;
			int      nIndex = strMiddle.ReverseFind('.');
			if (nIndex != -1)
			{
				strMiddle = strMiddle.Mid(nIndex+1);
				strMiddle.MakeLower();
				if (strMiddle == _T("dat") || strMiddle == _T("wlt"))		
				{
					//����ͼ���ļ��ͷ�ͼ���ļ�����FieName����
					strFilePath = "";
					strFilePath = m_strFingerPath + strFileName;	
					DeleteFile(strFilePath);
				}
			}

		}
	}	

	std::vector<CString>::iterator tem_itItem;
	for (tem_itItem=m_vcFaceImg.begin(); tem_itItem!=m_vcFaceImg.end(); tem_itItem++)
	{
		::DeleteFile(*tem_itItem);
	}
	for (tem_itItem=m_vcFingerImg.begin(); tem_itItem!=m_vcFingerImg.end(); tem_itItem++)
	{
		::DeleteFile(*tem_itItem);
	}
	for (tem_itItem=m_vcQRCodeImg.begin(); tem_itItem!=m_vcQRCodeImg.end(); tem_itItem++)
	{
		::DeleteFile(*tem_itItem);
	}


	CDialogEx::OnCancel();
}


void CUDSCard::OnBnClickedOk()
{
	CString   tem_str = SubGetMyDocument();
	tem_str += _T("\\UDSData\\");
	tem_str += _T("���֤��Ϣ");
	ShellExecute(NULL, NULL, tem_str, NULL, NULL, SW_SHOW);
}


void CUDSCard::OnClickedChkAutocard()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_AUTOCARD))
	{
		m_BAutoRead           = TRUE;
		GetDlgItem(IDC_SLID_PERIOD)->EnableWindow(FALSE);
		//������ʱ�߳�
		stcThreadInfo.hWnd    = GetSafeHwnd();
		stcThreadInfo.nTime   = m_nReadTime;
		stcThreadInfo.strInfo = _T("");

		hThreadHandle = CreateThread(NULL, 0, ThreadProc, &stcThreadInfo, 0, &dwThreadID);
	} 
	else
	{
		m_BAutoRead = FALSE;
		GetDlgItem(IDC_SLID_PERIOD)->EnableWindow(TRUE);
		//�رռ�ʱ�߳�
		KillTimer(1);
		TerminateThread(hThreadHandle,0);
	}
	CRect    tem_rcRect;; 
	GetDlgItem(IDC_STA_PERIOD)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);
}


DWORD WINAPI ThreadProc(LPVOID lpParam)  
{
	ThreadInfo*   tem_stcThreadInfo = (ThreadInfo*)lpParam;
	SetTimer(tem_stcThreadInfo->hWnd, 1, tem_stcThreadInfo->nTime, NULL);
	return TRUE;
}


void CUDSCard::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString  tem_strPicPath = Self_GetSystemTime(m_strPicBuffer);
	tem_strPicPath = Self_ReadCard(tem_strPicPath);
	if (!tem_strPicPath.IsEmpty())
	{
		ShowPicture(tem_strPicPath);
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CUDSCard::Self_SaveCardCopy(IDCardInfo info, CString prontimg, CString backimg, CString outimg)
{
	if (m_BSaveCopy)
	{
		int        tem_nBackWidth  = 1580;    //����ֽ�Ŀ�
		int        tem_nBackHeight = 2280;    //����ֽ�ĸ�
		CString    tem_strImg         = info.imgpath;
		CString    tem_strName        = info.name;
		CString    tem_strSex         = info.sex;
		CString    tem_strNation      = info.nation;
		CString    tem_strBirth       = info.birth;
		CString    tem_strAddress     = info.address;
		CString    tem_strID          = info.IDnumber;
		CString    tem_strOffice      = info.office;
		CString    tem_strValidate    = info.validate;

		CString    tem_strBirth_year  = tem_strBirth.Mid(0,4);
		CString    tem_strBirth_month = tem_strBirth.Mid(5,2);
		CString    tem_strBirth_day   = tem_strBirth.Mid(8,2);

		//1)��ͼ�����------------------------------------------------------
		CxImage    pImageFront, pImageBack;
		CxImage    pImageCard;

		pImageFront.Load(prontimg, CMAX_IMAGE_FORMATS);
		pImageBack.Load(backimg, CMAX_IMAGE_FORMATS);
		pImageCard.Load(tem_strImg, CMAX_IMAGE_FORMATS);
		pImageFront.Light(0, 5);    pImageFront.Erode(3);    pImageFront.UnsharpMask(); 
		pImageBack.Light(0, 5);    pImageBack.Erode(3);    pImageBack.UnsharpMask(); 

		//2)ͼ��͸��--------------------------------------------------------
		pImageCard.AlphaCreate();
		pImageCard.AlphaSet(255);

		RGBQUAD   rgb = pImageCard.GetPixelColor(1, 120);     //	  rgb = {254, 254, 254, 0};

		int bpp = pImageCard.GetBpp();
		if (bpp!=24)
		{
			pImageCard.IncreaseBpp(24);
		}
		pImageCard.SetTransIndex(0);
		pImageCard.SetTransColor(rgb);
		pImageCard.Resample(310, 375);

		//3)ͼ��ϲ�---------------------------------------------------------
		pImageFront.Mix(pImageCard, CxImage::OpScreen, -656, -160, FALSE);       //ԭͼ���ƣ�͸��������������

		//4)������ֲ���-----------------------------------------------------
		CxImage::CXTEXTINFO WMTxtInfo;  // ��Ȩ����ˮӡ
		pImageFront.InitTextInfo( &WMTxtInfo );

		RGBQUAD   rgbTEXT = {0, 0, 0, 0};
		pImageFront.DrawString(0, 200, 124, tem_strName, rgbTEXT, _T("����"), 44, 400, 0, 0, false);
		pImageFront.DrawString(0, 200, 200, tem_strSex, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
		pImageFront.DrawString(0, 420, 200, tem_strNation, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
		pImageFront.DrawString(0, 200, 280, tem_strBirth_year, rgbTEXT, _T("����"), 40, 400, 0, 0, false);
		pImageFront.DrawString(0, 360, 280, tem_strBirth_month, rgbTEXT, _T("����"), 40, 400, 0, 0, false);
		pImageFront.DrawString(0, 460, 280, tem_strBirth_day, rgbTEXT, _T("����"), 40, 400, 0, 0, false);

		//ÿ�������ʾ11�������ַ�
		int tem_nSize = tem_strAddress.GetLength();
		if (tem_nSize<=11)
		{
			pImageFront.DrawString(0, 200, 360, tem_strAddress, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
		}
		else if (tem_nSize>11 && tem_nSize<=22)
		{
			CString tem_strFirst  = tem_strAddress.Mid(0, 11);
			pImageFront.DrawString(0, 200, 360, tem_strFirst, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
			CString tem_strSecond = tem_strAddress.Mid(11);
			pImageFront.DrawString(0, 200, 415, tem_strSecond, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
		}
		else if (tem_nSize>22 && tem_nSize<=33)
		{
			CString tem_strFirst  = tem_strAddress.Mid(0, 11);
			pImageFront.DrawString(0, 200, 360, tem_strFirst, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
			CString tem_strSecond = tem_strAddress.Mid(11, 11);
			pImageFront.DrawString(0, 200, 415, tem_strSecond, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
			CString tem_strThird  = tem_strAddress.Mid(22);
			pImageFront.DrawString(0, 200, 470, tem_strThird, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
		}
		else
		{
			CString tem_strFirst  = tem_strAddress.Mid(0, 11);
			pImageFront.DrawString(0, 200, 360, tem_strFirst, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
			CString tem_strSecond = tem_strAddress.Mid(11, 11);
			pImageFront.DrawString(0, 200, 415, tem_strSecond, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
			CString tem_strThird  = tem_strAddress.Mid(22,11);
			pImageFront.DrawString(0, 200, 470, tem_strThird, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
			CString tem_strFouth  = tem_strAddress.Mid(33);
			pImageFront.DrawString(0, 200, 525, tem_strFouth, rgbTEXT, _T("����"), 37, 400, 0, 0, false);

		}

		pImageFront.DrawString(0, 350, 565, tem_strID, rgbTEXT, _T("OCR-B 10 BT"), 50, 400, 0, 0, false);

		pImageBack.DrawString(0, 430, 485, tem_strOffice, rgbTEXT, _T("����"), 37, 200, 0, 0, false);
		pImageBack.DrawString(0, 430, 570, tem_strValidate, rgbTEXT, _T("����"), 38, 200, 0, 0, false);


		//˫ͼ�ϲ�
		CxImage    pImageMerge;
		COLORREF   rgbBack = RGB(255, 255, 255);
		pImageMerge.Create(tem_nBackWidth, tem_nBackHeight, 24);
		for (unsigned int i=0; i<pImageMerge.GetWidth(); i++)
		{
			for (unsigned int j=0; j<pImageMerge.GetHeight(); j++)
			{
				pImageMerge.SetPixelColor(i, j,rgbBack);
			}
		}

		pImageMerge.SetXDPI(200);
		pImageMerge.SetYDPI(200);

		pImageFront.SetXDPI(200);
		pImageFront.SetYDPI(200);
		pImageFront.Resample(674, 426);
		int   tem_nOffsetX = (tem_nBackWidth-pImageFront.GetWidth())/2;
		int   tem_nOffsetY = (tem_nBackHeight-3*pImageFront.GetHeight()/2);
		pImageMerge.MixFrom(pImageFront, tem_nOffsetX, tem_nOffsetY);

		pImageBack.SetXDPI(200);
		pImageBack.SetYDPI(200);
		pImageBack.Resample(674, 426);
		tem_nOffsetY = tem_nBackHeight-3*pImageFront.GetHeight();
		pImageMerge.MixFrom(pImageBack, tem_nOffsetX, tem_nOffsetY);


		pImageMerge.Save(outimg, CXIMAGE_FORMAT_JPG);

	}
}


void CUDSCard::Self_ShowCopyImg(CString img)
{
	CxImage* pImage;
	pImage = new CxImage;
	pImage->Load(img, CXIMAGE_FORMAT_JPG);
	CWnd*  pWnd = NULL;
	pWnd = GetDlgItem(IDC_STA_COPYIMG);
	pDc = pWnd->GetDC();

	CRect    tem_rectChildPic;
	GetDlgItem(IDC_STA_COPYIMG)->GetWindowRect(&tem_rectChildPic);
	ScreenToClient(&tem_rectChildPic);

	pImage->Resample(tem_rectChildPic.Width(), tem_rectChildPic.Height());
	imageDC.CreateCompatibleDC(pDc);
	HBITMAP   m_hBitmap;
	m_hBitmap = pImage->MakeBitmap(imageDC);
	CBitmap m_bmp;
	m_bmp.Attach(m_hBitmap);
	imageDC.SelectObject(&m_bmp);
	pDc->BitBlt(0,0,tem_rectChildPic.right,tem_rectChildPic.bottom,&imageDC,0,0,SRCCOPY);
}


void CUDSCard::Self_ClearImg(void)
{
	CWnd*  tem_pWnd = NULL;
	tem_pWnd = GetDlgItem(IDC_STA_PIC);
	CDC*   tem_pDc;
	tem_pDc = tem_pWnd->GetDC();
	CRect   tem_rcPicRect;
	GetDlgItem(IDC_STA_PIC)->GetWindowRect(&tem_rcPicRect);
	ScreenToClient(&tem_rcPicRect);

	tem_pDc->FillSolidRect(0, 0, tem_rcPicRect.Width(), tem_rcPicRect.Height(),RGB(176,198,191));
	m_conCardImg.SetBitmap(NULL);

	tem_pWnd = GetDlgItem(IDC_STA_COPYIMG);
	tem_pDc = tem_pWnd->GetDC();
	GetDlgItem(IDC_STA_COPYIMG)->GetWindowRect(&tem_rcPicRect);
	ScreenToClient(&tem_rcPicRect);

	tem_pDc->FillSolidRect(0, 0, tem_rcPicRect.Width(), tem_rcPicRect.Height(),RGB(176,198,191));
	m_conCardImg.SetBitmap(NULL);
}


void CUDSCard::OnBnClickedChkSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED ==IsDlgButtonChecked(IDC_CHK_SAVE))
	{
		m_BSaveCopy = TRUE;
	} 
	else
	{
		m_BSaveCopy = FALSE;
	}
}


void CUDSCard::OnDblclkStaCopyimg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_strCopyImg != _T("")&&m_BSaveCopy)
	{
		ShellExecute(NULL, _T("open"), m_strCopyImg, NULL, NULL, SW_SHOWNORMAL);
	}
}


void CUDSCard::OnCustomdrawSlidPeriod(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nReadTime            = m_conPeriod.GetPos();
	float    tem_fPeriod   = (float)m_nReadTime*1.0/1000;
	CString  tem_strPeriod = _T("");
	tem_strPeriod.Format(_T("%.1f"), tem_fPeriod);
	GetDlgItem(IDC_STA_PERIODV)->SetWindowText(tem_strPeriod);
	CRect    tem_rcRect;; 
	GetDlgItem(IDC_STA_PERIODV)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); 
	InvalidateRect(&tem_rcRect);

	//д��ini�ļ�
	CString tem_strSens = _T("");
	tem_strSens.Format(_T("%d"), m_nReadTime);
	::WritePrivateProfileString(_T("Resource"), _T("ReadSens"), tem_strSens, m_strIniPath2); 


	*pResult = 0;
}

//ָ�Ʋɼ���ָ��ʶ��--------------------------------------------------------------
BYTE penple_code[10 * 2];
void CUDSCard::OnBnClickedBtnFinger()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	float      tem_fProximity  = 0;
	CString    tem_strImgPath  = m_strFingerPath;
	CString    tem_strDatPath  = m_strFingerPath;
	tem_strImgPath    += m_editName;
	tem_strImgPath    += m_editCardnum;
	tem_strImgPath    += _T(".bmp");

	m_strFingerImg     = tem_strImgPath;

	tem_strDatPath    += m_editName;
	tem_strDatPath    += m_editCardnum;
	tem_strDatPath    += _T(".dat");

	//1����ȡ����ʾָ����Ϣ
	CString tem_strRC = Self_ReadFigerPrint(tem_strImgPath);
	if (tem_strRC == _T(""))
	{
		return;
	}
	m_vcFingerImg.push_back(tem_strImgPath);
	//2���ȶԲ���ʾ���
	tem_fProximity = Self_ExMatchFeatures(tem_strImgPath, tem_strDatPath);

	//3��ָ��ƥ����ȷ��Ϊ�ĸ���ָ
	CString tem_strMatchResult = _T("");
	if (tem_fProximity >= m_fPassValue)
	{
		//ƥ��ɹ�
		switch(penple_code[2*m_nFigerIndex])
		{
		case 11: 
			m_strFingerIndex = _T("����Ĵָ"); 
			break;
		case 12: 
			m_strFingerIndex = _T("����ʳָ"); 
			break;
		case 13: 
			m_strFingerIndex = _T("������ָ"); 
			break;
		case 14: 
			m_strFingerIndex = _T("���ֻ�ָ"); 
			break;
		case 15: 
			m_strFingerIndex =_T( "����Сָ"); 
			break;
		case 16: 
			m_strFingerIndex = _T("����Ĵָ"); 
			break;
		case 17: 
			m_strFingerIndex = _T("����ʳָ"); 
			break;
		case 18: 
			m_strFingerIndex = _T("������ָ"); 
			break;
		case 19: 
			m_strFingerIndex = _T("���ֻ�ָ"); 
			break;
		case 20: 
			m_strFingerIndex = _T("����Сָ"); 
			break;
		case 97: 
			m_strFingerIndex = _T("���ֲ�ȷ��ָ"); 
			break;
		case 98: 
			m_strFingerIndex = _T("���ֲ�ȷ��ָ"); 
			break;
		case 99: 
			m_strFingerIndex = _T("��ȷ��ָ"); 
			break;
		default: 
			break;
		}
		
		tem_strMatchResult.Format(_T("ƥ��\n���ƶȣ� %.1f%%"), tem_fProximity*100);
		GetDlgItem(IDC_STA_MATCHV)->SetWindowText(tem_strMatchResult);
		GetDlgItem(IDC_STA_FINGERINDEX)->SetWindowText(m_strFingerIndex);

		m_strScore.Format(_T("%.1f%%"), tem_fProximity*100);
		m_strResult = _T("ƥ��");
	}
	else
	{
		//ƥ��ʧ��
		m_strFingerIndex = _T("");
		tem_strMatchResult.Format(_T("��ƥ��\n���ƶȣ� %.1f%%"), tem_fProximity*100);
		GetDlgItem(IDC_STA_MATCHV)->SetWindowText(tem_strMatchResult);
		GetDlgItem(IDC_STA_FINGERINDEX)->SetWindowText(m_strFingerIndex);

		m_strScore.Format(_T("%.1f%%"), tem_fProximity*100);
		m_strResult = _T("��ƥ��");
	}
	
	
	CRect   tem_rcStaInfo;
	GetDlgItem(IDC_STA_MATCHV)->GetWindowRect(&tem_rcStaInfo); 
	ScreenToClient(&tem_rcStaInfo);        
	InvalidateRect(&tem_rcStaInfo);

	GetDlgItem(IDC_STA_FINGERINDEX)->GetWindowRect(&tem_rcStaInfo); 
	ScreenToClient(&tem_rcStaInfo);        
	InvalidateRect(&tem_rcStaInfo);
	UpdateWindow();	
}


BYTE FPRawData[FPRIMG_MAX_SIZE];                            //�ɼ�����ָ��ͼ���Ԫ����
BYTE g_FPBmpData[BMP_HEAD_SIZE + FPRIMG_MAX_SIZE];          //bmpͼ������ָ�룬���ڱ���Ϊbmpͼ��
BYTE g_FPBmpDataTemp[360*256];                              //bmpͼ������ָ�룬����������ȡ
CString CUDSCard::Self_ReadFigerPrint(CString imgpath)
{
	if (LIVESCAN_Init() == LIVESCAN_SUCCESS)
	{
		int  tem_nRC = LIVESCAN_GetCaptWindow(0, &m_nOriX, &m_nOriY, &m_nWidth, &m_nHeight);
		char szDesc[1024] = {0};
		memset(szDesc, 0, 1024);
		tem_nRC = LIVESCAN_GetDesc(szDesc);
		if (tem_nRC != LIVESCAN_SUCCESS)
		{
			//��ȡͼ������ʧ��
			GetDlgItem(IDC_STA_INFO)->SetWindowText(_T("��ȡָ������ʧ�ܣ�"));
			CRect   tem_rcStaInfo;
			GetDlgItem(IDC_STA_INFO)->GetWindowRect(&tem_rcStaInfo); 
			ScreenToClient(&tem_rcStaInfo);        
			InvalidateRect(&tem_rcStaInfo);
			return _T("");
		}
		tem_nRC = LIVESCAN_BeginCapture(0);
		if (tem_nRC != LIVESCAN_SUCCESS)
		{
			GetDlgItem(IDC_STA_INFO)->SetWindowText(_T("��ȡָ��ͼ��ʧ�ܣ�"));
			CRect   tem_rcStaInfo;
			GetDlgItem(IDC_STA_INFO)->GetWindowRect(&tem_rcStaInfo); 
			ScreenToClient(&tem_rcStaInfo);        
			InvalidateRect(&tem_rcStaInfo);
			return _T("");
		}
		//1����ȡͼ��Raw����----------------------------
		tem_nRC = LIVESCAN_GetFPRawData(0, FPRawData);
		//2����Raw����תΪBmp---------------------------
		USES_CONVERSION;
		char* tem_cImgPath = T2A(imgpath);
		imgpath.ReleaseBuffer();
		if (tem_nRC == LIVESCAN_SUCCESS)
		{
			//1)��д���ļ�ͷ----------------------------
			WriteHead(g_FPBmpData, FPRawData, m_nWidth, m_nHeight);      //Ԫ����ΪRAW��Ȼ����װ��λbmp
			//2)��д���ļ�����--------------------------
			FPBmpDataToBmp(g_FPBmpData, BMP_HEAD_SIZE + m_nWidth * m_nHeight, tem_cImgPath);
			tem_nRC = LIVESCAN_EndCapture(0);
			if (tem_nRC != LIVESCAN_SUCCESS)
			{
				return _T("");
			}
			tem_nRC = LIVESCAN_Close();
			if(tem_nRC != LIVESCAN_SUCCESS)
			{
				return _T("");
			}	
		}
		Self_ShowFingerImg(imgpath);
		LoadDll();
		tem_nRC = FP_Begin();
		unsigned char tem_cScore = 0;
		tem_nRC = FP_GetQualityScore(FPRawData, &tem_cScore);      //��ȡָ��ͼ�������ֵ,ͼ������ֵ 00H - 64H;��������ͼ����������ʱδ��
		CString tem_strScore;
		tem_strScore.Format(_T("%d"), tem_cScore);
		tem_nRC = FP_End();
		FreeDll();
	}
	else 
	{
		GetDlgItem(IDC_STA_INFO)->SetWindowText(_T("ָ���豸����ʧ�ܣ�"));
		CRect   tem_rcStaInfo;
		GetDlgItem(IDC_STA_INFO)->GetWindowRect(&tem_rcStaInfo); 
		ScreenToClient(&tem_rcStaInfo);        
		InvalidateRect(&tem_rcStaInfo);
		UpdateWindow();	

		return _T("");
	}
	return imgpath;
}


int CUDSCard::WriteHead(unsigned char* Output, unsigned char* Input, int nWidth, int nHeight)
{
	int IMAGE_X=nWidth,IMAGE_Y=nHeight;
	unsigned char head[1078]={
		/***************************/
		//file header
		0x42,0x4d,//file type 
		//0x36,0x6c,0x01,0x00, //file size***
		0x0,0x0,0x0,0x00, //file size***
		0x00,0x00, //reserved
		0x00,0x00,//reserved
		0x36,0x4,0x00,0x00,//head byte***
		/***************************/
		//infoheader
		0x28,0x00,0x00,0x00,//struct size

		//0x00,0x01,0x00,0x00,//map width*** 
		0x00,0x00,0x0,0x00,//map width*** 
		//0x68,0x01,0x00,0x00,//map height***
		0x00,0x00,0x00,0x00,//map height***

		0x01,0x00,//must be 1
		0x08,0x00,//color count***
		0x00,0x00,0x00,0x00, //compression
		//0x00,0x68,0x01,0x00,//data size***
		0x00,0x00,0x00,0x00,//data size***
		0x00,0x00,0x00,0x00, //dpix
		0x00,0x00,0x00,0x00, //dpiy
		0x00,0x00,0x00,0x00,//color used
		0x00,0x00,0x00,0x00,//color important

	};

	long num;
	num=IMAGE_X; head[18]= num & 0xFF;
	num=num>>8;  head[19]= num & 0xFF;
	num=num>>8;  head[20]= num & 0xFF;
	num=num>>8;  head[21]= num & 0xFF;


	num=IMAGE_Y; head[22]= num & 0xFF;
	num=num>>8;  head[23]= num & 0xFF;
	num=num>>8;  head[24]= num & 0xFF;
	num=num>>8;  head[25]= num & 0xFF;

	int i,j;

	j=0;
	for (i=54;i<1078;i=i+4)
	{
		head[i]=head[i+1]=head[i+2]=j; 
		head[i+3]=0;
		j++;
	} 

	memcpy(Output,head,sizeof(byte)*1078);
	for(  i=0;i<=IMAGE_Y-1; i++ )
	{
		memcpy(Output+1078*sizeof(char)+(i)*(IMAGE_X),Input+i*IMAGE_X,IMAGE_X*sizeof(char));
	}

	return 1;
}


void CUDSCard::FPBmpDataToBmp(BYTE* FPBmpData, DWORD dataLen, char* bmpFileName)
{
	FILE *nf = fopen(bmpFileName, "wb");
	if (!nf)
		return;

	fwrite(FPBmpData, sizeof(unsigned char), dataLen, nf);
	fclose(nf);
}


void CUDSCard::Self_ShowFingerImg(CString img)
{
	CxImage* pImage;
	pImage = new CxImage;
	pImage->Load(img, CXIMAGE_FORMAT_JPG);
	CWnd*  pWnd = NULL;
	pWnd = GetDlgItem(IDC_PIC_FINGERORINT);
	pDc = pWnd->GetDC();

	CRect    tem_rectChildPic;
	GetDlgItem(IDC_PIC_FINGERORINT)->GetWindowRect(&tem_rectChildPic);
	ScreenToClient(&tem_rectChildPic);

	pImage->Resample(tem_rectChildPic.Width(), tem_rectChildPic.Height());
	imageDC.CreateCompatibleDC(pDc);
	HBITMAP   m_hBitmap;
	m_hBitmap = pImage->MakeBitmap(imageDC);
	CBitmap m_bmp;
	m_bmp.Attach(m_hBitmap);
	imageDC.SelectObject(&m_bmp);
	pDc->BitBlt(0,0,tem_rectChildPic.right,tem_rectChildPic.bottom,&imageDC,0,0,SRCCOPY);
}

//����ȡ�ͺϲ������϶�Ϊһ-------------------------------------
BYTE FPcharDatatemp[512];     //��������ָ��
void CUDSCard::Self_ExtractFeatures(CString imgpath)
{
	USES_CONVERSION;
	char* tem_cImgPath = T2A(imgpath);
	LoadDll();
	//1����ȡ�ļ����ݣ���������ָ��
	FILE*    tem_fileImg;
	tem_fileImg = fopen(tem_cImgPath, "rb");
	fseek(tem_fileImg, 1078, SEEK_SET);
	long     tem_nFileLength = fread(g_FPBmpDataTemp, sizeof(char), 360*256, tem_fileImg);
	fclose(tem_fileImg);

	//2����ȡ��������������Ϊ��������ָ��
	int       tem_nRC = FP_Begin();
	tem_nRC = FP_FeatureExtract(0, 0, g_FPBmpDataTemp, FPcharDatatemp);   //��ȡͼ������
	if (tem_nRC != LIVESCAN_SUCCESS)
	{
		return;
	}
	tem_nRC = FP_End();
	FreeDll();
}
BYTE pTemplate[512*10];
void CUDSCard::Self_MatchFeatures(CString datpath)
{
	USES_CONVERSION;
	char* tem_cDatPath = T2A(datpath);

	LoadDll();
	int    tem_nRC = FP_Begin();
	int    tem_nReadItems   = 0;     //��ȡ��������
	int    tem_nFileLenghth = 0;
	int    tem_nFileSize    = 0;     //�õ��ļ�λ��������ļ��׵�ƫ���ֽ���
	float  tem_fProximity   = 0;

	FILE* tem_fileDat;
	if ((tem_fileDat = fopen(tem_cDatPath, "rb")) == NULL)
	{
		return;
	}
	fseek(tem_fileDat, 0, SEEK_END);
	tem_nFileSize = ftell(tem_fileDat);
	rewind(tem_fileDat);
	tem_nReadItems = fread(pTemplate, sizeof(char), tem_nFileSize, tem_fileDat);
	fclose(tem_fileDat);

	//��ȡDat�ļ���ָ�Ƹ���
	int  tem_nFingerNum = tem_nFileSize/512;

	BYTE temp[512];
	for (int i=0; i<tem_nFingerNum; i++)
	{
		for (int j=0; j<512; j++)
		{
			temp[j] = pTemplate[512*i + j];
		}
		tem_nRC = FP_FeatureMatch(FPcharDatatemp, temp, &tem_fProximity);
		if (tem_nRC == 1)
		{
			//�ȶԳɹ�����ʾ�ȶԽ��
		}
		else
		{
			//�ȶ�ʧ�ܣ����²ɼ�ָ��ͼ��
		}

	}
	
	tem_nRC = FP_End();
	FreeDll();
}


float CUDSCard::Self_ExMatchFeatures(CString imgpath, CString datpath)
{
	m_strFingerIndex = _T("");
	float  tem_fMaxValue  = -1;

	USES_CONVERSION;
	char* tem_cImgPath = T2A(imgpath);
	char* tem_cDatPath = T2A(datpath);

	LoadDll();
	//1����ȡͼ���ļ����ݣ���������ָ��-----------------------------------
	FILE*    tem_fileImg;
	tem_fileImg = fopen(tem_cImgPath, "rb");
	fseek(tem_fileImg, 1078, SEEK_SET);
	long     tem_nFileLength = fread(g_FPBmpDataTemp, sizeof(char), 360*256, tem_fileImg);
	fclose(tem_fileImg);

	//2����ȡ��������������Ϊ��������ָ��---------------------------------
	int       tem_nRC = FP_Begin();
	tem_nRC = FP_FeatureExtract(0, 0, g_FPBmpDataTemp, FPcharDatatemp);   //��ȡͼ������
	if (tem_nRC != LIVESCAN_SUCCESS)
	{
		tem_nRC = FP_End();
		FreeDll();
		return 0;    //��ȡָ������ʧ�ܣ������²ɼ�ָ��
	}

	//3����ȡָ���ļ�����-------------------------------------------------
	int    tem_nReadItems   = 0;     //��ȡ��������
	int    tem_nFileLenghth = 0;
	int    tem_nFileSize    = 0;     //�õ��ļ�λ��������ļ��׵�ƫ���ֽ���
	float  tem_fProximity   = 0;

	FILE* tem_fileDat;
	if ((tem_fileDat = fopen(tem_cDatPath, "rb")) == NULL)
	{
		tem_nRC = FP_End();
		FreeDll();
		return 0;    //û���ҵ�ָ��dat�ļ�
	}
	fseek(tem_fileDat, 0, SEEK_END);
	tem_nFileSize = ftell(tem_fileDat);
	rewind(tem_fileDat);
	tem_nReadItems = fread(pTemplate, sizeof(char), tem_nFileSize, tem_fileDat);
	fclose(tem_fileDat);

	//��ȡDat�ļ���ָ�Ƹ���
	int  tem_nFingerNum = tem_nFileSize/512;

	BYTE temp[512];
	for (int i=0; i<tem_nFingerNum; i++)
	{
		//���ȡֵdat��ָ������-------------
		for (int j=0; j<512; j++)
		{
			temp[j] = pTemplate[512*i + j];
		}
		//ȡ����Ӧdat�е�ָ�ƶ�λ����--------
		penple_code[2 * i] = pTemplate[512*i + 5];

		tem_nRC = FP_FeatureMatch(FPcharDatatemp, temp, &tem_fProximity);
		if (tem_nRC == 1)
		{
			//ƥ��ɹ�����¼���ƶ�
			if (tem_fProximity>tem_fMaxValue)
			{
				tem_fMaxValue = tem_fProximity;
				m_nFigerIndex = i;
			}
			
		}
		
	}

	tem_nRC = FP_End();
	FreeDll();

	//����һ�����ƶ�����
	return tem_fMaxValue;
}


void CUDSCard::Self_SetCtrlState(int mode)
{
	
}


void CUDSCard::OnBnClickedBtnPrintdoc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Self_SaveResultCopy(m_stcIdInfo, m_strProntImg, m_strBackImg, m_strResultImg);
	
}


void CUDSCard::Self_SaveResultCopy(IDCardInfo info, CString prontimg, CString backimg, CString outimg)
{

	if (m_strFingerImg == _T(""))
	{
		return;
	}
	int        tem_nBackWidth  = 1580;    //����ֽ�Ŀ�
	int        tem_nBackHeight = 2280;    //����ֽ�ĸ�
	CString    tem_strImg         = info.imgpath;
	CString    tem_strName        = info.name;
	CString    tem_strSex         = info.sex;
	CString    tem_strNation      = info.nation;
	CString    tem_strBirth       = info.birth;
	CString    tem_strAddress     = info.address;
	CString    tem_strID          = info.IDnumber;
	CString    tem_strOffice      = info.office;
	CString    tem_strValidate    = info.validate;

	CString    tem_strBirth_year  = tem_strBirth.Mid(0,4);
	CString    tem_strBirth_month = tem_strBirth.Mid(5,2);
	CString    tem_strBirth_day   = tem_strBirth.Mid(8,2);

	//1)��ͼ�����------------------------------------------------------
	CxImage    pImageFront, pImageBack;
	CxImage    pImageCard;

	pImageFront.Load(prontimg, CMAX_IMAGE_FORMATS);
	pImageBack.Load(backimg, CMAX_IMAGE_FORMATS);
	pImageCard.Load(tem_strImg, CMAX_IMAGE_FORMATS);
	pImageFront.Light(0, 5);    pImageFront.Erode(3);    pImageFront.UnsharpMask(); 
	pImageBack.Light(0, 5);    pImageBack.Erode(3);    pImageBack.UnsharpMask(); 

	//2)ͼ��͸��--------------------------------------------------------
	pImageCard.AlphaCreate();
	pImageCard.AlphaSet(255);

	RGBQUAD   rgb = pImageCard.GetPixelColor(1, 120);     //	  rgb = {254, 254, 254, 0};

	int bpp = pImageCard.GetBpp();
	if (bpp!=24)
	{
		pImageCard.IncreaseBpp(24);
	}
	pImageCard.SetTransIndex(0);
	pImageCard.SetTransColor(rgb);
	pImageCard.Resample(310, 375);

	//3)ͼ��ϲ�---------------------------------------------------------
	pImageFront.Mix(pImageCard, CxImage::OpScreen, -656, -160, FALSE);       //ԭͼ���ƣ�͸��������������

	//4)������ֲ���-----------------------------------------------------
	CxImage::CXTEXTINFO WMTxtInfo;  // ��Ȩ����ˮӡ
	pImageFront.InitTextInfo( &WMTxtInfo );

	RGBQUAD   rgbTEXT = {0, 0, 0, 0};
	pImageFront.DrawString(0, 200, 124, tem_strName, rgbTEXT, _T("����"), 44, 400, 0, 0, false);
	pImageFront.DrawString(0, 200, 200, tem_strSex, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
	pImageFront.DrawString(0, 420, 200, tem_strNation, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
	pImageFront.DrawString(0, 200, 280, tem_strBirth_year, rgbTEXT, _T("����"), 40, 400, 0, 0, false);
	pImageFront.DrawString(0, 360, 280, tem_strBirth_month, rgbTEXT, _T("����"), 40, 400, 0, 0, false);
	pImageFront.DrawString(0, 460, 280, tem_strBirth_day, rgbTEXT, _T("����"), 40, 400, 0, 0, false);

	//ÿ�������ʾ11�������ַ�
	int tem_nSize = tem_strAddress.GetLength();
	if (tem_nSize<=11)
	{
		pImageFront.DrawString(0, 200, 360, tem_strAddress, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
	}
	else if (tem_nSize>11 && tem_nSize<=22)
	{
		CString tem_strFirst  = tem_strAddress.Mid(0, 11);
		pImageFront.DrawString(0, 200, 360, tem_strFirst, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
		CString tem_strSecond = tem_strAddress.Mid(11);
		pImageFront.DrawString(0, 200, 415, tem_strSecond, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
	}
	else if (tem_nSize>22 && tem_nSize<=33)
	{
		CString tem_strFirst  = tem_strAddress.Mid(0, 11);
		pImageFront.DrawString(0, 200, 360, tem_strFirst, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
		CString tem_strSecond = tem_strAddress.Mid(11, 11);
		pImageFront.DrawString(0, 200, 415, tem_strSecond, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
		CString tem_strThird  = tem_strAddress.Mid(22);
		pImageFront.DrawString(0, 200, 470, tem_strThird, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
	}
	else
	{
		CString tem_strFirst  = tem_strAddress.Mid(0, 11);
		pImageFront.DrawString(0, 200, 360, tem_strFirst, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
		CString tem_strSecond = tem_strAddress.Mid(11, 11);
		pImageFront.DrawString(0, 200, 415, tem_strSecond, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
		CString tem_strThird  = tem_strAddress.Mid(22,11);
		pImageFront.DrawString(0, 200, 470, tem_strThird, rgbTEXT, _T("����"), 37, 400, 0, 0, false);
		CString tem_strFouth  = tem_strAddress.Mid(33);
		pImageFront.DrawString(0, 200, 525, tem_strFouth, rgbTEXT, _T("����"), 37, 400, 0, 0, false);

	}

	pImageFront.DrawString(0, 350, 565, tem_strID, rgbTEXT, _T("OCR-B 10 BT"), 50, 400, 0, 0, false);

	pImageBack.DrawString(0, 430, 485, tem_strOffice, rgbTEXT, _T("����"), 37, 200, 0, 0, false);
	pImageBack.DrawString(0, 430, 570, tem_strValidate, rgbTEXT, _T("����"), 38, 200, 0, 0, false);


	//˫ͼ�ϲ�
	CxImage    pImageMerge;
	COLORREF   rgbBack = RGB(255, 255, 255);
	pImageMerge.Create(tem_nBackWidth, tem_nBackHeight, 24);
	for (unsigned int i=0; i<pImageMerge.GetWidth(); i++)
	{
		for (unsigned int j=0; j<pImageMerge.GetHeight(); j++)
		{
			pImageMerge.SetPixelColor(i, j,rgbBack);
		}
	}

	pImageMerge.SetXDPI(200);
	pImageMerge.SetYDPI(200);

	pImageFront.SetXDPI(200);
	pImageFront.SetYDPI(200);
	pImageFront.Resample(674, 426);
	// 	int   tem_nOffsetX = (tem_nBackWidth-pImageFront.GetWidth())/2;
	// 	int   tem_nOffsetY = (tem_nBackHeight-3*pImageFront.GetHeight()/2);
	int   tem_nOffsetX = 200;
	int   tem_nOffsetY = tem_nBackHeight - 800;
	pImageMerge.MixFrom(pImageFront, tem_nOffsetX, tem_nOffsetY);

	pImageBack.SetXDPI(200);
	pImageBack.SetYDPI(200);
	pImageBack.Resample(674, 426);
	//	tem_nOffsetY = tem_nBackHeight-3*pImageFront.GetHeight();
	tem_nOffsetY -= 430;
	pImageMerge.MixFrom(pImageBack, tem_nOffsetX, tem_nOffsetY);

	//��ӱ���----------------------------------------------------------------------------------
	m_strCopyBT = _T("ָ�ƶԱ�ȷ�ϵ�");
	pImageMerge.DrawString(0, 500, 220, m_strCopyBT, rgbTEXT, _T("����"),90, 400, 0, 0, false);

	//��Ӷ�ά��--------------------------------------------------------------------------------
	//	m_strQRCode = _T("D:\\Documents\\UDSData\\���֤��Ϣ\\Image\\IMG_4297.JPG");

	m_strQRImgInfo     = m_stcIdInfo.name;
	m_strQRImgInfo    += m_stcIdInfo.sex;
	m_strQRImgInfo    += m_stcIdInfo.nation;
	m_strQRImgInfo    += m_stcIdInfo.birth;
	m_strQRImgInfo    += m_stcIdInfo.address;
	m_strQRImgInfo    += m_stcIdInfo.IDnumber;
	m_strQRImgInfo    += m_stcIdInfo.office;
	m_strQRImgInfo    += m_stcIdInfo.validate;
	m_strQRImgInfo    += m_strFingerIndex;
	m_strQRImgInfo    += _T("�ȶԷ�ֵ��");
	m_strQRImgInfo    += m_strScore;
	m_strQRImgInfo    += _T("�ȶԽ����");
	m_strQRImgInfo    += m_strResult;
	m_strQRImgInfo    += _T("��֤ʱ�䣺");
	m_strQRImgInfo    += m_strVerifyTime;

	CStringA tem_straPath(m_strQRCode.GetBuffer(0));  
	m_strQRCode.ReleaseBuffer();  	
	std::string   tem_sPath = tem_straPath.GetBuffer(0);  
 
	CStringA tem_straInfo(m_strQRImgInfo.GetBuffer(0));  
	m_strQRImgInfo.ReleaseBuffer();  
	std::string   tem_sInfo = tem_straInfo.GetBuffer(0); 
 
	
 	GernerateBarcode(tem_sInfo.c_str(), 0, tem_sPath.c_str());
	m_vcQRCodeImg.push_back(m_strQRCode);

	CxImage    pImageQRCode;
	pImageQRCode.Load(m_strQRCode, CMAX_IMAGE_FORMATS);
	pImageQRCode.SetXDPI(200);
	pImageQRCode.SetYDPI(200);
	pImageQRCode.Resample(250, 250);
	tem_nOffsetX = 1000;
	tem_nOffsetY = tem_nBackHeight - 700;
	pImageMerge.MixFrom(pImageQRCode, tem_nOffsetX, tem_nOffsetY);


	//��ӱȶԽ��-------------------------------------------------------------------------------
	CString   tem_strScore = _T("�ȶԷ�ֵ��");
	tem_strScore += m_strScore;

	CString   tem_strResult= _T("�ȶԽ����");
	tem_strResult+= m_strResult;

	pImageMerge.DrawString(0, 1000, 1000, tem_strScore, rgbTEXT, _T("����"),40, 400, 0, 0, false);
	pImageMerge.DrawString(0, 1000, 1100, tem_strResult, rgbTEXT, _T("����"),40, 400, 0, 0, false);

	//����ֳ�����ͼ��---------------------------------------------------------------------------
	CxImage    pImageFaceImg;
	pImageFaceImg.Load(m_strFingerImg, CMAX_IMAGE_FORMATS);
// 	int        tem_nNewWidth, tem_nNewHigh;
// 	if (pImageFaceImg.GetWidth()>pImageFaceImg.GetHeight())
// 	{
// 		tem_nNewWidth = 500;
// 		tem_nNewHigh  = (int)(tem_nNewWidth*pImageFaceImg.GetHeight()*1.0/pImageFaceImg.GetWidth()*1.0);
// 	} 
// 	else
// 	{
// 		tem_nNewHigh  = 500;
// 		tem_nNewWidth = (int)(tem_nNewHigh*pImageFaceImg.GetWidth()*1.0/pImageFaceImg.GetHeight()*1.0);
// 	}
// 	pImageFaceImg.Resample(tem_nNewWidth, tem_nNewHigh);
	pImageFaceImg.SetXDPI(200);
	pImageFaceImg.SetYDPI(200);

	tem_nOffsetX = 300;
	tem_nOffsetY = tem_nBackHeight - 1900;
	pImageMerge.MixFrom(pImageFaceImg, tem_nOffsetX, tem_nOffsetY);


	//��֤ʱ��+ǩ��-------------------------------------------------------------------------------
	CString  tem_strVerifyTime = _T("��֤ʱ�䣺");
	tem_strVerifyTime += m_strVerifyTime;
	pImageMerge.DrawString(0, 600, 1800, tem_strVerifyTime, rgbTEXT, _T("����"),40, 400, 0, 0, false);

	CString  tem_strSignate    = _T("�ͻ�ǩ�֣�");
	pImageMerge.DrawString(0, 600, 1900, tem_strSignate, rgbTEXT, _T("����"),40, 400, 0, 0, false);

	pImageMerge.Save(outimg, CXIMAGE_FORMAT_JPG);

	ShellExecute(NULL, _T("print"), outimg, NULL, NULL, SW_SHOWNORMAL);
	
}


BOOL CUDSCard::GernerateBarcode(const char* szText, int len , const char* szOutPath)
{
	
	struct zint_symbol* symbol;
	int ret = 0;
	
	try
	{
		symbol = ZBarcode_Create();
		if (symbol != NULL)
		{
			symbol->scale     = 4;
			symbol->option_1  = 1;                  //�ݴ���
			symbol->option_2  = 1;                  //�汾������ͼ���С
			symbol->symbology = BARCODE_QRCODE;
			symbol->output_options = 0;
			symbol->show_hrt  = 0;                   //����ʾ��Ϣ���������Ϊ1������Ҫ����textֵ
			symbol->input_mode= DATA_MODE;

			if (szOutPath)
			{
				memcpy(symbol->outfile, szOutPath, sizeof(symbol->outfile)-1);     //����ļ���
			}
			ret = ZBarcode_Encode(symbol, (unsigned char*)szText, len);            //����
			ret = ZBarcode_Print(symbol,0);                                        //antate angle ��ת�Ƕ�
			ZBarcode_Delete(symbol);  
			return TRUE;  
		}
	}
	catch (CException* e)
	{
		wchar_t szErr[256];  
		e->GetErrorMessage(szErr,255);  
		return FALSE;  

	}
	
	return TRUE;
}

