#pragma once
#include "resource.h"
#include "PngButton.h"


// CUDSChildDcm 对话框

class CUDSChildDcm : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSChildDcm)

public:
	CUDSChildDcm(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDSChildDcm();

// 对话框数据
	enum { IDD = IDD_DLG_DCMINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClickedChkMan();
	afx_msg void OnClickedChkWman();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	BOOL      m_BSexMan;      //默认为男
	CString   m_strDcmInfo;   //向父窗口传递的DCM所有信息
	CPngButton m_btnOK;
	CPngButton m_btnCancel;
	CToolTipCtrl   m_btnTipsMain;
};
