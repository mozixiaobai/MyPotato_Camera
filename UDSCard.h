#pragma once
#include "resource.h"
#include "shellapi.h"       //shell头文件
#include "ximage.h"
//#include "CardReader.h"  //原身份证读卡
#include "CTermbReader.h"  //新身份证读卡
#include "PngButton.h"
#include "zint.h"          //生成二维条码
#include <vector>



//创建线程
DWORD WINAPI ThreadProc(LPVOID lpParam);
struct ThreadInfo
{
	HWND     hWnd;      //窗口句柄用于发送消息
	int      nTime;     //定时时长，单位ms
	CString  strInfo;   //附加消息
};


typedef struct tagIDCardInfo
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
}IDCardInfo;



// CUDSCard 对话框

class CUDSCard : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSCard)

public:
	CUDSCard(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDSCard();

// 对话框数据
	enum { IDD = IDD_DLG_CARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CCardReader*    m_iSubCard;  //重读
	CTermbReader*   m_iSubCard;

	CString        m_strName;
	CString        m_strSex;
	CString        m_strNation;
	CString        m_strBirth;
	CString        m_strAddress;
	CString        m_strID;
	CString        m_strOffice;
	CString        m_strValidity;
	CString        m_strFilePath;
	CString        m_strCardIniPath;     //身份信息ini文件路径
	CString        m_strInfoBuffer;      //身份证读卡缓存目录
	CString        m_strPicBuffer;       //身份证图像缓存目录

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	int Write2Excel(CString inipath);
	CString SelectPath(void);
	void ShowPicture(CString imgpath);
	CDC*       pDc;
	CDC        imageDC;
	afx_msg void OnPaint();
	BOOL       m_BFirst;  //首次打开显示图像
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString       m_strIniPath;
	CPngButton m_btnSave;
	CPngButton m_btnRecard;
	CPngButton m_btnExit;
	CToolTipCtrl    m_tipCardInfo;  //按钮文字提示
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnCardsave();
	CString Save2File(void);
	CString SubGetMyDocument(void);
	CString Self_ReadCard(CString picpath);
	CString m_editName;
	CString m_editSex;
	CString m_editNation;
	CString m_editBirth;
	CString m_editCardnum;
	CString m_editOffice;
	CString m_editValidity;
	CString m_editAddress;
	int Self_Write2Excel(CString inipath, CString xlsdir);
	CString Self_GetSystemTime(CString dir);
	afx_msg void OnClickedChkAutocard();
private:
	HANDLE      hThreadHandle;      //存储线程句柄
	DWORD       dwThreadID;         //寻出线程ID
	ThreadInfo  stcThreadInfo;      //存储线程参数
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_StaInfo;

	IDCardInfo   m_stcIdInfo;    //身份证信息结构体
	void Self_SaveCardCopy(IDCardInfo info, CString prontimg, CString backimg, CString outimg);
	void Self_ShowCopyImg(CString img);
	void Self_ClearImg(void);
	afx_msg void OnBnClickedChkSave();
	afx_msg void OnDblclkStaCopyimg();
	CStatic m_conCopyImg;
	CStatic m_conCardImg;

	CString    m_strProntImg;    //身份证正面模板
	CString    m_strBackImg;     //身份证背面模板
	CString    m_strCopyImg;     //身份证复印件
	int        m_nReadTime;      //自动读卡间隔时间
	BOOL       m_BAutoRead;      //自动读卡标识位

	BOOL       m_BSaveCopy;     //保存复印件
	CSliderCtrl m_conPeriod;
	afx_msg void OnCustomdrawSlidPeriod(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnFinger();
	CString    m_strFingerPath;
	//采集指纹
	int        m_nOriX;
	int        m_nOriY;
	int        m_nWidth;
	int        m_nHeight;
	CString Self_ReadFigerPrint(CString imgpath);
	void FPBmpDataToBmp(BYTE* FPBmpData, DWORD dataLen, char* bmpFileName);
	int WriteHead(unsigned char* Output, unsigned char* Input, int nWidth, int nHeight);
	void Self_ShowFingerImg(CString img);
	void Self_ExtractFeatures(CString imgpath);
	void Self_MatchFeatures(CString datpath);
	int        m_nFingerNum;       //身份证包含指纹个数
	int        m_nFigerIndex;      //手指索引
	CString    m_strFingerIndex;   //定位哪根手指
	float Self_ExMatchFeatures(CString imgpath, CString datpath);
	void Self_SetCtrlState(int mode);
	CPngButton m_btnReadFinger;
	CString    m_strIniPath2;

	//生成比对结果确认单---------------------------------------------
	CString      m_strResultImg;                 //确认单路径
	CString      m_strQRCode;                    //二维码存放路径
	CString      m_strQRImgInfo;                 //条码包含信息
	CString      m_strVerifyTime;                //验证时间
	CString      m_strScore;                     //比对分值
	CString      m_strResult;                    //比对结果
	CString      m_strFingerImg;                 //指纹图像的路径
	CString      m_strCopyBT;                    //表单标题
	float        m_fPassValue;                   //指纹识别通过基准值
	
	std::vector<CString> m_vcFingerImg;          //指纹图像缓存vector
	std::vector<CString> m_vcFaceImg;            //身份证头像缓存vector
	std::vector<CString> m_vcQRCodeImg;          //二维码缓存vector

	afx_msg void OnBnClickedBtnPrintdoc();
	void Self_SaveResultCopy(IDCardInfo info, CString prontimg, CString backimg, CString outimg);

	BOOL GernerateBarcode(const char* szText, int len , const char* szOutPath);
	CPngButton m_btnPrint;
};
