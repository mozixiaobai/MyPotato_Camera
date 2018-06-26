// UDSChildSet.cpp : 实现文件
//

#include "stdafx.h"
#include "UDS SmartCamera v1.0.0.h"
#include "UDSChildSet.h"
#include "afxdialogex.h"


// CUDSChildSet 对话框

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


// CUDSChildSet 消息处理程序


BOOL CUDSChildSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/*********************************************
	*
	*0、控件初始化相关变量
	*1、 变量初始化
	*2、 SliderBar初始化
	*3、 CheckBox初始化
	*4、 设置界面相关初始化
	*5、 Radio控件初始化
	*
	**********************************************/
	
	//0、----------------------------------------
	/*
	TCHAR        tem_tcFilepath[MAX_PATH+1] = {0};
	CString      tem_strIniPath;
	CString      tem_strRead;
	GetModuleFileName(NULL, tem_tcFilepath, MAX_PATH);
	(_tcsrchr(tem_tcFilepath, _T('\\')))[1] = 0;
	tem_strIniPath    = tem_tcFilepath;
//	tem_strIniPath   += _T("UDSSmartCamera.ini");   //配置文件路径
	int tem_nDirIndex = tem_strIniPath.ReverseFind('\\');
	tem_strIniPath = tem_strIniPath.Mid(0, tem_nDirIndex);
	tem_nDirIndex = tem_strIniPath.ReverseFind('\\');
	tem_strIniPath = tem_strIniPath.Mid(0, tem_nDirIndex+1);

	tem_strIniPath   += _T("config.ini");   //配置文件路径
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
		tem_strIniPath   += _T("config.ini");   //配置文件路径
//		tem_strIniPath.Replace(_T("\\"), _T("\\\\"));
	}


	int     tem_nShowInfo;
	int     tem_nNamingMode;
	int     tem_nJpegQuality;
	int     tem_nAutoSense;
	::GetPrivateProfileString(_T("AdvanceSet"), _T("ShowInfo"), _T("没有找到ShowInfo信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nShowInfo = _ttoi(tem_strRead);
	::GetPrivateProfileString(_T("AdvanceSet"), _T("NamingMode"), _T("没有找到NamingMode信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nNamingMode = _ttoi(tem_strRead);
	switch(tem_nNamingMode)
	{
	case 0:
		//顺序命名
		((CButton*)GetDlgItem(IDC_CHK_CAPODER))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_CHK_PRENAME))->SetCheck(0);
		m_conEditPre.EnableWindow(FALSE);
		break;
	case 1:
		//时间命名
		((CButton*)GetDlgItem(IDC_CHK_CAPODER))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_CHK_PRENAME))->SetCheck(0);
		m_conEditPre.EnableWindow(FALSE);
		break;
	case 2:
		//前缀命名
		((CButton*)GetDlgItem(IDC_CHK_CAPODER))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_CHK_PRENAME))->SetCheck(1);
		m_conEditPre.EnableWindow(TRUE);
		::GetPrivateProfileString(_T("AdvanceSet"), _T("PreName"), _T("没有找到PreName信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	    m_conEditPre.SetWindowText(tem_strRead);
        //文件前缀传递给Main类
		break;
	default:
		//顺序命名
		((CButton*)GetDlgItem(IDC_CHK_CAPODER))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_CHK_PRENAME))->SetCheck(0);
		m_conEditPre.EnableWindow(FALSE);
		break;
	}

	::GetPrivateProfileString(_T("AdvanceSet"), _T("JPEGQuality"), _T("没有找到JPEGQuality 信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nJpegQuality = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();
	

	::GetPrivateProfileString(_T("AdvanceSet"), _T("AutoCaptureSense"), _T("没有找到AutoCaptureSense信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	tem_nAutoSense = _ttoi(tem_strRead);
	tem_strRead.ReleaseBuffer();

	::GetPrivateProfileString(_T("AdvanceSet"), _T("HTTP"), _T("没有找到HTTP信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strURL = tem_strRead;
	tem_strRead.ReleaseBuffer();
	m_conEditHttp.SetWindowText(m_strURL);

	::GetPrivateProfileString(_T("AdvanceSet"), _T("FTP"), _T("没有找到FTP信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
	m_strFtp = tem_strRead;
	tem_strRead.ReleaseBuffer();
	
	//1、----------------------------------------
	m_pWndSet = GetParentOwner();
	m_hWndSet = m_pWndSet->m_hWnd;
	m_strDefaultDoc = "";
	m_BHttp   = TRUE;

	//2、----------------------------------------
	m_conSlidImgQ.SetRange(10, 100);
	m_conSlidImgQ.SetPos(tem_nJpegQuality);
	
	m_conImgQ = tem_nJpegQuality;     //通过读取配置文件更改默认质量
	UpdateData(FALSE);

	m_conSlidAutoS.SetRange(1, 20);
	m_conSlidAutoS.SetPos(tem_nAutoSense);
	
	m_conAutoS = tem_nAutoSense;
	UpdateData(FALSE);

	//3、------------------------------------------
	((CButton*)GetDlgItem(IDC_CHK_VEDIOINFO))->SetCheck(tem_nShowInfo);
	((CButton*)GetDlgItem(IDC_CHK_HTTP))->SetCheck(0);

	//4、------------------------------------------
	//方法二：设置背景颜色,这种方法控件的背景色也会根据界面背景色发生改变
	
	
	CDialogEx::SetBackgroundColor(RGB(72,77,91));
	m_btnShangchuan.Init(IDB_PNG_SC, BTN_IMG_1, BTN_TYPE_NORMAL);
	m_btnMaincam.Init(IDB_PNG_SETSET, BTN_IMG_3, BTN_TYPE_NORMAL);
	

	m_btnTipsSet.Create(this);
	m_btnTipsSet.AddTool(GetDlgItem(IDC_BTN_UPLOAD), _T("上传当前文件"));
	m_btnTipsSet.AddTool(GetDlgItem(IDC_BTN_CAMREM), _T("设置"));
	m_btnTipsSet.SetDelayTime(200);   //设置延迟
	m_btnTipsSet.SetTipTextColor(RGB(0, 0, 0));//设置字体颜色
	m_btnTipsSet.SetTipBkColor(RGB(255, 255, 255));//设置提示框背景颜色
	m_btnTipsSet.Activate(TRUE); //启用提示功能

	//5、---------------------------------------------
	((CButton*)GetDlgItem(IDC_RADIO_MAINCAM))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_SUBCAM))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_VEDIO))->SetCheck(FALSE);

	((CButton*)GetDlgItem(IDC_RADIO_HTTP))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_FTP))->SetCheck(FALSE);

	::GetPrivateProfileString(_T("OtherSet"), _T("SoundOpen"), _T("没有找到SoundOpen信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, tem_strIniPath);
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
	// 异常: OCX 属性页应返回 FALSE
}


void CUDSChildSet::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

}


HBRUSH CUDSChildSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	//Slider控件美化
	if (pWnd->GetDlgCtrlID() == IDC_SLID_IMGQULITY)
	{
		return (HBRUSH) CreateSolidBrush(RGB(72,77,91));
	}
	if (pWnd->GetDlgCtrlID() == IDC_SLID_AUTOSENS)
	{
		return (HBRUSH) CreateSolidBrush(RGB(72,77,91));
	}

	//Static控件美化
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
		tem_Font.CreatePointFont(100, _T("宋体"));
		pDC->SelectObject(&tem_Font);
	}

	if (pWnd->GetDlgCtrlID()==IDC_GRP_SETONE || pWnd->GetDlgCtrlID()==IDC_GRP_SETTWO || pWnd->GetDlgCtrlID()==IDC_STA_UPLOAD || pWnd->GetDlgCtrlID()==IDC_STA_GROUNEW2)
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
	}


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


BOOL CUDSChildSet::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_MOUSEMOVE)
	{
		m_btnTipsSet.RelayEvent(pMsg);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


//是否显示视频信息
void CUDSChildSet::OnBnClickedChkVedioinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_VEDIOINFO))
	{
		::SendMessage(m_hWndSet, WM_ADVCESET, 1, 0);
	} 
	else
	{
		::SendMessage(m_hWndSet, WM_ADVCESET, 0, 0);
	}

}


//设置JPEG图像质量
void CUDSChildSet::OnCustomdrawSlidImgqulity(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(FALSE);
	m_conImgQ = m_conSlidImgQ.GetPos();

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_IMGQULITYSHOW)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); //转到客户端界面
	InvalidateRect(&tem_rcRect);//最后刷新对话框背景

	::SendMessage(m_hWndSet, WM_ADVCESET, m_conImgQ, 1);
	
	*pResult = 0;
}


//设置自拍连灵敏度
void CUDSChildSet::OnNMCustomdrawSlidAutosens(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(FALSE);
	m_conAutoS = m_conSlidAutoS.GetPos();

	CRect  tem_rcRect;; 
	GetDlgItem(IDC_STA_AUTOSENSSHOW)->GetWindowRect(&tem_rcRect); 
	ScreenToClient(&tem_rcRect); //转到客户端界面
	InvalidateRect(&tem_rcRect);//最后刷新对话框背景 

	::SendMessage(m_hWndSet, WM_ADVCESET, m_conAutoS, 2);

	*pResult = 0;
}


//设置时间命名
void CUDSChildSet::OnBnClickedChkTime()
{
	// TODO: 在此添加控件通知处理程序代码
	((CButton*)GetDlgItem(IDC_CHK_CAPODER))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHK_PRENAME))->SetCheck(0);
	m_conEditPre.SetWindowText(_T(""));
	m_conEditPre.EnableWindow(FALSE);
	::SendMessage(m_hWndSet, WM_ADVCESET, 1, 3);

}


//设置次序命名
void CUDSChildSet::OnBnClickedChkCapoder()
{
	// TODO: 在此添加控件通知处理程序代码
	((CButton*)GetDlgItem(IDC_CHK_CAPODER))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHK_TIME))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHK_PRENAME))->SetCheck(0);
	m_conEditPre.SetWindowText(_T(""));
	m_conEditPre.EnableWindow(FALSE);
	::SendMessage(m_hWndSet, WM_ADVCESET, 1, 4);
}


//指定前缀命名
void CUDSChildSet::OnBnClickedChkPrename()
{
	// TODO: 在此添加控件通知处理程序代码
	//指定前缀命名前，先检查编辑框前缀是否为空，为空则要给出提示
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
		MessageBox(_T("请输入前缀名！"));
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
		//发送tem_strPreName字符串
		::SendMessage(m_hWndSet, WM_ADVCESET, 1, 5);
	}
	*/
}


