
// UDS SmartCamera v1.0.0Dlg.h : 头文件
//
#pragma once
#define  WM_SWITCH     WM_USER+1001
#define  WM_SUBSWITCH  WM_USER+1002
#define  WM_ADVCESET   WM_USER+1003
#define  WM_FACEID     WM_USER+1004

#include "UDSChildNor.h"
#include "UDSChildAdv.h"
#include "UDSChildSet.h"
#include "uds_videoctrl1.h"
#include "shellapi.h"   //shell头文件
#include <vector>       //缩略图添加
#include "ximage.h"
#include "BASE64_API.h"
#include "Base64.h"
#include "PngButton.h"
#include <windows.h>
#include <atlimage.h>
#include "UDSChildDcm.h"  //输入dcm输入信息
#include "IMAGEAndDCM.h"  //JPG转DCM库
#include "UDSDeleteitem.h"
#include "HSMenu.h"     //用于菜单自绘
#include "HSMenuPro.h"
#include "HSMenuX.h"
#include <algorithm>     //排序函数
//#include "CardReader.h"     //原身份证读卡   
#include "UDSCard.h"
#include "pdflib.h"     //pdf lib
#include "pdflib.hpp"
#include "Dbt.h"        //检测USB口的变动情况
#include "MMsystem.h"   //延时函数
#include "UDSFront.h"
#include "allheaders.h"  //ocr文字识别
#include "baseapi.h"     //ocr文字识别
#include <locale>         //向TXT中写入中文
#include "UDSFaceID.h"

// #include "Uxtheme.h"
// #pragma comment(lib, "Uxtheme.lib")

using namespace std;
using namespace pdflib;





// CUDSSmartCamerav100Dlg 对话框
class CUDSSmartCamerav100Dlg : public CDialogEx 
{
// 构造
public:
	CUDSSmartCamerav100Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_UDSSMARTCAMERAV100_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CUDSChildNor   m_iChildNor;
	CUDSChildAdv   m_iChildAdv;
	CUDSChildSet   m_iChildSet;
	CUDSChildDcm   m_iChildDcm;
	CUDSDeleteitem m_iDeleteTip;
	CUDSCard       m_iChildCard;
	CTabCtrl m_conTab;
	afx_msg void OnSelchangeTabSet(NMHDR *pNMHDR, LRESULT *pResult);
//-	CStatic m_conStaFram;
	afx_msg void OnBnClickedBtnTest2();
protected:
	afx_msg LRESULT OnSwitchItem(WPARAM wParam, LPARAM lParam);
public:
//	CString  m_strDefaultPath;   //默认路径
	CString  m_strDllPath;       //dll所在文件夹
	int   m_nLastUsedScanner;    //上次使用拍摄仪的索引
	int   m_nLastUsedResolu;     //上次使用分辨率索引
	int   m_nLastUsedFile;       //上次使用的文件类型
	int   m_nLastUsedColor;      //上次使用的色彩类型
	int   m_nImageCount;         //暂时采用计数命名,用于可改名的计数统计
	int   m_nImageCountOther;    //用于不可改名的，如条码、自动连拍
	int   m_nNamingMode;         //命名方式
	int   m_nDeviceNumber;       //设备数量
	CString  m_strFileFormat;    //文件格式
	BOOL  m_BAutoExp;            //自动曝光
	BOOL  m_BAutoCrop;           //自动裁切
	BOOL  m_BManualCrop;         //手动裁切
	int   m_nManualVaule;        //保存手动曝光的设定值
	afx_msg void OnBnClickedBtnCapature();
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnLrotate();
	afx_msg void OnBnClickedBtnRrotate();
	//以上为使用DLL过程中使用的一些变量
	//下面将DLL改为OCX控件增加的一些变量
//	CUds_videoctrl1 m_conVideoOcx;
	long            m_lReturnCode;       //函数返回码
//	int             m_nIndexRes;         //分辨率索引值
	CStringArray    m_straDeviceName;    //保存设备名称
	int             m_nLastSubScan;      //保存副头索引
	int             m_nLastSubRes;       //保存副头分辨率
	int             m_nRotate;           //计算旋转方向
	int             m_nJpegQulity;       //保存JPEG质量
	int             m_nAutoSense;        //保存自动连拍灵敏度
	int             m_nVideoWidth;       //视频宽
	int             m_nVideoHeight;      //视频高
	int             m_nVideoBit;         //视频比特率,预留参数
	int             m_nVideoFPS;         //视频帧率，预留参数

