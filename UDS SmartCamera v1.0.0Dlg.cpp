
// UDS SmartCamera v1.0.0Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "opencv\cv.h"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\core\core.hpp"
#include "UDS SmartCamera v1.0.0.h"
#include "UDS SmartCamera v1.0.0Dlg.h"
#include "afxdialogex.h"


using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CString    g_strFrontImg;   //���֤����ͼ��·��
CString    g_strFaceImg;    //�ֳ�����ͼ��·��
CString    m_strDefaultPath;   //Ĭ��·��

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{  
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
//	afx_msg LRESULT OnSwitchItem(WPARAM wParam, LPARAM lParam);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_MESSAGE(WM_SWITCH, &CAboutDlg::OnSwitchItem)
END_MESSAGE_MAP()


// CUDSSmartCamerav100Dlg �Ի���




CUDSSmartCamerav100Dlg::CUDSSmartCamerav100Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSSmartCamerav100Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_staImageSize = _T("");
}

void CUDSSmartCamerav100Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SET, m_conTab);
	//-  DDX_Control(pDX, IDC_STA_OCXAREA, m_conStaFram);
	DDX_Control(pDX, IDC_UDS_VIDEOCTRL1, m_conVideoOcx);
	DDX_Control(pDX, IDC_LIST_IMAGE, m_conListCtrl);
	DDX_Control(pDX, IDC_BTN_CAPATURE, m_btnCapture);
	DDX_Control(pDX, IDC_BTN_CAPBAR, m_btnBar);
	//  DDX_Control(pDX, IDC_BTN_CAPGOON, m_btnZD);
	DDX_Control(pDX, IDC_BTN_CAP2SIDE, m_btnSides);
	DDX_Control(pDX, IDC_BTN_TEST2, m_btnExit);
	DDX_Control(pDX, IDC_BTN_BROWS, m_btnBrows);
	DDX_Control(pDX, IDC_BTN_CAPGOON, m_btnCapture2);
	DDX_Control(pDX, IDC_BTN_LROTATE, m_btnRotateL);
	DDX_Control(pDX, IDC_BTN_RROTATE, m_btnRotateR);
	DDX_Control(pDX, IDC_BTN_MIN, m_conMin);
	DDX_Control(pDX, IDC_BTN_WEB, m_conWeb);
	DDX_Control(pDX, IDC_BTN_SAVEPATH, m_btnSlcPath);
	DDX_Control(pDX, IDC_BTN_DECLEAR, m_btnMax);
	DDX_Control(pDX, IDC_BTN_READCARD, m_conCard);
	DDX_Text(pDX, IDC_STA_IMAGESIZE, m_staImageSize);
	DDX_Control(pDX, IDC_BTN_ZOOMIN, m_btnZoomIn);
	DDX_Control(pDX, IDC_BTN_ZOOMOUT, m_btnZoomOut);
	DDX_Control(pDX, IDC_BTN_RECOVER, m_btnRecovery);
	DDX_Control(pDX, IDC_BTN_CARDCOPY, m_btnCopyCard);
	DDX_Control(pDX, IDC_UDS_VIDEOCTRL1, m_conVideoOcx);
	DDX_Control(pDX, IDC_BTN_FACEID, m_btnCompare);
}

BEGIN_MESSAGE_MAP(CUDSSmartCamerav100Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SET, &CUDSSmartCamerav100Dlg::OnSelchangeTabSet)
	ON_BN_CLICKED(IDC_BTN_TEST2, &CUDSSmartCamerav100Dlg::OnBnClickedBtnTest2)
	ON_MESSAGE(WM_SWITCH, &CUDSSmartCamerav100Dlg::OnSwitchItem)
	ON_BN_CLICKED(IDC_BTN_CAPATURE, &CUDSSmartCamerav100Dlg::OnBnClickedBtnCapature)
	ON_WM_CLOSE()
ON_BN_CLICKED(IDC_BTN_LROTATE, &CUDSSmartCamerav100Dlg::OnBnClickedBtnLrotate)
ON_BN_CLICKED(IDC_BTN_RROTATE, &CUDSSmartCamerav100Dlg::OnBnClickedBtnRrotate)
ON_MESSAGE(WM_SUBSWITCH, &CUDSSmartCamerav100Dlg::OnSubswitch)
ON_MESSAGE(WM_ADVCESET, &CUDSSmartCamerav100Dlg::OnAdvceset)
ON_BN_CLICKED(IDC_BTN_CAPBAR, &CUDSSmartCamerav100Dlg::OnBnClickedBtnCapbar)
ON_BN_CLICKED(IDC_BTN_CAP2SIDE, &CUDSSmartCamerav100Dlg::OnBnClickedBtnCap2side)
ON_BN_CLICKED(IDC_BTN_CAPGOON, &CUDSSmartCamerav100Dlg::OnBnClickedBtnCapgoon)
ON_BN_CLICKED(IDC_BTN_BROWS, &CUDSSmartCamerav100Dlg::OnBnClickedBtnBrows)
ON_NOTIFY(NM_DBLCLK, IDC_LIST_IMAGE, &CUDSSmartCamerav100Dlg::OnDblclkListImage)
ON_STN_DBLCLK(IDC_STA_INFOPATH, &CUDSSmartCamerav100Dlg::OnDblclkStaInfopath)
ON_WM_CTLCOLOR()
ON_WM_ERASEBKGND()
ON_BN_CLICKED(IDC_BTN_MIN, &CUDSSmartCamerav100Dlg::OnBnClickedBtnMin)
ON_BN_CLICKED(IDC_BTN_WEB, &CUDSSmartCamerav100Dlg::OnBnClickedBtnWeb)
ON_BN_CLICKED(IDC_BTN_DECLEAR, &CUDSSmartCamerav100Dlg::OnBnClickedBtnDeclear)
ON_WM_NCHITTEST()
ON_WM_LBUTTONDOWN()
ON_BN_CLICKED(IDC_BTN_SAVEPATH, &CUDSSmartCamerav100Dlg::OnBnClickedBtnSavepath)
ON_NOTIFY(LVN_DELETEITEM, IDC_LIST_IMAGE, &CUDSSmartCamerav100Dlg::OnDeleteitemListImage)
ON_NOTIFY(NM_CLICK, IDC_LIST_IMAGE, &CUDSSmartCamerav100Dlg::OnClickListImage)
ON_NOTIFY(NM_RCLICK, IDC_LIST_IMAGE, &CUDSSmartCamerav100Dlg::OnRclickListImage)
ON_COMMAND(ID_32771, &CUDSSmartCamerav100Dlg::OnCopyIt)
ON_COMMAND(ID_32772, &CUDSSmartCamerav100Dlg::OnDeleteIt)
ON_COMMAND(ID_32773, &CUDSSmartCamerav100Dlg::OnRename)
ON_COMMAND(ID_32774, &CUDSSmartCamerav100Dlg::OnProperty)
ON_NOTIFY(NM_HOVER, IDC_LIST_IMAGE, &CUDSSmartCamerav100Dlg::OnHoverListImage)
ON_BN_CLICKED(IDC_BTN_READCARD, &CUDSSmartCamerav100Dlg::OnBnClickedBtnReadcard)
//ON_NOTIFY(HDN_ITEMCLICK, 0, &CUDSSmartCamerav100Dlg::OnItemclickListImage)
ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_LIST_IMAGE, &CUDSSmartCamerav100Dlg::OnBeginlabeleditListImage)
ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_IMAGE, &CUDSSmartCamerav100Dlg::OnEndlabeleditListImage)
ON_BN_CLICKED(IDC_BTN_ZOOMIN, &CUDSSmartCamerav100Dlg::OnBnClickedBtnZoomin)
ON_BN_CLICKED(IDC_BTN_ZOOMOUT, &CUDSSmartCamerav100Dlg::OnBnClickedBtnZoomout)
ON_BN_CLICKED(IDC_BTN_RECOVER, &CUDSSmartCamerav100Dlg::OnBnClickedBtnRecover)
ON_MESSAGE(WM_DEVICECHANGE, &CUDSSmartCamerav100Dlg::OnDevicechange)
ON_WM_SHOWWINDOW()
ON_BN_CLICKED(IDC_BTN_CARDCOPY, &CUDSSmartCamerav100Dlg::OnBnClickedBtnCardcopy)
ON_WM_MOVE()
ON_COMMAND(ID_32775, &CUDSSmartCamerav100Dlg::On32775Word)
ON_COMMAND(ID_32776, &CUDSSmartCamerav100Dlg::On32776Excel)
ON_COMMAND(ID_32777, &CUDSSmartCamerav100Dlg::On32777AutoRotate)
ON_BN_CLICKED(IDC_BTN_FACEID, &CUDSSmartCamerav100Dlg::OnBnClickedBtnFaceid)
ON_MESSAGE(WM_FACEID, &CUDSSmartCamerav100Dlg::OnFaceid)
ON_COMMAND(ID_32778, &CUDSSmartCamerav100Dlg::On32778RightRotateL)
ON_COMMAND(ID_32779, &CUDSSmartCamerav100Dlg::On32779RightRotateR)
END_MESSAGE_MAP()


// CUDSSmartCamerav100Dlg ��Ϣ�������

BOOL CUDSSmartCamerav100Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	/*****************************************************
	*
	* 1�� Tab�ؼ���ʼ��
	* 2�� OCX�ؼ���ʼ��
	* 3�� Ĭ��·������
	* 4�� ������ʼ��
	* 5�� ���ý����ʼ��
	* 6�� png��ť��ʼ��
	* 7�� ��ť������ʾ
	* 8�� ListCtrl��ʼ��
	* 9�� UI����
	* 10��Menu�˵���ʼ��
	* 11�����USB�ڵı䶯���
	*
    ******************************************************/

	//0��-------------------------------------------
	m_nImageCount      = 0;
	m_nNamingCount     = 1;
	m_nImageCountOther = 0;
//	m_nLastUsedScanner = 1;  //��ȡ�����ļ����Ը�ֵ���ò���
	m_nLastUsedResolu  = 0;
	m_nLastUsedFile    = 1;
	m_nLastUsedColor   = 2;
	m_strFileFormat    = ".jpg";
	m_nManualVaule     = 0;
	m_BAutoExp         = TRUE;
	m_BAutoCrop        = TRUE;
	m_BManualCrop      = FALSE;
	//DLL��OCX�ָ���---------------------------------
	m_lReturnCode  = 0;
	m_nLastSubScan = -1;   //��ȡ�����ļ���ͷ
	m_nLastSubRes  = 0;
	m_nRotate      = 0;
	m_nJpegQulity  = 50;
	m_nAutoSense   = 6;
	m_nVideoWidth  = 640;       //��Ƶ��
	m_nVideoHeight = 480;       //��Ƶ��
	m_nVideoBit    = 600;         //��Ƶ������
	m_nVideoFPS    = 24;         //��Ƶ֡��
	m_BPDFCpt      = FALSE;     //�������ļ���ȡʱע���ļ���ʽ��Ӧ
	m_BBase64Cpt   = FALSE;     //ͬ��
	m_BDcmCpt      = FALSE;     //DCM���գ���ʼ���ر�
	m_BOfdCpt      = FALSE;     //OFD����
	m_BMerge       = FALSE;
	m_nMergeMode   = 1;         //Ĭ���ڲ��ϲ�
	m_nMergeLocation = 3;       //Ĭ�����Ͻ�
	m_nNamingMode    = 0;       //Ĭ��0-˳�������� 1-ʱ�������� 2-ǰ׺����, 3-ǰ׺+ʱ������
	m_nThumbWidth    = 220;
	m_nThumbHeight   = 160;
	m_BShowInfo      = FALSE;
	m_strUrl         = "";
	m_nPDfimg        = 10001;
//	m_BDownBk        = GetSystemInfo();
	m_BDownBk        = TRUE;   //1027
	m_BFront         = TRUE;
	m_nSlctItem      = -1;
	m_BParentVideo   = TRUE;
	m_BMaxDlg        = TRUE;
	m_BSpaceDown     = TRUE;
	m_BCardDlg       = FALSE;
	m_strFrontName    = _T("");

	m_strHttp        = _T("");
    m_strFtpIP       = _T("");          
	m_strFtpDir      = _T("");        
	m_strFtpUserName = _T("");       
	m_strFtpPassWord = _T("");       
	m_strFtpPort     = _T("");       

	m_strCardName    = _T("");
	m_strCardSex     = _T("");
	m_strCardNation  = _T("");
	m_strCardBirth   = _T("");
	m_strCardAddress = _T("");
	m_strCardID      = _T("");
	m_strCardOffice  = _T("");
	m_strCardValidity= _T("");
	m_strVideoFormat = _T(".mp4");

	g_strFaceImg     = _T("");
	m_nOptBright     = 0;
	m_nOptContrast   = 20;

	m_BCamera200 = FALSE;
	m_BCamera500 = FALSE;
	m_BCamera800 = FALSE;
	m_BCamera1200= FALSE;
	m_BCamera1300= FALSE;
	m_BCameraTo1500 = FALSE;

	m_BAutoRotate = FALSE;
	m_BOptimize   = FALSE;
	
	m_strPID200 = _T("3420");
	m_strVID200 = _T("0AC8");

	m_strPID500  = _T("0524");
	m_strVID500  = _T("1B17");

// 	m_strPID500  = _T("B502");
// 	m_strVID500  = _T("04F2");

	m_strPID800  = _T("BC01");        //800W������
	m_strVID800  = _T("8001");

	m_strPID800GS= _T("10A4");       //GS1000,800->1000W
	m_strVID800GS= _T("1B17");

	m_strPID800b = _T("6366");        //800W����
	m_strVID800b = _T("0C45");

	m_strPID1200 = _T("0013");        //1000W�豸PID_VIDδ��
	m_strVID1200 = _T("0EDC");  

	m_strPID1300 = _T("150C");
	m_strVID1300 = _T("1B17");

	m_strPIDTo1500 = _T("0F10");
	m_strVIDTo1500 = _T("0AC8");

	m_BGS1600     = FALSE;
	m_strGS16_PID = _T("BC01");
	m_strGS16_VID = _T("1301");

	m_strPID800Un= _T("0800");       //δ֪����800->1000W, GS1000
	m_strVID800Un= _T("1B17"); 

	m_nInterpolateReso    = 0;
	m_nInterpolateSubReso = 0;
	
	m_nCardWidth = 674;    //����һ��ƫ������׼�ߴ�Ϊ647*426
	m_nCardHeight= 426;
	m_nA4Width   = 1580;
	m_nA4Height  = 2280;
	m_nSameCameraLast = 2;
	m_nAudioIndex     = 0;

	m_BSoundOpen = TRUE;
	m_BOcrOpened = FALSE;

 	m_fColorPercentage = 13.0;

//	m_iCard = new CCardReader();   //��ʼ�����֤������

	m_nScreenWidth  = GetSystemMetrics(SM_CXSCREEN);
	m_nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	//����GDI+----------------------------------------
	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_pGdiToken;
	GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL);

	//3��---------------------------------------------
// 	TCHAR        tem_tcFilepath[MAX_PATH+1] = {0};
// 	GetModuleFileName(NULL, tem_tcFilepath, MAX_PATH);
// 	(_tcsrchr(tem_tcFilepath, _T('\\')))[1] = 0;
// 
// 	m_strIniPath    = tem_tcFilepath;
// 	int tem_nDirIndex2 = m_strIniPath.ReverseFind('\\');
// 	m_strIniPath = m_strIniPath.Mid(0, tem_nDirIndex2);
// 
// 	tem_nDirIndex2 = m_strIniPath.ReverseFind('\\');
// 	m_strIniPath = m_strIniPath.Mid(0, tem_nDirIndex2+1);

	m_strIniPath   = GetMyDocument();
	m_strIniPath   += _T("\\");
	m_strIniPath   += _T("UDSData\\");

	//��������ͼ����Ŀ¼
	m_strBufferPath  = m_strIniPath;
	m_strBufferPath += _T("ScanBuffer");
	CFileFind    tem_fFileFind;
	if (!tem_fFileFind.FindFile(m_strBufferPath))
	{
		CreateDirectory(m_strBufferPath, NULL);
	}
	m_strBufferPath += _T("\\");

	m_strFingerDoc  = m_strIniPath;
	m_strFingerDoc += _T("���֤��Ϣ");
	m_strFaceDoc    = m_strFingerDoc;

	if (!tem_fFileFind.FindFile(m_strFingerDoc))
	{
		CreateDirectory(m_strFingerDoc, NULL);
	}
	m_strFingerDoc += _T("\\Finger");
	if (!tem_fFileFind.FindFile(m_strFingerDoc))
	{
		CreateDirectory(m_strFingerDoc, NULL);
	}
	m_strFingerDoc += _T("\\");

	m_strFaceDoc += _T("\\Face");
	if (!tem_fFileFind.FindFile(m_strFaceDoc))
	{
		CreateDirectory(m_strFaceDoc, NULL);
	}
	m_strFaceDoc += _T("\\");

	m_strIniPath   += _T("config.ini");   //�����ļ�·��

	
	LoadIniFile();

/*	//����������ļ���û�ж�ȡ��Ĭ�ϱ���·�������������ļ���
	m_strDefaultPath += "ScanBuffer";
	CFileFind    tem_fFileFind;
	if (!tem_fFileFind.FindFile(m_strDefaultPath))
	{
		CreateDirectory(m_strDefaultPath, NULL);
	}
	m_strDefaultPath += "\\";
*/
	
	
	//1��-------------------------------------------
	//����ѡ�����
	m_conTab.InsertItem(0, _T("��ͷ"));
	m_conTab.InsertItem(1, _T("��ͷ"));
	m_conTab.InsertItem(2, _T("�߼�"));

	//����Ĭ��ѡ�
	m_iChildNor.Create(IDD_DLG_CHILDNORMAL, GetDlgItem(IDC_TAB_SET));
	m_iChildAdv.Create(IDD_DLG_CHILDADV, GetDlgItem(IDC_TAB_SET));
	m_iChildSet.Create(IDD_DLG_SET, GetDlgItem(IDC_TAB_SET));

	//��ȡTab�ͻ�����С
	CRect   rcTab;
	m_conTab.GetClientRect(&rcTab);
	rcTab.top     += 22;  //�ϲ��������ȫ��ѱ�ǩ�����ǣ���������Tab�ؼ����ñ�ǩ��ɫ
// 	rcTab.left    += 3;   //���ҡ��²಻�����ȫ�����ñ���������°ױ�
// 	rcTab.right   -= 3;
// 	rcTab.bottom  -= 10;

	//�����Ի����С�ڸ������е�λ��
	m_iChildNor.MoveWindow(&rcTab);
	m_iChildAdv.MoveWindow(&rcTab);
	m_iChildSet.MoveWindow(&rcTab);

	////���ñ�ǩ���Ŀ��
	//int cx = (rcTab.right-rcTab.left-30)/3;
	//int cy = 40;
	//CSize   tem_sizeTab;
	//tem_sizeTab.cx = cx;
	//tem_sizeTab.cy = cy;
	//m_conTab.SetItemSize(tem_sizeTab);
	//CFont   tem_fontTab;
	//tem_fontTab.CreatePointFont(50, _T("����"));
	//m_conTab.SetFont(&tem_fontTab);
	//


	//����Ĭ����ʾ������
	m_iChildNor.ShowWindow(TRUE);
	m_iChildAdv.ShowWindow(FALSE);
	m_iChildSet.ShowWindow(FALSE);

	m_conTab.SetCurSel(0);

	//2��----------------------------------------------
	m_lReturnCode = m_conVideoOcx.Initial();
	if (m_lReturnCode != 0)
	{
		MessageBox(_T("�ؼ���ʼ��ʧ�ܣ�"), _T("��ͼUDS"), MB_OK);

//		::SendMessage(m_hWnd, WM_CLOSE, NULL, NULL);
		CDialog::OnOK();   //1027XPϵͳ�ϴ��ڴ��󣬽�sendmessage�޸�Ϊonok
		return FALSE;
	}
	m_straDeviceName.RemoveAll();
	int      tem_nDevCount = m_conVideoOcx.GetDeviceCount();//��ǰ�豸����
	m_nDeviceNumber = tem_nDevCount;
	if (tem_nDevCount>0)
	{
		for (int i=0; i<tem_nDevCount;i++)
		{
			CString tem_strDevName = m_conVideoOcx.GetDeviceName(i);
			tem_strDevName = CheckCameraName(tem_strDevName);
			m_iChildNor.m_conComScanner.InsertString(i, tem_strDevName);
			m_straDeviceName.Add(tem_strDevName);
		}

		m_vcCameraName.clear();

		//���ȴ���ͼ�豸����δ������ͼ�豸�򿪵��ϴ�ʹ���豸���豸
		std::vector<CString> tem_vcUDSCamera;
		tem_vcUDSCamera.push_back(_T("0524"));
		tem_vcUDSCamera.push_back(_T("BC01"));
		tem_vcUDSCamera.push_back(_T("6366"));
		tem_vcUDSCamera.push_back(_T("0013"));
		tem_vcUDSCamera.push_back(_T("150C"));
		tem_vcUDSCamera.push_back(_T("3370"));
		tem_vcUDSCamera.push_back(_T("0F10"));
		tem_vcUDSCamera.push_back(_T("BC01"));
		tem_vcUDSCamera.push_back(_T("0800"));
		tem_vcUDSCamera.push_back(_T("3420"));

		BOOL       tem_BFindUDS = FALSE;
		std::vector<CString>::iterator item;
		for (int i=0; i<tem_nDevCount; i++)
		{
			//��ȡÿ���豸��PID��VID��ƥ���Ƿ�Ϊ��ͼ�豸
			CString   tem_strPID = m_conVideoOcx.GetDevDisplayName(i);
			for (item =tem_vcUDSCamera.begin();item!=tem_vcUDSCamera.end(); item++)
			{
				if (tem_strPID.Find(*item)!=-1)
				{
					m_nLastUsedScanner = i;
					tem_BFindUDS = TRUE;
					break;
				}
			}
		}

        /*
        CString    tem_strUDSCamera[6] = {_T("0524"), _T("BC01"), _T("6366"), _T("0013"), _T("150C"), _T("3370")};
		BOOL       tem_BFindUDS = FALSE;
		for (int i=0; i<tem_nDevCount; i++)
		{
			//��ȡÿ���豸��PID��VID��ƥ���Ƿ�Ϊ��ͼ�豸
			CString   tem_strPID = m_conVideoOcx.GetDevDisplayName(i);
			for (int j=0; j<6; j++)
			{
				if (tem_strPID.Find(tem_strUDSCamera[j])!=-1)
				{
					m_nLastUsedScanner = i;
					tem_BFindUDS = TRUE;
					break;
				}
			}
		}
		*/

// 		if (!tem_BFindUDS)
// 		{
// 			m_nLastUsedScanner = 0;
// 		}

		m_nSameCameraLast = 2;

		m_iChildNor.m_conComScanner.SetCurSel(m_nLastUsedScanner);

		/*
		m_conVideoOcx.StartRun(1);
		m_conVideoOcx.StopRun();
		m_lReturnCode = m_conVideoOcx.StartRun(m_nLastUsedScanner);
		*/

		m_lReturnCode = m_conVideoOcx.StartRun(m_nLastUsedScanner);         //��������ͷ

		m_conVideoOcx.RotatedVideo(m_nRotate);
		m_nMainOpen = m_lReturnCode;
		

		//�鿴�򿪵��豸�Ƿ�Ϊָ���豸----------------------------------------------
		CString   tem_strPIDVID = _T("");
		int       tem_nPID200   = -1;
		int       tem_nVID200   = -1;
		int       tem_nPID500   = -1;
		int       tem_nVID500   = -1;
		int       tem_nPID800   = -1;
		int       tem_nVID800   = -1;
		int       tem_nPID800GS = -1;
		int       tem_nVID800GS = -1;
		int       tem_nPID800b  = -1;
		int       tem_nVID800b  = -1;
		int       tem_nPID1200  = -1;
		int       tem_nVID1200  = -1;
		int       tem_nPID1300  = -1;
		int       tem_nVID1300  = -1;
		int       tem_nPIDTo1500 = -1;
		int       tem_nVIDTo1500 = -1;
		int       tem_nGS16_PID  = -1;
		int       tem_nGS16_VID  = -1;
		int       tem_nPID800Un = -1;
		int       tem_nVID800Un = -1;
		if (m_lReturnCode == 0)
		{
			//�豸�򿪳ɹ������Ȼ�ȡ�豸PID_VID
			tem_strPIDVID = m_conVideoOcx.GetDevDisplayName(m_nLastUsedScanner);
			//����PID_VID�Ƿ�Ϊָ�����豸
			tem_strPIDVID.MakeUpper();

			tem_nPID200 = tem_strPIDVID.Find(m_strPID200);
			tem_nVID200 = tem_strPIDVID.Find(m_strVID200);
			tem_nPID500 = tem_strPIDVID.Find(m_strPID500);
			tem_nVID500 = tem_strPIDVID.Find(m_strVID500);
			tem_nPID800 = tem_strPIDVID.Find(m_strPID800);
			tem_nVID800 = tem_strPIDVID.Find(m_strVID800);
			tem_nPID800GS = tem_strPIDVID.Find(m_strPID800GS);
			tem_nVID800GS = tem_strPIDVID.Find(m_strVID800GS);
			tem_nPID800b= tem_strPIDVID.Find(m_strPID800b);
			tem_nVID800b= tem_strPIDVID.Find(m_strVID800b);
			tem_nPID1200= tem_strPIDVID.Find(m_strPID1200);
			tem_nVID1200= tem_strPIDVID.Find(m_strVID1200);
			tem_nPID1300= tem_strPIDVID.Find(m_strPID1300);
			tem_nVID1300= tem_strPIDVID.Find(m_strVID1300);
			tem_nPIDTo1500 = tem_strPIDVID.Find(m_strPIDTo1500);
			tem_nVIDTo1500 = tem_strPIDVID.Find(m_strVIDTo1500);
			tem_nGS16_PID  = tem_strPIDVID.Find(m_strGS16_PID);
			tem_nGS16_VID  = tem_strPIDVID.Find(m_strGS16_VID);
			tem_nPID800Un = tem_strPIDVID.Find(m_strPID800Un);
			tem_nVID800Un = tem_strPIDVID.Find(m_strVID800Un);
			CString   tem_strResolution = _T("");

			if ((tem_nPID800!=-1 && tem_nVID800!=-1) || (tem_nPID800b!=-1 && tem_nVID800b!=-1) || (tem_nPID800GS!=-1 && tem_nVID800GS!=-1) || 
				(tem_nPID800Un!=-1 && tem_nVID800Un!=-1))
			{
				//���豸Ϊָ���豸�����ָ���ֱ���
				//800W->1000W
				m_BCamera800 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{
					
					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("3664��2744");
				m_iChildNor.m_conComReso.InsertString(-1, tem_strResolution);

				//������õ�ǰ�ֱ������������ܸ�����˵���÷ֱ���Ϊ��ֵ�ֱ��ʣ�Ӧ����ΪӲ�����ֱ���
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//�ҳ����ֱ��ʶ�Ӧ����
					int  tem_nMaxIndex = GetmaxResoindex();

					m_conVideoOcx.SetResolution(tem_nMaxIndex);
				}
				else
				{
					m_conVideoOcx.SetResolution(m_nLastUsedResolu);
				}
				
			}
			else if (tem_nPID500!=-1 && tem_nVID500!=-1)
			{
				//500W->1000W
				m_BCamera500 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("3664*2744");
				m_iChildNor.m_conComReso.InsertString(-1, tem_strResolution);

				//������õ�ǰ�ֱ������������ܸ�����˵���÷ֱ���Ϊ��ֵ�ֱ��ʣ�Ӧ����ΪӲ�����ֱ���
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//�ҳ����ֱ��ʶ�Ӧ����
					int  tem_nMaxIndex = GetmaxResoindex(); 
					m_conVideoOcx.SetResolution(tem_nMaxIndex);
				}
				else
				{
					m_conVideoOcx.SetResolution(m_nLastUsedResolu);
				}

			}
 			else if (tem_nPID1200!=-1 && tem_nVID1200!=-1)
 			{
 				//1200W->1600W
 				m_BCamera1200 = TRUE;
 				int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
				m_nInterpolateReso   = tem_nResCount;
 				for (int i=0; i<tem_nResCount; i++)
 				{
 
 					tem_strResolution = m_conVideoOcx.GetResolution(i);
 					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
 				}
 				tem_strResolution = _T("4680��3510");
 				m_iChildNor.m_conComReso.InsertString(-1, tem_strResolution);
 
 				//������õ�ǰ�ֱ������������ܸ�����˵���÷ֱ���Ϊ��ֵ�ֱ��ʣ�Ӧ����ΪӲ�����ֱ���
 				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
 				if (m_nLastUsedResolu == m_nInterpolateReso)
 				{
 					//�ҳ����ֱ��ʶ�Ӧ����
 					int  tem_nMaxIndex = GetmaxResoindex(); 
 					m_conVideoOcx.SetResolution(tem_nMaxIndex);
 				}
 				else
 				{
 					m_conVideoOcx.SetResolution(m_nLastUsedResolu);
 				}
 
 			}
			else if (tem_nPID1300!=-1 && tem_nVID1300!=-1)
			{
				//1300W------------------------------------------------1010
				m_BCamera1300 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("4480��3360");
				m_iChildNor.m_conComReso.InsertString(-1, tem_strResolution);

				//������õ�ǰ�ֱ������������ܸ�����˵���÷ֱ���Ϊ��ֵ�ֱ��ʣ�Ӧ����ΪӲ�����ֱ���
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
				CString    tem_strCurRes;
				int        tem_nFindIndex;
				CString    tem_strFirst;
				CString    tem_strLast;
				int        tem_nFirst;
				int        tem_nLast;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//�ҳ����ֱ��ʶ�Ӧ����
// 					int  tem_nMaxIndex = GetmaxResoindex(); 
// 					m_conVideoOcx.SetResolution(tem_nMaxIndex);
					//��õڶ���ֱ���
					int  tem_nMaxIndex = GetDiyResoindex(1);
					if (tem_nMaxIndex<0 ||tem_nMaxIndex>13)
					{
						m_conVideoOcx.SetResolution(9);
					}
					else
					{
						m_conVideoOcx.SetResolution(tem_nMaxIndex);
					}
					m_conVideoOcx.SetDisPlayInfo(4480, 3360, 0);					
				}
				else
				{
					m_conVideoOcx.SetResolution(m_nLastUsedResolu);
					tem_strCurRes = m_conVideoOcx.GetResolution(m_nLastUsedResolu);
					tem_nFindIndex = tem_strCurRes.Find('*');

					tem_strFirst = tem_strCurRes;
					tem_strLast  = tem_strCurRes;
					tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
					tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
					tem_nFirst   = _ttoi(tem_strFirst);
					tem_nLast    = _ttoi(tem_strLast);

					if (tem_nFirst<1000)
					{
//						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 30);
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}
					else if (tem_nFirst<2000 && tem_nFirst>=1000)
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}
					else
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}
				}

			}
			else if (tem_nPIDTo1500!=-1 && tem_nVIDTo1500!=-1)
			{
				//��ֵ��1500W------------------------------------------------1010
				m_BCameraTo1500 = TRUE;
				
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("4480��3360");
				m_iChildNor.m_conComReso.InsertString(-1, tem_strResolution);

				//������õ�ǰ�ֱ������������ܸ�����˵���÷ֱ���Ϊ��ֵ�ֱ��ʣ�Ӧ����ΪӲ�����ֱ���
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
				CString    tem_strCurRes;
				int        tem_nFindIndex;
				CString    tem_strFirst;
				CString    tem_strLast;
				int        tem_nFirst;
				int        tem_nLast;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//�ҳ����ֱ��ʶ�Ӧ����
//					int  tem_nMaxIndex = GetmaxResoindex(); 
//					m_conVideoOcx.SetResolution(tem_nMaxIndex);
					//��ȡ�ڶ���ֱ���
					int  tem_nMaxIndex = GetDiyResoindex(1);
					m_conVideoOcx.SetResolution(tem_nMaxIndex);
					m_conVideoOcx.SetDisPlayInfo(4480, 3360, 0);
				}
				else
				{
					m_conVideoOcx.SetResolution(m_nLastUsedResolu);

					
					tem_strCurRes = m_conVideoOcx.GetResolution(m_nLastUsedResolu);
					tem_nFindIndex = tem_strCurRes.Find('*');

					tem_strFirst = tem_strCurRes;
					tem_strLast  = tem_strCurRes;
					tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
					tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
					tem_nFirst   = _ttoi(tem_strFirst);
					tem_nLast    = _ttoi(tem_strLast);
				
					if (tem_nFirst<1000)
					{
//						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 30);
						m_conVideoOcx.SetDisPlayInfo(0, 0, 0);
					}
					else if (tem_nFirst<2000 && tem_nFirst>=1000)
					{
						m_conVideoOcx.SetDisPlayInfo(0, 0, 0);
					}
					else
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}	
				}
				
			}
			else if (tem_nGS16_PID!=-1 && tem_nGS16_VID!=-1)
			{
				//GS1600 1300W->1600W-------------------------------------------0126
				m_BGS1600 = TRUE;

				int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("4928��3264");
				m_iChildNor.m_conComReso.InsertString(-1, tem_strResolution);

				//������õ�ǰ�ֱ������������ܸ�����˵���÷ֱ���Ϊ��ֵ�ֱ��ʣ�Ӧ����ΪӲ�����ֱ���
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
				CString    tem_strCurRes;
				int        tem_nFindIndex;
				CString    tem_strFirst;
				CString    tem_strLast;
				int        tem_nFirst;
				int        tem_nLast;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//��ȡ���ֱ�������
					int  tem_nMaxIndex = GetDiyResoindex(1);
					m_conVideoOcx.SetResolution(tem_nMaxIndex);
					m_conVideoOcx.SetDisPlayInfo(4928, 3264, 0);
				}
				else
				{
					m_conVideoOcx.SetResolution(m_nLastUsedResolu);


					tem_strCurRes = m_conVideoOcx.GetResolution(m_nLastUsedResolu);
					tem_nFindIndex = tem_strCurRes.Find('*');

					tem_strFirst = tem_strCurRes;
					tem_strLast  = tem_strCurRes;
					tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
					tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
					tem_nFirst   = _ttoi(tem_strFirst);
					tem_nLast    = _ttoi(tem_strLast);

					if (tem_nFirst<1000)
					{
						//						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 30);
						m_conVideoOcx.SetDisPlayInfo(0, 0, 0);
					}
					else if (tem_nFirst<2000 && tem_nFirst>=1000)
					{
						m_conVideoOcx.SetDisPlayInfo(0, 0, 0);
					}
					else
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}	
				}

			}
			else if (tem_nPID200!=-1 && tem_nVID200!=-1)
			{
				//��ͷ 200W->300W-------------------------------------------0126
				m_BCamera200 = TRUE;

				int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{
					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("2048��1536");
				m_iChildNor.m_conComReso.InsertString(-1, tem_strResolution);

				//������õ�ǰ�ֱ������������ܸ�����˵���÷ֱ���Ϊ��ֵ�ֱ��ʣ�Ӧ����ΪӲ�����ֱ���
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
				CString    tem_strCurRes;
				int        tem_nFindIndex;
				CString    tem_strFirst;
				CString    tem_strLast;
				int        tem_nFirst;
				int        tem_nLast;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//��ȡ���ֱ�������
					int  tem_nMaxIndex = GetDiyResoindex(1);
					m_conVideoOcx.SetResolution(tem_nMaxIndex);
					m_conVideoOcx.SetDisPlayInfo(2048, 1536, 0);
				}
				else
				{
					m_conVideoOcx.SetResolution(m_nLastUsedResolu);


					tem_strCurRes = m_conVideoOcx.GetResolution(m_nLastUsedResolu);
					tem_nFindIndex = tem_strCurRes.Find('*');

					tem_strFirst = tem_strCurRes;
					tem_strLast  = tem_strCurRes;
					tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
					tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
					tem_nFirst   = _ttoi(tem_strFirst);
					tem_nLast    = _ttoi(tem_strLast);

					if (tem_nFirst<1000)
					{
						m_conVideoOcx.SetDisPlayInfo(0, 0, 0);
					}
					else if (tem_nFirst<2000 && tem_nFirst>=1000)
					{
						m_conVideoOcx.SetDisPlayInfo(0, 0, 0);
					}
					else
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}	
				}
			}
			else
			{
				//���豸Ϊ��ͨ�豸
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
				for (int i=0; i<tem_nResCount; i++)
				{
					tem_strResolution = m_conVideoOcx.GetResolution(i);
					if (tem_strResolution==_T("640*480"))
					{
						tem_strResolution += _T("(VGA)");
					}
					else if (tem_strResolution == _T("352*288"))
					{
						tem_strResolution += _T("(CIF)");
					}
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
				m_conVideoOcx.SetResolution(m_nLastUsedResolu);
			}


			//-------------------------------------------------------------------------------
			m_conVideoOcx.SetColorMode(m_nLastUsedColor);	
			//��ȡ�عⷶΧ
			//Ĭ�Ͽ����Զ��ع�
			m_iChildNor.m_conStaExpStr = _T("");   
			long tem_lExmin = 0, tem_lExmax = 0, tem_lAutoExp = 0, tem_lValue = 0;
			m_lReturnCode = m_conVideoOcx.GetExposureRange(&tem_lExmin, &tem_lExmax);
			//	m_conVideoOcx.SetAutoExposure(m_BAutoExp);   //����Ĭ���Զ��ع�ini��ͨ���ò����޸�
			if (m_lReturnCode == 0)
			{
				 
				m_iChildNor.m_conSlidExpos.SetRange(tem_lExmin, tem_lExmax); //����slider��Χ
				m_iChildNor.m_conSlidExpos.SetPageSize(1);
				m_conVideoOcx.GetExposure(&tem_lValue, &tem_lAutoExp);
				UpdateData(TRUE);
				m_iChildNor.m_conSlidExpos.SetPos(tem_lValue);       //����slider��ǰֵ
				m_iChildNor.m_conStaExp = tem_lValue;                //����slider��ʾ��ǰֵ
				m_iChildNor.m_conStaExpStr.Format(_T("%d"), m_iChildNor.m_conStaExp);
				m_iChildNor.m_conSlidExpos.EnableWindow(FALSE);	
				UpdateData(FALSE);	
			}

			if (m_BAutoExp)
			{
				m_conVideoOcx.SetAutoExposure(TRUE);
			} 
			else 
			{
				if (m_nManualVaule>=tem_lExmin && m_nManualVaule<=tem_lExmax)
				{
					m_conVideoOcx.SetAutoExposure(FALSE);
					m_conVideoOcx.SetExposure(m_nManualVaule, FALSE);
				} 
				else
				{
					m_conVideoOcx.SetAutoExposure(FALSE);
					m_conVideoOcx.SetExposure(0, FALSE);
				}	
			}
			
			//������ת����


			//��ȡ���ȷ�Χ
			//����Ĭ������
			long   tem_lBrightMax = 0, tem_lBrightMin = 0, tem_lAutoBrg = 0, tem_lValueBrg = 0;
			m_lReturnCode = m_conVideoOcx.GetBrightnessRange(&tem_lBrightMin, &tem_lBrightMax);
			if (m_lReturnCode == 0)
			{
				//���ù�����
				m_iChildNor.m_conSlidBright.SetRange(tem_lBrightMin, tem_lBrightMax);   //����slider��Χ
				m_iChildNor.m_conSlidBright.SetPageSize(1);
				m_conVideoOcx.GetBrightness(&tem_lValueBrg, &tem_lAutoBrg);
				UpdateData(TRUE);
				m_iChildNor.m_conSlidBright.SetPos(tem_lValueBrg);
				m_iChildNor.m_conStaBrg = tem_lValueBrg;
				UpdateData(FALSE);
				m_iChildNor.m_conSlidBright.EnableWindow(TRUE);
				if (m_nBriValue>=tem_lBrightMin && m_nBriValue<=tem_lBrightMax)
				{
					m_conVideoOcx.SetBrightness(m_nBriValue, FALSE);
				} 
				else
				{
					m_conVideoOcx.SetBrightness(0, FALSE);
				}	
			}
			
//			m_conVideoOcx.SetAutoExposure(m_BAutoExp);   //����Ĭ���Զ��ع�ini��ͨ���ò����޸�
//			m_conVideoOcx.SetAutoExposure(TRUE);   //����Ĭ���Զ��ع�ini��ͨ���ò����޸�
			
			m_conVideoOcx.AdjuestImageCrop(m_BAutoCrop);  //Ĭ�Ͽ�ʼ�Զ�����,ini��ͨ���ò����޸�
			if (!m_BAutoCrop)
			{
				m_conVideoOcx.ManualImageCrop(m_BManualCrop);
			}
			m_conVideoOcx.SetJpegQuality(m_nJpegQulity);  //����Ĭ��JPEG����
			m_conVideoOcx.SetAutomaticSensitiveness(m_nAutoSense);  //�����Զ����ĵ�������
		}
		else
		{
			MessageBox(_T("δ����ָ���豸��"), _T("��ͼUDS"), MB_OK);
		}
	}
	else
	{
		m_conVideoOcx.Uninitial();
		MessageBox(_T("δ�ҵ������豸��"), _T("��ͼUDS"), MB_OK);
		::SendMessage(m_hWnd, WM_CLOSE, NULL, NULL);
	}
	
	//4��-------------------------------------------------------------------------
	GetDlgItem(IDC_STA_INFOPATH)->SetWindowText(m_strShowPath);
	GetDlgItem(IDC_STA_NUMBER)->SetWindowText(_T("0"));

	//5��-------------------------------------------------------------------------
	m_conVideoOcx.ShowVideoInfo(m_BShowInfo);     //��Ƶ��Ϣ
	m_conVideoOcx.SetJpegQuality(m_nJpegQulity);  //ͼ������
	m_conVideoOcx.SetAutomaticSensitiveness(m_nAutoSense);//����������

	//5.5��Ƶ�豸��ʼ��-----------------------------------------------------------
	//��ȡ��Ƶ�豸�б�
	int tem_nAudioCount = m_conVideoOcx.GetAudioDevCount();
	for(int i=0; i<tem_nAudioCount; i++)
	{
		CString tem_strAudioName = m_conVideoOcx.GetAudioDevName(i);
		m_iChildNor.m_conAudio.InsertString(i, tem_strAudioName);
	}
	//����Ĭ���豸
	m_iChildNor.m_conAudio.SetCurSel(0);




	//6��-----------------------------------------------------------------------
//	CImage  m_imgBK;
	LoadPicture(Image, IDB_PNG_BK);   //ʹ��PngButton���ر���
	m_btnCapture.Init(IDB_PNG_CAPTURE, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_btnBar.Init(IDB_PNG_BAR, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_btnSides.Init(IDB_PNG_HB, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_btnExit.Init(IDB_PNG_TC, BTN_IMG_1, BTN_TYPE_NORMAL);
	m_btnBrows.Init(IDB_PNG_BRO, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_btnCapture2.Init(IDB_PNG_LP, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_conCard.Init(IDB_PNG_CARD, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_btnRotateL.Init(IDB_PNG_ZX, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_btnRotateR.Init(IDB_PNG_YX, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_conMin.Init(IDB_PNG_MIN, BTN_IMG_1, BTN_TYPE_NORMAL);
	m_conWeb.Init(IDB_PNG_WEB, BTN_IMG_1, BTN_TYPE_NORMAL);
	m_btnSlcPath.Init(IDB_PNG_SLCPATH, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_btnMax.Init(IDB_PNG_MAX, BTN_IMG_1, BTN_TYPE_NORMAL);
	m_btnZoomIn.Init(IDB_PNG_ZOOMIN, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_btnZoomOut.Init(IDB_PNG_ZOOMOUT, BTN_IMG_4, BTN_TYPE_NORMAL);
	m_btnRecovery.Init(IDB_PNG_RECOVER, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_btnCopyCard.Init(IDB_PNG_COPYCARD, BTN_IMG_3, BTN_TYPE_NORMAL);
	m_btnCompare.Init(IDB_PNG_COMPARE, BTN_IMG_3, BTN_TYPE_NORMAL);

	//7��-------------------------------------------------------------------------
	m_tipInfo.Create(this);
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_CAPATURE), _T("��ͷ����"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_CAPBAR), _T("������������"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_CAPGOON), _T("�Զ�����"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_CAP2SIDE), _T("������ϲ�����"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_BROWS), _T("�򿪱���Ŀ¼"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_TEST2), _T("�˳�"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_DECLEAR), _T("���"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_MIN), _T("��С��"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_SAVEPATH), _T("ѡ�񱣴�Ŀ¼"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_LROTATE), _T("Ԥ������"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_RROTATE), _T("Ԥ������"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_READCARD), _T("���֤����"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_ZOOMIN), _T("Ԥ���Ŵ�"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_ZOOMOUT), _T("Ԥ����С"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_RECOVER), _T("Ԥ���ʺ�"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_CARDCOPY), _T("���֤��ӡ"));
	
	m_tipInfo.SetDelayTime(TTDT_INITIAL, 100);    //�������������ʾʱ��
	m_tipInfo.SetDelayTime(TTDT_AUTOPOP, 5000);   //������ʾʱ��
	m_tipInfo.SetDelayTime(TTDT_RESHOW, 100);     //�����л���ťʱ���ʱ��
	m_tipInfo.SetTipTextColor(RGB(255, 255, 255));//����������ɫ
	m_tipInfo.SetTipBkColor(RGB(0, 0, 0));//������ʾ�򱳾���ɫ
	m_tipInfo.Activate(TRUE); //������ʾ����

	GetDlgItem(IDC_BTN_ZOOMOUT)->EnableWindow(FALSE);

	//8��-------------------------------------------------------------------------
	m_conListCtrl.SetBkColor(RGB(72,77,91));

	//9��-------------------------------------------------------------------------
	//Static�ؼ�����
//	SetWindowTheme(GetDlgItem(IDC_STA_GRP_SM)->GetSafeHwnd(), L"", L"");

	//Tab�ؼ�����


	//��ӱ���

	//10��-------------------------------------------------------------------------
	CreateHSMenu();
	CDialogEx::SetBackgroundColor(RGB(72,77,91));

	//ͼ��ߴ�
	GetDlgItem(IDC_STA_IMAGESIZE)->GetWindowRect(&m_rcImageSize); 
	ScreenToClient(&m_rcImageSize); //ת���ͻ��˽���
	GetDlgItem(IDC_STA_IMAGESIZE)->SetWindowText(_T("ͼ���С:"));

	//11��-------------------------------------------------------------------------
	static const GUID GUID_DEVINTERFACE_LIST[] ={0xA5DCBF10, 0x6530, 0x11D2, {0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED}};
	HDEVNOTIFY                      hDevNotify;  
	DEV_BROADCAST_DEVICEINTERFACE   NotificationFilter;  
	ZeroMemory(&NotificationFilter, sizeof(NotificationFilter));  
	NotificationFilter.dbcc_size       = sizeof(DEV_BROADCAST_DEVICEINTERFACE);  
	NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;  

	for(int i=0; i<sizeof(GUID_DEVINTERFACE_LIST)/sizeof(GUID); i++)   
	{  
		NotificationFilter.dbcc_classguid = GUID_DEVINTERFACE_LIST[i];  
		hDevNotify = RegisterDeviceNotification(this->GetSafeHwnd(), &NotificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE);  
		if( !hDevNotify )   
		{  
			AfxMessageBox(CString("Can't register device notification: ")   
				+ _com_error(GetLastError()).ErrorMessage(), MB_ICONEXCLAMATION);  
			return FALSE;  
		}  
	}  
	
	OnBnClickedBtnDeclear();    //�������
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


void CUDSSmartCamerav100Dlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: �ڴ˴������Ϣ����������
	//���ñ�ǩ���Ŀ��
	CRect  tem_rcTab;
	m_conTab.GetWindowRect(&tem_rcTab);
	ScreenToClient(&tem_rcTab);

	CSize  tem_szTab;
	tem_szTab.cx = (tem_rcTab.Width()-30)/3;
	tem_szTab.cy = 20;
	m_conTab.SetItemSize(tem_szTab);
}


void CUDSSmartCamerav100Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUDSSmartCamerav100Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (m_BDownBk)
		{
			/*����һ��CImage�����Pngͼ�񣬵���Ӱ���˰�ť�ؼ���״̬��ʾ
			//����ͼ�񱳾�
			
			CDC *pDC = GetDC();		
			Image.Load(_T("res\\BK.png"));
//			Image.LoadFromResource(AfxGetInstanceHandle(), IDB_PNG_BK);
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
			m_BDownBk = FALSE;
			*/


			//��������ʹ��PngButton::LoadPicture���ر���
			
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

			if (!Image.IsNull())
			{
				CRect rcImg = CRect(0, 0, Image.GetWidth(), Image.GetHeight());
				Image.Draw(dcMem.m_hDC, rcImg, rcImg);
			}

			pDC->BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &dcMem, 0, 0, SRCCOPY);
			//		pDC->StretchBlt(0, 0, rcClient.Width(), rcClient.Height(), &dcMem,0,0, 1100,700,SRCCOPY);
			memBitmap.DeleteObject();
			

		}
//		CDialogEx::OnPaint();
	}
}


BOOL CUDSSmartCamerav100Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CDialogEx::OnEraseBkgnd(pDC);
}


HBRUSH CUDSSmartCamerav100Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO:  �ڴ˸��� DC ���κ�����
	//Statci�ؼ�����
	if (pWnd->GetDlgCtrlID() == IDC_STA_NUMCOUNT || pWnd->GetDlgCtrlID()==IDC_STA_NUMBER || pWnd->GetDlgCtrlID()==IDC_STA_PAGE ||
		pWnd->GetDlgCtrlID()==IDC_STA_NOWPATH || pWnd->GetDlgCtrlID()==IDC_STA_INFOPATH ||pWnd->GetDlgCtrlID()==IDC_STA_IMAGESIZE)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
//		pDC->SetTextColor(RGB(246, 246, 11));
		pDC->SetTextColor(RGB(255, 255, 255));
		CFont   tem_Font;
		tem_Font.CreatePointFont(100, _T("����"));
		pDC->SelectObject(&tem_Font);
	}
	else if (pWnd->GetDlgCtrlID()==IDC_STA_BIAOTI)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
//		pDC->SetTextColor(RGB(174, 174, 175));
		pDC->SetTextColor(RGB(255, 255, 255));
		CFont   tem_FontSta;
		tem_FontSta.CreatePointFont(250, _T("����"));
//		tem_FontSta.CreateFont(40, 30, 0, 0, FW_BOLD, TRUE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_SWISS, _T("����"));
		pDC->SelectObject(&tem_FontSta);
	}
// 	if (pWnd->GetDlgCtrlID()==IDC_STA_GRP_SM)
// 	{
// 		pDC->SetTextColor(RGB(255, 255, 255));//�����ɫ
// 		hbr = CreateSolidBrush(RGB(0, 0, 0));//������ɫ
// 		
// 	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	
	return hbr;
}


//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CUDSSmartCamerav100Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUDSSmartCamerav100Dlg::LoadIniFile(void)
{
	int        tem_nRead   = 0;
	CString    tem_strRead = _T("");

	//��ͷ�������--------------------
	::GetPrivateProfileString(_T("ParentCamera"), _T("LastUsed"), _T("û���ҵ���ͷLastUsed��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastUsedScanner = tem_nRead;

	::GetPrivateProfileString(_T("ParentCamera"), _T("Resolution"), _T("û���ҵ�Resolution��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastUsedResolu = tem_nRead;

	::GetPrivateProfileString(_T("ParentCamera"), _T("FileMode"), _T("û���ҵ�FileMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_strRead.ReleaseBuffer();
	tem_nRead = _ttoi(tem_strRead);
	switch(tem_nRead)
	{
	case 0:
		m_nLastUsedFile = tem_nRead;
		m_strFileFormat = ".bmp";
		m_BPDFCpt       = FALSE;
		m_BBase64Cpt    = FALSE;
		m_BDcmCpt       = FALSE;
		m_BOfdCpt       = FALSE;
		break;
	case 1:
		m_nLastUsedFile = tem_nRead;
		m_strFileFormat = ".jpg";
		m_BPDFCpt       = FALSE;
		m_BBase64Cpt    = FALSE;
		m_BDcmCpt       = FALSE;
		m_BOfdCpt       = FALSE;
		break;
	case 2:
		m_nLastUsedFile = tem_nRead;
		m_strFileFormat = ".tif";
		m_BPDFCpt       = FALSE;
		m_BBase64Cpt    = FALSE;
		m_BDcmCpt       = FALSE;
		m_BOfdCpt       = FALSE;
		break;
	case 3:
		m_nLastUsedFile = tem_nRead;
		m_strFileFormat = ".png";
		m_BPDFCpt       = FALSE;
		m_BBase64Cpt    = FALSE;
		m_BDcmCpt       = FALSE;
		m_BOfdCpt       = FALSE;
		break;
	case 4:
		m_nLastUsedFile = tem_nRead;
		m_strFileFormat = ".pdf";
		m_BPDFCpt       = TRUE;
		m_BBase64Cpt    = FALSE;
		m_BDcmCpt       = FALSE;
		m_BOfdCpt       = FALSE;
		break;
	case 5:
		m_nLastUsedFile = tem_nRead;
		m_strFileFormat = ".txt";
		m_BPDFCpt       = FALSE;
		m_BBase64Cpt    = TRUE;
		m_BDcmCpt       = FALSE;
		m_BOfdCpt       = FALSE;
		break;
	case 6:
		m_nLastUsedFile = tem_nRead;
		m_strFileFormat = ".dcm";
		m_BPDFCpt       = FALSE;
		m_BBase64Cpt    = FALSE;
		m_BDcmCpt       = TRUE;
		m_BOfdCpt       = FALSE;
		break; 
	case 7:
		m_nLastUsedFile = tem_nRead;
		m_strFileFormat = ".ofd";
		m_BPDFCpt       = FALSE;
		m_BBase64Cpt    = FALSE;
		m_BDcmCpt       = FALSE;
		m_BOfdCpt       = TRUE;
		break;
	default:
		m_nLastUsedFile = 1;
		m_strFileFormat    = ".jpg";
		m_BPDFCpt       = FALSE;
		m_BBase64Cpt    = FALSE;
		m_BDcmCpt       = FALSE;
		m_BOfdCpt       = FALSE;
		break;
	}	

	::GetPrivateProfileString(_T("ParentCamera"), _T("ColorMode"), _T("û���ҵ�ColorMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
	if (tem_nRead>=0 && tem_nRead<3)
	{
		m_nLastUsedColor = tem_nRead;
	} 
	else
	{
		m_nLastUsedColor = 2;
	}
	
	::GetPrivateProfileString(_T("ParentCamera"), _T("AutoCrop"), _T("û���ҵ�AutoCrop��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	switch(tem_nRead)
	{
	case 0:
		m_BAutoCrop        = FALSE;
		m_BManualCrop      = TRUE;
		break;
	case 1:
		m_BAutoCrop        = TRUE;
		m_BManualCrop      = FALSE;
		break;
	default:
		m_BAutoCrop        = TRUE;
		m_BManualCrop      = FALSE;
		break;
	}

	::GetPrivateProfileString(_T("ParentCamera"), _T("AutoExp"), _T("û���ҵ�AutoExp��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	switch(tem_nRead)
	{
	case 0:
		m_BAutoExp         = FALSE;
		break;
	case 1:
		m_BAutoExp         = TRUE;
		break;
	default:
		m_BAutoExp         = TRUE;
		break;
	}
	m_BAutoExp   = TRUE;

	//0112
	::GetPrivateProfileString(_T("ParentCamera"), _T("VideoRotate"), _T("û���ҵ�VideoRotate��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nRotate = tem_nRead;


	::GetPrivateProfileString(_T("ParentCamera"), _T("ExpValue"), _T("û���ҵ�ExpValue��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
	m_nManualVaule = tem_nRead;

	::GetPrivateProfileString(_T("ParentCamera"), _T("BriValue"), _T("û���ҵ�BriValue��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
	m_nBriValue = tem_nRead;

	::GetPrivateProfileString(_T("Resource"), _T("AutoRotate"), _T("û���ҵ�AutoRotate��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
	if (tem_nRead==0)
	{
		m_BAutoRotate = FALSE;
	} 
	else
	{
		m_BAutoRotate = TRUE;
	}

	::GetPrivateProfileString(_T("Resource"), _T("AutoOptimize"), _T("û���ҵ�AutoOptimize��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
	if (tem_nRead==0)
	{
		m_BOptimize = FALSE;
	} 
	else
	{
		m_BOptimize = TRUE;
	}

	//��ͷ�������----------------------
//	::GetPrivateProfileString(_T("ChildCamera"), _T("LasrUsed"), _T("û���ҵ���ͷLasrUsed��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
//	tem_nRead = _ttoi(tem_strRead);
//	m_nLastSubScan = tem_nRead;

// 	::GetPrivateProfileString(_T("ChildCamera"), _T("Resolution"), _T("û���ҵ���ͷResolution��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
// 	tem_nRead = _ttoi(tem_strRead);
// 	m_nLastUsedFile = tem_nRead;

	//���ò���--------------------------
	::GetPrivateProfileString(_T("AdvanceSet"), _T("ShowInfo"), _T("û���ҵ�ShowInfo��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	switch(tem_nRead)
	{
	case 0:
		m_BShowInfo    = FALSE;
		break;
	case 1:
		m_BShowInfo    = TRUE;
		break;
	default:
		m_BShowInfo    = FALSE;
		break;
	}

	::GetPrivateProfileString(_T("AdvanceSet"), _T("JPEGQuality"), _T("û���ҵ�JPEGQuality ��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	if (tem_nRead>0 && tem_nRead<100)
	{
		m_nJpegQulity   = tem_nRead;
	}
	else
	{
		m_nJpegQulity   = 50;
	}

	::GetPrivateProfileString(_T("AdvanceSet"), _T("AutoCaptureSense"), _T("û���ҵ�AutoCaptureSense��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	if (tem_nRead>0)
	{
		m_nAutoSense    = tem_nRead;
	}
	else
	{
		m_nAutoSense    = 6;
	}

	::GetPrivateProfileString(_T("AdvanceSet"), _T("NamingMode"), _T("û���ҵ�NamingMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	switch(tem_nRead)
	{
	case 0:
		m_nNamingMode    = 0;
		break;
	case 1:
		m_nNamingMode    = 1;
		break;
	case 2:
		m_nNamingMode    = 2;
		::GetPrivateProfileString(_T("AdvanceSet"), _T("PreName"), _T("û���ҵ�PreName��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		m_strPreName     = tem_strRead;
		break;
	default:
		m_nNamingMode    = 0;
		break;
	}

	::GetPrivateProfileString(_T("Resource"), _T("curdirectory"), _T("û���ҵ�curdirectory��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strDefaultPath    = tem_strRead;

	//�ж��ļ����Ƿ����
	CFileFind    tem_fFileFind;
	if (!tem_fFileFind.FindFile(m_strDefaultPath))
	{
		CreateDirectory(m_strDefaultPath, NULL);
	}
	m_strDefaultPath.ReleaseBuffer();
	m_strShowPath = m_strDefaultPath;
	m_strDefaultPath += "\\";

	::GetPrivateProfileString(_T("AdvanceSet"), _T("HTTP"), _T("û���ҵ�HTTP��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strHttp         = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("AdvanceSet"), _T("FTP"), _T("û���ҵ�FTP��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strFtpIP       = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("AdvanceSet"), _T("FtpDir"), _T("û���ҵ�FTP��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strFtpDir      = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("AdvanceSet"), _T("FtpUserName"), _T("û���ҵ�FTP��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strFtpUserName = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("AdvanceSet"), _T("FtpPassWord"), _T("û���ҵ�FTP��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strFtpPassWord       = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("AdvanceSet"), _T("FtpPort"), _T("û���ҵ�FTP��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strFtpPort          = tem_strRead;
	tem_strRead.ReleaseBuffer();


	//��������----------------------------------------------
	::GetPrivateProfileString(_T("OtherSet"), _T("ThumbWidth"), _T("û���ҵ�ThumbWidth��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	if (tem_nRead>0 && tem_nRead<=500)
	{
		m_nThumbWidth = tem_nRead;
	}
	else
	{
		m_nThumbWidth = 220;
	}

	::GetPrivateProfileString(_T("OtherSet"), _T("ThumbHeight"), _T("û���ҵ�ThumbHeight��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	if (tem_nRead>0 && tem_nRead<=700)
	{
		m_nThumbHeight = tem_nRead;
	} 
	else
	{
		m_nThumbHeight = 160;
	}
	::GetPrivateProfileString(_T("OtherSet"), _T("SoundOpen"), _T("û���ҵ�SoundOpen��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	if (tem_nRead==1)
	{
		m_BSoundOpen = TRUE;
	} 
	else
	{
		m_BSoundOpen = FALSE;
	}

	::GetPrivateProfileString(_T("Resource"), _T("AutoRotateMode"), _T("û���ҵ�AutoRotateMode��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_nAutoRotateMode = _ttoi(tem_strRead);

}


void CUDSSmartCamerav100Dlg::OnSelchangeTabSet(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int   nCursel = m_conTab.GetCurSel();
	switch (nCursel)
	{
	case 0:
		m_iChildNor.ShowWindow(TRUE);
		m_iChildAdv.ShowWindow(FALSE);
		m_iChildSet.ShowWindow(FALSE);
		break;
	case 1:
		m_iChildNor.ShowWindow(FALSE);
		m_iChildAdv.ShowWindow(TRUE);
		m_iChildSet.ShowWindow(FALSE);
		break;
	case 2:
		m_iChildNor.ShowWindow(FALSE);
		m_iChildAdv.ShowWindow(FALSE);
		m_iChildSet.ShowWindow(TRUE);
		break;
	default:
		break;
	}
	*pResult = 0;
}

//�˳���ť
void CUDSSmartCamerav100Dlg::OnBnClickedBtnTest2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString    tem_strCamera = _T("1");
	m_conVideoOcx.StopRun();
	m_conVideoOcx.Uninitial();
	//ɾ������buffer
	std::vector<CString>::iterator  tem_item;
	for (tem_item=m_vcDeleteBuffer.begin(); tem_item!=m_vcDeleteBuffer.end(); tem_item++)
	{
		DeleteFile(*tem_item);
	}
	for (tem_item=m_vcWholeName.begin(); tem_item!=m_vcWholeName.end();tem_item++)
	{
		DeleteFile(*tem_item);
	}
	if (m_vcOcrBuffer.size()>0)
	{
		std::vector<CString>::iterator  item;
		for (item=m_vcOcrBuffer.begin(); item!=m_vcOcrBuffer.end(); item++)
		{
			DeleteFile(*item);
		}
	}
	if (m_BOcrOpened)
	{
		m_api->End();
		pixDestroy(&m_image);
	}


	//���ʹܹ�����������Ϣ��������ͼ��ʾ
	CString   tem_str   = _T("1");
//	HWND      tem_hWnd = ::FindWindow(_T("MyResourceManagement"), NULL);   //�ޱ��ⴰ��
	HWND      tem_hWnd = ::FindWindow(NULL, _T("��ͼSmartScanӰ��ƽ̨ϵͳv1.8"));   //���ⴰ��
	if (tem_hWnd != NULL)
	{
		::SendMessage(tem_hWnd, WM_SETTEXT, 0, (LPARAM)tem_str.GetBuffer(tem_str.GetLength()));
	}
	CDialogEx::OnOK();
}


afx_msg LRESULT CUDSSmartCamerav100Dlg::OnSwitchItem(WPARAM wParam, LPARAM lParam)
{
	int   tem_nSelect    = (int)wParam;     //����ѡ����豸���ж��Ƿ������ʹ�õ���ͬ
	int   tem_nOperation = (int)lParam;     //����������
	long tem_lExmin = 0, tem_lExmax = 0, tem_lAutoExp = 0, tem_lValue = 0;   //�����ع������
	long tem_lExp   = 0, tem_lBrg   = 0; //�ֶ��ع�ֵ
	CString   tem_strVideoName;    //���ڱ�����Ƶ��
	CString   tem_strWholeName;
	BOOL      tem_BAutoCrop;      //���ڼ�¼¼��ǰ���Զ�����״̬
	CString   tem_strIniInfo;     //������ini�ļ�д����Ϣ
    LPCTSTR   tem_lstrVideoPath;  //��Ƶ��ַ
	CString   tem_strCurResolution; //��ȡ��ǰ�ֱ��ʣ�����������Ƶ�ߴ�
	CString   tem_strWH;            //����ӷֱ����в�ֳ����Ŀ��
	int       tem_nVedioWidth = 640;  //��Ƶ�ֱ��ʿ�
	int       tem_nVedioHeight= 480;  //��Ƶ�ֱ��ʸ�
	int       tem_nSite;            //��Ƶ�ֱ��ʲ��
	int n=-1;
	int tem_ndpi=0;

	switch(tem_nOperation)
	{
	case 0:
		if (m_nLastUsedScanner != tem_nSelect)
		{
			//�жϸø�ͷ�Ƿ��
			if (m_nLastSubScan == tem_nSelect)
			{
				m_iChildNor.m_conComScanner.SetCurSel(m_nLastUsedScanner);
				MessageBox(_T("���豸�Ѵ򿪣�"), _T("��ͼUDS"), MB_OK);
				return 0;
			}

			//����ѡ���豸����
			m_conVideoOcx.StopRun();
			m_nLastUsedScanner = tem_nSelect;
			m_nMainOpen = m_conVideoOcx.StartRun(m_nLastUsedScanner);
			//���л���ĸ�ͷд��ini�ļ�
			tem_strIniInfo.Format(_T("%d"), m_nLastUsedScanner);
			::WritePrivateProfileString(_T("ParentCamera"), _T("LastUsed"), tem_strIniInfo, m_strIniPath); 

			//�л����Ƿֱ��ʡ��Զ����С��Զ��ع�����
			m_iChildNor.m_conComReso.ResetContent();

			//�ж��Ƿ�Ϊ800W�豸
			CString   tem_strPIDVID = _T("");
			int tem_nPID200 = -1;
			int tem_nVID200 = -1;
			int       tem_nPID500   = -1;
			int       tem_nVID500  = -1;
			int       tem_nPID800   = -1;
			int       tem_nPID800GS = -1;
			int       tem_nVID800GS = -1;
			int       tem_nVID800b  = -1;
			int       tem_nPID800b  = -1;
			int       tem_nVID800   = -1;
			int       tem_nPID1200  = -1;
			int       tem_nVID1200  = -1;
			int       tem_nPID1300  = -1;
			int       tem_nVID1300  = -1;
			int       tem_nPIDTo1500= -1;
			int       tem_nVIDTo1500= -1;
			int       tem_nGS16_PID = -1;
			int       tem_nGS16_VID = -1;
			int       tem_nPID800Un = -1;
			int       tem_nVID800Un = -1;
			
			
			//�豸�򿪳ɹ������Ȼ�ȡ�豸PID_VID
			tem_strPIDVID = m_conVideoOcx.GetDevDisplayName(m_nLastUsedScanner);
			tem_strPIDVID.MakeUpper();
			//����PID_VID�Ƿ�Ϊָ�����豸
			tem_nPID200 = tem_strPIDVID.Find(m_strPID200);
			tem_nVID200 = tem_strPIDVID.Find(m_strVID200);
			tem_nPID500 = tem_strPIDVID.Find(m_strPID500);
			tem_nVID500 = tem_strPIDVID.Find(m_strVID500);
			tem_nPID800 = tem_strPIDVID.Find(m_strPID800);
			tem_nVID800 = tem_strPIDVID.Find(m_strVID800);
			tem_nPID800GS = tem_strPIDVID.Find(m_strPID800GS);
			tem_nVID800GS = tem_strPIDVID.Find(m_strVID800GS);
			tem_nPID800b= tem_strPIDVID.Find(m_strPID800b);
			tem_nVID800b= tem_strPIDVID.Find(m_strVID800b);
			tem_nPID1200 = tem_strPIDVID.Find(m_strPID1200);
			tem_nVID1200 = tem_strPIDVID.Find(m_strVID1200);
			tem_nPID1300 = tem_strPIDVID.Find(m_strPID1300);
			tem_nVID1300 = tem_strPIDVID.Find(m_strVID1300);
			tem_nPIDTo1500 = tem_strPIDVID.Find(m_strPIDTo1500);
			tem_nVIDTo1500 = tem_strPIDVID.Find(m_strVIDTo1500);
			tem_nGS16_PID  = tem_strPIDVID.Find(m_strGS16_PID);
			tem_nGS16_VID  = tem_strPIDVID.Find(m_strGS16_VID);
			tem_nPID800Un = tem_strPIDVID.Find(m_strPID800Un);
			tem_nVID800Un = tem_strPIDVID.Find(m_strVID800Un);
			
			CString   tem_strResolution = _T("");
			if ((tem_nPID800!=-1 && tem_nVID800!=-1) || (tem_nPID800b!=-1 && tem_nVID800b!=-1) || (tem_nPID800GS!=-1 && tem_nVID800GS!=-1) ||
				(tem_nPID800Un!=-1 && tem_nVID800Un!=-1))
			{
				//���豸Ϊָ���豸�����ָ���ֱ���
				m_BCamera800 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("3664��2744");
				m_iChildNor.m_conComReso.InsertString(-1, tem_strResolution);

				//������õ�ǰ�ֱ������������ܸ�����˵���÷ֱ���Ϊ��ֵ�ֱ��ʣ�Ӧ����ΪӲ�����ֱ���
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
				
				m_nLastUsedResolu = m_conVideoOcx.GetCurResoIndex();
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					int  tem_nMaxIndex = GetmaxResoindex();
					m_conVideoOcx.SetResolution(tem_nMaxIndex);
				}
				else
				{
					m_conVideoOcx.SetResolution(m_nLastUsedResolu);
				}
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
			}
			else if (tem_nPID500!=-1 && tem_nVID500!=-1)
			{
				//���豸Ϊָ���豸�����ָ���ֱ���
				m_BCamera500 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("3644*2744");
				m_iChildNor.m_conComReso.InsertString(m_nInterpolateReso, tem_strResolution);

				//������õ�ǰ�ֱ������������ܸ�����˵���÷ֱ���Ϊ��ֵ�ֱ��ʣ�Ӧ����ΪӲ�����ֱ���
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);

				m_nLastUsedResolu = m_conVideoOcx.GetCurResoIndex();
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					int  tem_nMaxIndex = GetmaxResoindex();
					m_conVideoOcx.SetResolution(tem_nMaxIndex);
				}
				else
				{
					m_conVideoOcx.SetResolution(m_nLastUsedResolu);
				}
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
			}
			else if (tem_nPID1200!=-1 && tem_nVID1200!=-1)
			{
				//���豸Ϊָ���豸�����ָ���ֱ���
				m_BCamera1200 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("4680��3510");
				m_iChildNor.m_conComReso.InsertString(m_nInterpolateReso, tem_strResolution);

				//������õ�ǰ�ֱ������������ܸ�����˵���÷ֱ���Ϊ��ֵ�ֱ��ʣ�Ӧ����ΪӲ�����ֱ���
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);

				m_nLastUsedResolu = m_conVideoOcx.GetCurResoIndex();
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					int  tem_nMaxIndex = GetmaxResoindex();
					m_conVideoOcx.SetResolution(tem_nMaxIndex);
				}
				else
				{
					m_conVideoOcx.SetResolution(m_nLastUsedResolu);
				}
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
			}
			else if (tem_nPID1300!=-1 && tem_nVID1300!=-1)
			{
				//���豸Ϊָ���豸�����ָ���ֱ���
				m_BCamera1300 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("4680��3360");
				m_iChildNor.m_conComReso.InsertString(m_nInterpolateReso, tem_strResolution);

				//������õ�ǰ�ֱ������������ܸ�����˵���÷ֱ���Ϊ��ֵ�ֱ��ʣ�Ӧ����ΪӲ�����ֱ���
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);

				m_nLastUsedResolu = m_conVideoOcx.GetCurResoIndex();
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
// 					int  tem_nMaxIndex = GetmaxResoindex();
// 					m_conVideoOcx.SetResolution(tem_nMaxIndex);

					int  tem_nMaxIndex = GetDiyResoindex(1);
					if (tem_nMaxIndex<0 ||tem_nMaxIndex>13)
					{
						m_conVideoOcx.SetResolution(9);
					} 
					else
					{
						m_conVideoOcx.SetResolution(tem_nMaxIndex);
					}
					
					
					m_conVideoOcx.SetDisPlayInfo(4480, 3360, 0);
				}
				else
				{
					m_conVideoOcx.SetResolution(m_nLastUsedResolu);

					CString    tem_strCurRes = m_conVideoOcx.GetResolution(m_nLastUsedResolu);
					int        tem_nFindIndex = tem_strCurRes.Find('*');

					CString    tem_strFirst = tem_strCurRes;
					CString    tem_strLast  = tem_strCurRes;
					tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
					tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
					int        tem_nFirst   = _ttoi(tem_strFirst);
					int        tem_nLast    = _ttoi(tem_strLast);

					if (tem_nFirst<1000)
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}
					else if (tem_nFirst>=1000 && tem_nFirst<2000)
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);	
					}
					else
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}	

				}
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
			}
			else if (tem_nPIDTo1500!=-1 && tem_nVIDTo1500!=-1)
			{
				//���豸Ϊָ���豸�����ָ���ֱ���
				m_BCameraTo1500 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("4480��3360");
				m_iChildNor.m_conComReso.InsertString(m_nInterpolateReso, tem_strResolution);

				//������õ�ǰ�ֱ������������ܸ�����˵���÷ֱ���Ϊ��ֵ�ֱ��ʣ�Ӧ����ΪӲ�����ֱ���
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);

				m_nLastUsedResolu = m_conVideoOcx.GetCurResoIndex();
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
//					int  tem_nMaxIndex = GetmaxResoindex();
// 					m_conVideoOcx.SetResolution(tem_nMaxIndex);
					int  tem_nMaxIndex = GetDiyResoindex(1);
					m_conVideoOcx.SetResolution(tem_nMaxIndex);
					m_conVideoOcx.SetDisPlayInfo(4480, 3360, 0);
				}
				else
				{
					m_conVideoOcx.SetResolution(m_nLastUsedResolu);

					CString    tem_strCurRes = m_conVideoOcx.GetResolution(m_nLastUsedResolu);
					int        tem_nFindIndex = tem_strCurRes.Find('*');

					CString    tem_strFirst = tem_strCurRes;
					CString    tem_strLast  = tem_strCurRes;
					tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
					tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
					int        tem_nFirst   = _ttoi(tem_strFirst);
					int        tem_nLast    = _ttoi(tem_strLast);

					if (tem_nFirst<1000)
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}
					else if (tem_nFirst>=1000 && tem_nFirst<2000)
					{
						m_conVideoOcx.SetDisPlayInfo(0, 0, 0);	
					}
					else
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}	
				}
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
			}
			else if (tem_nGS16_PID!=-1 && tem_nGS16_VID!=-1)
			{
				//���豸Ϊָ���豸�����ָ���ֱ���
				m_BGS1600 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("4928��3264");
				m_iChildNor.m_conComReso.InsertString(m_nInterpolateReso, tem_strResolution);

				//������õ�ǰ�ֱ������������ܸ�����˵���÷ֱ���Ϊ��ֵ�ֱ��ʣ�Ӧ����ΪӲ�����ֱ���
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);

				m_nLastUsedResolu = m_conVideoOcx.GetCurResoIndex();
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//					int  tem_nMaxIndex = GetmaxResoindex();
					// 					m_conVideoOcx.SetResolution(tem_nMaxIndex);
					int  tem_nMaxIndex = GetDiyResoindex(1);
					m_conVideoOcx.SetResolution(tem_nMaxIndex);
					m_conVideoOcx.SetDisPlayInfo(4928, 3264, 0);
				}
				else
				{
					m_conVideoOcx.SetResolution(m_nLastUsedResolu);

					CString    tem_strCurRes = m_conVideoOcx.GetResolution(m_nLastUsedResolu);
					int        tem_nFindIndex = tem_strCurRes.Find('*');

					CString    tem_strFirst = tem_strCurRes;
					CString    tem_strLast  = tem_strCurRes;
					tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
					tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
					int        tem_nFirst   = _ttoi(tem_strFirst);
					int        tem_nLast    = _ttoi(tem_strLast);

					if (tem_nFirst<1000)
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}
					else if (tem_nFirst>=1000 && tem_nFirst<2000)
					{
						m_conVideoOcx.SetDisPlayInfo(0, 0, 0);	
					}
					else
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}	
				}
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
			}
			else if (tem_nGS16_PID!=-1 && tem_nGS16_VID!=-1)
			{
				//���豸Ϊָ���豸�����ָ���ֱ���
				m_BGS1600 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("4928��3264");
				m_iChildNor.m_conComReso.InsertString(m_nInterpolateReso, tem_strResolution);

				//������õ�ǰ�ֱ������������ܸ�����˵���÷ֱ���Ϊ��ֵ�ֱ��ʣ�Ӧ����ΪӲ�����ֱ���
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);

				m_nLastUsedResolu = m_conVideoOcx.GetCurResoIndex();
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//					int  tem_nMaxIndex = GetmaxResoindex();
					// 					m_conVideoOcx.SetResolution(tem_nMaxIndex);
					int  tem_nMaxIndex = GetDiyResoindex(1);
					m_conVideoOcx.SetResolution(tem_nMaxIndex);
					m_conVideoOcx.SetDisPlayInfo(4928, 3264, 0);
				}
				else
				{
					m_conVideoOcx.SetResolution(m_nLastUsedResolu);

					CString    tem_strCurRes = m_conVideoOcx.GetResolution(m_nLastUsedResolu);
					int        tem_nFindIndex = tem_strCurRes.Find('*');

					CString    tem_strFirst = tem_strCurRes;
					CString    tem_strLast  = tem_strCurRes;
					tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
					tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
					int        tem_nFirst   = _ttoi(tem_strFirst);
					int        tem_nLast    = _ttoi(tem_strLast);

					if (tem_nFirst<1000)
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}
					else if (tem_nFirst>=1000 && tem_nFirst<2000)
					{
						m_conVideoOcx.SetDisPlayInfo(0, 0, 0);	
					}
					else
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}	
				}
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
			}
			else if (tem_nPID200!=-1 && tem_nVID200!=-1)
			{
				//���豸Ϊָ���豸�����ָ���ֱ���
				m_BCamera200 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("2048��1536");
				m_iChildNor.m_conComReso.InsertString(m_nInterpolateReso, tem_strResolution);

				//������õ�ǰ�ֱ������������ܸ�����˵���÷ֱ���Ϊ��ֵ�ֱ��ʣ�Ӧ����ΪӲ�����ֱ���
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);

				m_nLastUsedResolu = m_conVideoOcx.GetCurResoIndex();
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//					int  tem_nMaxIndex = GetmaxResoindex();
					// 					m_conVideoOcx.SetResolution(tem_nMaxIndex);
					int  tem_nMaxIndex = GetDiyResoindex(1);
					m_conVideoOcx.SetResolution(tem_nMaxIndex);
					m_conVideoOcx.SetDisPlayInfo(2048, 1536, 0);
				}
				else
				{
					m_conVideoOcx.SetResolution(m_nLastUsedResolu);

					CString    tem_strCurRes = m_conVideoOcx.GetResolution(m_nLastUsedResolu);
					int        tem_nFindIndex = tem_strCurRes.Find('*');

					CString    tem_strFirst = tem_strCurRes;
					CString    tem_strLast  = tem_strCurRes;
					tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
					tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
					int        tem_nFirst   = _ttoi(tem_strFirst);
					int        tem_nLast    = _ttoi(tem_strLast);

					if (tem_nFirst<1000)
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}
					else if (tem_nFirst>=1000 && tem_nFirst<2000)
					{
						m_conVideoOcx.SetDisPlayInfo(0, 0, 0);	
					}
					else
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}	
				}
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
			}
			else
			{
				m_BCamera200 = FALSE;
				m_BCamera500  = FALSE;
				m_BCamera800  = FALSE;
				m_BCamera1200 = FALSE;
				m_BCamera1300 = FALSE;
				m_BCameraTo1500 = FALSE;
				m_BGS1600     = FALSE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
				for (int i=0; i<tem_nResCount; i++)
				{
					CString   tem_strResolution = m_conVideoOcx.GetResolution(i);
					if (tem_strResolution==_T("640*480"))
					{
						tem_strResolution += _T("(VGA)");
					}
					else if (tem_strResolution == _T("352*288"))
					{
						tem_strResolution += _T("(CIF)");
					}
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				m_nLastUsedResolu = m_conVideoOcx.GetCurResoIndex();
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
				
			}
	
			m_conVideoOcx.SetColorMode(m_nLastUsedColor);
			//�Զ����б��ֲ���
			m_conVideoOcx.AdjuestImageCrop(m_BAutoCrop);
			m_conVideoOcx.ManualImageCrop(m_BManualCrop);
			//�Զ��ع��Լ��ֶ��ع�ֵ
			if (m_BAutoExp)
			{
				m_conVideoOcx.SetAutoExposure(TRUE);
				m_iChildNor.m_conSlidExpos.EnableWindow(FALSE);
			}
			else
			{
				m_conVideoOcx.SetAutoExposure(FALSE);
				m_lReturnCode = m_conVideoOcx.GetExposureRange(&tem_lExmin, &tem_lExmax);
				m_iChildNor.m_conSlidExpos.SetRange(tem_lExmin, tem_lExmax); //����slider��Χ
				m_iChildNor.m_conSlidExpos.SetPageSize(1);
				m_conVideoOcx.GetExposure(&tem_lValue, &tem_lAutoExp);
				UpdateData(FALSE);
				if (m_nManualVaule>= tem_lExmin && m_nManualVaule<=tem_lExmax)
				{
					m_iChildNor.m_conSlidExpos.SetPos(m_nManualVaule);       //����slider��ǰֵ
					m_iChildNor.m_conStaExp = m_nManualVaule;                //����slider��ʾ��ǰֵ
					m_iChildNor.m_conStaExpStr.Format(_T("%d"), m_nManualVaule);
					m_conVideoOcx.SetExposure(m_nManualVaule, FALSE);
				} 
				else
				{
					m_iChildNor.m_conSlidExpos.SetPos(tem_lValue);       //����slider��ǰֵ
					m_iChildNor.m_conStaExp = tem_lValue;                //����slider��ʾ��ǰֵ
					m_iChildNor.m_conStaExpStr.Format(_T("%d"), m_iChildNor.m_conStaExp);
					m_nManualVaule = tem_lValue;
					m_conVideoOcx.SetExposure(m_nManualVaule, FALSE);
				}
				m_iChildNor.m_conSlidExpos.EnableWindow(TRUE);	
			}
			//�����ֶ�����ֵ
			Self_SetBriValue();
//			m_conVideoOcx.SetBrightness(m_nBriValue, FALSE);
		}
		break;
	case 1:
		if (m_nLastUsedResolu != tem_nSelect)
		{
			if (m_BCamera800)
			{
				//800W�豸
				m_nLastUsedResolu = tem_nSelect;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//��ʱΪ��ֵ�ֱ��ʣ�����Ϊ���ֱ���
					int  tem_nMaxIndex = GetmaxResoindex();
					m_conVideoOcx.SetResolution(tem_nMaxIndex);
					
				}
				else
				{
					m_conVideoOcx.SetResolution(tem_nSelect);
				}
				//��ѡ��ķֱ���д��ini�����ļ�
				tem_strIniInfo.Format(_T("%d"), tem_nSelect);
				::WritePrivateProfileString(_T("ParentCamera"), _T("Resolution"), tem_strIniInfo, m_strIniPath); 
			}
			else if (m_BCamera500)
			{
				//500W�豸
				m_nLastUsedResolu = tem_nSelect;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//��ʱΪ��ֵ�ֱ��ʣ�����Ϊ���ֱ���
					int  tem_nMaxIndex = GetmaxResoindex();
					m_conVideoOcx.SetResolution(tem_nMaxIndex);

				}
				else
				{
					m_conVideoOcx.SetResolution(tem_nSelect);
				}
				//��ѡ��ķֱ���д��ini�����ļ�
				tem_strIniInfo.Format(_T("%d"), tem_nSelect);
				::WritePrivateProfileString(_T("ParentCamera"), _T("Resolution"), tem_strIniInfo, m_strIniPath); 
			}
			else if (m_BCamera1200)
			{
				//1000W�豸
				m_nLastUsedResolu = tem_nSelect;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//��ʱΪ��ֵ�ֱ��ʣ�����Ϊ���ֱ���
					int  tem_nMaxIndex = GetmaxResoindex();
					m_conVideoOcx.SetResolution(tem_nMaxIndex);

				}
				else
				{
					m_conVideoOcx.SetResolution(tem_nSelect);
				}
				//��ѡ��ķֱ���д��ini�����ļ�
				tem_strIniInfo.Format(_T("%d"), tem_nSelect);
				::WritePrivateProfileString(_T("ParentCamera"), _T("Resolution"), tem_strIniInfo, m_strIniPath); 
			}
			else if (m_BCamera1300)
			{
				//1300W�豸
				m_nLastUsedResolu = tem_nSelect;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//��ʱΪ��ֵ�ֱ��ʣ�����Ϊ���ֱ���
// 					int  tem_nMaxIndex = GetmaxResoindex();
// 					m_conVideoOcx.SetResolution(tem_nMaxIndex);

					int  tem_nMaxIndex = GetDiyResoindex(1);
					if (tem_nMaxIndex<0 ||tem_nMaxIndex>13)
					{
						m_conVideoOcx.SetResolution(9);
					} 
					else
					{
						m_conVideoOcx.SetResolution(tem_nMaxIndex);
					}
				

					m_conVideoOcx.SetDisPlayInfo(4480, 3360, 0);

				}
				else
				{
					m_conVideoOcx.SetResolution(tem_nSelect);

					CString    tem_strCurRes = m_conVideoOcx.GetResolution(tem_nSelect);
					int        tem_nFindIndex = tem_strCurRes.Find('*');

					CString    tem_strFirst = tem_strCurRes;
					CString    tem_strLast  = tem_strCurRes;
					tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
					tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
					int        tem_nFirst   = _ttoi(tem_strFirst);
					int        tem_nLast    = _ttoi(tem_strLast);

					if (tem_nFirst<1000)
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}
					else if (tem_nFirst>=1000 && tem_nFirst<2000)
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}
					else
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}	

				
				}
				//��ѡ��ķֱ���д��ini�����ļ�
				tem_strIniInfo.Format(_T("%d"), tem_nSelect);
				::WritePrivateProfileString(_T("ParentCamera"), _T("Resolution"), tem_strIniInfo, m_strIniPath); 
			}
			else if (m_BCameraTo1500)
			{
				//1200W�豸
				m_nLastUsedResolu = tem_nSelect;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//��ʱΪ��ֵ�ֱ��ʣ�����Ϊ���ֱ���
// 					int  tem_nMaxIndex = GetmaxResoindex();
// 					m_conVideoOcx.SetResolution(tem_nMaxIndex);

					int  tem_nMaxIndex = GetDiyResoindex(1);
					m_conVideoOcx.SetResolution(tem_nMaxIndex);

					m_conVideoOcx.SetDisPlayInfo(4480, 3360, 0);

				}
				else
				{
					m_conVideoOcx.SetResolution(tem_nSelect);

					CString    tem_strCurRes = m_conVideoOcx.GetResolution(tem_nSelect);
					int        tem_nFindIndex = tem_strCurRes.Find('*');

					CString    tem_strFirst = tem_strCurRes;
					CString    tem_strLast  = tem_strCurRes;
					tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
					tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
					int        tem_nFirst   = _ttoi(tem_strFirst);
					int        tem_nLast    = _ttoi(tem_strLast);

					if (tem_nFirst<1000)
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}
					else if (tem_nFirst>=1000 && tem_nFirst<2000)
					{
						m_conVideoOcx.SetDisPlayInfo(0, 0, 0);
					}
					else
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}	
					
				}
				//��ѡ��ķֱ���д��ini�����ļ�
				tem_strIniInfo.Format(_T("%d"), tem_nSelect);
				::WritePrivateProfileString(_T("ParentCamera"), _T("Resolution"), tem_strIniInfo, m_strIniPath); 
			}
			else if (m_BGS1600)
			{
				//1300W->1600W�豸
				m_nLastUsedResolu = tem_nSelect;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					int  tem_nMaxIndex = GetDiyResoindex(1);
					m_conVideoOcx.SetResolution(tem_nMaxIndex);

					m_conVideoOcx.SetDisPlayInfo(4928, 3264, 0);

				}
				else
				{
					m_conVideoOcx.SetResolution(tem_nSelect);

					CString    tem_strCurRes = m_conVideoOcx.GetResolution(tem_nSelect);
					int        tem_nFindIndex = tem_strCurRes.Find('*');

					CString    tem_strFirst = tem_strCurRes;
					CString    tem_strLast  = tem_strCurRes;
					tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
					tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
					int        tem_nFirst   = _ttoi(tem_strFirst);
					int        tem_nLast    = _ttoi(tem_strLast);

					if (tem_nFirst<1000)
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}
					else if (tem_nFirst>=1000 && tem_nFirst<2000)
					{
						m_conVideoOcx.SetDisPlayInfo(0, 0, 0);
					}
					else
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}	

				}
				//��ѡ��ķֱ���д��ini�����ļ�
				tem_strIniInfo.Format(_T("%d"), tem_nSelect);
				::WritePrivateProfileString(_T("ParentCamera"), _T("Resolution"), tem_strIniInfo, m_strIniPath); 
			}
			else if (m_BCamera200)
			{
				//200W->300W�豸
				m_nLastUsedResolu = tem_nSelect;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					int  tem_nMaxIndex = GetDiyResoindex(1);
					m_conVideoOcx.SetResolution(tem_nMaxIndex);

					m_conVideoOcx.SetDisPlayInfo(2048, 1536, 0);

				}
				else
				{
					m_conVideoOcx.SetResolution(tem_nSelect);

					CString    tem_strCurRes = m_conVideoOcx.GetResolution(tem_nSelect);
					int        tem_nFindIndex = tem_strCurRes.Find('*');

					CString    tem_strFirst = tem_strCurRes;
					CString    tem_strLast  = tem_strCurRes;
					tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
					tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
					int        tem_nFirst   = _ttoi(tem_strFirst);
					int        tem_nLast    = _ttoi(tem_strLast);

					if (tem_nFirst<1000)
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}
					else if (tem_nFirst>=1000 && tem_nFirst<2000)
					{
						m_conVideoOcx.SetDisPlayInfo(0, 0, 0);
					}
					else
					{
						m_conVideoOcx.SetDisPlayInfo(tem_nFirst, tem_nLast, 0);
					}	

				}
				//��ѡ��ķֱ���д��ini�����ļ�
				tem_strIniInfo.Format(_T("%d"), tem_nSelect);
				::WritePrivateProfileString(_T("ParentCamera"), _T("Resolution"), tem_strIniInfo, m_strIniPath); 
			}
			else
			{
				//��ͨ�豸
				m_nLastUsedResolu = tem_nSelect;
				m_conVideoOcx.SetResolution(tem_nSelect);
				//��ѡ��ķֱ���д��ini�����ļ�
				tem_strIniInfo.Format(_T("%d"), tem_nSelect);
				::WritePrivateProfileString(_T("ParentCamera"), _T("Resolution"), tem_strIniInfo, m_strIniPath); 

			}
			tem_ndpi = m_conVideoOcx.GetImageDPI();
		}	
		
		break;
	case 2:
		//ѡ����ͷ���ո�ʽ
		switch(tem_nSelect)
		{
		case 0:
			m_strFileFormat = ".bmp";
			m_BPDFCpt       = FALSE;
			m_BBase64Cpt    = FALSE;
			m_BDcmCpt       = FALSE;
			m_BOfdCpt       = FALSE;
			break;
		case 1:
			m_strFileFormat = ".jpg";
			m_BPDFCpt       = FALSE;
			m_BBase64Cpt    = FALSE;
			m_BDcmCpt       = FALSE;
			m_BOfdCpt       = FALSE;
			break;
		case 2:
			m_strFileFormat = ".tif";
			m_BPDFCpt       = FALSE;
			m_BBase64Cpt    = FALSE;
			m_BDcmCpt       = FALSE;
			m_BOfdCpt       = FALSE;
			break;
		case 3:
			m_strFileFormat = ".png";
			m_BPDFCpt       = FALSE;
			m_BBase64Cpt    = FALSE;
			m_BDcmCpt       = FALSE;
			m_BOfdCpt       = FALSE;
			break;
		case 4:
			m_strFileFormat = ".pdf";
			m_BPDFCpt       = TRUE;
			m_BBase64Cpt    = FALSE;
			m_BDcmCpt       = FALSE;
			m_BOfdCpt       = FALSE;
			break;
		case 5:
			//base64�ļ�������
			m_strFileFormat = ".txt";
			m_BPDFCpt       = FALSE;
			m_BBase64Cpt    = TRUE;
			m_BDcmCpt       = FALSE;
			m_BOfdCpt       = FALSE;
			break;
		case 6:
			m_strFileFormat = ".dcm";
			m_BPDFCpt       = FALSE;
			m_BBase64Cpt    = FALSE;
			m_BDcmCpt       = TRUE;
			m_BOfdCpt       = FALSE;
			break;	
		case 7:
			m_strFileFormat = ".ofd";
			m_BPDFCpt       = FALSE;
			m_BBase64Cpt    = FALSE;
			m_BDcmCpt       = FALSE;
			m_BOfdCpt       = TRUE;
			break;
		default:
			break;
		}

		//��ѡ����ļ���ʽд��ini�����ļ�
		tem_strIniInfo.Format(_T("%d"), tem_nSelect);
		::WritePrivateProfileString(_T("ParentCamera"), _T("FileMode"), tem_strIniInfo, m_strIniPath); 
		break;
	case 3:
		switch(tem_nSelect)
		{
		case 0:
			m_conVideoOcx.SetColorMode(0);
			break;
		case 1:
			m_conVideoOcx.SetColorMode(1);
			break;
		case 2:
			m_conVideoOcx.SetColorMode(2);
			break;
		default:
			break;
		}
		m_nLastUsedColor = tem_nSelect;
		//��ѡ���ɫ��ģʽд��ini�����ļ�
		tem_strIniInfo.Format(_T("%d"), tem_nSelect);
		::WritePrivateProfileString(_T("ParentCamera"), _T("ColorMode"), tem_strIniInfo, m_strIniPath); 
		break;
	case 4:
		m_BAutoCrop   = tem_nSelect;
		m_BManualCrop = !tem_nSelect;
		if (tem_nSelect == 1)
		{
			//�����Զ�����
			m_conVideoOcx.ManualImageCrop(FALSE);
			m_conVideoOcx.AdjuestImageCrop(TRUE);
		} 
		else
		{
			//�����ֶ�����
			m_conVideoOcx.AdjuestImageCrop(FALSE);
			m_conVideoOcx.ManualImageCrop(TRUE);
			m_conVideoOcx.SetMessage(1);
		}
		

		//��ѡ����Զ�����д��ini�����ļ�
		tem_strIniInfo.Format(_T("%d"), tem_nSelect);
		::WritePrivateProfileString(_T("ParentCamera"), _T("AutoCrop"), tem_strIniInfo, m_strIniPath); 
		break;
	case 5:
		m_BAutoExp    = tem_nSelect;	
		if (m_BAutoExp)
		{
			//�Զ��ع�	
			m_lReturnCode = m_conVideoOcx.GetExposureRange(&tem_lExmin, &tem_lExmax);
			m_iChildNor.m_conSlidExpos.SetRange(tem_lExmin, tem_lExmax); //����slider��Χ
			m_iChildNor.m_conSlidExpos.SetPageSize(1);
			m_conVideoOcx.GetExposure(&tem_lValue, &tem_lAutoExp);
			UpdateData(TRUE);
			m_iChildNor.m_conSlidExpos.SetPos(tem_lValue);       //����slider��ǰֵ
			m_iChildNor.m_conStaExp = tem_lValue;                //����slider��ʾ��ǰֵ
			m_iChildNor.m_conStaExpStr.Format(_T("%d"), m_iChildNor.m_conStaExp);
			m_iChildNor.m_conSlidExpos.EnableWindow(FALSE);	
			m_conVideoOcx.SetAutoExposure(TRUE);	
			UpdateData(FALSE);
		} 
		else
		{
			//�ֶ��ع�
			m_conVideoOcx.SetAutoExposure(FALSE);
			m_lReturnCode = m_conVideoOcx.GetExposureRange(&tem_lExmin, &tem_lExmax);
			m_iChildNor.m_conSlidExpos.SetRange(tem_lExmin, tem_lExmax); //����slider��Χ
			m_iChildNor.m_conSlidExpos.SetPageSize(1);
			m_conVideoOcx.GetExposure(&tem_lValue, &tem_lAutoExp);
// 			UpdateData(FALSE);
// 			m_iChildNor.m_conSlidExpos.SetPos(tem_lValue);       //����slider��ǰֵ
// 			m_iChildNor.m_conStaExp = tem_lValue;                //����slider��ʾ��ǰֵ

			m_nManualVaule = tem_lValue;
			m_conVideoOcx.SetExposure(m_nManualVaule, FALSE);

			m_iChildNor.m_conSlidExpos.EnableWindow(TRUE);	
			tem_strIniInfo.Format(_T("%d"), tem_nSelect);
			::WritePrivateProfileString(_T("ParentCamera"), _T("ExpValue"), tem_strIniInfo, m_strIniPath);
		}

		//��ѡ����Զ��ع�д��ini�����ļ�
		tem_strIniInfo.Format(_T("%d"), tem_nSelect);
		::WritePrivateProfileString(_T("ParentCamera"), _T("AutoExp"), tem_strIniInfo, m_strIniPath);
		
		break;
	case 6:
		//�����ֶ��ع�ֵ
		tem_lExp = tem_nSelect;
		m_conVideoOcx.SetExposure(tem_lExp, FALSE);  
		tem_strIniInfo.Format(_T("%d"), tem_lExp);
		::WritePrivateProfileString(_T("ParentCamera"), _T("ExpValue"), tem_strIniInfo, m_strIniPath);
		break;
	case 7:
		m_BParentVideo = TRUE;
		//Ĭ��ʹ����ͷ��Ϊ¼����Ƶͷ
		//¼��ǰ�ر��Զ����У�¼�ƺ���Ʋ���ԭ��״̬
		tem_BAutoCrop = m_BAutoCrop;
		m_conVideoOcx.AdjuestImageCrop(FALSE);
		//		tem_strVideoName.Format(_T("%d"), m_nImageCount);
		tem_strVideoName = NamingFile(m_nNamingMode);
//		tem_strVideoName += ".mp4";
		tem_strVideoName += m_strVideoFormat;
		tem_strWholeName = m_strDefaultPath + tem_strVideoName;
		//���ӿ��----------------------------------------------------------------
		m_iChildNor.m_conComReso.GetWindowText(tem_strCurResolution);
		tem_nSite = tem_strCurResolution.Find(_T("*"));
		tem_strWH = tem_strCurResolution.Mid(0, tem_nSite);
		tem_nVedioWidth = _ttoi(tem_strWH);
		tem_strWH = tem_strCurResolution.Mid(tem_nSite+1);
		tem_nVedioHeight = _ttoi(tem_strWH);


		//������Ƶ���豸����
		m_nAudioIndex = tem_nSelect;
		n = m_conVideoOcx.StartRecord(m_nLastUsedScanner, tem_strWholeName, 640, 480, m_nVideoBit, m_nVideoFPS);
		m_conVideoOcx.StartRecordWithAudio(m_nLastUsedScanner, m_nAudioIndex, tem_strWholeName, 640, 480, m_nVideoBit, m_nVideoFPS);
		
//		m_conVideoOcx.StartRecordEx(tem_strWholeName, m_nVideoBit, m_nVideoFPS);
//		m_conVideoOcx.StartRecord(m_nLastUsedScanner, tem_strWholeName, m_nVideoWidth, m_nVideoHeight, m_nVideoBit, m_nVideoFPS);
		m_strVideoPath = tem_strWholeName;
		m_iChildNor.SetTimer(1, 10, NULL);
		m_nImageCount++;
		m_nNamingCount++;

/*
		//�жϸ�ͷ�Ƿ�򿪣�����ͷû�д�Ĭ����ͷ¼��
		if (m_nLastSubScan == -1)
		{
			m_BParentVideo = TRUE;
			//Ĭ��ʹ����ͷ��Ϊ¼����Ƶͷ
			//¼��ǰ�ر��Զ����У�¼�ƺ���Ʋ���ԭ��״̬
			tem_BAutoCrop = m_BAutoCrop;
			m_conVideoOcx.AdjuestImageCrop(FALSE);
			//		tem_strVideoName.Format(_T("%d"), m_nImageCount);
			tem_strVideoName = NamingFile(m_nNamingMode);
			tem_strVideoName += ".mp4";
			tem_strWholeName = m_strDefaultPath + tem_strVideoName;
			//���ӿ��----------------------------------------------------------------
			m_conVideoOcx.StartRecord(m_nLastUsedScanner, tem_strWholeName, m_nVideoWidth, m_nVideoHeight, m_nVideoBit, m_nVideoFPS);
			m_strVideoPath = tem_strWholeName;
			m_iChildNor.SetTimer(1, 10, NULL);
			m_nImageCount++;
		}
		else
		{
			m_BParentVideo = FALSE;
			//��ͷ�Ѵ򿪣�ͨ������ѡ������ͷ¼��
			tem_strVideoName = NamingFile(m_nNamingMode);
			tem_strVideoName += ".mp4";
			tem_strWholeName = m_strDefaultPath + tem_strVideoName;
			//���ӿ��----------------------------------------------------------------
			m_conVideoOcx.StartRecord(m_nLastSubScan, tem_strWholeName, m_nVideoWidth, m_nVideoHeight, m_nVideoBit, m_nVideoFPS);
			m_strVideoPath = tem_strWholeName;
			m_iChildNor.SetTimer(1, 10, NULL);
			m_nImageCount++;
		}
*/
	   
		break;
	case 8:
		m_iChildNor.KillTimer(1);
		m_conVideoOcx.StopRecord();

		m_iChildNor.m_conRichEdit.SetSelectionCharFormat(m_iChildNor.tem_fontRichEdit);  //�����ø�ʽ	
		m_iChildNor.m_conRichEdit.ReplaceSel(m_strVideoPath);
		m_iChildNor.m_conRichEdit.ReplaceSel(_T("\n"));
		m_iChildNor.m_conRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

		m_iChildNor.m_conComScanner.SetCurSel(m_nLastUsedScanner);
		m_conVideoOcx.StartRun(m_nLastUsedScanner);
		m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
		m_conVideoOcx.SetResolution(m_nLastUsedResolu);
		m_conVideoOcx.SetColorMode(m_nLastUsedColor);
		m_conVideoOcx.AdjuestImageCrop(m_BAutoCrop);


/*
		//ֹͣ¼���ָ��������
		if (m_BParentVideo)
		{
			m_iChildNor.m_conComScanner.SetCurSel(m_nLastUsedScanner);
			m_conVideoOcx.StartRun(m_nLastUsedScanner);
			m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
			m_conVideoOcx.SetResolution(m_nLastUsedResolu);
			m_conVideoOcx.SetColorMode(m_nLastUsedColor);
			m_conVideoOcx.AdjuestImageCrop(m_BAutoCrop);
		}
		else
		{
			m_conVideoOcx.StartSubCamera(m_nLastSubScan);

		}
	*/	
		break;
	case 9:
		//�����ֶ�����ֵ
		tem_lBrg = tem_nSelect;
		m_nBriValue = tem_lBrg;
		m_conVideoOcx.SetBrightness(tem_lBrg, FALSE);

		tem_strIniInfo.Format(_T("%d"), tem_lBrg);
		::WritePrivateProfileString(_T("ParentCamera"), _T("BriValue"), tem_strIniInfo, m_strIniPath);

		break;
	case 10:
		if (tem_nSelect==0)
		{
			m_strVideoFormat = _T(".mp4");
		}
		else if (tem_nSelect==1)
		{
			m_strVideoFormat = _T(".wmv");
		}
		else if (tem_nSelect==2)
		{
			m_strVideoFormat = _T(".avi");
		}
		break;
	case 11:
		if (tem_nSelect == 0)
		{
			m_BAutoRotate = FALSE;
		} 
		else
		{
			m_BAutoRotate = TRUE;
		}
		break;
	case 12:
		if (tem_nSelect == 0)
		{
			m_BOptimize = FALSE;
		} 
		else
		{
			m_BOptimize = TRUE;
		}
		break;
	default:
		break;
	}
	return 0;
}


//����
void CUDSSmartCamerav100Dlg::OnBnClickedBtnCapature()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	CString   tem_strName;         //�޺�׺
	CString   tem_strFileName;     //����׺
	CString   tem_strWholeName;    //��·��,ͼ���ļ�
	CString   tem_strPDFimgName;   //��·���������ļ�
	CString   tem_strTXTimgName;
	CString   tem_strThumbPath;    //����ͼ·��
	CString   tem_strSrcImageName; //��ֵԭͼ
	CString   tem_strSrcImagePDF;  //PDFԭͼ

	CString   tem_strThumFile;     //�Զ���ת�㷨2����ͼ
	
	tem_strName      = NamingFile(m_nNamingMode);
	tem_strFileName  = tem_strName + m_strFileFormat;
	tem_strWholeName = m_strDefaultPath + tem_strFileName;
	tem_strSrcImageName = m_strBufferPath + tem_strFileName;

	tem_strThumFile  = m_strBufferPath;
	tem_strThumFile += _T("\\Rotate_") ;
	tem_strThumFile += tem_strName;
	tem_strThumFile += _T(".jpg");

	if (m_BSoundOpen)
	{
		sndPlaySound(_T("CameraSound.WAV"), NULL);
	}
	/***********************************
	*           �����ṹ
	* PDF����-------��ֵ�豸
	*        -------��ͨ�豸
	*
	*base64����----��ֵ�豸
	*        ------��ͨ�豸
	*
	*DCM����-------��ֵ�豸
	*        ------��ͨ�豸
	*
	*OFD����-------��ֵ�豸
	*        ------��ͨ�豸
	*��ͨ����------��ֵ�豸
	*        ------��ͨ�豸
	*
	***********************************/

	if (m_BPDFCpt)
	{
		
		if (m_BCamera800 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//800W�豸
			//tem_strFileNameΪpdf�ļ���+��׺
			//��ȡԭͼ��������ֵͼ���������PDF��
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //����ͼ���Լ�·��
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}
			
			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 0);
			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath2, tem_strName);    //��������ͼ
			tem_strWholeName = GeneratePDF(tem_strPDFImgPath2, tem_strWholeName);


			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);
			
			DeleteFile(tem_strPDFImgPath1);
			DeleteFile(tem_strPDFImgPath2);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			//��ͨ����ת��ΪPDF�ļ�

		}
		else if (m_BCamera500 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//500W�豸
			//tem_strFileNameΪpdf�ļ���+��׺
			//��ȡԭͼ��������ֵͼ���������PDF��
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //����ͼ���Լ�·��
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}
			
			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 3);
			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath2, tem_strName);    //��������ͼ
			tem_strWholeName = GeneratePDF(tem_strPDFImgPath2, tem_strWholeName);


			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);
			DeleteFile(tem_strPDFImgPath2);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			//��ͨ����ת��ΪPDF�ļ�
		}
		else if (m_BCamera1200 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1200W�豸
			//tem_strFileNameΪpdf�ļ���+��׺
			//��ȡԭͼ��������ֵͼ���������PDF��
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //����ͼ���Լ�·��
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 1);
			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath2, tem_strName);    //��������ͼ
			tem_strWholeName = GeneratePDF(tem_strPDFImgPath2, tem_strWholeName);


			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);
			DeleteFile(tem_strPDFImgPath2);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			//��ͨ����ת��ΪPDF�ļ�
		}
		else if (m_BCamera1300 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1300W�豸
			//tem_strFileNameΪpdf�ļ���+��׺
			//��ȡԭͼ��������ֵͼ���������PDF��
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //����ͼ���Լ�·��
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 2);
			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath2, tem_strName);    //��������ͼ
			tem_strWholeName = GeneratePDF(tem_strPDFImgPath2, tem_strWholeName);


			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);
			DeleteFile(tem_strPDFImgPath2);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			//��ͨ����ת��ΪPDF�ļ�
		}
		else if (m_BCameraTo1500 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1200W�豸
			//tem_strFileNameΪpdf�ļ���+��׺
			//��ȡԭͼ��������ֵͼ���������PDF��
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //����ͼ���Լ�·��
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath1, tem_strName);    //��������ͼ
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath); 
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 4);
			tem_strWholeName = GeneratePDF(tem_strPDFImgPath2, tem_strWholeName);


			     
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);
			DeleteFile(tem_strPDFImgPath2);	
		}
		else if (m_BGS1600 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1300W->1600W�豸
			//tem_strFileNameΪpdf�ļ���+��׺
			//��ȡԭͼ��������ֵͼ���������PDF��
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //����ͼ���Լ�·��
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath1, tem_strName);    //��������ͼ
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath); 
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 5);
			tem_strWholeName = GeneratePDF(tem_strPDFImgPath2, tem_strWholeName);



			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);
			DeleteFile(tem_strPDFImgPath2);	
		}
		else if (m_BCamera200 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//200W->300W�豸
			//tem_strFileNameΪpdf�ļ���+��׺
			//��ȡԭͼ��������ֵͼ���������PDF��
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //����ͼ���Լ�·��
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath1, tem_strName);    //��������ͼ
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath); 
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 6);
			tem_strWholeName = GeneratePDF(tem_strPDFImgPath2, tem_strWholeName);



			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);
			DeleteFile(tem_strPDFImgPath2);	
		}
		else
		{
			//��ͨ�豸
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");                  //����ͼ��ȫ��

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //����ͼ���Լ�·��

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath1, tem_strName);    //��������ͼ
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath); 
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			tem_strWholeName = GeneratePDF(tem_strPDFImgPath1, tem_strWholeName);

			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);


			/*2018-04-12ԭ�����ֵʹ������ͼ��->PDF,�ǲ�ֵ��ʹ��OCX����PDF�������޷��Զ���ת�����ͳһ�޸�Ϊ����ͼ���Լ�����PDF
			m_conVideoOcx.CapturePDF(tem_strWholeName);
			tem_strPDFimgName = ShowPDF(tem_strWholeName);    //pdf�ļ�������ͼ���ļ�
			m_vcFileName.push_back(tem_strName);
			tem_strThumbPath = GetThumbPath(tem_strPDFimgName, tem_strName);    //��������ͼ
			m_vcWholeName.push_back(tem_strThumbPath);      //PDF��������ҳ����ͼ���ַ�������vector
			m_vcBussName.push_back(tem_strWholeName);
			m_vcDeleteBuffer.push_back(tem_strPDFimgName);
			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			*/
		}
		
		
		m_nPDfimg++;
	} 
	else if (m_BBase64Cpt)
	{
		if (m_BCamera800 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//800W�豸
			//ԭͼ����ֵͼ��txt�ļ�
			CString   tem_strImgName1 = tem_strName;     //ԭͼ����
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("TXT");       //��ֵͼ����
			tem_strImgName2 += tem_strName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strTXTImgPath1 = m_strBufferPath + tem_strImgName1;    //ԭͼ��·��+ͼ����
			CString   tem_strTXTImgPath2 = m_strBufferPath + tem_strImgName2;    //��ֵͼ��·��+ͼ����

			m_conVideoOcx.CaptureImage(tem_strTXTImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strTXTImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strTXTImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strTXTImgPath2 = InterPolateImage(tem_strTXTImgPath1, tem_strTXTImgPath2, 0);
			tem_strThumbPath = GetThumbPath(tem_strTXTImgPath2, tem_strName);    //��������ͼ
			tem_strWholeName = GenerateBase64(tem_strTXTImgPath2, tem_strWholeName);

			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      //PDF��������ҳ����ͼ���ַ�������vector
			m_vcBussName.push_back(tem_strWholeName);
			
			DeleteFile(tem_strTXTImgPath1);
			DeleteFile(tem_strTXTImgPath2);

            ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
 			m_nPDfimg++;
		}
		else if (m_BCamera500 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//500W�豸
			//ԭͼ����ֵͼ��txt�ļ�
			CString   tem_strImgName1 = tem_strName;     //ԭͼ����
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("TXT");       //��ֵͼ����
			tem_strImgName2 += tem_strName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strTXTImgPath1 = m_strBufferPath + tem_strImgName1;    //ԭͼ��·��+ͼ����
			CString   tem_strTXTImgPath2 = m_strBufferPath + tem_strImgName2;    //��ֵͼ��·��+ͼ����

			m_conVideoOcx.CaptureImage(tem_strTXTImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strTXTImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strTXTImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strTXTImgPath2 = InterPolateImage(tem_strTXTImgPath1, tem_strTXTImgPath2, 3);
			tem_strThumbPath = GetThumbPath(tem_strTXTImgPath2, tem_strName);    //��������ͼ
			tem_strWholeName = GenerateBase64(tem_strTXTImgPath2, tem_strWholeName);

			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      //PDF��������ҳ����ͼ���ַ�������vector
			m_vcBussName.push_back(tem_strWholeName);

			DeleteFile(tem_strTXTImgPath1);
			DeleteFile(tem_strTXTImgPath2);

			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			m_nPDfimg++;
		}
		else if (m_BCamera1200 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1200W�豸
			//ԭͼ����ֵͼ��txt�ļ�
			CString   tem_strImgName1 = tem_strName;     //ԭͼ����
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("TXT");       //��ֵͼ����
			tem_strImgName2 += tem_strName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strTXTImgPath1 = m_strBufferPath + tem_strImgName1;    //ԭͼ��·��+ͼ����
			CString   tem_strTXTImgPath2 = m_strBufferPath + tem_strImgName2;    //��ֵͼ��·��+ͼ����

			m_conVideoOcx.CaptureImage(tem_strTXTImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strTXTImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strTXTImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strTXTImgPath2 = InterPolateImage(tem_strTXTImgPath1, tem_strTXTImgPath2, 1);
			tem_strThumbPath = GetThumbPath(tem_strTXTImgPath2, tem_strName);    //��������ͼ
			tem_strWholeName = GenerateBase64(tem_strTXTImgPath2, tem_strWholeName);

			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      //PDF��������ҳ����ͼ���ַ�������vector
			m_vcBussName.push_back(tem_strWholeName);

			DeleteFile(tem_strTXTImgPath1);
			DeleteFile(tem_strTXTImgPath2);

			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			m_nPDfimg++;
		}
		else if (m_BCamera1300 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1300W�豸
			//ԭͼ����ֵͼ��txt�ļ�
			CString   tem_strImgName1 = tem_strName;     //ԭͼ����
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("TXT");       //��ֵͼ����
			tem_strImgName2 += tem_strName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strTXTImgPath1 = m_strBufferPath + tem_strImgName1;    //ԭͼ��·��+ͼ����
			CString   tem_strTXTImgPath2 = m_strBufferPath + tem_strImgName2;    //��ֵͼ��·��+ͼ����

			m_conVideoOcx.CaptureImage(tem_strTXTImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strTXTImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strTXTImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strTXTImgPath2 = InterPolateImage(tem_strTXTImgPath1, tem_strTXTImgPath2, 2);
			tem_strThumbPath = GetThumbPath(tem_strTXTImgPath2, tem_strName);    //��������ͼ
			tem_strWholeName = GenerateBase64(tem_strTXTImgPath2, tem_strWholeName);

			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      //PDF��������ҳ����ͼ���ַ�������vector
			m_vcBussName.push_back(tem_strWholeName);

			DeleteFile(tem_strTXTImgPath1);
			DeleteFile(tem_strTXTImgPath2);

			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			m_nPDfimg++;
		}
		else if (m_BCameraTo1500 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1200W�豸
			//ԭͼ����ֵͼ��txt�ļ�
			CString   tem_strImgName1 = tem_strName;     //ԭͼ����
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("TXT");       //��ֵͼ����
			tem_strImgName2 += tem_strName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strTXTImgPath1 = m_strBufferPath + tem_strImgName1;    //ԭͼ��·��+ͼ����
			CString   tem_strTXTImgPath2 = m_strBufferPath + tem_strImgName2;    //��ֵͼ��·��+ͼ����

			m_conVideoOcx.CaptureImage(tem_strTXTImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strTXTImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strTXTImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strThumbPath = GetThumbPath(tem_strTXTImgPath1, tem_strName);    //��������ͼ
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      //PDF��������ҳ����ͼ���ַ�������vector
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			tem_strTXTImgPath2 = InterPolateImage(tem_strTXTImgPath1, tem_strTXTImgPath2, 4);
			
			tem_strWholeName = GenerateBase64(tem_strTXTImgPath2, tem_strWholeName);

			
			m_vcBussName.push_back(tem_strWholeName);

			DeleteFile(tem_strTXTImgPath1);
			DeleteFile(tem_strTXTImgPath2);

			ShowImageSize(tem_strWholeName);
			
			m_nPDfimg++;
		}
		else if (m_BGS1600 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1300W->1600W�豸
			//ԭͼ����ֵͼ��txt�ļ�
			CString   tem_strImgName1 = tem_strName;     //ԭͼ����
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("TXT");       //��ֵͼ����
			tem_strImgName2 += tem_strName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strTXTImgPath1 = m_strBufferPath + tem_strImgName1;    //ԭͼ��·��+ͼ����
			CString   tem_strTXTImgPath2 = m_strBufferPath + tem_strImgName2;    //��ֵͼ��·��+ͼ����

			m_conVideoOcx.CaptureImage(tem_strTXTImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strTXTImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strTXTImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strThumbPath = GetThumbPath(tem_strTXTImgPath1, tem_strName);    //��������ͼ
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      //PDF��������ҳ����ͼ���ַ�������vector
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			tem_strTXTImgPath2 = InterPolateImage(tem_strTXTImgPath1, tem_strTXTImgPath2, 5);

			tem_strWholeName = GenerateBase64(tem_strTXTImgPath2, tem_strWholeName);


			m_vcBussName.push_back(tem_strWholeName);

			DeleteFile(tem_strTXTImgPath1);
			DeleteFile(tem_strTXTImgPath2);

			ShowImageSize(tem_strWholeName);

			m_nPDfimg++;
		}
		else if (m_BCamera200 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//200W->300W�豸
			//ԭͼ����ֵͼ��txt�ļ�
			CString   tem_strImgName1 = tem_strName;     //ԭͼ����
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("TXT");       //��ֵͼ����
			tem_strImgName2 += tem_strName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strTXTImgPath1 = m_strBufferPath + tem_strImgName1;    //ԭͼ��·��+ͼ����
			CString   tem_strTXTImgPath2 = m_strBufferPath + tem_strImgName2;    //��ֵͼ��·��+ͼ����

			m_conVideoOcx.CaptureImage(tem_strTXTImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strTXTImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strTXTImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strThumbPath = GetThumbPath(tem_strTXTImgPath1, tem_strName);    //��������ͼ
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      //PDF��������ҳ����ͼ���ַ�������vector
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			tem_strTXTImgPath2 = InterPolateImage(tem_strTXTImgPath1, tem_strTXTImgPath2, 6);

			tem_strWholeName = GenerateBase64(tem_strTXTImgPath2, tem_strWholeName);


			m_vcBussName.push_back(tem_strWholeName);

			DeleteFile(tem_strTXTImgPath1);
			DeleteFile(tem_strTXTImgPath2);

			ShowImageSize(tem_strWholeName);

			m_nPDfimg++;
		}
		else
		{
			//Base64��������BSTR
			CString  tem_strBaseReturn = m_conVideoOcx.CaptureBase64();
			try
			{
				//�����ļ��Ĵ򿪲���
				CStdioFile  tem_sfOutFile(tem_strWholeName, CFile::modeNoTruncate | 
					CFile::modeCreate | CFile::modeWrite | CFile::typeText);
				//�ļ�β�����¼�¼
				tem_sfOutFile.SeekToEnd();
				tem_sfOutFile.WriteString(tem_strBaseReturn);
				tem_sfOutFile.Close();

				//ͨ��txt�ļ�����ͼ�����Ԥ��
				tem_strTXTimgName = Base642Img(tem_strWholeName);  //�õ�ͼ����

				m_vcFileName.push_back(tem_strName);
				tem_strThumbPath = GetThumbPath(tem_strTXTimgName, tem_strName);    //��������ͼ
				m_vcWholeName.push_back(tem_strThumbPath);      //PDF��������ҳ����ͼ���ַ�������vector
				m_vcBussName.push_back(tem_strWholeName);
				m_vcDeleteBuffer.push_back(tem_strTXTimgName);
				ShowImageSize(tem_strWholeName);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
				m_nPDfimg++;
			}
			catch(CFileException *fx)
			{
				fx->Delete();
			}
		}
		
	} 
	else if (m_BDcmCpt)
	{
		//�����Ի�������DCM��Ϣ------
		m_iChildDcm.DoModal();

		//�ж��Ƿ��������-------------
		if (!m_iChildDcm.m_strDcmInfo.IsEmpty())
		{
			//��Ϣ�ַ�����Ϊ�գ�����
			CString   tem_strDcmInfo = m_iChildDcm.m_strDcmInfo;
			CString   tem_strTemporary;
			int       tem_nSite = -1;

			USES_CONVERSION;

			tem_nSite = tem_strDcmInfo.Find('|');
			if (tem_nSite == -1)
			{
				return;	
			}
			tem_strTemporary = tem_strDcmInfo.Mid(0, tem_nSite);
			tem_strDcmInfo   = tem_strDcmInfo.Mid(tem_nSite+1);
			char*  tem_cName = T2A(tem_strTemporary);

			tem_nSite = tem_strDcmInfo.Find('|');
			if (tem_nSite == -1)
			{
				return;
			}
			tem_strTemporary = tem_strDcmInfo.Mid(0, tem_nSite);
			tem_strDcmInfo   = tem_strDcmInfo.Mid(tem_nSite+1);
			char*  tem_cId = T2A(tem_strTemporary);	

			tem_nSite = tem_strDcmInfo.Find('|');
			if (tem_nSite == -1)
			{
				return;	
			}
			tem_strTemporary = tem_strDcmInfo.Mid(0, tem_nSite);
			tem_strDcmInfo   = tem_strDcmInfo.Mid(tem_nSite+1);
			char*     tem_cBirth = T2A(tem_strTemporary);

			tem_nSite = tem_strDcmInfo.Find('|');
			if (tem_nSite == -1)
			{
				return;	
			}
			tem_strTemporary = tem_strDcmInfo.Mid(0, tem_nSite);
			tem_strDcmInfo   = tem_strDcmInfo.Mid(tem_nSite+1);
			char*     tem_cSex = T2A(tem_strTemporary);

			tem_nSite = tem_strDcmInfo.Find('|');
			if (tem_nSite == -1)
			{
				return;
			}
			tem_strTemporary = tem_strDcmInfo.Mid(0, tem_nSite);
			tem_strDcmInfo   = tem_strDcmInfo.Mid(tem_nSite+1);
			char*     tem_cDName = T2A(tem_strTemporary);	

			tem_nSite = tem_strDcmInfo.Find('|');
			if (tem_nSite == -1)
			{
				return;
			}
			tem_strTemporary = tem_strDcmInfo.Mid(0, tem_nSite);
			tem_strDcmInfo   = tem_strDcmInfo.Mid(tem_nSite+1);
			char*     tem_cDate = T2A(tem_strTemporary);	

			char*     tem_cTime = T2A(tem_strDcmInfo);	

			//DCM��תΪJPG��
			tem_strTemporary = tem_strWholeName;  //.dcm
			tem_nSite        = tem_strTemporary.ReverseFind('.');
			tem_strTemporary = tem_strTemporary.Mid(0, tem_nSite);
			tem_strTemporary+= ".jpg";
		//	tem_strTemporary+= ".bmp";


			if (m_BCamera800 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//800W�豸
				CString     tem_strSrcImg = m_strBufferPath;
				tem_strSrcImg += tem_strName;                               //ԭ�ߴ�ͼ��
				tem_strSrcImg += _T(".jpg");	

				m_conVideoOcx.CaptureImage(tem_strSrcImg);             //����ԭͼ
				//�Զ���ת--------------------------------------------
				Self_RecognizeOrit(tem_strSrcImg, m_BAutoRotate);
				//�ĵ��Ż�--------------------------------------------
				if (m_BOptimize)
				{
					CxImage   tem_cxSrcImg;
					tem_cxSrcImg.Load(tem_strSrcImg, CMAX_IMAGE_FORMATS);

					float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


					if (tem_fColorPer>=m_fColorPercentage)
					{
						//��ɫͼ��
						Self_DocOptimize(tem_cxSrcImg, tem_strSrcImg, m_BOptimize, m_nOptBright, m_nOptContrast);
					} 
					else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
					{
						//�ڰ�ͼ��
						Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImg, m_BOptimize);
					}
					//����Ϊ��ֵͼ�񣬲����Ż�
				}

				tem_strTemporary = InterPolateImage(tem_strSrcImg, tem_strTemporary, 0);
				m_vcFileName.push_back(tem_strName);
				tem_strThumbPath = GetThumbPath(tem_strTemporary, tem_strName);    //��������ͼ
				m_vcWholeName.push_back(tem_strThumbPath);                         //��ʾ����ͼ
				m_vcDeleteBuffer.push_back(tem_strTemporary);

				DeleteFile(tem_strSrcImg);

			}
			else if (m_BCamera500 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//500W�豸
				CString     tem_strSrcImg = m_strBufferPath;
				tem_strSrcImg += tem_strName;                               //ԭ�ߴ�ͼ��
				tem_strSrcImg += _T(".jpg");	

				m_conVideoOcx.CaptureImage(tem_strSrcImg);             //����ԭͼ
				//�Զ���ת--------------------------------------------
				Self_RecognizeOrit(tem_strSrcImg, m_BAutoRotate);
				//�ĵ��Ż�--------------------------------------------
				if (m_BOptimize)
				{
					CxImage   tem_cxSrcImg;
					tem_cxSrcImg.Load(tem_strSrcImg, CMAX_IMAGE_FORMATS);

					float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


					if (tem_fColorPer>=m_fColorPercentage)
					{
						//��ɫͼ��
						Self_DocOptimize(tem_cxSrcImg, tem_strSrcImg, m_BOptimize, m_nOptBright, m_nOptContrast);
					} 
					else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
					{
						//�ڰ�ͼ��
						Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImg, m_BOptimize);
					}
					//����Ϊ��ֵͼ�񣬲����Ż�
				}

				tem_strTemporary = InterPolateImage(tem_strSrcImg, tem_strTemporary, 3);
				m_vcFileName.push_back(tem_strName);
				tem_strThumbPath = GetThumbPath(tem_strTemporary, tem_strName);    //��������ͼ
				m_vcWholeName.push_back(tem_strThumbPath);                         //��ʾ����ͼ
				m_vcDeleteBuffer.push_back(tem_strTemporary);

				DeleteFile(tem_strSrcImg);

			}
			else if (m_BCamera1200 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1200W�豸
				CString     tem_strSrcImg = m_strBufferPath;
				tem_strSrcImg += tem_strName;                               //ԭ�ߴ�ͼ��
				tem_strSrcImg += _T(".jpg");	

				m_conVideoOcx.CaptureImage(tem_strSrcImg);             //����ԭͼ
				//�Զ���ת--------------------------------------------
				Self_RecognizeOrit(tem_strSrcImg, m_BAutoRotate);
				//�ĵ��Ż�--------------------------------------------
				if (m_BOptimize)
				{
					CxImage   tem_cxSrcImg;
					tem_cxSrcImg.Load(tem_strSrcImg, CMAX_IMAGE_FORMATS);

					float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


					if (tem_fColorPer>=m_fColorPercentage)
					{
						//��ɫͼ��
						Self_DocOptimize(tem_cxSrcImg, tem_strSrcImg, m_BOptimize, m_nOptBright, m_nOptContrast);
					} 
					else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
					{
						//�ڰ�ͼ��
						Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImg, m_BOptimize);
					}
					//����Ϊ��ֵͼ�񣬲����Ż�
				}

				tem_strTemporary = InterPolateImage(tem_strSrcImg, tem_strTemporary, 1);
				m_vcFileName.push_back(tem_strName);
				tem_strThumbPath = GetThumbPath(tem_strTemporary, tem_strName);    //��������ͼ
				m_vcWholeName.push_back(tem_strThumbPath);                         //��ʾ����ͼ
				m_vcDeleteBuffer.push_back(tem_strTemporary);

				DeleteFile(tem_strSrcImg);

			}
			else if (m_BCamera1300 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1300W�豸
				CString     tem_strSrcImg = m_strBufferPath;
				tem_strSrcImg += tem_strName;                               //ԭ�ߴ�ͼ��
				tem_strSrcImg += _T(".jpg");	

				m_conVideoOcx.CaptureImage(tem_strSrcImg);             //����ԭͼ
				//�Զ���ת--------------------------------------------
				Self_RecognizeOrit(tem_strSrcImg, m_BAutoRotate);
				//�ĵ��Ż�--------------------------------------------
				if (m_BOptimize)
				{
					CxImage   tem_cxSrcImg;
					tem_cxSrcImg.Load(tem_strSrcImg, CMAX_IMAGE_FORMATS);

					float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


					if (tem_fColorPer>=m_fColorPercentage)
					{
						//��ɫͼ��
						Self_DocOptimize(tem_cxSrcImg, tem_strSrcImg, m_BOptimize, m_nOptBright, m_nOptContrast);
					} 
					else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
					{
						//�ڰ�ͼ��
						Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImg, m_BOptimize);
					}
					//����Ϊ��ֵͼ�񣬲����Ż�
				}

				tem_strThumbPath = GetThumbPath(tem_strSrcImg, tem_strName);    //��������ͼ
				tem_strTemporary = InterPolateImage(tem_strSrcImg, tem_strTemporary, 2);
				m_vcFileName.push_back(tem_strName);
				
				m_vcWholeName.push_back(tem_strThumbPath);                         //��ʾ����ͼ
				m_vcDeleteBuffer.push_back(tem_strTemporary);

				DeleteFile(tem_strSrcImg);

			}
			else if (m_BCameraTo1500 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1200W�豸
				CString     tem_strSrcImg = m_strBufferPath;
				tem_strSrcImg += tem_strName;                               //ԭ�ߴ�ͼ��
				tem_strSrcImg += _T(".jpg");	

				m_conVideoOcx.CaptureImage(tem_strSrcImg);             //����ԭͼ
				//�Զ���ת--------------------------------------------
				Self_RecognizeOrit(tem_strSrcImg, m_BAutoRotate);
				//�ĵ��Ż�--------------------------------------------
				if (m_BOptimize)
				{
					CxImage   tem_cxSrcImg;
					tem_cxSrcImg.Load(tem_strSrcImg, CMAX_IMAGE_FORMATS);

					float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


					if (tem_fColorPer>=m_fColorPercentage)
					{
						//��ɫͼ��
						Self_DocOptimize(tem_cxSrcImg, tem_strSrcImg, m_BOptimize, m_nOptBright, m_nOptContrast);
					} 
					else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
					{
						//�ڰ�ͼ��
						Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImg, m_BOptimize);
					}
					//����Ϊ��ֵͼ�񣬲����Ż�
				}

				m_vcFileName.push_back(tem_strName);
				tem_strThumbPath = GetThumbPath(tem_strSrcImg, tem_strName);    //��������ͼ
				tem_strTemporary = InterPolateImage(tem_strSrcImg, tem_strTemporary, 4);
				m_vcWholeName.push_back(tem_strThumbPath);                         //��ʾ����ͼ
				m_vcDeleteBuffer.push_back(tem_strTemporary);
				DeleteFile(tem_strSrcImg);
			}
			else if (m_BGS1600 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1300W->1600W�豸
				CString     tem_strSrcImg = m_strBufferPath;
				tem_strSrcImg += tem_strName;                               //ԭ�ߴ�ͼ��
				tem_strSrcImg += _T(".jpg");	

				m_conVideoOcx.CaptureImage(tem_strSrcImg);             //����ԭͼ
				//�Զ���ת--------------------------------------------
				Self_RecognizeOrit(tem_strSrcImg, m_BAutoRotate);
				//�ĵ��Ż�--------------------------------------------
				if (m_BOptimize)
				{
					CxImage   tem_cxSrcImg;
					tem_cxSrcImg.Load(tem_strSrcImg, CMAX_IMAGE_FORMATS);

					float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


					if (tem_fColorPer>=m_fColorPercentage)
					{
						//��ɫͼ��
						Self_DocOptimize(tem_cxSrcImg, tem_strSrcImg, m_BOptimize, m_nOptBright, m_nOptContrast);
					} 
					else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
					{
						//�ڰ�ͼ��
						Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImg, m_BOptimize);
					}
					//����Ϊ��ֵͼ�񣬲����Ż�
				}

				m_vcFileName.push_back(tem_strName);
				tem_strThumbPath = GetThumbPath(tem_strSrcImg, tem_strName);    //��������ͼ
				tem_strTemporary = InterPolateImage(tem_strSrcImg, tem_strTemporary, 5);
				m_vcWholeName.push_back(tem_strThumbPath);                         //��ʾ����ͼ
				m_vcDeleteBuffer.push_back(tem_strTemporary);
				DeleteFile(tem_strSrcImg);
			}
			else if (m_BCamera200 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//200W->300W�豸
				CString     tem_strSrcImg = m_strBufferPath;
				tem_strSrcImg += tem_strName;                               //ԭ�ߴ�ͼ��
				tem_strSrcImg += _T(".jpg");	

				m_conVideoOcx.CaptureImage(tem_strSrcImg);             //����ԭͼ
				//�Զ���ת--------------------------------------------
				Self_RecognizeOrit(tem_strSrcImg, m_BAutoRotate);
				//�ĵ��Ż�--------------------------------------------
				if (m_BOptimize)
				{
					CxImage   tem_cxSrcImg;
					tem_cxSrcImg.Load(tem_strSrcImg, CMAX_IMAGE_FORMATS);

					float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


					if (tem_fColorPer>=m_fColorPercentage)
					{
						//��ɫͼ��
						Self_DocOptimize(tem_cxSrcImg, tem_strSrcImg, m_BOptimize, m_nOptBright, m_nOptContrast);
					} 
					else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
					{
						//�ڰ�ͼ��
						Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImg, m_BOptimize);
					}
					//����Ϊ��ֵͼ�񣬲����Ż�
				}

				m_vcFileName.push_back(tem_strName);
				tem_strThumbPath = GetThumbPath(tem_strSrcImg, tem_strName);    //��������ͼ
				tem_strTemporary = InterPolateImage(tem_strSrcImg, tem_strTemporary, 6);
				m_vcWholeName.push_back(tem_strThumbPath);                         //��ʾ����ͼ
				m_vcDeleteBuffer.push_back(tem_strTemporary);
				DeleteFile(tem_strSrcImg);
			}
			else
			{
				//����bmpͼ��--------------
				m_conVideoOcx.CaptureImage(tem_strTemporary);
				//�Զ���ת--------------------------------------------
				Self_RecognizeOrit(tem_strTemporary, m_BAutoRotate);
				//�ĵ��Ż�--------------------------------------------
				if (m_BOptimize)
				{
					CxImage   tem_cxSrcImg;
					tem_cxSrcImg.Load(tem_strTemporary, CMAX_IMAGE_FORMATS);

					float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


					if (tem_fColorPer>=m_fColorPercentage)
					{
						//��ɫͼ��
						Self_DocOptimize(tem_cxSrcImg, tem_strTemporary, m_BOptimize, m_nOptBright, m_nOptContrast);
					} 
					else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
					{
						//�ڰ�ͼ��
						Self_DocOptimize2(tem_cxSrcImg, tem_strTemporary, m_BOptimize);
					}
					//����Ϊ��ֵͼ�񣬲����Ż�
				}

				m_vcFileName.push_back(tem_strName);
				tem_strThumbPath = GetThumbPath(tem_strTemporary, tem_strName);    //��������ͼ
				m_vcWholeName.push_back(tem_strThumbPath);                         //��ʾ����ͼ
				m_vcDeleteBuffer.push_back(tem_strTemporary);
			}
			


			//תJPGͼ��ΪDCMͼ��--------
			IMAGEAndDCM*   tem_dcm = new IMAGEAndDCM;
			tem_dcm->Set(tem_cName, tem_cId, tem_cBirth, tem_cSex, tem_cDName, tem_cDate, tem_cTime);

			char*  tem_cSrc = T2A(tem_strTemporary);
			char*  tem_cDst = T2A(tem_strWholeName);
//			tem_dcm->SaveJPGtoDCM(tem_cSrc, tem_cDst);
//			tem_dcm->SaveBMPtoDCM(tem_cSrc, tem_cDst);
			tem_dcm->SaveIMAGEtoDCM(tem_cSrc, tem_cDst);


			m_vcBussName.push_back(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			
		} 
		else
		{
			//��Ϣ�ַ���Ϊ�գ�ȡ������
			return;
		}
	}
	else if (m_BOfdCpt)
	{
		if (m_BCamera800 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//800W�豸
			//tem_strFileNameΪpdf�ļ���+��׺
			//��ȡԭͼ��������ֵͼ���������PDF��
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //����ͼ���Լ�·��
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}
			
			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 0);
			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath2, tem_strName);    //��������ͼ
			tem_strWholeName = GenerateOFD(tem_strPDFImgPath2, tem_strWholeName); 


			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);
			
			DeleteFile(tem_strPDFImgPath1);
//			DeleteFile(tem_strPDFImgPath2);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			//��ͨ����ת��ΪPDF�ļ�

		}
		else if (m_BCamera500 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//500W�豸
			//tem_strFileNameΪpdf�ļ���+��׺
			//��ȡԭͼ��������ֵͼ���������PDF��
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //����ͼ���Լ�·��
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}
			
			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 3);
			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath2, tem_strName);    //��������ͼ
			tem_strWholeName = GenerateOFD(tem_strPDFImgPath2, tem_strWholeName);


			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);
//			DeleteFile(tem_strPDFImgPath2);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			//��ͨ����ת��ΪPDF�ļ�
		}
		else if (m_BCamera1200 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1200W�豸
			//tem_strFileNameΪpdf�ļ���+��׺
			//��ȡԭͼ��������ֵͼ���������PDF��
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //����ͼ���Լ�·��
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 1);
			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath2, tem_strName);    //��������ͼ
			tem_strWholeName = GenerateOFD(tem_strPDFImgPath2, tem_strWholeName);


			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);
//			DeleteFile(tem_strPDFImgPath2);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			//��ͨ����ת��ΪPDF�ļ�
		}
		else if (m_BCamera1300 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1300W�豸
			//tem_strFileNameΪpdf�ļ���+��׺
			//��ȡԭͼ��������ֵͼ���������PDF��
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //����ͼ���Լ�·��
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 2);
			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath2, tem_strName);    //��������ͼ
			tem_strWholeName = GenerateOFD(tem_strPDFImgPath2, tem_strWholeName);


			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);
//			DeleteFile(tem_strPDFImgPath2);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			//��ͨ����ת��ΪPDF�ļ�
		}
		else if (m_BCameraTo1500 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1200W�豸
			//tem_strFileNameΪpdf�ļ���+��׺
			//��ȡԭͼ��������ֵͼ���������PDF��
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //����ͼ���Լ�·��
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath1, tem_strName);    //��������ͼ
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath); 
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 4);
			tem_strWholeName = GenerateOFD(tem_strPDFImgPath2, tem_strWholeName);


			     
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);
//			DeleteFile(tem_strPDFImgPath2);	
		}
		else if (m_BGS1600 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1300W->1600W�豸
			//tem_strFileNameΪpdf�ļ���+��׺
			//��ȡԭͼ��������ֵͼ���������PDF��
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //����ͼ���Լ�·��
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath1, tem_strName);    //��������ͼ
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath); 
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 5);
			tem_strWholeName = GenerateOFD(tem_strPDFImgPath2, tem_strWholeName);

			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);
//			DeleteFile(tem_strPDFImgPath2);	
		}
		else if (m_BCamera200 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//200W->300W�豸
			//tem_strFileNameΪpdf�ļ���+��׺
			//��ȡԭͼ��������ֵͼ���������PDF��
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //����ͼ���Լ�·��
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath1, tem_strName);    //��������ͼ
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath); 
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 6);
			tem_strWholeName = GenerateOFD(tem_strPDFImgPath2, tem_strWholeName);

			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);
		}
		else
		{
			//��ͨ�豸
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");                  //����ͼ��ȫ��

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //����ͼ���Լ�·��

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath1, tem_strName);    //��������ͼ
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath); 
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			tem_strWholeName = GenerateOFD(tem_strPDFImgPath1, tem_strWholeName);

			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

//			DeleteFile(tem_strPDFImgPath1);

		}
		
		
		m_nPDfimg++;

	}
	else
	{
		//JPEG��TIF��PNG��BMP
//		MessageBox(tem_strWholeName);
		if (m_BCamera800 && m_nLastUsedResolu == m_nInterpolateReso)
		{
			//800W�豸
			m_conVideoOcx.CaptureImage(tem_strSrcImageName);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strSrcImageName, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 0);
			DeleteFile(tem_strSrcImageName);
			m_vcFileName.push_back(tem_strName);
			tem_strThumbPath = GetThumbPath(tem_strWholeName, tem_strName);    //��������ͼ
			m_vcWholeName.push_back(tem_strThumbPath);                         //�洢����ͼ��������ʾ
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
		}
		else if (m_BCamera500 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//500W
			m_conVideoOcx.CaptureImage(tem_strSrcImageName);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strSrcImageName, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 3);
			DeleteFile(tem_strSrcImageName);
			m_vcFileName.push_back(tem_strName);
			tem_strThumbPath = GetThumbPath(tem_strWholeName, tem_strName);    //��������ͼ
			m_vcWholeName.push_back(tem_strThumbPath);                         //�洢����ͼ��������ʾ
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
		}
		else if (m_BCamera1200 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1200W
			m_conVideoOcx.CaptureImage(tem_strSrcImageName);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strSrcImageName, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 1);
			DeleteFile(tem_strSrcImageName);
			m_vcFileName.push_back(tem_strName);
			tem_strThumbPath = GetThumbPath(tem_strWholeName, tem_strName);    //��������ͼ
			m_vcWholeName.push_back(tem_strThumbPath);                         //�洢����ͼ��������ʾ
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
		}
		else if (m_BCamera1300 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1300W
			m_conVideoOcx.CaptureImage(tem_strSrcImageName);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strSrcImageName, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			m_vcFileName.push_back(tem_strName);
			tem_strThumbPath = GetThumbPath(tem_strSrcImageName, tem_strName);    //��������ͼ
			tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 2);
			DeleteFile(tem_strSrcImageName);
			
			m_vcWholeName.push_back(tem_strThumbPath);                         //�洢����ͼ��������ʾ
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
		}
		else if (m_BCameraTo1500 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1200W
			m_conVideoOcx.CaptureImage(tem_strSrcImageName);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strSrcImageName, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strThumbPath = GetThumbPath(tem_strSrcImageName, tem_strName);    //��������ͼ
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);                            //�洢����ͼ��������ʾ
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 4);
			DeleteFile(tem_strSrcImageName);
			
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);
			
		}
		else if (m_BGS1600 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1300W->1600W
			m_conVideoOcx.CaptureImage(tem_strSrcImageName);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strSrcImageName, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strThumbPath = GetThumbPath(tem_strSrcImageName, tem_strName);    //��������ͼ
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);                            //�洢����ͼ��������ʾ
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 5);
			DeleteFile(tem_strSrcImageName);

			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

		}
		else if (m_BCamera200 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//200W->300W
			m_conVideoOcx.CaptureImage(tem_strSrcImageName);
			//�Զ���ת--------------------------------------------
			Self_RecognizeOrit(tem_strSrcImageName, m_BAutoRotate);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}

			tem_strThumbPath = GetThumbPath(tem_strSrcImageName, tem_strName);    //��������ͼ
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);                            //�洢����ͼ��������ʾ
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 6);
			DeleteFile(tem_strSrcImageName);

			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

		}
		else
		{
			//��ͨ�豸
			m_conVideoOcx.CaptureImage(tem_strWholeName);

			//�Զ���ת--------------------------------------------
//			DWORD  tem_dBegin = GetTickCount();
			if (m_nAutoRotateMode == 0)
			{
				Self_RecognizeOrit(tem_strWholeName, m_BAutoRotate);
			} 
			else
			{
				Self_RecognizeOrit2(tem_strWholeName, tem_strThumFile, m_BAutoRotate);
			}	
// 			DWORD tem_dEnd = GetTickCount();
// 			CString str;
// 			str.Format(_T("%d"), (tem_dEnd-tem_dBegin));
// 			MessageBox(str);
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strWholeName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strWholeName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strWholeName, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}
			
//			Self_DocOptimize(tem_strWholeName, m_BOptimize, m_nOptBright, m_nOptContrast);
//			Self_DocOptimize2(tem_strWholeName, m_BOptimize);

			m_vcFileName.push_back(tem_strName);
			tem_strThumbPath = GetThumbPath(tem_strWholeName, tem_strName);    //��������ͼ
			m_vcWholeName.push_back(tem_strThumbPath);                         //�洢����ͼ��������ʾ
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
		}
		
		
	}
	m_nImageCount++;
	m_nNamingCount++;
	//�����²�ҳ����ʾ
	int       tem_nPageNumber;
	CString   tem_strPageNumber;
	tem_nPageNumber = m_nImageCount + m_nImageCountOther;
	tem_strPageNumber.Format(_T("%d"), tem_nPageNumber);
	GetDlgItem(IDC_STA_NUMBER)->SetWindowText(tem_strPageNumber);


	CRect rtlbl; 
	GetDlgItem(IDC_STA_NUMBER)->GetWindowRect(&rtlbl); 
	ScreenToClient(&rtlbl); //ת���ͻ��˽���
	InvalidateRect(&rtlbl);//���ˢ�¶Ի��򱳾� 
	UpdateWindow();

// 	CPaintDC  tem_dc(this);
// 	tem_dc.FillSolidRect(rtlbl, RGB(0, 0, 0));
// 	
// 	tem_dc.BitBlt(0, 0, rtlbl.Width(), rtlbl.Height(), &Image, 0, 0, SRCCOPY);
// 	
}


//��֤�ȶ�
void CUDSSmartCamerav100Dlg::OnBnClickedBtnFaceid()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	//1������------------------------------------------------------------------
	CString   tem_strName      = _T("");   //�޺�׺
	CString   tem_strFileName  = _T("");   //����׺
	CString   tem_strWholeName = _T("");   //��·��,ͼ���ļ�
	CString   tem_strThumbPath = _T("");   //����ͼ·��

	if (m_BSoundOpen)
	{
		sndPlaySound(_T("CameraSound.WAV"), NULL);
	}

	tem_strName      = NamingFile(3);
	if (m_BPDFCpt || m_BBase64Cpt || m_BDcmCpt || m_BOfdCpt)
	{
		tem_strFileName  = tem_strName + _T(".jpg");
	} 
	else
	{
		tem_strFileName  = tem_strName + m_strFileFormat;
	}
	tem_strWholeName = m_strFaceDoc + tem_strFileName;
	m_conVideoOcx.CaptureImage(tem_strWholeName);
	g_strFaceImg = tem_strWholeName;
	//�����������棬��Ĭ�϶�һ�ο�
//	m_dlgFaceID.DoModal();
	m_dlgFaceID.Create(IDD_DLG_FACEID, this);
	m_dlgFaceID.ShowWindow(SW_SHOWNORMAL);

	GetDlgItem(IDC_LIST_IMAGE)->GetWindowRect(&m_rcOCX);
	m_dlgFaceID.MoveWindow(m_rcOCX.left-150, m_rcOCX.top+30, m_rcOCX.Width()+150, m_rcOCX.Height()-70, TRUE);

// 	::DeleteFile(g_strFaceImg);
// 	g_strFaceImg = _T("");
	

}


//����ʶ��
void CUDSSmartCamerav100Dlg::OnBnClickedBtnCapbar()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int       tem_nFormat = 0;
	CString   tem_strDocPath    = m_strDefaultPath;
	CString   tem_strFileFormat = m_strFileFormat;
	CString   tem_strSrcImagePath = m_strBufferPath;   //��ֵԭͼĿ¼
	//�ж��ļ���ʽ��Ϊjpg, bmp, tif, png������Ӧ�ĸ�ʽ�� ��Ϊpdf��baseֱ�Ӵ���jpg,������Ӱ����ͨ����
	int  tem_nIndexJpg = tem_strFileFormat.Find(_T("jpg"));
	int  tem_nIndexBmp = tem_strFileFormat.Find(_T("bmp"));
	int  tem_nIndexPng = tem_strFileFormat.Find(_T("png"));
	int  tem_nIndexTif = tem_strFileFormat.Find(_T("tif"));
	
	if (tem_nIndexJpg != -1)
	{
		tem_nFormat = 0;
	}
	else if (tem_nIndexBmp != -1)
	{
		tem_nFormat = 1;
	}
	else if (tem_nIndexPng != -1)
	{
		tem_nFormat = 2;
	} 
	else if (tem_nIndexTif != -1)
	{
		tem_nFormat = 3;
	}
	else
	{
		//����ʽ��ΪJPG��ͬʱע����ʾ�б���Ӧ�޸�
		tem_nFormat     = 0;
		m_strFileFormat = ".jpg";  //��PDF��Base64����������޸ĺ�׺
		m_iChildNor.m_conComFilemode.SetCurSel(1);
	}

	if (m_BSoundOpen)
	{
		sndPlaySound(_T("CameraSound.WAV"), NULL);
	}

	if (m_BCamera800 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		m_conVideoOcx.CaptureBarcode(tem_strSrcImagePath, tem_nFormat);
	}
	else if (m_BCamera500 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		m_conVideoOcx.CaptureBarcode(tem_strSrcImagePath, tem_nFormat);
	}
	else if (m_BCamera1200 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		m_conVideoOcx.CaptureBarcode(tem_strSrcImagePath, tem_nFormat);
	}
	else if (m_BCamera1300 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		m_conVideoOcx.CaptureBarcode(tem_strSrcImagePath, tem_nFormat);
	}
	else if (m_BCameraTo1500 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		m_conVideoOcx.CaptureBarcode(tem_strSrcImagePath, tem_nFormat);
	}
	else if (m_BGS1600 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		m_conVideoOcx.CaptureBarcode(tem_strSrcImagePath, tem_nFormat);
	}
	else if (m_BCamera200 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		m_conVideoOcx.CaptureBarcode(tem_strSrcImagePath, tem_nFormat);
	}
	else
	{
		m_conVideoOcx.CaptureBarcode(tem_strDocPath, tem_nFormat);
	}
	
	

	m_nImageCountOther++;
	//�����²�ҳ����ʾ
	int       tem_nPageNumber;
	CString   tem_strPageNumber;
	tem_nPageNumber = m_nImageCount + m_nImageCountOther;
	tem_strPageNumber.Format(_T("%d"), tem_nPageNumber);
	GetDlgItem(IDC_STA_NUMBER)->SetWindowText(tem_strPageNumber);

	CRect rtlbl; 
	GetDlgItem(IDC_STA_NUMBER)->GetWindowRect(&rtlbl); 
	ScreenToClient(&rtlbl); //ת���ͻ��˽���
	InvalidateRect(&rtlbl);//���ˢ�¶Ի��򱳾� 
	UpdateWindow();
	//���ļ������ļ�·����ӵ�vector��������ʾ,���¼���
}


//������ϲ�
void CUDSSmartCamerav100Dlg::OnBnClickedBtnCap2side()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for(int i=0; i<2; i++)
	{
		CString   tem_strName;      //�޺�׺�ļ���
		CString   tem_strFileName;  //�к�׺�ļ���
		CString   tem_strWholeName; //��·���ļ���
		CString   tem_strThumbPath; //����ͼ·��
		CString   tem_strSrcImageName; //��ֵԭͼ

		//	tem_strFileName.Format(_T("%d"), m_nImageCount);

		//�жϵ�ǰ�Ƿ�ΪPDF��Base64��ʽ����Ϊ�����ָ�ʽ�޸�ΪĬ��jpg
		if (m_BPDFCpt || m_BBase64Cpt || m_BPDFCpt || m_BOfdCpt)
		{
			m_strFileFormat = ".jpg";
			m_iChildNor.m_conComFilemode.SetCurSel(1);
		}

		tem_strName      = NamingFile(m_nNamingMode);
		tem_strFileName  = tem_strName + m_strFileFormat;
		tem_strWholeName = m_strDefaultPath + tem_strFileName;
		tem_strSrcImageName = m_strBufferPath + tem_strFileName;

		long  tem_lReturn;

		if (m_BSoundOpen)
		{
			sndPlaySound(_T("CameraSound.WAV"), NULL);
		}

		if (m_BCamera800 && m_nLastUsedResolu == m_nInterpolateReso)
		{
			tem_lReturn = m_conVideoOcx.CaptureCombine(tem_strSrcImageName);    //���ϲ����ͼ�����ת��
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}
		}
		else if (m_BCamera500 && m_nLastUsedResolu == m_nInterpolateReso)
		{
			tem_lReturn = m_conVideoOcx.CaptureCombine(tem_strSrcImageName);    //���ϲ����ͼ�����ת��
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}
		}
		else if (m_BCamera1200 && m_nLastUsedResolu == m_nInterpolateReso)
		{
			tem_lReturn = m_conVideoOcx.CaptureCombine(tem_strSrcImageName);    //���ϲ����ͼ�����ת��
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}
		}
		else if (m_BCamera1300 && m_nLastUsedResolu == m_nInterpolateReso)
		{
			tem_lReturn = m_conVideoOcx.CaptureCombine(tem_strSrcImageName);    //���ϲ����ͼ�����ת��
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}
		}
		else if (m_BCameraTo1500 && m_nLastUsedResolu == m_nInterpolateReso)
		{
			tem_lReturn = m_conVideoOcx.CaptureCombine(tem_strSrcImageName);    //���ϲ����ͼ�����ת��
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}
		}
		else if(m_BGS1600 && m_nLastUsedResolu == m_nInterpolateReso)
		{
			tem_lReturn = m_conVideoOcx.CaptureCombine(tem_strSrcImageName);    //���ϲ����ͼ�����ת��
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}
		}
		else if(m_BCamera200 && m_nLastUsedResolu == m_nInterpolateReso)
		{
			tem_lReturn = m_conVideoOcx.CaptureCombine(tem_strSrcImageName);    //���ϲ����ͼ�����ת��
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}
		}
		else
		{
			tem_lReturn = m_conVideoOcx.CaptureCombine(tem_strWholeName);    //���ϲ����ͼ�����ת��
			//�ĵ��Ż�--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strWholeName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//��ɫͼ��
					Self_DocOptimize(tem_cxSrcImg, tem_strWholeName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//�ڰ�ͼ��
					Self_DocOptimize2(tem_cxSrcImg, tem_strWholeName, m_BOptimize);
				}
				//����Ϊ��ֵͼ�񣬲����Ż�
			}
		}
		
		
	
		if (tem_lReturn == 0)
		{
			if (m_BCamera800 && m_nLastUsedResolu == m_nInterpolateReso)
			{
				//800W�豸
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 0);
				DeleteFile(tem_strSrcImageName);
			}
			else if (m_BCamera500 && m_nLastUsedResolu == m_nInterpolateReso)
			{
				//500W�豸
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 3);
				DeleteFile(tem_strSrcImageName);
			}
			else if (m_BCamera1200 && m_nLastUsedResolu == m_nInterpolateReso)
			{
				//1200W�豸
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 1);
				DeleteFile(tem_strSrcImageName);
			}
			else if (m_BCamera1300 && m_nLastUsedResolu == m_nInterpolateReso)
			{
				//1300W�豸
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 2);
				DeleteFile(tem_strSrcImageName);
			}
			else if (m_BCameraTo1500 && m_nLastUsedResolu == m_nInterpolateReso)
			{
				//1200W�豸
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 4);
				DeleteFile(tem_strSrcImageName);
			}
			else if (m_BGS1600 && m_nLastUsedResolu == m_nInterpolateReso)
			{
				//1300W->1600W�豸
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 5);
				DeleteFile(tem_strSrcImageName);
			}
			else if (m_BCamera200 && m_nLastUsedResolu == m_nInterpolateReso)
			{
				//200W->300W�豸
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 6);
				DeleteFile(tem_strSrcImageName);
			}

			m_vcFileName.push_back(tem_strName);
			tem_strThumbPath = GetThumbPath(tem_strWholeName, tem_strName);    //��������ͼ
			m_vcWholeName.push_back(tem_strThumbPath);
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			m_nImageCount++;
			m_nNamingCount++;
			//�����²�ҳ����ʾ
			int       tem_nPageNumber;
			CString   tem_strPageNumber;
			tem_nPageNumber = m_nImageCount + m_nImageCountOther;
			tem_strPageNumber.Format(_T("%d"), tem_nPageNumber);
			GetDlgItem(IDC_STA_NUMBER)->SetWindowText(tem_strPageNumber);

			CRect rtlbl; 
			GetDlgItem(IDC_STA_NUMBER)->GetWindowRect(&rtlbl); 
			ScreenToClient(&rtlbl); //ת���ͻ��˽���
			InvalidateRect(&rtlbl);//���ˢ�¶Ի��򱳾� 
			UpdateWindow();
		}
		else
		{
			// 		MessageBox(_T("������ĵ����棬���ٴε�����ϲ����ա���ť��"));
			MessageBox(_T("������ĵ����棬�����ȷ������ť��ɺϲ����գ�"),_T("������ϲ�����"),MB_OK);
		}
	}
}


//�Զ�����
void CUDSSmartCamerav100Dlg::OnBnClickedBtnCapgoon()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int       tem_nFormat = 0;
	CString   tem_strDocPath    = m_strDefaultPath;
	tem_strDocPath = tem_strDocPath.Left(tem_strDocPath.GetLength()-1);
	CString   tem_strFileFormat = m_strFileFormat;
	CString   tem_strSrcImagePath = m_strBufferPath;   //��ֵԭͼĿ¼
	//�ж��ļ���ʽ��Ϊjpg, bmp, tif, png������Ӧ�ĸ�ʽ�� ��Ϊpdf��baseֱ�Ӵ���jpg,������Ӱ����ͨ����
	int  tem_nIndexJpg = tem_strFileFormat.Find(_T("jpg"));
	int  tem_nIndexBmp = tem_strFileFormat.Find(_T("bmp"));
	int  tem_nIndexPng = tem_strFileFormat.Find(_T("png"));
	int  tem_nIndexTif = tem_strFileFormat.Find(_T("tif"));

	if (tem_nIndexJpg != -1)
	{
		tem_nFormat = 0;
	}
	else if (tem_nIndexBmp != -1)
	{
		tem_nFormat = 1;
	}
	else if (tem_nIndexPng != -1)
	{
		tem_nFormat = 2;
	} 
	else if (tem_nIndexTif != -1)
	{
		tem_nFormat = 3;
	}
	else
	{
		tem_nFormat = 0;
		m_strFileFormat = ".jpg";  //��PDF��Base64����������޸ĺ�׺
		m_iChildNor.m_conComFilemode.SetCurSel(1);
	}
	m_iChildNor.m_chkAutoCrt.SetCheck(TRUE);  //�����Զ�����������

	if (m_BCamera800 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		m_conVideoOcx.AutomaticCapture(tem_strSrcImagePath, tem_nFormat);
	}
	else if (m_BCamera500 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		m_conVideoOcx.AutomaticCapture(tem_strSrcImagePath, tem_nFormat);
	}
	else if (m_BCamera1200 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		m_conVideoOcx.AutomaticCapture(tem_strSrcImagePath, tem_nFormat);
	}
	else if (m_BCamera1300 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		m_conVideoOcx.AutomaticCapture(tem_strSrcImagePath, tem_nFormat);
	}
	else if (m_BCameraTo1500 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		m_conVideoOcx.AutomaticCapture(tem_strSrcImagePath, tem_nFormat);
	}
	else if (m_BGS1600 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		m_conVideoOcx.AutomaticCapture(tem_strSrcImagePath, tem_nFormat);
	}
	else if (m_BCamera200 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		m_conVideoOcx.AutomaticCapture(tem_strSrcImagePath, tem_nFormat);
	}
	else
	{
		m_conVideoOcx.AutomaticCapture(tem_strDocPath, tem_nFormat);
	}
	
}


void CUDSSmartCamerav100Dlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	
	m_conVideoOcx.StopRun();
	m_conVideoOcx.Uninitial();

	CDialogEx::OnClose();
}


BOOL CUDSSmartCamerav100Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
// 	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
// 	{
// 		pMsg->wParam = VK_RETURN;
// 		m_BAutoCrop   = FALSE;
// 		m_BManualCrop = FALSE;
// 		AdjuestImageCrop(m_BAutoCrop);
// 		ManualImageCrop(m_BManualCrop);
// 	}

	if (pMsg->message == WM_MOUSEMOVE)
	{
		m_tipInfo.RelayEvent(pMsg);
	}

	//���λس����ո��˳�����
	CString   tem_strCamera = _T("1");
	CString   tem_strNewName;
	CString   tem_strBussName; 
	CString   tem_strMiddle;
	LPWSTR    tem_wstrBussName;
	CString   tem_strFormat; 
	CString   tem_strPath;
	CString   tem_strNewWhole;
	CString   tem_strNewBuss;
	CFile     tem_File;
	USES_CONVERSION;
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN:
			/*
			if (m_conRename == GetFocus())
			{
				m_conRename->GetWindowText(tem_strNewName);              //��ʾ��

				tem_strBussName = m_vcBussName[m_nLastSlcFile];	
				tem_strFormat   = PathFindExtension(tem_strBussName);    //��׺
				tem_strFormat.MakeLower();

				tem_strMiddle    = tem_strBussName;
				tem_wstrBussName = tem_strMiddle.GetBuffer();
				tem_strMiddle.ReleaseBuffer();
				PathRemoveFileSpecW(tem_wstrBussName);   //·��
				tem_strPath     = tem_wstrBussName;     //·��				
				
				if (tem_strFormat == _T(".jpg")||tem_strFormat == _T(".bmp")||tem_strFormat == _T(".png")||tem_strFormat == _T(".tif"))
				{
					//��ʾ���� ͼ�������ļ���
					
					tem_strNewWhole = tem_strPath + _T("\\") + tem_strNewName + tem_strFormat;
					tem_strNewBuss  = tem_strNewWhole;
	//				tem_File.Rename(tem_strBussName, tem_strNewBuss);

					int len =WideCharToMultiByte(CP_ACP,0,tem_strBussName,-1,NULL,0,NULL,NULL);  
					char *ptxtSrc =new char[len +1];  
					WideCharToMultiByte(CP_ACP,0,tem_strBussName,-1,ptxtSrc,len,NULL,NULL );  

					len =WideCharToMultiByte(CP_ACP,0,tem_strNewBuss,-1,NULL,0,NULL,NULL);  
					char *ptxtDst =new char[len +1];  
					WideCharToMultiByte(CP_ACP,0,tem_strNewBuss,-1,ptxtDst,len,NULL,NULL );  

					int  tem_rcRename = rename(ptxtSrc, ptxtDst);
					if (tem_rcRename == 0)
					{
						m_vcFileName[m_nLastSlcFile] = tem_strNewName;
						m_vcWholeName[m_nLastSlcFile]= tem_strNewWhole;
						m_vcBussName[m_nLastSlcFile] = tem_strNewBuss;					

						ThumbaiList(m_nThumbWidth, m_nThumbHeight);
					} 
					else
					{
				//		MessageBox(_T("�ļ����Ѵ��ڣ�"));
					}
					delete[] ptxtSrc;  
					delete[] ptxtDst;  
				} 
				else if (tem_strFormat == _T(".pdf")||tem_strFormat == _T(".txt")||tem_strFormat == _T(".dcm"))
				{
					tem_strNewBuss = tem_strPath + _T("\\") + tem_strNewName + tem_strFormat;
	//				tem_File.Rename(tem_strBussName, tem_strNewBuss);

					int len =WideCharToMultiByte(CP_ACP,0,tem_strBussName,-1,NULL,0,NULL,NULL);  
					char *ptxtSrc =new char[len +1];  
					WideCharToMultiByte(CP_ACP,0,tem_strBussName,-1,ptxtSrc,len,NULL,NULL );  

					len =WideCharToMultiByte(CP_ACP,0,tem_strNewBuss,-1,NULL,0,NULL,NULL);  
					char *ptxtDst =new char[len +1];  
					WideCharToMultiByte(CP_ACP,0,tem_strNewBuss,-1,ptxtDst,len,NULL,NULL );  

					int  tem_rcRename = rename(ptxtSrc, ptxtDst);
					if (tem_rcRename == 0)
					{
						m_vcFileName[m_nLastSlcFile] = tem_strNewName;
						m_vcBussName[m_nLastSlcFile] = tem_strNewBuss;

						ThumbaiList(m_nThumbWidth, m_nThumbHeight);
					}
					else
					{
						MessageBox(_T("�ļ����Ѵ��ڣ�"));
					}	
					delete[] ptxtSrc;  
					delete[] ptxtDst; 
				} 				
			} 
			*/
			return TRUE;	
			break;
		case VK_SPACE:
			//ע�����ְ��º͵����������
			if (m_BSpaceDown)
			{
				OnBnClickedBtnCapature();
				m_BSpaceDown = FALSE;
			} 
			return TRUE;
			break;
		case VK_DELETE:
			if (m_nSlctItem>=0)
			{
				m_iDeleteTip.DoModal();
				if (m_iDeleteTip.m_BDeleteIt)
				{
					//ɾ��ָ���ļ�
					SHFILEOPSTRUCT FileOp;
					BOOL           m_BRC;    //ReturnCode����������
					CString        strSrcPath;

					strSrcPath  = m_vcBussName[m_nSlctItem];
					strSrcPath += '\0';

					CString  tem_strDstPath;
					tem_strDstPath = '\0';     //ɾ��������ֱ����ΪNULL

					CString     tem_strTitle;
					tem_strTitle = _T("����ɾ��...");
					tem_strTitle += '\0';

					FileOp.fFlags = FOF_ALLOWUNDO|FOF_MULTIDESTFILES|FOF_SIMPLEPROGRESS|FOF_NOCONFIRMATION;

					FileOp.lpszProgressTitle = tem_strTitle;
					FileOp.hwnd              = m_hWnd;
					FileOp.hNameMappings     = NULL;
					FileOp.pFrom             = strSrcPath;
					FileOp.pTo               = tem_strDstPath;    //Ŀ��Ŀ¼
					FileOp.wFunc             = FO_DELETE;

					//������ʾ--------------------------------------------------



					m_BRC = SHFileOperation(&FileOp);
					if (!FileOp.fAnyOperationsAborted)
					{
						if(m_BRC)   
						{
							//�������ִ���
						}		
					}
					else
					{
						//����������ֹ
					}				


					//ɾ��vector����Ϣ
					m_vcFileName.erase(m_vcFileName.begin()+m_nSlctItem);
					m_vcWholeName.erase(m_vcWholeName.begin()+m_nSlctItem);
					m_vcBussName.erase(m_vcBussName.begin()+m_nSlctItem);

					ThumbaiList(m_nThumbWidth, m_nThumbHeight);
					//ˢ����ʾ


					
				}
			}
			else
			{
				//��ȡѡ����
				m_vcCtrlInex.clear();
				POSITION   pos;
				pos = m_conListCtrl.GetFirstSelectedItemPosition();
				while (pos)
				{
					int  tem_nIndex = (int)pos-1;
					m_vcCtrlInex.push_back(tem_nIndex);
					m_conListCtrl.GetNextSelectedItem(pos);		
				}
				if (m_vcCtrlInex.size()>0)
				{
					//����ɾ��
					OnDeleteIt();

				}
				
			}
			m_nSlctItem = -1;	
			break;
		case VK_ESCAPE:
			//�����˳���ť��Ӧ�ĺ���
			OnBnClickedBtnTest2();			
			break;
		case 0x41:
			//A��=0x41
			if (GetDlgItem(IDC_LIST_IMAGE)->GetSafeHwnd()==::GetFocus()&& (GetKeyState(VK_CONTROL)&0x8000))
			{
				m_vcCtrlInex.clear();
				m_nSlctItem = -1;
				for (int i=0; i<m_conListCtrl.GetItemCount(); i++)
				{
					m_vcCtrlInex.push_back(i);
					//ѡ�в���������
					m_conListCtrl.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
				}
				
			}
			break;
		}
	}
	else if (pMsg->message == WM_KEYUP)
	{
		switch(pMsg->wParam)
		{
		case  VK_SPACE:			
			m_BSpaceDown = TRUE;
			return TRUE;
			break;
		}
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}


void CUDSSmartCamerav100Dlg::OnBnClickedBtnLrotate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nRotate = (m_nRotate + 3)%4;
	m_conVideoOcx.RotatedVideo(m_nRotate);

	//д����תֵ
	CString   tem_strInfo = _T("");
	tem_strInfo.Format(_T("%d"), m_nRotate);
	::WritePrivateProfileString(_T("ParentCamera"), _T("VideoRotate"), tem_strInfo, m_strIniPath);

	
}


void CUDSSmartCamerav100Dlg::OnBnClickedBtnRrotate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nRotate = (m_nRotate + 1)%4;
	m_conVideoOcx.RotatedVideo(m_nRotate);

	//д����תֵ
	CString   tem_strInfo = _T("");
	tem_strInfo.Format(_T("%d"), m_nRotate);
	::WritePrivateProfileString(_T("ParentCamera"), _T("VideoRotate"), tem_strInfo, m_strIniPath);
}

//��ͷ��ز���--------------------------------------------------------------------------------------
afx_msg LRESULT CUDSSmartCamerav100Dlg::OnSubswitch(WPARAM wParam, LPARAM lParam)
{
	int   tem_nInfo      = (int)wParam;
	int   tem_nOperation = (int)lParam;

	CString   tem_strName;      //�޺�׺�ļ���
	CString   tem_strFileName;  //���ڸ�ͷ���ձ����ļ���
	CString   tem_strWholeName;
	CString   tem_strSrcImageName;    //�ϲ�ͼ�Ļ���ͼ��
	CString   tem_strIniInfo;
	CString   tem_strFileFormat = m_strFileFormat;
	int  tem_nIndexJpg;
	int  tem_nIndexBmp;
	int  tem_nIndexPng;
	int  tem_nIndexTif;
	int  tem_nIndexPdf;
	int  tem_nIndexBase64;
	int  tem_nIndexDcm;

	int       tem_nRead;
	CString   tem_strRead;
	int       tem_nPageNumber;    //����������ʾ
	CString   tem_strPageNumber;  //����������ʾ
	CRect     rtlbl;              //����������ʾ

	int       tem_nPID1300 = -1;
	int       tem_nVID1300 = -1;
	CString   tem_strPIDVID, tem_strPID1300, tem_strVID1300;

	switch(tem_nOperation)
	{
	case 0:
		if (tem_nInfo)
		{
			//�򿪸�ͷ
			if (m_nMainOpen!=0)
			{
				MessageBox(_T("���ȴ���ͷ�豸��"), _T("��ͼUDS"), MB_OK);
				m_iChildAdv.m_conChkOpen.SetCheck(BST_UNCHECKED);
				break;
			}
			::GetPrivateProfileString(_T("ChildCamera"), _T("LastUsed"), _T("û���ҵ���ͷLasrUsed��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
			tem_nRead = _ttoi(tem_strRead);
			m_nLastSubScan = tem_nRead;
			::GetPrivateProfileString(_T("ChildCamera"), _T("Resolution"), _T("û���ҵ���ͷResolution��Ϣ"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
			tem_nRead = _ttoi(tem_strRead);
			m_nLastSubRes = tem_nRead;

			m_iChildAdv.m_conComScannersub.ResetContent();
			m_iChildAdv.m_conComDPIsub.ResetContent();
			int tem_nDeviceCount = m_conVideoOcx.GetDeviceCount();
			if (tem_nDeviceCount>1)
			{
				for (int i=0; i<tem_nDeviceCount; i++)
				{
//					if (i!=m_nLastUsedScanner)
					{
						CString   tem_strDeviceName = m_conVideoOcx.GetDeviceName(i);
						tem_strDeviceName = CheckCameraName(tem_strDeviceName);
						m_iChildAdv.m_conComScannersub.InsertString(i, tem_strDeviceName);
					}
				}
				m_vcCameraName.clear();
				m_nSameCameraLast = 2;

				if (m_nLastSubScan != m_nLastUsedScanner) //ǰ�����Լ�����������ͷ��
				{
					m_iChildAdv.m_conComScannersub.SetCurSel(m_nLastSubScan);
					m_lReturnCode = m_conVideoOcx.StartSubCamera(m_nLastSubScan);//��������Combo����
					if (m_lReturnCode!=0)
					{
						MessageBox(_T("���豸��������ͷͬʱʹ�ã�"), _T("��ͼUDS"), MB_OK);
						//�رո�ͷ
						m_conVideoOcx.StopSubCamera();
//						m_iChildAdv.m_conComScannersub.ResetContent();
//						m_iChildAdv.m_conComDPIsub.ResetContent();
						m_nLastSubScan = -1;
//						m_iChildAdv.m_conChkOpen.SetCheck(BST_UNCHECKED);
						break;;

					}

					//1011-��ͷ��ֵ
					//�豸�򿪳ɹ������Ȼ�ȡ�豸PID_VID
					tem_strPIDVID = m_conVideoOcx.GetDevDisplayName(m_nLastSubScan);
					//����PID_VID�Ƿ�Ϊָ�����豸
					tem_nPID1300 = tem_strPIDVID.Find(m_strPID1300);
					tem_nVID1300 = tem_strPIDVID.Find(m_strVID1300);
					//1011


					CString   tem_strResolution = _T("");
					int  tem_nResCount = m_conVideoOcx.GetSubResoCount();
					m_nInterpolateSubReso = tem_nResCount;
					for (int i=0; i<tem_nResCount; i++) 
					{
						CString   tem_strResName = m_conVideoOcx.GetSubReso(i);
						if (tem_strResName==_T("640*480"))
						{
							tem_strResName += _T("(VGA)");
						}
						else if (tem_strResName == _T("352*288"))
						{
							tem_strResName += _T("(CIF)");
						}
						m_iChildAdv.m_conComDPIsub.InsertString(i, tem_strResName);
					}
					if (tem_nPID1300!=-1 && tem_nVID1300!=-1)
					{
						m_BCamera1300 = TRUE;
						m_iChildAdv.m_conComDPIsub.InsertString(tem_nResCount, _T("4680��3360"));
						if (m_nLastSubRes == m_nInterpolateSubReso)
						{
							int  tem_nMaxIndex = GetmaxResoindex();
							m_conVideoOcx.SetSubResolution(tem_nMaxIndex);
						}
						else
						{
							m_conVideoOcx.SetSubResolution(m_nLastSubRes);
						}

					}
					else
					{
						m_BCamera1300 = FALSE;
					}

//					m_nLastSubRes = m_conVideoOcx.GetSubCurResoIndex();   //��ȡ��ͷ��ǰ�ֱ��ʣ��޸�Ϊ����Ϊ�����ļ��ֱ���
					m_conVideoOcx.SetSubResolution(m_nLastSubRes);
					m_iChildAdv.m_conComDPIsub.SetCurSel(m_nLastSubRes);
				}
				else
				{
					MessageBox(_T("���豸�ѱ���ͷռ�ã�"), _T("��ͼUDS"), MB_OK);
					break;
				}
			}
			else
			{
				MessageBox(_T("��ǰ����һ����������ͷ��"), _T("��ͼUDS"), MB_OK);
				m_iChildAdv.m_conChkOpen.SetCheck(BST_UNCHECKED);
			}
			break;
		}
		else
		{
			//�رո�ͷ
			m_conVideoOcx.StopSubCamera();
			m_iChildAdv.m_conComScannersub.ResetContent();
			m_iChildAdv.m_conComDPIsub.ResetContent();
			m_nLastSubScan = -1;
			break;
		}
	case 1:
		if (tem_nInfo == m_nLastSubScan)
		{
			MessageBox(_T("���豸�Ѵ򿪣�"), _T("��ͼUDS"), MB_OK);
			break;
		}
		else if (tem_nInfo == m_nLastUsedScanner)
		{
			MessageBox(_T("���豸�ѱ���ͷռ�ã�"), _T("��ͼUDS"), MB_OK);
			//���������ã������������ͷ
			m_iChildAdv.m_conComScannersub.SetCurSel(m_nLastSubScan);
			break;
		}
		else
		{
//			m_conVideoOcx.StopRun();     //6-14ע�ͣ���ʱ��֪Ϊ��������ȹر��豸
			m_nLastSubScan = tem_nInfo;
			m_lReturnCode = m_conVideoOcx.StartSubCamera(m_nLastSubScan);
			if (m_lReturnCode!=0)
			{
				MessageBox(_T("���豸��������ͷͬʱʹ�ã�"), _T("��ͼUDS"), MB_OK);
				//�رո�ͷ
				m_conVideoOcx.StopSubCamera();
//				m_iChildAdv.m_conComScannersub.ResetContent();
//				m_iChildAdv.m_conComDPIsub.ResetContent();
				m_nLastSubScan = -1;
//				m_iChildAdv.m_conChkOpen.SetCheck(BST_UNCHECKED);
				break;

			}
			m_nLastSubRes = m_conVideoOcx.GetSubCurResoIndex();

			//1011-��ͷ��ֵ
			//�豸�򿪳ɹ������Ȼ�ȡ�豸PID_VID
			tem_strPIDVID = m_conVideoOcx.GetDevDisplayName(m_nLastSubScan);
			//����PID_VID�Ƿ�Ϊָ�����豸
			tem_nPID1300 = tem_strPIDVID.Find(m_strPID1300);
			tem_nVID1300 = tem_strPIDVID.Find(m_strVID1300);
			//1011

			//����ͷ��Ϣд��ini
			tem_strIniInfo.Format(_T("%d"), m_nLastSubScan);
			::WritePrivateProfileString(_T("ChildCamera"), _T("LastUsed"), tem_strIniInfo, m_strIniPath); 
			
			m_iChildAdv.m_conComDPIsub.ResetContent();
			int  tem_nResCount = m_conVideoOcx.GetSubResoCount();
			m_nInterpolateSubReso = tem_nResCount;
			for (int i=0; i<tem_nResCount; i++)
			{
				CString   tem_strResName = m_conVideoOcx.GetSubReso(i);
				//�ж�640*480�����VGA��꣬352*288�����CIF���
				if (tem_strResName==_T("640*480"))
				{
					tem_strResName += _T("(VGA)");
				}
				else if (tem_strResName == _T("352*288"))
				{
					tem_strResName += _T("(CIF)");
				}
				
				m_iChildAdv.m_conComDPIsub.InsertString(i, tem_strResName);
			}

			if (tem_nPID1300!=-1 && tem_nVID1300!=-1)
			{
				m_BCamera1300 = TRUE;
				m_iChildAdv.m_conComDPIsub.InsertString(tem_nResCount, _T("4680��3360"));
				if (m_nLastSubRes == m_nInterpolateSubReso)
				{
					int  tem_nMaxIndex = GetmaxResoindex();
					m_conVideoOcx.SetSubResolution(tem_nMaxIndex);
				}
				else
				{
					m_conVideoOcx.SetSubResolution(m_nLastSubRes);
				}

			}
			else
			{
				m_BCamera1300 = FALSE;
			}

			
			m_iChildAdv.m_conComDPIsub.SetCurSel(m_nLastSubRes);
			break;
		}
	case 2:
		if (tem_nInfo != m_nLastSubRes)
		{
			m_nLastSubRes = tem_nInfo;
			int  tem_nResCount = m_conVideoOcx.GetSubResoCount();
			m_nInterpolateSubReso = tem_nResCount;
			if (m_BCamera1300)
			{
				//1300W�豸
				if (m_nLastSubRes == m_nInterpolateSubReso)
				{
					//��ʱΪ��ֵ�ֱ��ʣ�����Ϊ���ֱ���
					int  tem_nMaxIndex = GetsubmaResoindex();
					m_conVideoOcx.SetSubResolution(tem_nMaxIndex);

				}
				else
				{
					m_conVideoOcx.SetSubResolution(m_nLastSubRes);
				}
			}
			else
			{
				m_conVideoOcx.SetSubResolution(m_nLastSubRes);
			}
		    
			//����ͷ�ֱ���д��ini
			tem_strIniInfo.Format(_T("%d"), m_nLastSubRes);
			::WritePrivateProfileString(_T("ChildCamera"), _T("Resolution"), tem_strIniInfo, m_strIniPath); 
		}
		break;
	case 3:
		//0-�ⲿ�ϲ���1-�ڲ��ϲ���2-���ϲ�
		switch(tem_nInfo)
		{
		case 0:
			m_BMerge = TRUE;
			m_nMergeMode = 0;
			m_nMergeLocation = 3;
			break;
		case 1:
			m_BMerge = TRUE;
			m_nMergeMode = 1;
			break;
		case 2:
			m_BMerge = FALSE;
			break;
		default:
			break;
		}
		break;
	case 4:
		switch (tem_nInfo)
		{
		case 0:
			m_nMergeLocation = 0;
			break;
		case 1:
			m_nMergeLocation = 1;
			break;
		case 2:
			m_nMergeLocation = 2;
			break;
		case 3:
			m_nMergeLocation = 3;
			break;
		case 4:
			m_nMergeLocation = 4;
			break;
		case 5:
			m_nMergeLocation = 5;
			break;
		case 6:
			m_nMergeLocation = 6;
			break;
		case 7:
			m_nMergeLocation = 7;
			break;
		default:
			break;
		}
		break;
	case 5:
		break;
	case 6:
		tem_nIndexPdf    = tem_strFileFormat.Find(_T("pdf"));
		tem_nIndexBase64 = tem_strFileFormat.Find(_T("txt"));
		tem_nIndexDcm    = tem_strFileFormat.Find(_T("dcm"));
		if (tem_nIndexPdf != -1 || tem_nIndexBase64 != -1 || tem_nIndexDcm != -1)
		{
			m_strFileFormat = _T(".jpg");  //��PDF��Base64����������޸ĺ�׺
			m_iChildNor.m_conComFilemode.SetCurSel(1);
			m_BPDFCpt       = FALSE;
			m_BBase64Cpt    = FALSE;
			m_BDcmCpt       = FALSE;
		}
	
		tem_strName      = NamingFile(m_nNamingMode);
		tem_strFileName  = tem_strName + m_strFileFormat;
		tem_strWholeName = m_strDefaultPath + tem_strFileName;
		tem_strSrcImageName = m_strBufferPath + tem_strFileName;    //1018
		if (m_BSoundOpen)
		{
			sndPlaySound(_T("CameraSound.WAV"), NULL);
		}
		if (m_BMerge)//�ϲ�����
		{
			if (m_BCamera500 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1)���ϲ�ͼ�񱣴�������Ŀ¼
				m_conVideoOcx.CaptureTwoCam(tem_strSrcImageName, m_nMergeMode, m_nMergeLocation);	
				//2)��ֵͼ��
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 3);
				m_vcFileName.push_back(tem_strName);
				tem_strSrcImageName = GetThumbPath(tem_strWholeName, tem_strName);    //��������ͼ
				m_vcWholeName.push_back(tem_strSrcImageName);
				m_vcBussName.push_back(tem_strWholeName);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
				//3)ɾ������ͼ��
				DeleteFile(tem_strSrcImageName);
			} 
			else if (m_BCamera800 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1)���ϲ�ͼ�񱣴�������Ŀ¼
				m_conVideoOcx.CaptureTwoCam(tem_strSrcImageName, m_nMergeMode, m_nMergeLocation);	
				//2)��ֵͼ��
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 0);
				m_vcFileName.push_back(tem_strName);
				tem_strSrcImageName = GetThumbPath(tem_strWholeName, tem_strName);    //��������ͼ
				m_vcWholeName.push_back(tem_strSrcImageName);
				m_vcBussName.push_back(tem_strWholeName);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
				//3)ɾ������ͼ��
				DeleteFile(tem_strSrcImageName);
			} 
			else if(m_BCamera1200 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1)���ϲ�ͼ�񱣴�������Ŀ¼
				m_conVideoOcx.CaptureTwoCam(tem_strSrcImageName, m_nMergeMode, m_nMergeLocation);	
				//2)��ֵͼ��
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 1);
				m_vcFileName.push_back(tem_strName);
				tem_strSrcImageName = GetThumbPath(tem_strWholeName, tem_strName);    //��������ͼ
				m_vcWholeName.push_back(tem_strSrcImageName);
				m_vcBussName.push_back(tem_strWholeName);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
				//3)ɾ������ͼ��
				DeleteFile(tem_strSrcImageName);
			}
			else if (m_BCamera1300 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1)���ϲ�ͼ�񱣴�������Ŀ¼
				m_conVideoOcx.CaptureTwoCam(tem_strSrcImageName, m_nMergeMode, m_nMergeLocation);	
				//2)��ֵͼ��
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 2);
				m_vcFileName.push_back(tem_strName);
				tem_strSrcImageName = GetThumbPath(tem_strWholeName, tem_strName);    //��������ͼ
				m_vcWholeName.push_back(tem_strSrcImageName);
				m_vcBussName.push_back(tem_strWholeName);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
				//3)ɾ������ͼ��
				DeleteFile(tem_strSrcImageName);
			}
			else if (m_BGS1600 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1)���ϲ�ͼ�񱣴�������Ŀ¼
				m_conVideoOcx.CaptureTwoCam(tem_strSrcImageName, m_nMergeMode, m_nMergeLocation);	
				//2)��ֵͼ��
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 5);
				m_vcFileName.push_back(tem_strName);
				tem_strSrcImageName = GetThumbPath(tem_strWholeName, tem_strName);    //��������ͼ
				m_vcWholeName.push_back(tem_strSrcImageName);
				m_vcBussName.push_back(tem_strWholeName);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
				//3)ɾ������ͼ��
				DeleteFile(tem_strSrcImageName);
			}
			else if (m_BCamera200 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1)���ϲ�ͼ�񱣴�������Ŀ¼
				m_conVideoOcx.CaptureTwoCam(tem_strSrcImageName, m_nMergeMode, m_nMergeLocation);	
				//2)��ֵͼ��
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 6);
				m_vcFileName.push_back(tem_strName);
				tem_strSrcImageName = GetThumbPath(tem_strWholeName, tem_strName);    //��������ͼ
				m_vcWholeName.push_back(tem_strSrcImageName);
				m_vcBussName.push_back(tem_strWholeName);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
				//3)ɾ������ͼ��
				DeleteFile(tem_strSrcImageName);
			}
			else
			{
				m_conVideoOcx.CaptureTwoCam(tem_strWholeName, m_nMergeMode, m_nMergeLocation);		
				m_vcFileName.push_back(tem_strName);
				tem_strSrcImageName = GetThumbPath(tem_strWholeName, tem_strName);    //��������ͼ
				m_vcWholeName.push_back(tem_strSrcImageName);
				m_vcBussName.push_back(tem_strWholeName);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			}
			
		}
		else
		{
			m_conVideoOcx.CaptureSubCam(tem_strWholeName);
			m_vcFileName.push_back(tem_strName);
			tem_strSrcImageName = GetThumbPath(tem_strWholeName, tem_strName);    //��������ͼ
			m_vcWholeName.push_back(tem_strSrcImageName);
			m_vcBussName.push_back(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
		}
	//	ShellExecuteW(NULL, TEXT("open"), tem_strWholeName, NULL, NULL, SW_SHOWNORMAL);
		m_nImageCount++;
		m_nNamingCount++;
		//�����²�ҳ����ʾ
		tem_nPageNumber = m_nImageCount + m_nImageCountOther;
		tem_strPageNumber.Format(_T("%d"), tem_nPageNumber);
		GetDlgItem(IDC_STA_NUMBER)->SetWindowText(tem_strPageNumber);

		
		GetDlgItem(IDC_STA_NUMBER)->GetWindowRect(&rtlbl); 
		ScreenToClient(&rtlbl); //ת���ͻ��˽���
		InvalidateRect(&rtlbl);//���ˢ�¶Ի��򱳾� 
		UpdateWindow();
		break;
	default:
		break;
	}

	return 0;
}


//���ù�����Ϣ��Ӧ----------------------------------------------------------
afx_msg LRESULT CUDSSmartCamerav100Dlg::OnAdvceset(WPARAM wParam, LPARAM lParam)
{
	int      tem_nInfo      = (int)wParam;
	int      tem_nOperation = (int)lParam;
	CString  tem_strIniInfo;
	std::vector<CString>::iterator iter;   //����HTTP�ϴ�
	int     tem_nUpLoadOK = -1;    //���״��ϴ�ʧ�ܣ�˵�������������⣬���������ļ��ϴ�
	CString tem_strUpLoad;         //�ϴ��ļ�ʱ���������ķ�����Ϣ
	int     tem_nRC       = -1;
	switch (tem_nOperation)
	{
	case 0:
		m_BShowInfo = tem_nInfo;
		m_conVideoOcx.ShowVideoInfo(m_BShowInfo);

		//����ʾ��Ƶ��Ϣд��ini
		tem_strIniInfo.Format(_T("%d"), tem_nInfo);
		::WritePrivateProfileString(_T("AdvanceSet"), _T("ShowInfo"), tem_strIniInfo, m_strIniPath);
		break;
	case 1:
		m_nJpegQulity = tem_nInfo;
		m_conVideoOcx.SetJpegQuality(m_nJpegQulity);

		//��JPEG����д��ini
		tem_strIniInfo.Format(_T("%d"), m_nJpegQulity);
		::WritePrivateProfileString(_T("AdvanceSet"), _T("JPEGQuality"), tem_strIniInfo, m_strIniPath);
		break;
	case 2:
		m_nAutoSense = tem_nInfo;
		m_conVideoOcx.SetAutomaticSensitiveness(m_nAutoSense);
		
		//��������д��ini
		tem_strIniInfo.Format(_T("%d"), m_nAutoSense);
		::WritePrivateProfileString(_T("AdvanceSet"), _T("AutoCaptureSense"), tem_strIniInfo, m_strIniPath);
		break;
	case 3:
		m_nNamingMode = 1; //ʱ������
	
		m_nNamingCount = 1;

		tem_strIniInfo.Format(_T("%d"), m_nNamingMode);
		::WritePrivateProfileString(_T("AdvanceSet"), _T("NamingMode"), tem_strIniInfo, m_strIniPath);
		break;
	case 4:
		m_nNamingMode = 0; //��������

		m_nNamingCount = 1;

		tem_strIniInfo.Format(_T("%d"), m_nNamingMode);
		::WritePrivateProfileString(_T("AdvanceSet"), _T("NamingMode"), tem_strIniInfo, m_strIniPath);
		break;
	case 5:
		m_nNamingMode = 2; //ǰ׺����
		m_strPreName = m_iChildSet.m_strPreName;
		m_nNamingCount = 1;
		tem_strIniInfo.Format(_T("%d"), m_nNamingMode);
		::WritePrivateProfileString(_T("AdvanceSet"), _T("NamingMode"), tem_strIniInfo, m_strIniPath);
		::WritePrivateProfileString(_T("AdvanceSet"), _T("PreName"), m_strPreName, m_strIniPath);
		break;
	case 6:
		m_strDefaultPath = m_iChildSet.m_strDefaultDoc;
		//ע������\\---------------------------------------------------------------------------------------
		::WritePrivateProfileString(_T("AdvanceSet"), _T("DefaultPath"), m_strDefaultPath, m_strIniPath);
		m_strDefaultPath += _T("\\");
		break;
	case 7:
		//�ϴ���ǰ�ĵ�	
		if (tem_nInfo == 0)
		{
			//HTTP�ϴ�
			//for (iter=m_vcBussName.begin(); iter!=m_vcBussName.end();iter++)
			//{
			//	tem_strUpLoad = m_conVideoOcx.UploadFileHttp(*iter, m_strHttp);	
			//}

//	        tem_strUpLoad = m_conVideoOcx.UploadFileHttp(TEXT("D:\\222.jpg"), m_strHttp);	
			tem_strUpLoad = m_conVideoOcx.HTTPUpload(m_strHttp, TEXT("D:\\�ֱ���1.jpg"), FALSE);
//			MessageBox(_T("�ϴ���ɣ�"), _T("HTTP�ϴ�"), MB_OK);
		} 
		else
		{
			//FTP�ϴ�
			for (iter=m_vcBussName.begin(); iter!=m_vcBussName.end();iter++)
			{
				tem_strUpLoad = m_conVideoOcx.UploadFileFtp(*iter, m_strFtpDir, m_strFtpIP, m_strFtpUserName, m_strFtpPassWord, m_strFtpPort);
				
			}
		}
		
		m_iChildSet.m_BUpLoadFiles = FALSE;
		break;
	case 8:
		//��ͷ���ã����ж���ͷ�Ƿ��
		m_conVideoOcx.ShowPorpertiesWindow(TRUE);
		break;
	case 9:
		//��ͷ���ã����жϸ�ͷ�Ƿ��
		tem_nRC = m_conVideoOcx.ShowPorpertiesWindow(FALSE);
		if (tem_nRC!=0)
		{
			MessageBox(_T("��ͷδ�򿪣�"), _T("��ͼUDS"), MB_OK);
		}
		
		break;
	case 10:
		//��ͷ��Ƶ����
		m_conVideoOcx.ShowVideoPorpertiesWindow(TRUE);
		break;
	case 11:
		//��ͷ��Ƶ����
		tem_nRC = m_conVideoOcx.ShowVideoPorpertiesWindow(FALSE);
		if (tem_nRC!=0)
		{
			MessageBox(_T("��ͷδ�򿪣�"), _T("��ͼUDS"), MB_OK);
		}
		break;
	case 12:
		if (tem_nInfo==1)
		{
			m_BSoundOpen = TRUE;
			::WritePrivateProfileString(_T("OtherSet"), _T("SoundOpen"), _T("1"), m_strIniPath);

		}
		else
		{
			m_BSoundOpen = FALSE;
			::WritePrivateProfileString(_T("OtherSet"), _T("SoundOpen"), _T("0"), m_strIniPath);
		}
		break;
	default:
		break;
	}

	return 0;
}


CString CUDSSmartCamerav100Dlg::NamingFile(int namecode)
{
	CString       tem_strName2;
	SYSTEMTIME    tem_st;
	CString       tem_strDate, tem_strTime;
	CString       tem_str; //ǰ׺����ʱ��ǰ׺��Ӵ�������
	CString       tem_strIniDate, tem_strIniCount, tem_strIniMark;
	int           tem_nIniMark, tem_nIniCount;

	m_strPreName.ReleaseBuffer();
	
	switch(namecode)
	{
	case 0:
//		tem_strName2.Format(_T("%04d"), m_nImageCount);
		tem_strName2.Format(_T("%04d"), m_nNamingCount);
		tem_strName2 = _T("IMG_") + tem_strName2;
		break;
	case 1:
		//���ȶ�ȡ�Ƿ�ʹ������+��������
		::GetPrivateProfileString(_T("AdvanceSet"), _T("DateMark"), _T("û���ҵ�DateMark ��Ϣ"), tem_strIniMark.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		tem_nIniMark = _ttoi(tem_strIniMark);
		if (tem_nIniMark == 1)
		{
			//��������+��������
			//�������ļ���ȡ����
			::GetPrivateProfileString(_T("AdvanceSet"), _T("Date"), _T("û���ҵ�Date ��Ϣ"), tem_strIniDate.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);

			::GetPrivateProfileString(_T("AdvanceSet"), _T("DayCount"), _T("û���ҵ�DayCount ��Ϣ"), tem_strIniCount.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
			tem_nIniCount = _ttoi(tem_strIniCount);
			tem_strIniCount.ReleaseBuffer();

			//��ȡ��ǰ����
			GetLocalTime(&tem_st);
			tem_strDate.Format(_T("%d%02d%02d"), tem_st.wYear, tem_st.wMonth, tem_st.wDay);

			//�Ƚ��Ƿ���ͬ
			if (tem_strDate == tem_strIniDate)
			{
				tem_nIniCount++;
				tem_strIniCount.Format(_T("%d"), tem_nIniCount);
				tem_strName2 = tem_strDate + _T("_") + tem_strIniCount;
				//���µļ���д�������ļ�
				::WritePrivateProfileString(_T("AdvanceSet"), _T("DayCount"), tem_strIniCount, m_strIniPath);
			}
			else
			{
				//���µ�����д�������ļ�
				::WritePrivateProfileString(_T("AdvanceSet"), _T("Date"), tem_strDate, m_strIniPath);
				tem_nIniCount=1;
				tem_strIniCount.Format(_T("%d"), tem_nIniCount);
				//���µļ���д�������ļ�
				::WritePrivateProfileString(_T("AdvanceSet"), _T("DayCount"), tem_strIniCount, m_strIniPath);
				tem_strName2 = tem_strDate + _T("_") + tem_strIniCount;			
			}
			
		}
		else
		{
			//��������+ʱ������
			//��ȡϵͳʱ������	
			GetLocalTime(&tem_st);
			tem_strDate.Format(_T("%d%02d%02d_"), tem_st.wYear, tem_st.wMonth, tem_st.wDay);
			tem_strTime.Format(_T("%02d%02d%02d"), tem_st.wHour, tem_st.wMinute, tem_st.wSecond);
			tem_strName2 = tem_strDate + tem_strTime;	
		}
		
		break;
	case 2:
//		tem_str.Format(_T("%d"), m_nImageCount);
		tem_str.Format(_T("%04d"), m_nNamingCount);
		if(m_strPreName == _T(""))
		{
			tem_strName2  = tem_str;
		}
		else
		{
			tem_strName2  = m_strPreName;
			tem_strName2 += _T("_");
			tem_strName2 += tem_str;
		}
		
		break;
	case 3:
		//��������+ʱ������
		//��ȡϵͳʱ������	
		GetLocalTime(&tem_st);
		tem_strDate.Format(_T("%d%02d%02d_"), tem_st.wYear, tem_st.wMonth, tem_st.wDay);
		tem_strTime.Format(_T("%02d%02d%02d"), tem_st.wHour, tem_st.wMinute, tem_st.wSecond);
		tem_strName2 = tem_strDate + tem_strTime;	
		break;
	default:
		break;
	}
	return tem_strName2;
}


//�ؼ��¼�-------------------------------------------------------------------------------------
BEGIN_EVENTSINK_MAP(CUDSSmartCamerav100Dlg, CDialogEx)
	ON_EVENT(CUDSSmartCamerav100Dlg, IDC_UDS_VIDEOCTRL1, 1, CUDSSmartCamerav100Dlg::GetBarcodeStringUdsVideoctrl1, VTS_BSTR)
	ON_EVENT(CUDSSmartCamerav100Dlg, IDC_UDS_VIDEOCTRL1, 2, CUDSSmartCamerav100Dlg::GetAutoCapFileNameUdsVideoctrl1, VTS_BSTR)
	ON_EVENT(CUDSSmartCamerav100Dlg, IDC_UDS_VIDEOCTRL1, 3, CUDSSmartCamerav100Dlg::DeviceChangedUdsVideoctrl1, VTS_BSTR VTS_BSTR)
END_EVENTSINK_MAP()


void CUDSSmartCamerav100Dlg::GetBarcodeStringUdsVideoctrl1(LPCTSTR Barcode)
{
	// TODO: �ڴ˴������Ϣ����������
	m_iChildNor.m_conRichEdit.SetSelectionCharFormat(m_iChildNor.tem_fontRichEdit); //�����ø�ʽ
	m_iChildNor.m_conRichEdit.ReplaceSel(_T("����:"));
	m_iChildNor.m_conRichEdit.ReplaceSel(Barcode);
	m_iChildNor.m_conRichEdit.ReplaceSel(_T("\n"));
	m_iChildNor.m_conRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	CString  tem_strName = Barcode;  //������׺���ļ���
	
	//��ʶ��Ϊ��ά����ַ������Ҫ����ά����ַ�е������ַ�ȥ��
	//��http��ͷΪ��ַ
	tem_strName.Replace('\\', '_');
	tem_strName.Replace('/', '_');
	tem_strName.Replace(':', '_');
	tem_strName.Replace('*', '_');
	tem_strName.Replace('?', '_');
	tem_strName.Replace('/"', '_');
	tem_strName.Replace('<', '_');
	tem_strName.Replace('>', '_');
	tem_strName.Replace('|', '_');

	CString  tem_strThumbPath = _T("");
	
	CString  tem_strFileName  = tem_strName + m_strFileFormat;
	CString  tem_strWholeName = m_strDefaultPath + tem_strFileName;
	CString  tem_strSrcName   = m_strBufferPath + tem_strFileName;

	m_vcFileName.push_back(tem_strName);
	if (m_BCamera800 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		tem_strWholeName = InterPolateImage(tem_strSrcName, tem_strWholeName, 0);
		DeleteFile(tem_strSrcName);
	}
	else if (m_BCamera500 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		tem_strWholeName = InterPolateImage(tem_strSrcName, tem_strWholeName, 3);
		DeleteFile(tem_strSrcName);
	}
	else if (m_BCamera1200 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		tem_strWholeName = InterPolateImage(tem_strSrcName, tem_strWholeName, 1);
		DeleteFile(tem_strSrcName);
	}
	else if (m_BCamera1300 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		tem_strWholeName = InterPolateImage(tem_strSrcName, tem_strWholeName, 2);
		DeleteFile(tem_strSrcName);
	}
	else if (m_BCameraTo1500 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		tem_strWholeName = InterPolateImage(tem_strSrcName, tem_strWholeName, 4);
		DeleteFile(tem_strSrcName);
	}
	else if (m_BGS1600 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		tem_strWholeName = InterPolateImage(tem_strSrcName, tem_strWholeName, 5);
		DeleteFile(tem_strSrcName);
	}
	else if (m_BCamera200 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		tem_strWholeName = InterPolateImage(tem_strSrcName, tem_strWholeName, 6);
		DeleteFile(tem_strSrcName);
	}

	//�ĵ��Ż�--------------------------------------------
	if (m_BOptimize)
	{
		CxImage   tem_cxSrcImg;
		tem_cxSrcImg.Load(tem_strWholeName, CMAX_IMAGE_FORMATS);

		float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


		if (tem_fColorPer>=m_fColorPercentage)
		{
			//��ɫͼ��
			Self_DocOptimize(tem_cxSrcImg, tem_strWholeName, m_BOptimize, m_nOptBright, m_nOptContrast);
		} 
		else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
		{
			//�ڰ�ͼ��
			Self_DocOptimize2(tem_cxSrcImg, tem_strWholeName, m_BOptimize);
		}
		//����Ϊ��ֵͼ�񣬲����Ż�
	}
	
	tem_strThumbPath = GetThumbPath(tem_strWholeName, tem_strName);    //��������ͼ
	m_vcWholeName.push_back(tem_strThumbPath);
	m_vcBussName.push_back(tem_strWholeName);

	ShowImageSize(tem_strWholeName);
	ThumbaiList(m_nThumbWidth, m_nThumbHeight);	
}


void CUDSSmartCamerav100Dlg::GetAutoCapFileNameUdsVideoctrl1(LPCTSTR fileName)
{
	// TODO: �ڴ˴������Ϣ����������
	CString  tem_strThumbPath = _T("");
	CString  tem_strName = fileName;  //������׺���ļ���
	CString  tem_strFileName  = PathFindFileName(tem_strName);   //����׺���ļ���
	CString  tem_strWholeName = fileName;
	CString  tem_strSrcName   = fileName;



	m_vcFileName.push_back(tem_strFileName);

	if (m_BCamera800 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		//����ԭ·��+�ļ����ó��ļ�����ͬʱת������·��
		tem_strWholeName = m_strDefaultPath + tem_strFileName;
		tem_strWholeName = InterPolateImage(tem_strName, tem_strWholeName, 0);
		DeleteFile(tem_strName);
	}
	else if (m_BCamera500 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		//����ԭ·��+�ļ����ó��ļ�����ͬʱת������·��
		tem_strWholeName = m_strDefaultPath + tem_strFileName;
		tem_strWholeName = InterPolateImage(tem_strName, tem_strWholeName, 3);
		DeleteFile(tem_strName);
	}
	else if (m_BCamera1200 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		//����ԭ·��+�ļ����ó��ļ�����ͬʱת������·��
		tem_strWholeName = m_strDefaultPath + tem_strFileName;
		tem_strWholeName = InterPolateImage(tem_strName, tem_strWholeName, 1);
		DeleteFile(tem_strName);
	}
	else if (m_BCamera1300 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		//����ԭ·��+�ļ����ó��ļ�����ͬʱת������·��
		tem_strWholeName = m_strDefaultPath + tem_strFileName;
		tem_strWholeName = InterPolateImage(tem_strName, tem_strWholeName, 2);
		DeleteFile(tem_strName);
	}
	else if (m_BCameraTo1500 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		//����ԭ·��+�ļ����ó��ļ�����ͬʱת������·��
		tem_strWholeName = m_strDefaultPath + tem_strFileName;
		tem_strWholeName = InterPolateImage(tem_strName, tem_strWholeName, 4);
		DeleteFile(tem_strName);
	}
	else if (m_BGS1600 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		//����ԭ·��+�ļ����ó��ļ�����ͬʱת������·��
		tem_strWholeName = m_strDefaultPath + tem_strFileName;
		tem_strWholeName = InterPolateImage(tem_strName, tem_strWholeName, 5);
		DeleteFile(tem_strName);
	}
	else if (m_BCamera200 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		//����ԭ·��+�ļ����ó��ļ�����ͬʱת������·��
		tem_strWholeName = m_strDefaultPath + tem_strFileName;
		tem_strWholeName = InterPolateImage(tem_strName, tem_strWholeName, 6);
		DeleteFile(tem_strName);
	}
	
	
	if (m_BSoundOpen)
	{
		sndPlaySound(_T("CameraSound.WAV"), NULL);
	}

	//�ĵ��Ż�--------------------------------------------
	if (m_BOptimize)
	{
		CxImage   tem_cxSrcImg;
		tem_cxSrcImg.Load(tem_strWholeName, CMAX_IMAGE_FORMATS);

		float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


		if (tem_fColorPer>=m_fColorPercentage)
		{
			//��ɫͼ��
			Self_DocOptimize(tem_cxSrcImg, tem_strWholeName, m_BOptimize, m_nOptBright, m_nOptContrast);
		} 
		else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
		{
			//�ڰ�ͼ��
			Self_DocOptimize2(tem_cxSrcImg, tem_strWholeName, m_BOptimize);
		}
		//����Ϊ��ֵͼ�񣬲����Ż�
	}
	tem_strThumbPath = GetThumbPath(tem_strWholeName, tem_strFileName);    //��������ͼ
	m_vcWholeName.push_back(tem_strThumbPath);
	m_vcBussName.push_back(tem_strWholeName);

//	CString str = m_conVideoOcx.QrCode(tem_strWholeName);

	m_iChildNor.m_conRichEdit.SetSelectionCharFormat(m_iChildNor.tem_fontRichEdit);  //�����ø�ʽ
	m_iChildNor.m_conRichEdit.ReplaceSel(tem_strWholeName);	
	m_iChildNor.m_conRichEdit.ReplaceSel(_T("\n"));
	m_iChildNor.m_conRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	

	ShowImageSize(tem_strWholeName);
	ThumbaiList(m_nThumbWidth, m_nThumbHeight);

	m_nImageCountOther++;
	m_nNamingCount++;
	//�����²�ҳ����ʾ
	int       tem_nPageNumber;
	CString   tem_strPageNumber;
	tem_nPageNumber = m_nImageCount + m_nImageCountOther;
	tem_strPageNumber.Format(_T("%d"), tem_nPageNumber);
	GetDlgItem(IDC_STA_NUMBER)->SetWindowText(tem_strPageNumber);

	CRect rtlbl; 
	GetDlgItem(IDC_STA_NUMBER)->GetWindowRect(&rtlbl); 
	ScreenToClient(&rtlbl); //ת���ͻ��˽���
	InvalidateRect(&rtlbl);//���ˢ�¶Ի��򱳾� 
	UpdateWindow();
	
}


void CUDSSmartCamerav100Dlg::DeviceChangedUdsVideoctrl1(LPCTSTR changeType, LPCTSTR deviceName)
{
	// TODO: �ڴ˴������Ϣ����������
	m_iChildNor.m_conRichEdit.SetSelectionCharFormat(m_iChildNor.tem_fontRichEdit);   //�����ø�ʽ
	m_iChildNor.m_conRichEdit.ReplaceSel(changeType);
	m_iChildNor.m_conRichEdit.ReplaceSel(_T(" - "));
	m_iChildNor.m_conRichEdit.ReplaceSel(deviceName);
	m_iChildNor.m_conRichEdit.ReplaceSel(_T("\n"));
	m_iChildNor.m_conRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}


void CUDSSmartCamerav100Dlg::OnBnClickedBtnBrows()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShellExecute(NULL, NULL, m_strDefaultPath, NULL, NULL, SW_SHOW);
}


BOOL CUDSSmartCamerav100Dlg::ThumbaiList(int thumbwidth, int thumbheight)
{

	int          m_nImageIndex= 0;
	DWORD  dwStyle;
	//CImageList��ʼ��
	m_imagelist.Create(thumbwidth,thumbheight,ILC_COLOR24,0,1);

	//ListCtrl��ʼ��
	dwStyle = m_conListCtrl.GetExtendedStyle();
//	dwStyle=dwStyle|LVS_SHOWSELALWAYS|LVS_ALIGNTOP|LVS_ICON|LVS_AUTOARRANGE|LVS_EDITLABELS;  //����EDITLABELS XPϵͳ�³���ͼ��
	dwStyle=dwStyle|LVS_SHOWSELALWAYS|LVS_ALIGNTOP|LVS_ICON|LVS_AUTOARRANGE;
	m_conListCtrl.SetExtendedStyle(dwStyle);
	m_conListCtrl.SetImageList(&m_imagelist,LVSIL_NORMAL);
	for(int i=0;i<m_imagelist.GetImageCount();i++)
	{
		m_imagelist.Remove(i);
	}
	m_conListCtrl.DeleteAllItems();
	m_imagelist.SetImageCount(m_vcFileName.size()); 

	wchar_t path[MAX_PATH]; //���ֽ�char
	std::vector<CString>::iterator iter1;
	std::vector<CString>::iterator iter2;
	m_conListCtrl.SetRedraw(false);
	m_nImageIndex = 0;
	m_conListCtrl.SetTextBkColor(RGB(72,77,91));
	m_conListCtrl.SetTextColor(RGB(255, 255, 255));
	for(iter1=m_vcFileName.begin();iter1!=m_vcFileName.end();iter1++,m_nImageIndex++)
	{
		m_conListCtrl.InsertItem(m_nImageIndex,*iter1,m_nImageIndex);
	}
	m_conListCtrl.SetRedraw(true);
	m_conListCtrl.Invalidate();

//	HBRUSH hBrushBorder    =::CreateSolidBrush(RGB(220,220,220));
//	HBRUSH hBrushBkground  =::CreateSolidBrush(RGB(255,255,255));

	HBRUSH hBrushBorder    =::CreateSolidBrush(RGB(72,77,91));
	HBRUSH hBrushBkground  =::CreateSolidBrush(RGB(72,77,91));

	RECT rcBorder;
	rcBorder.left=rcBorder.top  =0;
	rcBorder.right              =thumbwidth;
	rcBorder.bottom             =thumbheight;

	float fRatio=(float)thumbheight/thumbwidth; 

	int XDest,YDest,nDestWidth,nDestHeight;
	m_nImageIndex=0;

	for(iter2=m_vcWholeName.begin();iter2!=m_vcWholeName.end();iter2++,m_nImageIndex++)
	{
		_stprintf(path,*iter2);
		int nImageType=GetTypeFromFileName(path);
		if(nImageType==CXIMAGE_FORMAT_UNKNOWN)
			continue;
		CxImage image;
		image.Load(path, nImageType);
		if(image.IsValid()==false)
			continue;
		float fImgRatio=(float)image.GetHeight()/image.GetWidth();  
		if(fImgRatio>fRatio)
		{
			nDestWidth=(int)thumbheight/fImgRatio;   
			XDest=(thumbwidth-nDestWidth)/2;
			YDest=0;
			nDestHeight=thumbheight;
		}
		else
		{
			XDest=0;
			nDestWidth=thumbwidth;
			nDestHeight=(int)thumbwidth*fImgRatio;  
			YDest=(thumbheight-nDestHeight)/2;
		}

		CClientDC cdc(this);
		HDC hDC=::CreateCompatibleDC(cdc.m_hDC);
		HBITMAP bm=CreateCompatibleBitmap(cdc.m_hDC,thumbwidth,thumbheight);
		HBITMAP pOldBitmapImage=(HBITMAP)SelectObject(hDC,bm);

		::FillRect(hDC,&rcBorder,hBrushBkground);
		image.Stretch(hDC,XDest,YDest,nDestWidth,nDestHeight);
		::FrameRect(hDC,&rcBorder,hBrushBorder);
		SelectObject(hDC,pOldBitmapImage);
		CBitmap bitmap;
		bitmap.Attach(bm);
		m_imagelist.Replace(m_nImageIndex,&bitmap,NULL);
		m_conListCtrl.RedrawItems(m_nImageIndex,m_nImageIndex);

		DeleteDC(hDC);
		DeleteObject(bm);
	}
	DeleteObject(hBrushBorder);
	DeleteObject(hBrushBkground);
	int tem_nCount = m_conListCtrl.GetItemCount();
	if (tem_nCount>0)
	{

		m_conListCtrl.EnsureVisible(tem_nCount-1, FALSE);
	}
	m_conListCtrl.Invalidate();
	
	return TRUE;
}


int CUDSSmartCamerav100Dlg::GetTypeFromFileName(LPCTSTR pstr)
{	
	CString fileName(pstr);
	CString ext3=fileName.Right(3);
	CString ext4=fileName.Right(4);
#if CXIMAGE_SUPPORT_BMP
	if(ext3.CompareNoCase(_T("bmp"))==0)
		return CXIMAGE_FORMAT_BMP;
#endif

#if CXIMAGE_SUPPORT_GIF
	if(ext3.CompareNoCase(_T("gif"))==0)
		return CXIMAGE_FORMAT_GIF;
#endif

#if CXIMAGE_SUPPORT_JPG
	if(ext3.CompareNoCase(_T("jpg"))==0 || ext4.CompareNoCase(_T("jpeg"))==0)
		return CXIMAGE_FORMAT_JPG;
#endif

#if CXIMAGE_SUPPORT_PNG
	if(ext3.CompareNoCase(_T("png"))==0)
		return CXIMAGE_FORMAT_PNG;
#endif

#if CXIMAGE_SUPPORT_MNG
	if(ext3.CompareNoCase(_T("mng"))==0 || ext3.CompareNoCase(_T("jng"))==0 ||ext3.CompareNoCase(_T("png"))==0)
		return CXIMAGE_FORMAT_MNG;
#endif

#if CXIMAGE_SUPPORT_ICO
	if(ext3.CompareNoCase(_T("ico"))==0)
		return CXIMAGE_FORMAT_ICO;
#endif

#if CXIMAGE_SUPPORT_TIF
	if(ext3.CompareNoCase(_T("tif"))==0 || ext4.CompareNoCase(_T("tiff"))==0)
		return CXIMAGE_FORMAT_TIF;
#endif

#if CXIMAGE_SUPPORT_TGA
	if(ext3.CompareNoCase(_T("tga"))==0)
		return CXIMAGE_FORMAT_TGA;
#endif

#if CXIMAGE_SUPPORT_PCX
	if(ext3.CompareNoCase(_T("pcx"))==0)
		return CXIMAGE_FORMAT_PCX;
#endif

#if CXIMAGE_SUPPORT_WBMP
	if(ext4.CompareNoCase(_T("wbmp"))==0)
		return CXIMAGE_FORMAT_WBMP;
#endif

#if CXIMAGE_SUPPORT_WMF
	if(ext3.CompareNoCase(_T("wmf"))==0 || ext3.CompareNoCase(_T("emf"))==0)
		return CXIMAGE_FORMAT_WMF;
#endif

#if CXIMAGE_SUPPORT_J2K
	if(ext3.CompareNoCase(_T("j2k"))==0 || ext3.CompareNoCase(_T("jp2"))==0)
		return CXIMAGE_FORMAT_J2K;
#endif

#if CXIMAGE_SUPPORT_JBG
	if(ext3.CompareNoCase(_T("jbg"))==0)
		return CXIMAGE_FORMAT_JBG;
#endif

#if CXIMAGE_SUPPORT_JP2
	if(ext3.CompareNoCase(_T("j2k"))==0 || ext3.CompareNoCase(_T("jp2"))==0)
		return CXIMAGE_FORMAT_JP2;
#endif

#if CXIMAGE_SUPPORT_JPC
	if(ext3.CompareNoCase(_T("j2c"))==0 || ext3.CompareNoCase(_T("jpc"))==0)
		return CXIMAGE_FORMAT_JPC;
#endif

#if CXIMAGE_SUPPORT_PGX
	if(ext3.CompareNoCase(_T("pgx"))==0)
		return CXIMAGE_FORMAT_PGX;
#endif

#if CXIMAGE_SUPPORT_PNM
	if(ext3.CompareNoCase(_T("pnm"))==0 || ext3.CompareNoCase(_T("pgm"))==0 || ext3.CompareNoCase(_T("ppm"))==0)
		return CXIMAGE_FORMAT_PNM;
#endif

#if CXIMAGE_SUPPORT_RAS
	if(ext3.CompareNoCase(_T("ras"))==0)
		return CXIMAGE_FORMAT_RAS;
#endif

	return CXIMAGE_FORMAT_UNKNOWN;

}


void CUDSSmartCamerav100Dlg::OnDblclkListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	
	//��ȡ˫���ļ�����,���ж������Ƿ�Ϸ�
	int      tem_nSelct = pNMItemActivate->iItem;
	
	if (tem_nSelct>=0 && tem_nSelct<m_conListCtrl.GetItemCount())
	{
		CString  tem_strSlctPath = _T("");
		CString  tem_strFormat   = _T("");
		tem_strFormat   = m_vcBussName[tem_nSelct];
		//���ݺ�׺�ж���ͼ��base64����PDF������PDF�ļ������������Ķ���
		tem_strFormat   = tem_strFormat.Right(3);
		tem_strFormat.MakeUpper();
		if (tem_strFormat == _T("PDF"))
		{
			tem_strSlctPath = m_vcBussName[tem_nSelct];
			ShellExecute(NULL, _T("open"), tem_strSlctPath, NULL, NULL, SW_SHOWNORMAL);
		} 
		else if (tem_strFormat == _T("DCM"))
		{
			tem_strSlctPath = m_vcBussName[tem_nSelct];
			ShellExecute(NULL, _T("open"), tem_strSlctPath, NULL, NULL, SW_SHOWNORMAL);
		}

		else
		{
			tem_strSlctPath =  m_vcBussName[tem_nSelct];
			ShellExecute(NULL, _T("open"), tem_strSlctPath, NULL, NULL, SW_SHOWNORMAL);
		}		
	}
	
	
	
	*pResult = 0;
}


CString CUDSSmartCamerav100Dlg::ShowPDF(CString pdfpath)
{
	
	CString     tem_strImageName;        //ͼ����
	CString     tem_strImagePath;        //ͼ�񵼳�·��
	CString     tem_strResolution;       //ͼ��ֱ���
	CString     tem_strDllPath;
	CString     tem_strDllDoc = m_strDllPath;
	
	int len = WideCharToMultiByte(CP_ACP, 0, pdfpath, pdfpath.GetLength(), NULL, 0, NULL, NULL);
	char*   tem_cPDFFile = new char[len+1];    //����PDF·��+��
	WideCharToMultiByte(CP_ACP, 0, pdfpath, pdfpath.GetLength(), tem_cPDFFile, len, NULL, NULL);
//	tem_cPDFFile[len+1] = '\0';
	tem_cPDFFile[len] = '\0';

	tem_strImageName.Format(_T("%d"), m_nPDfimg);
	tem_strImageName += _T(".jpg");
	tem_strImagePath  = m_strDefaultPath + tem_strImageName;
	len = WideCharToMultiByte(CP_ACP, 0, tem_strImagePath, tem_strImagePath.GetLength(), NULL, 0, NULL, NULL);
	char*   tem_cImage = new char[len+1];       //����ͼ��·��+��
	WideCharToMultiByte(CP_ACP, 0, tem_strImagePath, tem_strImagePath.GetLength(), tem_cImage, len, NULL, NULL);
//	tem_cImage[len+1] = '\0';
	tem_cImage[len] = '\0';

	tem_strResolution = _T("150");
	len = WideCharToMultiByte(CP_ACP, 0, tem_strResolution, tem_strResolution.GetLength(), NULL, 0, NULL, NULL);
	char*   tem_cRes = new char[len+1];
	WideCharToMultiByte(CP_ACP, 0, tem_strResolution, tem_strResolution.GetLength(), tem_cRes, len, NULL, NULL);
//	tem_cRes[len+1] = '\0';
	tem_cRes[len+1] = '\0';
	
	tem_strDllPath = m_strDllPath + _T("gsdll32.dll");
		
	GhostPdf2Image(tem_cPDFFile, tem_cImage, tem_cRes, tem_strDllPath); //����PDF·���� ���ͼ��·���� �ֱ��ʣ� dll·��
	return tem_strImagePath;
}


BOOL WINAPI CUDSSmartCamerav100Dlg::GhostPdf2Image(char* pdfpath, char* imgpath, char* resolution, CString gsdll)
{
	CString tem_strDllPath = gsdll;
	HMODULE hModule = LoadLibrary(tem_strDllPath);
	if (!hModule)
	{
		return FALSE;
	}

	if (!resolution)
	{
		char cResolution[8] = "150x150";
		resolution = cResolution;
	}	

	// *** Declare all the dynamic typedef function pointers
	typedef int (WINAPI *gsapi_new_instance)( char **, int );
	gsapi_new_instance lp_gsapi_new_instance ;
	lp_gsapi_new_instance = (gsapi_new_instance) GetProcAddress(hModule,"gsapi_new_instance");

	typedef int (WINAPI *gsapi_delete_instance) (char *);
	gsapi_delete_instance lp_gsapi_delete_instance;
	lp_gsapi_delete_instance = (gsapi_delete_instance) GetProcAddress(hModule,"gsapi_delete_instance");

	typedef int (WINAPI *gsapi_init_with_args) (char *,int,char *);
	gsapi_init_with_args lp_gsapi_init_with_args;
	lp_gsapi_init_with_args = (gsapi_init_with_args) GetProcAddress(hModule,"gsapi_init_with_args");

	typedef int (WINAPI *gsapi_exit) (char *);
	gsapi_exit lp_gsapi_exit;
	lp_gsapi_exit = (gsapi_exit) GetProcAddress(hModule,"gsapi_exit");

	char ArgResolution[80] = "-r";
	strcat(ArgResolution,resolution);

	char ArgOutputFile[MAX_PATH + 16] = "-sOutputFile=";
	strcat(ArgOutputFile,imgpath);

	const char * gsargv[10];
	int gsargc;
	gsargv[0] = "-dNOPAUSE";  // no prompts
	gsargv[1] = "-dBATCH";    // exit after processing
	gsargv[2] = "-dSAFER";    // Safe mode
	gsargv[3] = ArgResolution;
	gsargv[4] ="-dNOTRANSPARENCY";
	gsargv[5] = "-sDEVICE=jpeg"; 
	gsargv[6] = "-dAdjustWidth=0";
	gsargv[7] = "-dMaxStripSize=999999999";
	gsargv[8] = ArgOutputFile;
	gsargv[9] = pdfpath;
	gsargc=10;

	char *Inst = NULL;
	int code = 0;

	code = (lp_gsapi_new_instance)(&Inst,NULL);
	if (code == 0)
	{
		// Do the conversion
		code = (lp_gsapi_init_with_args) (Inst,gsargc,(char *) gsargv );
		if (code == 0)
			code = (lp_gsapi_exit) (Inst);

		// *** Release the handle
		(lp_gsapi_delete_instance) (Inst);
	}
	if (hModule)
		FreeLibrary(hModule);

	if (code == 0)
		return TRUE;

	return FALSE;
}


CString CUDSSmartCamerav100Dlg::Base642Img(CString txtpath)
{
	CString   tem_strTxtPath = txtpath;
	CString   tem_strImgName;
	CString   tem_strImgPath;

	tem_strImgName.Format(_T("%d"), m_nPDfimg);
	tem_strImgName += _T(".jpg");
	tem_strImgPath  = m_strDefaultPath + tem_strImgName;

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	USES_CONVERSION;  
	LPCWSTR filename = new WCHAR[tem_strTxtPath.GetLength()+1];  
	wcscpy((LPTSTR)filename,T2W((LPTSTR)tem_strTxtPath.GetBuffer(NULL)));  
	tem_strTxtPath.ReleaseBuffer();  
	if (-1!=GetFileAttributes(filename))
	{
		CFile file;
		if(!file.Open(filename,CFile::modeRead))
		{
			return _T("");
		}
		DWORD dwSize = file.GetLength();
		BYTE *buff = new BYTE[file.GetLength()+1];
		file.Read(buff,file.GetLength());
		file.Close();
		CBase64 base;
		int nOut = base.DecodedSize(dwSize);
		char *pOut = new char[nOut];
		ZeroMemory(pOut,nOut);
		base.Decode((char *)buff,dwSize,pOut);

		CFile save(tem_strImgPath, CFile::modeCreate | CFile::modeWrite);
		save.Write(pOut, nOut);
		save.Close();
	}
	else
	{
		return _T("");
	}

	/*
	CString   tem_strTxtPath = _T("D:\\123.txt");
	CString   tem_strImgName;
	CString   tem_strImgPath;

	CFile     data(tem_strTxtPath, CFile::modeReadWrite);
	int len = data.GetLength();
	TCHAR *dv;
	dv = (TCHAR *)malloc(len*sizeof(TCHAR));
	data.Read(dv, len);
	data.Close();

	int slen = (len / 4) * 3;
	slen += 10;
	BYTE * tc;
	tc = (BYTE *)malloc(slen);

	BASE64_Decode(dv, len, tc);
	
	tem_strImgName.Format(_T("%d"), m_nPDfimg);
	tem_strImgName += _T(".jpg");
//	tem_strImgPath  = m_strDefaultPath + tem_strImgName;
	tem_strImgPath  = _T("D:\\123.jpg");
	CFile save(tem_strImgPath, CFile::modeCreate | CFile::modeWrite);
	save.Write(tc, slen);
	save.Close();


	free(tc);
	free(dv);
	*/
	return tem_strImgPath;
}


void CUDSSmartCamerav100Dlg::OnDblclkStaInfopath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString    tem_strSltPath;
	wchar_t    tem_crSltPath[MAX_PATH]; //Unicodeʹ��wchar_t��_t

	ZeroMemory(tem_crSltPath, sizeof(tem_crSltPath));
	BROWSEINFO   m_broseinfo;
	m_broseinfo.hwndOwner = m_hWnd;
	m_broseinfo.pidlRoot  = NULL;
	m_broseinfo.pszDisplayName = tem_crSltPath;
	m_broseinfo.lpszTitle = _T("��ѡ��Ŀ¼"); 
	m_broseinfo.ulFlags   = 0;
	m_broseinfo.lpfn      = NULL;
	m_broseinfo.lParam    = 0;
	m_broseinfo.iImage    = 0;
	LPITEMIDLIST   lp = SHBrowseForFolder(&m_broseinfo);
	if (lp&&SHGetPathFromIDList(lp, tem_crSltPath))
	{
		tem_strSltPath.Format(_T("%s"), tem_crSltPath);
//		tem_strSltPath.Replace(_T("\\"), _T("\\\\"));

		m_strDefaultPath = tem_strSltPath;
		//ע������\\---------------------------------------------------------------------------------------
		::WritePrivateProfileString(_T("Resource"), _T("curdirectory"), m_strDefaultPath, m_strIniPath);
		m_strDefaultPath += _T("\\\\");
		GetDlgItem(IDC_STA_INFOPATH)->SetWindowText(tem_strSltPath);
	} 
	CRect rtlbl; 
	GetDlgItem(IDC_STA_INFOPATH)->GetWindowRect(&rtlbl); 
	ScreenToClient(&rtlbl); //ת���ͻ��˽���
	InvalidateRect(&rtlbl);//���ˢ�¶Ի��򱳾� 
	UpdateWindow();
}


//����ѡ��·����ť��ԭ��Ϊ����˫��STACtrl�ĺ���
void CUDSSmartCamerav100Dlg::OnBnClickedBtnSavepath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString    tem_strSltPath;
	wchar_t    tem_crSltPath[MAX_PATH]; //Unicodeʹ��wchar_t��_t

	ZeroMemory(tem_crSltPath, sizeof(tem_crSltPath));
	BROWSEINFO   m_broseinfo;
	m_broseinfo.hwndOwner = m_hWnd;
	m_broseinfo.pidlRoot  = NULL;
	m_broseinfo.pszDisplayName = tem_crSltPath;
	m_broseinfo.lpszTitle = _T("��ѡ��Ŀ¼"); 
	m_broseinfo.ulFlags   = 0;
	m_broseinfo.lpfn      = NULL;
	m_broseinfo.lParam    = 0;
	m_broseinfo.iImage    = 0;
	LPITEMIDLIST   lp = SHBrowseForFolder(&m_broseinfo);
	if (lp&&SHGetPathFromIDList(lp, tem_crSltPath))
	{
		tem_strSltPath.Format(_T("%s"), tem_crSltPath);
		m_strDefaultPath = tem_strSltPath;
		//ע������\\---------------------------------------------------------------------------------------
		::WritePrivateProfileString(_T("Resource"), _T("curdirectory"), m_strDefaultPath, m_strIniPath);
		//�����C��D�̣����һλ�Դ���\���������
		CString  tem_strLast = m_strDefaultPath;
		tem_strLast = tem_strLast.Right(1);
		if (tem_strLast != _T("\\"))
		{
			m_strDefaultPath += _T("\\");
		}
		
		GetDlgItem(IDC_STA_INFOPATH)->SetWindowText(tem_strSltPath);
	} 
	CRect rtlbl; 
	GetDlgItem(IDC_STA_INFOPATH)->GetWindowRect(&rtlbl); 
	ScreenToClient(&rtlbl); //ת���ͻ��˽���
	InvalidateRect(&rtlbl);//���ˢ�¶Ի��򱳾� 
	UpdateWindow();
}


void CUDSSmartCamerav100Dlg::OnBnClickedBtnMin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_MINIMIZE);
}


void CUDSSmartCamerav100Dlg::OnBnClickedBtnWeb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShellExecute(NULL, _T("open"),  _T("http://www.arc-uds.com"), NULL, NULL,SW_SHOWNORMAL);
}


//���
void CUDSSmartCamerav100Dlg::OnBnClickedBtnDeclear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_BMaxDlg)
	{
		GetWindowRect(&m_rcRectSrc);

		GetDlgItem(IDC_STA_BIAOTI)->GetWindowRect(&m_rcBT);
		
		GetDlgItem(IDC_BTN_DECLEAR)->GetWindowRect(&m_rcMax);
		GetDlgItem(IDC_BTN_MIN)->GetWindowRect(&m_rcMin);
		GetDlgItem(IDC_BTN_TEST2)->GetWindowRect(&m_rcExit);

		GetDlgItem(IDC_BTN_CAPATURE)->GetWindowRect(&m_rcCamera);
		GetDlgItem(IDC_BTN_CAPGOON)->GetWindowRect(&m_rcAutoCamera);
		GetDlgItem(IDC_BTN_CAPBAR)->GetWindowRect(&m_rcBarCamera);
		GetDlgItem(IDC_BTN_CAP2SIDE)->GetWindowRect(&m_rcSideCamera);
		GetDlgItem(IDC_BTN_BROWS)->GetWindowRect(&m_rcBrows);
		GetDlgItem(IDC_BTN_FACEID)->GetWindowRect(&m_rcFaceID);
		GetDlgItem(IDC_BTN_READCARD)->GetWindowRect(&m_rcCard);
		GetDlgItem(IDC_BTN_CARDCOPY)->GetWindowRect(&m_rcCopyCard);

		GetDlgItem(IDC_TAB_SET)->GetWindowRect(&m_rcTab);
		GetDlgItem(IDC_UDS_VIDEOCTRL1)->GetWindowRect(&m_rcCtrl);
		GetDlgItem(IDC_LIST_IMAGE)->GetWindowRect(&m_rcList);

		GetDlgItem(IDC_STA_NUMCOUNT)->GetWindowRect(&m_rcStaCount);
		GetDlgItem(IDC_STA_PAGE)->GetWindowRect(&m_rcStaPage);
		GetDlgItem(IDC_STA_NUMBER)->GetWindowRect(&m_rcStaNumber);
		GetDlgItem(IDC_STA_NOWPATH)->GetWindowRect(&m_rcNowPath);
		GetDlgItem(IDC_STA_INFOPATH)->GetWindowRect(&m_rcShowPath);
		GetDlgItem(IDC_BTN_ZOOMIN)->GetWindowRect(&m_rcZoomIn);
		GetDlgItem(IDC_BTN_ZOOMOUT)->GetWindowRect(&m_rcZoomOut);
		GetDlgItem(IDC_BTN_RECOVER)->GetWindowRect(&m_rcRecover);
		GetDlgItem(IDC_BTN_LROTATE)->GetWindowRect(&m_rcLRotate);
		GetDlgItem(IDC_BTN_RROTATE)->GetWindowRect(&m_rcRRotate);
		GetDlgItem(IDC_BTN_SAVEPATH)->GetWindowRect(&m_rcChange);
		GetDlgItem(IDC_STA_IMAGESIZE)->GetWindowRect(&m_rcImageInfo);

		CRect rcWorkArea; 
		SystemParametersInfo(SPI_GETWORKAREA,0,&rcWorkArea,0); 

		//���¶�������ؼ���λ��
		//1������λ��
		CRect  tem_rcControl;
		tem_rcControl = rcWorkArea;
		tem_rcControl.top    = 10;
		tem_rcControl.left   = 20;
		tem_rcControl.right  = 700;
		tem_rcControl.bottom = 70;
		GetDlgItem(IDC_STA_BIAOTI)->MoveWindow(&tem_rcControl);

		//2������Сͼ��
		tem_rcControl = rcWorkArea;
		tem_rcControl.top    = 5;	
		tem_rcControl.right  -= 5;
		tem_rcControl.left   = tem_rcControl.right-16;
		tem_rcControl.bottom = 21;
		GetDlgItem(IDC_BTN_TEST2)->MoveWindow(&tem_rcControl);

		tem_rcControl = rcWorkArea;
		tem_rcControl.top    = 26;	
		tem_rcControl.right  -= 5;
		tem_rcControl.left   = tem_rcControl.right-16;
		tem_rcControl.bottom = 42;
		GetDlgItem(IDC_BTN_DECLEAR)->MoveWindow(&tem_rcControl);

		tem_rcControl = rcWorkArea;
		tem_rcControl.top    = 47;	
		tem_rcControl.right  -= 5;
		tem_rcControl.left   = tem_rcControl.right-16;
		tem_rcControl.bottom = 63;
		GetDlgItem(IDC_BTN_MIN)->MoveWindow(&tem_rcControl);

		//3�������ť
		tem_rcControl = rcWorkArea;
		tem_rcControl.top    = 14;	
		tem_rcControl.right  -= 30;
		tem_rcControl.left   = tem_rcControl.right-48;
		tem_rcControl.bottom = 62;
		GetDlgItem(IDC_BTN_BROWS)->MoveWindow(&tem_rcControl);

		tem_rcControl = rcWorkArea;
//		tem_rcControl.top    = 14;	
		tem_rcControl.top    = 17;
		tem_rcControl.right  -= 88;
		tem_rcControl.left   = tem_rcControl.right-48;
		tem_rcControl.bottom = 62;
		GetDlgItem(IDC_BTN_FACEID)->MoveWindow(&tem_rcControl);

		tem_rcControl = rcWorkArea;
		tem_rcControl.top    = 14;	
		tem_rcControl.right  -= 146;
		tem_rcControl.left   = tem_rcControl.right-48;
		tem_rcControl.bottom = 62;
		GetDlgItem(IDC_BTN_READCARD)->MoveWindow(&tem_rcControl);

		tem_rcControl = rcWorkArea;
		tem_rcControl.top    = 14;	
		tem_rcControl.right  -= 204;
		tem_rcControl.left   = tem_rcControl.right-48;
		tem_rcControl.bottom = 62;
		GetDlgItem(IDC_BTN_CARDCOPY)->MoveWindow(&tem_rcControl);

		tem_rcControl = rcWorkArea;
		tem_rcControl.top    = 14;	
		tem_rcControl.right  -= 262;
		tem_rcControl.left   = tem_rcControl.right-48;
		tem_rcControl.bottom = 62;
		GetDlgItem(IDC_BTN_CAP2SIDE)->MoveWindow(&tem_rcControl);

		tem_rcControl = rcWorkArea;
		tem_rcControl.top    = 14;	
		tem_rcControl.right  -= 320;
		tem_rcControl.left   = tem_rcControl.right-48;
		tem_rcControl.bottom = 62;
		GetDlgItem(IDC_BTN_CAPBAR)->MoveWindow(&tem_rcControl);

 		tem_rcControl = rcWorkArea;
 		tem_rcControl.top    = 14;	
 		tem_rcControl.right  -= 378;
 		tem_rcControl.left   = tem_rcControl.right-48;
 		tem_rcControl.bottom = 62;
 		GetDlgItem(IDC_BTN_CAPGOON)->MoveWindow(&tem_rcControl);

		tem_rcControl = rcWorkArea;
		tem_rcControl.top    = 14;	
		tem_rcControl.right  -= 436;
		tem_rcControl.left   = tem_rcControl.right-48;
		tem_rcControl.bottom = 62;
		GetDlgItem(IDC_BTN_CAPATURE)->MoveWindow(&tem_rcControl);

		//4�����������ʾ�ؼ�
		tem_rcControl = rcWorkArea;

		CClientDC dc(this);                                    //1010
		int  tem_nCellWidth  = dc.GetDeviceCaps(LOGPIXELSX);   //1010

		if (m_nScreenWidth>1800)
		{
			tem_rcControl.top    = 75;	
			tem_rcControl.bottom-= 50;
			tem_rcControl.left  += 3;
//1010			tem_rcControl.right  = tem_rcControl.left + 340;
		}
		else
		{
			tem_rcControl.top    = 75;	
			tem_rcControl.bottom-= 50;
			tem_rcControl.left  += 3;
//1010			tem_rcControl.right  = tem_rcControl.left + 260;
		}
		tem_rcControl.right = tem_rcControl.left + (int)((tem_nCellWidth*1.0)*2.5); //1010
		
		GetDlgItem(IDC_TAB_SET)->MoveWindow(&tem_rcControl);

		CRect   rcTab;
	    m_conTab.GetClientRect(&rcTab);
	    rcTab.top     += 22;  //�ϲ��������ȫ��ѱ�ǩ�����ǣ���������Tab�ؼ����ñ�ǩ��ɫ

	    //�����Ի����С�ڸ������е�λ��
	    m_iChildNor.MoveWindow(&rcTab);
	    m_iChildAdv.MoveWindow(&rcTab);
	    m_iChildSet.MoveWindow(&rcTab);

		int tem_nCtrlRight;   //�ؼ��²ఴť����
/*ԭʼ����
		tem_rcControl.left   = tem_rcControl.right + 3;
		tem_rcControl.right  = rcWorkArea.right;
		tem_rcControl.right -=266;
*/

//�̶��ߣ��޸Ŀ� ����=9:7
		int tem_nLastHeight= tem_rcControl.Height();
		int tem_nNewWidth  = (tem_nLastHeight*9)/7;
		tem_rcControl.left   = tem_rcControl.right + 3;
		tem_rcControl.right  = tem_rcControl.left + tem_nNewWidth;


    

/*�̶����޸ĸ� ����=16:9
		int tem_nLastHeight= tem_rcControl.Height();
		int tem_nLastTop   = tem_rcControl.top;
		int tem_nOffset    = (tem_nLastHeight- (tem_rcControl.Width()*9/16))/2;
		tem_rcControl.top  = tem_nLastTop;
		tem_rcControl.top += tem_nOffset;
		tem_rcControl.bottom = tem_rcControl.top +tem_rcControl.Width()*9/16;
*/
		tem_nCtrlRight       = tem_rcControl.right;
		GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(&tem_rcControl);

		int tem_nOCXRight = tem_rcControl.right;
		tem_rcControl = rcWorkArea;
		tem_rcControl.top    = 75;	
		tem_rcControl.bottom-= 50;
		tem_rcControl.right -= 3;
//		tem_rcControl.left   = tem_rcControl.right - 260;    ԭʼ
		tem_rcControl.left   = tem_nOCXRight + 6;
		GetDlgItem(IDC_LIST_IMAGE)->MoveWindow(&tem_rcControl);

		tem_rcControl.bottom = rcWorkArea.bottom -4;
		tem_rcControl.top    = tem_rcControl.bottom - 32;
		tem_rcControl.right  = tem_rcControl.left +250;
		GetDlgItem(IDC_STA_IMAGESIZE)->MoveWindow(&tem_rcControl);

		//5��������ʾ����
/*		tem_rcControl = rcWorkArea;			
		tem_rcControl.bottom-= 4;
		tem_rcControl.top    = tem_rcControl.bottom - 15;
		tem_rcControl.left   = 5;
		tem_rcControl.right  = 150;
		GetDlgItem(IDC_STA_NUMCOUNT)->MoveWindow(&tem_rcControl);

		tem_rcControl.left   = 153;
		tem_rcControl.right  = 203;
		GetDlgItem(IDC_STA_NUMBER)->MoveWindow(&tem_rcControl);

		tem_rcControl.left   = 206;
		tem_rcControl.right  = 236;
		GetDlgItem(IDC_STA_PAGE)->MoveWindow(&tem_rcControl);
		
		tem_rcControl.left   = 240;
		tem_rcControl.right  = 350;
		GetDlgItem(IDC_STA_NOWPATH)->MoveWindow(&tem_rcControl);
*/
		//6������������ť�Լ���ַ��ʾ����
		CRect  tem_conCtrl;
		GetDlgItem(IDC_UDS_VIDEOCTRL1)->GetWindowRect(&tem_conCtrl);

		int  tem_nBottom = tem_rcControl.bottom = rcWorkArea.bottom -4;
		int  tem_nTop    = tem_rcControl.top    = tem_rcControl.bottom - 32;
		tem_rcControl.right  = tem_nCtrlRight;
		tem_rcControl.left   = tem_rcControl.right - 32;
		GetDlgItem(IDC_BTN_RROTATE)->MoveWindow(&tem_rcControl);

		tem_rcControl.right  = tem_rcControl.left - 5;
		tem_rcControl.left   = tem_rcControl.right - 32;
		GetDlgItem(IDC_BTN_LROTATE)->MoveWindow(&tem_rcControl);

		tem_rcControl.right  = tem_rcControl.left - 5;
		tem_rcControl.left   = tem_rcControl.right - 32;
		GetDlgItem(IDC_BTN_ZOOMOUT)->MoveWindow(&tem_rcControl);

		tem_rcControl.right  = tem_rcControl.left - 5;
		tem_rcControl.left   = tem_rcControl.right - 32;
		GetDlgItem(IDC_BTN_ZOOMIN)->MoveWindow(&tem_rcControl);

		tem_rcControl.right  = tem_rcControl.left - 5;
		tem_rcControl.left   = tem_rcControl.right - 32;
		GetDlgItem(IDC_BTN_RECOVER)->MoveWindow(&tem_rcControl);

		tem_rcControl.right  = tem_rcControl.left - 5;
		tem_rcControl.left   = tem_rcControl.right - 32;
		GetDlgItem(IDC_BTN_SAVEPATH)->MoveWindow(&tem_rcControl);


// 		tem_rcControl.right  = tem_rcControl.left - 5;
// 		tem_rcControl.left   = 325;
// 		GetDlgItem(IDC_STA_INFOPATH)->MoveWindow(&tem_rcControl);

		tem_rcControl = rcWorkArea;			
		tem_rcControl.bottom = tem_nBottom ;
		tem_rcControl.top    = tem_nTop;
		tem_rcControl.left   = 5;
		tem_rcControl.right  = 150;
		GetDlgItem(IDC_STA_NUMCOUNT)->MoveWindow(&tem_rcControl);

		tem_rcControl.left   = 153;
		tem_rcControl.right  = 203;
		GetDlgItem(IDC_STA_NUMBER)->MoveWindow(&tem_rcControl);

		tem_rcControl.left   = 206;
		tem_rcControl.right  = 236;
		GetDlgItem(IDC_STA_PAGE)->MoveWindow(&tem_rcControl);

		tem_rcControl.left   = 240;
		tem_rcControl.right  = 350;
		GetDlgItem(IDC_STA_NOWPATH)->MoveWindow(&tem_rcControl);

		tem_rcControl.left   = 350;
		tem_rcControl.right  = 800;
		GetDlgItem(IDC_STA_INFOPATH)->MoveWindow(&tem_rcControl);

//		GetDlgItem(IDC_BTN_RROTATE)->MoveWindow(&tem_rcControl);

		m_tipInfo.AddTool(GetDlgItem(IDC_BTN_DECLEAR), _T("�ָ�"));

		MoveWindow(&rcWorkArea);
		m_BMaxDlg = FALSE;
	} 
	else
	{
		MoveWindow(&m_rcRectSrc);

		ScreenToClient(&m_rcBT);
		GetDlgItem(IDC_STA_BIAOTI)->MoveWindow(&m_rcBT);

		ScreenToClient(&m_rcMax);
		GetDlgItem(IDC_BTN_DECLEAR)->MoveWindow(&m_rcMax);
		ScreenToClient(&m_rcMin);
		GetDlgItem(IDC_BTN_MIN)->MoveWindow(&m_rcMin);
		ScreenToClient(&m_rcExit);
		GetDlgItem(IDC_BTN_TEST2)->MoveWindow(&m_rcExit);

		ScreenToClient(&m_rcCamera);
		GetDlgItem(IDC_BTN_CAPATURE)->MoveWindow(&m_rcCamera);
		ScreenToClient(&m_rcAutoCamera);
		GetDlgItem(IDC_BTN_CAPGOON)->MoveWindow(&m_rcAutoCamera);
		ScreenToClient(&m_rcBarCamera);
		GetDlgItem(IDC_BTN_CAPBAR)->MoveWindow(&m_rcBarCamera);
		ScreenToClient(&m_rcSideCamera);
		GetDlgItem(IDC_BTN_CAP2SIDE)->MoveWindow(&m_rcSideCamera);
		ScreenToClient(&m_rcBrows);
		GetDlgItem(IDC_BTN_BROWS)->MoveWindow(&m_rcBrows);
		ScreenToClient(m_rcFaceID);
		GetDlgItem(IDC_BTN_FACEID)->MoveWindow(m_rcFaceID);
		ScreenToClient(&m_rcCard);
		GetDlgItem(IDC_BTN_READCARD)->MoveWindow(&m_rcCard);
		ScreenToClient(&m_rcCopyCard);
		GetDlgItem(IDC_BTN_CARDCOPY)->MoveWindow(&m_rcCopyCard);

		ScreenToClient(&m_rcTab);
		GetDlgItem(IDC_TAB_SET)->MoveWindow(&m_rcTab);
		ScreenToClient(&m_rcCtrl);
		GetDlgItem(IDC_UDS_VIDEOCTRL1)->MoveWindow(&m_rcCtrl);
		ScreenToClient(&m_rcList);
		GetDlgItem(IDC_LIST_IMAGE)->MoveWindow(&m_rcList);

		ScreenToClient(&m_rcStaCount);
		GetDlgItem(IDC_STA_NUMCOUNT)->MoveWindow(&m_rcStaCount);
		ScreenToClient(&m_rcStaPage);
		GetDlgItem(IDC_STA_PAGE)->MoveWindow(&m_rcStaPage);
		ScreenToClient(&m_rcStaNumber);
		GetDlgItem(IDC_STA_NUMBER)->MoveWindow(&m_rcStaNumber);
		ScreenToClient(&m_rcNowPath);
		GetDlgItem(IDC_STA_NOWPATH)->MoveWindow(&m_rcNowPath);
		ScreenToClient(&m_rcShowPath);
		GetDlgItem(IDC_STA_INFOPATH)->MoveWindow(&m_rcShowPath);
		ScreenToClient(&m_rcLRotate);
		GetDlgItem(IDC_BTN_LROTATE)->MoveWindow(&m_rcLRotate);
		ScreenToClient(&m_rcZoomOut);
		GetDlgItem(IDC_BTN_ZOOMOUT)->MoveWindow(&m_rcZoomOut);
		ScreenToClient(&m_rcZoomIn);
		GetDlgItem(IDC_BTN_ZOOMIN)->MoveWindow(&m_rcZoomIn);
		ScreenToClient(&m_rcRecover);
		GetDlgItem(IDC_BTN_RECOVER)->MoveWindow(&m_rcRecover);
		ScreenToClient(&m_rcRRotate);
		GetDlgItem(IDC_BTN_RROTATE)->MoveWindow(&m_rcRRotate);
		ScreenToClient(&m_rcChange);
		GetDlgItem(IDC_BTN_SAVEPATH)->MoveWindow(&m_rcChange);
		ScreenToClient(&m_rcImageInfo);
		GetDlgItem(IDC_STA_IMAGESIZE)->MoveWindow(&m_rcImageInfo);

		m_tipInfo.AddTool(GetDlgItem(IDC_BTN_DECLEAR), _T("���"));

		m_BMaxDlg = TRUE;
	}
	ThumbaiList(m_nThumbWidth, m_nThumbHeight);
}


LRESULT CUDSSmartCamerav100Dlg::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ 
	UINT nHitTest = CDialog::OnNcHitTest(point);

	// �������ڴ��ڿͻ������򷵻ر��������Ÿ�Windows
	// ʹWindows������ڱ�����������д������ɵ����ƶ�����
	return (nHitTest==HTCLIENT) ? HTCAPTION : nHitTest;


//	return CDialogEx::OnNcHitTest(point);
}


void CUDSSmartCamerav100Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	PostMessage(WM_NCLBUTTONDOWN,   HTCAPTION,   MAKELPARAM(point.x,  point.y));  

//	CDialogEx::OnLButtonDown(nFlags, point);
}


void CUDSSmartCamerav100Dlg::OnDeleteitemListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CUDSSmartCamerav100Dlg::OnClickListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	BOOL    tem_BRepeat = FALSE;
	CString tem_strSlcFile;
	std::vector<int>::iterator       item_nIndex;
	
	//���ctrl�������£�˵��Ҫ����PDF���ҳTIF��ÿ�δ���vector��ӦӦ���������
	if (pNMItemActivate->uKeyFlags == LVKF_CONTROL)
	{
		m_nSlctItem = pNMItemActivate->iItem;
		if (m_nSlctItem>=0 && m_nSlctItem<m_conListCtrl.GetItemCount())
		{
			//�ж��Ƿ�Ϊ���ε�������ε��Ϊ��ѡ���ļ�
			for (item_nIndex=m_vcCtrlInex.begin(); item_nIndex!=m_vcCtrlInex.end(); item_nIndex++)
			{
				if (m_nSlctItem == *item_nIndex)
				{
					tem_BRepeat = TRUE;
					m_vcCtrlInex.erase(item_nIndex);
					break;
				}
			}
			if (tem_BRepeat)
			{
				//���ظ���
				tem_BRepeat = FALSE;
			}
			else
			{
				//���ظ���
				m_vcCtrlInex.push_back(m_nSlctItem);
			}
		}
	}
	else
	{
		m_vcCtrlInex.clear();
		m_nSlctItem = pNMItemActivate->iItem;
		if (m_nSlctItem>=0 && m_nSlctItem<m_conListCtrl.GetItemCount())
		{
			m_vcCtrlInex.push_back(m_nSlctItem);
			//��ʾ����ͼ���С

			CString   tem_strFilePath = m_vcBussName[m_nSlctItem];
			ShowImageSize(tem_strFilePath);
		}

	}
	
	*pResult = 0;
}


void CUDSSmartCamerav100Dlg::OnRclickListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_vcCtrlInex.clear();
	POSITION   pos;
	pos = m_conListCtrl.GetFirstSelectedItemPosition();
	while (pos)
	{
		int  tem_nIndex = (int)pos-1;
		m_vcCtrlInex.push_back(tem_nIndex);
		m_conListCtrl.GetNextSelectedItem(pos);		
	}
	m_nSlctItem = pNMItemActivate->iItem;
	//����ͼ�Ҽ���������Ҽ�����˵�
	if (m_nSlctItem>=0 && m_nSlctItem<m_conListCtrl.GetItemCount())
	{
		CPoint   tem_ptRight;
		GetCursorPos(&tem_ptRight);
		m_menuRightClick.TrackPopMenu(tem_ptRight.x, tem_ptRight.y);
	}
	*pResult = 0;
}


void CUDSSmartCamerav100Dlg::OnCopyIt()
{
	// TODO: �ڴ���������������
	if (m_vcCtrlInex.size()==0)
	{
		m_vcCtrlInex.clear();
		return;
	}
	std::vector<CString>            tem_vcFilesList;
	std::vector<int>::iterator      tem_nitem;
	for (tem_nitem=m_vcCtrlInex.begin(); tem_nitem!=m_vcCtrlInex.end(); tem_nitem++)
	{
		CString tem_strPath = m_vcBussName[*tem_nitem];
		tem_vcFilesList.push_back(tem_strPath);
	}
	CopyFiles2Clipboard(tem_vcFilesList);
	m_vcCtrlInex.clear();
	
}


void CUDSSmartCamerav100Dlg::OnDeleteIt()
{
	// TODO: �ڴ���������������
	if (m_vcCtrlInex.size() == 0)
	{
		return;
	}
	if (IDOK !=m_iDeleteTip.DoModal())
	{
		return;
	}
	//ɾ��ָ���ļ�
	SHFILEOPSTRUCT FileOp;
	BOOL           m_BRC;    //ReturnCode����������
	CString        strSrcPath;
    //ɾ��������վ
	std::vector<int>::iterator  tem_nIndex;
	for (tem_nIndex=m_vcCtrlInex.begin(); tem_nIndex!=m_vcCtrlInex.end(); tem_nIndex++)
	{
		int tem_nDeleteItem = *tem_nIndex;
		
		strSrcPath  = m_vcBussName[tem_nDeleteItem];

		strSrcPath += '\0';

		CString  tem_strDstPath;
		tem_strDstPath = '\0';     //ɾ��������ֱ����ΪNULL

		CString     tem_strTitle;
		tem_strTitle = _T("����ɾ��...");
		tem_strTitle += '\0';

		FileOp.fFlags = FOF_ALLOWUNDO|FOF_MULTIDESTFILES|FOF_SIMPLEPROGRESS|FOF_NOCONFIRMATION;

		FileOp.lpszProgressTitle = tem_strTitle;
		FileOp.hwnd              = m_hWnd;
		FileOp.hNameMappings     = NULL;
		FileOp.pFrom             = strSrcPath;
		FileOp.pTo               = tem_strDstPath;    //Ŀ��Ŀ¼
		FileOp.wFunc             = FO_DELETE;

		//������ʾ--------------------------------------------------


		m_BRC = SHFileOperation(&FileOp);
		if (!FileOp.fAnyOperationsAborted)
		{
			if(m_BRC)   
			{
				//�������ִ���
			}		
		}
		else
		{
			//����������ֹ
		}

	}

	//��m_vcCtrlIndex���дӴ�С������ɾ��vector��Ϣ����ɾ��������ɾ��ǰ���Ԫ��Ӱ������λ��
	//ʹ��sort�ͷ����������vector�Ž���
	sort(m_vcCtrlInex.rbegin(), m_vcCtrlInex.rend());
	for (tem_nIndex=m_vcCtrlInex.begin(); tem_nIndex!=m_vcCtrlInex.end(); tem_nIndex++)
	{	
		m_vcFileName.erase(m_vcFileName.begin()+*tem_nIndex);
		m_vcWholeName.erase(m_vcWholeName.begin()+*tem_nIndex);
		m_vcBussName.erase(m_vcBussName.begin()+*tem_nIndex);
	}

	
	ThumbaiList(m_nThumbWidth, m_nThumbHeight);
	m_vcCtrlInex.clear();
	//�����²�ҳ����ʾ
	int       tem_nPageNumber;
	CString   tem_strPageNumber;
	m_nImageCount--;
	tem_nPageNumber = m_nImageCount + m_nImageCountOther;
	tem_strPageNumber.Format(_T("%d"), tem_nPageNumber);
	GetDlgItem(IDC_STA_NUMBER)->SetWindowText(tem_strPageNumber);


	CRect rtlbl; 
	GetDlgItem(IDC_STA_NUMBER)->GetWindowRect(&rtlbl); 
	ScreenToClient(&rtlbl); //ת���ͻ��˽���
	InvalidateRect(&rtlbl);//���ˢ�¶Ի��򱳾� 
	UpdateWindow();
	
}


void CUDSSmartCamerav100Dlg::OnRename()
{
	// TODO: �ڴ���������������
	if (m_vcCtrlInex.size()==0)
	{
		return;
	}


	m_nLastSlcFile = m_vcCtrlInex.back();    //�ó����һ��ѡ���ļ�������
	m_conListCtrl.SetFocus();
	m_conRename = m_conListCtrl.EditLabel(m_nLastSlcFile);


	m_vcCtrlInex.clear();
}


void CUDSSmartCamerav100Dlg::OnProperty()
{
	// TODO: �ڴ���������������
	int       tem_nLastFile;
	CString   tem_strLastFile;

	if (m_vcCtrlInex.size()==0)
	{
		return;
	}
	tem_nLastFile = m_vcCtrlInex.back();
	tem_strLastFile = m_vcBussName[tem_nLastFile];  //��ȡ

	SHELLEXECUTEINFO   sei; 
	sei.hwnd   =   this->GetSafeHwnd(); 
	sei.lpVerb   =  TEXT( "properties"); 
	sei.lpFile   =   tem_strLastFile; 
	sei.lpDirectory   =   NULL; 
	sei.lpParameters   =  NULL; 
	sei.nShow   =   SW_SHOWNORMAL; 
	sei.fMask   =   SEE_MASK_INVOKEIDLIST ; 
	sei.lpIDList   =   NULL; 
	sei.cbSize   =   sizeof(SHELLEXECUTEINFO); 
	ShellExecuteEx(&sei);

	m_vcCtrlInex.clear();


//	ShellExecute(NULL, _T("properties"), _T("����.png"), NULL, NULL, SW_SHOWNORMAL);
}


void CUDSSmartCamerav100Dlg::On32775Word()
{
	// TODO: �ڴ���������������
	if (m_vcCtrlInex.size()==0)
	{
		return;
	}
	int       tem_nFileIndex  = 0;
	CString   tem_strFileName = _T("");
	CString   tem_strFilePath = _T("");
	
	//a����ȡ�ļ�����
	std::vector<int>::iterator tem_nItem;
	for (tem_nItem=m_vcCtrlInex.begin(); tem_nItem!=m_vcCtrlInex.end(); tem_nItem++)
	{
		tem_nFileIndex = *tem_nItem;
		tem_strFileName = m_vcFileName[tem_nFileIndex];
		tem_strFilePath = m_vcBussName[tem_nFileIndex];
		
		//�ж��ļ��Ƿ�Ϊͼ���ļ�
		CString   tem_strMiddle  = tem_strFilePath;
		LPWSTR    tem_wstrOutDoc;
		CString   tem_strOutTxt;                 //����txt·��
		CString   tem_strOutWord = _T("");       //����word·��
		int       tem_nIndex    = tem_strMiddle.ReverseFind('.');
		if (tem_nIndex != -1)
		{
			tem_strMiddle = tem_strMiddle.Mid(tem_nIndex+1);
			tem_strMiddle.MakeLower();
//			tem_strFilePath = _T("C:\Users\Administrator\Desktop\OCR����\\��_0002.jpg");
			if (tem_strMiddle == _T("jpg") || tem_strMiddle == _T("jpeg")||
				tem_strMiddle == _T("bmp") || tem_strMiddle == _T("png") )	
			{
				//����txt·��������txt�ļ�
				tem_strOutTxt  = m_strBufferPath;
				tem_strOutTxt += tem_strFileName;
				tem_strOutTxt += _T(".txt");
				Self_OcrRecognize(tem_strFilePath, tem_strOutTxt);			
				
				//����doc·��������word�ļ�
				tem_strMiddle = tem_strFilePath;
				tem_wstrOutDoc = tem_strMiddle.GetBuffer();
				PathRemoveFileSpec(tem_wstrOutDoc);
				tem_strOutWord  = tem_wstrOutDoc;
				tem_strOutWord += _T("\\");
				tem_strOutWord += tem_strFileName;
				tem_strOutWord += _T(".doc");

				Self_Write2Office(tem_strOutTxt, tem_strOutWord);

				m_vcOcrBuffer.push_back(tem_strOutTxt);
			}
			else if (tem_strMiddle == _T("tif") || tem_strMiddle == _T("tiff"))
			{
				//����txt·��������txt�ļ�
				tem_strOutTxt  = m_strBufferPath;
				tem_strOutTxt += tem_strFileName;
				tem_strOutTxt += _T(".txt");

				//��tif�ļ�ת��Ϊjpg
				CxImage   tem_cxImg;
				tem_cxImg.Load(tem_strFilePath);

				wchar_t*  tem_wstrNewPath = tem_strFilePath.GetBuffer();
				tem_strFilePath.ReleaseBuffer();
				PathRemoveExtension(tem_wstrNewPath);
				CString   tem_strNewPath            = tem_wstrNewPath;
				tem_strNewPath           += _T(".jpg");
	
				tem_cxImg.Save(tem_strNewPath, CXIMAGE_FORMAT_JPG);

				Self_OcrRecognize(tem_strNewPath, tem_strOutTxt);			

				//����doc·��������word�ļ�
				tem_strMiddle = tem_strFilePath;
				tem_wstrOutDoc = tem_strMiddle.GetBuffer();
				PathRemoveFileSpec(tem_wstrOutDoc);
				tem_strOutWord  = tem_wstrOutDoc;
				tem_strOutWord += _T("\\");
				tem_strOutWord += tem_strFileName;
				tem_strOutWord += _T(".doc");

				Self_Write2Office(tem_strOutTxt, tem_strOutWord);

				m_vcOcrBuffer.push_back(tem_strOutTxt);

				DeleteFile(tem_strNewPath);
			}
		}		
	}
	MessageBox(_T("������ϣ�"), _T("��ͼUDS"),MB_OK);
}


void CUDSSmartCamerav100Dlg::On32776Excel()
{
	// TODO: �ڴ���������������
	if (m_vcCtrlInex.size()==0)
	{
		return;
	}
	int       tem_nFileIndex  = 0;
	CString   tem_strFileName = _T("");
	CString   tem_strFilePath = _T("");

	//a����ȡ�ļ�����
	std::vector<int>::iterator tem_nItem;
	for (tem_nItem=m_vcCtrlInex.begin(); tem_nItem!=m_vcCtrlInex.end(); tem_nItem++)
	{
		tem_nFileIndex = *tem_nItem;
		tem_strFileName = m_vcFileName[tem_nFileIndex];
		tem_strFilePath = m_vcBussName[tem_nFileIndex];

		//�ж��ļ��Ƿ�Ϊͼ���ļ�
		CString   tem_strMiddle  = tem_strFilePath;
		LPWSTR    tem_wstrOutDoc;
		CString   tem_strOutTxt;                 //����txt·��
		CString   tem_strOutWord = _T("");       //����word·��
		int       tem_nIndex    = tem_strMiddle.ReverseFind('.');
		if (tem_nIndex != -1)
		{
			tem_strMiddle = tem_strMiddle.Mid(tem_nIndex+1);
			tem_strMiddle.MakeLower();
			if (tem_strMiddle == _T("jpg") || tem_strMiddle == _T("jpeg")||
				tem_strMiddle == _T("tif") || tem_strMiddle == _T("tiff")||
				tem_strMiddle == _T("bmp") || tem_strMiddle == _T("png") )	
			{
				//����txt·��������txt�ļ�
				tem_strOutTxt  = m_strBufferPath;
				tem_strOutTxt += tem_strFileName;
				tem_strOutTxt += _T(".txt");
//				m_conVideoOcx.OcrRecognizeEx(tem_strFilePath, tem_strOutTxt);
				Self_OcrRecognize(tem_strFilePath, tem_strOutTxt);

				//����doc·��������excel�ļ�
				tem_strMiddle = tem_strFilePath;
				tem_wstrOutDoc = tem_strMiddle.GetBuffer();
				PathRemoveFileSpec(tem_wstrOutDoc);
				tem_strOutWord  = tem_wstrOutDoc;
				tem_strOutWord += _T("\\");
				tem_strOutWord += tem_strFileName;
				tem_strOutWord += _T(".xls");

				Self_Write2Office(tem_strOutTxt, tem_strOutWord);

				m_vcOcrBuffer.push_back(tem_strOutTxt);
			}
		}		
	}
	MessageBox(_T("������ϣ�"), _T("��ͼUDS"),MB_OK);
}


void CUDSSmartCamerav100Dlg::Self_OcrRecognize(CString imgpath, CString txtpath)
{
	//������·��ת��Ϊconst char*----------------------------------------------
	CStringA    tem_straImgPath(imgpath.GetBuffer(0));  imgpath.ReleaseBuffer();   //GetBuffer(0)���Ǵ����0��ʼ�����Ǵ�������������0���ַ���Ҳ���ǲ��ö���//���ö�����˼��ԭ����buffer�ж�󣬷��ض��
	string      tem_sImgPath = tem_straImgPath.GetBuffer(0);
	const char* tem_cImgPath = tem_sImgPath.c_str();
	
	//��ʼ��OCR����------------------------------------------------------------
	wchar_t tem_lpInpath[MAX_PATH]={0};
	GetModuleFileName(AfxGetStaticModuleState()->m_hCurrentInstanceHandle, tem_lpInpath, MAX_PATH);
	PathRemoveFileSpec(tem_lpInpath);

	CString     tem_strInpath = tem_lpInpath;
	CStringA    tem_straInpath(tem_strInpath.GetBuffer(0));   tem_strInpath.ReleaseBuffer();
	string      tem_sInpath   = tem_straInpath.GetBuffer(0);
	const char* tem_cInput = tem_sInpath.c_str();
	
	m_api = new tesseract::TessBaseAPI();
	if (m_api->Init(tem_cInput, "data\\chi_sim"))
//	if (m_api->Init(tem_cInput, "data\\eng"))                //Ӣ�Ŀ⣬��ǰchi_simҲ��ʶ��Ӣ�ģ����Ӣ�Ŀ���δ��
 	{
 		MessageBox(_T("��ʼ��tesseractʧ�ܣ�"),_T("UDS"), MB_OK);
 		return;
 	}
	m_BOcrOpened = TRUE;

	//��ȡͼ����ʶ��-----------------------------------------------------------
	m_image = pixRead(tem_cImgPath);
	m_api->SetImage(m_image);
//	m_api->SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
//	m_api->SetRectangle(0, 0, 100, 100);    //����ʶ������

	char*      tem_cOutText;
	wchar_t*   tem_cTemp;
	CString    tem_strResult;
	tem_cOutText  = m_api->GetUTF8Text();               //0�����������ı�
	tem_cTemp     = Utf_8ToUnicode(tem_cOutText);       //1����һ�θ�ʽת��char*��>wchar_t*

	char*       tem_cTextAni;
	tem_cTextAni  = UnicodeToAnsi(tem_cTemp);           //2���ڶ��θ�ʽת��wchar_t*��>char*,   Unicode2Ansi

	USES_CONVERSION;
 	CString    tem_strText;
	tem_strText = A2T(tem_cTextAni);                    //3�������θ�ʽת��char*��>CString,	

	//��ʶ����ַ���������ָ����txt�ļ�-----------------------------------------
#ifdef _UNICODE
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );
#endif

	CStdioFile     tem_fileTxt;
	CFileException tem_Error;      
	tem_fileTxt.Open(txtpath, CFile::modeCreate|CFile::modeReadWrite, &tem_Error);
	tem_fileTxt.WriteString(tem_strText);                //û������ת��������ı�д��txt�ļ������ܻᱻ�ض�
	tem_fileTxt.Close();
	
#ifdef _UNICODE
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//��ԭ�����趨
#endif


	m_api->End();
	pixDestroy(&m_image);
}


wchar_t* CUDSSmartCamerav100Dlg::Utf_8ToUnicode(char* szU8)
{
	//UTF8 to Unicode  
	//��������ֱ�Ӹ��ƹ���������룬��������ʱ�ᱨ���ʲ���16������ʽ  

	//Ԥת�����õ�����ռ�Ĵ�С  
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);  
	//����ռ�Ҫ��'\0'�����ռ䣬MultiByteToWideChar�����'\0'�ռ�  
	wchar_t* wszString = new wchar_t[wcsLen + 1];  
	//ת��  
	::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);  
	//������'\0'  
	wszString[wcsLen] = '\0';  
	return wszString;  
}


//�����ֽ�wchar_t*ת��Ϊ���ֽ�char*  
char* CUDSSmartCamerav100Dlg::UnicodeToAnsi(const wchar_t* szStr)
{
	int nLen = WideCharToMultiByte( CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL );    
	if (nLen == 0)    
	{    
		return NULL;    
	}    
	char* pResult = new char[nLen];    

	WideCharToMultiByte( CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL );    

	return pResult;    
}


void CUDSSmartCamerav100Dlg::Self_Write2Office(CString txtpath, CString officepath)
{
	CString      tem_strOfficePath = officepath;   //���·��
	CString      tem_strPath;                      //txt+office����·������

	CString      tem_strExePath;
	TCHAR        tem_tcFilepath[MAX_PATH+1] = {0};
	GetModuleFileName(NULL, tem_tcFilepath, MAX_PATH);
	(_tcsrchr(tem_tcFilepath, _T('\\')))[1] = 0;

	tem_strExePath    = tem_tcFilepath;
	tem_strExePath   += _T("TxtToOffice.exe");   //�����ļ�·��


	tem_strPath.Format(_T("\"%s\" \"%s\""),txtpath, tem_strOfficePath);   //\"ת���ַ���\"=".������˫����֮�䣬�������ŵ�������������������

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
}


void CUDSSmartCamerav100Dlg::On32777AutoRotate()
{
	// TODO: �ڴ���������������
	/*
	if (m_vcCtrlInex.size()==0)
	{
		return;
	}
	int       tem_nFileIndex  = 0;
	CString   tem_strFileName = _T("");
	CString   tem_strFilePath = _T("");

	//a����ȡ�ļ�����
	std::vector<int>::iterator tem_nItem;
	for (tem_nItem=m_vcCtrlInex.begin(); tem_nItem!=m_vcCtrlInex.end(); tem_nItem++)
	{
		tem_nFileIndex = *tem_nItem;
		tem_strFileName = m_vcFileName[tem_nFileIndex];
		tem_strFilePath = m_vcBussName[tem_nFileIndex];

		//�ж��ļ��Ƿ�Ϊͼ���ļ�
		CString   tem_strMiddle  = tem_strFilePath;
		LPWSTR    tem_wstrOutDoc;
		int       tem_nIndex    = tem_strMiddle.ReverseFind('.');
		if (tem_nIndex != -1)
		{
			tem_strMiddle = tem_strMiddle.Mid(tem_nIndex+1);
			tem_strMiddle.MakeLower();
			if (tem_strMiddle == _T("jpg") || tem_strMiddle == _T("jpeg")||
				tem_strMiddle == _T("tif") || tem_strMiddle == _T("tiff")||
				tem_strMiddle == _T("bmp") || tem_strMiddle == _T("png") )	
			{	
				Self_AutoRotate(tem_strFilePath);
			}
		}		
	}
	*/
}


void CUDSSmartCamerav100Dlg::Self_AutoRotate(CString imgpath)
{
	//������·��ת��Ϊconst char*----------------------------------------------
	CStringA    tem_straImgPath(imgpath.GetBuffer(0));  imgpath.ReleaseBuffer();   //GetBuffer(0)���Ǵ����0��ʼ�����Ǵ�������������0���ַ���Ҳ���ǲ��ö���//���ö�����˼��ԭ����buffer�ж�󣬷��ض��
	string      tem_sImgPath = tem_straImgPath.GetBuffer(0);
	const char* tem_cImgPath = tem_sImgPath.c_str();

	tesseract::Orientation        tem_Orientation;
	tesseract::WritingDirection   tem_Direction;
	tesseract::TextlineOrder      tem_Oder;
	float                         tem_fAngle;
	PIX*                          tem_pImage = pixRead(tem_cImgPath);

	tesseract::TessBaseAPI*       tem_pAPI   = new tesseract::TessBaseAPI();

	//��ʼ��-------------------------------------------------------------------
	wchar_t tem_lpInpath[MAX_PATH]={0};
	GetModuleFileName(AfxGetStaticModuleState()->m_hCurrentInstanceHandle, tem_lpInpath, MAX_PATH);
	PathRemoveFileSpec(tem_lpInpath);

	CString     tem_strInpath = tem_lpInpath;
	CStringA    tem_straInpath(tem_strInpath.GetBuffer(0));   tem_strInpath.ReleaseBuffer();
	string      tem_sInpath   = tem_straInpath.GetBuffer(0);
	const char* tem_cInput = tem_sInpath.c_str();
	tem_pAPI->Init(tem_cInput, "data\\chi_sim");

	if (tem_pAPI != NULL)
	{
		int    tem_nAnle = 0;
		tem_pAPI->SetPageSegMode(tesseract::PSM_AUTO_OSD);
		tem_pAPI->SetImage(tem_pImage);
		tesseract::PageIterator* item = tem_pAPI->AnalyseLayout();
		item->Orientation(&tem_Orientation, &tem_Direction, &tem_Oder, &tem_fAngle);

		if (tem_Orientation == 0)
		{
			MessageBox(_T("��"));
		}
		else if (tem_Orientation == 1)
		{
//			MessageBox(_T("��90"));
			tem_nAnle = 90;
		}
		else if (tem_Orientation == 2)
		{
//			MessageBox(_T("180"));
			tem_nAnle = 180;
		}
		else if (tem_Orientation == 3)
		{
//			MessageBox(_T("��90"));
			tem_nAnle = 270;
		}

		//����ͼ��
		CxImage   tem_cxImage;
		tem_cxImage.Load(imgpath, 0);

		//��תͼ��
		tem_cxImage.Rotate(tem_fAngle);

		//����ͼ��
//		tem_cxImage.Save(imgpath);

		//��������ͼ

		//ˢ������ͼ
	}

	tem_pAPI->End();
	pixDestroy(&tem_pImage);
}


//�Ҽ��˵�-����90��
void CUDSSmartCamerav100Dlg::On32778RightRotateL()
{
	// TODO: �ڴ���������������
	//��ȡ����
	if (m_vcCtrlInex.size()==0)
	{
		return;
	}
	int       tem_nFileIndex  = 0;
	CString   tem_strThumPath = _T("");
	CString   tem_strFilePath = _T("");

	//a����ȡ�ļ�����
	std::vector<int>::iterator tem_nItem;
	for (tem_nItem=m_vcCtrlInex.begin(); tem_nItem!=m_vcCtrlInex.end(); tem_nItem++)
	{
		tem_nFileIndex = *tem_nItem;
		tem_strThumPath = m_vcWholeName[tem_nFileIndex];
		tem_strFilePath = m_vcBussName[tem_nFileIndex];

		//�ж��ļ��Ƿ�Ϊͼ���ļ�
		CString   tem_strMiddle  = tem_strFilePath;
		int       tem_nIndex    = tem_strMiddle.ReverseFind('.');
		if (tem_nIndex != -1)
		{
			tem_strMiddle = tem_strMiddle.Mid(tem_nIndex+1);
			tem_strMiddle.MakeLower();
			if (tem_strMiddle == _T("jpg") || tem_strMiddle == _T("jpeg")||
				tem_strMiddle == _T("bmp") || tem_strMiddle == _T("png") ||
				tem_strMiddle == _T("tif") || tem_strMiddle == _T("tiff"))	
			{
				CxImage  tem_cxThumb, tem_cxFile;
				tem_cxThumb.Load(tem_strThumPath, CMAX_IMAGE_FORMATS);
				tem_cxThumb.RotateLeft();
				tem_cxFile.Load(tem_strFilePath, CMAX_IMAGE_FORMATS);
				tem_cxFile.RotateLeft();

				if (tem_strMiddle == _T("jpg") || tem_strMiddle == _T("jpeg"))
				{
					tem_cxFile.SetJpegQuality(m_nJpegQulity);

				} 
				tem_cxThumb.Save(tem_strThumPath, CXIMAGE_FORMAT_JPG);
				tem_cxFile.Save(tem_strFilePath, GetTypeFromFileName(tem_strFilePath));

				//����ˢ��ListCtrl�ؼ�
				Self_ReplaceImage(m_nThumbWidth, m_nThumbHeight, tem_nFileIndex);
			}
			else
			{
				MessageBox(_T("�޷�����PDF/DCM/Base64�ĵ���"), _T("UDS"), MB_OK);
			}

		}	
		
	}
}


//�Ҽ��˵�-����90��
void CUDSSmartCamerav100Dlg::On32779RightRotateR()
{
	// TODO: �ڴ���������������
	//��ȡ����
	if (m_vcCtrlInex.size()==0)
	{
		return;
	}
	int       tem_nFileIndex  = 0;
	CString   tem_strThumPath = _T("");
	CString   tem_strFilePath = _T("");

	//a����ȡ�ļ�����
	std::vector<int>::iterator tem_nItem;
	for (tem_nItem=m_vcCtrlInex.begin(); tem_nItem!=m_vcCtrlInex.end(); tem_nItem++)
	{
		tem_nFileIndex = *tem_nItem;
		tem_strThumPath = m_vcWholeName[tem_nFileIndex];
		tem_strFilePath = m_vcBussName[tem_nFileIndex];

		//�ж��ļ��Ƿ�Ϊͼ���ļ�
		CString   tem_strMiddle  = tem_strFilePath;
		int       tem_nIndex    = tem_strMiddle.ReverseFind('.');
		if (tem_nIndex != -1)
		{
			tem_strMiddle = tem_strMiddle.Mid(tem_nIndex+1);
			tem_strMiddle.MakeLower();
			if (tem_strMiddle == _T("jpg") || tem_strMiddle == _T("jpeg")||
				tem_strMiddle == _T("bmp") || tem_strMiddle == _T("png") ||
				tem_strMiddle == _T("tif") || tem_strMiddle == _T("tiff"))	
			{
				CxImage  tem_cxThumb, tem_cxFile;
				tem_cxThumb.Load(tem_strThumPath, CMAX_IMAGE_FORMATS);
				tem_cxThumb.RotateRight();
				tem_cxFile.Load(tem_strFilePath, CMAX_IMAGE_FORMATS);
				tem_cxFile.RotateRight();
				if (tem_strMiddle == _T("jpg") || tem_strMiddle == _T("jpeg"))
				{
					tem_cxFile.SetJpegQuality(m_nJpegQulity);

				} 
				tem_cxThumb.Save(tem_strThumPath, CXIMAGE_FORMAT_JPG);
				tem_cxFile.Save(tem_strFilePath, GetTypeFromFileName(tem_strFilePath));
				//����ˢ��ListCtrl�ؼ�
				Self_ReplaceImage(m_nThumbWidth, m_nThumbHeight, tem_nFileIndex);
			}
			else
			{
				MessageBox(_T("�޷�����PDF/DCM/Base64�ĵ���"), _T("UDS"), MB_OK);
			}
		}	
		
	}
}


BOOL CUDSSmartCamerav100Dlg::CreateHSMenu(void)
{
	COLORREF    tem_clrSet0 = RGB(185,205,246);   //��ɫ
	COLORREF    tem_clrSet1 = RGB(222,160,228);   //ѡ����ɫ
	COLORREF    tem_clrSet2 = RGB(131,88,136);    //��֧ҹɫ

	HWND hwnd = GetSafeHwnd();
	m_menuRightClick.CreateMenu( hwnd );
	CHSMenu::SetMenuItemHeight(28);  //����Menu�߶�
	CHSMenuPro::SetColor(CLR_BKGNDMENU, tem_clrSet0); //���õ�ɫ
	CHSMenuPro::SetColor(CLR_BKGNDSEL, tem_clrSet1);	//���ñ�ѡ��ʱ��ɫ
	CHSMenuPro::SetColor(CLR_BORDERSPR, tem_clrSet2);	//���÷�֧��ɫ
	CHSMenuPro::SetMenuStyle(ML_ARROWROUND, true);
	CHSMenuPro::SetMenuStyle(ML_SELGRADIENT_V, true);

	m_menuRightClick.CreateMenu(hwnd);
	m_menuRightClick.AppendMenuW(_T("��  ��"), 32771, 0, 0);
	m_menuRightClick.AppendMenuW(_T("ɾ  ��"), 32772, 0, 0);
	m_menuRightClick.AppendMenuW(_T("������"), 32773, 0, 0); //����Ϊ�˵�ID
	m_menuRightClick.AppendMenuW(_T("��  ��"), 32774, 0, 0);
	m_menuRightClick.AppendMenuW(_T("����90��"), 32778, 0, 0);
	m_menuRightClick.AppendMenuW(_T("����90��"), 32779, 0, 0);
	m_menuRightClick.AppendMenuW(_T("һ��Word"), 32775, 0, 0);
//	m_menuRightClick.AppendMenuW(_T("һ��Excel"), 32776, 0, 0);
//	m_menuRightClick.AppendMenuW(_T("�Զ���ת"), 32777, 0, 0);
	

	return TRUE;
}


void CUDSSmartCamerav100Dlg::OnHoverListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 1;
}


BOOL CUDSSmartCamerav100Dlg::CopyFiles2Clipboard(std::vector<CString> const& vecFiles)
{
	UINT  uDropEffect     = RegisterClipboardFormat(_T("Preferred DropEffect"));  
	HGLOBAL hGblEffect    = GlobalAlloc(GMEM_ZEROINIT|GMEM_MOVEABLE|GMEM_DDESHARE, sizeof(DWORD));  
	DWORD *pDWDropEffect  = (DWORD*)GlobalLock(hGblEffect);  
	*pDWDropEffect        = DROPEFFECT_COPY;  
	GlobalUnlock(hGblEffect);  

	DROPFILES dropFiles;  
	dropFiles.pFiles = sizeof(DROPFILES);  
	dropFiles.pt.x   = 0;  
	dropFiles.pt.y   = 0;  
	dropFiles.fNC    = FALSE;  
	dropFiles.fWide  = TRUE;  

	UINT uFileListLen = 0;  
	for (std::vector<CString>::const_iterator it = vecFiles.begin(); it != vecFiles.end(); ++it)  
	{  
		uFileListLen += (it->GetLength() + 1);//β��һ��\0������  
	}  

	UINT uGblLen      = sizeof(DROPFILES) + sizeof(TCHAR)* (uFileListLen + 1);  
	HGLOBAL hGblFiles = GlobalAlloc(GMEM_ZEROINIT|GMEM_MOVEABLE|GMEM_DDESHARE, uGblLen);  
	BYTE *  pData     = (BYTE*)GlobalLock(hGblFiles);  
	memcpy(pData, (LPVOID)(&dropFiles), sizeof(DROPFILES));  

	BYTE *pFileList = pData + sizeof(DROPFILES);  

	for (std::vector<CString>::const_iterator it = vecFiles.begin(); it != vecFiles.end(); ++it)  
	{  
		UINT uLen = (it->GetLength() + 1) * sizeof(TCHAR);  
		memcpy(pFileList, (BYTE*)(LPCTSTR)(*it),  uLen);  
		pFileList += uLen;  
	}  

	GlobalUnlock(hGblFiles);  

	if( OpenClipboard() )  
	{  
		EmptyClipboard();  
		SetClipboardData( CF_HDROP, hGblFiles );  
		SetClipboardData(uDropEffect,hGblEffect);  
		CloseClipboard();  
		return TRUE;  
	}  
	else  
	{  
		::GlobalFree(hGblEffect);  
		::GlobalFree(hGblFiles);  
	}  
	return TRUE;  
}


void CUDSSmartCamerav100Dlg::OnBnClickedBtnReadcard()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	/*ԭ������������������*/
	/*
	BOOL   tem_BRC = FALSE;
	tem_BRC = ReadCard();
	if (tem_BRC)
	{
		m_iChildCard.DoModal();
	} 
	*/
	/*�£����������޸�����������*/
	m_iChildCard.DoModal();
	

}


BOOL CUDSSmartCamerav100Dlg::ReadCard(void)
{
	/*2018-03-08ע�ͣ�ԭ�򣺸öκ����޸����̺�δ�ã������޸Ķ�����
	m_strCardName    = _T("");
	m_strCardSex     = _T("");
	m_strCardNation  = _T("");
	m_strCardBirth   = _T("");
	m_strCardAddress = _T("");
	m_strCardID      = _T("");
	m_strCardOffice  = _T("");
	m_strCardValidity= _T("");
	//��黺��Ŀ¼�Ƿ���ڣ��������ڴ�������Ŀ¼
	//����Ŀ¼�����ݶ�C:\\UDSScanTemp
	//�ݶ�Ϊ�ҵ��ĵ���UDSData
//	CString    tem_strScanTemp = _T("C:\\UDSScanTemp");
	CString    tem_strScanTemp = GetMyDocument();
	tem_strScanTemp += _T("\\");
	tem_strScanTemp += _T("UDSData");
	CFileFind  tem_fFileFind;
	if (!tem_fFileFind.FindFile(tem_strScanTemp))
	{
		CreateDirectory(tem_strScanTemp, NULL);
	}


	//�ж������ļ��Ƿ����
	CString  tem_strCardIni = tem_strScanTemp + _T("\\");
	tem_strCardIni += _T("PersonInfo.INI");

	BOOL     tem_BFileFind = PathFileExists(tem_strCardIni);
	if (!tem_BFileFind)
	{
		//�ļ������ڣ���ԭ�����ļ����Ƶ�ָ��Ŀ¼
		TCHAR        tem_tcFilepath[MAX_PATH+1] = {0};
		GetModuleFileName(NULL, tem_tcFilepath, MAX_PATH);
		(_tcsrchr(tem_tcFilepath, _T('\\')))[1] = 0;
		m_strIniPath   = tem_tcFilepath;
		m_strIniPath  += _T("PersonInfo.INI");
//		m_strIniPath.Replace(_T("\\"), _T("\\\\"));

		CopyFile(m_strIniPath, tem_strCardIni, TRUE);
	}


	tem_strScanTemp += _T("\\���֤��Ϣ");
	if (!tem_fFileFind.FindFile(tem_strScanTemp))
	{
		CreateDirectory(tem_strScanTemp, NULL);
	}

	tem_strScanTemp += _T("\\Image");
	if (!tem_fFileFind.FindFile(tem_strScanTemp))
	{
		CreateDirectory(tem_strScanTemp, NULL);
	}



	//�Ե�ǰϵͳʱ������ͼ���ļ��������ظ�
	CString       tem_strPicName, tem_strNewPicName;   //���֤ͷ����
	SYSTEMTIME    tem_st;
	CString       tem_strDate, tem_strTime;

	GetLocalTime(&tem_st);
	tem_strDate.Format(_T("%d%02d%02d_"), tem_st.wYear, tem_st.wMonth, tem_st.wDay);
	tem_strTime.Format(_T("%02d%02d%02d"), tem_st.wHour, tem_st.wMinute, tem_st.wSecond);

	tem_strPicName += tem_strScanTemp;
	tem_strPicName += _T("\\");
	tem_strPicName += tem_strDate;
	tem_strPicName += tem_strTime;
	tem_strPicName += _T(".bmp");	

	CString tem_strRC= _T("");
	tem_strRC = m_iCard->OpenCardPort();
	if (tem_strRC != _T("�򿪶˿�ʧ��"))
	{
		m_iCard->SetHeadPicPath(tem_strPicName);
		tem_strRC = m_iCard->ReadIDCard();
		if (tem_strRC == _T(""))
		{
			//�����ɹ�
			m_strCardName    = m_iCard->GetCardName();
			m_strCardSex     = m_iCard->GetCardSex();
			m_strCardNation  = m_iCard->GetCardNation();
			m_strCardBirth   = m_iCard->GetCardBirth();
			m_strCardAddress = m_iCard->GetCardAddress();
			m_strCardID      = m_iCard->GetCardID();
			m_strCardOffice  = m_iCard->GetIssuingOrgan();
			m_strCardValidity= m_iCard->GetAllottedTime();
			m_iCard->CloseCardPort();

			tem_strNewPicName += tem_strScanTemp;
			tem_strNewPicName += _T("\\");
			tem_strNewPicName += m_strCardName;
			tem_strNewPicName += m_strCardID;
			tem_strNewPicName += _T(".bmp");

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

			m_iChildCard.m_strFilePath = tem_strNewPicName;
			m_iChildCard.m_strName    = m_strCardName;
			m_iChildCard.m_strSex     = m_strCardSex;
			m_iChildCard.m_strNation  = m_strCardNation;
			m_iChildCard.m_strBirth   = m_strCardBirth;
			m_iChildCard.m_strAddress = m_strCardAddress;
			m_iChildCard.m_strID      = m_strCardID;
			m_iChildCard.m_strOffice  = m_strCardOffice;
			m_iChildCard.m_strValidity=m_strCardValidity;

			return TRUE;	
		}
		else
		{
			m_iCard->CloseCardPort();
			MessageBox( _T("�����·������֤"), _T(""), MB_OK);
			return FALSE;
		}

	}
	else
	{
		m_iCard->CloseCardPort();
	}
	*/
	return FALSE;
}


int CUDSSmartCamerav100Dlg::ShowImageSize(CString imagepath)
{
	CString  tem_strImageSize= _T("");
	CString  tem_strImageInfo  = _T("ͼ���С��");
// 	long     tem_lFilesize     = 0;   //��λ�ֽ�
// 	int      tem_nFilesize     = 0;
// 
// 	//��ȡͼ���С
// 	CFile       tem_file;
// 	CFileStatus tem_filestatus;
// 	CFile::GetStatus(imagepath, tem_filestatus);
// 	tem_lFilesize = tem_filestatus.m_size;
// 	tem_nFilesize = tem_lFilesize/1024;
// 	tem_strImageSize.Format(_T("%d"), tem_nFilesize);
// 	tem_strImageInfo += tem_strImageSize;

	CFile        tem_file;
	ULONGLONG    tem_filesize;
	CString      tem_strfilesize;
	if (tem_file.Open(imagepath, CFile::modeRead))
	{
		tem_filesize = tem_file.GetLength();
		if (tem_filesize>1024)
		{
			//ת��Ϊkb��ʾ
			tem_filesize = tem_filesize/1024;
			tem_strfilesize.Format(_T("%I64d"), tem_filesize);
			tem_strImageInfo += tem_strfilesize;
			tem_strImageInfo += _T("kb");

		}
		else
		{
			//ʹ���ֽڱ�ʾ
			tem_strfilesize.Format(_T("%I64d"), tem_filesize);
			tem_strImageInfo += tem_strfilesize;
			tem_strImageInfo += _T("b");

		}
	}


	GetDlgItem(IDC_STA_IMAGESIZE)->SetWindowText(tem_strImageInfo);

	GetDlgItem(IDC_STA_IMAGESIZE)->GetWindowRect(&m_rcImageSize); 
	ScreenToClient(&m_rcImageSize); //ת���ͻ��˽���
	InvalidateRect(&m_rcImageSize);//���ˢ�¶Ի��򱳾� 
	UpdateWindow();

	/*���»�ȡͼ��ߴ�
	int tem_nImageType=GetTypeFromFileName(imagepath);
	if(tem_nImageType==CXIMAGE_FORMAT_UNKNOWN)
		return -1;

	CxImage   tem_image;
	tem_image.Load(imagepath, tem_nImageType);
	if (tem_image.Load(imagepath, tem_nImageType))
	{
		tem_nImageWidth = tem_image.GetWidth();
		tem_nImageHight = tem_image.GetHeight();
		tem_strImageWidth.Format(_T("%d"), tem_nImageWidth);
		tem_strImageHeight.Format(_T("%d"), tem_nImageHight);
		
		tem_strImageInfo += tem_strImageWidth; 
		tem_strImageInfo += _T("*");
		tem_strImageInfo += tem_strImageHeight;

		GetDlgItem(IDC_STA_IMAGESIZE)->SetWindowText(tem_strImageInfo);
		     
		GetDlgItem(IDC_STA_IMAGESIZE)->GetWindowRect(&m_rcImageSize); 
		ScreenToClient(&m_rcImageSize); //ת���ͻ��˽���
		InvalidateRect(&m_rcImageSize);//���ˢ�¶Ի��򱳾� 
		UpdateWindow();
		
	}
	*/


	return 0;
}


CString CUDSSmartCamerav100Dlg::GetMyDocument(void)
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


//void CUDSSmartCamerav100Dlg::OnItemclickListImage(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	MessageBox(_T("click"));
//	*pResult = 0;
//}


void CUDSSmartCamerav100Dlg::OnBeginlabeleditListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	
	*pResult = 0;
}


void CUDSSmartCamerav100Dlg::OnEndlabeleditListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	int       tem_nSlcImage =-1;
	tem_nSlcImage = pDispInfo->item.iItem;
	CString   tem_strSlcName      = m_vcFileName[tem_nSlcImage];    //ԭ�ļ���
//	CString   tem_strSlcWholeName = m_vcWholeName[tem_nSlcImage];
	CString   tem_strSlcBussName     = m_vcBussName[tem_nSlcImage];

	CString   tem_strNewName  = pDispInfo->item.pszText;           //���ļ���
	if (tem_strNewName == _T(""))
	{
		tem_strNewName = tem_strSlcName;
	}
	CString   tem_strNewWhole = _T("");
	CString   tem_strNewBuss  = _T("");

	CString   tem_strFormat   = PathFindExtension(tem_strSlcBussName);    //ԭ�ļ���׺
	tem_strFormat.MakeLower();

	CString   tem_strMiddle    = tem_strSlcBussName;  
	LPWSTR    tem_wstrBussName = tem_strMiddle.GetBuffer();
	tem_strMiddle.ReleaseBuffer();
	PathRemoveFileSpecW(tem_wstrBussName);   
	CString   tem_strDocumnet  = tem_wstrBussName;                       //ԭ�ļ�Ŀ¼
	
	if (tem_strFormat == _T(".jpg")||tem_strFormat == _T(".bmp")||tem_strFormat == _T(".png")||tem_strFormat == _T(".tif"))
	{
		tem_strNewWhole = tem_strDocumnet + _T("\\") + tem_strNewName + tem_strFormat;
		tem_strNewBuss  = tem_strNewWhole;

		int len =WideCharToMultiByte(CP_ACP,0,tem_strSlcBussName,-1,NULL,0,NULL,NULL);  
		char *ptxtSrc =new char[len +1];  
		WideCharToMultiByte(CP_ACP,0,tem_strSlcBussName,-1,ptxtSrc,len,NULL,NULL );  

		len =WideCharToMultiByte(CP_ACP,0,tem_strNewBuss,-1,NULL,0,NULL,NULL);  
		char *ptxtDst =new char[len +1];  
		WideCharToMultiByte(CP_ACP,0,tem_strNewBuss,-1,ptxtDst,len,NULL,NULL );  

		int  tem_rcRename = rename(ptxtSrc, ptxtDst);
		if (tem_rcRename == 0)
		{
			m_vcFileName[tem_nSlcImage] = tem_strNewName;
//			m_vcWholeName[tem_nSlcImage]= tem_strNewWhole;
			m_vcBussName[tem_nSlcImage] = tem_strNewBuss;					

			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
		} 
		else
		{
//			MessageBox(_T("�ļ����Ѵ��ڣ�"));
		}
		delete[] ptxtSrc;  
		delete[] ptxtDst;  
	} 
	else if (tem_strFormat == _T(".pdf")||tem_strFormat == _T(".txt")||tem_strFormat == _T(".dcm"))
	{
		tem_strNewBuss = tem_strDocumnet + _T("\\") + tem_strNewName + tem_strFormat;

		int len =WideCharToMultiByte(CP_ACP,0,tem_strSlcBussName,-1,NULL,0,NULL,NULL);  
		char *ptxtSrc =new char[len +1];  
		WideCharToMultiByte(CP_ACP,0,tem_strSlcBussName,-1,ptxtSrc,len,NULL,NULL );  

		len =WideCharToMultiByte(CP_ACP,0,tem_strNewBuss,-1,NULL,0,NULL,NULL);  
		char *ptxtDst =new char[len +1];  
		WideCharToMultiByte(CP_ACP,0,tem_strNewBuss,-1,ptxtDst,len,NULL,NULL );  

		int  tem_rcRename = rename(ptxtSrc, ptxtDst);
		if (tem_rcRename == 0)
		{
			m_vcFileName[tem_nSlcImage] = tem_strNewName;
			m_vcBussName[tem_nSlcImage] = tem_strNewBuss;

			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
		}
		else
		{
//			MessageBox(_T("�ļ����Ѵ��ڣ�"));
		}	
		delete[] ptxtSrc;  
		delete[] ptxtDst; 
	} 
	

	
	*pResult = 0;
}


CString CUDSSmartCamerav100Dlg::GetThumbPath(CString wholeimage, CString imagename)
{
	//�жϻ���Ŀ¼�Ƿ���ڣ�������Ŀ¼�����ڣ�����Ŀ¼

	
	
	
	//����ͼ�ļ����Լ��洢·��
	CString   tem_strNewFileName = _T("~")+imagename;
	tem_strNewFileName += _T(".jpg");
	CString   tem_strNewFilePath = m_strBufferPath +tem_strNewFileName;

	CString   tem_strFilePath = wholeimage;

	int       tem_nImageType=GetTypeFromFileName(tem_strFilePath);
	if(tem_nImageType==CXIMAGE_FORMAT_UNKNOWN)
	{
		return tem_strFilePath;
	}
	CxImage*  tem_pImage;
	tem_pImage = new CxImage;
	tem_pImage->Load(tem_strFilePath, tem_nImageType);
	if(tem_pImage->IsValid()==false)
	{
		return tem_strFilePath;
	}
	if (tem_pImage->GetBpp()==1)
	{
		tem_pImage->IncreaseBpp(24);
	}
	int   cx = 160;
	int   cy = (int)160*tem_pImage->GetHeight()/tem_pImage->GetWidth();
	tem_pImage->Resample(cx, cy, 1, NULL);
	tem_pImage->Save(tem_strNewFilePath, CXIMAGE_FORMAT_JPG);
	
	delete tem_pImage;
	return tem_strNewFilePath;
}


BOOL CUDSSmartCamerav100Dlg::GetSystemInfo(void)
{
	CString osName = _T("");  
	int a=0,b=0,i=0,j=0;    
	_asm    
	{    
		pushad    
			mov ebx,fs:[0x18] ; get self pointer from TEB    
			mov eax,fs:[0x30] ; get pointer to PEB / database    
			mov ebx,[eax+0A8h] ; get OSMinorVersion    
			mov eax,[eax+0A4h] ; get OSMajorVersion    
			mov j,ebx    
			mov i,eax    
			popad    
	}    

	if((i==5)&&(j==0))    
	{    
		osName = _T("��ǰϵͳ�汾Ϊ��Windows 2000");  
		return FALSE;
	}    
	else if((i==5)&&(j==1))    
	{     
		osName = _T("��ǰϵͳ�汾Ϊ��Windows XP");  
		return FALSE;
	}    
	else if((i==5)&&(j==2))    
	{    
		osName = _T("��ǰϵͳ�汾Ϊ��Windows 2003");  
		return FALSE;
	}    
	else if((i==6)&&(j==0))    
	{    
		osName = _T("��ǰϵͳ�汾Ϊ��Windows Vista");   
		return TRUE;
	}    
	else if((i==6)&&(j==1))    
	{    
		osName = _T("��ǰϵͳ�汾Ϊ��Windows 7");   
		return TRUE;
	}  
	else if((i==6)&&(j==2))    
	{    
		osName = _T("��ǰϵͳ�汾Ϊ��Windows 8");  
		return TRUE;
	}  
	else if((i==6)&&(j==3))    
	{    
		osName = _T("��ǰϵͳ�汾Ϊ��Windows 8.1");  
		return TRUE;
	}  
	else if((i==10)&&(j==0))    
	{    
		osName = _T("��ǰϵͳ�汾Ϊ��Windows 10");  
		return TRUE;
	}  
	else  
	{  
		osName = _T("��ǰϵͳ����Windows 2000�����߸���Windows 10������δ֪ϵͳ�汾");  
		return TRUE;
	}  
	return TRUE;
}


// ͼ���ֵ
CString CUDSSmartCamerav100Dlg::InterPolateImage(CString srcImage, CString dsImage, int index)
{
	int       tem_nInterpolateIndex = index;

	int       tem_nGoalResoW        = 0;          //Ŀ��ֱ���
	int       tem_nGoalResoH        = 0;
	float     tem_fRateW            = 0;          //ת���ʿ�
	float     tem_fRateH            = 0;

	long*     tem_lWidth;
	tem_lWidth  = new long;
	long*     tem_lHeight;  
	tem_lHeight = new long;
	float     tem_fWidth;
	float     tem_fHeight;

	CString   tem_strSrcImage       = srcImage;   //ԭͼ·��
	CString   tem_strDstImage       = dsImage;     //Ŀ��ͼ·��

	CxImage   tem_cxSrcImage;
	tem_cxSrcImage.Load(tem_strSrcImage);
	m_conVideoOcx.GetCurResolution(tem_lWidth, tem_lHeight);
	tem_fWidth  = *tem_lWidth;
	tem_fHeight = *tem_lHeight;

	switch(tem_nInterpolateIndex)
	{
	case 0:
		//800->1000
		tem_fRateW  = 3664/(3264*1.0);
		tem_fRateH  = 2744/(2448*1.0);
		break;
	case 1:
		//1200->1600
		tem_fRateW  = 4680/(4160*1.0);
		tem_fRateH  = 3510/(3120*1.0);
		break;
	case 2:
		//1300->1500
		tem_fRateW  = 4480/(4160*1.0);
		tem_fRateH  = 3360/(3120*1.0);

// 		tem_fRateW  = 4480/(3264*1.0);
// 		tem_fRateH  = 3360/(2448*1.0);
		break;
	case 3:
		//500W->1000W
		tem_fRateW  = 3664/(2592*1.0);
		tem_fRateH  = 2745/(1944*1.0);
		break;
	case 4:
		//1200->1500W
		tem_fRateW = 4480/(4032*1.0);
		tem_fRateH = 3360/(3024*1.0);

// 		tem_fRateW = 4480/(3264*1.0);
// 		tem_fRateH = 3360/(2448*1.0);
		break;
	case 5:
		//1300W->1600W
		tem_fRateW = 4928/(4160*1.0);
		tem_fRateH = 3264/(3120*1.0);
		break;
	case 6:
		//200W->300W
		tem_fRateW = 2048/(1600*1.0);
		tem_fRateH = 1536/(1200*1.0);
		break;
	default:
		return srcImage;
		break;
	}
	

//	tem_nGoalResoW = (int)(tem_cxSrcImage.GetWidth()*tem_fRate + 0.5);
//	tem_nGoalResoH = (int)(tem_cxSrcImage.GetHeight()*tem_fRate + 0.5);

	tem_nGoalResoW = (int)(tem_cxSrcImage.GetWidth()*tem_fRateW );
	tem_nGoalResoH = (int)(tem_cxSrcImage.GetHeight()*tem_fRateH);

	tem_cxSrcImage.Resample(tem_nGoalResoW, tem_nGoalResoH);

	//�ж�ͼ���ʽ
	int      tem_nFormat   = -1;
	CString  tem_strFormat = _T("");
	tem_strFormat = srcImage;
	tem_nFormat = tem_strFormat.ReverseFind('.');
	tem_strFormat = tem_strFormat.Mid(tem_nFormat+1);
	tem_strFormat.MakeLower();
	if (tem_strFormat == _T("bmp"))
	{
		tem_cxSrcImage.Save(tem_strDstImage, CXIMAGE_FORMAT_BMP);
	}
	else if (tem_strFormat == _T("jpg"))
	{
		tem_cxSrcImage.SetJpegQuality(m_nJpegQulity);
		tem_cxSrcImage.Save(tem_strDstImage, CXIMAGE_FORMAT_JPG);
	}
	else if (tem_strFormat == _T("tif"))
	{
		tem_cxSrcImage.Save(tem_strDstImage, CXIMAGE_FORMAT_TIF);
	}
	else if (tem_strFormat == _T("png"))
	{
		tem_cxSrcImage.SetJpegQuality(m_nJpegQulity);
		tem_cxSrcImage.Save(tem_strDstImage, CXIMAGE_FORMAT_PNG);
	}

	tem_cxSrcImage.Destroy();
	
	return tem_strDstImage;
}


CString CUDSSmartCamerav100Dlg::GeneratePDF(CString srcImg, CString dstImg)
{
	CString   tem_strInputPath  = srcImg;     //����ͼ��·��
	CString   tem_strOutputPath = dstImg;     //����PDF·��

	
	//����PDF--------
	int       doc, page, image, code, pagenum=2;
	wstring    outfile;
	outfile = tem_strOutputPath.GetBuffer(0);
	tem_strOutputPath.ReleaseBuffer();
	PDFlib*    pPdf;
	pPdf = new PDFlib;
	try
	{
//		pPdf->set_parameter("License", "w700602-009100-731090-Y6WPH2-5SE4A2");
		pPdf->set_parameter(_T("nodemostamp"), _T("false"));
		pPdf->set_parameter(_T("errorpolicy"), _T("return"));
//		pPdf->set_parameter(_T("hypertextencoding"), _T("host"));

		code = pPdf->begin_document(outfile, _T(""));
		if (code == -1)
		{
			return srcImg;
		}
		//����PDF������Ϣ******************************************************
		pPdf->set_info(_T("Creator"), _T("SmartScan"));   
		pPdf->set_info(_T("Author"), _T("UDS"));   
		pPdf->set_info(_T("Title"), _T("UDSPDF")); 
		pPdf->set_info(_T("Subject"), _T("ɨ���ĵ�"));

		//ͼƬ����***********************************************************
		{
			
			wstring sFilePath(tem_strInputPath.GetBuffer());
			image = pPdf->load_image(_T("auto"), sFilePath, _T(""));
			pPdf->begin_page_ext(10, 10, _T(""));
			pPdf->fit_image(image, 0, 0, _T("adjustpage dpi=0"));  //����ͼ��
			pPdf->close_image(image);
			pPdf->end_page_ext(_T(""));
		}		
		pPdf->end_document(_T(""));	
	}
	catch (PDFlib::Exception e)
	{
		int     num=-1;
		wstring  str;
		CString str2, str3;
		str = e.get_errmsg();
		num = e.get_errnum();
		str2 = str.c_str();
		str3.Format(_T("%d"), num);
	}

	return tem_strOutputPath;
}


CString CUDSSmartCamerav100Dlg::GenerateBase64(CString srcImg, CString dstImg)
{
	CString       tem_strInputPath  = srcImg;    //����ͼ���ַ
	CString       tem_strOutputPath = dstImg;    //����txt��ַ


	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;
	
	USES_CONVERSION;  
	LPCWSTR filename = new WCHAR[tem_strInputPath.GetLength()+1];  
	wcscpy((LPTSTR)filename,T2W((LPTSTR)tem_strInputPath.GetBuffer(NULL)));  
	tem_strInputPath.ReleaseBuffer();  
	if (-1!=GetFileAttributes(filename))
	{

		CFile file;
		if(!file.Open(filename,CFile::modeRead))
		{
//			return strResult.AllocSysString();
			return tem_strInputPath;
		}

		DWORD dwSize = file.GetLength();
		BYTE *buff = new BYTE[file.GetLength()+1];
		file.Read(buff,file.GetLength());
		file.Close();

		CBase64 base;
		int nOut = base.EncodedSize(dwSize);
		char *pOut = new char[nOut];
		ZeroMemory(pOut,nOut);
		base.Encode((char *)buff,dwSize,pOut);
	
		CFile save(tem_strOutputPath, CFile::modeCreate | CFile::modeWrite);
		save.Write(pOut, nOut);
		save.Close();

		strResult = CString(pOut);
		strResult.Replace(L" ",L"");
		delete [] pOut;
		delete [] buff;
//		return strResult.AllocSysString();
		return tem_strOutputPath;
	}
	else
	{
		strResult="";
//		return strResult.AllocSysString();
		return tem_strInputPath;

	}

	return tem_strOutputPath;
}


int CUDSSmartCamerav100Dlg::GetmaxResoindex(void)
{
	int     tem_nMaxIndex     = 0;
	long    tem_lValue1       = -1;
	long    tem_lValue2       = 10;
	long    tem_lMiddle       = 0;

	BOOL    tem_BMark         = TRUE;
	
	CString tem_strResolution = _T("");
	int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
	for (int i=0; i<tem_nResCount; i++)
	{

		tem_strResolution = m_conVideoOcx.GetResolution(i);
		int        tem_nFindIndex = tem_strResolution.Find(_T('*'));
		CString    tem_strFirst = tem_strResolution;
		CString    tem_strLast  = tem_strResolution;
		tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
		tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
		int        tem_nFirst   = _ttoi(tem_strFirst);
		int        tem_nLast    = _ttoi(tem_strLast);

		if (tem_BMark)
		{
			tem_lValue1   = tem_nFirst*tem_nLast;
			tem_nMaxIndex = i;
			tem_BMark   = FALSE;
			continue;
		}

		tem_lValue2 = tem_nFirst*tem_nLast;

		if (tem_lValue1<tem_lValue2)
		{
			tem_lValue1   = tem_lValue2;
			tem_nMaxIndex = i;
		}
	}
	return tem_nMaxIndex;
}

//��ȡָ���ֱ��ʵ�����ֵ�����ȡ�ڶ���ֱ��ʣ�������ֱ���
int CUDSSmartCamerav100Dlg::GetDiyResoindex(int diyvalue)
{
	int     tem_nMaxIndex     = 0;
	long    tem_lValue1       = -1;
	long    tem_lValue2       = 10;
	long    tem_lMiddle       = 0;

	BOOL    tem_BMark         = TRUE;

	CString tem_strResolution = _T("");
	int    tem_nResCount = m_conVideoOcx.GetResCount();  //�豸����������
	std::vector<int>  tem_vcResIndex;
	std::vector<int>  tem_vcResValue;
	
	tem_vcResIndex.clear();
	tem_vcResValue.clear();

	for (int i=0; i<tem_nResCount; i++)
	{

		tem_strResolution = m_conVideoOcx.GetResolution(i);
		int        tem_nFindIndex = tem_strResolution.Find('*');
		CString    tem_strFirst = tem_strResolution;
		CString    tem_strLast  = tem_strResolution;
		tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
		tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
		int        tem_nFirst   = _ttoi(tem_strFirst);
		int        tem_nLast    = _ttoi(tem_strLast);

		tem_lValue1   = tem_nFirst*tem_nLast;
		tem_nMaxIndex = i;

		tem_vcResValue.push_back(tem_lValue1);
		tem_vcResIndex.push_back(i);
	}
	//��vector��������ͬʱ������Ӧ��Ӧ�ĵ�ֵ,��С����
	for (int i=0; i<tem_vcResValue.size()-1; i++)
	{
		for (int j=0; j<tem_vcResValue.size()-i-1; j++)
		{
			if (tem_vcResValue[j]>tem_vcResValue[j+1])
			{
				int tem_nValue = tem_vcResValue[j];
				tem_vcResValue[j] = tem_vcResValue[j+1];
				tem_vcResValue[j+1] = tem_nValue;
				int tem_nIndex = tem_vcResIndex[j];
				tem_vcResIndex[j] = tem_vcResIndex[j+1];
				tem_vcResIndex[j+1] = tem_nIndex;
			}
		}
	}

	int  tem_nSecond = tem_vcResIndex.at(tem_vcResIndex.size()-diyvalue);

	return tem_nSecond;
}


int CUDSSmartCamerav100Dlg::GetsubmaResoindex(void)
{
	int     tem_nMaxIndex     = 0;
	long    tem_lValue1       = -1;
	long    tem_lValue2       = 10;
	long    tem_lMiddle       = 0;

	BOOL    tem_BMark         = TRUE;

	CString tem_strResolution = _T("");
	int    tem_nResCount = m_conVideoOcx.GetSubResoCount();  //�豸����������
	for (int i=0; i<tem_nResCount; i++)
	{

		tem_strResolution = m_conVideoOcx.GetSubReso(i);
		int        tem_nFindIndex = tem_strResolution.Find(_T('*'));
		CString    tem_strFirst = tem_strResolution;
		CString    tem_strLast  = tem_strResolution;
		tem_strFirst = tem_strFirst.Mid(0, tem_nFindIndex);
		tem_strLast  = tem_strLast.Mid(tem_nFindIndex+1);
		int        tem_nFirst   = _ttoi(tem_strFirst);
		int        tem_nLast    = _ttoi(tem_strLast);

		if (tem_BMark)
		{
			tem_lValue1   = tem_nFirst*tem_nLast;
			tem_nMaxIndex = i;
			tem_BMark   = FALSE;
			continue;
		}

		tem_lValue2 = tem_nFirst*tem_nLast;

		if (tem_lValue1<tem_lValue2)
		{
			tem_lValue1   = tem_lValue2;
			tem_nMaxIndex = i;
		}
	}
	return tem_nMaxIndex;
}


void CUDSSmartCamerav100Dlg::OnBnClickedBtnZoomin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!GetDlgItem(IDC_BTN_ZOOMOUT)->IsWindowEnabled())
	{
		CRect  tem_rcZoomOut;
		GetDlgItem(IDC_BTN_ZOOMOUT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ZOOMOUT)->GetWindowRect(&tem_rcZoomOut); 
		ScreenToClient(&tem_rcZoomOut); //ת���ͻ��˽���
		InvalidateRect(&tem_rcZoomOut);//���ˢ�¶Ի��򱳾� 
		UpdateWindow();
	}
	
	m_conVideoOcx.ZoomIn();
}


void CUDSSmartCamerav100Dlg::OnBnClickedBtnZoomout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ��������
	m_conVideoOcx.ZoomOut();
}


void CUDSSmartCamerav100Dlg::OnBnClickedBtnRecover()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_conVideoOcx.ReturnOrigin();
}


afx_msg LRESULT CUDSSmartCamerav100Dlg::OnDevicechange(WPARAM wParam, LPARAM lParam)
{
	if ( DBT_DEVICEARRIVAL == wParam || DBT_DEVICEREMOVECOMPLETE == wParam ) {  
		PDEV_BROADCAST_HDR pHdr = (PDEV_BROADCAST_HDR)lParam;  
		PDEV_BROADCAST_DEVICEINTERFACE pDevInf;  
		PDEV_BROADCAST_HANDLE pDevHnd;  
		PDEV_BROADCAST_OEM pDevOem;  
		PDEV_BROADCAST_PORT pDevPort;  
		PDEV_BROADCAST_VOLUME pDevVolume;  
		switch( pHdr->dbch_devicetype ) {  
		case DBT_DEVTYP_DEVICEINTERFACE:  
			{  
				//�豸�䶯�����豸����ʱ�����»�ȡ�豸��������combox
//				Sleep(200);
				TimeDelayed(200);
				UpdateDevices(m_nDeviceNumber);

			}  
			break;  

		case DBT_DEVTYP_HANDLE:  
			pDevHnd = (PDEV_BROADCAST_HANDLE)pHdr;  
			break;  

		case DBT_DEVTYP_OEM:  
			pDevOem = (PDEV_BROADCAST_OEM)pHdr;  
			break;  

		case DBT_DEVTYP_PORT:  
			pDevPort = (PDEV_BROADCAST_PORT)pHdr;  
			break;  

		case DBT_DEVTYP_VOLUME:  
			pDevVolume = (PDEV_BROADCAST_VOLUME)pHdr;  
			break;  
		}  
	}  
	return 0;
}


void CUDSSmartCamerav100Dlg::UpdateDevices(int number)
{
	int      tem_nDevCount = m_conVideoOcx.GetDeviceCount();//��ǰ�豸����
	if (tem_nDevCount == number)
	{
		//�豸����δ��
		return;
	}
	m_nDeviceNumber = tem_nDevCount;
	if (tem_nDevCount>0)
	{
		m_iChildNor.m_conComScanner.ResetContent();
		for (int i=0; i<tem_nDevCount;i++)
		{
			CString tem_strDevName = m_conVideoOcx.GetDeviceName(i);
			m_iChildNor.m_conComScanner.InsertString(i, tem_strDevName);
//			m_straDeviceName.Add(tem_strDevName);
		}
		m_iChildNor.m_conComScanner.SetCurSel(m_nLastUsedScanner);
	}
}


// ���ȡ�������
#pragma comment(lib, "winmm.lib")  
void CUDSSmartCamerav100Dlg::TimeDelayed(int time_ms)
{
	DWORD    tem_dTimeBegin = timeGetTime();
	DWORD    tem_dTimeEnd   = 0;
	do 
	{
		tem_dTimeEnd = timeGetTime();
	} while (tem_dTimeEnd-tem_dTimeBegin<=time_ms);
}


void CUDSSmartCamerav100Dlg::OnBnClickedBtnCardcopy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	
	CString   tem_strName;         //�޺�׺
	CString   tem_strFileName;     //����׺
	CString   tem_strWholeName;    //��·��,ͼ���ļ�
	CString   tem_strPDFimgName;   //��·���������ļ�
	CString   tem_strTXTimgName;
	CString   tem_strThumbPath;    //����ͼ·��
	CString   tem_strSrcImageName; //��ֵԭͼ
	CString   tem_strSrcImagePDF;  //PDFԭͼ
	CString   tem_strCardFormat;
	CString   tem_strCardFront;     //���֤����·��
	CString   tem_strCardBack;     //���֤����·��
	CString   tem_strPDFImg;       //����PDFʱԭͼ
	if (!m_BCardDlg)
	{
		tem_strName      = NamingFile(m_nNamingMode);
		m_strFrontName    = tem_strName;
		tem_strCardFormat = m_strFrontName;
		tem_strCardFormat+= _T(".jpg");		
		tem_strCardFront = m_strBufferPath;     //���֤����·��
		tem_strCardFront += _T("Front");
		tem_strCardFront += tem_strCardFormat;

		//1������ͼ�񣬲�����ͼ��
		g_strFrontImg = tem_strCardFront;
		if (m_BSoundOpen)
		{
			sndPlaySound(_T("CameraSound.WAV"), NULL);
		}
		m_conVideoOcx.CaptureImage(tem_strCardFront);

		m_dlgFront.Create(IDD_DLG_FRONT, this);
		m_dlgFront.ShowWindow(SW_SHOWNORMAL);
		GetDlgItem(IDC_UDS_VIDEOCTRL1)->GetWindowRect(&m_rcOCX);
		m_dlgFront.MoveWindow(m_rcOCX.left, m_rcOCX.top, 440, 160, TRUE);
		m_BCardDlg = TRUE;
	} 
	else
	{
		if (m_strFileFormat==_T(".bmp")||m_strFileFormat==_T(".jpg")||m_strFileFormat==_T(".png")||m_strFileFormat==_T(".tif")||m_strFileFormat==_T(".pdf")||m_strFileFormat==_T(".ofd"))
		{
			tem_strFileName = m_strFrontName + m_strFileFormat;
		}
		else
		{
			tem_strFileName = m_strFrontName + _T(".jpg");
		}

		tem_strWholeName = m_strDefaultPath + tem_strFileName;
		tem_strSrcImageName = m_strBufferPath + tem_strFileName;

		tem_strCardFormat= m_strFrontName;
		tem_strCardFormat+= _T(".jpg");
		tem_strCardBack  = m_strBufferPath;     //���֤����·��
		tem_strPDFImg    = m_strBufferPath;     //����PDFʱԭͼ
		
		tem_strCardBack  += _T("Back");
		tem_strCardBack  += tem_strCardFormat;
		tem_strPDFImg    += _T("PDF");
		tem_strPDFImg    += tem_strCardFormat;
		if (m_BSoundOpen)
		{
			sndPlaySound(_T("CameraSound.WAV"), NULL);
		}
		m_conVideoOcx.CaptureImage(tem_strCardBack);

		CxImage tem_FrontImage, tem_BackImage, tem_MergeImage;
		//a����������ֽ
		COLORREF    rgbBack = RGB(255, 255, 255);
		tem_MergeImage.Create(m_nA4Width, m_nA4Height, 24);
		for (unsigned int i=0; i<m_nA4Width; i++)
		{
			for (unsigned int j=0; j<m_nA4Height; j++)
			{
				tem_MergeImage.SetPixelColor(i, j, rgbBack);
			}
		}
		tem_MergeImage.SetXDPI(200);
		tem_MergeImage.SetYDPI(200);

		//b���������֤ͼ�񣬲�����dpi�Լ�ͼ��ߴ�
		tem_FrontImage.Load(g_strFrontImg, CXIMAGE_FORMAT_JPG);
		tem_FrontImage.SetXDPI(200);
		tem_FrontImage.SetYDPI(200);
		tem_FrontImage.Resample(m_nCardWidth, m_nCardHeight);

		tem_BackImage.Load(tem_strCardBack, CXIMAGE_FORMAT_JPG);
		tem_BackImage.SetXDPI(200);
		tem_BackImage.SetYDPI(200);
		tem_BackImage.Resample(m_nCardWidth, m_nCardHeight);

		//c���ϲ�ͼ��
		int   tem_nOffsetX = (m_nA4Width - m_nCardWidth)/2;    //���Ҿ���
		int   tem_nOffsetY = (m_nA4Height/2+(m_nA4Height/2 - m_nCardHeight)/2);
		tem_MergeImage.MixFrom(tem_FrontImage, tem_nOffsetX, tem_nOffsetY);
		tem_nOffsetY = (m_nA4Height/2 - m_nCardHeight/2);
		tem_MergeImage.MixFrom(tem_BackImage, tem_nOffsetX, tem_nOffsetY);

		//d������ͼ�񲢸�����ʾ

		if (m_strFileFormat == _T(".bmp"))
		{
			tem_MergeImage.Save(tem_strWholeName, CXIMAGE_FORMAT_BMP);
		} 
		else if (m_strFileFormat == _T(".jpg"))
		{
			tem_MergeImage.Save(tem_strWholeName, CXIMAGE_FORMAT_JPG);
		} 
		else if (m_strFileFormat == _T(".png"))
		{
			tem_MergeImage.Save(tem_strWholeName, CXIMAGE_FORMAT_PNG);
		} 
		else if (m_strFileFormat == _T(".tif"))
		{
			tem_MergeImage.Save(tem_strWholeName, CXIMAGE_FORMAT_TIF);
		}
		else if (m_strFileFormat == _T(".pdf"))
		{
			tem_MergeImage.Save(tem_strPDFImg, CXIMAGE_FORMAT_JPG);
			GeneratePDF(tem_strPDFImg, tem_strWholeName);
		}
		else if (m_strFileFormat == _T(".ofd"))
		{
			tem_MergeImage.Save(tem_strPDFImg, CXIMAGE_FORMAT_JPG);
			GenerateOFD(tem_strPDFImg, tem_strWholeName);
		}
		else
		{
			tem_MergeImage.Save(tem_strWholeName, CXIMAGE_FORMAT_JPG);
		}


		m_vcFileName.push_back(m_strFrontName);
		if (m_strFileFormat == _T(".pdf")||m_strFileFormat == _T(".ofd"))
		{
			tem_strThumbPath = GetThumbPath(tem_strPDFImg, m_strFrontName);    //��������ͼ
		}
		else
		{
			tem_strThumbPath = GetThumbPath(tem_strWholeName, m_strFrontName);    //��������ͼ
		}

		m_vcWholeName.push_back(tem_strThumbPath);                         //�洢����ͼ��������ʾ
		m_vcBussName.push_back(tem_strWholeName);
		ShowImageSize(tem_strWholeName);
		ThumbaiList(m_nThumbWidth, m_nThumbHeight);

		m_nImageCount++;
		m_nNamingCount++;
		//�����²�ҳ����ʾ
		int       tem_nPageNumber;
		CString   tem_strPageNumber;
		tem_nPageNumber = m_nImageCount + m_nImageCountOther;
		tem_strPageNumber.Format(_T("%d"), tem_nPageNumber);
		GetDlgItem(IDC_STA_NUMBER)->SetWindowText(tem_strPageNumber);

		CRect rtlbl; 
		GetDlgItem(IDC_STA_NUMBER)->GetWindowRect(&rtlbl); 
		ScreenToClient(&rtlbl); //ת���ͻ��˽���
		InvalidateRect(&rtlbl);//���ˢ�¶Ի��򱳾� 
		UpdateWindow();

		//e���ر��Ӵ���
	    m_dlgFront.DestroyWindow();

		//f�����ô�ӡ����
		ShellExecute(NULL, _T("print"), tem_strWholeName, NULL, NULL, SW_SHOWNORMAL);

		//g���ļ������ͷ��ڴ�
		DeleteFile(g_strFrontImg);
		DeleteFile(tem_strCardBack);
		//ofd�Ļ���ɾ�����ڵ��õ�exe��
		if (m_strFileFormat != _T(".ofd"))
		{
			DeleteFile(tem_strPDFImg);
		}
		

		m_BCardDlg = FALSE;
	}	
	
}


void CUDSSmartCamerav100Dlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: �ڴ˴������Ϣ����������
	if (m_BCardDlg)
	{
		GetDlgItem(IDC_UDS_VIDEOCTRL1)->GetWindowRect(&m_rcOCX);
		m_dlgFront.MoveWindow(m_rcOCX.left, m_rcOCX.top, 440, 160, TRUE);
	}
}


// ����豸���Ƿ��ظ�����XPϵͳ��Camera��ΪUSB��Ƶ�豸
CString CUDSSmartCamerav100Dlg::CheckCameraName(CString cameraname)
{
	CString  tem_strLastName   = _T("");
	CString  tem_strCameraName = cameraname;
	
	std::vector<CString>::iterator  iter;
	for (iter=m_vcCameraName.begin(); iter!=m_vcCameraName.end(); iter++)
	{
		if (tem_strCameraName == *iter)
		{
			tem_strLastName.Format(_T("%d"), m_nSameCameraLast);
			tem_strCameraName += _T("#");
			tem_strCameraName += tem_strLastName;
			m_nSameCameraLast++;
		}
	}
	m_vcCameraName.push_back(tem_strCameraName);

	return tem_strCameraName;
}


void CUDSSmartCamerav100Dlg::Self_SetBriValue(void)
{
	long   tem_lBrightMax = 0, tem_lBrightMin = 0, tem_lAutoBrg = 0, tem_lValueBrg = 0;
	m_lReturnCode = m_conVideoOcx.GetBrightnessRange(&tem_lBrightMin, &tem_lBrightMax);
	if (m_lReturnCode == 0)
	{
		//���ù�����
		m_iChildNor.m_conSlidBright.SetRange(tem_lBrightMin, tem_lBrightMax);   //����slider��Χ
		m_iChildNor.m_conSlidBright.SetPageSize(1);
//		m_conVideoOcx.GetBrightness(&tem_lValueBrg, &tem_lAutoBrg);
		UpdateData(TRUE);	
		if (m_nBriValue>=tem_lBrightMin && m_nBriValue<=tem_lBrightMax)
		{
			m_conVideoOcx.SetBrightness(m_nBriValue, FALSE);
			m_iChildNor.m_conSlidBright.SetPos(m_nBriValue);
			m_iChildNor.m_conStaBrg = m_nBriValue;
		} 
		else
		{
			m_conVideoOcx.SetBrightness(0, FALSE);
			m_iChildNor.m_conSlidBright.SetPos(0);
			m_iChildNor.m_conStaBrg = 0;
		}	
		
		m_iChildNor.m_conSlidBright.EnableWindow(TRUE);
		UpdateData(FALSE);
	}
}

// �Զ���ת
int CUDSSmartCamerav100Dlg::Self_RecognizeOrit(CString imgpath, BOOL on_off)
{
	if (!on_off)
	{
		return 0;
	}
	//1���ж�ͼ���Ƿ�Ϊtif,��Ϊtif��ʽ��ת��Ϊjpg--------------------------------
	BOOL      tem_BTR        = FALSE;
	CString   tem_strNewPath = _T("");

	wchar_t*  tem_wstrFormat = imgpath.GetBuffer();
	imgpath.ReleaseBuffer();
	tem_wstrFormat = PathFindExtension(tem_wstrFormat);
	CString tem_strFormat = tem_wstrFormat;
	tem_strFormat.MakeLower();
	if (tem_strFormat == _T(".tif"))
	{
		//ת��Ϊjpg��ʽ
		wchar_t*   tem_wstrName = imgpath.GetBuffer();
		tem_wstrName = PathFindFileName(tem_wstrName);
		CString   tem_strFileName = tem_wstrName;
		tem_strFileName.Replace(_T(".tif"), _T(".jpg"));
		tem_strNewPath  = m_strBufferPath;
		tem_strNewPath += _T("TR_");
		tem_strNewPath += tem_strFileName;


		CxImage tem_cxTrans;
		tem_cxTrans.Load(imgpath, CMAX_IMAGE_FORMATS);
		tem_cxTrans.SetJpegQuality(m_nJpegQulity);
		tem_cxTrans.Save(tem_strNewPath, CXIMAGE_FORMAT_JPG);
		tem_BTR        = TRUE;
	} 
	else
	{
		tem_strNewPath = imgpath;
		tem_BTR        = FALSE;
	}

	//2����ȡ��ת�Ƕ�--------------------------------------------------------------
	CStringA    tem_straImgPath(tem_strNewPath.GetBuffer(0));  tem_strNewPath.ReleaseBuffer();   
	string      tem_sImgPath = tem_straImgPath.GetBuffer(0);
	const char* tem_cImgPath = tem_sImgPath.c_str();

	tesseract::Orientation        tem_Orientation;
	tesseract::WritingDirection   tem_Direction;
	tesseract::TextlineOrder      tem_Oder;
	float                         tem_fAngle;
	int                           tem_nAnle = 0;
	PIX*                          tem_pImage = pixRead(tem_cImgPath);

	tesseract::TessBaseAPI*       tem_pAPI   = new tesseract::TessBaseAPI();

	//��ʼ��-------------------------------------------------------------------
	wchar_t tem_lpInpath[MAX_PATH]={0};
	GetModuleFileName(AfxGetStaticModuleState()->m_hCurrentInstanceHandle, tem_lpInpath, MAX_PATH);
	PathRemoveFileSpec(tem_lpInpath);

	CString     tem_strInpath = tem_lpInpath;
	CStringA    tem_straInpath(tem_strInpath.GetBuffer(0));   tem_strInpath.ReleaseBuffer();
	string      tem_sInpath   = tem_straInpath.GetBuffer(0);
	const char* tem_cInput = tem_sInpath.c_str();
	tem_pAPI->Init(tem_cInput, "data\\chi_sim");

	if (tem_pAPI != NULL)
	{

		tem_pAPI->SetPageSegMode(tesseract::PSM_AUTO_OSD);
		tem_pAPI->SetImage(tem_pImage);
		tesseract::PageIterator* item = tem_pAPI->AnalyseLayout();
		item->Orientation(&tem_Orientation, &tem_Direction, &tem_Oder, &tem_fAngle);
		CxImage  tem_cxRotate;
		/***************************
		ORIENTATION_PAGE_UP = 0,
		ORIENTATION_PAGE_RIGHT = 1,
		ORIENTATION_PAGE_DOWN = 2,
		ORIENTATION_PAGE_LEFT = 3,
		***************************/
		if (tem_Orientation == 0)
		{
			//UP
			tem_nAnle = 0;
		}
		else if (tem_Orientation == 1)
		{
			//RIGHT
			tem_nAnle = 90;
			tem_cxRotate.Load(imgpath, CMAX_IMAGE_FORMATS);
			tem_cxRotate.RotateLeft();
			if (tem_strFormat == _T(".jpg"))
			{
				tem_cxRotate.SetJpegQuality(m_nJpegQulity);
				tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_JPG);
			} 
			else if(tem_strFormat == _T(".bmp"))
			{
				tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_BMP);
			}
			else if(tem_strFormat == _T(".png"))
			{
				tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_PNG);
			}
			else if(tem_strFormat == _T(".tif"))
			{
				tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_TIF);
			}
			
		}
		else if (tem_Orientation == 2)
		{
			//DOWN
			tem_nAnle = 180;
			tem_cxRotate.Load(imgpath, CMAX_IMAGE_FORMATS);
			tem_cxRotate.Rotate(tem_nAnle);
			if (tem_strFormat == _T(".jpg"))
			{
				tem_cxRotate.SetJpegQuality(m_nJpegQulity);
				tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_JPG);
			} 
			else if(tem_strFormat == _T(".bmp"))
			{
				tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_BMP);
			}
			else if(tem_strFormat == _T(".png"))
			{
				tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_PNG);
			}
			else if(tem_strFormat == _T(".tif"))
			{
				tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_TIF);
			}
		}
		else if (tem_Orientation == 3)
		{
			//LEFT
			tem_nAnle = 270;
			tem_cxRotate.Load(imgpath, CMAX_IMAGE_FORMATS);
			tem_cxRotate.RotateRight();
			if (tem_strFormat == _T(".jpg"))
			{
				tem_cxRotate.SetJpegQuality(m_nJpegQulity);
				tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_JPG);
			} 
			else if(tem_strFormat == _T(".bmp"))
			{
				tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_BMP);
			}
			else if(tem_strFormat == _T(".png"))
			{
				tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_PNG);
			}
			else if(tem_strFormat == _T(".tif"))
			{
				tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_TIF);
			}
		}
	}

	tem_pAPI->End();
	pixDestroy(&tem_pImage);

	if (tem_BTR)
	{
		::DeleteFile(tem_strNewPath);
	}

	return tem_nAnle;
}


typedef std::pair<string, float> Prediction;
typedef std::vector<Prediction> Vec_Prediction;
typedef bool(_stdcall *Fun_GetPrediction)(const string& trained_file,
	const string& mean_file,
	const string& label_file,
	const string& image_file,
	string& best_prediction);
int CUDSSmartCamerav100Dlg::Self_RecognizeOrit2(CString imgpath, CString thumbpath, bool on_off)
{
	if (!on_off)
	{
		return 0;
	}
	
	//1���ж�ͼ���Ƿ�Ϊtif,��Ϊtif��ʽ��ת��Ϊjpg-----------------------------------
	CString   tem_strNewPath = imgpath;	

	CxImage tem_cxRotate;
	tem_cxRotate.Load(imgpath, CMAX_IMAGE_FORMATS);
	CxImage tem_cxTemp = tem_cxRotate;
	tem_cxTemp.SetJpegQuality(100);
	tem_cxTemp.Resample(224, 224);
	tem_cxTemp.Save(thumbpath, CXIMAGE_FORMAT_JPG);


	wchar_t*  tem_wstrFormat = imgpath.GetBuffer();
	imgpath.ReleaseBuffer();
	tem_wstrFormat = PathFindExtension(tem_wstrFormat);
	CString tem_strFormat = tem_wstrFormat;
	tem_strFormat.MakeLower();
		
	//3������dll���ļ�-------------------------------------------------------------
	wchar_t tem_lpInpath[MAX_PATH]={0};
	GetModuleFileName(AfxGetStaticModuleState()->m_hCurrentInstanceHandle, tem_lpInpath, MAX_PATH);
	PathRemoveFileSpec(tem_lpInpath);

	CString tem_strDllPath = tem_lpInpath; tem_strDllPath += _T("\\TD4.dll");

	CString tem_strTrained = tem_lpInpath; tem_strTrained += _T("\\td\\td11_iter_18000.td");
	CStringA tem_straTrained(tem_strTrained);
	string tem_sTrained = tem_straTrained.GetBuffer(0);

	CString tem_strMeanFile = tem_lpInpath; tem_strMeanFile+= _T("\\td\\td11_mean.binaryproto");
	CStringA tem_straMeanFIle(tem_strMeanFile);
	string tem_sMeanFile = tem_straMeanFIle.GetBuffer(0);

	CString tem_strLabelFile = tem_lpInpath; tem_strLabelFile += _T("\\td\\synset_words.txt");
	CStringA tem_straLabelFile(tem_strLabelFile);
	string tem_sLabelFile = tem_straLabelFile.GetBuffer(0); tem_straLabelFile.ReleaseBuffer();
	
	CStringA tem_straNewPath(thumbpath);
	string tem_sNewPath = tem_straNewPath.GetBuffer(0); tem_straNewPath.ReleaseBuffer();

	string tem_sResult;
	
	HMODULE tem_hMoudle = LoadLibraryEx(tem_strDllPath, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	if (tem_hMoudle == NULL)
	{
		return 0;
	}
	Fun_GetPrediction GetPrediction = (Fun_GetPrediction)GetProcAddress(tem_hMoudle, "GetPrediction");
	if (GetPrediction == NULL)
	{
		return 0;
	}
	GetPrediction(tem_sTrained, tem_sMeanFile, tem_sLabelFile, tem_sNewPath, tem_sResult);
	
	
	int tem_nAnle = 0;
	if (tem_sResult == "1")
	{
		//ͼ��Ϊ����90��
//		MessageBox(_T("������90��"));
		
		tem_nAnle = 90;
		tem_cxRotate.RotateLeft();
		if (tem_strFormat == _T(".jpg"))
		{
			tem_cxRotate.SetJpegQuality(m_nJpegQulity);
			tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_JPG);
		} 
		else if(tem_strFormat == _T(".bmp"))
		{
			tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_BMP);
		}
		else if(tem_strFormat == _T(".png"))
		{
			tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_PNG);
		}
		else if(tem_strFormat == _T(".tif"))
		{
			tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_TIF);
		}
	}
	else if (tem_sResult == "2")
	{
		//ͼ����
//		MessageBox(_T("����ת180��"));
		tem_nAnle = 180;
		tem_cxRotate.Rotate(tem_nAnle);
		if (tem_strFormat == _T(".jpg"))
		{
			tem_cxRotate.SetJpegQuality(m_nJpegQulity);
			tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_JPG);
		} 
		else if(tem_strFormat == _T(".bmp"))
		{
			tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_BMP);
		}
		else if(tem_strFormat == _T(".png"))
		{
			tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_PNG);
		}
		else if(tem_strFormat == _T(".tif"))
		{
			tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_TIF);
		}
	}
	else if (tem_sResult == "3")
	{
		//ͼ��Ϊ����90��
//		MessageBox(_T("������90��"));
		tem_nAnle = 270;
		tem_cxRotate.RotateRight();
		if (tem_strFormat == _T(".jpg"))
		{
			tem_cxRotate.SetJpegQuality(m_nJpegQulity);
			tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_JPG);
		} 
		else if(tem_strFormat == _T(".bmp"))
		{
			tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_BMP);
		}
		else if(tem_strFormat == _T(".png"))
		{
			tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_PNG);
		}
		else if(tem_strFormat == _T(".tif"))
		{
			tem_cxRotate.Save(imgpath, CXIMAGE_FORMAT_TIF);
		}
	}
	
	::DeleteFile(thumbpath);
	return tem_nAnle;
}

float CUDSSmartCamerav100Dlg::Self_GetColorPercentage(CxImage img, bool on_off)
{
	if (!on_off)
	{
		return -1;
	}
	CxImage  tem_cxImage = img;
	tem_cxImage.Light(30, 30);
//	tem_cxImage.Load(imgpath, CMAX_IMAGE_FORMATS);
	if (tem_cxImage.GetBpp() == 1)
	{
		//��ʱΪ�ڰ�ͼ��
		return -1;
	}

	int      tem_nWidth  = tem_cxImage.GetWidth();
	int      tem_nHeight = tem_cxImage.GetHeight();
	int      tem_nCount  = 0;                         //��¼��ɫ����

	for (int i=0; i<tem_nWidth; i++)
	{
		for (int j=0; j<tem_nHeight; j++)
		{
			RGBQUAD   rgb = tem_cxImage.GetPixelColor(i, j, false);
			if ((rgb.rgbRed<50 && rgb.rgbGreen<50 && rgb.rgbBlue<50) || (rgb.rgbRed>230 && rgb.rgbGreen>230 && rgb.rgbBlue>230))
			{	
			}
			else
			{
				//��Ϊ�ڰ׼�Ϊ��ɫ
				tem_nCount++;
			}
		}
	}
	float tem_fPer =  (float)tem_nCount*100.0 / (float)(tem_nWidth*tem_nHeight);
	return tem_fPer;
}


//img-����ͼ�� imgpath-���ͼ���·��
int CUDSSmartCamerav100Dlg::Self_DocOptimize(CxImage img, CString imgpath, BOOL on_off, int bright, int contrast)
{
	if (!on_off)
	{
		return 0;
	}
	CxImage tem_cxOptimize;
	tem_cxOptimize = img;
//	tem_cxOptimize.Load(imgpath, CMAX_IMAGE_FORMATS);

// 	tem_cxOptimize2 = tem_cxOptimize;
// 	tem_cxOptimize2.Light(bright, contrast);  //light=(-255, 255)   contrast=(-100, 100)
// 	tem_cxOptimize2.Save(_T("C:\\Users\\Administrator\\Desktop\\��֤�ȶ�\\����.jpg"), GetTypeFromFileName(imgpath));

// 	tem_cxOptimize2 = tem_cxOptimize;
// 	tem_cxOptimize2.Dilate(2);     //����
// 	tem_cxOptimize2.Save(_T("C:\\Users\\Administrator\\Desktop\\��֤�ȶ�\\����.jpg"), GetTypeFromFileName(imgpath));

// 	tem_cxOptimize2 = tem_cxOptimize;
// 	tem_cxOptimize2.Erode(2);      //��ʴ
// 	tem_cxOptimize2.Light(bright, contrast);  //light=(-255, 255)   contrast=(-100, 100)
// 	tem_cxOptimize2.Save(_T("C:\\Users\\Administrator\\Desktop\\��֤�ȶ�\\��ʴ_����.jpg"), GetTypeFromFileName(imgpath));

	tem_cxOptimize = tem_cxOptimize;
	tem_cxOptimize.Light(bright, contrast);  //light=(-255, 255)   contrast=(-100, 100)
	tem_cxOptimize.Erode(2);      //��ʴ

	//�ж��ļ���ʽ��jpg����ѹ����
	if (GetTypeFromFileName(imgpath) == CXIMAGE_FORMAT_JPG)
	{
		tem_cxOptimize.SetJpegQuality(m_nJpegQulity);
	}

	tem_cxOptimize.Save(imgpath, GetTypeFromFileName(imgpath));
	
	return 0;
}


int CUDSSmartCamerav100Dlg::Self_DocOptimize2(CxImage img, CString imgpath, bool on_off)
{
	//1��ͼ�����--------------------------------------------------------------------------
	CxImage m_Image = img;
//	m_Image.Load(imgpath, CMAX_IMAGE_FORMATS);

	CxImage imageSrc,imageRed;
	imageSrc.CreateFromArray(m_Image.GetBits(),m_Image.GetWidth(),
		m_Image.GetHeight(),m_Image.GetBpp(),m_Image.GetEffWidth(),false);   

	//2����ֵ��----------------------------------------------------------------------------
	IplImage * imageCV,*image_CVBW;
	imageCV = cvCreateImage(cvSize(m_Image.GetWidth(),m_Image.GetHeight()),IPL_DEPTH_8U,3);
	image_CVBW = cvCreateImage(cvSize(m_Image.GetWidth(),m_Image.GetHeight()),IPL_DEPTH_8U,1);
	imageCV->imageData = (char*)m_Image.GetBits();
	
	cvCvtColor(imageCV,image_CVBW,CV_BGR2GRAY);
	
	cvAdaptiveThreshold(image_CVBW,image_CVBW,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY,65);
	m_Image.Destroy();
	m_Image.CreateFromArray((BYTE *)image_CVBW->imageData,image_CVBW->width,image_CVBW->height,image_CVBW->nChannels * 8,
		image_CVBW->widthStep,FALSE);
	//m_Image.Threshold(128);;
	cvReleaseImage(&imageCV);
	cvReleaseImage(&image_CVBW);
	m_Image.IncreaseBpp(24);

	//����;
	RGBQUAD srcColor,srcColorRed;
	RGBQUAD hsl;
	RGBQUAD fillColor,fillColorWight;
	fillColorWight.rgbBlue = fillColorWight.rgbGreen = fillColorWight.rgbRed = 255;
	fillColor.rgbRed = 255;
	fillColor.rgbBlue = fillColor.rgbGreen = 0;
	for (int i = 0 ;i < m_Image.GetHeight() ;i ++)
	{
		for (int j = 0 ;j < m_Image.GetWidth() ;j ++)
		{
			srcColor = imageSrc.GetPixelColor(j,i);
			hsl = CxImage::RGBtoHSL(srcColor);
			if (((hsl.rgbRed >= 0 && hsl.rgbRed < 15)|| (hsl.rgbRed > 240 && hsl.rgbRed <= 255))
				&&hsl.rgbBlue < 150 && hsl.rgbBlue > 30)
			{				
				imageSrc.SetPixelColor(j,i,fillColor);				
			}
			else
			{
				imageSrc.SetPixelColor(j,i,fillColorWight);	
			}
		}
	}
	imageCV = cvCreateImage(cvSize(m_Image.GetWidth(),m_Image.GetHeight()),IPL_DEPTH_8U,3);
	imageCV->imageData = (char*)imageSrc.GetBits();
	IplImage * imageCV_Smooth = cvCreateImage(cvSize(m_Image.GetWidth(),m_Image.GetHeight()),IPL_DEPTH_8U,3);
	//ȥ��;
	cvSmooth(imageCV,imageCV_Smooth,CV_MEDIAN,3);
	cvSmooth(imageCV_Smooth,imageCV_Smooth,CV_MEDIAN);
	IplConvKernel * kerner = cvCreateStructuringElementEx(30,30,0,0,CV_SHAPE_RECT,NULL);
	cvErode(imageCV_Smooth,imageCV_Smooth,kerner);

	imageRed.CreateFromArray((BYTE *)imageCV_Smooth->imageData,imageCV_Smooth->width,imageCV_Smooth->height,imageCV_Smooth->nChannels * 8,
		imageCV_Smooth->widthStep,FALSE);


	cvReleaseStructuringElement(&kerner);
	cvReleaseImage(&imageCV_Smooth);
	cvReleaseImage(&imageCV);

	for (int i = 0 ;i < m_Image.GetHeight() ;i ++)
	{
		for (int j = 0 ;j < m_Image.GetWidth() ;j ++)	
		{
			srcColor = imageSrc.GetPixelColor(j,i);
			srcColorRed = imageRed.GetPixelColor(j,i);

			hsl = CxImage::RGBtoHSL(srcColor);
			if (((hsl.rgbRed >= 0 && hsl.rgbRed < 20)|| (hsl.rgbRed > 234 && hsl.rgbRed <= 255))
				&& srcColorRed.rgbGreen == 0)
			{				
				m_Image.SetPixelColor(j,i,fillColor);				
			}
		}
	}

	//�ж��ļ���ʽ��jpg����ѹ����
	if (GetTypeFromFileName(imgpath) == CXIMAGE_FORMAT_JPG)
	{
		m_Image.SetJpegQuality(m_nJpegQulity);
	}
	m_Image.Save(imgpath, GetTypeFromFileName(imgpath));
	return 0;
}


afx_msg LRESULT CUDSSmartCamerav100Dlg::OnFaceid(WPARAM wParam, LPARAM lParam)
{
	//1������------------------------------------------------------------------
	CString   tem_strName      = _T("");   //�޺�׺
	CString   tem_strFileName  = _T("");   //����׺
	CString   tem_strWholeName = _T("");   //��·��,ͼ���ļ�
	CString   tem_strThumbPath = _T("");   //����ͼ·��

	if (m_BSoundOpen)
	{
		sndPlaySound(_T("CameraSound.WAV"), NULL);
	}

	tem_strName      = NamingFile(3);
	if (m_BPDFCpt || m_BBase64Cpt || m_BDcmCpt)
	{
		tem_strFileName  = tem_strName + _T(".jpg");
	} 
	else
	{
		tem_strFileName  = tem_strName + m_strFileFormat;
	}
	tem_strWholeName = m_strFaceDoc + tem_strFileName;
	m_conVideoOcx.CaptureImage(tem_strWholeName);
	g_strFaceImg = tem_strWholeName;
	return 0;
}

void CUDSSmartCamerav100Dlg::Self_ReplaceImage(int thumbwidth, int thumbheight, int item)
{
	CString    tem_strItemPath = m_vcWholeName[item];

	COLORREF      m_clBackColor = RGB(72, 77, 91);
	HBRUSH hBrushBorder    =::CreateSolidBrush(m_clBackColor);       //����ͼ�߿�ɫ
	HBRUSH hBrushBkground  =::CreateSolidBrush(m_clBackColor);       //����ͼ����ɫ

	float fRatio=(float)thumbheight/thumbwidth; 
	RECT rcBorder;
	rcBorder.left=rcBorder.top  =0;
	rcBorder.right              =thumbwidth;
	rcBorder.bottom             =thumbheight;

	int XDest,YDest,nDestWidth,nDestHeight;
	CxImage    image; 
	int nImageType=GetTypeFromFileName(tem_strItemPath);
	image.Load(tem_strItemPath, nImageType);
	float fImgRatio=(float)image.GetHeight()/image.GetWidth();  
	if(fImgRatio>fRatio)
	{
		nDestWidth=(int)thumbheight/fImgRatio;   
		XDest=(thumbwidth-nDestWidth)/2;
		YDest=0;
		nDestHeight=thumbheight;
	}
	else
	{
		XDest=0;
		nDestWidth=thumbwidth;
		nDestHeight=(int)thumbwidth*fImgRatio;  
		YDest=(thumbheight-nDestHeight)/2;
	}

	CClientDC cdc(this);
	HDC hDC=::CreateCompatibleDC(cdc.m_hDC);
	HBITMAP bm=CreateCompatibleBitmap(cdc.m_hDC,thumbwidth,thumbheight);
	HBITMAP pOldBitmapImage=(HBITMAP)SelectObject(hDC,bm);

	::FillRect(hDC,&rcBorder,hBrushBkground);
	image.Stretch(hDC,XDest,YDest,nDestWidth,nDestHeight);
	::FrameRect(hDC,&rcBorder,hBrushBorder);
	SelectObject(hDC,pOldBitmapImage);
	CBitmap bitmap;
	bitmap.Attach(bm);
	m_imagelist.Replace(item,&bitmap,NULL);
	m_conListCtrl.RedrawItems(item, item);           //ListCtrl�ػ��Ӧ��ǰҳ����Item������
	DeleteDC(hDC);
	DeleteObject(bm);



	DeleteObject(hBrushBorder);
	DeleteObject(hBrushBkground);
}


CString CUDSSmartCamerav100Dlg::GenerateOFD(CString srcImg, CString dstImg)
{
	CString tem_strImgPath = srcImg;
	CString tem_strOfdPath = dstImg;

	SHELLEXECUTEINFO tem_Info = {0};
	tem_Info.cbSize = sizeof(SHELLEXECUTEINFO);
	tem_Info.fMask = SEE_MASK_NOCLOSEPROCESS;
	tem_Info.hwnd = NULL;
	tem_Info.lpVerb = _T("Open");
	tem_Info.lpFile = _T("editor.exe");

	//���롢����ļ�·��-----------------------------------------------------
	CString tem_strFilesPath = _T("");
	tem_strFilesPath.Format(_T("\"%s\" \"%s\" \"%s\""), _T("1"), tem_strOfdPath, tem_strImgPath);
	MessageBox(tem_strFilesPath);
	tem_Info.lpParameters = tem_strFilesPath;

	//editor.exeȫ·��------------------------------------------------------
	TCHAR        tem_tcExePath[MAX_PATH+1] = {0};
	GetModuleFileName(NULL, tem_tcExePath, MAX_PATH);
	(_tcsrchr(tem_tcExePath, _T('\\')))[1] = 0;
	CString tem_strExePath = tem_tcExePath;
	tem_strExePath += _T("ofd\\");

	tem_Info.lpDirectory = tem_strExePath;
	tem_Info.nShow = SW_HIDE;
	tem_Info.hInstApp = NULL;
	ShellExecuteEx(&tem_Info);
	
	return tem_strOfdPath;
}
