// D:\项目\EzCad3_VS2015\EzCad3_VS2015\Mark\DlgMotionPanel.cpp : 实现文件
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "DlgMotionPanel.h"
#include "afxdialogex.h"
#include "QGlobal.h"
#include "qMotorMgr.h"
#include "qdlg.h"
#include "DlgSplitParam.h"
#include "QUser.h"
#include "usermessdef.h"
#include "Markstd\DlgMark.h"
#include "Qinifile.h"

// CDlgMotionPanel 对话框

IMPLEMENT_DYNAMIC(CDlgMotionPanel, CDialogEx)

CDlgMotionPanel::CDlgMotionPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MOTIONPANEL, pParent)
{ 
	m_bHideFocusPos = FALSE;
	m_bHideOrigin = FALSE;
	m_bEnableAutoFocus = FALSE;
}

CDlgMotionPanel::~CDlgMotionPanel()
{
	if (m_bEnableAutoFocus)
	{
		E3_AutoFocusClose();
		m_bEnableAutoFocus = FALSE;
	}
}

void CDlgMotionPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_UP, m_buttonUp);
	DDX_Control(pDX, IDC_BUTTON_DOWN, m_buttonDown);
	DDX_Control(pDX, IDC_BUTTON_UPZ, m_buttonUpZ);
	DDX_Control(pDX, IDC_BUTTON_DOWNZ, m_buttonDownZ);
	DDX_Control(pDX, IDC_BUTTON_LEFT, m_buttonLeft);
	DDX_Control(pDX, IDC_BUTTON_RIGHT, m_buttonRight);
	DDX_Control(pDX, IDC_BUTTON_ACCW, m_buttonACCW);
	DDX_Control(pDX, IDC_BUTTON_ACW, m_buttonACW);
	DDX_Control(pDX, IDC_BUTTON_PREVIEW, m_buttonWrap);
	DDX_Control(pDX, IDC_BUTTON_AUTOFOCUS, m_buttonAutoFocus);
	DDX_Control(pDX, IDC_BUTTON_PREVIEW2, m_buttonPreviewSplitBox); 
}


BEGIN_MESSAGE_MAP(CDlgMotionPanel, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgMotionPanel::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgMotionPanel::OnBnClickedCancel) 
	ON_BN_CLICKED(IDC_BUTTON_UP, &CDlgMotionPanel::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CDlgMotionPanel::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CDlgMotionPanel::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CDlgMotionPanel::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_PARTHEIGHT, &CDlgMotionPanel::OnBnClickedButtonPartheight)
	ON_BN_CLICKED(IDC_BUTTON_FOCUS, &CDlgMotionPanel::OnBnClickedButtonFocus)
	ON_BN_CLICKED(IDC_BUTTON_HOME, &CDlgMotionPanel::OnBnClickedButtonHome)
	ON_BN_CLICKED(IDC_BUTTON_SPLITPARAM, &CDlgMotionPanel::OnBnClickedButtonSplitparam)
	ON_BN_CLICKED(IDC_BUTTON_DOWNZ, &CDlgMotionPanel::OnBnClickedButtonDownz)
	ON_BN_CLICKED(IDC_BUTTON_UPZ, &CDlgMotionPanel::OnBnClickedButtonUpz)
	ON_BN_CLICKED(IDC_BUTTON_GOORG, &CDlgMotionPanel::OnBnClickedButtonGoorg)
	ON_BN_CLICKED(IDC_BUTTON_ORG, &CDlgMotionPanel::OnBnClickedButtonOrg)

	ON_BN_CLICKED(IDC_BUTTON_ACCW, &CDlgMotionPanel::OnBnClickedButtonACCW)
	ON_BN_CLICKED(IDC_BUTTON_ACW, &CDlgMotionPanel::OnBnClickedButtonACW)

	ON_MESSAGE(WM_USER_CHANGECURLAYER, OnUserChangeCurLayer)
	ON_BN_CLICKED(IDC_BUTTON_PARTDIAMETER, &CDlgMotionPanel::OnBnClickedButtonPartdiameter)
	ON_BN_CLICKED(IDC_BUTTON_HANDWHEEL, &CDlgMotionPanel::OnBnClickedButtonHandwheel)
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW, &CDlgMotionPanel::OnBnClickedButtonPreview)
	ON_BN_CLICKED(IDC_BUTTON_AUTOFOCUS, &CDlgMotionPanel::OnBnClickedButtonAutofocus)
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW2, &CDlgMotionPanel::OnBnClickedButtonPreview2)
END_MESSAGE_MAP()


// CDlgMotionPanel 消息处理程序


void CDlgMotionPanel::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CDlgMotionPanel::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
}

 
void CDlgMotionPanel::OnKeyUp()
{
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	} 
	pDlg->LockMarker();
	PMarker pMarker = pDlg->GetMarker();	 

	if (pMarker!=NULL && E3_MarkerGetAxisSol(pMarker) == MOTOR_SOL_Z)
	{
		pDlg->UnLockMarker();
		OnBnClickedButtonUpz();
	}
	else
	{
		pDlg->UnLockMarker();
		OnBnClickedButtonUp();
	}
}

void CDlgMotionPanel::OnKeyDown() 
{
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	}
	pDlg->LockMarker();
	PMarker pMarker = pDlg->GetMarker();
	if (pMarker!=NULL && E3_MarkerGetAxisSol(pMarker) == MOTOR_SOL_Z)
	{
		pDlg->UnLockMarker();
		OnBnClickedButtonDownz();
	}
	else
	{
		pDlg->UnLockMarker();
		OnBnClickedButtonDown();
	}
}
void CDlgMotionPanel::OnKeyLeft()
{
	OnBnClickedButtonLeft();
}

void CDlgMotionPanel::OnKeyRight()
{
	OnBnClickedButtonRight();
}
void CDlgMotionPanel::OnBnClickedButtonUp()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT_STEP)->GetWindowText(str);
	gf_GetMotorMgr()->m_dStepDist = QGlobal::ATOF(str);

	if (gf_GetMotorMgr()->GetMotor(MOTOR_Y)->m_bEnable)
	{//Y
		double y = gf_GetMotorMgr()->GetMotor(MOTOR_Y)->m_dCmdPos;
		if (gf_GetMotorMgr()->m_bTableMoveY)
		{
			MoveY(y - gf_GetMotorMgr()->m_dStepDist);
		}
		else
		{
			MoveY(y + gf_GetMotorMgr()->m_dStepDist);
		}
	}
	else if (gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_bEnable && gf_GetMotorMgr()->m_nAasMode == MOTOR_A_AS_Y)
	{
		PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
		if (pEM == NULL)
		{
			return;
		}

		PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
		ASSERT(pLayer != NULL); 
		double dDiameter = E3_GetCurLayerDiamater(pLayer );
		double dPerimeter = dDiameter * PAI;
		double dAng = 360 * gf_GetMotorMgr()->m_dStepDist / dPerimeter;
		double a = gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_dCmdPos;		
		MoveA(a + dAng);
	}
}



void CDlgMotionPanel::OnBnClickedButtonDown()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT_STEP)->GetWindowText(str);
	gf_GetMotorMgr()->m_dStepDist = QGlobal::ATOF(str);
	if (gf_GetMotorMgr()->GetMotor(MOTOR_Y)->m_bEnable)
	{//Y
		double y = gf_GetMotorMgr()->GetMotor(MOTOR_Y)->m_dCmdPos;
		if (gf_GetMotorMgr()->m_bTableMoveY)
		{
			MoveY(y + gf_GetMotorMgr()->m_dStepDist);
		}
		else
		{
			MoveY(y - gf_GetMotorMgr()->m_dStepDist);
		}
	}
	else if (gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_bEnable && gf_GetMotorMgr()->m_nAasMode == MOTOR_A_AS_Y)
	{
		PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
		if (pEM == NULL)
		{
			return;
		}

		PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
		ASSERT(pLayer != NULL);
		double dDiameter = E3_GetCurLayerDiamater(pLayer);
		double dPerimeter = dDiameter * PAI;
		double dAng = 360 * gf_GetMotorMgr()->m_dStepDist / dPerimeter;
		double a = gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_dCmdPos;
		MoveA(a - dAng);
	}
}

