// dlgmarkadvance.cpp : implementation file
//

#include "stdafx.h"
#include "..\ezcad3.h"
#include "dlgmarkadvance.h"
#include "qglobal.h"
#include "SysParam.h"
#include "qmath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMarkAdvance dialog


CDlgMarkAdvance::CDlgMarkAdvance(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMarkAdvance::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMarkAdvance)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	m_dJumpSpeed = 1000;
	m_nJumpPosTC = 0;
	m_nJumpDistTC =0;
	
	m_dEndComp = 0;
	m_dAccDist = 0;
	m_dPointTime= 0.1;

	m_bPulsePointMode=FALSE;
	m_nPulseNum=1;
		m_bYagOptimizeMode = FALSE;
		m_bYagOptimizeInterlace = FALSE;

		m_bWobble = FALSE;
		m_dWobbleDiameter=1;
		m_dWobbleDist = 0.5;

		//Ä©Î²¼Óµã
		m_bEndAddPt=FALSE;
		m_nEndPointNum=1;
		m_dEndPointDist=0.01;
		m_dEndPointTime=1.0;
		m_nEndPointCyc=1;
}


void CDlgMarkAdvance::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMarkAdvance)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMarkAdvance, CDialog)
	//{{AFX_MSG_MAP(CDlgMarkAdvance)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK_PULSEMODE, OnCheckPulse)
	ON_BN_CLICKED(IDC_CHECK_YAGOPTIM, OnCheckOptim)
	
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMarkAdvance message handlers

