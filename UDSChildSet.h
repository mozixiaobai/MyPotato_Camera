#pragma once
#define  WM_ADVCESET   WM_USER+1003

#include "PngButton.h"
#include "Uxtheme.h"    
#pragma comment(lib, "Uxtheme.lib")



// CUDSChildSet �Ի���

class CUDSChildSet : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSChildSet)

public:
	CUDSChildSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDSChildSet();

// �Ի�������
	enum { IDD = IDD_DLG_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	CPngButton m_btnUpload;
	afx_msg void OnBnClickedChkVedioinfo();
	CWnd*   m_pWndSet;
	HWND    m_hWndSet;
	virtual BOOL OnInitDialog();
	CSliderCtrl m_conSlidImgQ;   //ͼ������SliderBar
	afx_msg void OnCustomdrawSlidImgqulity(NMHDR *pNMHDR, LRESULT *pResult);
	int m_conImgQ;
	afx_msg void OnNMCustomdrawSlidAutosens(NMHDR *pNMHDR, LRESULT *pResult);
	int m_conAutoS;
	CSliderCtrl m_conSlidAutoS;
	afx_msg void OnBnClickedChkTime();
	afx_msg void OnBnClickedChkCapoder();
	afx_msg void OnBnClickedChkPrename();
	CEdit m_conEditPre;
	CString    m_strPreName;
	CString    m_strDefaultDoc;
	afx_msg void OnBnClickedBtnSetpath();
	afx_msg void OnBnClickedChkHttp();
	CString    m_strURL;
	CString    m_strFtp;
	CEdit m_conEditHttp;
	afx_msg void OnBnClickedBtnUpload();
	afx_msg void OnPaint();
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CToolTipCtrl   m_btnTipsSet;

	CPngButton m_btnShangchuan;   //PNGButton ����ʾ
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	BOOL      m_BUpLoadFiles;   //����ϴ���ʶ����ֹ�ظ����
	BOOL      m_BHttp;          //Ĭ��Http�ϴ�
	afx_msg void OnBnClickedBtnCamres();
	afx_msg void OnBnClickedBtnCamrem();
	CPngButton m_btnMaincam;
	afx_msg void OnChangeEditPrename();
	afx_msg void OnBnClickedRadioHttp();
	afx_msg void OnBnClickedRadioFtp();
	afx_msg void OnRadioMaincam();
	afx_msg void OnRadioSubcam();
	afx_msg void OnRadioVedio();
	afx_msg void OnRadioVedio2();
	afx_msg void OnBnClickedBtnVideo1();
	afx_msg void OnBnClickedBtnVideo2();
	int   m_nSoundOpen;    //��������
};
