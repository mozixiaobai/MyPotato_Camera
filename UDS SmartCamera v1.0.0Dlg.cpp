
// UDS SmartCamera v1.0.0Dlg.cpp : 实现文件
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


CString    g_strFrontImg;   //身份证正面图像路径
CString    g_strFaceImg;    //现场拍摄图像路径
CString    m_strDefaultPath;   //默认路径

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{  
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CUDSSmartCamerav100Dlg 对话框




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


// CUDSSmartCamerav100Dlg 消息处理程序

BOOL CUDSSmartCamerav100Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	/*****************************************************
	*
	* 1、 Tab控件初始化
	* 2、 OCX控件初始化
	* 3、 默认路径配置
	* 4、 下栏初始化
	* 5、 设置界面初始化
	* 6、 png按钮初始化
	* 7、 按钮文字提示
	* 8、 ListCtrl初始化
	* 9、 UI美化
	* 10、Menu菜单初始化
	* 11、检测USB口的变动情况
	*
    ******************************************************/

	//0、-------------------------------------------
	m_nImageCount      = 0;
	m_nNamingCount     = 1;
	m_nImageCountOther = 0;
//	m_nLastUsedScanner = 1;  //读取配置文件可以赋值给该参数
	m_nLastUsedResolu  = 0;
	m_nLastUsedFile    = 1;
	m_nLastUsedColor   = 2;
	m_strFileFormat    = ".jpg";
	m_nManualVaule     = 0;
	m_BAutoExp         = TRUE;
	m_BAutoCrop        = TRUE;
	m_BManualCrop      = FALSE;
	//DLL和OCX分割线---------------------------------
	m_lReturnCode  = 0;
	m_nLastSubScan = -1;   //读取配置文件副头
	m_nLastSubRes  = 0;
	m_nRotate      = 0;
	m_nJpegQulity  = 50;
	m_nAutoSense   = 6;
	m_nVideoWidth  = 640;       //视频宽
	m_nVideoHeight = 480;       //视频高
	m_nVideoBit    = 600;         //视频比特率
	m_nVideoFPS    = 24;         //视频帧率
	m_BPDFCpt      = FALSE;     //从配置文件读取时注意文件格式对应
	m_BBase64Cpt   = FALSE;     //同上
	m_BDcmCpt      = FALSE;     //DCM拍照，初始化关闭
	m_BOfdCpt      = FALSE;     //OFD拍照
	m_BMerge       = FALSE;
	m_nMergeMode   = 1;         //默认内部合并
	m_nMergeLocation = 3;       //默认右上角
	m_nNamingMode    = 0;       //默认0-顺序命名， 1-时间命名， 2-前缀命名, 3-前缀+时间命名
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

	m_strPID800  = _T("BC01");        //800W量产机
	m_strVID800  = _T("8001");

	m_strPID800GS= _T("10A4");       //GS1000,800->1000W
	m_strVID800GS= _T("1B17");

	m_strPID800b = _T("6366");        //800W样机
	m_strVID800b = _T("0C45");

	m_strPID1200 = _T("0013");        //1000W设备PID_VID未定
	m_strVID1200 = _T("0EDC");  

	m_strPID1300 = _T("150C");
	m_strVID1300 = _T("1B17");

	m_strPIDTo1500 = _T("0F10");
	m_strVIDTo1500 = _T("0AC8");

	m_BGS1600     = FALSE;
	m_strGS16_PID = _T("BC01");
	m_strGS16_VID = _T("1301");

	m_strPID800Un= _T("0800");       //未知机型800->1000W, GS1000
	m_strVID800Un= _T("1B17"); 

	m_nInterpolateReso    = 0;
	m_nInterpolateSubReso = 0;
	
	m_nCardWidth = 674;    //存在一定偏移误差，标准尺寸为647*426
	m_nCardHeight= 426;
	m_nA4Width   = 1580;
	m_nA4Height  = 2280;
	m_nSameCameraLast = 2;
	m_nAudioIndex     = 0;

	m_BSoundOpen = TRUE;
	m_BOcrOpened = FALSE;

 	m_fColorPercentage = 13.0;

//	m_iCard = new CCardReader();   //初始化身份证读卡器

	m_nScreenWidth  = GetSystemMetrics(SM_CXSCREEN);
	m_nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	//配置GDI+----------------------------------------
	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_pGdiToken;
	GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL);

	//3、---------------------------------------------
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

	//创建缩略图缓存目录
	m_strBufferPath  = m_strIniPath;
	m_strBufferPath += _T("ScanBuffer");
	CFileFind    tem_fFileFind;
	if (!tem_fFileFind.FindFile(m_strBufferPath))
	{
		CreateDirectory(m_strBufferPath, NULL);
	}
	m_strBufferPath += _T("\\");

	m_strFingerDoc  = m_strIniPath;
	m_strFingerDoc += _T("身份证信息");
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

	m_strIniPath   += _T("config.ini");   //配置文件路径

	
	LoadIniFile();

/*	//如果从配置文件中没有读取到默认保存路径，创建缓存文件夹
	m_strDefaultPath += "ScanBuffer";
	CFileFind    tem_fFileFind;
	if (!tem_fFileFind.FindFile(m_strDefaultPath))
	{
		CreateDirectory(m_strDefaultPath, NULL);
	}
	m_strDefaultPath += "\\";
*/
	
	
	//1、-------------------------------------------
	//设置选项卡名称
	m_conTab.InsertItem(0, _T("主头"));
	m_conTab.InsertItem(1, _T("副头"));
	m_conTab.InsertItem(2, _T("高级"));

	//设置默认选项卡
	m_iChildNor.Create(IDD_DLG_CHILDNORMAL, GetDlgItem(IDC_TAB_SET));
	m_iChildAdv.Create(IDD_DLG_CHILDADV, GetDlgItem(IDC_TAB_SET));
	m_iChildSet.Create(IDD_DLG_SET, GetDlgItem(IDC_TAB_SET));

	//获取Tab客户区大小
	CRect   rcTab;
	m_conTab.GetClientRect(&rcTab);
	rcTab.top     += 22;  //上侧若填充完全会把标签栏覆盖，遗留问题Tab控件设置标签颜色
// 	rcTab.left    += 3;   //左、右、下侧不填充完全，设置背景后会留下白边
// 	rcTab.right   -= 3;
// 	rcTab.bottom  -= 10;

	//调整对话框大小在父窗口中的位置
	m_iChildNor.MoveWindow(&rcTab);
	m_iChildAdv.MoveWindow(&rcTab);
	m_iChildSet.MoveWindow(&rcTab);

	////设置标签栏的宽高
	//int cx = (rcTab.right-rcTab.left-30)/3;
	//int cy = 40;
	//CSize   tem_sizeTab;
	//tem_sizeTab.cx = cx;
	//tem_sizeTab.cy = cy;
	//m_conTab.SetItemSize(tem_sizeTab);
	//CFont   tem_fontTab;
	//tem_fontTab.CreatePointFont(50, _T("宋体"));
	//m_conTab.SetFont(&tem_fontTab);
	//


	//设置默认显示和隐藏
	m_iChildNor.ShowWindow(TRUE);
	m_iChildAdv.ShowWindow(FALSE);
	m_iChildSet.ShowWindow(FALSE);

	m_conTab.SetCurSel(0);

	//2、----------------------------------------------
	m_lReturnCode = m_conVideoOcx.Initial();
	if (m_lReturnCode != 0)
	{
		MessageBox(_T("控件初始化失败！"), _T("紫图UDS"), MB_OK);

//		::SendMessage(m_hWnd, WM_CLOSE, NULL, NULL);
		CDialog::OnOK();   //1027XP系统上存在错误，将sendmessage修改为onok
		return FALSE;
	}
	m_straDeviceName.RemoveAll();
	int      tem_nDevCount = m_conVideoOcx.GetDeviceCount();//当前设备数量
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

		//优先打开紫图设备，若未发现紫图设备打开第上次使用设备个设备
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
			//获取每个设备的PID和VID并匹配是否为紫图设备
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
			//获取每个设备的PID和VID并匹配是否为紫图设备
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

		m_lReturnCode = m_conVideoOcx.StartRun(m_nLastUsedScanner);         //启动摄像头

		m_conVideoOcx.RotatedVideo(m_nRotate);
		m_nMainOpen = m_lReturnCode;
		

		//查看打开的设备是否为指定设备----------------------------------------------
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
			//设备打开成功，首先获取设备PID_VID
			tem_strPIDVID = m_conVideoOcx.GetDevDisplayName(m_nLastUsedScanner);
			//检查该PID_VID是否为指定的设备
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
				//该设备为指定设备，添加指定分辨率
				//800W->1000W
				m_BCamera800 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{
					
					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("3664×2744");
				m_iChildNor.m_conComReso.InsertString(-1, tem_strResolution);

				//如果设置当前分辨率索引大于总个数，说明该分辨率为插值分辨率，应设置为硬件最大分辨率
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//找出最大分辨率对应索引
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
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("3664*2744");
				m_iChildNor.m_conComReso.InsertString(-1, tem_strResolution);

				//如果设置当前分辨率索引大于总个数，说明该分辨率为插值分辨率，应设置为硬件最大分辨率
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//找出最大分辨率对应索引
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
 				int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
				m_nInterpolateReso   = tem_nResCount;
 				for (int i=0; i<tem_nResCount; i++)
 				{
 
 					tem_strResolution = m_conVideoOcx.GetResolution(i);
 					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
 				}
 				tem_strResolution = _T("4680×3510");
 				m_iChildNor.m_conComReso.InsertString(-1, tem_strResolution);
 
 				//如果设置当前分辨率索引大于总个数，说明该分辨率为插值分辨率，应设置为硬件最大分辨率
 				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
 				if (m_nLastUsedResolu == m_nInterpolateReso)
 				{
 					//找出最大分辨率对应索引
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
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("4480×3360");
				m_iChildNor.m_conComReso.InsertString(-1, tem_strResolution);

				//如果设置当前分辨率索引大于总个数，说明该分辨率为插值分辨率，应设置为硬件最大分辨率
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
				CString    tem_strCurRes;
				int        tem_nFindIndex;
				CString    tem_strFirst;
				CString    tem_strLast;
				int        tem_nFirst;
				int        tem_nLast;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//找出最大分辨率对应索引
// 					int  tem_nMaxIndex = GetmaxResoindex(); 
// 					m_conVideoOcx.SetResolution(tem_nMaxIndex);
					//获得第二大分辨率
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
				//插值到1500W------------------------------------------------1010
				m_BCameraTo1500 = TRUE;
				
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("4480×3360");
				m_iChildNor.m_conComReso.InsertString(-1, tem_strResolution);

				//如果设置当前分辨率索引大于总个数，说明该分辨率为插值分辨率，应设置为硬件最大分辨率
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
				CString    tem_strCurRes;
				int        tem_nFindIndex;
				CString    tem_strFirst;
				CString    tem_strLast;
				int        tem_nFirst;
				int        tem_nLast;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//找出最大分辨率对应索引
//					int  tem_nMaxIndex = GetmaxResoindex(); 
//					m_conVideoOcx.SetResolution(tem_nMaxIndex);
					//获取第二大分辨率
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

				int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("4928×3264");
				m_iChildNor.m_conComReso.InsertString(-1, tem_strResolution);

				//如果设置当前分辨率索引大于总个数，说明该分辨率为插值分辨率，应设置为硬件最大分辨率
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
				CString    tem_strCurRes;
				int        tem_nFindIndex;
				CString    tem_strFirst;
				CString    tem_strLast;
				int        tem_nFirst;
				int        tem_nLast;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//获取最大分辨率索引
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
				//副头 200W->300W-------------------------------------------0126
				m_BCamera200 = TRUE;

				int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{
					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("2048×1536");
				m_iChildNor.m_conComReso.InsertString(-1, tem_strResolution);

				//如果设置当前分辨率索引大于总个数，说明该分辨率为插值分辨率，应设置为硬件最大分辨率
				m_iChildNor.m_conComReso.SetCurSel(m_nLastUsedResolu);
				CString    tem_strCurRes;
				int        tem_nFindIndex;
				CString    tem_strFirst;
				CString    tem_strLast;
				int        tem_nFirst;
				int        tem_nLast;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//获取最大分辨率索引
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
				//该设备为普通设备
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
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
			//获取曝光范围
			//默认开启自动曝光
			m_iChildNor.m_conStaExpStr = _T("");   
			long tem_lExmin = 0, tem_lExmax = 0, tem_lAutoExp = 0, tem_lValue = 0;
			m_lReturnCode = m_conVideoOcx.GetExposureRange(&tem_lExmin, &tem_lExmax);
			//	m_conVideoOcx.SetAutoExposure(m_BAutoExp);   //设置默认自动曝光ini可通过该参数修改
			if (m_lReturnCode == 0)
			{
				 
				m_iChildNor.m_conSlidExpos.SetRange(tem_lExmin, tem_lExmax); //设置slider范围
				m_iChildNor.m_conSlidExpos.SetPageSize(1);
				m_conVideoOcx.GetExposure(&tem_lValue, &tem_lAutoExp);
				UpdateData(TRUE);
				m_iChildNor.m_conSlidExpos.SetPos(tem_lValue);       //设置slider当前值
				m_iChildNor.m_conStaExp = tem_lValue;                //设置slider显示当前值
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
			
			//设置旋转方向


			//获取亮度范围
			//设置默认亮度
			long   tem_lBrightMax = 0, tem_lBrightMin = 0, tem_lAutoBrg = 0, tem_lValueBrg = 0;
			m_lReturnCode = m_conVideoOcx.GetBrightnessRange(&tem_lBrightMin, &tem_lBrightMax);
			if (m_lReturnCode == 0)
			{
				//设置滚动条
				m_iChildNor.m_conSlidBright.SetRange(tem_lBrightMin, tem_lBrightMax);   //设置slider范围
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
			
//			m_conVideoOcx.SetAutoExposure(m_BAutoExp);   //设置默认自动曝光ini可通过该参数修改
//			m_conVideoOcx.SetAutoExposure(TRUE);   //设置默认自动曝光ini可通过该参数修改
			
			m_conVideoOcx.AdjuestImageCrop(m_BAutoCrop);  //默认开始自动裁切,ini可通过该参数修改
			if (!m_BAutoCrop)
			{
				m_conVideoOcx.ManualImageCrop(m_BManualCrop);
			}
			m_conVideoOcx.SetJpegQuality(m_nJpegQulity);  //设置默认JPEG质量
			m_conVideoOcx.SetAutomaticSensitiveness(m_nAutoSense);  //设置自动连拍的灵敏度
		}
		else
		{
			MessageBox(_T("未发现指定设备！"), _T("紫图UDS"), MB_OK);
		}
	}
	else
	{
		m_conVideoOcx.Uninitial();
		MessageBox(_T("未找到可用设备！"), _T("紫图UDS"), MB_OK);
		::SendMessage(m_hWnd, WM_CLOSE, NULL, NULL);
	}
	
	//4、-------------------------------------------------------------------------
	GetDlgItem(IDC_STA_INFOPATH)->SetWindowText(m_strShowPath);
	GetDlgItem(IDC_STA_NUMBER)->SetWindowText(_T("0"));

	//5、-------------------------------------------------------------------------
	m_conVideoOcx.ShowVideoInfo(m_BShowInfo);     //视频信息
	m_conVideoOcx.SetJpegQuality(m_nJpegQulity);  //图像质量
	m_conVideoOcx.SetAutomaticSensitiveness(m_nAutoSense);//连拍灵敏度

	//5.5音频设备初始化-----------------------------------------------------------
	//获取音频设备列表
	int tem_nAudioCount = m_conVideoOcx.GetAudioDevCount();
	for(int i=0; i<tem_nAudioCount; i++)
	{
		CString tem_strAudioName = m_conVideoOcx.GetAudioDevName(i);
		m_iChildNor.m_conAudio.InsertString(i, tem_strAudioName);
	}
	//设置默认设备
	m_iChildNor.m_conAudio.SetCurSel(0);




	//6、-----------------------------------------------------------------------
//	CImage  m_imgBK;
	LoadPicture(Image, IDB_PNG_BK);   //使用PngButton加载背景
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

	//7、-------------------------------------------------------------------------
	m_tipInfo.Create(this);
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_CAPATURE), _T("主头拍照"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_CAPBAR), _T("条码命名拍照"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_CAPGOON), _T("自动连拍"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_CAP2SIDE), _T("正反面合并拍照"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_BROWS), _T("打开保存目录"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_TEST2), _T("退出"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_DECLEAR), _T("最大化"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_MIN), _T("最小化"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_SAVEPATH), _T("选择保存目录"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_LROTATE), _T("预览左旋"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_RROTATE), _T("预览右旋"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_READCARD), _T("身份证读卡"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_ZOOMIN), _T("预览放大"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_ZOOMOUT), _T("预览缩小"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_RECOVER), _T("预览适合"));
	m_tipInfo.AddTool(GetDlgItem(IDC_BTN_CARDCOPY), _T("身份证复印"));
	
	m_tipInfo.SetDelayTime(TTDT_INITIAL, 100);    //设置鼠标悬浮显示时间
	m_tipInfo.SetDelayTime(TTDT_AUTOPOP, 5000);   //设置显示时间
	m_tipInfo.SetDelayTime(TTDT_RESHOW, 100);     //设置切换按钮时间隔时间
	m_tipInfo.SetTipTextColor(RGB(255, 255, 255));//设置字体颜色
	m_tipInfo.SetTipBkColor(RGB(0, 0, 0));//设置提示框背景颜色
	m_tipInfo.Activate(TRUE); //启用提示功能

	GetDlgItem(IDC_BTN_ZOOMOUT)->EnableWindow(FALSE);

	//8、-------------------------------------------------------------------------
	m_conListCtrl.SetBkColor(RGB(72,77,91));

	//9、-------------------------------------------------------------------------
	//Static控件美化
//	SetWindowTheme(GetDlgItem(IDC_STA_GRP_SM)->GetSafeHwnd(), L"", L"");

	//Tab控件美化


	//添加背景

	//10、-------------------------------------------------------------------------
	CreateHSMenu();
	CDialogEx::SetBackgroundColor(RGB(72,77,91));

	//图像尺寸
	GetDlgItem(IDC_STA_IMAGESIZE)->GetWindowRect(&m_rcImageSize); 
	ScreenToClient(&m_rcImageSize); //转到客户端界面
	GetDlgItem(IDC_STA_IMAGESIZE)->SetWindowText(_T("图像大小:"));

	//11、-------------------------------------------------------------------------
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
	
	OnBnClickedBtnDeclear();    //启动最大化
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CUDSSmartCamerav100Dlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	//设置标签栏的宽高
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUDSSmartCamerav100Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (m_BDownBk)
		{
			/*方法一：CImage类加载Png图像，但是影响了按钮控件的状态显示
			//加载图像背景
			
			CDC *pDC = GetDC();		
			Image.Load(_T("res\\BK.png"));
//			Image.LoadFromResource(AfxGetInstanceHandle(), IDB_PNG_BK);
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
			m_BDownBk = FALSE;
			*/


			//方法二：使用PngButton::LoadPicture加载背景
			
			CPaintDC dc(this);
			CDC* pDC = &dc;

			CDC dcMem;
			dcMem.CreateCompatibleDC(pDC);

			CRect rcClient;
			GetClientRect(rcClient);

			CBitmap memBitmap;
			memBitmap.CreateCompatibleBitmap(pDC, rcClient.Width(), rcClient.Height());
			dcMem.SelectObject(memBitmap);

			dcMem.FillSolidRect(rcClient, RGB(255, 255, 255));	//设置画布颜色

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
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CDialogEx::OnEraseBkgnd(pDC);
}


HBRUSH CUDSSmartCamerav100Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO:  在此更改 DC 的任何特性
	//Statci控件美化
	if (pWnd->GetDlgCtrlID() == IDC_STA_NUMCOUNT || pWnd->GetDlgCtrlID()==IDC_STA_NUMBER || pWnd->GetDlgCtrlID()==IDC_STA_PAGE ||
		pWnd->GetDlgCtrlID()==IDC_STA_NOWPATH || pWnd->GetDlgCtrlID()==IDC_STA_INFOPATH ||pWnd->GetDlgCtrlID()==IDC_STA_IMAGESIZE)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
//		pDC->SetTextColor(RGB(246, 246, 11));
		pDC->SetTextColor(RGB(255, 255, 255));
		CFont   tem_Font;
		tem_Font.CreatePointFont(100, _T("宋体"));
		pDC->SelectObject(&tem_Font);
	}
	else if (pWnd->GetDlgCtrlID()==IDC_STA_BIAOTI)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
//		pDC->SetTextColor(RGB(174, 174, 175));
		pDC->SetTextColor(RGB(255, 255, 255));
		CFont   tem_FontSta;
		tem_FontSta.CreatePointFont(250, _T("黑体"));
//		tem_FontSta.CreateFont(40, 30, 0, 0, FW_BOLD, TRUE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_SWISS, _T("楷体"));
		pDC->SelectObject(&tem_FontSta);
	}
// 	if (pWnd->GetDlgCtrlID()==IDC_STA_GRP_SM)
// 	{
// 		pDC->SetTextColor(RGB(255, 255, 255));//字体白色
// 		hbr = CreateSolidBrush(RGB(0, 0, 0));//背景颜色
// 		
// 	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	
	return hbr;
}


