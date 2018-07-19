#pragma once
#define  WM_SWITCH    WM_USER+1001

#include "PngButton.h"
#include "Uxtheme.h"    //用于设置GroupBox标题栏颜色
#pragma comment(lib, "Uxtheme.lib")


// CUDSChildNor 对话框

class CUDSChildNor : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSChildNor)

public:
	CUDSChildNor(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDSChildNor();

// 对话框数据
	enum { IDD = IDD_DLG_CHILDNORMAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnStnClickedStaExp();
	CComboBox m_conComScanner;
	CComboBox m_conComReso;
	afx_msg void OnBnClickedBtnTest();
	virtual BOOL OnInitDialog();
	CComboBox m_conComFilemode;
	CComboBox m_conComColormode;
//	CSliderCtrl m_conSlidBright;
	CSliderCtrl m_conSlidExpos;
//	int m_conStaBright;
//	afx_msg void OnNMCustomdrawSlidBright(NMHDR *pNMHDR, LRESULT *pResult);
//	int m_conStaBrt;
	int m_conStaExp;
	afx_msg void OnNMCustomdrawSlidExposure(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangeCmbScanners();
	afx_msg void OnSelchangeCmbFilemode();
	afx_msg void OnSelchangeCmbColormode();
	afx_msg void OnSelchangeCmbDpi();

	int   m_nIndexScanner;
	int   m_nIndexDPI;
	int   m_nIndexFile;
	int   m_nIndexColor;
	int   m_nIndexCrop;
	CWnd*   m_pWnd;
	HWND    m_hWnd;
	afx_msg void OnBnClickedChkAutocrt();
	afx_msg void OnBnClickedChkAutoexp();
	CButton m_conChkExp;
	afx_msg void OnBnClickedBtnEnd();
	BOOL      m_BBegin;   //标识开始录制
	BOOL      m_BEnd;     //接收标识位
	BOOL      m_BAutoExp; //由于每次自动曝光后，自动调用了一次Slid切换为手动曝光，因此增加标志位
//	CRichEditCtrl m_conRichEdit;
	CRichEditCtrl m_conRichEdit;
	void LoadIniFile(void);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CButton        m_groupScanMain1;
	CPngButton     m_btnStart;
	CPngButton     m_btnEnd;
	CToolTipCtrl   m_btnTipsMain;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	BOOL           m_BMainDownBk;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_staTimer;
	UINT  mm;
	UINT  ss;
	UINT mss;
	CHARFORMAT  tem_fontRichEdit;  //设置RichEditControl控件字体样式
	CButton m_chkAutoCrt;
	CImage   m_img;   //子窗口背景
	CSliderCtrl m_conSlidBright;
	afx_msg void OnCustomdrawSlidBright(NMHDR *pNMHDR, LRESULT *pResult);
	int m_conStaBrg;
	CString m_conStaExpStr;
	CComboBox m_conAudio;
	afx_msg void OnSelchangeCmbAudeo();
	int   m_nAudioIndex;    //音频设备索引
	CComboBox m_conAudioFmt;
	afx_msg void OnSelchangeCmbAudeoformat();
	afx_msg void OnClickedChkAutrotate();
	afx_msg void OnClickedChkOptimize();
	CString   m_strIniPath;
	CComboBox m_conCropMode;
	afx_msg void OnSelchangeCmbCropmode2();
	afx_msg void OnClickedStaDpi();

	//分辨率与DPI切换
	BOOL m_BDpiOpen;
	CComboBox m_conComDpi;
	afx_msg void OnSelchangeCmbDpi2();
	afx_msg void OnBnClickedBtnCorrectdpi();
};
