// D:\项目\EzCad3_VS2015\EzCad3_VS2015\Mark\DlgSplitParam.cpp : 实现文件
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "DlgSplitParam.h"
#include "afxdialogex.h"
#include "QGlobal.h"
#include "QDlg.h"
// CDlgSplitParam 对话框

IMPLEMENT_DYNAMIC(CDlgSplitParam, CDialogEx)

CDlgSplitParam::CDlgSplitParam(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SPLITPARAM, pParent)
{
	m_nSplitModeX = 0;
	m_dSplitSizeX = 1;

	m_nSplitModeY = 0;
	m_dSplitSizeY = 1;

	m_bSphereWrap = FALSE;
	m_bRevolveWrap = FALSE;
	m_bShowSphereWrap = FALSE;
	m_bNoCutEntity = FALSE;
	m_bUseSplitCenAsMarkingCen = FALSE;
	m_bEnableA = FALSE;
	m_bMark360 = FALSE;
	m_nMarkCount = 1;
	m_dMarkAngle = 90;
	m_bHideX = FALSE;
	m_bHideY = FALSE;
	m_bSplitByGLB = FALSE;
	m_bDisableAxisA = FALSE;
	m_bShowDisableA = FALSE;
	m_bCylinderWrap = FALSE;
	m_bShowCylinderWrap = FALSE;
	m_nSplitAttrib = 0;
}

CDlgSplitParam::~CDlgSplitParam()
{
}

void CDlgSplitParam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_MODE, m_comboModeX);
	DDX_Control(pDX, IDC_COMBO_MODE2, m_comboModeY);
}


BEGIN_MESSAGE_MAP(CDlgSplitParam, CDialogEx)
 
	ON_BN_CLICKED(IDOK, &CDlgSplitParam::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_KEEPORDER, &CDlgSplitParam::OnBnClickedCheckKeeporder)
	ON_CBN_SELCHANGE(IDC_COMBO_MODE, &CDlgSplitParam::OnCbnSelchangeComboMode)
	ON_CBN_SELCHANGE(IDC_COMBO_MODE2, &CDlgSplitParam::OnCbnSelchangeComboModeY)
	ON_BN_CLICKED(IDC_CHECK_REVOLVEWARP, &CDlgSplitParam::OnBnClickedCheckRevolvewarp)
	ON_BN_CLICKED(IDC_CHECK_SPHEREWARP, &CDlgSplitParam::OnBnClickedCheckSpherewarp)
	ON_BN_CLICKED(IDC_CHECK_CYLINDERWARP, &CDlgSplitParam::OnBnClickedCheckCylinderwarp)
	ON_BN_CLICKED(IDC_BUTTON_COUNT, &CDlgSplitParam::OnBnClickedButtonCount)
	ON_BN_CLICKED(IDC_BUTTON_ANGLE, &CDlgSplitParam::OnBnClickedButtonAngle)
	ON_BN_CLICKED(IDC_CHECK_360, &CDlgSplitParam::OnBnClickedCheck360)
	ON_BN_CLICKED(IDC_CHECK_DISABLEAXISA, &CDlgSplitParam::OnBnClickedCheckDisableaxisa)
END_MESSAGE_MAP()


// CDlgSplitParam 消息处理程序

 

