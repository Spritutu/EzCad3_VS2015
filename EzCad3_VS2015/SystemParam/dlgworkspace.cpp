h// dlgworkspace.cpp : implementation file

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "dlgworkspace.h"
#include "qglobal.h"
#include "sysparam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWorkSpace dialog


CDlgWorkSpace::CDlgWorkSpace(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWorkSpace::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWorkSpace)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pParam = NULL;
}


void CDlgWorkSpace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWorkSpace)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWorkSpace, CDialog)
	//{{AFX_MSG_MAP(CDlgWorkSpace)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWorkSpace message handlers

BOOL CDlgWorkSpace::OnInitDialog() 
{
	CDialog::OnInitDialog();
		ASSERT(m_pParam!=NULL);
	// TODO: Add extra initialization here
		GetDlgItem(IDC_CHECK_SHOW)->SetWindowText(QGlobal::gf_Str(_T("WORKSPAC_SHOW"),_T("Show workspace")));
	GetDlgItem(IDC_CHECK_CIRCLE)->SetWindowText(QGlobal::gf_Str(_T("WORKSPAC_CIRCLE"),_T("Circle workspace")));
	GetDlgItem(IDC_STATIC_LEFTCORNER)->SetWindowText(QGlobal::gf_Str(_T("LB_CORNER"),_T("Left bottom corner")));		
	GetDlgItem(IDC_STATIC_SIZE)->SetWindowText(QGlobal::gf_Str(_T("SIZE"),_T("Size")));
	GetDlgItem(IDC_STATIC_LENGTH)->SetWindowText(QGlobal::gf_Str(_T("WIDTH"),_T("Width")));
	GetDlgItem(IDC_STATIC_WIDTH)->SetWindowText(QGlobal::gf_Str(_T("HEIGHT"),_T("Height")));

	GetDlgItem(IDC_CHECK_CROSSLINE)->SetWindowText(QGlobal::gf_Str(_T("SHOWCROSSLINE"),_T("Show center cross line")));

	CString strUnit = QGlobal::gf_Str(_T("MM"),_T("mm"));
	if(m_pParam ->GetParamInt(INT_PARAM_UNITTYPE)!=UNIT_MM)
	{
		strUnit = QGlobal::gf_Str(_T("INCH"),_T("inch"));
	}
	GetDlgItem(IDC_STATIC_UNIT1)->SetWindowText(strUnit);	
	GetDlgItem(IDC_STATIC_UNIT2)->SetWindowText(strUnit);	
	GetDlgItem(IDC_STATIC_UNIT3)->SetWindowText(strUnit);	
	GetDlgItem(IDC_STATIC_UNIT4)->SetWindowText(strUnit);	
	
	OnReInit();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgWorkSpace::OnReInit()
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_SHOW);
	pBtn->SetCheck(m_pParam->GetParamInt(INT_PARAM_SHOWWORKSPACE)); 

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_CIRCLE);
	pBtn->SetCheck(m_pParam->GetParamInt(INT_PARAM_WORKSPACETYPE)); 

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_CROSSLINE);
	pBtn->SetCheck(m_pParam->GetParamInt(INT_PARAM_SHOWCROSSLINE)); 

	CString str;
	GetDlgItem(IDC_EDIT_LB_X)->SetWindowText(QGlobal::gf_GetLenStr(m_pParam->GetParamDouble(DOUBLE_PARAM_WORKSPACEX)));
	GetDlgItem(IDC_EDIT_LB_Y)->SetWindowText(QGlobal::gf_GetLenStr(m_pParam->GetParamDouble(DOUBLE_PARAM_WORKSPACEY)));
	GetDlgItem(IDC_EDIT_LEN)->SetWindowText(QGlobal::gf_GetLenStr(m_pParam->GetParamDouble(DOUBLE_PARAM_WORKSPACEW)));
	GetDlgItem(IDC_EDIT_WID)->SetWindowText(QGlobal::gf_GetLenStr(m_pParam->GetParamDouble(DOUBLE_PARAM_WORKSPACEH)));
}

void CDlgWorkSpace::OnOK() 
{
	// TODO: Add extra validation here
	
}

void CDlgWorkSpace::OnCancel() 
{
	// TODO: Add extra cleanup here	

}

void CDlgWorkSpace::OK()
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_SHOW);
	m_pParam->SetParamInt(INT_PARAM_SHOWWORKSPACE,pBtn->GetCheck());
	 
	pBtn = (CButton*)GetDlgItem(IDC_CHECK_CIRCLE);
	m_pParam->SetParamInt(INT_PARAM_WORKSPACETYPE,pBtn->GetCheck());
	 
	pBtn = (CButton*)GetDlgItem(IDC_CHECK_CROSSLINE);
	m_pParam->SetParamInt(INT_PARAM_SHOWCROSSLINE,pBtn->GetCheck());
	 
	CString str;
	GetDlgItem(IDC_EDIT_LB_X)->GetWindowText(str);
	m_pParam->SetParamDouble(DOUBLE_PARAM_WORKSPACEX, QGlobal::ATOF(str));
	
	GetDlgItem(IDC_EDIT_LB_Y)->GetWindowText(str);
	m_pParam->SetParamDouble(DOUBLE_PARAM_WORKSPACEY, QGlobal::ATOF(str));

	GetDlgItem(IDC_EDIT_LEN)->GetWindowText(str);
	m_pParam->SetParamDouble(DOUBLE_PARAM_WORKSPACEW, QGlobal::ATOF(str));

	GetDlgItem(IDC_EDIT_WID)->GetWindowText(str);
	m_pParam->SetParamDouble(DOUBLE_PARAM_WORKSPACEH, QGlobal::ATOF(str));	
}
