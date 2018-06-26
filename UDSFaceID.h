#pragma once
#define  WM_FACEID     WM_USER+1004

#include "resource.h"
#include "CTermbReader.h"  //新身份证读卡
#include "ximage.h"
#include "UDS_FaceCore.h"  //人证比对
#include "Shellapi.h"
#include "zint.h"          //生成二维条码


typedef struct tagIDCardInfo2
{
	CString    imgpath;
	CString    name;
	CString    sex;
	CString    nation;
	CString    birth;
	CString    address;
	CString    IDnumber;
	CString    office;
	CString    validate;
}IDCardInfo2;

// CUDSFaceID 对话框
class CUDSFaceID : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSFaceID)

public:
	CUDSFaceID(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDSFaceID();

// 对话框数据
	enum { IDD = IDD_DLG_FACEID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CTermbReader   m_iReadCard;
	IDCardInfo2    m_stcIdInfo;    //身份证信息结构体

	BOOL           m_BFirst;

	CString        m_strName;
	CString        m_strSex;
	CString        m_strNation;
	CString        m_strBirth;
	CString        m_strAddress;
	CString        m_strID;
	CString        m_strOffice;
	CString        m_strValidity;
	CString        m_strCardImgPath;     //身份证图像路径

	CString        m_strFilePath;
	CString        m_strCardIniPath;     //身份信息ini文件路径
	CString        m_strPicBuffer;       //身份证图像缓存目录
	CString        m_strFingerPath;      //身份证指纹缓存目录
	CString        m_strIniPath;         //配置文件路径
	
	CString        m_strInfoBuffer;      //身份证读卡缓存目录

	CString        m_editNation;
	CString        m_editName;
	CString        m_editBirth;
	CString        m_editCardnum;
	CString        m_editOffice;
	CString        m_editSex;
	CString        m_editValidity;
	CString        m_editAddress;
	CString        m_StaInfo;             //读卡结果信息显示


	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	
	CString SubGetMyDocument(void);
	CString Self_ReadCard(CString picpath);	
	void Self_ShowImg(CString imgpath, int ctrlID);
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnContrast();
	CString Self_GetSystemTime(CString dir);
	void Self_FaceIDCompare(CString idimg, CString faceimg);
	float         m_fPassValue;                  //人脸比对通过基准值
//	float         m_editScore;
	CString       m_editScore;
	CString       m_editResult;


	//生成身份证正面面图像
	CString       m_strProntImg;
	CString       m_strBackImg;
	CString       m_strCopyImg;                 //确认单路径
	CString       m_strCopyBT;                  //文件标题，从配置文件读取
	CString       m_strQRCode;                  //二维码存放路径
	CString       m_strVerifyTime;              //验证时间
	CString       m_strQRImgInfo;               //条码包含信息
	void Self_SaveCardImg(IDCardInfo2 info, CString prontimg, CString backimg, CString outimg);
	afx_msg void OnBnClickedBtnIdprint();	
	BOOL GernerateBarcode(const char* szText, int len , const char* szOutPath);
	afx_msg void OnBnClickedBtnFacecap();
	afx_msg void OnBnClickedBtnReadcard2();
	void Self_ClearImg(int ctrlID);
	CStatic m_conIDImg;
	HWND    m_hSubWnd;
	int Self_Write2Excel(CString inipath, CString xlsdir);
};