void CDlgMotionPanel::OnBnClickedButtonACCW()
{
	CString str;
	GetDlgItem(IDC_EDIT_STEP)->GetWindowText(str);
	gf_GetMotorMgr()->m_dStepDist = QGlobal::ATOF(str);
	if (gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_bEnable)
	{//A
		double a = gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_dCmdPos;
		MoveA(a + gf_GetMotorMgr()->m_dStepDist);
	}
}

void CDlgMotionPanel::OnBnClickedButtonACW()
{
	CString str;
	GetDlgItem(IDC_EDIT_STEP)->GetWindowText(str);
	gf_GetMotorMgr()->m_dStepDist = QGlobal::ATOF(str);
	if (gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_bEnable)
	{//A
		double a = gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_dCmdPos;
		MoveA(a - gf_GetMotorMgr()->m_dStepDist);
	}
}

void CDlgMotionPanel::OnBnClickedButtonLeft()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	}
 	
	CString str;
	GetDlgItem(IDC_EDIT_STEP)->GetWindowText(str);
	gf_GetMotorMgr()->m_dStepDist = QGlobal::ATOF(str);
 
	if(gf_GetMotorMgr()->GetMotor(MOTOR_X)->m_bEnable)
	{ 
	 	double x = gf_GetMotorMgr()->GetMotor(MOTOR_X)->m_dCmdPos;

		if (gf_GetMotorMgr()->m_bTableMoveX)
		{
			MoveX(x + gf_GetMotorMgr()->m_dStepDist);
		}
		else
		{
			MoveX(x - gf_GetMotorMgr()->m_dStepDist);
		}
	}
	else if (gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_bEnable && gf_GetMotorMgr()->m_nAasMode == MOTOR_A_AS_X)
	{
		PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
		if (pEM == NULL)
		{
			return;
		}

		PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
		ASSERT(pLayer != NULL);
		double dDiameter = E3_GetCurLayerDiamater(pLayer);
		double dPerimeter = dDiameter * PAI;
		double dAng = 360 * gf_GetMotorMgr()->m_dStepDist / dPerimeter;
		double a = gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_dCmdPos;
		MoveA(a - dAng);
	} 
}

void CDlgMotionPanel::OnBnClickedButtonRight()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	}

	CString str;
	GetDlgItem(IDC_EDIT_STEP)->GetWindowText(str);
	gf_GetMotorMgr()->m_dStepDist = QGlobal::ATOF(str);
	
	if (gf_GetMotorMgr()->GetMotor(MOTOR_X)->m_bEnable)
	{ 
		double x = gf_GetMotorMgr()->GetMotor(MOTOR_X)->m_dCmdPos;
		if (gf_GetMotorMgr()->m_bTableMoveX)
		{
			MoveX(x - gf_GetMotorMgr()->m_dStepDist);
		}
		else
		{
			MoveX(x + gf_GetMotorMgr()->m_dStepDist);
		}
	}
	else if (gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_bEnable && gf_GetMotorMgr()->m_nAasMode == MOTOR_A_AS_X)
	{
		PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
		if (pEM == NULL)
		{
			return;
		}

		PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
		ASSERT(pLayer != NULL);
		double dDiameter = E3_GetCurLayerDiamater(pLayer);
		double dPerimeter = dDiameter * PAI;
		double dAng = 360 * gf_GetMotorMgr()->m_dStepDist / dPerimeter;
		double a = gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_dCmdPos;
		MoveA(a + dAng);
	}
}