BOOL CDlgSplitParam::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	GetDlgItem(IDC_CHECK_CYLINDERWARP)->ShowWindow(m_bShowCylinderWrap ? SW_SHOW : SW_HIDE);

	GetDlgItem(IDC_CHECK_SPHEREWARP)->ShowWindow(m_bShowSphereWrap ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_CHECK_REVOLVEWRAP)->ShowWindow(m_bShowSphereWrap ? SW_SHOW : SW_HIDE);

	GetDlgItem(IDOK)->SetWindowText(QGlobal::gf_Str(_T("IDOK"), _T("&OK")));
	GetDlgItem(IDCANCEL)->SetWindowText(QGlobal::gf_Str(_T("IDCANCEL"), _T("&Cancel")));

	SetWindowText(QGlobal::gf_Str(_T("SPLITPARAM"), _T("Split param.")));
	GetDlgItem(IDC_STATIC_SPLITSIZE)->SetWindowText(QGlobal::gf_Str(_T("SPLITSIZE"), _T("Split size")));
	GetDlgItem(IDC_STATIC_SPLITSIZE2)->SetWindowText(QGlobal::gf_Str(_T("SPLITSIZE"), _T("Split size")));

	GetDlgItem(IDC_STATIC_UNIT1)->SetWindowText(QGlobal::gf_GetUnitStr());
	GetDlgItem(IDC_STATIC_UNIT5)->SetWindowText(QGlobal::gf_GetUnitStr());

	
	GetDlgItem(IDC_CHECK_CYLINDERWARP)->SetWindowText(QGlobal::gf_Str(_T("CYLINDERWRAP"), _T("Cylinder wrap"))); 
	GetDlgItem(IDC_CHECK_SPHEREWARP)->SetWindowText(QGlobal::gf_Str(_T("SPHEREWRAP"), _T("Sphere wrap")));
	GetDlgItem(IDC_CHECK_REVOLVEWRAP)->SetWindowText(QGlobal::gf_Str(_T("REVOLVEWRAP"), _T("Revolve wrap")));

	GetDlgItem(IDC_CHECK_KEEPORDER)->SetWindowText(QGlobal::gf_Str(_T("KEEPENTORDER"), _T("Keep entity order")));
	GetDlgItem(IDC_CHECK_NOCUTENTITY)->SetWindowText(QGlobal::gf_Str(_T("NOCUTENTITY"), _T("No cut entity")));
	GetDlgItem(IDC_CHECK_NOCUTTEXT)->SetWindowText(QGlobal::gf_Str(_T("NOCUTTEXT"), _T("No cut text")));
	
	GetDlgItem(IDC_CHECK_USESPLITBOXCEN)->SetWindowText(QGlobal::gf_Str(_T("USESPLITBOXCENASMARKCEN"), _T("Use split box center as marking center")));
	GetDlgItem(IDC_CHECK_SPLITBYGUIDELINEBOX)->SetWindowText(QGlobal::gf_Str(_T("SPLITBYGUIDELINEBOX"), _T("Split by guideline box")));
	GetDlgItem(IDC_CHECK_DISABLEAXISA)->SetWindowText(QGlobal::gf_Str(_T("DISABLEAXISA"), _T("Disable Axis A")));

	GetDlgItem(IDC_BUTTON_COUNT)->SetWindowText(QGlobal::gf_Str(_T("COUNT"), _T("Count")));
	GetDlgItem(IDC_BUTTON_ANGLE)->SetWindowText(QGlobal::gf_Str(_T("ANGLE"), _T("Angle")));
	GetDlgItem(IDC_CHECK_360)->SetWindowText(QGlobal::gf_Str(_T("360MARK"), _T("360 degree mark")));

	GetDlgItem(IDC_CHECK_YFIRST)->SetWindowText(QGlobal::gf_Str(_T("MENU_SORT_BYY"), _T("Sort by Y")));


	
	GetDlgItem(IDC_EDIT_SPLITSIZE)->SetWindowText(QGlobal::gf_GetLenStr(m_dSplitSizeX));
	GetDlgItem(IDC_EDIT_SPLITSIZEY)->SetWindowText(QGlobal::gf_GetLenStr(m_dSplitSizeY));

	UpdateWrapType();

	GetDlgItem(IDC_CHECK_INVERTX)->SetWindowText(QGlobal::gf_Str(_T("INVERT"), _T("Invert")));
	GetDlgItem(IDC_CHECK_INVERTY)->SetWindowText(QGlobal::gf_Str(_T("INVERT"), _T("Invert")));

	
	((CButton*)GetDlgItem(IDC_CHECK_INVERTX))->SetCheck(m_nSplitAttrib&SPLITATT_INVERT_X);
	((CButton*)GetDlgItem(IDC_CHECK_INVERTY))->SetCheck(m_nSplitAttrib & SPLITATT_INVERT_Y);
	((CButton*)GetDlgItem(IDC_CHECK_NOCUTTEXT))->SetCheck(m_nSplitAttrib & SPLITATT_NOTCUT_CHAR);
	((CButton*)GetDlgItem(IDC_CHECK_YFIRST))->SetCheck(m_nSplitAttrib & SPLITATT_YFIRST);

	
	((CButton*)GetDlgItem(IDC_CHECK_SPLITBYGUIDELINEBOX))->SetCheck(m_bSplitByGLB);
	((CButton*)GetDlgItem(IDC_CHECK_KEEPORDER ))->SetCheck(m_bKeepEntOrder);
	((CButton*)GetDlgItem(IDC_CHECK_NOCUTENTITY))->SetCheck(m_bNoCutEntity);
	((CButton*)GetDlgItem(IDC_CHECK_USESPLITBOXCEN))->SetCheck(m_bUseSplitCenAsMarkingCen);
	
	((CButton*)GetDlgItem(IDC_CHECK_DISABLEAXISA))->SetCheck(m_bDisableAxisA); 
	GetDlgItem(IDC_CHECK_DISABLEAXISA)->ShowWindow(m_bShowDisableA?SW_SHOW:SW_HIDE);
	
	((CButton*)GetDlgItem(IDC_CHECK_360))->SetCheck(m_bMark360); 


	GetDlgItem(IDC_STATIC_COUNT)->SetWindowText(QGlobal::gf_GetIntStr(m_nMarkCount));
	GetDlgItem(IDC_STATIC_ANGLE)->SetWindowText(QGlobal::gf_GetLenStr(m_dMarkAngle)); 

	if (m_bEnableA)
	{
		GetDlgItem(IDC_STATIC_A)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_360)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_COUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_COUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_ANGLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_ANGLE)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_BUTTON_ANGLE)->EnableWindow(!m_bMark360);
	}

	

 
	GetDlgItem(IDC_STATIC_SPLITMODE)->SetWindowText(QGlobal::gf_Str(_T("SPLITMODE"), _T("Split mode")));

	m_comboModeX.AddString(QGlobal::gf_Str(_T("NOSPLIT"), _T("No split")));
	m_comboModeX.AddString(QGlobal::gf_Str(_T("SPLITBYSIZE"), _T("Split by size")));
	m_comboModeX.AddString(QGlobal::gf_Str(_T("SPLITBYGUILDLINE"), _T("Split by guildline")));

	m_comboModeX.SetCurSel(m_nSplitModeX);


	GetDlgItem(IDC_STATIC_SPLITMODE2)->SetWindowText(QGlobal::gf_Str(_T("SPLITMODE"), _T("Split mode")));

	m_comboModeY.AddString(QGlobal::gf_Str(_T("NOSPLIT"), _T("No split")));
	m_comboModeY.AddString(QGlobal::gf_Str(_T("SPLITBYSIZE"), _T("Split by size")));
	m_comboModeY.AddString(QGlobal::gf_Str(_T("SPLITBYGUILDLINE"), _T("Split by guildline")));

	m_comboModeY.SetCurSel(m_nSplitModeY);

	UpdataModeX();
	UpdataModeY();

	if (m_bHideX)
	{
		GetDlgItem(IDC_STATIC_X)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SPLITMODE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_MODE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SPLITSIZE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_SPLITSIZE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_UNIT1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_INVERTX)->ShowWindow(SW_HIDE);
	}
	if (m_bHideY)
	{
		GetDlgItem(IDC_STATIC_Y)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SPLITMODE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_MODE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SPLITSIZE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_SPLITSIZEY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_UNIT5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_INVERTY)->ShowWindow(SW_HIDE);
	}


	if (m_bHideX|| m_bHideY)
	{
		GetDlgItem(IDC_CHECK_YFIRST)->ShowWindow(SW_HIDE); 
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void CDlgSplitParam::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bSplitByGLB = ((CButton*)GetDlgItem(IDC_CHECK_SPLITBYGUIDELINEBOX))->GetCheck();
	m_bKeepEntOrder = ((CButton*)GetDlgItem(IDC_CHECK_KEEPORDER))->GetCheck(); 
	m_bCylinderWrap = ((CButton*)GetDlgItem(IDC_CHECK_CYLINDERWARP))->GetCheck();
	m_bRevolveWrap = ((CButton*)GetDlgItem(IDC_CHECK_REVOLVEWRAP))->GetCheck( );
	m_bSphereWrap = ((CButton*)GetDlgItem(IDC_CHECK_SPHEREWARP))->GetCheck(); 
	m_bNoCutEntity = ((CButton*)GetDlgItem(IDC_CHECK_NOCUTENTITY))->GetCheck();
	m_bUseSplitCenAsMarkingCen = ((CButton*)GetDlgItem(IDC_CHECK_USESPLITBOXCEN))->GetCheck();
	m_bDisableAxisA = ((CButton*)GetDlgItem(IDC_CHECK_DISABLEAXISA))->GetCheck();

	m_nSplitAttrib = 0;
	if (((CButton*)GetDlgItem(IDC_CHECK_INVERTX))->GetCheck())
	{
		m_nSplitAttrib |= SPLITATT_INVERT_X;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK_INVERTY))->GetCheck())
	{
		m_nSplitAttrib |= SPLITATT_INVERT_Y;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK_NOCUTTEXT))->GetCheck())
	{
		m_nSplitAttrib |= SPLITATT_NOTCUT_CHAR;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK_YFIRST))->GetCheck())
	{
		m_nSplitAttrib |= SPLITATT_YFIRST;
	}
	 
 
	CString str;
	GetDlgItem(IDC_EDIT_SPLITSIZE)->GetWindowText(str);

	m_dSplitSizeX = QGlobal::ATOF(str);
	if (m_dSplitSizeX < 0.001)
	{
		m_dSplitSizeX = 0.001;
	}
	else if (m_dSplitSizeX >1000)
	{
		m_dSplitSizeX = 1000;
	} 
	GetDlgItem(IDC_EDIT_SPLITSIZEY)->GetWindowText(str);

	m_dSplitSizeY = QGlobal::ATOF(str);
	if (m_dSplitSizeY < 0.001)
	{
		m_dSplitSizeY = 0.001;
	}
	else if (m_dSplitSizeY >1000)
	{
		m_dSplitSizeY = 1000;
	}
	CDialogEx::OnOK();
}


