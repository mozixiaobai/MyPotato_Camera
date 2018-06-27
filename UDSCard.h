#pragma once
#include "resource.h"
#include "shellapi.h"       //shellͷ�ļ�
#include "ximage.h"
//#include "CardReader.h"  //ԭ���֤����
#include "CTermbReader.h"  //�����֤����
#include "PngButton.h"
#include "zint.h"          //���ɶ�ά����
#include <vector>



//�����߳�
DWORD WINAPI ThreadProc(LPVOID lpParam);
struct ThreadInfo
{
	HWND     hWnd;      //���ھ�����ڷ�����Ϣ
	int      nTime;     //��ʱʱ������λms
	CString  strInfo;   //������Ϣ
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



// CUDSCard �Ի���

class CUDSCard : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSCard)

public:
	CUDSCard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDSCard();

// �Ի�������
	enum { IDD = IDD_DLG_CARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	CCardReader*    m_iSubCard;  //�ض�
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
	CString        m_strCardIniPath;     //�����Ϣini�ļ�·��
	CString        m_strInfoBuffer;      //���֤��������Ŀ¼
	CString        m_strPicBuffer;       //���֤ͼ�񻺴�Ŀ¼

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
	BOOL       m_BFirst;  //�״δ���ʾͼ��
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString       m_strIniPath;
	CPngButton m_btnSave;
	CPngButton m_btnRecard;
	CPngButton m_btnExit;
	CToolTipCtrl    m_tipCardInfo;  //��ť������ʾ
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
	HANDLE      hThreadHandle;      //�洢�߳̾��
	DWORD       dwThreadID;         //Ѱ���߳�ID
	ThreadInfo  stcThreadInfo;      //�洢�̲߳���
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_StaInfo;

	IDCardInfo   m_stcIdInfo;    //���֤��Ϣ�ṹ��
	void Self_SaveCardCopy(IDCardInfo info, CString prontimg, CString backimg, CString outimg);
	void Self_ShowCopyImg(CString img);
	void Self_ClearImg(void);
	afx_msg void OnBnClickedChkSave();
	afx_msg void OnDblclkStaCopyimg();
	CStatic m_conCopyImg;
	CStatic m_conCardImg;

	CString    m_strProntImg;    //���֤����ģ��
	CString    m_strBackImg;     //���֤����ģ��
	CString    m_strCopyImg;     //���֤��ӡ��
	int        m_nReadTime;      //�Զ��������ʱ��
	BOOL       m_BAutoRead;      //�Զ�������ʶλ

	BOOL       m_BSaveCopy;     //���渴ӡ��
	CSliderCtrl m_conPeriod;
	afx_msg void OnCustomdrawSlidPeriod(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnFinger();
	CString    m_strFingerPath;
	//�ɼ�ָ��
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
	int        m_nFingerNum;       //���֤����ָ�Ƹ���
	int        m_nFigerIndex;      //��ָ����
	CString    m_strFingerIndex;   //��λ�ĸ���ָ
	float Self_ExMatchFeatures(CString imgpath, CString datpath);
	void Self_SetCtrlState(int mode);
	CPngButton m_btnReadFinger;
	CString    m_strIniPath2;

	//���ɱȶԽ��ȷ�ϵ�---------------------------------------------
	CString      m_strResultImg;                 //ȷ�ϵ�·��
	CString      m_strQRCode;                    //��ά����·��
	CString      m_strQRImgInfo;                 //���������Ϣ
	CString      m_strVerifyTime;                //��֤ʱ��
	CString      m_strScore;                     //�ȶԷ�ֵ
	CString      m_strResult;                    //�ȶԽ��
	CString      m_strFingerImg;                 //ָ��ͼ���·��
	CString      m_strCopyBT;                    //������
	float        m_fPassValue;                   //ָ��ʶ��ͨ����׼ֵ
	
	std::vector<CString> m_vcFingerImg;          //ָ��ͼ�񻺴�vector
	std::vector<CString> m_vcFaceImg;            //���֤ͷ�񻺴�vector
	std::vector<CString> m_vcQRCodeImg;          //��ά�뻺��vector

	afx_msg void OnBnClickedBtnPrintdoc();
	void Self_SaveResultCopy(IDCardInfo info, CString prontimg, CString backimg, CString outimg);

	BOOL GernerateBarcode(const char* szText, int len , const char* szOutPath);
	CPngButton m_btnPrint;
};