void CDlgMotionPanel::MoveY(double y)
{
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	}
	pDlg->LockMarker();
	PMarker pMarker = pDlg->GetMarker();

	int nErr = gf_GetMotorMgr()->GetMotor(MOTOR_Y)->GoPos(pMarker,y, gf_GetMotorMgr()->GetMotor(MOTOR_Y)->m_dMaxVel);

	pDlg->UnLockMarker();
	ShowCurCoor();

	if (nErr != MOTOR_ERR_SUCCESS && nErr != MOTOR_ERR_USERSTOP)
	{
		if (nErr == MOTOR_ERR_NOTHOME)
		{
			if (gf_DlgYesNo(QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")), gf_GetMotorErrStr(nErr)) == IDOK)
			{
				Home();
			}
		}
		else
		{
			gf_DlgYesNo(QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")), gf_GetMotorErrStr(nErr), TRUE);
		}
	}
}
void CDlgMotionPanel::MoveX(double x)
{
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	}
	pDlg->LockMarker();
	PMarker pMarker = pDlg->GetMarker();

	int nErr = gf_GetMotorMgr()->GetMotor(MOTOR_X)->GoPos(pMarker,x, gf_GetMotorMgr()->GetMotor(MOTOR_X)->m_dMaxVel);

	pDlg->UnLockMarker();
	ShowCurCoor();

	if (nErr != MOTOR_ERR_SUCCESS  )
	{
		if (nErr == MOTOR_ERR_NOTHOME)
		{
			if (gf_DlgYesNo(QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")), gf_GetMotorErrStr(nErr)) == IDOK)
			{
				Home();
			}
		}
		else
		{
			gf_DlgYesNo(QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")), gf_GetMotorErrStr(nErr), TRUE);
		}
	}
}
void CDlgMotionPanel::MoveZ(double z)
{
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	}
	pDlg->LockMarker();
	PMarker pMarker = pDlg->GetMarker();

	int nErr = gf_GetMotorMgr()->GetMotor(MOTOR_Z)->GoPos(pMarker,z, gf_GetMotorMgr()->GetMotor(MOTOR_Z)->m_dMaxVel);

	pDlg->UnLockMarker();
	ShowCurCoor();

	if (nErr != MOTOR_ERR_SUCCESS )
	{
		if (nErr == MOTOR_ERR_NOTHOME)
		{
			if (gf_DlgYesNo(QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")),gf_GetMotorErrStr(nErr)) == IDOK)
			{
				Home();
			}
		}
		else  
		{ 
			gf_DlgYesNo(QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")), gf_GetMotorErrStr(nErr), TRUE);
		}
	}
}
void CDlgMotionPanel::MoveA(double a)
{
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	}
	pDlg->LockMarker();
	PMarker pMarker = pDlg->GetMarker();
	 
	int nErr = gf_GetMotorMgr()->GetMotor(MOTOR_A)->GoPos(pMarker,a, gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_dMaxVel);

	pDlg->UnLockMarker();
	ShowCurCoor();

	if (nErr != MOTOR_ERR_SUCCESS  )
	{
		if (nErr == MOTOR_ERR_NOTHOME)
		{
			if (gf_DlgYesNo(QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")), gf_GetMotorErrStr(nErr)) == IDOK)
			{
				Home();
			}
		}
		else
		{
			gf_DlgYesNo(QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")), gf_GetMotorErrStr(nErr), TRUE);
		}
	}
}

 
void CDlgMotionPanel::Home()
{
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	}
	pDlg->LockMarker();
	PMarker pMarker = pDlg->GetMarker();

	int nErr = gf_GetMotorMgr()->HomeAllAxis(pMarker);

	pDlg->UnLockMarker();

	ShowCurCoor();

	if (nErr != MOTOR_ERR_SUCCESS )
	{
		gf_DlgYesNo(QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")), gf_GetMotorErrStr(nErr), TRUE);
		return;
	}  
}
BOOL CDlgMotionPanel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化 
	GetDlgItem(IDC_STATIC_STEP)->SetWindowText(QGlobal::gf_Str(_T("AXISSTEP"), _T("Axis Step")));
	GetDlgItem(IDC_BUTTON_HOME)->SetWindowText(QGlobal::gf_Str(_T("FINDHOME"), _T("Find home")));
	GetDlgItem(IDC_BUTTON_ORG)->SetWindowText(QGlobal::gf_Str(_T("SETORIGIN"), _T("Set origin"))); 
	GetDlgItem(IDC_BUTTON_PARTDIAMETER)->SetWindowText(QGlobal::gf_Str(_T("PARTDIA"), _T("Part Diameter")));
	GetDlgItem(IDC_BUTTON_PARTHEIGHT)->SetWindowText(QGlobal::gf_Str(_T("PARTHEIGHT"), _T("Part height")));
	GetDlgItem(IDC_BUTTON_SPLITPARAM)->SetWindowText(QGlobal::gf_Str(_T("SPLITPARAM"), _T("Split Param.")));
	GetDlgItem(IDC_BUTTON_HANDWHEEL)->SetWindowText(QGlobal::gf_Str(_T("HANDWHEEL"), _T("Handwheel")));

	m_buttonWrap.LoadImage(QGlobal::gf_GetResourcePath() + _T("Wrap.png"));
	m_buttonAutoFocus.LoadImage(QGlobal::gf_GetResourcePath() + _T("AutoFocus.png"));
	m_buttonPreviewSplitBox.LoadImage(QGlobal::gf_GetResourcePath() + _T("SplitBox.png"));
	
	m_buttonACCW.LoadImage(QGlobal::gf_GetResourcePath() + _T("ACCWArrow.png"));
	m_buttonACW.LoadImage(QGlobal::gf_GetResourcePath() + _T("ACWArrow.png"));
	m_buttonUpZ.LoadImage(QGlobal::gf_GetResourcePath() + _T("ZUpArrow.png"));
	m_buttonDownZ.LoadImage(QGlobal::gf_GetResourcePath() + _T("ZDownArrow.png"));
	m_buttonUp.LoadImage(QGlobal::gf_GetResourcePath() + _T("UpArrow.png"));
	m_buttonDown.LoadImage(QGlobal::gf_GetResourcePath() + _T("DownArrow.png"));
	m_buttonLeft.LoadImage(QGlobal::gf_GetResourcePath() + _T("LeftArrow.png"));
	m_buttonRight.LoadImage(QGlobal::gf_GetResourcePath() + _T("RightArrow.png"));




	{
		CQIniFile qini;
		CString  strFile = QGlobal::gf_GetParamPath() + _T("Custom.ini");
		qini.SetPath(strFile);
		if (qini.ReadFile())
		{			
			m_bHideFocusPos = qini.GetValueI(_T("PARAM"), _T("HIDEFOCUPOS")) != 0 ? TRUE : FALSE;
			m_bHideOrigin = qini.GetValueI(_T("PARAM"), _T("HIDEORIGIN")) != 0 ? TRUE : FALSE; 
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CDlgMotionPanel::UpdateParam()
{
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	}

	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}

	m_bEnableAutoFocus = E3_AutoFocusIsEnable();

	BOOL bEnableMotorX = FALSE;
	BOOL bEnableMotorY = FALSE;
	BOOL bEnableMotorZ = FALSE;
	BOOL bEnableMotorA = FALSE;
	BOOL bEnableMotorHomeX = FALSE;
	BOOL bEnableMotorHomeY = FALSE;
	BOOL bEnableMotorHomeZ = FALSE;
	BOOL bEnableMotorHomeA = FALSE;
	if (gf_GetMotorMgr() != NULL)
	{
		bEnableMotorX = gf_GetMotorMgr()->GetMotor(MOTOR_X)->m_bEnable;
		bEnableMotorY = gf_GetMotorMgr()->GetMotor(MOTOR_Y)->m_bEnable;
		bEnableMotorZ = gf_GetMotorMgr()->GetMotor(MOTOR_Z)->m_bEnable;
		bEnableMotorA = gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_bEnable;
		bEnableMotorHomeX = gf_GetMotorMgr()->GetMotor(MOTOR_X)->m_bEnableHome;
		bEnableMotorHomeY = gf_GetMotorMgr()->GetMotor(MOTOR_Y)->m_bEnableHome;
		bEnableMotorHomeZ = gf_GetMotorMgr()->GetMotor(MOTOR_Z)->m_bEnableHome;
		bEnableMotorHomeA = gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_bEnableHome;
	}


	BOOL bHaveSplitBox = FALSE;
	BOOL bHaveHome = FALSE;
	BOOL bHavePartHeight = FALSE;
	BOOL bHaveOrigin = FALSE;
	BOOL bHaveFocus = FALSE;
	BOOL bHaveHandWheel = FALSE;
	BOOL bHaveWrapBtn = FALSE;
	BOOL bHaveSplitParamBtn = FALSE;
	BOOL bHaveDiameter = FALSE;

	BOOL bHaveButtonUp = FALSE;
	BOOL bHaveButtonDown = FALSE;
	BOOL bHaveButtonUpZ = FALSE;
	BOOL bHaveButtonDownZ = FALSE;
	BOOL bHaveButtonLeft = FALSE;
	BOOL bHaveButtonRight = FALSE;
	BOOL bHaveButtonACCW = FALSE;
	BOOL bHaveButtonACW = FALSE;


	PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
	ASSERT(pLayer != NULL);

	int nSplitMode = 0;
	double dSplitSize = 1;
	int nSplitModeY = 0;
	double dSplitSizeY = 1;
	BOOL bNoCutEntity, bKeepEntOrder, bSphereWrap, bRevolveWrap, bUseSplitCenAsMarkingCen, bSplitByGLB, bDisableAxisA, bCylinderWrap, nSplitAttrib;
	E3_EntLayerGetSplitParam(pLayer, nSplitMode, dSplitSize, nSplitModeY, dSplitSizeY, bNoCutEntity, bKeepEntOrder, bSphereWrap, bRevolveWrap, bUseSplitCenAsMarkingCen, bSplitByGLB, bDisableAxisA, bCylinderWrap,  nSplitAttrib);

	if (bDisableAxisA)
	{//关闭A
		bEnableMotorA = FALSE;
	}

	pDlg->LockMarker();
	PMarker pMarker = pDlg->GetMarker();
	int nAxisSol = E3_MarkerGetAxisSol(pMarker);

	if (gf_GetMotorMgr() != NULL && gf_GetMotorMgr()->m_bEnableHandwheel && pMarker != NULL && nAxisSol != MOTOR_SOL_NONE)
	{
		bHaveHandWheel = TRUE;
	}
	else
	{
		bHaveHandWheel = FALSE;
	}



	if (bEnableMotorA && bEnableMotorZ && gf_GetMotorMgr()->m_nAasMode != MOTOR_A_AS_A)
	{//A
		GetDlgItem(IDC_BUTTON_FOCUS)->SetWindowText(QGlobal::gf_Str(_T("ROTATECENZ"), _T("Rotate Center Z")));
	}
	else
	{
		GetDlgItem(IDC_BUTTON_FOCUS)->SetWindowText(QGlobal::gf_Str(_T("FOCUSPOS"), _T("Focus Pos")));
	}

	if (gf_GetMotorMgr()->m_nAasMode == MOTOR_A_AS_A && bEnableMotorA)
	{
		bHaveButtonACCW = TRUE;
		bHaveButtonACW = TRUE;
	}

	if (gf_GetMotorMgr() != NULL)
	{
		CString strName;
		if (bEnableMotorX)
		{
			strName += _T("X");
		}
		else
		{
			if (bEnableMotorA)
			{
				if (gf_GetMotorMgr()->m_nAasMode == MOTOR_A_AS_X && !bEnableMotorX)
				{
					strName += _T("X");
				} 
			}
		}
		if (bEnableMotorY)
		{
			strName += _T("Y");
		}
		else
		{
			 if (gf_GetMotorMgr()->m_nAasMode == MOTOR_A_AS_Y && !bEnableMotorY)
			{
				strName += _T("Y");
			}
		}
		if (bEnableMotorZ)
		{
			strName += _T("Z");
		}
		if (bEnableMotorA)
		{
			if ( gf_GetMotorMgr()->m_nAasMode == MOTOR_A_AS_X && !bEnableMotorX)
			{
				 
			}
			else if (gf_GetMotorMgr()->m_nAasMode == MOTOR_A_AS_Y && !bEnableMotorY)
			{
				 
			}
			else
			{
				strName += _T("A");
			}
		}

		if (strName.GetLength() > 0)
		{
			strName += _T(":");
			GetDlgItem(IDC_STATIC_NAME)->SetWindowText(strName);
			GetDlgItem(IDC_STATIC_NAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_COOR)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_STEP)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_STEP)->ShowWindow(SW_SHOW);
		}
		else
		{
			GetDlgItem(IDC_STATIC_NAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_COOR)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STEP)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STEP)->ShowWindow(SW_HIDE);
		}
	}

	if (nAxisSol == MOTOR_SOL_A)
	{//A			 
		m_bEnableAutoFocus = FALSE;
		bHaveFocus = FALSE;
		bHaveSplitParamBtn = TRUE;
		if (gf_GetMotorMgr()->m_nAasMode != MOTOR_A_AS_A && bEnableMotorA)
		{
			bHaveWrapBtn = TRUE;

			if (!bRevolveWrap)
			{
				bHaveDiameter = TRUE;
			}
			if (gf_GetMotorMgr()->m_nAasMode == MOTOR_A_AS_X)
			{
				bHaveButtonLeft = TRUE;
				bHaveButtonRight = TRUE;
				bHaveSplitBox = TRUE;
			}
			else if (gf_GetMotorMgr()->m_nAasMode == MOTOR_A_AS_Y)
			{
				bHaveButtonUp = TRUE;
				bHaveButtonDown = TRUE;
				bHaveSplitBox = TRUE;
			}
		}
		if (bEnableMotorA && bEnableMotorHomeA)
		{
			bHaveHome = TRUE;
		}
	}
	else if (nAxisSol != MOTOR_SOL_NONE && nAxisSol != MOTOR_SOL_XYZA_FREE)
	{
		bHaveSplitParamBtn = TRUE;
		bHaveSplitBox = TRUE;
		if (bEnableMotorZ)
		{
			bHaveFocus = TRUE;
			bHaveButtonUpZ = TRUE;
			bHaveButtonDownZ = TRUE;

			bHavePartHeight = TRUE;

			if (m_bEnableAutoFocus && bEnableMotorA)
			{
				m_bEnableAutoFocus = FALSE;
				m_bHideFocusPos = TRUE;
			}
		}
		else
		{
			m_bEnableAutoFocus = FALSE;
			bHaveFocus = FALSE;
			bHavePartHeight = FALSE;
		}


		if (bEnableMotorY)
		{
			bHaveButtonUp = TRUE;
			bHaveButtonDown = TRUE;
		}
		if (bEnableMotorX)
		{
			bHaveButtonLeft = TRUE;
			bHaveButtonRight = TRUE;
		}

		if (bEnableMotorA)
		{
			if (gf_GetMotorMgr()->m_nAasMode != MOTOR_A_AS_A)
			{
				bHaveDiameter = TRUE;
				bHaveWrapBtn = TRUE;
				if (gf_GetMotorMgr()->m_nAasMode == MOTOR_A_AS_X)
				{
					bHaveButtonLeft = TRUE;
					bHaveButtonRight = TRUE;
				}
				else
				{
					bHaveButtonUp = TRUE;
					bHaveButtonDown = TRUE;
				}
			}
		}
		else
		{
			if (nAxisSol == MOTOR_SOL_XY_SPHERE)
			{
				bHaveDiameter = TRUE;
			}
		}

		if (bEnableMotorX && bEnableMotorHomeX)
		{
			bHaveHome = TRUE;
		}
		if (bEnableMotorY && bEnableMotorHomeY)
		{
			bHaveHome = TRUE;
		}
		if (bEnableMotorZ && bEnableMotorHomeZ)
		{
			bHaveHome = TRUE;
		}
		if (bEnableMotorA && bEnableMotorHomeA)
		{
			bHaveHome = TRUE;
		}

		if (gf_GetUserMgr()->GetCurUser()->m_bEnableDevParam)
		{
			if (m_bHideFocusPos &&
				(!(bEnableMotorA && bEnableMotorZ &&
					gf_GetMotorMgr()->m_nAasMode != MOTOR_A_AS_A))
				)
			{
				bHaveFocus = FALSE;
			}
		}
		else
		{ 
		//	bHaveSplitBox = FALSE;
		//	bHaveDiameter = FALSE;
		//	bHavePartHeight = FALSE;
		//	bHaveOrigin = FALSE; 
		}
	}
	else
	{
		m_bEnableAutoFocus = FALSE;
	}

	if (m_bHideOrigin)
	{
		bHaveOrigin = FALSE;
	}
	if (m_bEnableAutoFocus)
	{
		bHavePartHeight = FALSE;
	}

	pDlg->UnLockMarker();

	GetDlgItem(IDC_EDIT_STEP)->SetWindowText(QGlobal::gf_GetLenStr(gf_GetMotorMgr()->m_dStepDist));

	m_buttonUp.ShowWindow(bHaveButtonUp ? SW_SHOW : SW_HIDE);
	m_buttonDown.ShowWindow(bHaveButtonDown ? SW_SHOW : SW_HIDE);
	m_buttonUpZ.ShowWindow(bHaveButtonUpZ ? SW_SHOW : SW_HIDE);
	m_buttonDownZ.ShowWindow(bHaveButtonDownZ ? SW_SHOW : SW_HIDE);
	m_buttonLeft.ShowWindow(bHaveButtonLeft ? SW_SHOW : SW_HIDE);
	m_buttonRight.ShowWindow(bHaveButtonRight ? SW_SHOW : SW_HIDE);
	m_buttonACCW.ShowWindow(bHaveButtonACCW ? SW_SHOW : SW_HIDE);
	m_buttonACW.ShowWindow(bHaveButtonACW ? SW_SHOW : SW_HIDE);

	GetDlgItem(IDC_BUTTON_PARTDIAMETER)->ShowWindow(bHaveDiameter ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_STATIC_DIAMETER)->ShowWindow(bHaveDiameter ? SW_SHOW : SW_HIDE); 
	GetDlgItem(IDC_BUTTON_SPLITPARAM)->ShowWindow(bHaveSplitParamBtn ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_STATIC_SPLITPARAM)->ShowWindow(bHaveSplitParamBtn ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BUTTON_PREVIEW)->ShowWindow(bHaveWrapBtn ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BUTTON_HANDWHEEL)->ShowWindow(bHaveHandWheel ? SW_SHOW : SW_HIDE); 
	GetDlgItem(IDC_STATIC_FOCUS)->ShowWindow(bHaveFocus ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BUTTON_FOCUS)->ShowWindow(bHaveFocus ? SW_SHOW : SW_HIDE); 
	GetDlgItem(IDC_BUTTON_ORG)->ShowWindow(bHaveOrigin ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_STATIC_ORG)->ShowWindow(bHaveOrigin ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BUTTON_GOORG)->ShowWindow(bHaveOrigin ? SW_SHOW : SW_HIDE); 
	GetDlgItem(IDC_BUTTON_PARTHEIGHT)->ShowWindow(bHavePartHeight ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_STATIC_HEIGHT)->ShowWindow(bHavePartHeight ? SW_SHOW : SW_HIDE); 
	GetDlgItem(IDC_BUTTON_HOME)->ShowWindow(bHaveHome ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BUTTON_AUTOFOCUS)->ShowWindow(m_bEnableAutoFocus ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BUTTON_PREVIEW2)->ShowWindow(bHaveSplitBox ? SW_SHOW : SW_HIDE);


	ShowOrigin();
	ShowFocus();
	ShowCurCoor();
	ShowPartHeight();
	ShowPartDiameter();
	ShowSplitParam();
}

void CDlgMotionPanel::ShowFocus()
{
 	CString str;
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}

	PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
	ASSERT(pLayer != NULL);

	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	}
	pDlg->LockMarker();
	PMarker pMarker = pDlg->GetMarker();
	int nAxisSol = E3_MarkerGetAxisSol(pMarker);

	if ((pMarker != NULL && nAxisSol == MOTOR_SOL_A)
		|| (gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_bEnable &&
			gf_GetMotorMgr()->GetMotor(MOTOR_Z)->m_bEnable &&
			gf_GetMotorMgr()->m_nAasMode != MOTOR_A_AS_A)
		) 
	{//A
		str = QGlobal::gf_GetLenStr(E3_GetCurLayerRotateCenZ(pLayer));
	}
	else if(gf_GetMotorMgr()->GetMotor(MOTOR_Z)->m_bEnable)
	{//Z
		str = QGlobal::gf_GetLenStr(gf_GetMotorMgr()->m_dFocusPos);
	}
	
	pDlg->UnLockMarker();
	GetDlgItem(IDC_STATIC_FOCUS)->SetWindowText(str);
}
void CDlgMotionPanel::ShowPartDiameter()
{	
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}
	 
	PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
	ASSERT(pLayer != NULL);
  
	CString str; 
	str = QGlobal::gf_GetLenStr(E3_GetCurLayerDiamater(pLayer));
	GetDlgItem(IDC_STATIC_DIAMETER)->SetWindowText(str);
}

void CDlgMotionPanel::ShowPartHeight()
{  
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}

	PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
	ASSERT(pLayer != NULL);
	 
	CString str;
	 str = QGlobal::gf_GetLenStr(E3_GetCurLayerPartHeight(pLayer));
	 
	GetDlgItem(IDC_STATIC_HEIGHT)->SetWindowText(str); 
}

