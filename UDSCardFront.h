#pragma once
#include "resource.h"
#include "ximage.h"


// CUDSCardFront �Ի���

class CUDSCardFront : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSCardFront)

public:
	CUDSCardFront(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDSCardFront();

// �Ի�������
	enum { IDD = IDD_DLG_CARDFRONT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CRect     tem_rcDlg;


	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CStatic m_conPicCtrl;
	afx_msg void OnBnClickedBtnTest();
};