void CDlgSplitParam::OnBnClickedCheckKeeporder()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgSplitParam::OnCbnSelchangeComboMode()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nSplitModeX = m_comboModeX.GetCurSel();
	UpdataModeX();
}
void CDlgSplitParam::OnCbnSelchangeComboModeY()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nSplitModeY = m_comboModeY.GetCurSel();
	UpdataModeY();
}

void CDlgSplitParam::UpdataModeX()
{
	GetDlgItem(IDC_EDIT_SPLITSIZE)->EnableWindow(m_nSplitModeX==1?TRUE:FALSE);
//	GetDlgItem(IDC_CHECK_KEEPORDER)->EnableWindow(m_nSplitMode != 0 ? TRUE : FALSE); 
}
void CDlgSplitParam::UpdataModeY()
{
	GetDlgItem(IDC_EDIT_SPLITSIZEY)->EnableWindow(m_nSplitModeY == 1 ? TRUE : FALSE); 
}

void CDlgSplitParam::OnBnClickedCheckRevolvewarp()
{
	// TODO: 在此添加控件通知处理程序代码
 
	m_bRevolveWrap = ((CButton*)GetDlgItem(IDC_CHECK_REVOLVEWRAP))->GetCheck( );
	m_bCylinderWrap = false;
	m_bSphereWrap = false;

	UpdateWrapType();
	 
}
void CDlgSplitParam::UpdateWrapType()
{
	if (m_bCylinderWrap)
	{
		((CButton*)GetDlgItem(IDC_CHECK_CYLINDERWARP))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_SPHEREWARP))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_REVOLVEWRAP))->SetCheck(FALSE);
	}
	else if (m_bRevolveWrap)
	{
		((CButton*)GetDlgItem(IDC_CHECK_CYLINDERWARP))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_SPHEREWARP))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_REVOLVEWRAP))->SetCheck(TRUE);
	}
	else if (m_bSphereWrap)
	{
		((CButton*)GetDlgItem(IDC_CHECK_CYLINDERWARP))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_SPHEREWARP))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_REVOLVEWRAP))->SetCheck(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_CYLINDERWARP))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_SPHEREWARP))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_REVOLVEWRAP))->SetCheck(FALSE);
	}
}