void CDlgMotionPanel::ShowCurCoor()
{
	if (gf_GetMotorMgr() != NULL)
	{
		CString strCoor,str;
		if (gf_GetMotorMgr()->GetMotor(MOTOR_X)->m_bEnable)
		{ 
			strCoor += QGlobal::gf_GetLenStr( gf_GetMotorMgr()->GetMotor(MOTOR_X)->m_dCmdPos);
		}
		else
		{
			if (gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_bEnable && gf_GetMotorMgr()->m_nAasMode == MOTOR_A_AS_X)
			{
				PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
				PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
				ASSERT(pLayer != NULL);
				double dDiameter = E3_GetCurLayerDiamater(pLayer);
				double dPerimeter = dDiameter * PAI;
				double dDist = dPerimeter * gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_dCmdPos / 360;
				strCoor += QGlobal::gf_GetLenStr(dDist);
			}		
		}

		if (gf_GetMotorMgr()->GetMotor(MOTOR_Y)->m_bEnable)
		{
			if (strCoor.GetLength() > 0)
			{
				strCoor += _T(",");
			}
			strCoor += QGlobal::gf_GetLenStr( gf_GetMotorMgr()->GetMotor(MOTOR_Y)->m_dCmdPos);
		}
		else
		{
			if (gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_bEnable && gf_GetMotorMgr()->m_nAasMode == MOTOR_A_AS_Y)
			{
				PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
				PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
				ASSERT(pLayer != NULL);
				double dDiameter = E3_GetCurLayerDiamater(pLayer);
				double dPerimeter = dDiameter * PAI;
				double dDist = dPerimeter * gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_dCmdPos / 360;

				if (strCoor.GetLength() > 0)
				{
					strCoor += _T(",");
				}
				strCoor += QGlobal::gf_GetLenStr(dDist);
			}
		}

		if (gf_GetMotorMgr()->GetMotor(MOTOR_Z)->m_bEnable)
		{
			if (strCoor.GetLength() > 0)
			{
				strCoor += _T(",");
			}
			strCoor += QGlobal::gf_GetLenStr( gf_GetMotorMgr()->GetMotor(MOTOR_Z)->m_dCmdPos);
		}
		if (gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_bEnable && gf_GetMotorMgr()->m_nAasMode == MOTOR_A_AS_A)
		{
			if (strCoor.GetLength() > 0)
			{
				strCoor += _T(",");
			}
			strCoor += QGlobal::gf_GetLenStr(gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_dCmdPos);
		}
		 
		GetDlgItem(IDC_STATIC_COOR)->SetWindowText(strCoor);
	}
}
void CDlgMotionPanel::ShowOrigin()
{
	if (gf_GetMotorMgr() != NULL)
	{
		CString strCoor, str;
		if (gf_GetMotorMgr()->GetMotor(MOTOR_X)->m_bEnable)
		{
			strCoor += QGlobal::gf_GetLenStr(gf_GetMotorMgr()->m_dOriginX);
		}
		if (gf_GetMotorMgr()->GetMotor(MOTOR_Y)->m_bEnable)
		{
			if (strCoor.GetLength() > 0)
			{
				strCoor += _T(",");
			}
			strCoor += QGlobal::gf_GetLenStr(gf_GetMotorMgr()->m_dOriginY);
		}
		/*if (gf_GetMotorMgr()->GetMotor(MOTOR_Z)->m_bEnable)
		{
			if (strCoor.GetLength() > 0)
			{
				strCoor += _T(",");
			}
			strCoor += QGlobal::gf_GetLenStr(gf_GetMotorMgr()->m_dOriginZ);
		}*/
		if (gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_bEnable)
		{
			if (strCoor.GetLength() > 0)
			{
				strCoor += _T(",");
			}
			strCoor += QGlobal::gf_GetLenStr(gf_GetMotorMgr()->m_dOriginA);
		}

		GetDlgItem(IDC_STATIC_ORG)->SetWindowText(strCoor);
	}
}