void CUDSChildSet::OnBnClickedChkHttp()
{
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_HTTP))
	{
		::SendMessage(m_hWndSet, WM_ADVCESET, 1, 12);     //打开声音消息
	} 
	else
	{
		::SendMessage(m_hWndSet, WM_ADVCESET, 0, 12);     //关闭声音消息
	}
}

//HTTP上传
void CUDSChildSet::OnBnClickedBtnUpload()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_BUpLoadFiles)
	{
		m_BUpLoadFiles = TRUE;   //上传完成后置为FALSE
		/*新流程*/
		//流程简化仅发送相应消息
		if (m_BHttp)
		{
			::SendMessage(m_hWndSet, WM_ADVCESET, 0, 7);     //http上传消息
		} 
		else
		{
			::SendMessage(m_hWndSet, WM_ADVCESET, 1, 7);     //ftp上传消息
		}

		/*原流程
		//读取输入的HTTP-URL
		CString  tem_strHttp = _T("");
		m_conEditHttp.GetWindowText(tem_strHttp);
		m_strURL = tem_strHttp;

		//调用HTTP上传函数，上传当前所有文件
		::SendMessage(m_hWndSet, WM_ADVCESET, 0, 7);     //http上传消息

		::SendMessage(m_hWndSet, WM_ADVCESET, 1, 7);     //ftp上传消息

		//判断HTTP还是FTP再写入ini配置文件
		//写入ini文件
		TCHAR        tem_tcFilepath[MAX_PATH+1] = {0};
		CString      tem_strIniPath;
		CString      tem_strRead;
		GetModuleFileName(NULL, tem_tcFilepath, MAX_PATH);
		(_tcsrchr(tem_tcFilepath, _T('\\')))[1] = 0;
		tem_strIniPath    = tem_tcFilepath;
		tem_strIniPath   += _T("UDSSmartCamera.ini");   //配置文件路径
		::WritePrivateProfileString(_T("AdvanceSet"), _T("HTTP"), tem_strHttp, tem_strIniPath); 
		*/
	}
	
}


void CUDSChildSet::OnBnClickedBtnCamrem()
{
	// TODO: 在此添加控件通知处理程序代码
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


//主头属性
void CUDSChildSet::OnBnClickedBtnSetpath()
{
	// TODO: 在此添加控件通知处理程序代码

	::SendMessage(m_hWndSet, WM_ADVCESET, 0, 8);
}

//副头属性
void CUDSChildSet::OnBnClickedBtnCamres()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hWndSet, WM_ADVCESET, 0, 9);
}

//主头视频设置
void CUDSChildSet::OnBnClickedBtnVideo1()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hWndSet, WM_ADVCESET, 0, 10);
}

//副头视频设置
void CUDSChildSet::OnBnClickedBtnVideo2()
{
	// TODO: 在此添加控件通知处理程序代码
	::SendMessage(m_hWndSet, WM_ADVCESET, 0, 11);
}


void CUDSChildSet::OnChangeEditPrename()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//Edit控件内容发生改变，将字符串消息发送
	m_conEditPre.GetWindowText(m_strPreName);
	//发送tem_strPreName字符串
	::SendMessage(m_hWndSet, WM_ADVCESET, 1, 5);

}


void CUDSChildSet::OnBnClickedRadioHttp()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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

