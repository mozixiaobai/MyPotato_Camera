#pragma once
#include "resource.h"
#include "ximage.h"


// CUDSCardFront 对话框

class CUDSCardFront : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSCardFront)

public:
	CUDSCardFront(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDSCardFront();

// 对话框数据
	enum { IDD = IDD_DLG_CARDFRONT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CRect     tem_rcDlg;


	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CStatic m_conPicCtrl;
	afx_msg void OnBnClickedBtnTest();
};
