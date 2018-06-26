#pragma once
#define  WM_SUBSWITCH  WM_USER+1002

#include "PngButton.h"
#include "Uxtheme.h"    
#pragma comment(lib, "Uxtheme.lib")


// CUDSChildAdv 对话框

class CUDSChildAdv : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSChildAdv)

public:
	CUDSChildAdv(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDSChildAdv();

// 对话框数据
	enum { IDD = IDD_DLG_CHILDADV };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_conComScannersub;
	CComboBox m_conComDPIsub;
	afx_msg void OnSelchangeCmbSubname();
	afx_msg void OnSelchangeCmbSubdpi();
	afx_msg void OnClickedChkOpen();
	afx_msg void OnClickedChkGps();

	CWnd*   m_pWndSub;
	HWND    m_hWndSub;
	CButton m_conChkOpen;
	afx_msg void OnBnClickedBtnSubcap();
	afx_msg void OnBnClickedChkMerge();
	afx_msg void OnBnClickedChkExmerger();
	afx_msg void OnStnClickedStaLocation();


	COLORREF    m_ColorBig;   //中间区域颜色
	COLORREF    m_ColorLct0;
	COLORREF    m_ColorLct1;
	COLORREF    m_ColorLct2;
	COLORREF    m_ColorLct3;
	COLORREF    m_ColorLct4;
	COLORREF    m_ColorLct5;
	COLORREF    m_ColorLct6;
	COLORREF    m_ColorLct7;
	BOOL        m_BExMerge;  //外部合并标识位
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStnClickedStaLct1();
	afx_msg void OnStnClickedStaLct0();
	afx_msg void OnStnClickedStaLct2();
	afx_msg void OnStnClickedStaLct3();
	afx_msg void OnStnClickedStaLct4();
	afx_msg void OnStnClickedStaLct5();
	afx_msg void OnStnClickedStaLct6();
	afx_msg void OnStnClickedStaLct7();
	CStatic m_conStaLct0;
	afx_msg void OnPaint();
	CPngButton m_btnSubCap;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CToolTipCtrl   m_btnTipsSub;
	BOOL   m_BSubDownBk;
};
