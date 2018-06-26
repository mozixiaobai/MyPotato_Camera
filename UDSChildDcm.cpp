// UDSChildDcm.cpp : 实现文件
//

#include "stdafx.h"
#include "UDSChildDcm.h"
#include "afxdialogex.h"


// CUDSChildDcm 对话框

IMPLEMENT_DYNAMIC(CUDSChildDcm, CDialogEx)

CUDSChildDcm::CUDSChildDcm(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUDSChildDcm::IDD, pParent)
{

}

CUDSChildDcm::~CUDSChildDcm()
{
}

void CUDSChildDcm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CUDSChildDcm, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHK_MAN, &CUDSChildDcm::OnClickedChkMan)
	ON_BN_CLICKED(IDC_CHK_WMAN, &CUDSChildDcm::OnClickedChkWman)
	ON_BN_CLICKED(IDOK, &CUDSChildDcm::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUDSChildDcm::OnBnClickedCancel)
END_MESSAGE_MAP()


// CUDSChildDcm 消息处理程序


BOOL CUDSChildDcm::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/***********************************
	*
	* 1、数据初始化
	* 2、CheckBox初始化
	* 3、UI界面初始化
	*
	************************************/

	//1、------------------------------
	m_BSexMan   = TRUE;

	//2、------------------------------
	((CButton*)GetDlgItem(IDC_CHK_MAN))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_CHK_WMAN))->SetCheck(FALSE);


	//3、-------------------------------
	CDialogEx::SetBackgroundColor(RGB(72,77,91));

	m_btnOK.Init(IDB_PNG_NEXT, BTN_IMG_1, BTN_TYPE_NORMAL);
	m_btnCancel.Init(IDB_PNG_BEFOR, BTN_IMG_1, BTN_TYPE_NORMAL);

	m_btnTipsMain.Create(this);
	m_btnTipsMain.AddTool(GetDlgItem(IDOK), _T("下一步"));
	m_btnTipsMain.AddTool(GetDlgItem(IDCANCEL), _T("上一步"));
	m_btnTipsMain.SetDelayTime(200);   //设置延迟
	m_btnTipsMain.SetTipTextColor(RGB(0, 0, 0));//设置字体颜色
	m_btnTipsMain.SetTipBkColor(RGB(255, 255, 255));//设置提示框背景颜色
	m_btnTipsMain.Activate(TRUE); //启用提示功能

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CUDSChildDcm::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


HBRUSH CUDSChildDcm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	//静态Static控件美化-----
	if (pWnd->GetDlgCtrlID()==IDC_STA_NAME ||pWnd->GetDlgCtrlID()==IDC_STA_ID ||pWnd->GetDlgCtrlID()==IDC_STA_SEX ||
		pWnd->GetDlgCtrlID()==IDC_STA_BIRTH || pWnd->GetDlgCtrlID()==IDC_STA_DNAME ||
		pWnd->GetDlgCtrlID()==IDC_STACHK_MAN || pWnd->GetDlgCtrlID()==IDC_STACHK_WMAN)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		CFont   tem_Font;
		tem_Font.CreatePointFont(100, _T("宋体"));
		pDC->SelectObject(&tem_Font);

	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


BOOL CUDSChildDcm::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CUDSChildDcm::OnClickedChkMan()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_MAN))
	{
		((CButton*)GetDlgItem(IDC_CHK_WMAN))->SetCheck(FALSE);
		m_BSexMan = TRUE;
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_WMAN))->SetCheck(TRUE);
		m_BSexMan = FALSE;
	}
}


void CUDSChildDcm::OnClickedChkWman()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHK_WMAN))
	{
		((CButton*)GetDlgItem(IDC_CHK_MAN))->SetCheck(FALSE);
		m_BSexMan = FALSE;
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHK_MAN))->SetCheck(TRUE);
		m_BSexMan = TRUE;
	}
}


void CUDSChildDcm::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//格式: 患者姓名， 患者ID， 患者出生日期， 患者性别， 医师姓名， 日期，时间
	//获取姓名
	CString     tem_strName;
	SYSTEMTIME  tem_st;
	CString     tem_strDate, tem_strTime;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(tem_strName);
	if (tem_strName.IsEmpty())
	{
		MessageBox(_T("信息不完整！"));
		return;
	}
	m_strDcmInfo  = tem_strName + _T("|");

	GetDlgItem(IDC_EDIT_ID)->GetWindowText(tem_strName);
	if (tem_strName.IsEmpty())
	{
		MessageBox(_T("信息不完整！"));
		return;
	}
	m_strDcmInfo += tem_strName + _T("|");

	GetDlgItem(IDC_EDIT_BIRTH)->GetWindowText(tem_strName);
	if (tem_strName.IsEmpty())
	{
		MessageBox(_T("信息不完整！"));
		return;
	}
	m_strDcmInfo += tem_strName + _T("|");

	if (m_BSexMan)
	{
		m_strDcmInfo += _T("男");
		m_strDcmInfo +=  _T("|");
	}
	else
	{
		m_strDcmInfo += _T("女");
		m_strDcmInfo += _T("|");
	}

	GetDlgItem(IDC_EDIT_DNAME)->GetWindowText(tem_strName);
	if (tem_strName.IsEmpty())
	{
		MessageBox(_T("信息不完整！"));
		return;
	}
	m_strDcmInfo += tem_strName + _T("|");

	GetLocalTime(&tem_st);
	tem_strDate.Format(_T("%d%2d%2d"), tem_st.wYear, tem_st.wMonth, tem_st.wDay);
	//空格替换为 0 ，日期和事件要求为标准的8位
	tem_strDate.Replace(' ', '0');

	tem_strTime.Format(_T("%d%2d%2d"), tem_st.wHour, tem_st.wMinute, tem_st.wSecond);
	tem_strTime.Replace(' ', '0');

	m_strDcmInfo += tem_strDate + _T("|");
	m_strDcmInfo += tem_strTime;


	CDialogEx::OnOK();
}


void CUDSChildDcm::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strDcmInfo = _T("");
	CDialogEx::OnCancel();
}
