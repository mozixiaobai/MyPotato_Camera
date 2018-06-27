
// UDS SmartCamera v1.0.0Dlg.h : ͷ�ļ�
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
#include "shellapi.h"   //shellͷ�ļ�
#include <vector>       //����ͼ���
#include "ximage.h"
#include "BASE64_API.h"
#include "Base64.h"
#include "PngButton.h"
#include <windows.h>
#include <atlimage.h>
#include "UDSChildDcm.h"  //����dcm������Ϣ
#include "IMAGEAndDCM.h"  //JPGתDCM��
#include "UDSDeleteitem.h"
#include "HSMenu.h"     //���ڲ˵��Ի�
#include "HSMenuPro.h"
#include "HSMenuX.h"
#include <algorithm>     //������
//#include "CardReader.h"     //ԭ���֤����   
#include "UDSCard.h"
#include "pdflib.h"     //pdf lib
#include "pdflib.hpp"
#include "Dbt.h"        //���USB�ڵı䶯���
#include "MMsystem.h"   //��ʱ����
#include "UDSFront.h"
#include "allheaders.h"  //ocr����ʶ��
#include "baseapi.h"     //ocr����ʶ��
#include <locale>         //��TXT��д������
#include "UDSFaceID.h"

// #include "Uxtheme.h"
// #pragma comment(lib, "Uxtheme.lib")

using namespace std;
using namespace pdflib;





// CUDSSmartCamerav100Dlg �Ի���
class CUDSSmartCamerav100Dlg : public CDialogEx 
{
// ����
public:
	CUDSSmartCamerav100Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UDSSMARTCAMERAV100_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
//	CString  m_strDefaultPath;   //Ĭ��·��
	CString  m_strDllPath;       //dll�����ļ���
	int   m_nLastUsedScanner;    //�ϴ�ʹ�������ǵ�����
	int   m_nLastUsedResolu;     //�ϴ�ʹ�÷ֱ�������
	int   m_nLastUsedFile;       //�ϴ�ʹ�õ��ļ�����
	int   m_nLastUsedColor;      //�ϴ�ʹ�õ�ɫ������
	int   m_nImageCount;         //��ʱ���ü�������,���ڿɸ����ļ���ͳ��
	int   m_nImageCountOther;    //���ڲ��ɸ����ģ������롢�Զ�����
	int   m_nNamingMode;         //������ʽ
	int   m_nDeviceNumber;       //�豸����
	CString  m_strFileFormat;    //�ļ���ʽ
	BOOL  m_BAutoExp;            //�Զ��ع�
	BOOL  m_BAutoCrop;           //�Զ�����
	BOOL  m_BManualCrop;         //�ֶ�����
	int   m_nManualVaule;        //�����ֶ��ع���趨ֵ
	afx_msg void OnBnClickedBtnCapature();
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnLrotate();
	afx_msg void OnBnClickedBtnRrotate();
	//����Ϊʹ��DLL������ʹ�õ�һЩ����
	//���潫DLL��ΪOCX�ؼ����ӵ�һЩ����
//	CUds_videoctrl1 m_conVideoOcx;
	long            m_lReturnCode;       //����������
//	int             m_nIndexRes;         //�ֱ�������ֵ
	CStringArray    m_straDeviceName;    //�����豸����
	int             m_nLastSubScan;      //���渱ͷ����
	int             m_nLastSubRes;       //���渱ͷ�ֱ���
	int             m_nRotate;           //������ת����
	int             m_nJpegQulity;       //����JPEG����
	int             m_nAutoSense;        //�����Զ�����������
	int             m_nVideoWidth;       //��Ƶ��
	int             m_nVideoHeight;      //��Ƶ��
	int             m_nVideoBit;         //��Ƶ������,Ԥ������
	int             m_nVideoFPS;         //��Ƶ֡�ʣ�Ԥ������

	int             m_nExpValue;         //�ֶ��ع�ֵ
	int             m_nBriValue;         //�ֶ�����ֵ

	int             m_nCardWidth;        //���֤200dpi��Ӧ�������
	int             m_nCardHeight;       //���֤200dpi��Ӧ�߶�����
	int             m_nA4Width;          //A4ֽ200dpi��
	int             m_nA4Height;         //A4ֽ200dpi��
	

	BOOL            m_BPDFCpt;           //PDF����
	BOOL            m_BBase64Cpt;        //Base64����
	BOOL            m_BDcmCpt;           //DCM����
	BOOL            m_BOfdCpt;           //OFD����
	int             m_nOtherCpt;          //tga��pcx��ras
	BOOL            m_BMerge;            //����ͷ�ϲ�
	int             m_nMergeMode;        //�ϲ���ʽ
	int             m_nMergeLocation;    //�ⲿ����   
	CString         m_strPreName;        //����Set���͵�ǰ׺��
	int             m_nThumbWidth;       //����ͼ��
	int             m_nThumbHeight;      //����ͼ��
	CString         m_strIniPath;        //Ini�ļ�·��
	BOOL            m_BShowInfo;         //��ʾ��Ƶ��Ϣ
	BOOL            m_BSoundOpen;        //��������

