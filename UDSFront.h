#pragma once
#include "resource.h"
#include "ximage.h"

// CUDSFront �Ի���

class CUDSFront : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSFront)

public:
	CUDSFront(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDSFront();

// �Ի�������
	enum { IDD = IDD_DLG_FRONT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CDC*     m_pDC;
	CDC      m_ImageDC;
	CxImage  m_pImage;       //����ͼ��
	CxImage  m_pImageBack;   //������ʾģ��ͼ
	int      m_nOffsetX;
	int      m_nOffsetY;
	int      m_nImgWidth;    //ͼ����
	int      m_nImgHeight;
	CRect    m_rcPicRect;    //�ؼ��ߴ�

	CString  m_strTips; 

	CFont    m_TipFont;      //��ʾ��Ϣ������

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