void CDlgMotionPanel::OnBnClickedButtonFocus()
{
	// TODO: 在此添加控件通知处理程序代码
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}

	PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
	ASSERT(pLayer != NULL);

	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	}

	pDlg->LockMarker();
	PMarker pMarker = pDlg->GetMarker();
	if((pMarker!=NULL && E3_MarkerGetAxisSol(pMarker) == MOTOR_SOL_A)
|| (gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_bEnable &&
			gf_GetMotorMgr()->GetMotor(MOTOR_Z)->m_bEnable &&
			gf_GetMotorMgr()->m_nAasMode != MOTOR_A_AS_A)
		)
	{//A 
		pDlg->UnLockMarker();
		CString strText = QGlobal::gf_GetLenStr(E3_GetCurLayerRotateCenZ(pLayer));
		if (gf_DlgInputOne(NULL, strText, QGlobal::gf_Str(_T("ROTATECENZ"), _T("Center Z")), _T(""), QGlobal::gf_GetUnitStr()) == IDOK)
		{
			E3_SetCurLayerRotateCenZ(pLayer,QGlobal::ATOF(strText));
			 
			ShowFocus();
			gf_GetMotorMgr()->SaveParam(QGlobal::gf_GetParamPath() + _T("Motors.ini"));
		}
	}
	else
	{
		pDlg->UnLockMarker();
		if (gf_DlgYesNo2(QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")),QGlobal::gf_Str(_T("SETCURPOSASFOCUS"), _T("Set current position as focus position?")),
			FALSE, QGlobal::gf_Str(_T("MANUALSET"), _T("Manual set"))) == IDOK)
		{
			gf_GetMotorMgr()->m_dFocusPos = gf_GetMotorMgr()->GetMotor(MOTOR_Z)->m_dCmdPos;
			ShowFocus();
		}
		else
		{
			CString strText = QGlobal::gf_GetLenStr(gf_GetMotorMgr()->m_dFocusPos);
			if (gf_DlgInputOne(NULL, strText, QGlobal::gf_Str(_T("FOCUSPOS"), _T("Focus Pos")), _T(""), QGlobal::gf_GetUnitStr()) == IDOK)
			{
				gf_GetMotorMgr()->m_dFocusPos = QGlobal::ATOF(strText);
				ShowFocus();
				gf_GetMotorMgr()->SaveParam(QGlobal::gf_GetParamPath() + _T("Motors.ini"));
			}
		}
	}
}
#define MAX_AXIS_STEP 11
double gv_fAxisStep[MAX_AXIS_STEP] = { 0.01f,0.05f,0.1f,0.5f,1.0f,2.0f,5.0f,10.0f,20.0f,50.0f,100.0f };