	CString         m_strHttp;           //HTTP�ϴ���ַ
	CString         m_strFtpIP;          //FTP�ϴ���ַ
	CString         m_strFtpDir;         //FTP�ϴ�Ŀ¼
	CString         m_strFtpUserName;       //FTP�û���
	CString         m_strFtpPassWord;       //FTP����
	CString         m_strFtpPort;        //FTP�ϴ��˿�
	
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
	std::vector<CString> m_vcFileName;   //�ļ���
	std::vector<CString> m_vcWholeName;  //����ListCtrl��ʾ��·��+�ļ���
	std::vector<CString> m_vcBussName;   //���ڴ����·��+�ļ�����PDF+ͼ��+Base64...
	BOOL ThumbaiList(int thumbwidth, int thumbheight);
	int GetTypeFromFileName(LPCTSTR pstr);
	void LoadIniFile(void);
	afx_msg void OnDblclkListImage(NMHDR *pNMHDR, LRESULT *pResult);
	CString   m_strUrl;
	CString ShowPDF(CString pdfpath);
	int      m_nPDfimg;                //����������PDF ͼ����������10001��ʼ����
	BOOL WINAPI GhostPdf2Image(char* pdfpath, char* imgpath, char* resolution, CString gsdll);
	CString Base642Img(CString txtpath);
	CString     m_strShowPath;         //��������·����ʾ
	afx_msg void OnDblclkStaInfopath();

	BOOL           m_BDownBk;       //�״�OnPaint���ر���
	CToolTipCtrl   m_tipInfo;       //���ڰ�ť������ʾ
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
	BOOL       m_BFront;  //˫��ϲ����������������
	std::vector<CString>   m_vcDeleteBuffer;   //����ɾ��pdf��base64��dcm�ĵ�����ʱ�����Ļ���ͼ��
	std::vector<CString>   m_vcOcrBuffer;      //����ɾ��һ��word��excel������txtbuffer�ļ�
	