	int             m_nExpValue;         //手动曝光值
	int             m_nBriValue;         //手动亮度值

	int             m_nCardWidth;        //身份证200dpi对应宽度像素
	int             m_nCardHeight;       //身份证200dpi对应高度像素
	int             m_nA4Width;          //A4纸200dpi宽
	int             m_nA4Height;         //A4纸200dpi高
	

	BOOL            m_BPDFCpt;           //PDF拍照
	BOOL            m_BBase64Cpt;        //Base64拍照
	BOOL            m_BDcmCpt;           //DCM拍照
	BOOL            m_BOfdCpt;           //OFD拍照
	int             m_nOtherCpt;          //tga、pcx、ras
	BOOL            m_BMerge;            //与主头合并
	int             m_nMergeMode;        //合并方式
	int             m_nMergeLocation;    //外部坐标   
	CString         m_strPreName;        //保存Set发送的前缀名
	int             m_nThumbWidth;       //缩略图宽
	int             m_nThumbHeight;      //缩略图高
	CString         m_strIniPath;        //Ini文件路径
	BOOL            m_BShowInfo;         //显示视频信息
	BOOL            m_BSoundOpen;        //拍照声音

	CString         m_strHttp;           //HTTP上传地址
	CString         m_strFtpIP;          //FTP上传地址
	CString         m_strFtpDir;         //FTP上传目录
	CString         m_strFtpUserName;       //FTP用户名
	CString         m_strFtpPassWord;       //FTP密码
	CString         m_strFtpPort;        //FTP上传端口
	
