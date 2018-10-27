// D:\项目\Ezcad3-VS2010(20150605)\Ezcad3-VS2010\Ezcad3\dlg\DlgUserParam.cpp : 实现文件
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "DlgUserParam.h"
#include "afxdialogex.h"
#include "QGlobal.h"

// CDlgUserParam 对话框

IMPLEMENT_DYNAMIC(CDlgUserParam, CDialogEx)

CDlgUserParam::CDlgUserParam(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgUserParam::IDD, pParent)
{
	m_pUser = NULL;  
	m_bDisableName=FALSE;
}

CDlgUserParam::~CDlgUserParam()
{
}

void CDlgUserParam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgUserParam, CDialogEx)
END_MESSAGE_MAP()


// CDlgUserParam 消息处理程序
// CDlgIOSet 消息处理程序
BOOL CDlgUserParam::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	SetWindowText(QGlobal::gf_Str(_T("USER"),_T("User")));

	GetDlgItem(IDC_STATIC_1)->SetWindowText(QGlobal::gf_Str(_T("NAME"),_T("Name")));
	GetDlgItem(IDC_STATIC_2)->SetWindowText(QGlobal::gf_Str(_T("PASSWORD"),_T("Password")));
	GetDlgItem(IDC_STATIC_3)->SetWindowText(QGlobal::gf_Str(_T("CONFIRMPASSWORD"),_T("Confirm password")));
	 
	GetDlgItem(IDC_CHECK1)->SetWindowText(QGlobal::gf_Str(_T("ENSAVEFILE"),_T("Enable save file")));
	GetDlgItem(IDC_CHECK2)->SetWindowText(QGlobal::gf_Str(_T("ENDRAWENTITY"),_T("Enable draw entity")));
	GetDlgItem(IDC_CHECK3)->SetWindowText(QGlobal::gf_Str(_T("ENPICKMOVE"),_T("Enable pick move")));
	GetDlgItem(IDC_CHECK4)->SetWindowText(QGlobal::gf_Str(_T("ENEDITPARAM"),_T("Enable edit entity")));
	GetDlgItem(IDC_CHECK5)->SetWindowText(QGlobal::gf_Str(_T("ENPENPARAM"),_T("Enable pen parameter")));
	GetDlgItem(IDC_CHECK6)->SetWindowText(QGlobal::gf_Str(_T("ENDEVPARAM"),_T("Enable device parameter")));
	GetDlgItem(IDC_CHECK7)->SetWindowText(QGlobal::gf_Str(_T("ENSYSTEMPARAM"),_T("Enable system parameter")));
	GetDlgItem(IDC_CHECK8)->SetWindowText(QGlobal::gf_Str(_T("ENMARK"),_T("Enable mark")));
		GetDlgItem(IDOK)->SetWindowText(QGlobal::gf_Str(_T("IDOK"),_T("&OK")));
	GetDlgItem(IDCANCEL)->SetWindowText(QGlobal::gf_Str(_T("IDCANCEL"),_T("&Cancel")));


	if(m_pUser!=NULL)
	{
		GetDlgItem(IDC_EDIT1)->SetWindowText(m_pUser->m_strName);
		GetDlgItem(IDC_EDIT2)->SetWindowText(m_pUser->m_strPsw);
		GetDlgItem(IDC_EDIT3)->SetWindowText(m_pUser->m_strPsw);

		((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(m_pUser->m_bEnableSave);
		((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(m_pUser->m_bEnableDraw);
		((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(m_pUser->m_bEnablePickMove);
		((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(m_pUser->m_bEnableEditEntParam);
		((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(m_pUser->m_bEnablePenParam);
		((CButton*)GetDlgItem(IDC_CHECK6))->SetCheck(m_pUser->m_bEnableDevParam);
		((CButton*)GetDlgItem(IDC_CHECK7))->SetCheck(m_pUser->m_bEnableModifySysParam);
		((CButton*)GetDlgItem(IDC_CHECK8))->SetCheck(m_pUser->m_bEnableMark);
	} 

	 
	if(m_bDisableName)
	{
		GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	}
	return TRUE;
}

void CDlgUserParam::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	if(m_pUser!=NULL)
	{
		GetDlgItem(IDC_EDIT1)->GetWindowText(m_pUser->m_strName);
		CString str1,str2;
		GetDlgItem(IDC_EDIT2)->GetWindowText(str1);
		GetDlgItem(IDC_EDIT3)->GetWindowText(str2);
		if(str1 != str2)
		{
			AfxMessageBox(QGlobal::gf_Str(_T("PASSWORDNOSAME"),_T("Password is not same!")));
			return;
		}

		m_pUser->m_strPsw = str1;
		m_pUser->m_bEnableSave = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
		m_pUser->m_bEnableDraw = ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck();
		m_pUser->m_bEnablePickMove = ((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck();
		m_pUser->m_bEnableEditEntParam = ((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck();
		m_pUser->m_bEnablePenParam = ((CButton*)GetDlgItem(IDC_CHECK5))->GetCheck();
		m_pUser->m_bEnableDevParam = ((CButton*)GetDlgItem(IDC_CHECK6))->GetCheck();
		m_pUser->m_bEnableModifySysParam = ((CButton*)GetDlgItem(IDC_CHECK7))->GetCheck();
		m_pUser->m_bEnableMark= ((CButton*)GetDlgItem(IDC_CHECK8))->GetCheck();
	} 
	CDialog::OnOK();
}