//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUDSSmartCamerav100Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUDSSmartCamerav100Dlg::LoadIniFile(void)
{
	int        tem_nRead   = 0;
	CString    tem_strRead = _T("");

	//主头相关设置--------------------
	::GetPrivateProfileString(_T("ParentCamera"), _T("LastUsed"), _T("没有找到主头LastUsed信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastUsedScanner = tem_nRead;

	::GetPrivateProfileString(_T("ParentCamera"), _T("Resolution"), _T("没有找到Resolution信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nLastUsedResolu = tem_nRead;

	::GetPrivateProfileString(_T("ParentCamera"), _T("FileMode"), _T("没有找到FileMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
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

	::GetPrivateProfileString(_T("ParentCamera"), _T("ColorMode"), _T("没有找到ColorMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
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
	
	::GetPrivateProfileString(_T("ParentCamera"), _T("AutoCrop"), _T("没有找到AutoCrop信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
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

	::GetPrivateProfileString(_T("ParentCamera"), _T("AutoExp"), _T("没有找到AutoExp信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
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
	::GetPrivateProfileString(_T("ParentCamera"), _T("VideoRotate"), _T("没有找到VideoRotate信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	m_nRotate = tem_nRead;


	::GetPrivateProfileString(_T("ParentCamera"), _T("ExpValue"), _T("没有找到ExpValue信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
	m_nManualVaule = tem_nRead;

	::GetPrivateProfileString(_T("ParentCamera"), _T("BriValue"), _T("没有找到BriValue信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
	m_nBriValue = tem_nRead;

	::GetPrivateProfileString(_T("Resource"), _T("AutoRotate"), _T("没有找到AutoRotate信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
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

	::GetPrivateProfileString(_T("Resource"), _T("AutoOptimize"), _T("没有找到AutoOptimize信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
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

	//副头相关设置----------------------
//	::GetPrivateProfileString(_T("ChildCamera"), _T("LasrUsed"), _T("没有找到副头LasrUsed信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
//	tem_nRead = _ttoi(tem_strRead);
//	m_nLastSubScan = tem_nRead;

// 	::GetPrivateProfileString(_T("ChildCamera"), _T("Resolution"), _T("没有找到副头Resolution信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
// 	tem_nRead = _ttoi(tem_strRead);
// 	m_nLastUsedFile = tem_nRead;

	//设置部分--------------------------
	::GetPrivateProfileString(_T("AdvanceSet"), _T("ShowInfo"), _T("没有找到ShowInfo信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
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

	::GetPrivateProfileString(_T("AdvanceSet"), _T("JPEGQuality"), _T("没有找到JPEGQuality 信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	if (tem_nRead>0 && tem_nRead<100)
	{
		m_nJpegQulity   = tem_nRead;
	}
	else
	{
		m_nJpegQulity   = 50;
	}

	::GetPrivateProfileString(_T("AdvanceSet"), _T("AutoCaptureSense"), _T("没有找到AutoCaptureSense信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	if (tem_nRead>0)
	{
		m_nAutoSense    = tem_nRead;
	}
	else
	{
		m_nAutoSense    = 6;
	}

	::GetPrivateProfileString(_T("AdvanceSet"), _T("NamingMode"), _T("没有找到NamingMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
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
		::GetPrivateProfileString(_T("AdvanceSet"), _T("PreName"), _T("没有找到PreName信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		m_strPreName     = tem_strRead;
		break;
	default:
		m_nNamingMode    = 0;
		break;
	}

	::GetPrivateProfileString(_T("Resource"), _T("curdirectory"), _T("没有找到curdirectory信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strDefaultPath    = tem_strRead;

	//判断文件夹是否存在
	CFileFind    tem_fFileFind;
	if (!tem_fFileFind.FindFile(m_strDefaultPath))
	{
		CreateDirectory(m_strDefaultPath, NULL);
	}
	m_strDefaultPath.ReleaseBuffer();
	m_strShowPath = m_strDefaultPath;
	m_strDefaultPath += "\\";

	::GetPrivateProfileString(_T("AdvanceSet"), _T("HTTP"), _T("没有找到HTTP信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strHttp         = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("AdvanceSet"), _T("FTP"), _T("没有找到FTP信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strFtpIP       = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("AdvanceSet"), _T("FtpDir"), _T("没有找到FTP信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strFtpDir      = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("AdvanceSet"), _T("FtpUserName"), _T("没有找到FTP信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strFtpUserName = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("AdvanceSet"), _T("FtpPassWord"), _T("没有找到FTP信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strFtpPassWord       = tem_strRead;
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("AdvanceSet"), _T("FtpPort"), _T("没有找到FTP信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_strFtpPort          = tem_strRead;
	tem_strRead.ReleaseBuffer();


	//其他设置----------------------------------------------
	::GetPrivateProfileString(_T("OtherSet"), _T("ThumbWidth"), _T("没有找到ThumbWidth信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	if (tem_nRead>0 && tem_nRead<=500)
	{
		m_nThumbWidth = tem_nRead;
	}
	else
	{
		m_nThumbWidth = 220;
	}

	::GetPrivateProfileString(_T("OtherSet"), _T("ThumbHeight"), _T("没有找到ThumbHeight信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	if (tem_nRead>0 && tem_nRead<=700)
	{
		m_nThumbHeight = tem_nRead;
	} 
	else
	{
		m_nThumbHeight = 160;
	}
	::GetPrivateProfileString(_T("OtherSet"), _T("SoundOpen"), _T("没有找到SoundOpen信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_nRead = _ttoi(tem_strRead);
	if (tem_nRead==1)
	{
		m_BSoundOpen = TRUE;
	} 
	else
	{
		m_BSoundOpen = FALSE;
	}

	::GetPrivateProfileString(_T("Resource"), _T("AutoRotateMode"), _T("没有找到AutoRotateMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	m_nAutoRotateMode = _ttoi(tem_strRead);

}


void CUDSSmartCamerav100Dlg::OnSelchangeTabSet(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
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

//退出按钮
void CUDSSmartCamerav100Dlg::OnBnClickedBtnTest2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString    tem_strCamera = _T("1");
	m_conVideoOcx.StopRun();
	m_conVideoOcx.Uninitial();
	//删除缓存buffer
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


	//向资管管理器发送消息，更新视图显示
	CString   tem_str   = _T("1");
//	HWND      tem_hWnd = ::FindWindow(_T("MyResourceManagement"), NULL);   //无标题窗口
	HWND      tem_hWnd = ::FindWindow(NULL, _T("紫图SmartScan影像平台系统v1.8"));   //标题窗口
	if (tem_hWnd != NULL)
	{
		::SendMessage(tem_hWnd, WM_SETTEXT, 0, (LPARAM)tem_str.GetBuffer(tem_str.GetLength()));
	}
	CDialogEx::OnOK();
}


afx_msg LRESULT CUDSSmartCamerav100Dlg::OnSwitchItem(WPARAM wParam, LPARAM lParam)
{
	int   tem_nSelect    = (int)wParam;     //本次选择的设备，判断是否跟正在使用的相同
	int   tem_nOperation = (int)lParam;     //操作索引码
	long tem_lExmin = 0, tem_lExmax = 0, tem_lAutoExp = 0, tem_lValue = 0;   //设置曝光相关项
	long tem_lExp   = 0, tem_lBrg   = 0; //手动曝光值
	CString   tem_strVideoName;    //用于保存视频名
	CString   tem_strWholeName;
	BOOL      tem_BAutoCrop;      //用于记录录制前后自动裁切状态
	CString   tem_strIniInfo;     //用于向ini文件写入信息
    LPCTSTR   tem_lstrVideoPath;  //视频地址
	CString   tem_strCurResolution; //获取当前分辨率，用于设置视频尺寸
	CString   tem_strWH;            //保存从分辨率中拆分出来的宽高
	int       tem_nVedioWidth = 640;  //视频分辨率宽
	int       tem_nVedioHeight= 480;  //视频分辨率高
	int       tem_nSite;            //视频分辨率拆分
	int n=-1;
	int tem_ndpi=0;

	switch(tem_nOperation)
	{
	case 0:
		if (m_nLastUsedScanner != tem_nSelect)
		{
			//判断该副头是否打开
			if (m_nLastSubScan == tem_nSelect)
			{
				m_iChildNor.m_conComScanner.SetCurSel(m_nLastUsedScanner);
				MessageBox(_T("该设备已打开！"), _T("紫图UDS"), MB_OK);
				return 0;
			}

			//重新选择设备并打开
			m_conVideoOcx.StopRun();
			m_nLastUsedScanner = tem_nSelect;
			m_nMainOpen = m_conVideoOcx.StartRun(m_nLastUsedScanner);
			//将切换后的副头写入ini文件
			tem_strIniInfo.Format(_T("%d"), m_nLastUsedScanner);
			::WritePrivateProfileString(_T("ParentCamera"), _T("LastUsed"), tem_strIniInfo, m_strIniPath); 

			//切换后考虑分辨率、自动裁切、自动曝光问题
			m_iChildNor.m_conComReso.ResetContent();

			//判断是否为800W设备
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
			
			
			//设备打开成功，首先获取设备PID_VID
			tem_strPIDVID = m_conVideoOcx.GetDevDisplayName(m_nLastUsedScanner);
			tem_strPIDVID.MakeUpper();
			//检查该PID_VID是否为指定的设备
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
				//该设备为指定设备，添加指定分辨率
				m_BCamera800 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("3664×2744");
				m_iChildNor.m_conComReso.InsertString(-1, tem_strResolution);

				//如果设置当前分辨率索引大于总个数，说明该分辨率为插值分辨率，应设置为硬件最大分辨率
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
				//该设备为指定设备，添加指定分辨率
				m_BCamera500 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("3644*2744");
				m_iChildNor.m_conComReso.InsertString(m_nInterpolateReso, tem_strResolution);

				//如果设置当前分辨率索引大于总个数，说明该分辨率为插值分辨率，应设置为硬件最大分辨率
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
				//该设备为指定设备，添加指定分辨率
				m_BCamera1200 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("4680×3510");
				m_iChildNor.m_conComReso.InsertString(m_nInterpolateReso, tem_strResolution);

				//如果设置当前分辨率索引大于总个数，说明该分辨率为插值分辨率，应设置为硬件最大分辨率
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
				//该设备为指定设备，添加指定分辨率
				m_BCamera1300 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("4680×3360");
				m_iChildNor.m_conComReso.InsertString(m_nInterpolateReso, tem_strResolution);

				//如果设置当前分辨率索引大于总个数，说明该分辨率为插值分辨率，应设置为硬件最大分辨率
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
				//该设备为指定设备，添加指定分辨率
				m_BCameraTo1500 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("4480×3360");
				m_iChildNor.m_conComReso.InsertString(m_nInterpolateReso, tem_strResolution);

				//如果设置当前分辨率索引大于总个数，说明该分辨率为插值分辨率，应设置为硬件最大分辨率
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
				//该设备为指定设备，添加指定分辨率
				m_BGS1600 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("4928×3264");
				m_iChildNor.m_conComReso.InsertString(m_nInterpolateReso, tem_strResolution);

				//如果设置当前分辨率索引大于总个数，说明该分辨率为插值分辨率，应设置为硬件最大分辨率
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
				//该设备为指定设备，添加指定分辨率
				m_BGS1600 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("4928×3264");
				m_iChildNor.m_conComReso.InsertString(m_nInterpolateReso, tem_strResolution);

				//如果设置当前分辨率索引大于总个数，说明该分辨率为插值分辨率，应设置为硬件最大分辨率
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
				//该设备为指定设备，添加指定分辨率
				m_BCamera200 = TRUE;
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
				m_nInterpolateReso   = tem_nResCount;
				for (int i=0; i<tem_nResCount; i++)
				{

					tem_strResolution = m_conVideoOcx.GetResolution(i);
					m_iChildNor.m_conComReso.InsertString(i, tem_strResolution);
				}
				tem_strResolution = _T("2048×1536");
				m_iChildNor.m_conComReso.InsertString(m_nInterpolateReso, tem_strResolution);

				//如果设置当前分辨率索引大于总个数，说明该分辨率为插值分辨率，应设置为硬件最大分辨率
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
				int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
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
			//自动裁切保持不变
			m_conVideoOcx.AdjuestImageCrop(m_BAutoCrop);
			m_conVideoOcx.ManualImageCrop(m_BManualCrop);
			//自动曝光以及手动曝光值
			if (m_BAutoExp)
			{
				m_conVideoOcx.SetAutoExposure(TRUE);
				m_iChildNor.m_conSlidExpos.EnableWindow(FALSE);
			}
			else
			{
				m_conVideoOcx.SetAutoExposure(FALSE);
				m_lReturnCode = m_conVideoOcx.GetExposureRange(&tem_lExmin, &tem_lExmax);
				m_iChildNor.m_conSlidExpos.SetRange(tem_lExmin, tem_lExmax); //设置slider范围
				m_iChildNor.m_conSlidExpos.SetPageSize(1);
				m_conVideoOcx.GetExposure(&tem_lValue, &tem_lAutoExp);
				UpdateData(FALSE);
				if (m_nManualVaule>= tem_lExmin && m_nManualVaule<=tem_lExmax)
				{
					m_iChildNor.m_conSlidExpos.SetPos(m_nManualVaule);       //设置slider当前值
					m_iChildNor.m_conStaExp = m_nManualVaule;                //设置slider显示当前值
					m_iChildNor.m_conStaExpStr.Format(_T("%d"), m_nManualVaule);
					m_conVideoOcx.SetExposure(m_nManualVaule, FALSE);
				} 
				else
				{
					m_iChildNor.m_conSlidExpos.SetPos(tem_lValue);       //设置slider当前值
					m_iChildNor.m_conStaExp = tem_lValue;                //设置slider显示当前值
					m_iChildNor.m_conStaExpStr.Format(_T("%d"), m_iChildNor.m_conStaExp);
					m_nManualVaule = tem_lValue;
					m_conVideoOcx.SetExposure(m_nManualVaule, FALSE);
				}
				m_iChildNor.m_conSlidExpos.EnableWindow(TRUE);	
			}
			//更新手动亮度值
			Self_SetBriValue();
//			m_conVideoOcx.SetBrightness(m_nBriValue, FALSE);
		}
		break;
	case 1:
		if (m_nLastUsedResolu != tem_nSelect)
		{
			if (m_BCamera800)
			{
				//800W设备
				m_nLastUsedResolu = tem_nSelect;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//此时为插值分辨率，设置为最大分辨率
					int  tem_nMaxIndex = GetmaxResoindex();
					m_conVideoOcx.SetResolution(tem_nMaxIndex);
					
				}
				else
				{
					m_conVideoOcx.SetResolution(tem_nSelect);
				}
				//将选择的分辨率写入ini配置文件
				tem_strIniInfo.Format(_T("%d"), tem_nSelect);
				::WritePrivateProfileString(_T("ParentCamera"), _T("Resolution"), tem_strIniInfo, m_strIniPath); 
			}
			else if (m_BCamera500)
			{
				//500W设备
				m_nLastUsedResolu = tem_nSelect;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//此时为插值分辨率，设置为最大分辨率
					int  tem_nMaxIndex = GetmaxResoindex();
					m_conVideoOcx.SetResolution(tem_nMaxIndex);

				}
				else
				{
					m_conVideoOcx.SetResolution(tem_nSelect);
				}
				//将选择的分辨率写入ini配置文件
				tem_strIniInfo.Format(_T("%d"), tem_nSelect);
				::WritePrivateProfileString(_T("ParentCamera"), _T("Resolution"), tem_strIniInfo, m_strIniPath); 
			}
			else if (m_BCamera1200)
			{
				//1000W设备
				m_nLastUsedResolu = tem_nSelect;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//此时为插值分辨率，设置为最大分辨率
					int  tem_nMaxIndex = GetmaxResoindex();
					m_conVideoOcx.SetResolution(tem_nMaxIndex);

				}
				else
				{
					m_conVideoOcx.SetResolution(tem_nSelect);
				}
				//将选择的分辨率写入ini配置文件
				tem_strIniInfo.Format(_T("%d"), tem_nSelect);
				::WritePrivateProfileString(_T("ParentCamera"), _T("Resolution"), tem_strIniInfo, m_strIniPath); 
			}
			else if (m_BCamera1300)
			{
				//1300W设备
				m_nLastUsedResolu = tem_nSelect;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//此时为插值分辨率，设置为最大分辨率
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
				//将选择的分辨率写入ini配置文件
				tem_strIniInfo.Format(_T("%d"), tem_nSelect);
				::WritePrivateProfileString(_T("ParentCamera"), _T("Resolution"), tem_strIniInfo, m_strIniPath); 
			}
			else if (m_BCameraTo1500)
			{
				//1200W设备
				m_nLastUsedResolu = tem_nSelect;
				if (m_nLastUsedResolu == m_nInterpolateReso)
				{
					//此时为插值分辨率，设置为最大分辨率
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
				//将选择的分辨率写入ini配置文件
				tem_strIniInfo.Format(_T("%d"), tem_nSelect);
				::WritePrivateProfileString(_T("ParentCamera"), _T("Resolution"), tem_strIniInfo, m_strIniPath); 
			}
			else if (m_BGS1600)
			{
				//1300W->1600W设备
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
				//将选择的分辨率写入ini配置文件
				tem_strIniInfo.Format(_T("%d"), tem_nSelect);
				::WritePrivateProfileString(_T("ParentCamera"), _T("Resolution"), tem_strIniInfo, m_strIniPath); 
			}
			else if (m_BCamera200)
			{
				//200W->300W设备
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
				//将选择的分辨率写入ini配置文件
				tem_strIniInfo.Format(_T("%d"), tem_nSelect);
				::WritePrivateProfileString(_T("ParentCamera"), _T("Resolution"), tem_strIniInfo, m_strIniPath); 
			}
			else
			{
				//普通设备
				m_nLastUsedResolu = tem_nSelect;
				m_conVideoOcx.SetResolution(tem_nSelect);
				//将选择的分辨率写入ini配置文件
				tem_strIniInfo.Format(_T("%d"), tem_nSelect);
				::WritePrivateProfileString(_T("ParentCamera"), _T("Resolution"), tem_strIniInfo, m_strIniPath); 

			}
			tem_ndpi = m_conVideoOcx.GetImageDPI();
		}	
		
		break;
	case 2:
		//选择主头拍照格式
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
			//base64文件名问题
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

		//将选择的文件格式写入ini配置文件
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
		//将选择的色彩模式写入ini配置文件
		tem_strIniInfo.Format(_T("%d"), tem_nSelect);
		::WritePrivateProfileString(_T("ParentCamera"), _T("ColorMode"), tem_strIniInfo, m_strIniPath); 
		break;
	case 4:
		m_BAutoCrop   = tem_nSelect;
		m_BManualCrop = !tem_nSelect;
		if (tem_nSelect == 1)
		{
			//开启自动裁切
			m_conVideoOcx.ManualImageCrop(FALSE);
			m_conVideoOcx.AdjuestImageCrop(TRUE);
		} 
		else
		{
			//开启手动裁切
			m_conVideoOcx.AdjuestImageCrop(FALSE);
			m_conVideoOcx.ManualImageCrop(TRUE);
			m_conVideoOcx.SetMessage(1);
		}
		

		//将选择的自动裁切写入ini配置文件
		tem_strIniInfo.Format(_T("%d"), tem_nSelect);
		::WritePrivateProfileString(_T("ParentCamera"), _T("AutoCrop"), tem_strIniInfo, m_strIniPath); 
		break;
	case 5:
		m_BAutoExp    = tem_nSelect;	
		if (m_BAutoExp)
		{
			//自动曝光	
			m_lReturnCode = m_conVideoOcx.GetExposureRange(&tem_lExmin, &tem_lExmax);
			m_iChildNor.m_conSlidExpos.SetRange(tem_lExmin, tem_lExmax); //设置slider范围
			m_iChildNor.m_conSlidExpos.SetPageSize(1);
			m_conVideoOcx.GetExposure(&tem_lValue, &tem_lAutoExp);
			UpdateData(TRUE);
			m_iChildNor.m_conSlidExpos.SetPos(tem_lValue);       //设置slider当前值
			m_iChildNor.m_conStaExp = tem_lValue;                //设置slider显示当前值
			m_iChildNor.m_conStaExpStr.Format(_T("%d"), m_iChildNor.m_conStaExp);
			m_iChildNor.m_conSlidExpos.EnableWindow(FALSE);	
			m_conVideoOcx.SetAutoExposure(TRUE);	
			UpdateData(FALSE);
		} 
		else
		{
			//手动曝光
			m_conVideoOcx.SetAutoExposure(FALSE);
			m_lReturnCode = m_conVideoOcx.GetExposureRange(&tem_lExmin, &tem_lExmax);
			m_iChildNor.m_conSlidExpos.SetRange(tem_lExmin, tem_lExmax); //设置slider范围
			m_iChildNor.m_conSlidExpos.SetPageSize(1);
			m_conVideoOcx.GetExposure(&tem_lValue, &tem_lAutoExp);
// 			UpdateData(FALSE);
// 			m_iChildNor.m_conSlidExpos.SetPos(tem_lValue);       //设置slider当前值
// 			m_iChildNor.m_conStaExp = tem_lValue;                //设置slider显示当前值

			m_nManualVaule = tem_lValue;
			m_conVideoOcx.SetExposure(m_nManualVaule, FALSE);

			m_iChildNor.m_conSlidExpos.EnableWindow(TRUE);	
			tem_strIniInfo.Format(_T("%d"), tem_nSelect);
			::WritePrivateProfileString(_T("ParentCamera"), _T("ExpValue"), tem_strIniInfo, m_strIniPath);
		}

		//将选择的自动曝光写入ini配置文件
		tem_strIniInfo.Format(_T("%d"), tem_nSelect);
		::WritePrivateProfileString(_T("ParentCamera"), _T("AutoExp"), tem_strIniInfo, m_strIniPath);
		
		break;
	case 6:
		//设置手动曝光值
		tem_lExp = tem_nSelect;
		m_conVideoOcx.SetExposure(tem_lExp, FALSE);  
		tem_strIniInfo.Format(_T("%d"), tem_lExp);
		::WritePrivateProfileString(_T("ParentCamera"), _T("ExpValue"), tem_strIniInfo, m_strIniPath);
		break;
	case 7:
		m_BParentVideo = TRUE;
		//默认使用主头作为录制视频头
		//录制前关闭自动裁切，录制后绘制裁切原来状态
		tem_BAutoCrop = m_BAutoCrop;
		m_conVideoOcx.AdjuestImageCrop(FALSE);
		//		tem_strVideoName.Format(_T("%d"), m_nImageCount);
		tem_strVideoName = NamingFile(m_nNamingMode);
//		tem_strVideoName += ".mp4";
		tem_strVideoName += m_strVideoFormat;
		tem_strWholeName = m_strDefaultPath + tem_strVideoName;
		//增加宽高----------------------------------------------------------------
		m_iChildNor.m_conComReso.GetWindowText(tem_strCurResolution);
		tem_nSite = tem_strCurResolution.Find(_T("*"));
		tem_strWH = tem_strCurResolution.Mid(0, tem_nSite);
		tem_nVedioWidth = _ttoi(tem_strWH);
		tem_strWH = tem_strCurResolution.Mid(tem_nSite+1);
		tem_nVedioHeight = _ttoi(tem_strWH);


		//更新音频是设备索引
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
		//判断副头是否打开，若副头没有打开默认主头录像
		if (m_nLastSubScan == -1)
		{
			m_BParentVideo = TRUE;
			//默认使用主头作为录制视频头
			//录制前关闭自动裁切，录制后绘制裁切原来状态
			tem_BAutoCrop = m_BAutoCrop;
			m_conVideoOcx.AdjuestImageCrop(FALSE);
			//		tem_strVideoName.Format(_T("%d"), m_nImageCount);
			tem_strVideoName = NamingFile(m_nNamingMode);
			tem_strVideoName += ".mp4";
			tem_strWholeName = m_strDefaultPath + tem_strVideoName;
			//增加宽高----------------------------------------------------------------
			m_conVideoOcx.StartRecord(m_nLastUsedScanner, tem_strWholeName, m_nVideoWidth, m_nVideoHeight, m_nVideoBit, m_nVideoFPS);
			m_strVideoPath = tem_strWholeName;
			m_iChildNor.SetTimer(1, 10, NULL);
			m_nImageCount++;
		}
		else
		{
			m_BParentVideo = FALSE;
			//副头已打开，通过弹窗选择主副头录像
			tem_strVideoName = NamingFile(m_nNamingMode);
			tem_strVideoName += ".mp4";
			tem_strWholeName = m_strDefaultPath + tem_strVideoName;
			//增加宽高----------------------------------------------------------------
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

		m_iChildNor.m_conRichEdit.SetSelectionCharFormat(m_iChildNor.tem_fontRichEdit);  //先设置格式	
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
		//停止录像后恢复拍摄界面
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
		//设置手动亮度值
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


//拍照
void CUDSSmartCamerav100Dlg::OnBnClickedBtnCapature()
{
	// TODO: 在此添加控件通知处理程序代码	
	CString   tem_strName;         //无后缀
	CString   tem_strFileName;     //带后缀
	CString   tem_strWholeName;    //带路径,图像文件
	CString   tem_strPDFimgName;   //带路径，所有文件
	CString   tem_strTXTimgName;
	CString   tem_strThumbPath;    //缩略图路径
	CString   tem_strSrcImageName; //插值原图
	CString   tem_strSrcImagePDF;  //PDF原图

	CString   tem_strThumFile;     //自动旋转算法2缩略图
	
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
	*           函数结构
	* PDF拍照-------插值设备
	*        -------普通设备
	*
	*base64拍照----插值设备
	*        ------普通设备
	*
	*DCM拍照-------插值设备
	*        ------普通设备
	*
	*OFD拍照-------插值设备
	*        ------普通设备
	*普通拍照------插值设备
	*        ------普通设备
	*
	***********************************/

	if (m_BPDFCpt)
	{
		
		if (m_BCamera800 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//800W设备
			//tem_strFileName为pdf文件名+后缀
			//获取原图像名、插值图像名、输出PDF名
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //拍照图像以及路径
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}
			
			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 0);
			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath2, tem_strName);    //保存缩略图
			tem_strWholeName = GeneratePDF(tem_strPDFImgPath2, tem_strWholeName);


			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);
			
			DeleteFile(tem_strPDFImgPath1);
			DeleteFile(tem_strPDFImgPath2);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			//普通拍照转换为PDF文件

		}
		else if (m_BCamera500 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//500W设备
			//tem_strFileName为pdf文件名+后缀
			//获取原图像名、插值图像名、输出PDF名
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //拍照图像以及路径
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}
			
			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 3);
			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath2, tem_strName);    //保存缩略图
			tem_strWholeName = GeneratePDF(tem_strPDFImgPath2, tem_strWholeName);


			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);
			DeleteFile(tem_strPDFImgPath2);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			//普通拍照转换为PDF文件
		}
		else if (m_BCamera1200 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1200W设备
			//tem_strFileName为pdf文件名+后缀
			//获取原图像名、插值图像名、输出PDF名
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //拍照图像以及路径
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 1);
			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath2, tem_strName);    //保存缩略图
			tem_strWholeName = GeneratePDF(tem_strPDFImgPath2, tem_strWholeName);


			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);
			DeleteFile(tem_strPDFImgPath2);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			//普通拍照转换为PDF文件
		}
		else if (m_BCamera1300 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1300W设备
			//tem_strFileName为pdf文件名+后缀
			//获取原图像名、插值图像名、输出PDF名
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //拍照图像以及路径
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 2);
			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath2, tem_strName);    //保存缩略图
			tem_strWholeName = GeneratePDF(tem_strPDFImgPath2, tem_strWholeName);


			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);
			DeleteFile(tem_strPDFImgPath2);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			//普通拍照转换为PDF文件
		}
		else if (m_BCameraTo1500 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1200W设备
			//tem_strFileName为pdf文件名+后缀
			//获取原图像名、插值图像名、输出PDF名
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //拍照图像以及路径
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath1, tem_strName);    //保存缩略图
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
			//1300W->1600W设备
			//tem_strFileName为pdf文件名+后缀
			//获取原图像名、插值图像名、输出PDF名
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //拍照图像以及路径
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath1, tem_strName);    //保存缩略图
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
			//200W->300W设备
			//tem_strFileName为pdf文件名+后缀
			//获取原图像名、插值图像名、输出PDF名
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //拍照图像以及路径
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath1, tem_strName);    //保存缩略图
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
			//普通设备
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");                  //缓存图像全名

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //拍照图像以及路径

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath1, tem_strName);    //保存缩略图
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath); 
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			tem_strWholeName = GeneratePDF(tem_strPDFImgPath1, tem_strWholeName);

			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);


			/*2018-04-12原代码插值使用拍摄图像->PDF,非插值则使用OCX拍摄PDF。但是无法自动旋转，因此统一修改为拍摄图像，自己生成PDF
			m_conVideoOcx.CapturePDF(tem_strWholeName);
			tem_strPDFimgName = ShowPDF(tem_strWholeName);    //pdf文件导出的图像文件
			m_vcFileName.push_back(tem_strName);
			tem_strThumbPath = GetThumbPath(tem_strPDFimgName, tem_strName);    //保存缩略图
			m_vcWholeName.push_back(tem_strThumbPath);      //PDF解析出首页，将图像地址存放至该vector
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
			//800W设备
			//原图、插值图、txt文件
			CString   tem_strImgName1 = tem_strName;     //原图像名
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("TXT");       //插值图像名
			tem_strImgName2 += tem_strName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strTXTImgPath1 = m_strBufferPath + tem_strImgName1;    //原图像路径+图像名
			CString   tem_strTXTImgPath2 = m_strBufferPath + tem_strImgName2;    //插值图像路径+图像名

			m_conVideoOcx.CaptureImage(tem_strTXTImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strTXTImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strTXTImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strTXTImgPath2 = InterPolateImage(tem_strTXTImgPath1, tem_strTXTImgPath2, 0);
			tem_strThumbPath = GetThumbPath(tem_strTXTImgPath2, tem_strName);    //保存缩略图
			tem_strWholeName = GenerateBase64(tem_strTXTImgPath2, tem_strWholeName);

			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      //PDF解析出首页，将图像地址存放至该vector
			m_vcBussName.push_back(tem_strWholeName);
			
			DeleteFile(tem_strTXTImgPath1);
			DeleteFile(tem_strTXTImgPath2);

            ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
 			m_nPDfimg++;
		}
		else if (m_BCamera500 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//500W设备
			//原图、插值图、txt文件
			CString   tem_strImgName1 = tem_strName;     //原图像名
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("TXT");       //插值图像名
			tem_strImgName2 += tem_strName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strTXTImgPath1 = m_strBufferPath + tem_strImgName1;    //原图像路径+图像名
			CString   tem_strTXTImgPath2 = m_strBufferPath + tem_strImgName2;    //插值图像路径+图像名

			m_conVideoOcx.CaptureImage(tem_strTXTImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strTXTImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strTXTImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strTXTImgPath2 = InterPolateImage(tem_strTXTImgPath1, tem_strTXTImgPath2, 3);
			tem_strThumbPath = GetThumbPath(tem_strTXTImgPath2, tem_strName);    //保存缩略图
			tem_strWholeName = GenerateBase64(tem_strTXTImgPath2, tem_strWholeName);

			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      //PDF解析出首页，将图像地址存放至该vector
			m_vcBussName.push_back(tem_strWholeName);

			DeleteFile(tem_strTXTImgPath1);
			DeleteFile(tem_strTXTImgPath2);

			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			m_nPDfimg++;
		}
		else if (m_BCamera1200 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1200W设备
			//原图、插值图、txt文件
			CString   tem_strImgName1 = tem_strName;     //原图像名
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("TXT");       //插值图像名
			tem_strImgName2 += tem_strName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strTXTImgPath1 = m_strBufferPath + tem_strImgName1;    //原图像路径+图像名
			CString   tem_strTXTImgPath2 = m_strBufferPath + tem_strImgName2;    //插值图像路径+图像名

			m_conVideoOcx.CaptureImage(tem_strTXTImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strTXTImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strTXTImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strTXTImgPath2 = InterPolateImage(tem_strTXTImgPath1, tem_strTXTImgPath2, 1);
			tem_strThumbPath = GetThumbPath(tem_strTXTImgPath2, tem_strName);    //保存缩略图
			tem_strWholeName = GenerateBase64(tem_strTXTImgPath2, tem_strWholeName);

			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      //PDF解析出首页，将图像地址存放至该vector
			m_vcBussName.push_back(tem_strWholeName);

			DeleteFile(tem_strTXTImgPath1);
			DeleteFile(tem_strTXTImgPath2);

			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			m_nPDfimg++;
		}
		else if (m_BCamera1300 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1300W设备
			//原图、插值图、txt文件
			CString   tem_strImgName1 = tem_strName;     //原图像名
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("TXT");       //插值图像名
			tem_strImgName2 += tem_strName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strTXTImgPath1 = m_strBufferPath + tem_strImgName1;    //原图像路径+图像名
			CString   tem_strTXTImgPath2 = m_strBufferPath + tem_strImgName2;    //插值图像路径+图像名

			m_conVideoOcx.CaptureImage(tem_strTXTImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strTXTImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strTXTImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strTXTImgPath2 = InterPolateImage(tem_strTXTImgPath1, tem_strTXTImgPath2, 2);
			tem_strThumbPath = GetThumbPath(tem_strTXTImgPath2, tem_strName);    //保存缩略图
			tem_strWholeName = GenerateBase64(tem_strTXTImgPath2, tem_strWholeName);

			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      //PDF解析出首页，将图像地址存放至该vector
			m_vcBussName.push_back(tem_strWholeName);

			DeleteFile(tem_strTXTImgPath1);
			DeleteFile(tem_strTXTImgPath2);

			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			m_nPDfimg++;
		}
		else if (m_BCameraTo1500 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1200W设备
			//原图、插值图、txt文件
			CString   tem_strImgName1 = tem_strName;     //原图像名
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("TXT");       //插值图像名
			tem_strImgName2 += tem_strName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strTXTImgPath1 = m_strBufferPath + tem_strImgName1;    //原图像路径+图像名
			CString   tem_strTXTImgPath2 = m_strBufferPath + tem_strImgName2;    //插值图像路径+图像名

			m_conVideoOcx.CaptureImage(tem_strTXTImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strTXTImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strTXTImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strThumbPath = GetThumbPath(tem_strTXTImgPath1, tem_strName);    //保存缩略图
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      //PDF解析出首页，将图像地址存放至该vector
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
			//1300W->1600W设备
			//原图、插值图、txt文件
			CString   tem_strImgName1 = tem_strName;     //原图像名
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("TXT");       //插值图像名
			tem_strImgName2 += tem_strName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strTXTImgPath1 = m_strBufferPath + tem_strImgName1;    //原图像路径+图像名
			CString   tem_strTXTImgPath2 = m_strBufferPath + tem_strImgName2;    //插值图像路径+图像名

			m_conVideoOcx.CaptureImage(tem_strTXTImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strTXTImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strTXTImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strThumbPath = GetThumbPath(tem_strTXTImgPath1, tem_strName);    //保存缩略图
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      //PDF解析出首页，将图像地址存放至该vector
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
			//200W->300W设备
			//原图、插值图、txt文件
			CString   tem_strImgName1 = tem_strName;     //原图像名
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("TXT");       //插值图像名
			tem_strImgName2 += tem_strName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strTXTImgPath1 = m_strBufferPath + tem_strImgName1;    //原图像路径+图像名
			CString   tem_strTXTImgPath2 = m_strBufferPath + tem_strImgName2;    //插值图像路径+图像名

			m_conVideoOcx.CaptureImage(tem_strTXTImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strTXTImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strTXTImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strTXTImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strThumbPath = GetThumbPath(tem_strTXTImgPath1, tem_strName);    //保存缩略图
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      //PDF解析出首页，将图像地址存放至该vector
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
			//Base64函数返回BSTR
			CString  tem_strBaseReturn = m_conVideoOcx.CaptureBase64();
			try
			{
				//设置文件的打开参数
				CStdioFile  tem_sfOutFile(tem_strWholeName, CFile::modeNoTruncate | 
					CFile::modeCreate | CFile::modeWrite | CFile::typeText);
				//文件尾插入新纪录
				tem_sfOutFile.SeekToEnd();
				tem_sfOutFile.WriteString(tem_strBaseReturn);
				tem_sfOutFile.Close();

				//通过txt文件导出图像，添加预览
				tem_strTXTimgName = Base642Img(tem_strWholeName);  //得到图像名

				m_vcFileName.push_back(tem_strName);
				tem_strThumbPath = GetThumbPath(tem_strTXTimgName, tem_strName);    //保存缩略图
				m_vcWholeName.push_back(tem_strThumbPath);      //PDF解析出首页，将图像地址存放至该vector
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
		//弹出对话框，输入DCM信息------
		m_iChildDcm.DoModal();

		//判断是否继续拍照-------------
		if (!m_iChildDcm.m_strDcmInfo.IsEmpty())
		{
			//信息字符串不为空，继续
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

			//DCM名转为JPG名
			tem_strTemporary = tem_strWholeName;  //.dcm
			tem_nSite        = tem_strTemporary.ReverseFind('.');
			tem_strTemporary = tem_strTemporary.Mid(0, tem_nSite);
			tem_strTemporary+= ".jpg";
		//	tem_strTemporary+= ".bmp";


			if (m_BCamera800 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//800W设备
				CString     tem_strSrcImg = m_strBufferPath;
				tem_strSrcImg += tem_strName;                               //原尺寸图像
				tem_strSrcImg += _T(".jpg");	

				m_conVideoOcx.CaptureImage(tem_strSrcImg);             //拍摄原图
				//自动旋转--------------------------------------------
				Self_RecognizeOrit(tem_strSrcImg, m_BAutoRotate);
				//文档优化--------------------------------------------
				if (m_BOptimize)
				{
					CxImage   tem_cxSrcImg;
					tem_cxSrcImg.Load(tem_strSrcImg, CMAX_IMAGE_FORMATS);

					float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


					if (tem_fColorPer>=m_fColorPercentage)
					{
						//彩色图像
						Self_DocOptimize(tem_cxSrcImg, tem_strSrcImg, m_BOptimize, m_nOptBright, m_nOptContrast);
					} 
					else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
					{
						//黑白图像
						Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImg, m_BOptimize);
					}
					//否则为二值图像，不做优化
				}

				tem_strTemporary = InterPolateImage(tem_strSrcImg, tem_strTemporary, 0);
				m_vcFileName.push_back(tem_strName);
				tem_strThumbPath = GetThumbPath(tem_strTemporary, tem_strName);    //保存缩略图
				m_vcWholeName.push_back(tem_strThumbPath);                         //显示缩略图
				m_vcDeleteBuffer.push_back(tem_strTemporary);

				DeleteFile(tem_strSrcImg);

			}
			else if (m_BCamera500 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//500W设备
				CString     tem_strSrcImg = m_strBufferPath;
				tem_strSrcImg += tem_strName;                               //原尺寸图像
				tem_strSrcImg += _T(".jpg");	

				m_conVideoOcx.CaptureImage(tem_strSrcImg);             //拍摄原图
				//自动旋转--------------------------------------------
				Self_RecognizeOrit(tem_strSrcImg, m_BAutoRotate);
				//文档优化--------------------------------------------
				if (m_BOptimize)
				{
					CxImage   tem_cxSrcImg;
					tem_cxSrcImg.Load(tem_strSrcImg, CMAX_IMAGE_FORMATS);

					float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


					if (tem_fColorPer>=m_fColorPercentage)
					{
						//彩色图像
						Self_DocOptimize(tem_cxSrcImg, tem_strSrcImg, m_BOptimize, m_nOptBright, m_nOptContrast);
					} 
					else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
					{
						//黑白图像
						Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImg, m_BOptimize);
					}
					//否则为二值图像，不做优化
				}

				tem_strTemporary = InterPolateImage(tem_strSrcImg, tem_strTemporary, 3);
				m_vcFileName.push_back(tem_strName);
				tem_strThumbPath = GetThumbPath(tem_strTemporary, tem_strName);    //保存缩略图
				m_vcWholeName.push_back(tem_strThumbPath);                         //显示缩略图
				m_vcDeleteBuffer.push_back(tem_strTemporary);

				DeleteFile(tem_strSrcImg);

			}
			else if (m_BCamera1200 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1200W设备
				CString     tem_strSrcImg = m_strBufferPath;
				tem_strSrcImg += tem_strName;                               //原尺寸图像
				tem_strSrcImg += _T(".jpg");	

				m_conVideoOcx.CaptureImage(tem_strSrcImg);             //拍摄原图
				//自动旋转--------------------------------------------
				Self_RecognizeOrit(tem_strSrcImg, m_BAutoRotate);
				//文档优化--------------------------------------------
				if (m_BOptimize)
				{
					CxImage   tem_cxSrcImg;
					tem_cxSrcImg.Load(tem_strSrcImg, CMAX_IMAGE_FORMATS);

					float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


					if (tem_fColorPer>=m_fColorPercentage)
					{
						//彩色图像
						Self_DocOptimize(tem_cxSrcImg, tem_strSrcImg, m_BOptimize, m_nOptBright, m_nOptContrast);
					} 
					else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
					{
						//黑白图像
						Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImg, m_BOptimize);
					}
					//否则为二值图像，不做优化
				}

				tem_strTemporary = InterPolateImage(tem_strSrcImg, tem_strTemporary, 1);
				m_vcFileName.push_back(tem_strName);
				tem_strThumbPath = GetThumbPath(tem_strTemporary, tem_strName);    //保存缩略图
				m_vcWholeName.push_back(tem_strThumbPath);                         //显示缩略图
				m_vcDeleteBuffer.push_back(tem_strTemporary);

				DeleteFile(tem_strSrcImg);

			}
			else if (m_BCamera1300 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1300W设备
				CString     tem_strSrcImg = m_strBufferPath;
				tem_strSrcImg += tem_strName;                               //原尺寸图像
				tem_strSrcImg += _T(".jpg");	

				m_conVideoOcx.CaptureImage(tem_strSrcImg);             //拍摄原图
				//自动旋转--------------------------------------------
				Self_RecognizeOrit(tem_strSrcImg, m_BAutoRotate);
				//文档优化--------------------------------------------
				if (m_BOptimize)
				{
					CxImage   tem_cxSrcImg;
					tem_cxSrcImg.Load(tem_strSrcImg, CMAX_IMAGE_FORMATS);

					float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


					if (tem_fColorPer>=m_fColorPercentage)
					{
						//彩色图像
						Self_DocOptimize(tem_cxSrcImg, tem_strSrcImg, m_BOptimize, m_nOptBright, m_nOptContrast);
					} 
					else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
					{
						//黑白图像
						Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImg, m_BOptimize);
					}
					//否则为二值图像，不做优化
				}

				tem_strThumbPath = GetThumbPath(tem_strSrcImg, tem_strName);    //保存缩略图
				tem_strTemporary = InterPolateImage(tem_strSrcImg, tem_strTemporary, 2);
				m_vcFileName.push_back(tem_strName);
				
				m_vcWholeName.push_back(tem_strThumbPath);                         //显示缩略图
				m_vcDeleteBuffer.push_back(tem_strTemporary);

				DeleteFile(tem_strSrcImg);

			}
			else if (m_BCameraTo1500 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1200W设备
				CString     tem_strSrcImg = m_strBufferPath;
				tem_strSrcImg += tem_strName;                               //原尺寸图像
				tem_strSrcImg += _T(".jpg");	

				m_conVideoOcx.CaptureImage(tem_strSrcImg);             //拍摄原图
				//自动旋转--------------------------------------------
				Self_RecognizeOrit(tem_strSrcImg, m_BAutoRotate);
				//文档优化--------------------------------------------
				if (m_BOptimize)
				{
					CxImage   tem_cxSrcImg;
					tem_cxSrcImg.Load(tem_strSrcImg, CMAX_IMAGE_FORMATS);

					float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


					if (tem_fColorPer>=m_fColorPercentage)
					{
						//彩色图像
						Self_DocOptimize(tem_cxSrcImg, tem_strSrcImg, m_BOptimize, m_nOptBright, m_nOptContrast);
					} 
					else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
					{
						//黑白图像
						Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImg, m_BOptimize);
					}
					//否则为二值图像，不做优化
				}

				m_vcFileName.push_back(tem_strName);
				tem_strThumbPath = GetThumbPath(tem_strSrcImg, tem_strName);    //保存缩略图
				tem_strTemporary = InterPolateImage(tem_strSrcImg, tem_strTemporary, 4);
				m_vcWholeName.push_back(tem_strThumbPath);                         //显示缩略图
				m_vcDeleteBuffer.push_back(tem_strTemporary);
				DeleteFile(tem_strSrcImg);
			}
			else if (m_BGS1600 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1300W->1600W设备
				CString     tem_strSrcImg = m_strBufferPath;
				tem_strSrcImg += tem_strName;                               //原尺寸图像
				tem_strSrcImg += _T(".jpg");	

				m_conVideoOcx.CaptureImage(tem_strSrcImg);             //拍摄原图
				//自动旋转--------------------------------------------
				Self_RecognizeOrit(tem_strSrcImg, m_BAutoRotate);
				//文档优化--------------------------------------------
				if (m_BOptimize)
				{
					CxImage   tem_cxSrcImg;
					tem_cxSrcImg.Load(tem_strSrcImg, CMAX_IMAGE_FORMATS);

					float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


					if (tem_fColorPer>=m_fColorPercentage)
					{
						//彩色图像
						Self_DocOptimize(tem_cxSrcImg, tem_strSrcImg, m_BOptimize, m_nOptBright, m_nOptContrast);
					} 
					else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
					{
						//黑白图像
						Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImg, m_BOptimize);
					}
					//否则为二值图像，不做优化
				}

				m_vcFileName.push_back(tem_strName);
				tem_strThumbPath = GetThumbPath(tem_strSrcImg, tem_strName);    //保存缩略图
				tem_strTemporary = InterPolateImage(tem_strSrcImg, tem_strTemporary, 5);
				m_vcWholeName.push_back(tem_strThumbPath);                         //显示缩略图
				m_vcDeleteBuffer.push_back(tem_strTemporary);
				DeleteFile(tem_strSrcImg);
			}
			else if (m_BCamera200 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//200W->300W设备
				CString     tem_strSrcImg = m_strBufferPath;
				tem_strSrcImg += tem_strName;                               //原尺寸图像
				tem_strSrcImg += _T(".jpg");	

				m_conVideoOcx.CaptureImage(tem_strSrcImg);             //拍摄原图
				//自动旋转--------------------------------------------
				Self_RecognizeOrit(tem_strSrcImg, m_BAutoRotate);
				//文档优化--------------------------------------------
				if (m_BOptimize)
				{
					CxImage   tem_cxSrcImg;
					tem_cxSrcImg.Load(tem_strSrcImg, CMAX_IMAGE_FORMATS);

					float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


					if (tem_fColorPer>=m_fColorPercentage)
					{
						//彩色图像
						Self_DocOptimize(tem_cxSrcImg, tem_strSrcImg, m_BOptimize, m_nOptBright, m_nOptContrast);
					} 
					else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
					{
						//黑白图像
						Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImg, m_BOptimize);
					}
					//否则为二值图像，不做优化
				}

				m_vcFileName.push_back(tem_strName);
				tem_strThumbPath = GetThumbPath(tem_strSrcImg, tem_strName);    //保存缩略图
				tem_strTemporary = InterPolateImage(tem_strSrcImg, tem_strTemporary, 6);
				m_vcWholeName.push_back(tem_strThumbPath);                         //显示缩略图
				m_vcDeleteBuffer.push_back(tem_strTemporary);
				DeleteFile(tem_strSrcImg);
			}
			else
			{
				//拍摄bmp图像--------------
				m_conVideoOcx.CaptureImage(tem_strTemporary);
				//自动旋转--------------------------------------------
				Self_RecognizeOrit(tem_strTemporary, m_BAutoRotate);
				//文档优化--------------------------------------------
				if (m_BOptimize)
				{
					CxImage   tem_cxSrcImg;
					tem_cxSrcImg.Load(tem_strTemporary, CMAX_IMAGE_FORMATS);

					float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


					if (tem_fColorPer>=m_fColorPercentage)
					{
						//彩色图像
						Self_DocOptimize(tem_cxSrcImg, tem_strTemporary, m_BOptimize, m_nOptBright, m_nOptContrast);
					} 
					else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
					{
						//黑白图像
						Self_DocOptimize2(tem_cxSrcImg, tem_strTemporary, m_BOptimize);
					}
					//否则为二值图像，不做优化
				}

				m_vcFileName.push_back(tem_strName);
				tem_strThumbPath = GetThumbPath(tem_strTemporary, tem_strName);    //保存缩略图
				m_vcWholeName.push_back(tem_strThumbPath);                         //显示缩略图
				m_vcDeleteBuffer.push_back(tem_strTemporary);
			}
			


			//转JPG图像为DCM图像--------
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
			//信息字符串为空，取消拍照
			return;
		}
	}
	else if (m_BOfdCpt)
	{
		if (m_BCamera800 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//800W设备
			//tem_strFileName为pdf文件名+后缀
			//获取原图像名、插值图像名、输出PDF名
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //拍照图像以及路径
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}
			
			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 0);
			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath2, tem_strName);    //保存缩略图
			tem_strWholeName = GenerateOFD(tem_strPDFImgPath2, tem_strWholeName); 


			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);
			
			DeleteFile(tem_strPDFImgPath1);
//			DeleteFile(tem_strPDFImgPath2);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			//普通拍照转换为PDF文件

		}
		else if (m_BCamera500 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//500W设备
			//tem_strFileName为pdf文件名+后缀
			//获取原图像名、插值图像名、输出PDF名
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //拍照图像以及路径
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}
			
			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 3);
			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath2, tem_strName);    //保存缩略图
			tem_strWholeName = GenerateOFD(tem_strPDFImgPath2, tem_strWholeName);


			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);
//			DeleteFile(tem_strPDFImgPath2);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			//普通拍照转换为PDF文件
		}
		else if (m_BCamera1200 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1200W设备
			//tem_strFileName为pdf文件名+后缀
			//获取原图像名、插值图像名、输出PDF名
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //拍照图像以及路径
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 1);
			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath2, tem_strName);    //保存缩略图
			tem_strWholeName = GenerateOFD(tem_strPDFImgPath2, tem_strWholeName);


			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);
//			DeleteFile(tem_strPDFImgPath2);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			//普通拍照转换为PDF文件
		}
		else if (m_BCamera1300 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1300W设备
			//tem_strFileName为pdf文件名+后缀
			//获取原图像名、插值图像名、输出PDF名
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //拍照图像以及路径
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strPDFImgPath2 = InterPolateImage(tem_strPDFImgPath1, tem_strPDFImgPath2, 2);
			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath2, tem_strName);    //保存缩略图
			tem_strWholeName = GenerateOFD(tem_strPDFImgPath2, tem_strWholeName);


			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);      
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

			DeleteFile(tem_strPDFImgPath1);
//			DeleteFile(tem_strPDFImgPath2);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			//普通拍照转换为PDF文件
		}
		else if (m_BCameraTo1500 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1200W设备
			//tem_strFileName为pdf文件名+后缀
			//获取原图像名、插值图像名、输出PDF名
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //拍照图像以及路径
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath1, tem_strName);    //保存缩略图
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
			//1300W->1600W设备
			//tem_strFileName为pdf文件名+后缀
			//获取原图像名、插值图像名、输出PDF名
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //拍照图像以及路径
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath1, tem_strName);    //保存缩略图
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
			//200W->300W设备
			//tem_strFileName为pdf文件名+后缀
			//获取原图像名、插值图像名、输出PDF名
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");
			CString   tem_strImgName2 = _T("PDF");
			tem_strImgName2 += tem_strPDFPreName;
			tem_strImgName2 += _T(".jpg");

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //拍照图像以及路径
			CString   tem_strPDFImgPath2 = m_strBufferPath + tem_strImgName2;

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath1, tem_strName);    //保存缩略图
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
			//普通设备
			int       tem_nIndex        = tem_strFileName.ReverseFind(_T('.'));

			CString   tem_strPDFPreName = tem_strFileName;
			tem_strPDFPreName = tem_strPDFPreName.Mid(0, tem_nIndex);

			CString   tem_strImgName1 = tem_strPDFPreName;
			tem_strImgName1 += _T(".jpg");                  //缓存图像全名

			CString   tem_strPDFImgPath1 = m_strBufferPath + tem_strImgName1;    //拍照图像以及路径

			m_conVideoOcx.CaptureImage(tem_strPDFImgPath1);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strPDFImgPath1, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strPDFImgPath1, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strPDFImgPath1, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strThumbPath = GetThumbPath(tem_strPDFImgPath1, tem_strName);    //保存缩略图
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
		//JPEG、TIF、PNG、BMP
//		MessageBox(tem_strWholeName);
		if (m_BCamera800 && m_nLastUsedResolu == m_nInterpolateReso)
		{
			//800W设备
			m_conVideoOcx.CaptureImage(tem_strSrcImageName);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strSrcImageName, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 0);
			DeleteFile(tem_strSrcImageName);
			m_vcFileName.push_back(tem_strName);
			tem_strThumbPath = GetThumbPath(tem_strWholeName, tem_strName);    //保存缩略图
			m_vcWholeName.push_back(tem_strThumbPath);                         //存储缩略图，用于显示
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
		}
		else if (m_BCamera500 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//500W
			m_conVideoOcx.CaptureImage(tem_strSrcImageName);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strSrcImageName, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 3);
			DeleteFile(tem_strSrcImageName);
			m_vcFileName.push_back(tem_strName);
			tem_strThumbPath = GetThumbPath(tem_strWholeName, tem_strName);    //保存缩略图
			m_vcWholeName.push_back(tem_strThumbPath);                         //存储缩略图，用于显示
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
		}
		else if (m_BCamera1200 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1200W
			m_conVideoOcx.CaptureImage(tem_strSrcImageName);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strSrcImageName, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 1);
			DeleteFile(tem_strSrcImageName);
			m_vcFileName.push_back(tem_strName);
			tem_strThumbPath = GetThumbPath(tem_strWholeName, tem_strName);    //保存缩略图
			m_vcWholeName.push_back(tem_strThumbPath);                         //存储缩略图，用于显示
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
		}
		else if (m_BCamera1300 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1300W
			m_conVideoOcx.CaptureImage(tem_strSrcImageName);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strSrcImageName, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			m_vcFileName.push_back(tem_strName);
			tem_strThumbPath = GetThumbPath(tem_strSrcImageName, tem_strName);    //保存缩略图
			tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 2);
			DeleteFile(tem_strSrcImageName);
			
			m_vcWholeName.push_back(tem_strThumbPath);                         //存储缩略图，用于显示
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
		}
		else if (m_BCameraTo1500 && m_nLastUsedResolu==m_nInterpolateReso)
		{
			//1200W
			m_conVideoOcx.CaptureImage(tem_strSrcImageName);
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strSrcImageName, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strThumbPath = GetThumbPath(tem_strSrcImageName, tem_strName);    //保存缩略图
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);                            //存储缩略图，用于显示
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
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strSrcImageName, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strThumbPath = GetThumbPath(tem_strSrcImageName, tem_strName);    //保存缩略图
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);                            //存储缩略图，用于显示
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
			//自动旋转--------------------------------------------
			Self_RecognizeOrit(tem_strSrcImageName, m_BAutoRotate);
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}

			tem_strThumbPath = GetThumbPath(tem_strSrcImageName, tem_strName);    //保存缩略图
			m_vcFileName.push_back(tem_strName);
			m_vcWholeName.push_back(tem_strThumbPath);                            //存储缩略图，用于显示
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);

			tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 6);
			DeleteFile(tem_strSrcImageName);

			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);

		}
		else
		{
			//普通设备
			m_conVideoOcx.CaptureImage(tem_strWholeName);

			//自动旋转--------------------------------------------
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
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strWholeName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strWholeName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strWholeName, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}
			
//			Self_DocOptimize(tem_strWholeName, m_BOptimize, m_nOptBright, m_nOptContrast);
//			Self_DocOptimize2(tem_strWholeName, m_BOptimize);

			m_vcFileName.push_back(tem_strName);
			tem_strThumbPath = GetThumbPath(tem_strWholeName, tem_strName);    //保存缩略图
			m_vcWholeName.push_back(tem_strThumbPath);                         //存储缩略图，用于显示
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
		}
		
		
	}
	m_nImageCount++;
	m_nNamingCount++;
	//更新下侧页码显示
	int       tem_nPageNumber;
	CString   tem_strPageNumber;
	tem_nPageNumber = m_nImageCount + m_nImageCountOther;
	tem_strPageNumber.Format(_T("%d"), tem_nPageNumber);
	GetDlgItem(IDC_STA_NUMBER)->SetWindowText(tem_strPageNumber);


	CRect rtlbl; 
	GetDlgItem(IDC_STA_NUMBER)->GetWindowRect(&rtlbl); 
	ScreenToClient(&rtlbl); //转到客户端界面
	InvalidateRect(&rtlbl);//最后刷新对话框背景 
	UpdateWindow();

// 	CPaintDC  tem_dc(this);
// 	tem_dc.FillSolidRect(rtlbl, RGB(0, 0, 0));
// 	
// 	tem_dc.BitBlt(0, 0, rtlbl.Width(), rtlbl.Height(), &Image, 0, 0, SRCCOPY);
// 	
}


//人证比对
void CUDSSmartCamerav100Dlg::OnBnClickedBtnFaceid()
{
	// TODO: 在此添加控件通知处理程序代码	
	//1、拍照------------------------------------------------------------------
	CString   tem_strName      = _T("");   //无后缀
	CString   tem_strFileName  = _T("");   //带后缀
	CString   tem_strWholeName = _T("");   //带路径,图像文件
	CString   tem_strThumbPath = _T("");   //缩略图路径

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
	//弹出读卡界面，并默认读一次卡
//	m_dlgFaceID.DoModal();
	m_dlgFaceID.Create(IDD_DLG_FACEID, this);
	m_dlgFaceID.ShowWindow(SW_SHOWNORMAL);

	GetDlgItem(IDC_LIST_IMAGE)->GetWindowRect(&m_rcOCX);
	m_dlgFaceID.MoveWindow(m_rcOCX.left-150, m_rcOCX.top+30, m_rcOCX.Width()+150, m_rcOCX.Height()-70, TRUE);

// 	::DeleteFile(g_strFaceImg);
// 	g_strFaceImg = _T("");
	

}


//条码识别
void CUDSSmartCamerav100Dlg::OnBnClickedBtnCapbar()
{
	// TODO: 在此添加控件通知处理程序代码
	int       tem_nFormat = 0;
	CString   tem_strDocPath    = m_strDefaultPath;
	CString   tem_strFileFormat = m_strFileFormat;
	CString   tem_strSrcImagePath = m_strBufferPath;   //插值原图目录
	//判断文件格式若为jpg, bmp, tif, png传入相应的格式； 若为pdf和base直接传入jpg,这样不影响普通拍照
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
		//将格式置为JPG，同时注意显示列表相应修改
		tem_nFormat     = 0;
		m_strFileFormat = ".jpg";  //对PDF和Base64两种情况，修改后缀
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
	//更新下侧页码显示
	int       tem_nPageNumber;
	CString   tem_strPageNumber;
	tem_nPageNumber = m_nImageCount + m_nImageCountOther;
	tem_strPageNumber.Format(_T("%d"), tem_nPageNumber);
	GetDlgItem(IDC_STA_NUMBER)->SetWindowText(tem_strPageNumber);

	CRect rtlbl; 
	GetDlgItem(IDC_STA_NUMBER)->GetWindowRect(&rtlbl); 
	ScreenToClient(&rtlbl); //转到客户端界面
	InvalidateRect(&rtlbl);//最后刷新对话框背景 
	UpdateWindow();
	//将文件名和文件路径添加到vector并更新显示,在事件中
}


//正反面合并
void CUDSSmartCamerav100Dlg::OnBnClickedBtnCap2side()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i=0; i<2; i++)
	{
		CString   tem_strName;      //无后缀文件名
		CString   tem_strFileName;  //有后缀文件名
		CString   tem_strWholeName; //带路径文件名
		CString   tem_strThumbPath; //缩略图路径
		CString   tem_strSrcImageName; //插值原图

		//	tem_strFileName.Format(_T("%d"), m_nImageCount);

		//判断当前是否为PDF或Base64格式，若为这两种格式修改为默认jpg
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
			tem_lReturn = m_conVideoOcx.CaptureCombine(tem_strSrcImageName);    //将合并后的图像进行转换
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}
		}
		else if (m_BCamera500 && m_nLastUsedResolu == m_nInterpolateReso)
		{
			tem_lReturn = m_conVideoOcx.CaptureCombine(tem_strSrcImageName);    //将合并后的图像进行转换
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}
		}
		else if (m_BCamera1200 && m_nLastUsedResolu == m_nInterpolateReso)
		{
			tem_lReturn = m_conVideoOcx.CaptureCombine(tem_strSrcImageName);    //将合并后的图像进行转换
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}
		}
		else if (m_BCamera1300 && m_nLastUsedResolu == m_nInterpolateReso)
		{
			tem_lReturn = m_conVideoOcx.CaptureCombine(tem_strSrcImageName);    //将合并后的图像进行转换
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}
		}
		else if (m_BCameraTo1500 && m_nLastUsedResolu == m_nInterpolateReso)
		{
			tem_lReturn = m_conVideoOcx.CaptureCombine(tem_strSrcImageName);    //将合并后的图像进行转换
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}
		}
		else if(m_BGS1600 && m_nLastUsedResolu == m_nInterpolateReso)
		{
			tem_lReturn = m_conVideoOcx.CaptureCombine(tem_strSrcImageName);    //将合并后的图像进行转换
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}
		}
		else if(m_BCamera200 && m_nLastUsedResolu == m_nInterpolateReso)
		{
			tem_lReturn = m_conVideoOcx.CaptureCombine(tem_strSrcImageName);    //将合并后的图像进行转换
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strSrcImageName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strSrcImageName, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}
		}
		else
		{
			tem_lReturn = m_conVideoOcx.CaptureCombine(tem_strWholeName);    //将合并后的图像进行转换
			//文档优化--------------------------------------------
			if (m_BOptimize)
			{
				CxImage   tem_cxSrcImg;
				tem_cxSrcImg.Load(tem_strWholeName, CMAX_IMAGE_FORMATS);

				float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


				if (tem_fColorPer>=m_fColorPercentage)
				{
					//彩色图像
					Self_DocOptimize(tem_cxSrcImg, tem_strWholeName, m_BOptimize, m_nOptBright, m_nOptContrast);
				} 
				else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
				{
					//黑白图像
					Self_DocOptimize2(tem_cxSrcImg, tem_strWholeName, m_BOptimize);
				}
				//否则为二值图像，不做优化
			}
		}
		
		
	
		if (tem_lReturn == 0)
		{
			if (m_BCamera800 && m_nLastUsedResolu == m_nInterpolateReso)
			{
				//800W设备
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 0);
				DeleteFile(tem_strSrcImageName);
			}
			else if (m_BCamera500 && m_nLastUsedResolu == m_nInterpolateReso)
			{
				//500W设备
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 3);
				DeleteFile(tem_strSrcImageName);
			}
			else if (m_BCamera1200 && m_nLastUsedResolu == m_nInterpolateReso)
			{
				//1200W设备
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 1);
				DeleteFile(tem_strSrcImageName);
			}
			else if (m_BCamera1300 && m_nLastUsedResolu == m_nInterpolateReso)
			{
				//1300W设备
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 2);
				DeleteFile(tem_strSrcImageName);
			}
			else if (m_BCameraTo1500 && m_nLastUsedResolu == m_nInterpolateReso)
			{
				//1200W设备
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 4);
				DeleteFile(tem_strSrcImageName);
			}
			else if (m_BGS1600 && m_nLastUsedResolu == m_nInterpolateReso)
			{
				//1300W->1600W设备
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 5);
				DeleteFile(tem_strSrcImageName);
			}
			else if (m_BCamera200 && m_nLastUsedResolu == m_nInterpolateReso)
			{
				//200W->300W设备
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 6);
				DeleteFile(tem_strSrcImageName);
			}

			m_vcFileName.push_back(tem_strName);
			tem_strThumbPath = GetThumbPath(tem_strWholeName, tem_strName);    //保存缩略图
			m_vcWholeName.push_back(tem_strThumbPath);
			m_vcBussName.push_back(tem_strWholeName);
			ShowImageSize(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			m_nImageCount++;
			m_nNamingCount++;
			//更新下侧页码显示
			int       tem_nPageNumber;
			CString   tem_strPageNumber;
			tem_nPageNumber = m_nImageCount + m_nImageCountOther;
			tem_strPageNumber.Format(_T("%d"), tem_nPageNumber);
			GetDlgItem(IDC_STA_NUMBER)->SetWindowText(tem_strPageNumber);

			CRect rtlbl; 
			GetDlgItem(IDC_STA_NUMBER)->GetWindowRect(&rtlbl); 
			ScreenToClient(&rtlbl); //转到客户端界面
			InvalidateRect(&rtlbl);//最后刷新对话框背景 
			UpdateWindow();
		}
		else
		{
			// 		MessageBox(_T("请更换文档背面，并再次点击“合并拍照”按钮！"));
			MessageBox(_T("请更换文档背面，点击“确定”按钮完成合并拍照！"),_T("正反面合并拍照"),MB_OK);
		}
	}
}


//自动连拍
void CUDSSmartCamerav100Dlg::OnBnClickedBtnCapgoon()
{
	// TODO: 在此添加控件通知处理程序代码
	int       tem_nFormat = 0;
	CString   tem_strDocPath    = m_strDefaultPath;
	tem_strDocPath = tem_strDocPath.Left(tem_strDocPath.GetLength()-1);
	CString   tem_strFileFormat = m_strFileFormat;
	CString   tem_strSrcImagePath = m_strBufferPath;   //插值原图目录
	//判断文件格式若为jpg, bmp, tif, png传入相应的格式； 若为pdf和base直接传入jpg,这样不影响普通拍照
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
		m_strFileFormat = ".jpg";  //对PDF和Base64两种情况，修改后缀
		m_iChildNor.m_conComFilemode.SetCurSel(1);
	}
	m_iChildNor.m_chkAutoCrt.SetCheck(TRUE);  //连拍自动打开启动裁切

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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	
	m_conVideoOcx.StopRun();
	m_conVideoOcx.Uninitial();

	CDialogEx::OnClose();
}


BOOL CUDSSmartCamerav100Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
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

	//屏蔽回车、空格退出问题
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
				m_conRename->GetWindowText(tem_strNewName);              //显示名

				tem_strBussName = m_vcBussName[m_nLastSlcFile];	
				tem_strFormat   = PathFindExtension(tem_strBussName);    //后缀
				tem_strFormat.MakeLower();

				tem_strMiddle    = tem_strBussName;
				tem_wstrBussName = tem_strMiddle.GetBuffer();
				tem_strMiddle.ReleaseBuffer();
				PathRemoveFileSpecW(tem_wstrBussName);   //路径
				tem_strPath     = tem_wstrBussName;     //路径				
				
				if (tem_strFormat == _T(".jpg")||tem_strFormat == _T(".bmp")||tem_strFormat == _T(".png")||tem_strFormat == _T(".tif"))
				{
					//显示名， 图像名，文件名
					
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
				//		MessageBox(_T("文件名已存在！"));
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
						MessageBox(_T("文件名已存在！"));
					}	
					delete[] ptxtSrc;  
					delete[] ptxtDst; 
				} 				
			} 
			*/
			return TRUE;	
			break;
		case VK_SPACE:
			//注意区分按下和弹起两项操作
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
					//删除指定文件
					SHFILEOPSTRUCT FileOp;
					BOOL           m_BRC;    //ReturnCode操作返回码
					CString        strSrcPath;

					strSrcPath  = m_vcBussName[m_nSlctItem];
					strSrcPath += '\0';

					CString  tem_strDstPath;
					tem_strDstPath = '\0';     //删除操作，直接置为NULL

					CString     tem_strTitle;
					tem_strTitle = _T("正在删除...");
					tem_strTitle += '\0';

					FileOp.fFlags = FOF_ALLOWUNDO|FOF_MULTIDESTFILES|FOF_SIMPLEPROGRESS|FOF_NOCONFIRMATION;

					FileOp.lpszProgressTitle = tem_strTitle;
					FileOp.hwnd              = m_hWnd;
					FileOp.hNameMappings     = NULL;
					FileOp.pFrom             = strSrcPath;
					FileOp.pTo               = tem_strDstPath;    //目标目录
					FileOp.wFunc             = FO_DELETE;

					//弹窗提示--------------------------------------------------



					m_BRC = SHFileOperation(&FileOp);
					if (!FileOp.fAnyOperationsAborted)
					{
						if(m_BRC)   
						{
							//操作出现错误
						}		
					}
					else
					{
						//出现意外中止
					}				


					//删除vector中信息
					m_vcFileName.erase(m_vcFileName.begin()+m_nSlctItem);
					m_vcWholeName.erase(m_vcWholeName.begin()+m_nSlctItem);
					m_vcBussName.erase(m_vcBussName.begin()+m_nSlctItem);

					ThumbaiList(m_nThumbWidth, m_nThumbHeight);
					//刷新显示


					
				}
			}
			else
			{
				//获取选中项
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
					//逐项删除
					OnDeleteIt();

				}
				
			}
			m_nSlctItem = -1;	
			break;
		case VK_ESCAPE:
			//调用退出按钮对应的函数
			OnBnClickedBtnTest2();			
			break;
		case 0x41:
			//A键=0x41
			if (GetDlgItem(IDC_LIST_IMAGE)->GetSafeHwnd()==::GetFocus()&& (GetKeyState(VK_CONTROL)&0x8000))
			{
				m_vcCtrlInex.clear();
				m_nSlctItem = -1;
				for (int i=0; i<m_conListCtrl.GetItemCount(); i++)
				{
					m_vcCtrlInex.push_back(i);
					//选中并高亮该项
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
	// TODO: 在此添加控件通知处理程序代码
	m_nRotate = (m_nRotate + 3)%4;
	m_conVideoOcx.RotatedVideo(m_nRotate);

	//写入旋转值
	CString   tem_strInfo = _T("");
	tem_strInfo.Format(_T("%d"), m_nRotate);
	::WritePrivateProfileString(_T("ParentCamera"), _T("VideoRotate"), tem_strInfo, m_strIniPath);

	
}


void CUDSSmartCamerav100Dlg::OnBnClickedBtnRrotate()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nRotate = (m_nRotate + 1)%4;
	m_conVideoOcx.RotatedVideo(m_nRotate);

	//写入旋转值
	CString   tem_strInfo = _T("");
	tem_strInfo.Format(_T("%d"), m_nRotate);
	::WritePrivateProfileString(_T("ParentCamera"), _T("VideoRotate"), tem_strInfo, m_strIniPath);
}

//副头相关操作--------------------------------------------------------------------------------------
afx_msg LRESULT CUDSSmartCamerav100Dlg::OnSubswitch(WPARAM wParam, LPARAM lParam)
{
	int   tem_nInfo      = (int)wParam;
	int   tem_nOperation = (int)lParam;

	CString   tem_strName;      //无后缀文件名
	CString   tem_strFileName;  //用于副头拍照保存文件名
	CString   tem_strWholeName;
	CString   tem_strSrcImageName;    //合并图的缓存图像
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
	int       tem_nPageNumber;    //更新下栏显示
	CString   tem_strPageNumber;  //更新下栏显示
	CRect     rtlbl;              //更新下栏显示

	int       tem_nPID1300 = -1;
	int       tem_nVID1300 = -1;
	CString   tem_strPIDVID, tem_strPID1300, tem_strVID1300;

	switch(tem_nOperation)
	{
	case 0:
		if (tem_nInfo)
		{
			//打开副头
			if (m_nMainOpen!=0)
			{
				MessageBox(_T("请先打开主头设备！"), _T("紫图UDS"), MB_OK);
				m_iChildAdv.m_conChkOpen.SetCheck(BST_UNCHECKED);
				break;
			}
			::GetPrivateProfileString(_T("ChildCamera"), _T("LastUsed"), _T("没有找到副头LasrUsed信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
			tem_nRead = _ttoi(tem_strRead);
			m_nLastSubScan = tem_nRead;
			::GetPrivateProfileString(_T("ChildCamera"), _T("Resolution"), _T("没有找到副头Resolution信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
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

				if (m_nLastSubScan != m_nLastUsedScanner) //前提是以及有至少两个头了
				{
					m_iChildAdv.m_conComScannersub.SetCurSel(m_nLastSubScan);
					m_lReturnCode = m_conVideoOcx.StartSubCamera(m_nLastSubScan);//该索引非Combo索引
					if (m_lReturnCode!=0)
					{
						MessageBox(_T("该设备不能与主头同时使用！"), _T("紫图UDS"), MB_OK);
						//关闭副头
						m_conVideoOcx.StopSubCamera();
//						m_iChildAdv.m_conComScannersub.ResetContent();
//						m_iChildAdv.m_conComDPIsub.ResetContent();
						m_nLastSubScan = -1;
//						m_iChildAdv.m_conChkOpen.SetCheck(BST_UNCHECKED);
						break;;

					}

					//1011-副头插值
					//设备打开成功，首先获取设备PID_VID
					tem_strPIDVID = m_conVideoOcx.GetDevDisplayName(m_nLastSubScan);
					//检查该PID_VID是否为指定的设备
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
						m_iChildAdv.m_conComDPIsub.InsertString(tem_nResCount, _T("4680×3360"));
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

//					m_nLastSubRes = m_conVideoOcx.GetSubCurResoIndex();   //获取副头当前分辨率，修改为设置为配置文件分辨率
					m_conVideoOcx.SetSubResolution(m_nLastSubRes);
					m_iChildAdv.m_conComDPIsub.SetCurSel(m_nLastSubRes);
				}
				else
				{
					MessageBox(_T("该设备已被主头占用！"), _T("紫图UDS"), MB_OK);
					break;
				}
			}
			else
			{
				MessageBox(_T("当前仅有一个可用摄像头！"), _T("紫图UDS"), MB_OK);
				m_iChildAdv.m_conChkOpen.SetCheck(BST_UNCHECKED);
			}
			break;
		}
		else
		{
			//关闭副头
			m_conVideoOcx.StopSubCamera();
			m_iChildAdv.m_conComScannersub.ResetContent();
			m_iChildAdv.m_conComDPIsub.ResetContent();
			m_nLastSubScan = -1;
			break;
		}
	case 1:
		if (tem_nInfo == m_nLastSubScan)
		{
			MessageBox(_T("该设备已打开！"), _T("紫图UDS"), MB_OK);
			break;
		}
		else if (tem_nInfo == m_nLastUsedScanner)
		{
			MessageBox(_T("该设备已被主头占用！"), _T("紫图UDS"), MB_OK);
			//将索引重置，否则会显现主头
			m_iChildAdv.m_conComScannersub.SetCurSel(m_nLastSubScan);
			break;
		}
		else
		{
//			m_conVideoOcx.StopRun();     //6-14注释，当时不知为何添加了先关闭设备
			m_nLastSubScan = tem_nInfo;
			m_lReturnCode = m_conVideoOcx.StartSubCamera(m_nLastSubScan);
			if (m_lReturnCode!=0)
			{
				MessageBox(_T("该设备不能与主头同时使用！"), _T("紫图UDS"), MB_OK);
				//关闭副头
				m_conVideoOcx.StopSubCamera();
//				m_iChildAdv.m_conComScannersub.ResetContent();
//				m_iChildAdv.m_conComDPIsub.ResetContent();
				m_nLastSubScan = -1;
//				m_iChildAdv.m_conChkOpen.SetCheck(BST_UNCHECKED);
				break;

			}
			m_nLastSubRes = m_conVideoOcx.GetSubCurResoIndex();

			//1011-副头插值
			//设备打开成功，首先获取设备PID_VID
			tem_strPIDVID = m_conVideoOcx.GetDevDisplayName(m_nLastSubScan);
			//检查该PID_VID是否为指定的设备
			tem_nPID1300 = tem_strPIDVID.Find(m_strPID1300);
			tem_nVID1300 = tem_strPIDVID.Find(m_strVID1300);
			//1011

			//将副头信息写入ini
			tem_strIniInfo.Format(_T("%d"), m_nLastSubScan);
			::WritePrivateProfileString(_T("ChildCamera"), _T("LastUsed"), tem_strIniInfo, m_strIniPath); 
			
			m_iChildAdv.m_conComDPIsub.ResetContent();
			int  tem_nResCount = m_conVideoOcx.GetSubResoCount();
			m_nInterpolateSubReso = tem_nResCount;
			for (int i=0; i<tem_nResCount; i++)
			{
				CString   tem_strResName = m_conVideoOcx.GetSubReso(i);
				//判断640*480则添加VGA后标，352*288则添加CIF后标
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
				m_iChildAdv.m_conComDPIsub.InsertString(tem_nResCount, _T("4680×3360"));
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
				//1300W设备
				if (m_nLastSubRes == m_nInterpolateSubReso)
				{
					//此时为插值分辨率，设置为最大分辨率
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
		    
			//将副头分辨率写入ini
			tem_strIniInfo.Format(_T("%d"), m_nLastSubRes);
			::WritePrivateProfileString(_T("ChildCamera"), _T("Resolution"), tem_strIniInfo, m_strIniPath); 
		}
		break;
	case 3:
		//0-外部合并，1-内部合并，2-不合并
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
			m_strFileFormat = _T(".jpg");  //对PDF和Base64两种情况，修改后缀
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
		if (m_BMerge)//合并拍照
		{
			if (m_BCamera500 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1)将合并图像保存至缓存目录
				m_conVideoOcx.CaptureTwoCam(tem_strSrcImageName, m_nMergeMode, m_nMergeLocation);	
				//2)插值图像
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 3);
				m_vcFileName.push_back(tem_strName);
				tem_strSrcImageName = GetThumbPath(tem_strWholeName, tem_strName);    //保存缩略图
				m_vcWholeName.push_back(tem_strSrcImageName);
				m_vcBussName.push_back(tem_strWholeName);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
				//3)删除缓存图像
				DeleteFile(tem_strSrcImageName);
			} 
			else if (m_BCamera800 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1)将合并图像保存至缓存目录
				m_conVideoOcx.CaptureTwoCam(tem_strSrcImageName, m_nMergeMode, m_nMergeLocation);	
				//2)插值图像
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 0);
				m_vcFileName.push_back(tem_strName);
				tem_strSrcImageName = GetThumbPath(tem_strWholeName, tem_strName);    //保存缩略图
				m_vcWholeName.push_back(tem_strSrcImageName);
				m_vcBussName.push_back(tem_strWholeName);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
				//3)删除缓存图像
				DeleteFile(tem_strSrcImageName);
			} 
			else if(m_BCamera1200 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1)将合并图像保存至缓存目录
				m_conVideoOcx.CaptureTwoCam(tem_strSrcImageName, m_nMergeMode, m_nMergeLocation);	
				//2)插值图像
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 1);
				m_vcFileName.push_back(tem_strName);
				tem_strSrcImageName = GetThumbPath(tem_strWholeName, tem_strName);    //保存缩略图
				m_vcWholeName.push_back(tem_strSrcImageName);
				m_vcBussName.push_back(tem_strWholeName);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
				//3)删除缓存图像
				DeleteFile(tem_strSrcImageName);
			}
			else if (m_BCamera1300 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1)将合并图像保存至缓存目录
				m_conVideoOcx.CaptureTwoCam(tem_strSrcImageName, m_nMergeMode, m_nMergeLocation);	
				//2)插值图像
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 2);
				m_vcFileName.push_back(tem_strName);
				tem_strSrcImageName = GetThumbPath(tem_strWholeName, tem_strName);    //保存缩略图
				m_vcWholeName.push_back(tem_strSrcImageName);
				m_vcBussName.push_back(tem_strWholeName);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
				//3)删除缓存图像
				DeleteFile(tem_strSrcImageName);
			}
			else if (m_BGS1600 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1)将合并图像保存至缓存目录
				m_conVideoOcx.CaptureTwoCam(tem_strSrcImageName, m_nMergeMode, m_nMergeLocation);	
				//2)插值图像
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 5);
				m_vcFileName.push_back(tem_strName);
				tem_strSrcImageName = GetThumbPath(tem_strWholeName, tem_strName);    //保存缩略图
				m_vcWholeName.push_back(tem_strSrcImageName);
				m_vcBussName.push_back(tem_strWholeName);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
				//3)删除缓存图像
				DeleteFile(tem_strSrcImageName);
			}
			else if (m_BCamera200 && m_nLastUsedResolu==m_nInterpolateReso)
			{
				//1)将合并图像保存至缓存目录
				m_conVideoOcx.CaptureTwoCam(tem_strSrcImageName, m_nMergeMode, m_nMergeLocation);	
				//2)插值图像
				tem_strWholeName = InterPolateImage(tem_strSrcImageName, tem_strWholeName, 6);
				m_vcFileName.push_back(tem_strName);
				tem_strSrcImageName = GetThumbPath(tem_strWholeName, tem_strName);    //保存缩略图
				m_vcWholeName.push_back(tem_strSrcImageName);
				m_vcBussName.push_back(tem_strWholeName);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
				//3)删除缓存图像
				DeleteFile(tem_strSrcImageName);
			}
			else
			{
				m_conVideoOcx.CaptureTwoCam(tem_strWholeName, m_nMergeMode, m_nMergeLocation);		
				m_vcFileName.push_back(tem_strName);
				tem_strSrcImageName = GetThumbPath(tem_strWholeName, tem_strName);    //保存缩略图
				m_vcWholeName.push_back(tem_strSrcImageName);
				m_vcBussName.push_back(tem_strWholeName);
				ThumbaiList(m_nThumbWidth, m_nThumbHeight);
			}
			
		}
		else
		{
			m_conVideoOcx.CaptureSubCam(tem_strWholeName);
			m_vcFileName.push_back(tem_strName);
			tem_strSrcImageName = GetThumbPath(tem_strWholeName, tem_strName);    //保存缩略图
			m_vcWholeName.push_back(tem_strSrcImageName);
			m_vcBussName.push_back(tem_strWholeName);
			ThumbaiList(m_nThumbWidth, m_nThumbHeight);
		}
	//	ShellExecuteW(NULL, TEXT("open"), tem_strWholeName, NULL, NULL, SW_SHOWNORMAL);
		m_nImageCount++;
		m_nNamingCount++;
		//更新下侧页码显示
		tem_nPageNumber = m_nImageCount + m_nImageCountOther;
		tem_strPageNumber.Format(_T("%d"), tem_nPageNumber);
		GetDlgItem(IDC_STA_NUMBER)->SetWindowText(tem_strPageNumber);

		
		GetDlgItem(IDC_STA_NUMBER)->GetWindowRect(&rtlbl); 
		ScreenToClient(&rtlbl); //转到客户端界面
		InvalidateRect(&rtlbl);//最后刷新对话框背景 
		UpdateWindow();
		break;
	default:
		break;
	}

	return 0;
}


//设置功能消息响应----------------------------------------------------------
afx_msg LRESULT CUDSSmartCamerav100Dlg::OnAdvceset(WPARAM wParam, LPARAM lParam)
{
	int      tem_nInfo      = (int)wParam;
	int      tem_nOperation = (int)lParam;
	CString  tem_strIniInfo;
	std::vector<CString>::iterator iter;   //用于HTTP上传
	int     tem_nUpLoadOK = -1;    //若首次上传失败，说明服务器有问题，放弃后续文件上传
	CString tem_strUpLoad;         //上传文件时，服务器的返回信息
	int     tem_nRC       = -1;
	switch (tem_nOperation)
	{
	case 0:
		m_BShowInfo = tem_nInfo;
		m_conVideoOcx.ShowVideoInfo(m_BShowInfo);

		//将显示视频信息写入ini
		tem_strIniInfo.Format(_T("%d"), tem_nInfo);
		::WritePrivateProfileString(_T("AdvanceSet"), _T("ShowInfo"), tem_strIniInfo, m_strIniPath);
		break;
	case 1:
		m_nJpegQulity = tem_nInfo;
		m_conVideoOcx.SetJpegQuality(m_nJpegQulity);

		//将JPEG质量写入ini
		tem_strIniInfo.Format(_T("%d"), m_nJpegQulity);
		::WritePrivateProfileString(_T("AdvanceSet"), _T("JPEGQuality"), tem_strIniInfo, m_strIniPath);
		break;
	case 2:
		m_nAutoSense = tem_nInfo;
		m_conVideoOcx.SetAutomaticSensitiveness(m_nAutoSense);
		
		//将灵敏度写入ini
		tem_strIniInfo.Format(_T("%d"), m_nAutoSense);
		::WritePrivateProfileString(_T("AdvanceSet"), _T("AutoCaptureSense"), tem_strIniInfo, m_strIniPath);
		break;
	case 3:
		m_nNamingMode = 1; //时间命名
	
		m_nNamingCount = 1;

		tem_strIniInfo.Format(_T("%d"), m_nNamingMode);
		::WritePrivateProfileString(_T("AdvanceSet"), _T("NamingMode"), tem_strIniInfo, m_strIniPath);
		break;
	case 4:
		m_nNamingMode = 0; //次序命名

		m_nNamingCount = 1;

		tem_strIniInfo.Format(_T("%d"), m_nNamingMode);
		::WritePrivateProfileString(_T("AdvanceSet"), _T("NamingMode"), tem_strIniInfo, m_strIniPath);
		break;
	case 5:
		m_nNamingMode = 2; //前缀命名
		m_strPreName = m_iChildSet.m_strPreName;
		m_nNamingCount = 1;
		tem_strIniInfo.Format(_T("%d"), m_nNamingMode);
		::WritePrivateProfileString(_T("AdvanceSet"), _T("NamingMode"), tem_strIniInfo, m_strIniPath);
		::WritePrivateProfileString(_T("AdvanceSet"), _T("PreName"), m_strPreName, m_strIniPath);
		break;
	case 6:
		m_strDefaultPath = m_iChildSet.m_strDefaultDoc;
		//注意后面的\\---------------------------------------------------------------------------------------
		::WritePrivateProfileString(_T("AdvanceSet"), _T("DefaultPath"), m_strDefaultPath, m_strIniPath);
		m_strDefaultPath += _T("\\");
		break;
	case 7:
		//上传当前文档	
		if (tem_nInfo == 0)
		{
			//HTTP上传
			//for (iter=m_vcBussName.begin(); iter!=m_vcBussName.end();iter++)
			//{
			//	tem_strUpLoad = m_conVideoOcx.UploadFileHttp(*iter, m_strHttp);	
			//}

//	        tem_strUpLoad = m_conVideoOcx.UploadFileHttp(TEXT("D:\\222.jpg"), m_strHttp);	
			tem_strUpLoad = m_conVideoOcx.HTTPUpload(m_strHttp, TEXT("D:\\分辨率1.jpg"), FALSE);
//			MessageBox(_T("上传完成！"), _T("HTTP上传"), MB_OK);
		} 
		else
		{
			//FTP上传
			for (iter=m_vcBussName.begin(); iter!=m_vcBussName.end();iter++)
			{
				tem_strUpLoad = m_conVideoOcx.UploadFileFtp(*iter, m_strFtpDir, m_strFtpIP, m_strFtpUserName, m_strFtpPassWord, m_strFtpPort);
				
			}
		}
		
		m_iChildSet.m_BUpLoadFiles = FALSE;
		break;
	case 8:
		//主头设置，先判断主头是否打开
		m_conVideoOcx.ShowPorpertiesWindow(TRUE);
		break;
	case 9:
		//副头设置，先判断副头是否打开
		tem_nRC = m_conVideoOcx.ShowPorpertiesWindow(FALSE);
		if (tem_nRC!=0)
		{
			MessageBox(_T("副头未打开！"), _T("紫图UDS"), MB_OK);
		}
		
		break;
	case 10:
		//主头视频设置
		m_conVideoOcx.ShowVideoPorpertiesWindow(TRUE);
		break;
	case 11:
		//副头视频设置
		tem_nRC = m_conVideoOcx.ShowVideoPorpertiesWindow(FALSE);
		if (tem_nRC!=0)
		{
			MessageBox(_T("副头未打开！"), _T("紫图UDS"), MB_OK);
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
	CString       tem_str; //前缀命名时，前缀后加次序区分
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
		//首先读取是否使用日期+计数命名
		::GetPrivateProfileString(_T("AdvanceSet"), _T("DateMark"), _T("没有找到DateMark 信息"), tem_strIniMark.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
		tem_nIniMark = _ttoi(tem_strIniMark);
		if (tem_nIniMark == 1)
		{
			//采用日期+计数命名
			//从配置文件读取日期
			::GetPrivateProfileString(_T("AdvanceSet"), _T("Date"), _T("没有找到Date 信息"), tem_strIniDate.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);

			::GetPrivateProfileString(_T("AdvanceSet"), _T("DayCount"), _T("没有找到DayCount 信息"), tem_strIniCount.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
			tem_nIniCount = _ttoi(tem_strIniCount);
			tem_strIniCount.ReleaseBuffer();

			//获取当前日期
			GetLocalTime(&tem_st);
			tem_strDate.Format(_T("%d%02d%02d"), tem_st.wYear, tem_st.wMonth, tem_st.wDay);

			//比较是否相同
			if (tem_strDate == tem_strIniDate)
			{
				tem_nIniCount++;
				tem_strIniCount.Format(_T("%d"), tem_nIniCount);
				tem_strName2 = tem_strDate + _T("_") + tem_strIniCount;
				//将新的计数写入配置文件
				::WritePrivateProfileString(_T("AdvanceSet"), _T("DayCount"), tem_strIniCount, m_strIniPath);
			}
			else
			{
				//将新的日期写入配置文件
				::WritePrivateProfileString(_T("AdvanceSet"), _T("Date"), tem_strDate, m_strIniPath);
				tem_nIniCount=1;
				tem_strIniCount.Format(_T("%d"), tem_nIniCount);
				//将新的计数写入配置文件
				::WritePrivateProfileString(_T("AdvanceSet"), _T("DayCount"), tem_strIniCount, m_strIniPath);
				tem_strName2 = tem_strDate + _T("_") + tem_strIniCount;			
			}
			
		}
		else
		{
			//采用日期+时间命名
			//获取系统时间日期	
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
		//采用日期+时间命名
		//获取系统时间日期	
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


//控件事件-------------------------------------------------------------------------------------
BEGIN_EVENTSINK_MAP(CUDSSmartCamerav100Dlg, CDialogEx)
	ON_EVENT(CUDSSmartCamerav100Dlg, IDC_UDS_VIDEOCTRL1, 1, CUDSSmartCamerav100Dlg::GetBarcodeStringUdsVideoctrl1, VTS_BSTR)
	ON_EVENT(CUDSSmartCamerav100Dlg, IDC_UDS_VIDEOCTRL1, 2, CUDSSmartCamerav100Dlg::GetAutoCapFileNameUdsVideoctrl1, VTS_BSTR)
	ON_EVENT(CUDSSmartCamerav100Dlg, IDC_UDS_VIDEOCTRL1, 3, CUDSSmartCamerav100Dlg::DeviceChangedUdsVideoctrl1, VTS_BSTR VTS_BSTR)
END_EVENTSINK_MAP()


void CUDSSmartCamerav100Dlg::GetBarcodeStringUdsVideoctrl1(LPCTSTR Barcode)
{
	// TODO: 在此处添加消息处理程序代码
	m_iChildNor.m_conRichEdit.SetSelectionCharFormat(m_iChildNor.tem_fontRichEdit); //先设置格式
	m_iChildNor.m_conRichEdit.ReplaceSel(_T("条码:"));
	m_iChildNor.m_conRichEdit.ReplaceSel(Barcode);
	m_iChildNor.m_conRichEdit.ReplaceSel(_T("\n"));
	m_iChildNor.m_conRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	CString  tem_strName = Barcode;  //不带后缀的文件名
	
	//若识别为二维码网址，则需要将二维码网址中的特殊字符去掉
	//以http开头为网址
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

	//文档优化--------------------------------------------
	if (m_BOptimize)
	{
		CxImage   tem_cxSrcImg;
		tem_cxSrcImg.Load(tem_strWholeName, CMAX_IMAGE_FORMATS);

		float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


		if (tem_fColorPer>=m_fColorPercentage)
		{
			//彩色图像
			Self_DocOptimize(tem_cxSrcImg, tem_strWholeName, m_BOptimize, m_nOptBright, m_nOptContrast);
		} 
		else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
		{
			//黑白图像
			Self_DocOptimize2(tem_cxSrcImg, tem_strWholeName, m_BOptimize);
		}
		//否则为二值图像，不做优化
	}
	
	tem_strThumbPath = GetThumbPath(tem_strWholeName, tem_strName);    //保存缩略图
	m_vcWholeName.push_back(tem_strThumbPath);
	m_vcBussName.push_back(tem_strWholeName);

	ShowImageSize(tem_strWholeName);
	ThumbaiList(m_nThumbWidth, m_nThumbHeight);	
}


void CUDSSmartCamerav100Dlg::GetAutoCapFileNameUdsVideoctrl1(LPCTSTR fileName)
{
	// TODO: 在此处添加消息处理程序代码
	CString  tem_strThumbPath = _T("");
	CString  tem_strName = fileName;  //不带后缀的文件名
	CString  tem_strFileName  = PathFindFileName(tem_strName);   //带后缀的文件名
	CString  tem_strWholeName = fileName;
	CString  tem_strSrcName   = fileName;



	m_vcFileName.push_back(tem_strFileName);

	if (m_BCamera800 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		//根据原路径+文件名拿出文件名，同时转移至新路径
		tem_strWholeName = m_strDefaultPath + tem_strFileName;
		tem_strWholeName = InterPolateImage(tem_strName, tem_strWholeName, 0);
		DeleteFile(tem_strName);
	}
	else if (m_BCamera500 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		//根据原路径+文件名拿出文件名，同时转移至新路径
		tem_strWholeName = m_strDefaultPath + tem_strFileName;
		tem_strWholeName = InterPolateImage(tem_strName, tem_strWholeName, 3);
		DeleteFile(tem_strName);
	}
	else if (m_BCamera1200 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		//根据原路径+文件名拿出文件名，同时转移至新路径
		tem_strWholeName = m_strDefaultPath + tem_strFileName;
		tem_strWholeName = InterPolateImage(tem_strName, tem_strWholeName, 1);
		DeleteFile(tem_strName);
	}
	else if (m_BCamera1300 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		//根据原路径+文件名拿出文件名，同时转移至新路径
		tem_strWholeName = m_strDefaultPath + tem_strFileName;
		tem_strWholeName = InterPolateImage(tem_strName, tem_strWholeName, 2);
		DeleteFile(tem_strName);
	}
	else if (m_BCameraTo1500 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		//根据原路径+文件名拿出文件名，同时转移至新路径
		tem_strWholeName = m_strDefaultPath + tem_strFileName;
		tem_strWholeName = InterPolateImage(tem_strName, tem_strWholeName, 4);
		DeleteFile(tem_strName);
	}
	else if (m_BGS1600 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		//根据原路径+文件名拿出文件名，同时转移至新路径
		tem_strWholeName = m_strDefaultPath + tem_strFileName;
		tem_strWholeName = InterPolateImage(tem_strName, tem_strWholeName, 5);
		DeleteFile(tem_strName);
	}
	else if (m_BCamera200 && m_nLastUsedResolu==m_nInterpolateReso)
	{
		//根据原路径+文件名拿出文件名，同时转移至新路径
		tem_strWholeName = m_strDefaultPath + tem_strFileName;
		tem_strWholeName = InterPolateImage(tem_strName, tem_strWholeName, 6);
		DeleteFile(tem_strName);
	}
	
	
	if (m_BSoundOpen)
	{
		sndPlaySound(_T("CameraSound.WAV"), NULL);
	}

	//文档优化--------------------------------------------
	if (m_BOptimize)
	{
		CxImage   tem_cxSrcImg;
		tem_cxSrcImg.Load(tem_strWholeName, CMAX_IMAGE_FORMATS);

		float tem_fColorPer = Self_GetColorPercentage(tem_cxSrcImg, m_BOptimize);


		if (tem_fColorPer>=m_fColorPercentage)
		{
			//彩色图像
			Self_DocOptimize(tem_cxSrcImg, tem_strWholeName, m_BOptimize, m_nOptBright, m_nOptContrast);
		} 
		else if (tem_fColorPer>=0 && tem_fColorPer<m_fColorPercentage)
		{
			//黑白图像
			Self_DocOptimize2(tem_cxSrcImg, tem_strWholeName, m_BOptimize);
		}
		//否则为二值图像，不做优化
	}
	tem_strThumbPath = GetThumbPath(tem_strWholeName, tem_strFileName);    //保存缩略图
	m_vcWholeName.push_back(tem_strThumbPath);
	m_vcBussName.push_back(tem_strWholeName);

//	CString str = m_conVideoOcx.QrCode(tem_strWholeName);

	m_iChildNor.m_conRichEdit.SetSelectionCharFormat(m_iChildNor.tem_fontRichEdit);  //先设置格式
	m_iChildNor.m_conRichEdit.ReplaceSel(tem_strWholeName);	
	m_iChildNor.m_conRichEdit.ReplaceSel(_T("\n"));
	m_iChildNor.m_conRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	

	ShowImageSize(tem_strWholeName);
	ThumbaiList(m_nThumbWidth, m_nThumbHeight);

	m_nImageCountOther++;
	m_nNamingCount++;
	//更新下侧页码显示
	int       tem_nPageNumber;
	CString   tem_strPageNumber;
	tem_nPageNumber = m_nImageCount + m_nImageCountOther;
	tem_strPageNumber.Format(_T("%d"), tem_nPageNumber);
	GetDlgItem(IDC_STA_NUMBER)->SetWindowText(tem_strPageNumber);

	CRect rtlbl; 
	GetDlgItem(IDC_STA_NUMBER)->GetWindowRect(&rtlbl); 
	ScreenToClient(&rtlbl); //转到客户端界面
	InvalidateRect(&rtlbl);//最后刷新对话框背景 
	UpdateWindow();
	
}


void CUDSSmartCamerav100Dlg::DeviceChangedUdsVideoctrl1(LPCTSTR changeType, LPCTSTR deviceName)
{
	// TODO: 在此处添加消息处理程序代码
	m_iChildNor.m_conRichEdit.SetSelectionCharFormat(m_iChildNor.tem_fontRichEdit);   //先设置格式
	m_iChildNor.m_conRichEdit.ReplaceSel(changeType);
	m_iChildNor.m_conRichEdit.ReplaceSel(_T(" - "));
	m_iChildNor.m_conRichEdit.ReplaceSel(deviceName);
	m_iChildNor.m_conRichEdit.ReplaceSel(_T("\n"));
	m_iChildNor.m_conRichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}


void CUDSSmartCamerav100Dlg::OnBnClickedBtnBrows()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, NULL, m_strDefaultPath, NULL, NULL, SW_SHOW);
}


BOOL CUDSSmartCamerav100Dlg::ThumbaiList(int thumbwidth, int thumbheight)
{

	int          m_nImageIndex= 0;
	DWORD  dwStyle;
	//CImageList初始化
	m_imagelist.Create(thumbwidth,thumbheight,ILC_COLOR24,0,1);

	//ListCtrl初始化
	dwStyle = m_conListCtrl.GetExtendedStyle();
//	dwStyle=dwStyle|LVS_SHOWSELALWAYS|LVS_ALIGNTOP|LVS_ICON|LVS_AUTOARRANGE|LVS_EDITLABELS;  //设置EDITLABELS XP系统下出现图裂
	dwStyle=dwStyle|LVS_SHOWSELALWAYS|LVS_ALIGNTOP|LVS_ICON|LVS_AUTOARRANGE;
	m_conListCtrl.SetExtendedStyle(dwStyle);
	m_conListCtrl.SetImageList(&m_imagelist,LVSIL_NORMAL);
	for(int i=0;i<m_imagelist.GetImageCount();i++)
	{
		m_imagelist.Remove(i);
	}
	m_conListCtrl.DeleteAllItems();
	m_imagelist.SetImageCount(m_vcFileName.size()); 

	wchar_t path[MAX_PATH]; //多字节char
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
	// TODO: 在此添加控件通知处理程序代码
	
	
	//获取双击文件索引,并判断索引是否合法
	int      tem_nSelct = pNMItemActivate->iItem;
	
	if (tem_nSelct>=0 && tem_nSelct<m_conListCtrl.GetItemCount())
	{
		CString  tem_strSlctPath = _T("");
		CString  tem_strFormat   = _T("");
		tem_strFormat   = m_vcBussName[tem_nSelct];
		//根据后缀判断是图像、base64或者PDF，对于PDF文件，单独调用阅读器
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
	
	CString     tem_strImageName;        //图像名
	CString     tem_strImagePath;        //图像导出路径
	CString     tem_strResolution;       //图像分辨率
	CString     tem_strDllPath;
	CString     tem_strDllDoc = m_strDllPath;
	
	int len = WideCharToMultiByte(CP_ACP, 0, pdfpath, pdfpath.GetLength(), NULL, 0, NULL, NULL);
	char*   tem_cPDFFile = new char[len+1];    //导入PDF路径+名
	WideCharToMultiByte(CP_ACP, 0, pdfpath, pdfpath.GetLength(), tem_cPDFFile, len, NULL, NULL);
//	tem_cPDFFile[len+1] = '\0';
	tem_cPDFFile[len] = '\0';

	tem_strImageName.Format(_T("%d"), m_nPDfimg);
	tem_strImageName += _T(".jpg");
	tem_strImagePath  = m_strDefaultPath + tem_strImageName;
	len = WideCharToMultiByte(CP_ACP, 0, tem_strImagePath, tem_strImagePath.GetLength(), NULL, 0, NULL, NULL);
	char*   tem_cImage = new char[len+1];       //导出图像路径+名
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
		
	GhostPdf2Image(tem_cPDFFile, tem_cImage, tem_cRes, tem_strDllPath); //输入PDF路径， 输出图像路径， 分辨率， dll路径
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
	// TODO: 在此添加控件通知处理程序代码
	CString    tem_strSltPath;
	wchar_t    tem_crSltPath[MAX_PATH]; //Unicode使用wchar_t型_t

	ZeroMemory(tem_crSltPath, sizeof(tem_crSltPath));
	BROWSEINFO   m_broseinfo;
	m_broseinfo.hwndOwner = m_hWnd;
	m_broseinfo.pidlRoot  = NULL;
	m_broseinfo.pszDisplayName = tem_crSltPath;
	m_broseinfo.lpszTitle = _T("请选择目录"); 
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
		//注意后面的\\---------------------------------------------------------------------------------------
		::WritePrivateProfileString(_T("Resource"), _T("curdirectory"), m_strDefaultPath, m_strIniPath);
		m_strDefaultPath += _T("\\\\");
		GetDlgItem(IDC_STA_INFOPATH)->SetWindowText(tem_strSltPath);
	} 
	CRect rtlbl; 
	GetDlgItem(IDC_STA_INFOPATH)->GetWindowRect(&rtlbl); 
	ScreenToClient(&rtlbl); //转到客户端界面
	InvalidateRect(&rtlbl);//最后刷新对话框背景 
	UpdateWindow();
}


//增加选择路径按钮，原来为上面双击STACtrl的函数
void CUDSSmartCamerav100Dlg::OnBnClickedBtnSavepath()
{
	// TODO: 在此添加控件通知处理程序代码
	CString    tem_strSltPath;
	wchar_t    tem_crSltPath[MAX_PATH]; //Unicode使用wchar_t型_t

	ZeroMemory(tem_crSltPath, sizeof(tem_crSltPath));
	BROWSEINFO   m_broseinfo;
	m_broseinfo.hwndOwner = m_hWnd;
	m_broseinfo.pidlRoot  = NULL;
	m_broseinfo.pszDisplayName = tem_crSltPath;
	m_broseinfo.lpszTitle = _T("请选择目录"); 
	m_broseinfo.ulFlags   = 0;
	m_broseinfo.lpfn      = NULL;
	m_broseinfo.lParam    = 0;
	m_broseinfo.iImage    = 0;
	LPITEMIDLIST   lp = SHBrowseForFolder(&m_broseinfo);
	if (lp&&SHGetPathFromIDList(lp, tem_crSltPath))
	{
		tem_strSltPath.Format(_T("%s"), tem_crSltPath);
		m_strDefaultPath = tem_strSltPath;
		//注意后面的\\---------------------------------------------------------------------------------------
		::WritePrivateProfileString(_T("Resource"), _T("curdirectory"), m_strDefaultPath, m_strIniPath);
		//如果是C、D盘，最后一位自带“\”不用添加
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
	ScreenToClient(&rtlbl); //转到客户端界面
	InvalidateRect(&rtlbl);//最后刷新对话框背景 
	UpdateWindow();
}


void CUDSSmartCamerav100Dlg::OnBnClickedBtnMin()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_MINIMIZE);
}


void CUDSSmartCamerav100Dlg::OnBnClickedBtnWeb()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, _T("open"),  _T("http://www.arc-uds.com"), NULL, NULL,SW_SHOWNORMAL);
}


//最大化
void CUDSSmartCamerav100Dlg::OnBnClickedBtnDeclear()
{
	// TODO: 在此添加控件通知处理程序代码
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

		//重新定义各个控件的位置
		//1、标题位置
		CRect  tem_rcControl;
		tem_rcControl = rcWorkArea;
		tem_rcControl.top    = 10;
		tem_rcControl.left   = 20;
		tem_rcControl.right  = 700;
		tem_rcControl.bottom = 70;
		GetDlgItem(IDC_STA_BIAOTI)->MoveWindow(&tem_rcControl);

		//2、三个小图标
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

		//3、五个大按钮
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

		//4、三个大的显示控件
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
	    rcTab.top     += 22;  //上侧若填充完全会把标签栏覆盖，遗留问题Tab控件设置标签颜色

	    //调整对话框大小在父窗口中的位置
	    m_iChildNor.MoveWindow(&rcTab);
	    m_iChildAdv.MoveWindow(&rcTab);
	    m_iChildSet.MoveWindow(&rcTab);

		int tem_nCtrlRight;   //控件下侧按钮对齐
/*原始方法
		tem_rcControl.left   = tem_rcControl.right + 3;
		tem_rcControl.right  = rcWorkArea.right;
		tem_rcControl.right -=266;
*/

//固定高，修改宽 宽：高=9:7
		int tem_nLastHeight= tem_rcControl.Height();
		int tem_nNewWidth  = (tem_nLastHeight*9)/7;
		tem_rcControl.left   = tem_rcControl.right + 3;
		tem_rcControl.right  = tem_rcControl.left + tem_nNewWidth;


    

/*固定宽，修改高 宽：高=16:9
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
//		tem_rcControl.left   = tem_rcControl.right - 260;    原始
		tem_rcControl.left   = tem_nOCXRight + 6;
		GetDlgItem(IDC_LIST_IMAGE)->MoveWindow(&tem_rcControl);

		tem_rcControl.bottom = rcWorkArea.bottom -4;
		tem_rcControl.top    = tem_rcControl.bottom - 32;
		tem_rcControl.right  = tem_rcControl.left +250;
		GetDlgItem(IDC_STA_IMAGESIZE)->MoveWindow(&tem_rcControl);

		//5、低栏显示设置
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
		//6、低栏三个按钮以及地址显示区域
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

		m_tipInfo.AddTool(GetDlgItem(IDC_BTN_DECLEAR), _T("恢复"));

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

		m_tipInfo.AddTool(GetDlgItem(IDC_BTN_DECLEAR), _T("最大化"));

		m_BMaxDlg = TRUE;
	}
	ThumbaiList(m_nThumbWidth, m_nThumbHeight);
}


LRESULT CUDSSmartCamerav100Dlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值 
	UINT nHitTest = CDialog::OnNcHitTest(point);

	// 如果鼠标在窗口客户区，则返回标题条代号给Windows
	// 使Windows按鼠标在标题条上类进行处理，即可单击移动窗口
	return (nHitTest==HTCLIENT) ? HTCAPTION : nHitTest;


//	return CDialogEx::OnNcHitTest(point);
}


void CUDSSmartCamerav100Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	PostMessage(WM_NCLBUTTONDOWN,   HTCAPTION,   MAKELPARAM(point.x,  point.y));  

//	CDialogEx::OnLButtonDown(nFlags, point);
}


void CUDSSmartCamerav100Dlg::OnDeleteitemListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CUDSSmartCamerav100Dlg::OnClickListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	BOOL    tem_BRepeat = FALSE;
	CString tem_strSlcFile;
	std::vector<int>::iterator       item_nIndex;
	
	//如果ctrl键被按下，说明要导出PDF或多页TIF，每次存入vector都应应该首先清空
	if (pNMItemActivate->uKeyFlags == LVKF_CONTROL)
	{
		m_nSlctItem = pNMItemActivate->iItem;
		if (m_nSlctItem>=0 && m_nSlctItem<m_conListCtrl.GetItemCount())
		{
			//判断是否为二次点击，二次点击为不选该文件
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
				//是重复的
				tem_BRepeat = FALSE;
			}
			else
			{
				//非重复的
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
			//显示下栏图像大小

			CString   tem_strFilePath = m_vcBussName[m_nSlctItem];
			ShowImageSize(tem_strFilePath);
		}

	}
	
	*pResult = 0;
}


void CUDSSmartCamerav100Dlg::OnRclickListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
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
	//缩略图右键处理，添加右键处理菜单
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
	if (m_vcCtrlInex.size() == 0)
	{
		return;
	}
	if (IDOK !=m_iDeleteTip.DoModal())
	{
		return;
	}
	//删除指定文件
	SHFILEOPSTRUCT FileOp;
	BOOL           m_BRC;    //ReturnCode操作返回码
	CString        strSrcPath;
    //删除至回收站
	std::vector<int>::iterator  tem_nIndex;
	for (tem_nIndex=m_vcCtrlInex.begin(); tem_nIndex!=m_vcCtrlInex.end(); tem_nIndex++)
	{
		int tem_nDeleteItem = *tem_nIndex;
		
		strSrcPath  = m_vcBussName[tem_nDeleteItem];

		strSrcPath += '\0';

		CString  tem_strDstPath;
		tem_strDstPath = '\0';     //删除操作，直接置为NULL

		CString     tem_strTitle;
		tem_strTitle = _T("正在删除...");
		tem_strTitle += '\0';

		FileOp.fFlags = FOF_ALLOWUNDO|FOF_MULTIDESTFILES|FOF_SIMPLEPROGRESS|FOF_NOCONFIRMATION;

		FileOp.lpszProgressTitle = tem_strTitle;
		FileOp.hwnd              = m_hWnd;
		FileOp.hNameMappings     = NULL;
		FileOp.pFrom             = strSrcPath;
		FileOp.pTo               = tem_strDstPath;    //目标目录
		FileOp.wFunc             = FO_DELETE;

		//弹窗提示--------------------------------------------------


		m_BRC = SHFileOperation(&FileOp);
		if (!FileOp.fAnyOperationsAborted)
		{
			if(m_BRC)   
			{
				//操作出现错误
			}		
		}
		else
		{
			//出现意外中止
		}

	}

	//对m_vcCtrlIndex进行从大到小的排序，删除vector信息逆向删除，避免删除前面的元素影响后面的位置
	//使用sort和反向迭代器对vector排降序
	sort(m_vcCtrlInex.rbegin(), m_vcCtrlInex.rend());
	for (tem_nIndex=m_vcCtrlInex.begin(); tem_nIndex!=m_vcCtrlInex.end(); tem_nIndex++)
	{	
		m_vcFileName.erase(m_vcFileName.begin()+*tem_nIndex);
		m_vcWholeName.erase(m_vcWholeName.begin()+*tem_nIndex);
		m_vcBussName.erase(m_vcBussName.begin()+*tem_nIndex);
	}

	
	ThumbaiList(m_nThumbWidth, m_nThumbHeight);
	m_vcCtrlInex.clear();
	//更新下侧页码显示
	int       tem_nPageNumber;
	CString   tem_strPageNumber;
	m_nImageCount--;
	tem_nPageNumber = m_nImageCount + m_nImageCountOther;
	tem_strPageNumber.Format(_T("%d"), tem_nPageNumber);
	GetDlgItem(IDC_STA_NUMBER)->SetWindowText(tem_strPageNumber);


	CRect rtlbl; 
	GetDlgItem(IDC_STA_NUMBER)->GetWindowRect(&rtlbl); 
	ScreenToClient(&rtlbl); //转到客户端界面
	InvalidateRect(&rtlbl);//最后刷新对话框背景 
	UpdateWindow();
	
}


void CUDSSmartCamerav100Dlg::OnRename()
{
	// TODO: 在此添加命令处理程序代码
	if (m_vcCtrlInex.size()==0)
	{
		return;
	}


	m_nLastSlcFile = m_vcCtrlInex.back();    //拿出最后一个选中文件的索引
	m_conListCtrl.SetFocus();
	m_conRename = m_conListCtrl.EditLabel(m_nLastSlcFile);


	m_vcCtrlInex.clear();
}


void CUDSSmartCamerav100Dlg::OnProperty()
{
	// TODO: 在此添加命令处理程序代码
	int       tem_nLastFile;
	CString   tem_strLastFile;

	if (m_vcCtrlInex.size()==0)
	{
		return;
	}
	tem_nLastFile = m_vcCtrlInex.back();
	tem_strLastFile = m_vcBussName[tem_nLastFile];  //获取

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


//	ShellExecute(NULL, _T("properties"), _T("背景.png"), NULL, NULL, SW_SHOWNORMAL);
}


void CUDSSmartCamerav100Dlg::On32775Word()
{
	// TODO: 在此添加命令处理程序代码
	if (m_vcCtrlInex.size()==0)
	{
		return;
	}
	int       tem_nFileIndex  = 0;
	CString   tem_strFileName = _T("");
	CString   tem_strFilePath = _T("");
	
	//a、获取文件索引
	std::vector<int>::iterator tem_nItem;
	for (tem_nItem=m_vcCtrlInex.begin(); tem_nItem!=m_vcCtrlInex.end(); tem_nItem++)
	{
		tem_nFileIndex = *tem_nItem;
		tem_strFileName = m_vcFileName[tem_nFileIndex];
		tem_strFilePath = m_vcBussName[tem_nFileIndex];
		
		//判断文件是否为图像文件
		CString   tem_strMiddle  = tem_strFilePath;
		LPWSTR    tem_wstrOutDoc;
		CString   tem_strOutTxt;                 //导出txt路径
		CString   tem_strOutWord = _T("");       //导出word路径
		int       tem_nIndex    = tem_strMiddle.ReverseFind('.');
		if (tem_nIndex != -1)
		{
			tem_strMiddle = tem_strMiddle.Mid(tem_nIndex+1);
			tem_strMiddle.MakeLower();
//			tem_strFilePath = _T("C:\Users\Administrator\Desktop\OCR测试\\正_0002.jpg");
			if (tem_strMiddle == _T("jpg") || tem_strMiddle == _T("jpeg")||
				tem_strMiddle == _T("bmp") || tem_strMiddle == _T("png") )	
			{
				//生成txt路径，导出txt文件
				tem_strOutTxt  = m_strBufferPath;
				tem_strOutTxt += tem_strFileName;
				tem_strOutTxt += _T(".txt");
				Self_OcrRecognize(tem_strFilePath, tem_strOutTxt);			
				
				//生成doc路径，导出word文件
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
				//生成txt路径，导出txt文件
				tem_strOutTxt  = m_strBufferPath;
				tem_strOutTxt += tem_strFileName;
				tem_strOutTxt += _T(".txt");

				//将tif文件转换为jpg
				CxImage   tem_cxImg;
				tem_cxImg.Load(tem_strFilePath);

				wchar_t*  tem_wstrNewPath = tem_strFilePath.GetBuffer();
				tem_strFilePath.ReleaseBuffer();
				PathRemoveExtension(tem_wstrNewPath);
				CString   tem_strNewPath            = tem_wstrNewPath;
				tem_strNewPath           += _T(".jpg");
	
				tem_cxImg.Save(tem_strNewPath, CXIMAGE_FORMAT_JPG);

				Self_OcrRecognize(tem_strNewPath, tem_strOutTxt);			

				//生成doc路径，导出word文件
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
	MessageBox(_T("导出完毕！"), _T("紫图UDS"),MB_OK);
}


void CUDSSmartCamerav100Dlg::On32776Excel()
{
	// TODO: 在此添加命令处理程序代码
	if (m_vcCtrlInex.size()==0)
	{
		return;
	}
	int       tem_nFileIndex  = 0;
	CString   tem_strFileName = _T("");
	CString   tem_strFilePath = _T("");

	//a、获取文件索引
	std::vector<int>::iterator tem_nItem;
	for (tem_nItem=m_vcCtrlInex.begin(); tem_nItem!=m_vcCtrlInex.end(); tem_nItem++)
	{
		tem_nFileIndex = *tem_nItem;
		tem_strFileName = m_vcFileName[tem_nFileIndex];
		tem_strFilePath = m_vcBussName[tem_nFileIndex];

		//判断文件是否为图像文件
		CString   tem_strMiddle  = tem_strFilePath;
		LPWSTR    tem_wstrOutDoc;
		CString   tem_strOutTxt;                 //导出txt路径
		CString   tem_strOutWord = _T("");       //导出word路径
		int       tem_nIndex    = tem_strMiddle.ReverseFind('.');
		if (tem_nIndex != -1)
		{
			tem_strMiddle = tem_strMiddle.Mid(tem_nIndex+1);
			tem_strMiddle.MakeLower();
			if (tem_strMiddle == _T("jpg") || tem_strMiddle == _T("jpeg")||
				tem_strMiddle == _T("tif") || tem_strMiddle == _T("tiff")||
				tem_strMiddle == _T("bmp") || tem_strMiddle == _T("png") )	
			{
				//生成txt路径，导出txt文件
				tem_strOutTxt  = m_strBufferPath;
				tem_strOutTxt += tem_strFileName;
				tem_strOutTxt += _T(".txt");
//				m_conVideoOcx.OcrRecognizeEx(tem_strFilePath, tem_strOutTxt);
				Self_OcrRecognize(tem_strFilePath, tem_strOutTxt);

				//生成doc路径，导出excel文件
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
	MessageBox(_T("导出完毕！"), _T("紫图UDS"),MB_OK);
}


void CUDSSmartCamerav100Dlg::Self_OcrRecognize(CString imgpath, CString txtpath)
{
	//将输入路径转换为const char*----------------------------------------------
	CStringA    tem_straImgPath(imgpath.GetBuffer(0));  imgpath.ReleaseBuffer();   //GetBuffer(0)不是代表从0开始，而是代表缓冲区至少有0个字符（也就是不用动）//不用动的意思是原来的buffer有多大，返回多大
	string      tem_sImgPath = tem_straImgPath.GetBuffer(0);
	const char* tem_cImgPath = tem_sImgPath.c_str();
	
	//初始化OCR部分------------------------------------------------------------
	wchar_t tem_lpInpath[MAX_PATH]={0};
	GetModuleFileName(AfxGetStaticModuleState()->m_hCurrentInstanceHandle, tem_lpInpath, MAX_PATH);
	PathRemoveFileSpec(tem_lpInpath);

	CString     tem_strInpath = tem_lpInpath;
	CStringA    tem_straInpath(tem_strInpath.GetBuffer(0));   tem_strInpath.ReleaseBuffer();
	string      tem_sInpath   = tem_straInpath.GetBuffer(0);
	const char* tem_cInput = tem_sInpath.c_str();
	
	m_api = new tesseract::TessBaseAPI();
	if (m_api->Init(tem_cInput, "data\\chi_sim"))
//	if (m_api->Init(tem_cInput, "data\\eng"))                //英文库，当前chi_sim也可识别英文，因此英文库暂未用
 	{
 		MessageBox(_T("初始化tesseract失败！"),_T("UDS"), MB_OK);
 		return;
 	}
	m_BOcrOpened = TRUE;

	//读取图像与识别-----------------------------------------------------------
	m_image = pixRead(tem_cImgPath);
	m_api->SetImage(m_image);
//	m_api->SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
//	m_api->SetRectangle(0, 0, 100, 100);    //设置识别区域

	char*      tem_cOutText;
	wchar_t*   tem_cTemp;
	CString    tem_strResult;
	tem_cOutText  = m_api->GetUTF8Text();               //0、最初的输出文本
	tem_cTemp     = Utf_8ToUnicode(tem_cOutText);       //1、第一次格式转换char*—>wchar_t*

	char*       tem_cTextAni;
	tem_cTextAni  = UnicodeToAnsi(tem_cTemp);           //2、第二次格式转换wchar_t*—>char*,   Unicode2Ansi

	USES_CONVERSION;
 	CString    tem_strText;
	tem_strText = A2T(tem_cTextAni);                    //3、第三次格式转换char*—>CString,	

	//将识别的字符串导出到指定的txt文件-----------------------------------------
#ifdef _UNICODE
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );
#endif

	CStdioFile     tem_fileTxt;
	CFileException tem_Error;      
	tem_fileTxt.Open(txtpath, CFile::modeCreate|CFile::modeReadWrite, &tem_Error);
	tem_fileTxt.WriteString(tem_strText);                //没有以上转换，输出文本写入txt文件，可能会被截断
	tem_fileTxt.Close();
	
#ifdef _UNICODE
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//还原区域设定
#endif


	m_api->End();
	pixDestroy(&m_image);
}


wchar_t* CUDSSmartCamerav100Dlg::Utf_8ToUnicode(char* szU8)
{
	//UTF8 to Unicode  
	//由于中文直接复制过来会成乱码，编译器有时会报错，故采用16进制形式  

	//预转换，得到所需空间的大小  
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);  
	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间  
	wchar_t* wszString = new wchar_t[wcsLen + 1];  
	//转换  
	::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);  
	//最后加上'\0'  
	wszString[wcsLen] = '\0';  
	return wszString;  
}


//将宽字节wchar_t*转化为单字节char*  
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
	CString      tem_strOfficePath = officepath;   //输出路径
	CString      tem_strPath;                      //txt+office两个路径参数

	CString      tem_strExePath;
	TCHAR        tem_tcFilepath[MAX_PATH+1] = {0};
	GetModuleFileName(NULL, tem_tcFilepath, MAX_PATH);
	(_tcsrchr(tem_tcFilepath, _T('\\')))[1] = 0;

	tem_strExePath    = tem_tcFilepath;
	tem_strExePath   += _T("TxtToOffice.exe");   //配置文件路径


	tem_strPath.Format(_T("\"%s\" \"%s\""),txtpath, tem_strOfficePath);   //\"转义字符，\"=".用于在双引号之间，存在引号的情况，避免编译器出错

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
	// TODO: 在此添加命令处理程序代码
	/*
	if (m_vcCtrlInex.size()==0)
	{
		return;
	}
	int       tem_nFileIndex  = 0;
	CString   tem_strFileName = _T("");
	CString   tem_strFilePath = _T("");

	//a、获取文件索引
	std::vector<int>::iterator tem_nItem;
	for (tem_nItem=m_vcCtrlInex.begin(); tem_nItem!=m_vcCtrlInex.end(); tem_nItem++)
	{
		tem_nFileIndex = *tem_nItem;
		tem_strFileName = m_vcFileName[tem_nFileIndex];
		tem_strFilePath = m_vcBussName[tem_nFileIndex];

		//判断文件是否为图像文件
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
	//将输入路径转换为const char*----------------------------------------------
	CStringA    tem_straImgPath(imgpath.GetBuffer(0));  imgpath.ReleaseBuffer();   //GetBuffer(0)不是代表从0开始，而是代表缓冲区至少有0个字符（也就是不用动）//不用动的意思是原来的buffer有多大，返回多大
	string      tem_sImgPath = tem_straImgPath.GetBuffer(0);
	const char* tem_cImgPath = tem_sImgPath.c_str();

	tesseract::Orientation        tem_Orientation;
	tesseract::WritingDirection   tem_Direction;
	tesseract::TextlineOrder      tem_Oder;
	float                         tem_fAngle;
	PIX*                          tem_pImage = pixRead(tem_cImgPath);

	tesseract::TessBaseAPI*       tem_pAPI   = new tesseract::TessBaseAPI();

	//初始化-------------------------------------------------------------------
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
			MessageBox(_T("正"));
		}
		else if (tem_Orientation == 1)
		{
//			MessageBox(_T("左90"));
			tem_nAnle = 90;
		}
		else if (tem_Orientation == 2)
		{
//			MessageBox(_T("180"));
			tem_nAnle = 180;
		}
		else if (tem_Orientation == 3)
		{
//			MessageBox(_T("右90"));
			tem_nAnle = 270;
		}

		//加载图像
		CxImage   tem_cxImage;
		tem_cxImage.Load(imgpath, 0);

		//旋转图像
		tem_cxImage.Rotate(tem_fAngle);

		//保存图像
//		tem_cxImage.Save(imgpath);

		//更新缩略图

		//刷新缩略图
	}

	tem_pAPI->End();
	pixDestroy(&tem_pImage);
}


//右键菜单-左旋90度
void CUDSSmartCamerav100Dlg::On32778RightRotateL()
{
	// TODO: 在此添加命令处理程序代码
	//获取索引
	if (m_vcCtrlInex.size()==0)
	{
		return;
	}
	int       tem_nFileIndex  = 0;
	CString   tem_strThumPath = _T("");
	CString   tem_strFilePath = _T("");

	//a、获取文件索引
	std::vector<int>::iterator tem_nItem;
	for (tem_nItem=m_vcCtrlInex.begin(); tem_nItem!=m_vcCtrlInex.end(); tem_nItem++)
	{
		tem_nFileIndex = *tem_nItem;
		tem_strThumPath = m_vcWholeName[tem_nFileIndex];
		tem_strFilePath = m_vcBussName[tem_nFileIndex];

		//判断文件是否为图像文件
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

				//单张刷新ListCtrl控件
				Self_ReplaceImage(m_nThumbWidth, m_nThumbHeight, tem_nFileIndex);
			}
			else
			{
				MessageBox(_T("无法处理PDF/DCM/Base64文档！"), _T("UDS"), MB_OK);
			}

		}	
		
	}
}


//右键菜单-右旋90度
void CUDSSmartCamerav100Dlg::On32779RightRotateR()
{
	// TODO: 在此添加命令处理程序代码
	//获取索引
	if (m_vcCtrlInex.size()==0)
	{
		return;
	}
	int       tem_nFileIndex  = 0;
	CString   tem_strThumPath = _T("");
	CString   tem_strFilePath = _T("");

	//a、获取文件索引
	std::vector<int>::iterator tem_nItem;
	for (tem_nItem=m_vcCtrlInex.begin(); tem_nItem!=m_vcCtrlInex.end(); tem_nItem++)
	{
		tem_nFileIndex = *tem_nItem;
		tem_strThumPath = m_vcWholeName[tem_nFileIndex];
		tem_strFilePath = m_vcBussName[tem_nFileIndex];

		//判断文件是否为图像文件
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
				//单张刷新ListCtrl控件
				Self_ReplaceImage(m_nThumbWidth, m_nThumbHeight, tem_nFileIndex);
			}
			else
			{
				MessageBox(_T("无法处理PDF/DCM/Base64文档！"), _T("UDS"), MB_OK);
			}
		}	
		
	}
}


BOOL CUDSSmartCamerav100Dlg::CreateHSMenu(void)
{
	COLORREF    tem_clrSet0 = RGB(185,205,246);   //底色
	COLORREF    tem_clrSet1 = RGB(222,160,228);   //选中颜色
	COLORREF    tem_clrSet2 = RGB(131,88,136);    //分支夜色

	HWND hwnd = GetSafeHwnd();
	m_menuRightClick.CreateMenu( hwnd );
	CHSMenu::SetMenuItemHeight(28);  //设置Menu高度
	CHSMenuPro::SetColor(CLR_BKGNDMENU, tem_clrSet0); //设置底色
	CHSMenuPro::SetColor(CLR_BKGNDSEL, tem_clrSet1);	//设置被选中时底色
	CHSMenuPro::SetColor(CLR_BORDERSPR, tem_clrSet2);	//设置分支颜色
	CHSMenuPro::SetMenuStyle(ML_ARROWROUND, true);
	CHSMenuPro::SetMenuStyle(ML_SELGRADIENT_V, true);

	m_menuRightClick.CreateMenu(hwnd);
	m_menuRightClick.AppendMenuW(_T("复  制"), 32771, 0, 0);
	m_menuRightClick.AppendMenuW(_T("删  除"), 32772, 0, 0);
	m_menuRightClick.AppendMenuW(_T("重命名"), 32773, 0, 0); //数字为菜单ID
	m_menuRightClick.AppendMenuW(_T("属  性"), 32774, 0, 0);
	m_menuRightClick.AppendMenuW(_T("左旋90度"), 32778, 0, 0);
	m_menuRightClick.AppendMenuW(_T("右旋90度"), 32779, 0, 0);
	m_menuRightClick.AppendMenuW(_T("一键Word"), 32775, 0, 0);
//	m_menuRightClick.AppendMenuW(_T("一键Excel"), 32776, 0, 0);
//	m_menuRightClick.AppendMenuW(_T("自动旋转"), 32777, 0, 0);
	

	return TRUE;
}


void CUDSSmartCamerav100Dlg::OnHoverListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
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
		uFileListLen += (it->GetLength() + 1);//尾部一个\0结束符  
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
	// TODO: 在此添加控件通知处理程序代码	
	/*原：读卡流程在主界面*/
	/*
	BOOL   tem_BRC = FALSE;
	tem_BRC = ReadCard();
	if (tem_BRC)
	{
		m_iChildCard.DoModal();
	} 
	*/
	/*新：读卡流程修改至读卡界面*/
	m_iChildCard.DoModal();
	

}


BOOL CUDSSmartCamerav100Dlg::ReadCard(void)
{
	/*2018-03-08注释，原因：该段函数修改流程后未用，现需修改读卡库
	m_strCardName    = _T("");
	m_strCardSex     = _T("");
	m_strCardNation  = _T("");
	m_strCardBirth   = _T("");
	m_strCardAddress = _T("");
	m_strCardID      = _T("");
	m_strCardOffice  = _T("");
	m_strCardValidity= _T("");
	//检查缓存目录是否存在，若不存在创建缓存目录
	//缓存目录初步暂定C:\\UDSScanTemp
	//暂定为我的文档，UDSData
//	CString    tem_strScanTemp = _T("C:\\UDSScanTemp");
	CString    tem_strScanTemp = GetMyDocument();
	tem_strScanTemp += _T("\\");
	tem_strScanTemp += _T("UDSData");
	CFileFind  tem_fFileFind;
	if (!tem_fFileFind.FindFile(tem_strScanTemp))
	{
		CreateDirectory(tem_strScanTemp, NULL);
	}


	//判断配置文件是否存在
	CString  tem_strCardIni = tem_strScanTemp + _T("\\");
	tem_strCardIni += _T("PersonInfo.INI");

	BOOL     tem_BFileFind = PathFileExists(tem_strCardIni);
	if (!tem_BFileFind)
	{
		//文件不存在，将原配置文件复制到指定目录
		TCHAR        tem_tcFilepath[MAX_PATH+1] = {0};
		GetModuleFileName(NULL, tem_tcFilepath, MAX_PATH);
		(_tcsrchr(tem_tcFilepath, _T('\\')))[1] = 0;
		m_strIniPath   = tem_tcFilepath;
		m_strIniPath  += _T("PersonInfo.INI");
//		m_strIniPath.Replace(_T("\\"), _T("\\\\"));

		CopyFile(m_strIniPath, tem_strCardIni, TRUE);
	}


	tem_strScanTemp += _T("\\身份证信息");
	if (!tem_fFileFind.FindFile(tem_strScanTemp))
	{
		CreateDirectory(tem_strScanTemp, NULL);
	}

	tem_strScanTemp += _T("\\Image");
	if (!tem_fFileFind.FindFile(tem_strScanTemp))
	{
		CreateDirectory(tem_strScanTemp, NULL);
	}



	//以当前系统时间命名图像文件，避免重复
	CString       tem_strPicName, tem_strNewPicName;   //身份证头像名
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
	if (tem_strRC != _T("打开端口失败"))
	{
		m_iCard->SetHeadPicPath(tem_strPicName);
		tem_strRC = m_iCard->ReadIDCard();
		if (tem_strRC == _T(""))
		{
			//读卡成功
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

			//判断m_strNewPicName是否存在，若存在删除本次保存图像，若不存在重命名为该图像
			BOOL   tem_BIsFinded = FALSE;
			CFileFind  tem_find;
			tem_BIsFinded = tem_find.FindFile(tem_strNewPicName);
			if (tem_BIsFinded)
			{
				//文件已存在
				DeleteFile(tem_strPicName);
			}
			else
			{
				//文件不存在
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
			MessageBox( _T("请重新放置身份证"), _T(""), MB_OK);
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
	CString  tem_strImageInfo  = _T("图像大小：");
// 	long     tem_lFilesize     = 0;   //单位字节
// 	int      tem_nFilesize     = 0;
// 
// 	//获取图像大小
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
			//转换为kb显示
			tem_filesize = tem_filesize/1024;
			tem_strfilesize.Format(_T("%I64d"), tem_filesize);
			tem_strImageInfo += tem_strfilesize;
			tem_strImageInfo += _T("kb");

		}
		else
		{
			//使用字节表示
			tem_strfilesize.Format(_T("%I64d"), tem_filesize);
			tem_strImageInfo += tem_strfilesize;
			tem_strImageInfo += _T("b");

		}
	}


	GetDlgItem(IDC_STA_IMAGESIZE)->SetWindowText(tem_strImageInfo);

	GetDlgItem(IDC_STA_IMAGESIZE)->GetWindowRect(&m_rcImageSize); 
	ScreenToClient(&m_rcImageSize); //转到客户端界面
	InvalidateRect(&m_rcImageSize);//最后刷新对话框背景 
	UpdateWindow();

	/*以下获取图像尺寸
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
		ScreenToClient(&m_rcImageSize); //转到客户端界面
		InvalidateRect(&m_rcImageSize);//最后刷新对话框背景 
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
//	// TODO: 在此添加控件通知处理程序代码
//	MessageBox(_T("click"));
//	*pResult = 0;
//}


void CUDSSmartCamerav100Dlg::OnBeginlabeleditListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	
	*pResult = 0;
}


void CUDSSmartCamerav100Dlg::OnEndlabeleditListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	int       tem_nSlcImage =-1;
	tem_nSlcImage = pDispInfo->item.iItem;
	CString   tem_strSlcName      = m_vcFileName[tem_nSlcImage];    //原文件名
//	CString   tem_strSlcWholeName = m_vcWholeName[tem_nSlcImage];
	CString   tem_strSlcBussName     = m_vcBussName[tem_nSlcImage];

	CString   tem_strNewName  = pDispInfo->item.pszText;           //新文件名
	if (tem_strNewName == _T(""))
	{
		tem_strNewName = tem_strSlcName;
	}
	CString   tem_strNewWhole = _T("");
	CString   tem_strNewBuss  = _T("");

	CString   tem_strFormat   = PathFindExtension(tem_strSlcBussName);    //原文件后缀
	tem_strFormat.MakeLower();

	CString   tem_strMiddle    = tem_strSlcBussName;  
	LPWSTR    tem_wstrBussName = tem_strMiddle.GetBuffer();
	tem_strMiddle.ReleaseBuffer();
	PathRemoveFileSpecW(tem_wstrBussName);   
	CString   tem_strDocumnet  = tem_wstrBussName;                       //原文件目录
	
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
//			MessageBox(_T("文件名已存在！"));
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
//			MessageBox(_T("文件名已存在！"));
		}	
		delete[] ptxtSrc;  
		delete[] ptxtDst; 
	} 
	

	
	*pResult = 0;
}


CString CUDSSmartCamerav100Dlg::GetThumbPath(CString wholeimage, CString imagename)
{
	//判断缓存目录是否存在，若缓存目录不存在，创建目录

	
	
	
	//缩略图文件名以及存储路径
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
		osName = _T("当前系统版本为：Windows 2000");  
		return FALSE;
	}    
	else if((i==5)&&(j==1))    
	{     
		osName = _T("当前系统版本为：Windows XP");  
		return FALSE;
	}    
	else if((i==5)&&(j==2))    
	{    
		osName = _T("当前系统版本为：Windows 2003");  
		return FALSE;
	}    
	else if((i==6)&&(j==0))    
	{    
		osName = _T("当前系统版本为：Windows Vista");   
		return TRUE;
	}    
	else if((i==6)&&(j==1))    
	{    
		osName = _T("当前系统版本为：Windows 7");   
		return TRUE;
	}  
	else if((i==6)&&(j==2))    
	{    
		osName = _T("当前系统版本为：Windows 8");  
		return TRUE;
	}  
	else if((i==6)&&(j==3))    
	{    
		osName = _T("当前系统版本为：Windows 8.1");  
		return TRUE;
	}  
	else if((i==10)&&(j==0))    
	{    
		osName = _T("当前系统版本为：Windows 10");  
		return TRUE;
	}  
	else  
	{  
		osName = _T("当前系统低于Windows 2000，或者高于Windows 10，或者未知系统版本");  
		return TRUE;
	}  
	return TRUE;
}


// 图像插值
CString CUDSSmartCamerav100Dlg::InterPolateImage(CString srcImage, CString dsImage, int index)
{
	int       tem_nInterpolateIndex = index;

	int       tem_nGoalResoW        = 0;          //目标分辨率
	int       tem_nGoalResoH        = 0;
	float     tem_fRateW            = 0;          //转换率宽
	float     tem_fRateH            = 0;

	long*     tem_lWidth;
	tem_lWidth  = new long;
	long*     tem_lHeight;  
	tem_lHeight = new long;
	float     tem_fWidth;
	float     tem_fHeight;

	CString   tem_strSrcImage       = srcImage;   //原图路径
	CString   tem_strDstImage       = dsImage;     //目标图路径

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

	//判断图像格式
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
	CString   tem_strInputPath  = srcImg;     //导入图像路径
	CString   tem_strOutputPath = dstImg;     //导出PDF路径

	
	//导出PDF--------
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
		//设置PDF属性信息******************************************************
		pPdf->set_info(_T("Creator"), _T("SmartScan"));   
		pPdf->set_info(_T("Author"), _T("UDS"));   
		pPdf->set_info(_T("Title"), _T("UDSPDF")); 
		pPdf->set_info(_T("Subject"), _T("扫描文档"));

		//图片导入***********************************************************
		{
			
			wstring sFilePath(tem_strInputPath.GetBuffer());
			image = pPdf->load_image(_T("auto"), sFilePath, _T(""));
			pPdf->begin_page_ext(10, 10, _T(""));
			pPdf->fit_image(image, 0, 0, _T("adjustpage dpi=0"));  //导入图像
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
	CString       tem_strInputPath  = srcImg;    //导入图像地址
	CString       tem_strOutputPath = dstImg;    //导出txt地址


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
	int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
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

//获取指定分辨率的索引值，如获取第二大分辨率，第三大分辨率
int CUDSSmartCamerav100Dlg::GetDiyResoindex(int diyvalue)
{
	int     tem_nMaxIndex     = 0;
	long    tem_lValue1       = -1;
	long    tem_lValue2       = 10;
	long    tem_lMiddle       = 0;

	BOOL    tem_BMark         = TRUE;

	CString tem_strResolution = _T("");
	int    tem_nResCount = m_conVideoOcx.GetResCount();  //设备分量率数量
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
	//对vector进行排序，同时索引对应相应的的值,由小到大
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
	int    tem_nResCount = m_conVideoOcx.GetSubResoCount();  //设备分量率数量
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
	// TODO: 在此添加控件通知处理程序代码
	if (!GetDlgItem(IDC_BTN_ZOOMOUT)->IsWindowEnabled())
	{
		CRect  tem_rcZoomOut;
		GetDlgItem(IDC_BTN_ZOOMOUT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ZOOMOUT)->GetWindowRect(&tem_rcZoomOut); 
		ScreenToClient(&tem_rcZoomOut); //转到客户端界面
		InvalidateRect(&tem_rcZoomOut);//最后刷新对话框背景 
		UpdateWindow();
	}
	
	m_conVideoOcx.ZoomIn();
}


void CUDSSmartCamerav100Dlg::OnBnClickedBtnZoomout()
{
	// TODO: 在此添加控件通知处理程序代
	m_conVideoOcx.ZoomOut();
}


void CUDSSmartCamerav100Dlg::OnBnClickedBtnRecover()
{
	// TODO: 在此添加控件通知处理程序代码
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
				//设备变动，有设备接入时，重新获取设备名并插入combox
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
	int      tem_nDevCount = m_conVideoOcx.GetDeviceCount();//当前设备数量
	if (tem_nDevCount == number)
	{
		//设备数量未变
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


// 精度——毫秒
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
	// TODO: 在此添加控件通知处理程序代码	
	
	CString   tem_strName;         //无后缀
	CString   tem_strFileName;     //带后缀
	CString   tem_strWholeName;    //带路径,图像文件
	CString   tem_strPDFimgName;   //带路径，所有文件
	CString   tem_strTXTimgName;
	CString   tem_strThumbPath;    //缩略图路径
	CString   tem_strSrcImageName; //插值原图
	CString   tem_strSrcImagePDF;  //PDF原图
	CString   tem_strCardFormat;
	CString   tem_strCardFront;     //身份证正面路径
	CString   tem_strCardBack;     //身份证背面路径
	CString   tem_strPDFImg;       //生成PDF时原图
	if (!m_BCardDlg)
	{
		tem_strName      = NamingFile(m_nNamingMode);
		m_strFrontName    = tem_strName;
		tem_strCardFormat = m_strFrontName;
		tem_strCardFormat+= _T(".jpg");		
		tem_strCardFront = m_strBufferPath;     //身份证正面路径
		tem_strCardFront += _T("Front");
		tem_strCardFront += tem_strCardFormat;

		//1、拍摄图像，并调整图像
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
		tem_strCardBack  = m_strBufferPath;     //身份证背面路径
		tem_strPDFImg    = m_strBufferPath;     //生成PDF时原图
		
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
		//a、创建背景纸
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

		//b、加载身份证图像，并调整dpi以及图像尺寸
		tem_FrontImage.Load(g_strFrontImg, CXIMAGE_FORMAT_JPG);
		tem_FrontImage.SetXDPI(200);
		tem_FrontImage.SetYDPI(200);
		tem_FrontImage.Resample(m_nCardWidth, m_nCardHeight);

		tem_BackImage.Load(tem_strCardBack, CXIMAGE_FORMAT_JPG);
		tem_BackImage.SetXDPI(200);
		tem_BackImage.SetYDPI(200);
		tem_BackImage.Resample(m_nCardWidth, m_nCardHeight);

		//c、合并图像
		int   tem_nOffsetX = (m_nA4Width - m_nCardWidth)/2;    //左右居中
		int   tem_nOffsetY = (m_nA4Height/2+(m_nA4Height/2 - m_nCardHeight)/2);
		tem_MergeImage.MixFrom(tem_FrontImage, tem_nOffsetX, tem_nOffsetY);
		tem_nOffsetY = (m_nA4Height/2 - m_nCardHeight/2);
		tem_MergeImage.MixFrom(tem_BackImage, tem_nOffsetX, tem_nOffsetY);

		//d、保存图像并更新显示

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
			tem_strThumbPath = GetThumbPath(tem_strPDFImg, m_strFrontName);    //保存缩略图
		}
		else
		{
			tem_strThumbPath = GetThumbPath(tem_strWholeName, m_strFrontName);    //保存缩略图
		}

		m_vcWholeName.push_back(tem_strThumbPath);                         //存储缩略图，用于显示
		m_vcBussName.push_back(tem_strWholeName);
		ShowImageSize(tem_strWholeName);
		ThumbaiList(m_nThumbWidth, m_nThumbHeight);

		m_nImageCount++;
		m_nNamingCount++;
		//更新下侧页码显示
		int       tem_nPageNumber;
		CString   tem_strPageNumber;
		tem_nPageNumber = m_nImageCount + m_nImageCountOther;
		tem_strPageNumber.Format(_T("%d"), tem_nPageNumber);
		GetDlgItem(IDC_STA_NUMBER)->SetWindowText(tem_strPageNumber);

		CRect rtlbl; 
		GetDlgItem(IDC_STA_NUMBER)->GetWindowRect(&rtlbl); 
		ScreenToClient(&rtlbl); //转到客户端界面
		InvalidateRect(&rtlbl);//最后刷新对话框背景 
		UpdateWindow();

		//e、关闭子窗口
	    m_dlgFront.DestroyWindow();

		//f、调用打印程序
		ShellExecute(NULL, _T("print"), tem_strWholeName, NULL, NULL, SW_SHOWNORMAL);

		//g、文件清理，释放内存
		DeleteFile(g_strFrontImg);
		DeleteFile(tem_strCardBack);
		//ofd的缓存删除放在调用的exe中
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

	// TODO: 在此处添加消息处理程序代码
	if (m_BCardDlg)
	{
		GetDlgItem(IDC_UDS_VIDEOCTRL1)->GetWindowRect(&m_rcOCX);
		m_dlgFront.MoveWindow(m_rcOCX.left, m_rcOCX.top, 440, 160, TRUE);
	}
}


// 检查设备名是否重复，在XP系统下Camera均为USB视频设备
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
		//设置滚动条
		m_iChildNor.m_conSlidBright.SetRange(tem_lBrightMin, tem_lBrightMax);   //设置slider范围
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

// 自动旋转
int CUDSSmartCamerav100Dlg::Self_RecognizeOrit(CString imgpath, BOOL on_off)
{
	if (!on_off)
	{
		return 0;
	}
	//1、判断图像是否为tif,若为tif格式则转换为jpg--------------------------------
	BOOL      tem_BTR        = FALSE;
	CString   tem_strNewPath = _T("");

	wchar_t*  tem_wstrFormat = imgpath.GetBuffer();
	imgpath.ReleaseBuffer();
	tem_wstrFormat = PathFindExtension(tem_wstrFormat);
	CString tem_strFormat = tem_wstrFormat;
	tem_strFormat.MakeLower();
	if (tem_strFormat == _T(".tif"))
	{
		//转换为jpg格式
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

	//2、获取旋转角度--------------------------------------------------------------
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

	//初始化-------------------------------------------------------------------
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
	
	//1、判断图像是否为tif,若为tif格式则转换为jpg-----------------------------------
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
		
	//3、加载dll等文件-------------------------------------------------------------
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
		//图像为右旋90度
//		MessageBox(_T("需左旋90度"));
		
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
		//图像倒置
//		MessageBox(_T("需旋转180度"));
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
		//图像为左旋90度
//		MessageBox(_T("需右旋90度"));
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
		//此时为黑白图像
		return -1;
	}

	int      tem_nWidth  = tem_cxImage.GetWidth();
	int      tem_nHeight = tem_cxImage.GetHeight();
	int      tem_nCount  = 0;                         //记录彩色点数

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
				//不为黑白即为彩色
				tem_nCount++;
			}
		}
	}
	float tem_fPer =  (float)tem_nCount*100.0 / (float)(tem_nWidth*tem_nHeight);
	return tem_fPer;
}


//img-输入图像， imgpath-输出图像的路径
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
// 	tem_cxOptimize2.Save(_T("C:\\Users\\Administrator\\Desktop\\人证比对\\亮度.jpg"), GetTypeFromFileName(imgpath));

// 	tem_cxOptimize2 = tem_cxOptimize;
// 	tem_cxOptimize2.Dilate(2);     //膨胀
// 	tem_cxOptimize2.Save(_T("C:\\Users\\Administrator\\Desktop\\人证比对\\膨胀.jpg"), GetTypeFromFileName(imgpath));

// 	tem_cxOptimize2 = tem_cxOptimize;
// 	tem_cxOptimize2.Erode(2);      //腐蚀
// 	tem_cxOptimize2.Light(bright, contrast);  //light=(-255, 255)   contrast=(-100, 100)
// 	tem_cxOptimize2.Save(_T("C:\\Users\\Administrator\\Desktop\\人证比对\\腐蚀_亮度.jpg"), GetTypeFromFileName(imgpath));

	tem_cxOptimize = tem_cxOptimize;
	tem_cxOptimize.Light(bright, contrast);  //light=(-255, 255)   contrast=(-100, 100)
	tem_cxOptimize.Erode(2);      //腐蚀

	//判断文件格式，jpg设置压缩率
	if (GetTypeFromFileName(imgpath) == CXIMAGE_FORMAT_JPG)
	{
		tem_cxOptimize.SetJpegQuality(m_nJpegQulity);
	}

	tem_cxOptimize.Save(imgpath, GetTypeFromFileName(imgpath));
	
	return 0;
}


int CUDSSmartCamerav100Dlg::Self_DocOptimize2(CxImage img, CString imgpath, bool on_off)
{
	//1、图像加载--------------------------------------------------------------------------
	CxImage m_Image = img;
//	m_Image.Load(imgpath, CMAX_IMAGE_FORMATS);

	CxImage imageSrc,imageRed;
	imageSrc.CreateFromArray(m_Image.GetBits(),m_Image.GetWidth(),
		m_Image.GetHeight(),m_Image.GetBpp(),m_Image.GetEffWidth(),false);   

	//2、二值化----------------------------------------------------------------------------
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

	//留红;
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
	//去噪;
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

	//判断文件格式，jpg设置压缩率
	if (GetTypeFromFileName(imgpath) == CXIMAGE_FORMAT_JPG)
	{
		m_Image.SetJpegQuality(m_nJpegQulity);
	}
	m_Image.Save(imgpath, GetTypeFromFileName(imgpath));
	return 0;
}


afx_msg LRESULT CUDSSmartCamerav100Dlg::OnFaceid(WPARAM wParam, LPARAM lParam)
{
	//1、拍照------------------------------------------------------------------
	CString   tem_strName      = _T("");   //无后缀
	CString   tem_strFileName  = _T("");   //带后缀
	CString   tem_strWholeName = _T("");   //带路径,图像文件
	CString   tem_strThumbPath = _T("");   //缩略图路径

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
	HBRUSH hBrushBorder    =::CreateSolidBrush(m_clBackColor);       //缩略图边框色
	HBRUSH hBrushBkground  =::CreateSolidBrush(m_clBackColor);       //缩略图背景色

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
	m_conListCtrl.RedrawItems(item, item);           //ListCtrl重绘对应当前页面中Item的索引
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

	//输入、输出文件路径-----------------------------------------------------
	CString tem_strFilesPath = _T("");
	tem_strFilesPath.Format(_T("\"%s\" \"%s\" \"%s\""), _T("1"), tem_strOfdPath, tem_strImgPath);
	MessageBox(tem_strFilesPath);
	tem_Info.lpParameters = tem_strFilesPath;

	//editor.exe全路径------------------------------------------------------
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