void CDlgSplitParam::OnBnClickedCheckSpherewarp()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bSphereWrap =  ((CButton*)GetDlgItem(IDC_CHECK_SPHEREWARP))->GetCheck();
	m_bCylinderWrap = false; 
	m_bRevolveWrap = false;
	UpdateWrapType();
}

void CDlgSplitParam::OnBnClickedCheckCylinderwarp()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bCylinderWrap  = ((CButton*)GetDlgItem(IDC_CHECK_CYLINDERWARP))->GetCheck();
	m_bRevolveWrap = false;
	m_bSphereWrap = false;
	UpdateWrapType();
}


void CDlgSplitParam::OnBnClickedButtonCount()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strText= QGlobal::gf_GetIntStr(m_nMarkCount);
	if (gf_DlgInputOne(NULL, strText, QGlobal::gf_Str(_T("COUNT"), _T("Count")), _T("")) == IDOK)
	{
		m_nMarkCount = QGlobal::ATOI(strText);
		if (m_nMarkCount < 1)
		{
			m_nMarkCount = 1;
		}
		GetDlgItem(IDC_STATIC_COUNT)->SetWindowText(QGlobal::gf_GetIntStr(m_nMarkCount));
	}
}


void CDlgSplitParam::OnBnClickedButtonAngle()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strText = QGlobal::gf_GetLenStr(m_dMarkAngle);
	if (gf_DlgInputOne(NULL, strText, QGlobal::gf_Str(_T("ANGLE"), _T("Angle")), _T("")) == IDOK)
	{
		m_dMarkAngle = QGlobal::ATOF(strText); 
		GetDlgItem(IDC_STATIC_ANGLE)->SetWindowText(QGlobal::gf_GetLenStr(m_dMarkAngle)); 
	}
}


void CDlgSplitParam::OnBnClickedCheck360()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bMark360 = ((CButton*)GetDlgItem(IDC_CHECK_360))->GetCheck();
	GetDlgItem(IDC_BUTTON_ANGLE)->EnableWindow(!m_bMark360);
}


void CDlgSplitParam::OnBnClickedCheckDisableaxisa()
{
	// TODO: 在此添加控件通知处理程序代码
}
