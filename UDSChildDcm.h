#pragma once
#include "resource.h"
#include "PngButton.h"


// CUDSChildDcm �Ի���

class CUDSChildDcm : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSChildDcm)

public:
	CUDSChildDcm(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDSChildDcm();

// �Ի�������
	enum { IDD = IDD_DLG_DCMINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	BOOL      m_BSexMan;      //Ĭ��Ϊ��
	CString   m_strDcmInfo;   //�򸸴��ڴ��ݵ�DCM������Ϣ
	CPngButton m_btnOK;
	CPngButton m_btnCancel;
	CToolTipCtrl   m_btnTipsMain;
};
