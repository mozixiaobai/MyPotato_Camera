#pragma once
#define  WM_FACEID     WM_USER+1004

#include "resource.h"
#include "CTermbReader.h"  //�����֤����
#include "ximage.h"
#include "UDS_FaceCore.h"  //��֤�ȶ�
#include "Shellapi.h"
#include "zint.h"          //���ɶ�ά����


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

// CUDSFaceID �Ի���
class CUDSFaceID : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSFaceID)

public:
	CUDSFaceID(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDSFaceID();

// �Ի�������
	enum { IDD = IDD_DLG_FACEID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CTermbReader   m_iReadCard;
	IDCardInfo2    m_stcIdInfo;    //���֤��Ϣ�ṹ��

	BOOL           m_BFirst;

	CString        m_strName;
	CString        m_strSex;
	CString        m_strNation;
	CString        m_strBirth;
	CString        m_strAddress;
	CString        m_strID;
	CString        m_strOffice;
	CString        m_strValidity;
	CString        m_strCardImgPath;     //���֤ͼ��·��

	CString        m_strFilePath;
	CString        m_strCardIniPath;     //�����Ϣini�ļ�·��
	CString        m_strPicBuffer;       //���֤ͼ�񻺴�Ŀ¼
	CString        m_strFingerPath;      //���ָ֤�ƻ���Ŀ¼
	CString        m_strIniPath;         //�����ļ�·��
	
	CString        m_strInfoBuffer;      //���֤��������Ŀ¼

	CString        m_editNation;
	CString        m_editName;
	CString        m_editBirth;
	CString        m_editCardnum;
	CString        m_editOffice;
	CString        m_editSex;
	CString        m_editValidity;
	CString        m_editAddress;
	CString        m_StaInfo;             //���������Ϣ��ʾ


	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	
	CString SubGetMyDocument(void);
	CString Self_ReadCard(CString picpath);	
	void Self_ShowImg(CString imgpath, int ctrlID);
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnContrast();
	CString Self_GetSystemTime(CString dir);
	void Self_FaceIDCompare(CString idimg, CString faceimg);
	float         m_fPassValue;                  //�����ȶ�ͨ����׼ֵ
//	float         m_editScore;
	CString       m_editScore;
	CString       m_editResult;


	//�������֤������ͼ��
	CString       m_strProntImg;
	CString       m_strBackImg;
	CString       m_strCopyImg;                 //ȷ�ϵ�·��
	CString       m_strCopyBT;                  //�ļ����⣬�������ļ���ȡ
	CString       m_strQRCode;                  //��ά����·��
	CString       m_strVerifyTime;              //��֤ʱ��
	CString       m_strQRImgInfo;               //���������Ϣ
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
