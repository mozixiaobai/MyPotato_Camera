// UDSFaceID.cpp : 实现文件
//

#include "stdafx.h"
#include "UDSFaceID.h"
#include "afxdialogex.h"

#include "opencv\cv.h"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\core\core.hpp"

using namespace cv;

extern CString    g_strFaceImg;    //现场拍摄图像路径
extern CString    m_strDefaultPath;   //默认路径
// CUDSFaceID 对话框

IMPLEMENT_DYNAMIC(CUDSFaceID, CDialogEx)

CUDSFaceID::CUDSFaceID(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSFaceID::IDD, pParent)
{

	m_editNation = _T("");
	m_editName = _T("");
	m_editBirth = _T("");
	m_editCardnum = _T("");
	m_editOffice = _T("");
	m_editSex = _T("");
	m_editValidity = _T("");
	m_editAddress = _T("");
	m_StaInfo = _T("");
	m_editResult = _T("");
	m_editScore = _T("");
}

CUDSFaceID::~CUDSFaceID()
{
}

void CUDSFaceID::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT_FACENAME, m_editName);
	//  DDX_Control(pDX, IDC_EDIT_FACESEX, m_editSex);
	DDX_Text(pDX, IDC_EDIT_FACENATION, m_editNation);
	DDX_Text(pDX, IDC_EDIT_FACENAME, m_editName);
	//  DDX_Control(pDX, IDC_EDIT_FACESEX, m_editSex);
	DDX_Text(pDX, IDC_EDIT_FACEBIRTH, m_editBirth);
	DDX_Text(pDX, IDC_EDIT_FACENUMBER, m_editCardnum);
	DDX_Text(pDX, IDC_EDIT_FACEOFFICE, m_editOffice);
	DDX_Text(pDX, IDC_EDIT_FACESEX, m_editSex);
	DDX_Text(pDX, IDC_EDIT_FACEVALID, m_editValidity);
	DDX_Text(pDX, IDC_EDIT_FACEADDRESS, m_editAddress);
	DDX_Text(pDX, IDC_STA_CARDINFO, m_StaInfo);
	//  DDX_Text(pDX, IDC_EDIT_SCORE, m_editScore);
	//  DDV_MinMaxFloat(pDX, m_editScore, 0, 100);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_editResult);
	//  DDX_Control(pDX, IDC_EDIT_SCORE, m_editScore);
	DDX_Text(pDX, IDC_EDIT_SCORE, m_editScore);
	DDX_Control(pDX, IDC_PIC_IDIMG, m_conIDImg);
}


BEGIN_MESSAGE_MAP(CUDSFaceID, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_CONTRAST, &CUDSFaceID::OnBnClickedBtnContrast)
	ON_BN_CLICKED(IDC_BTN_IDPRINT, &CUDSFaceID::OnBnClickedBtnIdprint)
	ON_BN_CLICKED(IDC_BTN_FACECAP, &CUDSFaceID::OnBnClickedBtnFacecap)
	ON_BN_CLICKED(IDC_BTN_READCARD2, &CUDSFaceID::OnBnClickedBtnReadcard2)
END_MESSAGE_MAP()


// CUDSFaceID 消息处理程序


