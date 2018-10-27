// dlgpsw.cpp : implementation file
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "dlgpsw.h"
#include "qglobal.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPsw dialog


CDlgPsw::CDlgPsw(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPsw::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPsw)
	m_strPsw1 = _T("");
	m_strPsw2 = _T("");
	m_strName = _T("");
	//}}AFX_DATA_INIT
	m_bCanChangeName = FALSE;
}


void CDlgPsw::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPsw)
	DDX_Text(pDX, IDC_EDIT_PSW_1, m_strPsw1);
	DDX_Text(pDX, IDC_EDIT_PSW_2, m_strPsw2);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPsw, CDialog)
	//{{AFX_MSG_MAP(CDlgPsw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPsw message handlers

BOOL CDlgPsw::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText(QGlobal::gf_Str(_T("PASSWORD"),_T("Password")));
	
	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(QGlobal::gf_Str(_T("NAME"),_T("Name")));

	GetDlgItem(IDC_STATIC_PSW)->SetWindowText(QGlobal::gf_Str(_T("PASSWORD"),_T("Password"))+_T("1"));
	GetDlgItem(IDC_STATIC_PSW2)->SetWindowText(QGlobal::gf_Str(_T("PASSWORD"),_T("Password"))+_T("2"));

	GetDlgItem(IDOK)->SetWindowText(QGlobal::gf_Str(_T("IDOK"),_T("&OK")));
	GetDlgItem(IDCANCEL)->SetWindowText(QGlobal::gf_Str(_T("IDCANCEL"),_T("&Cancel")));
	

	// TODO: Add extra initialization here
	if(m_bCanChangeName)
	{
		GetDlgItem(IDC_EDIT_NAME)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_NAME)->EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPsw::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	m_strName.TrimLeft();
	m_strName.TrimRight();
	if(m_strName.IsEmpty())
	{
		AfxMessageBox(_T("Name is null!"));
		return;
	}
	if(m_strName.GetLength()>200)
	{
		AfxMessageBox(_T("Name is too long!"));
		return;
	}
	if(m_strPsw1!=m_strPsw2)
	{
		AfxMessageBox(_T("Password is not same!"));
		return;
	}

	if(m_strPsw1.GetLength()>100)
	{
		AfxMessageBox(_T("Password is too long!"));
		return;
	}
	CDialog::OnOK();
}