BOOL CDlgMarkAdvance::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText(QGlobal::gf_Str(_T("ADVANCEMARKPARAM"),_T("Advance mark param")));

	GetDlgItem(IDOK)->SetWindowText(QGlobal::gf_Str(_T("IDOK"),_T("&OK")));
	GetDlgItem(IDCANCEL)->SetWindowText(QGlobal::gf_Str(_T("IDCANCEL"),_T("&Cancel")));

	CString strUnit = QGlobal::gf_GetUnitStr();
	GetDlgItem(IDC_STATIC_UNIT1)->SetWindowText(strUnit);	  
	GetDlgItem(IDC_STATIC_UNIT2)->SetWindowText(strUnit);
	GetDlgItem(IDC_STATIC_UNIT3)->SetWindowText(strUnit);	  
	GetDlgItem(IDC_STATIC_UNIT4)->SetWindowText(strUnit);
	
	//GetDlgItem(IDC_STATIC_SPDUNIT)->SetWindowText(strUnit+"/"+QGlobal::gf_Str(_T("SECOND"),_T("s")));

	GetDlgItem(IDC_STATIC_US)->SetWindowText(QGlobal::gf_Str(_T("US"),_T("us")));
	GetDlgItem(IDC_STATIC_US2)->SetWindowText(QGlobal::gf_Str(_T("US"),_T("us")));
	
	GetDlgItem(IDC_STATIC_JUMPSPEED)->SetWindowText(QGlobal::gf_Str(_T("JUMPSPEED"),_T("Jump Speed")));
	GetDlgItem(IDC_STATIC_JUMPPOSTC)->SetWindowText(QGlobal::gf_Str(_T("JUMPPOSTC"),_T("Jump Position TC")));
	GetDlgItem(IDC_STATIC_JUMPDISTTC)->SetWindowText(QGlobal::gf_Str(_T("JUMPDISTTC"),_T("Jump Dist TC")));
	
	GetDlgItem(IDC_STATIC_ENDCOMP)->SetWindowText(QGlobal::gf_Str(_T("ENDCOMP"),_T("End compensate")));
	GetDlgItem(IDC_STATIC_ACCDIST)->SetWindowText(QGlobal::gf_Str(_T("ACCDIST"),_T("Acc. Distance")));
	GetDlgItem(IDC_STATIC_POINTTIME)->SetWindowText(QGlobal::gf_Str(_T("POINTTIME"),_T("Point time")));
	

	GetDlgItem(IDC_EDIT_JUMPSPD)->SetWindowText(QGlobal::gf_GetLenStr(m_dJumpSpeed) );

	GetDlgItem(IDC_EDIT_ENDCOMP)->SetWindowText(QGlobal::gf_GetLenStr(m_dEndComp) );
	GetDlgItem(IDC_EDIT_ACCDIST)->SetWindowText(QGlobal::gf_GetLenStr(m_dAccDist) );
	GetDlgItem(IDC_EDIT_POINTTIME)->SetWindowText(QGlobal::gf_GetLenStr(m_dPointTime) );

	GetDlgItem(IDC_CHECK_PULSEMODE)->SetWindowText(QGlobal::gf_Str(_T("PULSEMODE"),_T("vector point mode")));
	GetDlgItem(IDC_STATIC_PULSEPER)->SetWindowText(QGlobal::gf_Str(_T("PULSEPER"),_T("Pulse per point")));

	GetDlgItem(IDC_CHECK_YAGOPTIM)->SetWindowText(QGlobal::gf_Str(_T("YAGOPTIMIZEMODE"),_T("Yag Optimize mode")));

	GetDlgItem(IDC_CHECK1)->SetWindowText(QGlobal::gf_Str(_T("WOBBLE"),_T("Wobble")));
	GetDlgItem(IDC_STATIC_DIA)->SetWindowText(QGlobal::gf_Str(_T("DIAMETER"),_T("Diameter")));
	GetDlgItem(IDC_STATIC_DIST)->SetWindowText(QGlobal::gf_Str(_T("WOBBLEDIST"),_T("Distance")));
	
	GetDlgItem(IDC_CHECK2)->SetWindowText(QGlobal::gf_Str(_T("ENDADDPTS"),_T("End Add Points")));
	GetDlgItem(IDC_STATIC_ENDNUM)->SetWindowText(QGlobal::gf_Str(_T("COUNT"),_T("Count")));
	GetDlgItem(IDC_STATIC_PTDIST)->SetWindowText(QGlobal::gf_Str(_T("DISTANCE"),_T("Distance")));
	GetDlgItem(IDC_STATIC_POINTTIME2)->SetWindowText(QGlobal::gf_Str(_T("POINTTIME"),_T("Point time")));
	GetDlgItem(IDC_STATIC_PTCYC)->SetWindowText(QGlobal::gf_Str(_T("PTCYCLES"),_T("Point Cycles")));
	GetDlgItem(IDC_STATIC_UNIT5)->SetWindowText(strUnit);

	CString str;
	str.Format(_T("%d"),m_nJumpPosTC);
	GetDlgItem(IDC_EDIT_POSTC)->SetWindowText(str);

	str.Format(_T("%d"),m_nJumpDistTC);
	GetDlgItem(IDC_EDIT_DISTTC)->SetWindowText(str);
	

	str.Format(_T("%d"),m_nPulseNum);
	GetDlgItem(IDC_EDIT_NUM)->SetWindowText(str);

	

	((CButton*)GetDlgItem(IDC_CHECK_PULSEMODE))->SetCheck(m_bPulsePointMode);
	if(m_bPulsePointMode)
	{
		GetDlgItem(IDC_EDIT_NUM)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_NUM)->EnableWindow(FALSE);
	}
	((CButton*)GetDlgItem(IDC_CHECK_YAGOPTIM))->SetCheck(m_bYagOptimizeMode);
	

	if( m_bYagOptimizeInterlace )
		((CButton*)GetDlgItem(IDC_BUTTON1))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_OPTMIZE2));
	else
		((CButton*)GetDlgItem(IDC_BUTTON1))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_OPTMIZE1));

	if(!m_bYagOptimizeMode)
	{
		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);	
	}

	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(m_bWobble);
	GetDlgItem(IDC_EDIT_DIA)->SetWindowText(QGlobal::gf_GetLenStr(m_dWobbleDiameter));
	GetDlgItem(IDC_EDIT_DIST)->SetWindowText(QGlobal::gf_GetLenStr(m_dWobbleDist));	


	((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(m_bEndAddPt);
	str.Format(_T("%d"),m_nEndPointNum);
	GetDlgItem(IDC_EDIT_PTCOUNT)->SetWindowText(str);
	
	GetDlgItem(IDC_EDIT_PTDIST)->SetWindowText(QGlobal::gf_GetLenStr(m_dEndPointDist));	
	str.Format(_T("%.3f"),m_dEndPointTime);
	GetDlgItem(IDC_EDIT_POINTTIME2)->SetWindowText(str);
	str.Format(_T("%d"),m_nEndPointCyc);
	GetDlgItem(IDC_EDIT_PTCOUNT2)->SetWindowText(str);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMarkAdvance::OnButton1() 
{
	m_bYagOptimizeInterlace = !m_bYagOptimizeInterlace;
	if( m_bYagOptimizeInterlace )
		((CButton*)GetDlgItem(IDC_BUTTON1))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_OPTMIZE2));
	else
		((CButton*)GetDlgItem(IDC_BUTTON1))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_OPTMIZE1));
}
void CDlgMarkAdvance::OnCheckOptim() 
{
	// TODO: Add your control notific
	m_bYagOptimizeMode = !m_bYagOptimizeMode;
	((CButton*)GetDlgItem(IDC_CHECK_YAGOPTIM))->SetCheck(m_bYagOptimizeMode);
	if(m_bYagOptimizeMode)
	{
		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW);	
	}
	else
	{
		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);	
	}
}