BOOL CUDSFaceID::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/*1、变量初始化*/
	m_BFirst      = TRUE;

	m_fPassValue  = 10.0;

	m_strName     = _T("");
	m_strSex      = _T("");
	m_strNation   = _T("");
	m_strBirth    = _T("");
	m_strAddress  = _T("");
	m_strID       = _T("");
	m_strOffice   = _T("");
	m_strValidity = _T("");
	m_strFilePath = _T("");
	m_strCopyImg  = _T("");

	m_strCardImgPath = _T("");
	m_strCopyBT      = _T("");
	m_strQRCode      = _T("");
	m_strVerifyTime  = _T("");
	m_strQRImgInfo   = _T("");

	m_editName    = _T("");
	m_editSex     = _T("");
	m_editNation  = _T("");
	m_editBirth   = _T("");
	m_editCardnum = _T("");
	m_editOffice  = _T("");
	m_editValidity= _T("");
	m_editAddress = _T("");
	m_StaInfo     = _T("");

	m_editScore   = _T("");
	m_editResult  = _T("");
	UpdateData(FALSE);

	m_hSubWnd = AfxGetMainWnd()->m_hWnd;

	/*2、缓存目录*/
	CFileFind  tem_fFileFind;
	CString   tem_strScanTemp = SubGetMyDocument();
	tem_strScanTemp += _T("\\");
	tem_strScanTemp += _T("UDSData");

	m_strCardIniPath  = tem_strScanTemp + _T("\\");
	m_strCardIniPath += _T("FaceInfo.INI");

	m_strIniPath      = tem_strScanTemp + _T("\\");
	m_strIniPath     += _T("config.ini");

	m_strPicBuffer  = tem_strScanTemp;
	m_strPicBuffer += _T("\\身份证信息");
	m_strFingerPath = m_strPicBuffer;
	m_strInfoBuffer = m_strPicBuffer;
	
	if (!tem_fFileFind.FindFile(m_strPicBuffer))
	{
		CreateDirectory(m_strPicBuffer, NULL);
	}

	m_strPicBuffer += _T("\\Image");
	if (!tem_fFileFind.FindFile(m_strPicBuffer))
	{
		CreateDirectory(m_strPicBuffer, NULL);
	}

	m_strFingerPath += _T("\\Finger");
	if (!tem_fFileFind.FindFile(m_strPicBuffer))
	{
		CreateDirectory(m_strPicBuffer, NULL);
	}


	//生成身份证图像-----------------------------------------
	TCHAR     tem_tcExepath[MAX_PATH+1] = {0};
	GetModuleFileName(NULL, tem_tcExepath, MAX_PATH);
	(_tcsrchr(tem_tcExepath, _T('\\')))[1] = 0;

	m_strProntImg   = tem_tcExepath;
	m_strBackImg    = tem_tcExepath;
	m_strProntImg  += _T("res\\");
	m_strBackImg   += _T("res\\");
	m_strProntImg  += _T("PrintFront.jpg");
	m_strBackImg   += _T("PrintBack.jpg");

	//读取人证比对通过值--------------------------------------
	CString tem_strRead;
	::GetPrivateProfileString(_T("Resource"), _T("FacePassvalue"), _T("没有找到FacePassvalue信息"), tem_strRead.GetBuffer(MAX_PATH), MAX_PATH, m_strIniPath);
	tem_strRead.ReleaseBuffer();
	m_fPassValue = _tstof(tem_strRead);
	if (m_fPassValue>100)
	{
		m_fPassValue = 100.0;
	}
	else if (m_fPassValue<0)
	{
		m_fPassValue = 0.0;
	}
	


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CUDSFaceID::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	if (m_BFirst && (g_strFaceImg!=_T("")))
	{
		m_BFirst = FALSE;
		m_strCardImgPath = Self_GetSystemTime(m_strPicBuffer);
		m_strCardImgPath = Self_ReadCard(m_strCardImgPath);
		if (m_strCardImgPath != _T(""))
		{
			Self_ShowImg(m_strCardImgPath, IDC_PIC_IDIMG);
			Self_FaceIDCompare(m_strCardImgPath, g_strFaceImg);
		}
	
		Self_ShowImg(g_strFaceImg, IDC_PIC_CAPIMG);	
	}	
}



/*****************************
*        目录
* 1、获取我的文档
* 2、获取系统时间
* 3、显示图像
* 4、清空图像显示
*
*****************************/
CString CUDSFaceID::SubGetMyDocument(void)
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