	afx_msg void OnDeleteitemListImage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickListImage(NMHDR *pNMHDR, LRESULT *pResult);
	int          m_nSlctItem;   //ѡ�е�����ͼ����
	CString      m_strVideoPath;   //����¼�����ʱ����ʾ¼���ļ�·��
	BOOL         m_BParentVideo;   //ʹ����ͷ¼��
	afx_msg void OnRclickListImage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCopyIt();
	afx_msg void OnDeleteIt();
	afx_msg void OnRename();
	afx_msg void OnProperty();
	BOOL CreateHSMenu(void);
	CHSMenu     m_menuRightClick; //�Ҽ��˵�
	std::vector<int>  m_vcCtrlInex;  //��ѡ����
	std::vector<CString>  m_vcCtrlBPath;   //��ͼ���ļ���ͼ���ļ�·��������ͼ�˳�ʱ�ᱻ����
	afx_msg void OnHoverListImage(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL CopyFiles2Clipboard(std::vector<CString> const& vecFiles);
	CEdit*    m_conRename;      //������ʱ�ɱ༭��
	int       m_nLastSlcFile;   //��������������ļ�ʱ�������һ������
	CPngButton m_btnMax;
	BOOL     m_BMaxDlg;         //������󻯱�ʶ
	CRect    m_rcRectSrc;        //����Ŀͻ��������С
	CRect    m_rcBT, m_rcMax, m_rcMin, m_rcExit, m_rcCamera, m_rcAutoCamera, m_rcBarCamera, m_rcSideCamera, m_rcBrows, m_rcFaceID, m_rcCard, m_rcCopyCard;
	CRect    m_rcTab, m_rcCtrl, m_rcList;
	CRect    m_rcStaCount, m_rcStaPage, m_rcStaNumber, m_rcNowPath, m_rcShowPath, m_rcZoomIn, m_rcZoomOut, m_rcRecover, m_rcLRotate, m_rcRRotate, m_rcChange, m_rcImageInfo;
	int      m_nNamingCount;   //�������������ڸ���������ʽ�󣬴�0��ʼ����
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
	BOOL           m_BSpaceDown;  //�������ְ�����Ӧ�������뵯��
	
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
	BOOL      m_BCamera200;   //200W�豸��־λ
	BOOL      m_BCamera500;   //500W�豸��־λ
	BOOL      m_BCamera800;   //800W�豸��־λ
	BOOL      m_BCamera1200;  //1200W�豸��־λ
	BOOL      m_BCamera1300;  //1300W�豸��ʶλ
	BOOL      m_BCameraTo1500;
	BOOL      m_BGS1600;      //GS1600 1300->1600��ֵ
	CString   m_strGS16_PID;
	CString   m_strGS16_VID;

	CString   m_strPID200;
	CString   m_strVID200;
	CString   m_strPID500;
	CString   m_strVID500;
	CString   m_strPID800;    //ָ��800W�豸PID��Ϣ
	CString   m_strVID800;    //ָ��800W�豸VID��Ϣ
	CString   m_strPID800b;   //800W����
	CString   m_strVID800b;
	CString   m_strPID800GS;    //GS1000
	CString   m_strVID800GS;    //GS1000
	CString   m_strPID1300;
	CString   m_strVID1300;
	CString   m_strPID1200;   //ָ��1200W�豸PID��Ϣ
	CString   m_strVID1200;   //ָ��1200W�豸VID��Ϣ
	CString   m_strPIDTo1500; //1221��ֵ��1500W
	CString   m_strVIDTo1500;

	CString   m_strPID800Un;    //0425��֪�������ͺ�
	CString   m_strVID800Un;    //0425��֪�������ͺ�

	// ͼ���ֵ
	CString InterPolateImage(CString srcImage, CString dsImage, int index); //index = 0: 800->1000; index=1:1200->1600
	CString GeneratePDF(CString srcImg, CString dstImg);
	CString GenerateBase64(CString srcImg, CString dstImg);
	int GetmaxResoindex(void);
	int      m_nInterpolateReso;      //��ֵ�ֱ��ʶ�Ӧ������ֵ
	int      m_nInterpolateSubReso;   //��ͷ��ֵ�ֱ��ʶ�Ӧ������ֵ
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
	// ���ȡ�������
	void TimeDelayed(int time_ms);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	int GetsubmaResoindex(void);
	afx_msg void OnBnClickedBtnCardcopy();



	//1102���֤��ӡ��ʾ����
	BOOL            m_BCardDlg;    //���֤������ʾ��ʶλ
	CString         m_strFrontName; //���֤ͼ������
	CRect           m_rcOCX;
	CUDSFront       m_dlgFront;
	afx_msg void OnMove(int x, int y);
	
	// ����豸���Ƿ��ظ�����XPϵͳ��Camera��ΪUSB��Ƶ�豸
	int      m_nLastRotate;
	int      m_nSameCameraLast;     //������3����3�������豸ʱ��������
	std::vector<CString> m_vcCameraName;
	CString CheckCameraName(CString cameraname);
	int      m_nMainOpen;        //��ͷ������ʶλ
	int      m_nAudioIndex;      //Ĭ����Ƶ�豸����
	CUds_videoctrl1 m_conVideoOcx;
	CString  m_strVideoFormat;   //��Ƶ��ʽ
	int GetDiyResoindex(int diyvalue);
	afx_msg void On32775Word();
	afx_msg void On32776Excel();
	void Self_SetBriValue(void);
	void Self_Write2Office(CString txtpath, CString officepath);
	void Self_OcrRecognize(CString imgpath, CString txtpath);

	//OCR����ʶ��
	tesseract::TessBaseAPI *m_api;
	Pix *m_image;
	BOOL                    m_BOcrOpened;      //OCR��ʼ���ɹ���־λ
	wchar_t* Utf_8ToUnicode(char* szU8);
	char* UnicodeToAnsi(const wchar_t* szStr);

	//ָ��ʶ��
	CString   m_strFingerDoc;   
	afx_msg void On32777AutoRotate();
	void Self_AutoRotate(CString imgpath);
	afx_msg void OnBnClickedBtnFaceid();

	//��֤�ȶ�
	CString      m_strFaceDoc;
	CUDSFaceID   m_dlgFaceID;

	//�Զ���ת�������Ż�
	BOOL         m_BAutoRotate;
	BOOL         m_BOptimize; 
	// �Զ���ת
	int Self_RecognizeOrit(CString imgpath, BOOL on_off);
	CPngButton m_btnCompare;
	int          m_nOptBright;          //�ĵ��Ż�����
	int          m_nOptContrast;        //�ĵ��Ż��Աȶ�
	int Self_DocOptimize(CxImage img, CString imgpath, BOOL on_off, int bright, int contrast);
protected:
	afx_msg LRESULT OnFaceid(WPARAM wParam, LPARAM lParam);
public:
	int Self_DocOptimize2(CxImage img, CString imgpath, bool on_off);
	float Self_GetColorPercentage(CxImage img, bool on_off);
	float m_fColorPercentage;
	int Self_RecognizeOrit2(CString imgpath, CString thumbpath, bool on_off);
	int   m_nAutoRotateMode;       //�Զ���ת�ķ����� 0-�ȸ裬1-����ѧϰ
	void Self_ReplaceImage(int thumbwidth, int thumbheight, int item);
	afx_msg void On32778RightRotateL();
	afx_msg void On32779RightRotateR();
	CString GenerateOFD(CString srcImg, CString dstImg);
	CString GenerateOthers(CString srcImg, CString dstImg, int mode);
	int m_nMainCodec; //��ͷ��Ƶ����
	int m_nSubCodec; //��ͷ��Ƶ����
};
