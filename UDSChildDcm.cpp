// UDSChildDcm.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDSChildDcm.h"
#include "afxdialogex.h"


// CUDSChildDcm �Ի���

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


// CUDSChildDcm ��Ϣ�������


BOOL CUDSChildDcm::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	/***********************************
	*
	* 1�����ݳ�ʼ��
	* 2��CheckBox��ʼ��
	* 3��UI�����ʼ��
	*
	************************************/

	//1��------------------------------
	m_BSexMan   = TRUE;

	//2��------------------------------
	((CButton*)GetDlgItem(IDC_CHK_MAN))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_CHK_WMAN))->SetCheck(FALSE);


	//3��-------------------------------
	CDialogEx::SetBackgroundColor(RGB(72,77,91));

	m_btnOK.Init(IDB_PNG_NEXT, BTN_IMG_1, BTN_TYPE_NORMAL);
	m_btnCancel.Init(IDB_PNG_BEFOR, BTN_IMG_1, BTN_TYPE_NORMAL);

	m_btnTipsMain.Create(this);
	m_btnTipsMain.AddTool(GetDlgItem(IDOK), _T("��һ��"));
	m_btnTipsMain.AddTool(GetDlgItem(IDCANCEL), _T("��һ��"));
	m_btnTipsMain.SetDelayTime(200);   //�����ӳ�
	m_btnTipsMain.SetTipTextColor(RGB(0, 0, 0));//����������ɫ
	m_btnTipsMain.SetTipBkColor(RGB(255, 255, 255));//������ʾ�򱳾���ɫ
	m_btnTipsMain.Activate(TRUE); //������ʾ����

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CUDSChildDcm::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


HBRUSH CUDSChildDcm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	//��̬Static�ؼ�����-----
	if (pWnd->GetDlgCtrlID()==IDC_STA_NAME ||pWnd->GetDlgCtrlID()==IDC_STA_ID ||pWnd->GetDlgCtrlID()==IDC_STA_SEX ||
		pWnd->GetDlgCtrlID()==IDC_STA_BIRTH || pWnd->GetDlgCtrlID()==IDC_STA_DNAME ||
		pWnd->GetDlgCtrlID()==IDC_STACHK_MAN || pWnd->GetDlgCtrlID()==IDC_STACHK_WMAN)
	{
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		CFont   tem_Font;
		tem_Font.CreatePointFont(100, _T("����"));
		pDC->SelectObject(&tem_Font);

	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


BOOL CUDSChildDcm::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CUDSChildDcm::OnClickedChkMan()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʽ: ���������� ����ID�� ���߳������ڣ� �����Ա� ҽʦ������ ���ڣ�ʱ��
	//��ȡ����
	CString     tem_strName;
	SYSTEMTIME  tem_st;
	CString     tem_strDate, tem_strTime;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(tem_strName);
	if (tem_strName.IsEmpty())
	{
		MessageBox(_T("��Ϣ��������"));
		return;
	}
	m_strDcmInfo  = tem_strName + _T("|");

	GetDlgItem(IDC_EDIT_ID)->GetWindowText(tem_strName);
	if (tem_strName.IsEmpty())
	{
		MessageBox(_T("��Ϣ��������"));
		return;
	}
	m_strDcmInfo += tem_strName + _T("|");

	GetDlgItem(IDC_EDIT_BIRTH)->GetWindowText(tem_strName);
	if (tem_strName.IsEmpty())
	{
		MessageBox(_T("��Ϣ��������"));
		return;
	}
	m_strDcmInfo += tem_strName + _T("|");

	if (m_BSexMan)
	{
		m_strDcmInfo += _T("��");
		m_strDcmInfo +=  _T("|");
	}
	else
	{
		m_strDcmInfo += _T("Ů");
		m_strDcmInfo += _T("|");
	}

	GetDlgItem(IDC_EDIT_DNAME)->GetWindowText(tem_strName);
	if (tem_strName.IsEmpty())
	{
		MessageBox(_T("��Ϣ��������"));
		return;
	}
	m_strDcmInfo += tem_strName + _T("|");

	GetLocalTime(&tem_st);
	tem_strDate.Format(_T("%d%2d%2d"), tem_st.wYear, tem_st.wMonth, tem_st.wDay);
	//�ո��滻Ϊ 0 �����ں��¼�Ҫ��Ϊ��׼��8λ
	tem_strDate.Replace(' ', '0');

	tem_strTime.Format(_T("%d%2d%2d"), tem_st.wHour, tem_st.wMinute, tem_st.wSecond);
	tem_strTime.Replace(' ', '0');

	m_strDcmInfo += tem_strDate + _T("|");
	m_strDcmInfo += tem_strTime;


	CDialogEx::OnOK();
}


void CUDSChildDcm::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_strDcmInfo = _T("");
	CDialogEx::OnCancel();
}