CString CUDSFaceID::Self_GetSystemTime(CString dir)
{
	CString       tem_strPicName = dir;   //身份证头像名
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


void CUDSFaceID::Self_ShowImg(CString imgpath, int ctrlID)
{
	CWnd*  pWnd = NULL;
	pWnd = GetDlgItem(ctrlID);
	CDC*   pDc;
	CDC    imageDC;
	pDc = pWnd->GetDC();

	int     cx, cy;    //图像宽高
	CxImage* pImage;
	pImage = new CxImage; 
	CRect    tem_rectChildPic;

	pImage->Load(imgpath);
	cx = pImage->GetWidth();
	cy = pImage->GetHeight();

	GetDlgItem(ctrlID)->GetWindowRect(&tem_rectChildPic);
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


void CUDSFaceID::Self_ClearImg(int ctrlID)
{
	CWnd*  tem_pWnd = NULL;
	tem_pWnd = GetDlgItem(ctrlID);
	CDC*   tem_pDc;
	tem_pDc = tem_pWnd->GetDC();
	CRect   tem_rcPicRect;
	GetDlgItem(ctrlID)->GetWindowRect(&tem_rcPicRect);
	ScreenToClient(&tem_rcPicRect);

	tem_pDc->FillSolidRect(0, 0, tem_rcPicRect.Width(), tem_rcPicRect.Height(),RGB(240,240,240));
	m_conIDImg.SetBitmap(NULL);	
}


/*****************************
*        目录
* 1、读卡
* 2、人脸比对
* 3、生成二维码
* 4、生成比对单
*
*****************************/

//picpath身份证图像路径
CString CUDSFaceID::Self_ReadCard(CString picpath)
{
	//1、信息显示控件初始化------------------------------------------------
	m_strCopyImg   = _T("");
	m_strQRCode    = _T("");
	m_strQRImgInfo = _T("");
	m_strVerifyTime= _T("");

	//清空比对结果显示
	m_editScore  = _T("");
	m_editResult = _T("");
	UpdateData(FALSE);

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


	CString    tem_strRC         = _T("");
	CString    tem_strPicName    = picpath;      //身份证图像保存路径
	CString    tem_strNewPicName = m_strPicBuffer; 
	CString    tem_strIDCopyPath = m_strPicBuffer;
	CString    tem_strRecardDate = _T("");

	CString    tem_strOriDat     = m_strFingerPath;
	CString    tem_strOriWlt     = m_strFingerPath;

	//获取读卡时间
	SYSTEMTIME  tem_stDateTime;
	GetLocalTime(&tem_stDateTime);
	tem_strRecardDate.Format(_T("%d-%02d-%02d %02d:%02d:%02d"), tem_stDateTime.wYear, tem_stDateTime.wMonth, tem_stDateTime.wDay,
		tem_stDateTime.wHour, tem_stDateTime.wMinute, tem_stDateTime.wSecond);

	tem_strRC = m_iReadCard.OpenCardPort();
	if (tem_strRC != _T("打开端口失败"))
	{
		m_iReadCard.SetHeadPicPath(tem_strPicName);
		tem_strRC = m_iReadCard.ReadIDCard(m_strFingerPath);
		if (tem_strRC == _T(""))
		{
			//读卡成功
			m_editName     = m_iReadCard.GetCardName();
			m_editSex      = m_iReadCard.GetCardSex();
			m_editNation   = m_iReadCard.GetCardNation();
			m_editBirth    = m_iReadCard.GetCardBirth();
			m_editAddress  = m_iReadCard.GetCardAddress();
			m_editCardnum  = m_iReadCard.GetCardID();
			m_editOffice   = m_iReadCard.GetIssuingOrgan();
			m_editValidity = m_iReadCard.GetAllottedTime();

			m_iReadCard.CloseCardPort();


			tem_strNewPicName += _T("\\");
			tem_strNewPicName += m_editName;
			tem_strNewPicName += m_editCardnum;
			tem_strNewPicName += _T(".bmp");

			tem_strIDCopyPath += _T("\\");
			tem_strIDCopyPath += m_editName;
			tem_strIDCopyPath += m_editCardnum;
			tem_strIDCopyPath += _T(".jpg");
//			m_strCopyImg       = tem_strIDCopyPath;
			m_strCopyImg       = m_strDefaultPath;
			m_strCopyImg      += m_editName;
			m_strCopyImg      += m_editCardnum;
			m_strCopyImg      += _T(".jpg");

			m_strQRCode        = m_strPicBuffer;
			m_strQRCode       += _T("\\QR");
			m_strQRCode       += m_editName;
			m_strQRCode       += m_editCardnum;
			m_strQRCode       += _T(".png");


			m_stcIdInfo.imgpath  = tem_strNewPicName;
			m_stcIdInfo.name     = m_editName;
			m_stcIdInfo.sex      = m_editSex;
			m_stcIdInfo.nation   = m_editNation;
			m_stcIdInfo.birth    = m_editBirth;
			m_stcIdInfo.address  = m_editAddress;
			m_stcIdInfo.IDnumber = m_editCardnum;
			m_stcIdInfo.office   = m_editOffice;
			m_stcIdInfo.validate = m_editValidity;

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

			UpdateData(FALSE);
			//写入ini文件
			::WritePrivateProfileString(_T("PersonInfo"), _T("cardname"), m_editName, m_strCardIniPath); 
			::WritePrivateProfileString(_T("PersonInfo"), _T("cardsex"), m_editSex, m_strCardIniPath); 
			::WritePrivateProfileString(_T("PersonInfo"), _T("cardnation"), m_editNation, m_strCardIniPath); 
			::WritePrivateProfileString(_T("PersonInfo"), _T("cardbirthdate"), m_editBirth, m_strCardIniPath); 
			::WritePrivateProfileString(_T("PersonInfo"), _T("cardaddress"), m_editAddress, m_strCardIniPath); 
			::WritePrivateProfileString(_T("PersonInfo"), _T("cardid"), m_editCardnum, m_strCardIniPath); 
			::WritePrivateProfileString(_T("PersonInfo"), _T("cardissueo"), m_editOffice, m_strCardIniPath); 
			::WritePrivateProfileString(_T("PersonInfo"), _T("cardvaliddate"), m_editValidity, m_strCardIniPath); 
			::WritePrivateProfileString(_T("PersonInfo"), _T("cardimage"), tem_strNewPicName, m_strCardIniPath);

			m_strVerifyTime = tem_strRecardDate;

			tem_strOriDat     += _T("\\fp.dat");
			tem_strOriWlt     += _T("\\xp.wlt");
			::DeleteFile(tem_strOriDat);
			::DeleteFile(tem_strOriWlt);

			//读卡成功提示
			m_StaInfo      = _T("读卡成功！");
			UpdateData(FALSE);

			return tem_strNewPicName;
		}
		else
		{
			m_iReadCard.CloseCardPort();
			m_StaInfo      = _T("读卡失败，重新读卡！");
			UpdateData(FALSE);
			//清空头像显示
			Self_ClearImg(IDC_PIC_IDIMG);

			return _T("");
		}

	}
	else
	{
		m_StaInfo      = _T("打开端口失败，重新读卡！");
		UpdateData(FALSE);
		//清空头像显示
		Self_ClearImg(IDC_PIC_IDIMG);

		return _T("");
	}

}


void CUDSFaceID::Self_FaceIDCompare(CString idimg, CString faceimg)
{
	::WritePrivateProfileString(_T("PersonInfo"), _T("personimage"), faceimg, m_strCardIniPath);
	USES_CONVERSION;
	float    tem_fScore     = 0.0f;
	CString  tem_strDllPath = _T("model");
	int      tem_nRC        = InitFaceEngine(T2A(tem_strDllPath));
	if (tem_nRC != UDS_NOERR)
	{
		ExitFaceEngine();
		return;
	}


	VerifyImage(T2A(idimg), T2A(faceimg), tem_fScore);	
	
	tem_fScore *= (float)100;
	if (tem_fScore>0)
	{
		float   tem_fSqrt = sqrt(tem_fScore);
		tem_fScore  = tem_fScore/tem_fSqrt;
		tem_fScore *= (float)10;
	}
	
	m_editScore.Format(_T("%.1f"), tem_fScore);

	::WritePrivateProfileString(_T("PersonInfo"), _T("varifyvalue"), m_editScore, m_strCardIniPath);

	m_editScore += _T("%");
	if (tem_fScore>=m_fPassValue)
	{
		m_editResult = _T("通过");
		::WritePrivateProfileString(_T("PersonInfo"), _T("ispass"), _T("1"), m_strCardIniPath);
	}
	else
	{
		m_editResult = _T("失败");
		::WritePrivateProfileString(_T("PersonInfo"), _T("ispass"), _T("0"), m_strCardIniPath);
	}
	
	UpdateData(FALSE);
	ExitFaceEngine();

	//将验证时间写入配置文件写入配置文件---------------------------------------------
	//获取读卡时间
	CString     tem_strFaceTime = _T("");
	SYSTEMTIME  tem_stDateTime;
	GetLocalTime(&tem_stDateTime);
	tem_strFaceTime.Format(_T("%d-%02d-%02d %02d:%02d:%02d"), tem_stDateTime.wYear, tem_stDateTime.wMonth, tem_stDateTime.wDay,
		tem_stDateTime.wHour, tem_stDateTime.wMinute, tem_stDateTime.wSecond);
	::WritePrivateProfileString(_T("PersonInfo"), _T("varifytime"), tem_strFaceTime, m_strCardIniPath);
	//写入Excel--------------------------------------------------------------------
	Self_Write2Excel(m_strCardIniPath, m_strInfoBuffer);

}


BOOL CUDSFaceID::GernerateBarcode(const char* szText, int len, const char* szOutPath)
{
	struct zint_symbol* symbol;
	int ret = 0;
	try
	{
		symbol = ZBarcode_Create();
		if (symbol != NULL)
		{
			symbol->scale     = 4;
			symbol->option_1  = 1;                  //容错级别
			symbol->option_2  = 1;                  //版本，决定图像大小
			symbol->symbology = BARCODE_QRCODE;
			symbol->output_options = 0;
			symbol->show_hrt  = 0;                   //可显示信息，如果设置为1，则需要设置text值
			symbol->input_mode= DATA_MODE;

			if (szOutPath)
			{
				memcpy(symbol->outfile, szOutPath, sizeof(symbol->outfile)-1);     //输出文件名
			}
			ret = ZBarcode_Encode(symbol, (unsigned char*)szText, len);            //编码
			ret = ZBarcode_Print(symbol,0);                                        //antate angle 旋转角度
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


void CUDSFaceID::Self_SaveCardImg(IDCardInfo2 info, CString prontimg, CString backimg, CString outimg)
{
	int        tem_nBackWidth  = 1580;    //背景纸的宽
	int        tem_nBackHeight = 2280;    //背景纸的高
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

	//1)、图像加载------------------------------------------------------
	CxImage    pImageFront, pImageBack;
	CxImage    pImageCard;

	pImageFront.Load(prontimg, CMAX_IMAGE_FORMATS);
	pImageBack.Load(backimg, CMAX_IMAGE_FORMATS);
	pImageCard.Load(tem_strImg, CMAX_IMAGE_FORMATS);
	pImageFront.Light(0, 5);    pImageFront.Erode(3);    pImageFront.UnsharpMask(); 
	pImageBack.Light(0, 5);    pImageBack.Erode(3);    pImageBack.UnsharpMask(); 

	//2)图像透明--------------------------------------------------------
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

	//3)图像合并---------------------------------------------------------
	pImageFront.Mix(pImageCard, CxImage::OpScreen, -656, -160, FALSE);       //原图复制，透明保留——可用

	//4)添加文字部分-----------------------------------------------------
	CxImage::CXTEXTINFO WMTxtInfo;  // 授权文字水印
	pImageFront.InitTextInfo( &WMTxtInfo );

	RGBQUAD   rgbTEXT = {0, 0, 0, 0};
	pImageFront.DrawString(0, 200, 124, tem_strName, rgbTEXT, _T("黑体"), 44, 400, 0, 0, false);
	pImageFront.DrawString(0, 200, 200, tem_strSex, rgbTEXT, _T("黑体"), 37, 400, 0, 0, false);
	pImageFront.DrawString(0, 420, 200, tem_strNation, rgbTEXT, _T("黑体"), 37, 400, 0, 0, false);
	pImageFront.DrawString(0, 200, 280, tem_strBirth_year, rgbTEXT, _T("黑体"), 40, 400, 0, 0, false);
	pImageFront.DrawString(0, 360, 280, tem_strBirth_month, rgbTEXT, _T("黑体"), 40, 400, 0, 0, false);
	pImageFront.DrawString(0, 460, 280, tem_strBirth_day, rgbTEXT, _T("黑体"), 40, 400, 0, 0, false);

	//每行最多显示11个中文字符
	int tem_nSize = tem_strAddress.GetLength();
	if (tem_nSize<=11)
	{
		pImageFront.DrawString(0, 200, 360, tem_strAddress, rgbTEXT, _T("黑体"), 37, 400, 0, 0, false);
	}
	else if (tem_nSize>11 && tem_nSize<=22)
	{
		CString tem_strFirst  = tem_strAddress.Mid(0, 11);
		pImageFront.DrawString(0, 200, 360, tem_strFirst, rgbTEXT, _T("黑体"), 37, 400, 0, 0, false);
		CString tem_strSecond = tem_strAddress.Mid(11);
		pImageFront.DrawString(0, 200, 415, tem_strSecond, rgbTEXT, _T("黑体"), 37, 400, 0, 0, false);
	}
	else if (tem_nSize>22 && tem_nSize<=33)
	{
		CString tem_strFirst  = tem_strAddress.Mid(0, 11);
		pImageFront.DrawString(0, 200, 360, tem_strFirst, rgbTEXT, _T("黑体"), 37, 400, 0, 0, false);
		CString tem_strSecond = tem_strAddress.Mid(11, 11);
		pImageFront.DrawString(0, 200, 415, tem_strSecond, rgbTEXT, _T("黑体"), 37, 400, 0, 0, false);
		CString tem_strThird  = tem_strAddress.Mid(22);
		pImageFront.DrawString(0, 200, 470, tem_strThird, rgbTEXT, _T("黑体"), 37, 400, 0, 0, false);
	}
	else
	{
		CString tem_strFirst  = tem_strAddress.Mid(0, 11);
		pImageFront.DrawString(0, 200, 360, tem_strFirst, rgbTEXT, _T("黑体"), 37, 400, 0, 0, false);
		CString tem_strSecond = tem_strAddress.Mid(11, 11);
		pImageFront.DrawString(0, 200, 415, tem_strSecond, rgbTEXT, _T("黑体"), 37, 400, 0, 0, false);
		CString tem_strThird  = tem_strAddress.Mid(22,11);
		pImageFront.DrawString(0, 200, 470, tem_strThird, rgbTEXT, _T("黑体"), 37, 400, 0, 0, false);
		CString tem_strFouth  = tem_strAddress.Mid(33);
		pImageFront.DrawString(0, 200, 525, tem_strFouth, rgbTEXT, _T("黑体"), 37, 400, 0, 0, false);

	}

	pImageFront.DrawString(0, 350, 565, tem_strID, rgbTEXT, _T("OCR-B 10 BT"), 50, 400, 0, 0, false);

	pImageBack.DrawString(0, 430, 485, tem_strOffice, rgbTEXT, _T("黑体"), 37, 200, 0, 0, false);
	pImageBack.DrawString(0, 430, 570, tem_strValidate, rgbTEXT, _T("黑体"), 38, 200, 0, 0, false);


	//双图合并
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

	//添加标题----------------------------------------------------------------------------------
	m_strCopyBT = _T("人证对比确认单");
	pImageMerge.DrawString(0, 500, 220, m_strCopyBT, rgbTEXT, _T("宋体"),90, 400, 0, 0, false);

	//添加二维码--------------------------------------------------------------------------------
//	m_strQRCode = _T("D:\\Documents\\UDSData\\身份证信息\\Image\\IMG_4297.JPG");

	m_strQRImgInfo     = m_stcIdInfo.name;
	m_strQRImgInfo    += m_stcIdInfo.sex;
	m_strQRImgInfo    += m_stcIdInfo.nation;
	m_strQRImgInfo    += m_stcIdInfo.birth;
	m_strQRImgInfo    += m_stcIdInfo.address;
	m_strQRImgInfo    += m_stcIdInfo.IDnumber;
	m_strQRImgInfo    += m_stcIdInfo.office;
	m_strQRImgInfo    += m_stcIdInfo.validate;
	m_strQRImgInfo    += _T("比对分值：");
	m_strQRImgInfo    += m_editScore;
	m_strQRImgInfo    += _T("比对结果：");
	m_strQRImgInfo    += m_editResult;
	m_strQRImgInfo    += _T("验证时间：");
	m_strQRImgInfo    += m_strVerifyTime;

	CStringA tem_straPath(m_strQRCode.GetBuffer(0));  
	m_strQRCode.ReleaseBuffer();  
	string   tem_sPath = tem_straPath.GetBuffer(0);  

	CStringA tem_straInfo(m_strQRImgInfo.GetBuffer(0));  
	m_strQRImgInfo.ReleaseBuffer();  
	string   tem_sInfo = tem_straInfo.GetBuffer(0); 

	GernerateBarcode(tem_sInfo.c_str(), 0, tem_sPath.c_str());

	CxImage    pImageQRCode;
	pImageQRCode.Load(m_strQRCode, CMAX_IMAGE_FORMATS);
	pImageQRCode.SetXDPI(200);
	pImageQRCode.SetYDPI(200);
	pImageQRCode.Resample(250, 250);
	tem_nOffsetX = 1000;
	tem_nOffsetY = tem_nBackHeight - 700;
	pImageMerge.MixFrom(pImageQRCode, tem_nOffsetX, tem_nOffsetY);


	//添加比对结果-------------------------------------------------------------------------------
	CString   tem_strScore = _T("比对分值：");
	tem_strScore += m_editScore;

	CString   tem_strResult= _T("比对结果：");
	tem_strResult+= m_editResult;

	pImageMerge.DrawString(0, 1000, 1000, tem_strScore, rgbTEXT, _T("宋体"),40, 400, 0, 0, false);
	pImageMerge.DrawString(0, 1000, 1100, tem_strResult, rgbTEXT, _T("宋体"),40, 400, 0, 0, false);

	//添加现场拍摄图像---------------------------------------------------------------------------
	CxImage    pImageFaceImg;
	pImageFaceImg.Load(g_strFaceImg, CMAX_IMAGE_FORMATS);
	int        tem_nNewWidth, tem_nNewHigh;
	if (pImageFaceImg.GetWidth()>pImageFaceImg.GetHeight())
	{
		tem_nNewWidth = 500;
		tem_nNewHigh  = (int)(tem_nNewWidth*pImageFaceImg.GetHeight()*1.0/pImageFaceImg.GetWidth()*1.0);
	} 
	else
	{
		tem_nNewHigh  = 500;
		tem_nNewWidth = (int)(tem_nNewHigh*pImageFaceImg.GetWidth()*1.0/pImageFaceImg.GetHeight()*1.0);
	}
	pImageFaceImg.Resample(tem_nNewWidth, tem_nNewHigh);
	pImageFaceImg.SetXDPI(200);
	pImageFaceImg.SetYDPI(200);

	tem_nOffsetX = 150;
	tem_nOffsetY = tem_nBackHeight - 2000;
	pImageMerge.MixFrom(pImageFaceImg, tem_nOffsetX, tem_nOffsetY);

	//验证时间+签字-------------------------------------------------------------------------------
	CString  tem_strVerifyTime = _T("验证时间：");
	tem_strVerifyTime += m_strVerifyTime;
	pImageMerge.DrawString(0, 700, 1800, tem_strVerifyTime, rgbTEXT, _T("宋体"),40, 400, 0, 0, false);

	CString  tem_strSignate    = _T("客户签字：");
	pImageMerge.DrawString(0, 700, 1900, tem_strSignate, rgbTEXT, _T("宋体"),40, 400, 0, 0, false);
	
	pImageMerge.Save(outimg, CXIMAGE_FORMAT_JPG);

	ShellExecute(NULL, _T("print"), outimg, NULL, NULL, SW_SHOWNORMAL);
}


/************************************
*           目录
* 1、读卡
* 2、拍照
* 3、比对
* 4、打印
* 5、退出
*
************************************/

//读卡---------------------------------------
void CUDSFaceID::OnBnClickedBtnReadcard2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strCardImgPath = Self_GetSystemTime(m_strPicBuffer);
	m_strCardImgPath = Self_ReadCard(m_strCardImgPath);
	if (m_strCardImgPath != _T(""))
	{
		Self_ShowImg(m_strCardImgPath, IDC_PIC_IDIMG);
	}
}


//拍照----------------------------------------
void CUDSFaceID::OnBnClickedBtnFacecap()
{
	// TODO: 在此添加控件通知处理程序代码
	::DeleteFile(g_strFaceImg);
	g_strFaceImg = _T("");
	::SendMessage(m_hSubWnd, WM_FACEID, 0, 0);

	Self_ShowImg(g_strFaceImg, IDC_PIC_CAPIMG);

}


//比对---------------------------------------
void CUDSFaceID::OnBnClickedBtnContrast()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_strCardImgPath.IsEmpty() || g_strFaceImg.IsEmpty())
	{
		m_StaInfo = _T("请检查现场图或身份证图像！");
		UpdateData(FALSE);
		return;
	}

	m_editScore  = _T("");
	m_editResult = _T("");
	UpdateData(FALSE);
	Self_FaceIDCompare(m_strCardImgPath, g_strFaceImg);
}


//打印---------------------------------------
void CUDSFaceID::OnBnClickedBtnIdprint()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_strCardImgPath.IsEmpty() || g_strFaceImg.IsEmpty())
	{
		m_StaInfo = _T("请检查现场图或身份证图像！");
		UpdateData(FALSE);
		return;
	}
	Self_SaveCardImg(m_stcIdInfo, m_strProntImg, m_strBackImg, m_strCopyImg);
}


//关闭---------------------------------------
void CUDSFaceID::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	::DeleteFile(m_strQRCode);
	::DeleteFile(m_strCardImgPath);
	::DeleteFile(g_strFaceImg);
	g_strFaceImg = _T("");

	CDialogEx::OnClose();
}

int CUDSFaceID::Self_Write2Excel(CString inipath, CString xlsdir)
{

	CString      tem_strExlPath = xlsdir;   //输出Excel路径
	CString      tem_strPath;               //ini+excel两个路径参数

	CString      tem_strExePath;
	TCHAR        tem_tcFilepath[MAX_PATH+1] = {0};
	GetModuleFileName(NULL, tem_tcFilepath, MAX_PATH);
	(_tcsrchr(tem_tcFilepath, _T('\\')))[1] = 0;

	tem_strExePath    = tem_tcFilepath;
	tem_strExePath   += _T("FaceToExcel.exe");   //配置文件路径


	tem_strExlPath += _T("\\");
	tem_strExlPath += _T("人证比对信息集.xls");


	tem_strPath.Format(_T("\"%s\" \"%s\""),inipath, tem_strExlPath);   //\"转义字符，\"=".用于在双引号之间，存在引号的情况，避免编译器出错

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
