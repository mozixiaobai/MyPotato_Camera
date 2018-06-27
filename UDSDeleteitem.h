#pragma once
#include "resource.h"
#include "PngButton.h"

// CUDSDeleteitem �Ի���

class CUDSDeleteitem : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSDeleteitem)

public:
	CUDSDeleteitem(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDSDeleteitem();

// �Ի�������
	enum { IDD = IDD_DLG_DELETE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
