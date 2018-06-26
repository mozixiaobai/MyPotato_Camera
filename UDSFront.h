#pragma once
#include "resource.h"
#include "ximage.h"

// CUDSFront 对话框

class CUDSFront : public CDialogEx
{
	DECLARE_DYNAMIC(CUDSFront)

public:
	CUDSFront(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDSFront();

// 对话框数据
	enum { IDD = IDD_DLG_FRONT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CDC*     m_pDC;
	CDC      m_ImageDC;
	CxImage  m_pImage;       //正面图像
	CxImage  m_pImageBack;   //背面提示模板图
	int      m_nOffsetX;
	int      m_nOffsetY;
	int      m_nImgWidth;    //图像宽高
	int      m_nImgHeight;
	CRect    m_rcPicRect;    //控件尺寸

	CString  m_strTips; 

	CFont    m_TipFont;      //提示信息的字体

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