void CDlgMarkAdvance::OnCheckPulse() 
{
	// TODO: Add your control notification handler code here

	m_bPulsePointMode = !m_bPulsePointMode;
	((CButton*)GetDlgItem(IDC_CHECK_PULSEMODE))->SetCheck(m_bPulsePointMode);
	if(m_bPulsePointMode)
	{
		GetDlgItem(IDC_EDIT_NUM)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_NUM)->EnableWindow(FALSE);
	}

	
}

void CDlgMarkAdvance::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	CString str;
	GetDlgItem(IDC_EDIT_POSTC)->GetWindowText(str);
	m_nJumpPosTC = _ttoi(str);	
	if(m_nJumpPosTC<0)
		m_nJumpPosTC=0;

	GetDlgItem(IDC_EDIT_DISTTC)->GetWindowText(str);
	m_nJumpDistTC = _ttoi(str);	
	if(m_nJumpDistTC<0)
		m_nJumpDistTC=0;

	GetDlgItem(IDC_EDIT_JUMPSPD)->GetWindowText(str);
	m_dJumpSpeed = QGlobal::ATOF(str);
	if(m_dJumpSpeed<0.001)
		m_dJumpSpeed=0.001;



	GetDlgItem(IDC_EDIT_ENDCOMP)->GetWindowText(str);
	m_dEndComp = QGlobal::ATOF(str);
	if(m_dEndComp<0)
		m_dEndComp=0;


	GetDlgItem(IDC_EDIT_ACCDIST)->GetWindowText(str);
	m_dAccDist = QGlobal::ATOF(str);
	if(m_dAccDist<0)
		m_dAccDist=0;
	
	GetDlgItem(IDC_EDIT_POINTTIME)->GetWindowText(str);
	m_dPointTime = QGlobal::ATOF(str);
	if(m_dPointTime<0.001)
		m_dPointTime=0.001;


	GetDlgItem(IDC_EDIT_NUM)->GetWindowText(str);
	m_nPulseNum = _ttoi(str);
	if(m_nPulseNum<1)
		m_nPulseNum=1;
	if(m_nPulseNum>1000)
		m_nPulseNum=1000;


	m_bPulsePointMode = ((CButton*)GetDlgItem(IDC_CHECK_PULSEMODE))->GetCheck();

	m_bYagOptimizeMode = ((CButton*)GetDlgItem(IDC_CHECK_YAGOPTIM))->GetCheck();
	
	m_bWobble = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	GetDlgItem(IDC_EDIT_DIA)->GetWindowText(str);
	m_dWobbleDiameter = QGlobal::ATOF(str);
	if(gf_GetSysParam()->GetParamInt(INT_PARAM_UNITTYPE)==UNIT_MM)
	{
		if(m_dWobbleDiameter<0.01)
			m_dWobbleDiameter=0.01;
		if(m_dWobbleDiameter>100)
			m_dWobbleDiameter=100;
	}
	else
	{
		if(m_dWobbleDiameter<0.001)
			m_dWobbleDiameter=0.001;
	}
	
	GetDlgItem(IDC_EDIT_DIST)->GetWindowText(str);
	m_dWobbleDist = QGlobal::ATOF(str);
	if(gf_GetSysParam()->GetParamInt(INT_PARAM_UNITTYPE)==UNIT_MM)
	{
		if(m_dWobbleDist<0.01)
			m_dWobbleDist=0.01;
		if(m_dWobbleDist>100)
			m_dWobbleDist=100;
	}
	else
	{
		if(m_dWobbleDist<0.001)
			m_dWobbleDist=0.001;
	}



	
	m_bEndAddPt = ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck();
	
	GetDlgItem(IDC_EDIT_PTCOUNT)->GetWindowText(str);
	m_nEndPointNum = _ttoi(str);	

	GetDlgItem(IDC_EDIT_PTDIST)->GetWindowText(str);	
	m_dEndPointDist = QGlobal::ATOF(str);

	GetDlgItem(IDC_EDIT_POINTTIME2)->GetWindowText(str);
	m_dEndPointTime = QGlobal::ATOF(str);

	GetDlgItem(IDC_EDIT_PTCOUNT2)->GetWindowText(str);	
	m_nEndPointCyc = _ttoi(str);		
}
