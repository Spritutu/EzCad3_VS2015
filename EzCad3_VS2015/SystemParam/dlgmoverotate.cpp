// dlgmoverotate.cpp : implementation file
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "dlgmoverotate.h"

#include "qglobal.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMoveRotate dialog


CDlgMoveRotate::CDlgMoveRotate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMoveRotate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMoveRotate)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pParam = NULL;
}


void CDlgMoveRotate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMoveRotate)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMoveRotate, CDialog)
	//{{AFX_MSG_MAP(CDlgMoveRotate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMoveRotate message handlers

BOOL CDlgMoveRotate::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	 
	GetDlgItem(IDC_STATIC_KEY)->SetWindowText(QGlobal::gf_Str(_T("KEYBOARD"),_T("Keyboard")));
	GetDlgItem(IDC_STATIC_MOVE)->SetWindowText(QGlobal::gf_Str(_T("NAV_PICK_MOVEDIS"),_T("Nudge Distance")));
	GetDlgItem(IDC_STATIC_NUDGESCALE)->SetWindowText(QGlobal::gf_Str(_T("BIGNUDGESCALE"),_T("Big Nudge scale")));
	
	GetDlgItem(IDC_STATIC_ROTATE)->SetWindowText(QGlobal::gf_Str(_T("ROTATEANG"),_T("Rotate")));
	GetDlgItem(IDC_STATIC_ANG)->SetWindowText(QGlobal::gf_Str(_T("DEGREE"),_T("[deg]")));
	GetDlgItem(IDC_STATIC_PTNO)->SetWindowText(QGlobal::gf_Str(_T("ORIGIN_PTNUM"),_T("Input point NO.")));
	GetDlgItem(IDC_STATIC_ORIGINWAY)->SetWindowText(QGlobal::gf_Str(_T("ORIGIN_WAY"),_T("To Origin")));
	
	CString strUnit = QGlobal::gf_Str(_T("MM"),_T("mm"));
	if(m_pParam ->GetParamInt(INT_PARAM_UNITTYPE)!=UNIT_MM)
	{
		strUnit = QGlobal::gf_Str(_T("INCH"),_T("inch"));
	}
	GetDlgItem(IDC_STATIC_UNIT1)->SetWindowText(strUnit);	  

	CString str;
	GetDlgItem(IDC_EDIT_DIST)->SetWindowText(QGlobal::gf_GetLenStr(m_pParam->GetParamDouble(DOUBLE_PARAM_NUDGESMALLDIST)));
	GetDlgItem(IDC_EDIT_NUDGESCALE)->SetWindowText(QGlobal::gf_GetLenStr(m_pParam->GetParamDouble(DOUBLE_PARAM_NUDGEBIGDIST)));
	GetDlgItem(IDC_EDIT_ANG)->SetWindowText(QGlobal::gf_GetLenStr(m_pParam->GetParamDouble(DOUBLE_PARAM_NUDGEANGLE)));
	GetDlgItem(IDC_EDIT_X1)->SetWindowText(QGlobal::gf_GetLenStr(m_pParam->GetParamDouble(DOUBLE_PARAM_ORIGINX)));
	GetDlgItem(IDC_EDIT_Y1)->SetWindowText(QGlobal::gf_GetLenStr(m_pParam->GetParamDouble(DOUBLE_PARAM_ORIGINY)));
	

	//默认设置的回原点方式
	str.Format(_T("%d"),m_pParam->GetParamInt(INT_PARAM_MOVEORIGINFLAG));	
	GetDlgItem(IDC_EDIT_PTNUMBER)->SetWindowText(str);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgMoveRotate::OnOK() 
{
	// TODO: Add extra validation here
	
}

void CDlgMoveRotate::OnCancel() 
{
	// TODO: Add extra cleanup here	

}
void CDlgMoveRotate::OK()
{

	CString str;
	GetDlgItem(IDC_EDIT_DIST)->GetWindowText(str);
	m_pParam->SetParamDouble(DOUBLE_PARAM_NUDGESMALLDIST,QGlobal::ATOF(str));

	GetDlgItem(IDC_EDIT_NUDGESCALE)->GetWindowText(str);
	m_pParam->SetParamDouble(DOUBLE_PARAM_NUDGEBIGDIST,QGlobal::ATOF(str));

	
	GetDlgItem(IDC_EDIT_ANG)->GetWindowText(str);
	m_pParam->SetParamDouble(DOUBLE_PARAM_NUDGEANGLE,QGlobal::ATOF(str));

	GetDlgItem(IDC_EDIT_PTNUMBER)->GetWindowText(str);
	if (str.GetLength() > 1)
		str = str.Left(1);

	int nMoveToOriginFlag = _ttoi(str);
	if(nMoveToOriginFlag<0)
		nMoveToOriginFlag =0;
	if(nMoveToOriginFlag>8)
		nMoveToOriginFlag =8;

	m_pParam->SetParamInt(INT_PARAM_MOVEORIGINFLAG,nMoveToOriginFlag);

	GetDlgItem(IDC_EDIT_X1)->GetWindowText(str);
	m_pParam->SetParamDouble(DOUBLE_PARAM_ORIGINX,QGlobal::ATOF(str));
	
	GetDlgItem(IDC_EDIT_Y1)->GetWindowText(str);
	m_pParam->SetParamDouble(DOUBLE_PARAM_ORIGINY,QGlobal::ATOF(str));

	 

	
}