void CDlgMotionPanel::OnPageUp()
{
	CString str;
	GetDlgItem(IDC_EDIT_STEP)->GetWindowText(str);
	gf_GetMotorMgr()->m_dStepDist = QGlobal::ATOF(str);

	for (int i = 0; i < MAX_AXIS_STEP; i++)
	{
		if (gf_GetMotorMgr()->m_dStepDist < (gv_fAxisStep[i]-0.001))
		{
			gf_GetMotorMgr()->m_dStepDist = gv_fAxisStep[i];
			break;
		}
	}
	GetDlgItem(IDC_EDIT_STEP)->SetWindowText(QGlobal::gf_GetLenStr(gf_GetMotorMgr()->m_dStepDist));
}
void CDlgMotionPanel::OnPageDown()
{
	CString str;
	GetDlgItem(IDC_EDIT_STEP)->GetWindowText(str);
	gf_GetMotorMgr()->m_dStepDist = QGlobal::ATOF(str);

	for (int i = MAX_AXIS_STEP-1; i >=0; i--)
	{
		if (gf_GetMotorMgr()->m_dStepDist > (gv_fAxisStep[i]+0.001))
		{
			gf_GetMotorMgr()->m_dStepDist = gv_fAxisStep[i];
			break;
		}
	}
	GetDlgItem(IDC_EDIT_STEP)->SetWindowText(QGlobal::gf_GetLenStr(gf_GetMotorMgr()->m_dStepDist));
}

void CDlgMotionPanel::OnBnClickedButtonHome()
{
	// TODO: 在此添加控件通知处理程序代码
	Home();	
}

BOOL CDlgMotionPanel::IsHideX(PMarker pMarker,BOOL bDisableAxisA)
{
	BOOL bHideX = FALSE;
	if (pMarker != NULL)
	{
		int nSol = E3_MarkerGetAxisSol(pMarker);
		BOOL bAIsX = gf_GetMotorMgr()->m_nAasMode == MOTOR_A_AS_X ? TRUE : FALSE;
		if(nSol == MOTOR_SOL_NONE
			|| nSol == MOTOR_SOL_Y
			|| nSol == MOTOR_SOL_Z
			|| (nSol == MOTOR_SOL_A && !bAIsX )
			|| (nSol == MOTOR_SOL_A && bAIsX && bDisableAxisA)
			|| nSol == MOTOR_SOL_YZ
			|| (nSol == MOTOR_SOL_YA && !bAIsX)
			|| (nSol == MOTOR_SOL_YA && bAIsX && bDisableAxisA)
			|| (nSol == MOTOR_SOL_ZA && !bAIsX  )
			|| (nSol == MOTOR_SOL_ZA && bAIsX && bDisableAxisA)
			|| (nSol == MOTOR_SOL_YZA && !bAIsX)
			|| (nSol == MOTOR_SOL_YZA && bAIsX && bDisableAxisA)
			|| nSol == MOTOR_SOL_XYZA)
		{
			bHideX = TRUE;
		}
	}

	return bHideX;
}
BOOL CDlgMotionPanel::IsHideY(PMarker pMarker,BOOL bDisableAxisA)
{ 
	BOOL bHideY = FALSE;
	if (pMarker != NULL)
	{
		int nSol = E3_MarkerGetAxisSol(pMarker);
		BOOL bAIsY = gf_GetMotorMgr()->m_nAasMode == MOTOR_A_AS_Y ? TRUE : FALSE;
		if (nSol == MOTOR_SOL_NONE
			|| nSol == MOTOR_SOL_X
			|| nSol == MOTOR_SOL_Z
			|| (nSol == MOTOR_SOL_A && !bAIsY)
			|| (nSol == MOTOR_SOL_A && bAIsY&& bDisableAxisA)
			|| nSol == MOTOR_SOL_XZ
			|| (nSol == MOTOR_SOL_XA && !bAIsY)
			|| (nSol == MOTOR_SOL_XA && bAIsY && bDisableAxisA)
			|| (nSol == MOTOR_SOL_ZA && !bAIsY )
			|| (nSol == MOTOR_SOL_ZA && bAIsY && bDisableAxisA)
			|| (nSol == MOTOR_SOL_XZA && !bAIsY)
			|| (nSol == MOTOR_SOL_XZA && bAIsY && bDisableAxisA)
			|| nSol == MOTOR_SOL_XYZA)
		{
			bHideY = TRUE;
		} 
	}
	return bHideY;
}