 protected:
	afx_msg LRESULT OnSubswitch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAdvceset(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedBtnCapbar();
	afx_msg void OnBnClickedBtnCap2side();
	afx_msg void OnBnClickedBtnCapgoon();
	DECLARE_EVENTSINK_MAP()
	void GetBarcodeStringUdsVideoctrl1(LPCTSTR Barcode);
	void GetAutoCapFileNameUdsVideoctrl1(LPCTSTR fileName);
	void DeviceChangedUdsVideoctrl1(LPCTSTR changeType, LPCTSTR deviceName);
	CString NamingFile(int namecode);
	afx_msg void OnBnClickedBtnBrows();
	CListCtrl m_conListCtrl;
	CImageList      m_imagelist;
	std::vector<CString> m_vcFileName;   //文件名
	std::vector<CString> m_vcWholeName;  //用于ListCtrl显示的路径+文件名
	std::vector<CString> m_vcBussName;   //用于处理的路径+文件名，PDF+图像+Base64...
	BOOL ThumbaiList(int thumbwidth, int thumbheight);
	int GetTypeFromFileName(LPCTSTR pstr);
	void LoadIniFile(void);
	afx_msg void OnDblclkListImage(NMHDR *pNMHDR, LRESULT *pResult);
	CString   m_strUrl;
	CString ShowPDF(CString pdfpath);
	int      m_nPDfimg;                //解析出来的PDF 图像索引，从10001开始计数
	BOOL WINAPI GhostPdf2Image(char* pdfpath, char* imgpath, char* resolution, CString gsdll);
	CString Base642Img(CString txtpath);
	CString     m_strShowPath;         //用于下栏路径显示
	afx_msg void OnDblclkStaInfopath();

	BOOL           m_BDownBk;       //首次OnPaint加载背景
	CToolTipCtrl   m_tipInfo;       //用于按钮文字提示
	CPngButton     m_btnCapture;
	CPngButton     m_btnBar;
	CPngButton     m_btnSides;
	CPngButton     m_btnExit;
	CPngButton     m_btnBrows;
	CPngButton     m_btnCapture2;
	CPngButton     m_conCard;
	CPngButton     m_btnCopyCard;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CPngButton m_btnRotateL;
	CPngButton m_btnRotateR;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CImage Image;
	afx_msg void OnBnClickedBtnMin();
	afx_msg void OnBnClickedBtnWeb();
	afx_msg void OnBnClickedBtnDeclear();
	CPngButton m_conMin;
	CPngButton m_conWeb;
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnSavepath();
	CPngButton m_btnSlcPath;
	BOOL       m_BFront;  //双面合并，标记正面已拍照
	std::vector<CString>   m_vcDeleteBuffer;   //用于删除pdf、base64、dcm文档拍照时产生的缓存图像
	std::vector<CString>   m_vcOcrBuffer;      //用于删除一键word，excel产生的txtbuffer文件
	
	afx_msg void OnDeleteitemListImage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickListImage(NMHDR *pNMHDR, LRESULT *pResult);
	int          m_nSlctItem;   //选中的缩略图索引
	CString      m_strVideoPath;   //用于录像结束时，显示录像文件路径
	BOOL         m_BParentVideo;   //使用主头录像
	afx_msg void OnRclickListImage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCopyIt();
	afx_msg void OnDeleteIt();
	afx_msg void OnRename();
	afx_msg void OnProperty();
	BOOL CreateHSMenu(void);
	CHSMenu     m_menuRightClick; //右键菜单
	std::vector<int>  m_vcCtrlInex;  //多选索引
	std::vector<CString>  m_vcCtrlBPath;   //非图像文件和图像文件路径，缓存图退出时会被清理
	afx_msg void OnHoverListImage(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL CopyFiles2Clipboard(std::vector<CString> const& vecFiles);
	CEdit*    m_conRename;      //重命名时可编辑框
	int       m_nLastSlcFile;   //用于重命名多个文件时保存最后一个索引
	CPngButton m_btnMax;
	BOOL     m_BMaxDlg;         //窗口最大化标识
	CRect    m_rcRectSrc;        //最初的客户端区域大小
	CRect    m_rcBT, m_rcMax, m_rcMin, m_rcExit, m_rcCamera, m_rcAutoCamera, m_rcBarCamera, m_rcSideCamera, m_rcBrows, m_rcFaceID, m_rcCard, m_rcCopyCard;
	CRect    m_rcTab, m_rcCtrl, m_rcList;
	CRect    m_rcStaCount, m_rcStaPage, m_rcStaNumber, m_rcNowPath, m_rcShowPath, m_rcZoomIn, m_rcZoomOut, m_rcRecover, m_rcLRotate, m_rcRRotate, m_rcChange, m_rcImageInfo;
	int      m_nNamingCount;   //命名计数，用于更换命名方式后，从0开始计数
	afx_msg void OnBnClickedBtnReadcard();

//	CCardReader*   m_iCard;
	CString        m_strCardName;
	CString        m_strCardSex;
	CString        m_strCardNation;
	CString        m_strCardBirth;
	CString        m_strCardAddress;
	CString        m_strCardID;
	CString        m_strCardOffice;
	CString        m_strCardValidity;
	BOOL ReadCard(void);
	BOOL           m_BSpaceDown;  //用于区分按键响应，按下与弹起
	
	int ShowImageSize(CString imagepath);
	CString m_staImageSize;
	CRect    m_rcImageSize;
	CString GetMyDocument(void);
//	afx_msg void OnItemclickListImage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBeginlabeleditListImage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEndlabeleditListImage(NMHDR *pNMHDR, LRESULT *pResult);
	CString      m_strBufferPath;
	CString GetThumbPath(CString wholeimage, CString imagename);
	BOOL GetSystemInfo(void);
	int    m_nScreenWidth, m_nScreenHeight;
	BOOL      m_BCamera200;   //200W设备标志位
	BOOL      m_BCamera500;   //500W设备标志位
	BOOL      m_BCamera800;   //800W设备标志位
	BOOL      m_BCamera1200;  //1200W设备标志位
	BOOL      m_BCamera1300;  //1300W设备标识位
	BOOL      m_BCameraTo1500;
	BOOL      m_BGS1600;      //GS1600 1300->1600插值
	CString   m_strGS16_PID;
	CString   m_strGS16_VID;

	CString   m_strPID200;
	CString   m_strVID200;
	CString   m_strPID500;
	CString   m_strVID500;
	CString   m_strPID800;    //指定800W设备PID信息
	CString   m_strVID800;    //指定800W设备VID信息
	CString   m_strPID800b;   //800W样机
	CString   m_strVID800b;
	CString   m_strPID800GS;    //GS1000
	CString   m_strVID800GS;    //GS1000
	CString   m_strPID1300;
	CString   m_strVID1300;
	CString   m_strPID1200;   //指定1200W设备PID信息
	CString   m_strVID1200;   //指定1200W设备VID信息
	CString   m_strPIDTo1500; //1221插值到1500W
	CString   m_strVIDTo1500;

	CString   m_strPID800Un;    //0425不知道机器型号
	CString   m_strVID800Un;    //0425不知道机器型号

	// 图像插值
	CString InterPolateImage(CString srcImage, CString dsImage, int index); //index = 0: 800->1000; index=1:1200->1600
	CString GeneratePDF(CString srcImg, CString dstImg);
	CString GenerateBase64(CString srcImg, CString dstImg);
	int GetmaxResoindex(void);
	int      m_nInterpolateReso;      //插值分辨率对应的索引值
	int      m_nInterpolateSubReso;   //副头插值分辨率对应的索引值
	afx_msg void OnBnClickedBtnZoomin();
	afx_msg void OnBnClickedBtnZoomout();
	afx_msg void OnBnClickedBtnRecover();
	CPngButton m_btnZoomIn;
	CPngButton m_btnZoomOut;
	CPngButton m_btnRecovery;
protected:
	afx_msg LRESULT OnDevicechange(WPARAM wParam, LPARAM lParam);
public:
	void UpdateDevices(int number);
	// 精度——毫秒
	void TimeDelayed(int time_ms);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	int GetsubmaResoindex(void);
	afx_msg void OnBnClickedBtnCardcopy();



	//1102身份证复印显示部分
	BOOL            m_BCardDlg;    //身份证窗口显示标识位
	CString         m_strFrontName; //身份证图像名称
	CRect           m_rcOCX;
	CUDSFront       m_dlgFront;
	afx_msg void OnMove(int x, int y);
	
	// 检查设备名是否重复，在XP系统下Camera均为USB视频设备
	int      m_nLastRotate;
	int      m_nSameCameraLast;     //避免有3个及3个以上设备时出现重名
	std::vector<CString> m_vcCameraName;
	CString CheckCameraName(CString cameraname);
	int      m_nMainOpen;        //主头开启标识位
	int      m_nAudioIndex;      //默认音频设备索引
	CUds_videoctrl1 m_conVideoOcx;
	CString  m_strVideoFormat;   //视频格式
	int GetDiyResoindex(int diyvalue);
	afx_msg void On32775Word();
	afx_msg void On32776Excel();
	void Self_SetBriValue(void);
	void Self_Write2Office(CString txtpath, CString officepath);
	void Self_OcrRecognize(CString imgpath, CString txtpath);

	//OCR文字识别
	tesseract::TessBaseAPI *m_api;
	Pix *m_image;
	BOOL                    m_BOcrOpened;      //OCR初始化成功标志位
	wchar_t* Utf_8ToUnicode(char* szU8);
	char* UnicodeToAnsi(const wchar_t* szStr);

	//指纹识别
	CString   m_strFingerDoc;   
	afx_msg void On32777AutoRotate();
	void Self_AutoRotate(CString imgpath);
	afx_msg void OnBnClickedBtnFaceid();

	//人证比对
	CString      m_strFaceDoc;
	CUDSFaceID   m_dlgFaceID;

	//自动旋转和智能优化
	BOOL         m_BAutoRotate;
	BOOL         m_BOptimize; 
	// 自动旋转
	int Self_RecognizeOrit(CString imgpath, BOOL on_off);
	CPngButton m_btnCompare;
	int          m_nOptBright;          //文档优化亮度
	int          m_nOptContrast;        //文档优化对比度
	int Self_DocOptimize(CxImage img, CString imgpath, BOOL on_off, int bright, int contrast);
protected:
	afx_msg LRESULT OnFaceid(WPARAM wParam, LPARAM lParam);
public:
	int Self_DocOptimize2(CxImage img, CString imgpath, bool on_off);
	float Self_GetColorPercentage(CxImage img, bool on_off);
	float m_fColorPercentage;
	int Self_RecognizeOrit2(CString imgpath, CString thumbpath, bool on_off);
	int   m_nAutoRotateMode;       //自动旋转的方法， 0-谷歌，1-机器学习
	void Self_ReplaceImage(int thumbwidth, int thumbheight, int item);
	afx_msg void On32778RightRotateL();
	afx_msg void On32779RightRotateR();
	CString GenerateOFD(CString srcImg, CString dstImg);
	CString GenerateOthers(CString srcImg, CString dstImg, int mode);
	int m_nMainCodec; //主头视频编码
	int m_nSubCodec; //副头视频编码
};
