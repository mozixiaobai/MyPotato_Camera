#pragma once
#include "resource.h"
#include "PngButton.h"

// CUDSDeleteitem 对话框

class CUDSDeleteitem : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSDeleteitem)

public:
	CUDSDeleteitem(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDSDeleteitem();

// 对话框数据
	enum { IDD = IDD_DLG_DELETE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL    m_BDeleteIt;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CPngButton m_btnOK;
	CPngButton m_btnCancel;
};