void CDlgMotionPanel::OnBnClickedButtonSplitparam()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	}
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}

	pDlg->LockMarker();
	PMarker pMarker = pDlg->GetMarker();

	PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
	ASSERT(pLayer != NULL);
	BOOL bEnableMotorA = gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_bEnable;

	int nSplitMode=0;
	double dSplitSize=1;
	int nSplitModeY = 0;
	double dSplitSizeY = 1;

	BOOL bNoCutEntity, bKeepEntOrder, bSphereWrap, bRevolveWrap, bUseSplitCenAsMarkingCen, bSplitByGLB, bDisableAxisA, bCylinderWrap,  nSplitAttrib;
	E3_EntLayerGetSplitParam(pLayer, nSplitMode, dSplitSize, nSplitModeY, dSplitSizeY, bNoCutEntity, bKeepEntOrder, bSphereWrap, bRevolveWrap, bUseSplitCenAsMarkingCen, bSplitByGLB, bDisableAxisA, bCylinderWrap,  nSplitAttrib);

	CDlgSplitParam dlg(this);

	dlg.m_nSplitModeX = nSplitMode;
	dlg.m_dSplitSizeX = dSplitSize;
	dlg.m_nSplitModeY = nSplitModeY;
	dlg.m_dSplitSizeY = dSplitSizeY;
	dlg.m_bCylinderWrap = bCylinderWrap;
	dlg.m_bSphereWrap = bSphereWrap;
	dlg.m_bRevolveWrap = bRevolveWrap;
	dlg.m_bKeepEntOrder= bKeepEntOrder; 
	dlg.m_bSplitByGLB = bSplitByGLB;
	dlg.m_bNoCutEntity =bNoCutEntity; 
	dlg.m_bUseSplitCenAsMarkingCen = bUseSplitCenAsMarkingCen;
	dlg.m_bDisableAxisA = bDisableAxisA;
 	dlg.m_bShowDisableA = gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_bEnable;
	dlg.m_bShowCylinderWrap = (pMarker != NULL && bEnableMotorA && gf_GetMotorMgr()->m_nAasMode != MOTOR_A_AS_A);
	dlg.m_bShowSphereWrap = (pMarker!=NULL && E3_MarkerGetAxisSol(pMarker) == MOTOR_SOL_A);
	dlg.m_bEnableA = (pMarker != NULL && E3_MarkerGetAxisSol(pMarker) == MOTOR_SOL_A); 
	dlg.m_bHideX = IsHideX(pMarker , bDisableAxisA);
	dlg.m_bHideY = IsHideY(pMarker, bDisableAxisA);
	dlg.m_bMark360 = gf_GetMotorMgr()->m_bSolAMark360;
	dlg.m_nMarkCount = gf_GetMotorMgr()->m_nSolAMarkCount ;
	dlg.m_dMarkAngle = gf_GetMotorMgr()->m_dSolAMarkAngle  ; 
	dlg.m_nSplitAttrib = nSplitAttrib;
	pDlg->UnLockMarker(); 

	if (dlg.DoModal() == IDOK)
	{ 
		nSplitMode = dlg.m_nSplitModeX; 
		dSplitSize = dlg.m_dSplitSizeX;
		nSplitModeY = dlg.m_nSplitModeY;
		dSplitSizeY = dlg.m_dSplitSizeY;
		bSplitByGLB = dlg.m_bSplitByGLB ;
		bSphereWrap = dlg.m_bSphereWrap;
		bRevolveWrap = dlg.m_bRevolveWrap; 
		bKeepEntOrder = dlg.m_bKeepEntOrder; 
		bDisableAxisA = dlg.m_bDisableAxisA; 
		bNoCutEntity = dlg.m_bNoCutEntity;
		bUseSplitCenAsMarkingCen = dlg.m_bUseSplitCenAsMarkingCen;
		bCylinderWrap = dlg.m_bCylinderWrap;
		nSplitAttrib = dlg.m_nSplitAttrib ;
		 
		E3_EntLayerSetSplitParam(pLayer, nSplitMode, dSplitSize, nSplitModeY, dSplitSizeY, bNoCutEntity, bKeepEntOrder, bSphereWrap, bRevolveWrap, bUseSplitCenAsMarkingCen, bSplitByGLB, bDisableAxisA, bCylinderWrap,   nSplitAttrib);

		gf_GetMotorMgr()->m_bSolAMark360 = dlg.m_bMark360;
		gf_GetMotorMgr()->m_nSolAMarkCount = dlg.m_nMarkCount;
		gf_GetMotorMgr()->m_dSolAMarkAngle = dlg.m_dMarkAngle; 
		gf_GetMotorMgr()->SaveParam(QGlobal::gf_GetParamPath() + _T("Motors.ini")); 
		UpdateParam(); 
	}
}

void CDlgMotionPanel::ShowSplitParam()
{	
    CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	}
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}
	PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
	ASSERT(pLayer != NULL);
	int nSplitModeX = 0;
	double dSplitSizeX = 1;
	int nSplitModeY = 0;
	double dSplitSizeY = 1;
	BOOL bNoCutEntity, bKeepEntOrder, bSphereWrap, bRevolveWrap, bUseSplitCenAsMarkingCen, bSplitByGLB, bDisableAxisA, bCylinderWrap, nSplitAttrib;
	E3_EntLayerGetSplitParam(pLayer, nSplitModeX, dSplitSizeX, nSplitModeY, dSplitSizeY, bNoCutEntity, bKeepEntOrder, bSphereWrap, bRevolveWrap, bUseSplitCenAsMarkingCen, bSplitByGLB, bDisableAxisA, bCylinderWrap,  nSplitAttrib);

	pDlg->LockMarker();
	PMarker pMarker = pDlg->GetMarker();


	GetDlgItem(IDC_STATIC_SPLITPARAMY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_SPLITPARAM)->ShowWindow(SW_SHOW);

	if (pMarker!=NULL && E3_MarkerGetAxisSol(pMarker) != MOTOR_SOL_Z)
	{ 
		CString str;

		if (IsHideX(pMarker, bDisableAxisA))
		{
			if (IsHideY(pMarker, bDisableAxisA))
			{
				GetDlgItem(IDC_STATIC_SPLITPARAM)->SetWindowText(str);
				GetDlgItem(IDC_STATIC_SPLITPARAM)->ShowWindow(SW_HIDE);
			}
			else
			{ 
				if (nSplitModeY == 1)
				{
					str = QGlobal::gf_Str(_T("SPLITBYSIZE"), _T("Split by size"));
				}
				else if (nSplitModeY == 2)
				{
					str = QGlobal::gf_Str(_T("SPLITBYGUILDLINE"), _T("Split by guildline"));
				}
				else
				{
					str = QGlobal::gf_Str(_T("NOSPLIT"), _T("No split"));
				}
				GetDlgItem(IDC_STATIC_SPLITPARAM)->SetWindowText(str);
			}
		}
		else 
		{
			if (nSplitModeX == 1)
			{
				str = QGlobal::gf_Str(_T("SPLITBYSIZE"), _T("Split by size"));
			}
			else if (nSplitModeX == 2)
			{
				str = QGlobal::gf_Str(_T("SPLITBYGUILDLINE"), _T("Split by guildline"));
			}
			else
			{
				str = QGlobal::gf_Str(_T("NOSPLIT"), _T("No split"));
			}
			if (IsHideY(pMarker, bDisableAxisA))
			{
				GetDlgItem(IDC_STATIC_SPLITPARAM)->SetWindowText(str);
			}
			else
			{
				str = _T("X:") + str;
				GetDlgItem(IDC_STATIC_SPLITPARAM)->SetWindowText(str);
				
				if (nSplitModeY == 1)
				{
					str = QGlobal::gf_Str(_T("SPLITBYSIZE"), _T("Split by size"));
				}
				else if (nSplitModeY == 2)
				{
					str = QGlobal::gf_Str(_T("SPLITBYGUILDLINE"), _T("Split by guildline"));
				}
				else
				{
					str = QGlobal::gf_Str(_T("NOSPLIT"), _T("No split"));
				}
				str = _T("Y:") + str;
				GetDlgItem(IDC_STATIC_SPLITPARAMY)->SetWindowText(str);	
				GetDlgItem(IDC_STATIC_SPLITPARAMY)->ShowWindow(SW_SHOW);
			}
		}
	}	
	 
	pDlg->UnLockMarker(); 
}

void CDlgMotionPanel::OnBnClickedButtonDownz()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT_STEP)->GetWindowText(str);
	gf_GetMotorMgr()->m_dStepDist = QGlobal::ATOF(str);

	if (gf_GetMotorMgr()->GetMotor(MOTOR_Z)->m_bEnable)
	{//Z
		double z = gf_GetMotorMgr()->GetMotor(MOTOR_Z)->m_dCmdPos;
		MoveZ(z - gf_GetMotorMgr()->m_dStepDist);
	}
}


void CDlgMotionPanel::OnBnClickedButtonUpz()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT_STEP)->GetWindowText(str);
	gf_GetMotorMgr()->m_dStepDist = QGlobal::ATOF(str);
	if (gf_GetMotorMgr()->GetMotor(MOTOR_Z)->m_bEnable)
	{//Z
		double z = gf_GetMotorMgr()->GetMotor(MOTOR_Z)->m_dCmdPos;
		MoveZ(z +  gf_GetMotorMgr()->m_dStepDist);
	}
}


void CDlgMotionPanel::OnBnClickedButtonGoorg()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	}
	pDlg->LockMarker();
	PMarker pMarker = pDlg->GetMarker();
	BOOL  isHasMoved = FALSE;
	int nErr = gf_GetMotorMgr()->GotoPos(pMarker,gf_GetMotorMgr()->m_dOriginX, gf_GetMotorMgr()->m_dOriginY, gf_GetMotorMgr()->m_dFocusPos, gf_GetMotorMgr()->m_dOriginA, isHasMoved,1.0);

	pDlg->UnLockMarker();

	ShowCurCoor();
	if (nErr != MOTOR_ERR_SUCCESS && nErr != MOTOR_ERR_USERSTOP)
	{
		if (nErr == MOTOR_ERR_NOTHOME)
		{
			if (gf_DlgYesNo(QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")), gf_GetMotorErrStr(nErr)) == IDOK)
			{
				Home();
			}
		}
		else
		{
			gf_DlgYesNo(QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")), gf_GetMotorErrStr(nErr), TRUE); 
		}
	}
}


void CDlgMotionPanel::OnBnClickedButtonOrg()
{
	// TODO: 在此添加控件通知处理程序代码
	if (gf_DlgYesNo(QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")),QGlobal::gf_Str(_T("SETCURPOSASORIGIN"), _T("Set current position as origin?"))) == IDOK)
	{
		if (gf_GetMotorMgr()->GetMotor(MOTOR_X)->m_bEnable)
		{
			gf_GetMotorMgr()->m_dOriginX = gf_GetMotorMgr()->GetMotor(MOTOR_X)->m_dCmdPos;
		}
		if (gf_GetMotorMgr()->GetMotor(MOTOR_Y)->m_bEnable)
		{
			gf_GetMotorMgr()->m_dOriginY = gf_GetMotorMgr()->GetMotor(MOTOR_Y)->m_dCmdPos;
		}
		if (gf_GetMotorMgr()->GetMotor(MOTOR_Z)->m_bEnable)
		{
			gf_GetMotorMgr()->m_dOriginZ = gf_GetMotorMgr()->GetMotor(MOTOR_Z)->m_dCmdPos;
		}
		if (gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_bEnable)
		{
			gf_GetMotorMgr()->m_dOriginA = gf_GetMotorMgr()->GetMotor(MOTOR_A)->m_dCmdPos;
		}
		 
		ShowOrigin();
		gf_GetMotorMgr()->SaveParam(QGlobal::gf_GetParamPath() + _T("Motors.ini"));
	}
}


LRESULT CDlgMotionPanel::OnUserChangeCurLayer(WPARAM wParam, LPARAM lParam)
{ 
	UpdateParam();
	return 0;
}

void CDlgMotionPanel::OnBnClickedButtonPartheight()
{
	// TODO: 在此添加控件通知处理程序代码 
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}

	PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
	ASSERT(pLayer != NULL);
 

	CString strText = QGlobal::gf_GetLenStr(E3_GetCurLayerPartHeight(pLayer));
	if (gf_DlgInputOne(NULL, strText, QGlobal::gf_Str(_T("PARTHEIGHT"), _T("Part height")), _T(""), QGlobal::gf_GetUnitStr()) == IDOK)
	{
		E3_SetEntMgrModifyFlag(pEM, TRUE);
		
		E3_SetCurLayerPartHeight(pLayer, QGlobal::ATOF(strText));
		ShowPartHeight();
		gf_GetMotorMgr()->SaveParam(QGlobal::gf_GetParamPath() + _T("Motors.ini"));
	}
}
  
void CDlgMotionPanel::OnBnClickedButtonPartdiameter()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	}

	PEntMgr pEM =  E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}
	PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
	ASSERT(pLayer != NULL);

	CString strText = QGlobal::gf_GetLenStr(E3_GetCurLayerDiamater(pLayer));

	if (gf_DlgInputOne(NULL, strText, QGlobal::gf_Str(_T("PARTDIA"), _T("Part Diameter")), _T(""), QGlobal::gf_GetUnitStr()) == IDOK)
	{
		double dRotateDiameter = QGlobal::ATOF(strText);
		if (dRotateDiameter < 0.01)
		{
			dRotateDiameter = 0.01;
		}
		E3_SetCurLayerDiamater(pLayer, dRotateDiameter);
		E3_SetEntMgrModifyFlag(pEM,TRUE);
		ShowPartDiameter();
	}
}

void CDlgMotionPanel::OnBnClickedButtonHandwheel()
{
	// TODO: 在此添加控件通知处理程序代码
	CEntMgr* pEM = (CEntMgr*)E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}
	
	gf_GetMotorMgr()->ShowHandwheelDialog();
	ShowCurCoor();
}
 
void CDlgMotionPanel::OnBnClickedButtonPreview()
{
	// TODO: 在此添加控件通知处理程序代码
	CEntMgr* pEM = (CEntMgr*)E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	}

	PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
	ASSERT(pLayer != NULL);
	int nMarkFlag = 0;
	if (pDlg->IsMarkSelected())
	{
		nMarkFlag |= MAKRFLAG_SELECT;
	} 
	pDlg->LockMarker();
	PMarker pMarker = pDlg->GetMarker();
	PEntity pWrap = E3_MarkEntWithMotorSolGetCurves(pMarker, pEM, pLayer, nMarkFlag);
	pDlg->UnLockMarker();

	E3_DlgGlShowEnt(pWrap);	
}
  
void CDlgMotionPanel::OnBnClickedButtonAutofocus()
{
	// TODO: 在此添加控件通知处理程序代码 
	if ( !m_bEnableAutoFocus)
	{
		return;
	} 
	if (!E3_AutoFocusIsOpen())
	{
		E3_AutoFocusOpen();
	}

	if (E3_AutoFocusIsOpen())
	{
		double  dValue;
		if (E3_AutoFocusGetValue( dValue ))
		{
			gf_GetMotorMgr()->m_dFocusPos = gf_GetMotorMgr()->GetMotor(MOTOR_Z)->m_dCmdPos - dValue;
			MoveZ(gf_GetMotorMgr()->m_dFocusPos);
		}  
		else
		{
			AfxMessageBox(_T("Get focus distance failed!"));
		}
	}
}
 
void CDlgMotionPanel::OnBnClickedButtonPreview2()
{
	// TODO: 在此添加控件通知处理程序代码
	CEntMgr* pEM = (CEntMgr*)E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	}

	PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
	ASSERT(pLayer != NULL);
	int nMarkFlag = 0;
	if (pDlg->IsMarkSelected())
	{
		nMarkFlag |= MAKRFLAG_SELECT;
	}
	 
	if (E3_GetCmdMgr() != NULL)
	{
		pDlg->LockMarker();
		PMarker pMarker = pDlg->GetMarker();

		int nBoxCount = 0;
		Box2d* arrayBox = E3_MarkEntWithMotorSolGetAllSplitBoxes(pMarker, pEM, pLayer, nMarkFlag, nBoxCount);
		pDlg->UnLockMarker();

		E3_ShowSplitBoxesOnCurDC(E3_GetCmdMgr(), arrayBox, nBoxCount);
		if (arrayBox != NULL)
		{
			E3_DeleteAllBoxes(arrayBox);
		}
		return;
	}
}
