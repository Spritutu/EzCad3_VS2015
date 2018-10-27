// D:\项目\Visual Studio 2008\Ezcad3\Ezcad3\Mark\DlgMark.cpp : 实现文件
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "DlgMark.h"
#include "QGlobal.h"
#include "usermessdef.h"
#include "SysParam.h"

//#include "DlgMarkRedLight.h"
#include "DlgMarking.h"
#include "QUser.h"
#include "QMotorMgr.h"
#include "qDlg.h"
#include "Box3d.h"
#include "..\..\MainFrm.h"
#include "DlgSelMarker.h"

#define STARTMARK_TIMER 111
 
#ifdef KEYHOOK

HHOOK KeyHook;
CDlgMark* pHookWnd=NULL;

CDlgMark* gf_GetDlgMark() { return pHookWnd; }

BOOL st_bEnableHookUpDown = FALSE;
LRESULT CALLBACK MarkKeyHook(int nCode,WPARAM wParam,LPARAM lParam)
{
	TRACE("MarkKeyHook  \n");
	if(pHookWnd!=NULL && ((DWORD)lParam&0x40000000) && (HC_ACTION==nCode) ) //有键按下		
	{
		//if(gf_GetMarkWnd()==pHookWnd && !pHookWnd->m_bNowMark)
		if( !pHookWnd->m_bNowMark)
		{
			if(wParam==VK_F1)
			{
				PostMessage(pHookWnd->GetSafeHwnd(),WM_COMMAND,IDC_BUTTON_F1,0);
				return 0;
			}
			else if(wParam==VK_F2)
			{
				PostMessage(pHookWnd->GetSafeHwnd(),WM_COMMAND,IDC_BUTTON_F2,0);
				return 0;
			}
			else if(wParam==VK_F3)
			{
				if (!pHookWnd->m_bHideF3)
				{
					PostMessage(pHookWnd->GetSafeHwnd(), WM_COMMAND, IDC_BUTTON_F3, 0);
					return 0;
				}
			}	
			else if (wParam == VK_F4)
			{
				PostMessage(pHookWnd->GetSafeHwnd(), WM_COMMAND, IDC_BUTTON_F4, 0);
				return 0;
			}
			else if(wParam== VK_PRIOR)
			{//PAGE_UP
				pHookWnd->OnPageUp();
				return 0;
			}
			else if (wParam == VK_NEXT)
			{//PAGE_DOWN
				pHookWnd->OnPageDown();
				return 0;
			} 
			else if (wParam == VK_UP)
			{  
				TRACE("VK_UP 1\n");
				short nShift = GetKeyState(VK_LMENU);
				BOOL bShift = nShift & 0x8000 ? TRUE : FALSE;
				if (bShift)
				{
					pHookWnd->OnKeyUp();
					return 0;
				}
			}
			else if (wParam == VK_DOWN)
			{ 
				short nShift = GetKeyState(VK_LMENU);
				BOOL bShift = nShift & 0x8000 ? TRUE : FALSE;
				if (bShift)
				{
					pHookWnd->OnKeyDown();
					return 0;
				}
			} 
			else if (wParam == VK_LEFT)
			{
				short nShift = GetKeyState(VK_LMENU);

				BOOL bShift = nShift & 0x8000 ? TRUE : FALSE;
				if (bShift)
				{
					pHookWnd->OnKeyLeft();
					return 0;
				}
			}
			else if (wParam == VK_RIGHT)
			{
				short nShift = GetKeyState(VK_LMENU);
				BOOL bShift = nShift & 0x8000 ? TRUE : FALSE;
				if (bShift)
				{
					pHookWnd->OnKeyRight();
					return 0;
				}
			}
		}	
		else
		{
			if (wParam == VK_F2 && pHookWnd->m_bRedLightMode)
			{
				pHookWnd->LockMarker();
				PMarker pMarker = pHookWnd->GetMarker();
				if(pMarker !=NULL)
				{
					E3_MarkerSetCancelFlag(pMarker, TRUE); 
					pHookWnd->m_bSendF2Msg = TRUE;
				} 
				pHookWnd->UnLockMarker(); 
				return 0;
			}
		}
	}	
	return CallNextHookEx(KeyHook,nCode,wParam,lParam);
}
#endif



// CDlgMark 对话框

IMPLEMENT_DYNAMIC(CDlgMark, CDialog)

	CDlgMark::CDlgMark(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMark::IDD, pParent)
{
	m_pMarker = NULL;
	m_bNowMark = FALSE;
	m_bIsParamSetting=FALSE;
	m_nTotalCount = 0;
	m_nPartCount = 0;
	m_strPartTime = _T("00:00:00.000");
	m_pDlgMotionPanel = NULL;

	m_bHideF3 = FALSE; 
	m_bMarkRemovedFlag = FALSE;

	CString strMutexName;
	strMutexName.Format(_T("MUTEX_DLGMARK_MARKER"));
	m_hMutexMarker = CreateMutex(NULL, FALSE, strMutexName);
	m_nMutexCount = 0;
}

CDlgMark::~CDlgMark()
{

	if (m_hMutexMarker != NULL)
	{
		ASSERT(m_nMutexCount == 0);
	 	CloseHandle(m_hMutexMarker);
		m_hMutexMarker = NULL;
	}

#ifdef KEYHOOK
	pHookWnd=NULL;
	UnhookWindowsHookEx( KeyHook );
#endif


	QGlobal::gf_CloseUsbMonitor();

	E3_CloseMarkDriver();
}

void CDlgMark::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_F1, m_buttonF1);
	DDX_Control(pDX, IDC_BUTTON_F2, m_buttonF2);
	DDX_Control(pDX, IDC_BUTTON_F3, m_buttonF3);
	DDX_Control(pDX, IDC_BUTTON_F4, m_buttonF4);
	DDX_Control(pDX, IDC_STATIC_LAMP_READY, m_lampReady);
	DDX_Control(pDX, IDC_STATIC_LAMP_POWER, m_lampPower);
	DDX_Control(pDX, IDC_BUTTON_CAMERAONOFF, m_buttonCamera); 
}


BEGIN_MESSAGE_MAP(CDlgMark, CDialog)
	ON_MESSAGE(WM_USER_USBLMC_REMOVE, OnUsbLmcRemove)	
	ON_MESSAGE(WM_USER_USBLMC_ARRIVE , OnUsbLmcArrive)	
	ON_MESSAGE(WM_USER_UNITCHANGE , OnUserUnitChange)	
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_F1, &CDlgMark::OnBnClickedButtonF1)
	ON_BN_CLICKED(IDC_BUTTON_F2, &CDlgMark::OnBnClickedButtonF2)
	ON_BN_CLICKED(IDC_BUTTON_F3, &CDlgMark::OnBnClickedButtonF3)
	ON_BN_CLICKED(IDC_BUTTON_F4, &CDlgMark::OnBnClickedButtonF4)
	ON_BN_CLICKED(IDC_BUTTON_RESETCOUNT, &CDlgMark::OnBnClickedButtonReset) 
	ON_BN_CLICKED(IDC_BUTTON_CALC, &CDlgMark::OnBnClickedButtonCalcTime) 
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_OFFLINE, &CDlgMark::OnBnClickedCheckOffline)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CDlgMark::OnDeltaposSpin1)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgMark::OnBnClickedButtonGet)
	ON_STN_CLICKED(IDC_STATIC_MOTORPANEL, &CDlgMark::OnStnClickedStaticMotorpanel)
	ON_BN_CLICKED(IDC_BUTTON_FLYSPEED, &CDlgMark::OnBnClickedButtonFlyspeed)
	ON_BN_CLICKED(IDC_BUTTON_POWER, &CDlgMark::OnBnClickedButtonPower)
	ON_BN_CLICKED(IDC_BUTTON_CAMERAONOFF, &CDlgMark::OnBnClickedButtonCamera)
	ON_MESSAGE(WM_USER_CHANGEENTITY_1, OnUserChangeEntity_1)
	ON_MESSAGE(WM_USER_Red, OnUserRed)
	ON_MESSAGE(WM_USER_CHANGEENTITY, OnUserChangeEntity)
	
END_MESSAGE_MAP()

void CDlgMark::OnDestroy() 
{
	CDialog::OnDestroy();
	if (m_pDlgMotionPanel != NULL)
	{
		delete m_pDlgMotionPanel;
		m_pDlgMotionPanel = NULL;
	}

	gf_GetMotorMgr()->Close();
	// TODO: Add your message handler code here
	KillTimer(STARTMARK_TIMER);	
}
void CDlgMark::OnOK()
{
	// TODO: Add extra validation here

}

void CDlgMark::OnCancel()
{
	// TODO: Add extra cleanup here	

}
// CDlgMark 消息处理程序

BOOL CDlgMark::OnInitDialog()
{ 
	CDialog::OnInitDialog();
	
	 
	m_buttonF1.LoadImage(QGlobal::gf_GetResourcePath() + _T("Aim.png")); 
	m_buttonF2.LoadImage(QGlobal::gf_GetResourcePath() + _T("Mark.png"));
	m_buttonF3.LoadImage(QGlobal::gf_GetResourcePath() + _T("Param.png"));
	m_buttonF4.LoadImage(QGlobal::gf_GetResourcePath() + _T("Box.png"));


	GetDlgItem(IDC_CHECK_CONTINUE)->SetWindowText(QGlobal::gf_Str(_T("CONTINUES"),_T("Continuous")));
	GetDlgItem(IDC_CHECK_SELECTED)->SetWindowText(QGlobal::gf_Str(_T("MARKSELECT"),_T("Mark Selected")));
	GetDlgItem(IDC_CHECK_LAYER2)->SetWindowText(QGlobal::gf_Str(_T("MULTILAYER"),_T("Multi Layer")));
	GetDlgItem(IDC_CHECK_OFFLINE)->SetWindowText(QGlobal::gf_Str(_T("OFFLINE"), _T("Offline")));
	GetDlgItem(IDC_CHECK_REDCONTOUR)->SetWindowText(QGlobal::gf_Str(_T("ENSHOWCONTOUR"), _T("Show contour")));

	GetDlgItem(IDC_BUTTON_F1)->SetWindowText(QGlobal::gf_Str(_T("BTNLIGHT"),_T("Light(F1)")));
	GetDlgItem(IDC_BUTTON_F2)->SetWindowText(QGlobal::gf_Str(_T("BTNMARK"),_T("Mark(F2)")));
	GetDlgItem(IDC_BUTTON_F3)->SetWindowText(QGlobal::gf_Str(_T("BTNPARAM"),_T("Param(F3)")));

	GetDlgItem(IDC_BUTTON_FLYSPEED)->SetWindowText(QGlobal::gf_Str(_T("FLYSPEED"), _T("Fly speed")));
	GetDlgItem(IDC_STATIC_READY)->SetWindowText(QGlobal::gf_Str(_T("READY"), _T("Ready")));
	{
		CQIniFile qini;
		CString  strFile = QGlobal::gf_GetParamPath() + _T("Custom.ini");
		qini.SetPath(strFile);
		if (qini.ReadFile())
		{
			CString str = qini.GetValue(_T("PARAM"), _T("HIDEF3"));
			m_bHideF3 = qini.GetValueI(_T("PARAM"), _T("HIDEF3"))!=0 ? TRUE:FALSE;
		}
	}

	if (m_bHideF3)
	{
		GetDlgItem(IDC_BUTTON_F3)->ShowWindow(SW_HIDE);
	}

	if (gf_GetSysParam()->GetParamInt(INT_PARAM_PROJECTVIEW))
	{
		GetDlgItem(IDC_BUTTON_F4)->SetWindowText(QGlobal::gf_Str(_T("BTNPRJ"), _T("Project(F4)")));
	}
	else
	{
		GetDlgItem(IDC_BUTTON_F4)->SetWindowText(QGlobal::gf_Str(_T("BTNBOX"), _T("Box(F4)")));
	}

	GetDlgItem(IDC_STATIC_PART)->SetWindowText(QGlobal::gf_Str(_T("PART"),_T("Part")));
	GetDlgItem(IDC_STATIC_TOTAL)->SetWindowText(QGlobal::gf_Str(_T("TOTALNUM"),_T("Total")));

	GetDlgItem(IDC_BUTTON_POWER)->SetWindowText(QGlobal::gf_Str(_T("LASERPOWER"), _T("Laser power")));

	

	GetDlgItem(IDC_EDIT_PARTTIME)->SetWindowText(_T("00:00:00.000"));
	GetDlgItem(IDC_EDIT_TOTALTIME)->SetWindowText(_T("00:00:00.000"));
	m_nFileCount = 1;
	GetDlgItem(IDC_EDIT_FILEINDEX)->SetWindowText(_T("1"));

 
	m_pDlgMotionPanel = new CDlgMotionPanel();
	m_pDlgMotionPanel->Create(IDD_DIALOG_MOTIONPANEL, GetDlgItem(IDC_STATIC_MOTORPANEL));



	if(E3_GetCmdMgr()!=NULL)
	{
		E3_CmdMgrAddEntityWnd(E3_GetCmdMgr(), this );//告诉命令管理器当前窗口需要接收系统消息
		E3_CmdMgrAddEntityWnd(E3_GetCmdMgr(), m_pDlgMotionPanel);//告诉命令管理器当前窗口需要接收系统消息
	}
 
	//打开驱动
	m_pMarker = NULL;
	if (E3_OpenMarkDriver())
	{
		PMarker markerBuf[8];
		int nValidMarker = 0;
		for (int i = 0; i < 8; i++)
		{
			markerBuf[i] = E3_GetOneValidDev();//得到当前有效的一个设备
			if (markerBuf[i] != NULL)
			{
				nValidMarker++;
			}
		}

		if (nValidMarker > 0)
		{
			if (nValidMarker ==1)
			{
				m_pMarker = markerBuf[0];//得到当前有效的一个设备
			}
			else
			{
				//选择使用那块卡
				CDlgSelMarker dlg(this);
				for (int i = 0; i < 8; i++)
				{
					dlg.m_markerBuf[i] = markerBuf[i];
				}
				if (dlg.DoModal() == IDOK)
				{
					m_pMarker = markerBuf[dlg.m_nSelIndex];//得到当前有效的一个设备
				}
				else
				{
					m_pMarker = markerBuf[0];//得到当前有效的一个设备
				}
			}
		} 
	}

#ifdef KEYHOOK
	KeyHook = (HHOOK)SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)MarkKeyHook, AfxGetApp()->m_hInstance, GetCurrentThreadId());
	pHookWnd = this;
#endif

	if(m_pMarker!=NULL)
	{			 
		E3_MarkerSetup(m_pMarker);//初始化当前设备
		UpdateMotionPanel();	 
	}

	if (E3_MarkerIsDeviceValid(m_pMarker))
	{//检查设备是否有效 
		E3_CmdMgrSetDemo(E3_GetCmdMgr(), FALSE );
	}
	else
	{
		E3_CmdMgrSetDemo(E3_GetCmdMgr(), TRUE);
	}

	QGlobal::gf_InitUsbMonitor(this);//初始化usb监视
	
	m_lampReady.Off();
	m_lampPower.Off();

	UpdateDevState();
	
	m_bMarkRemovedFlag = FALSE; 

	ShowCount(); 

	if (E3_GetCmdMgr() != NULL)
	{//激光器被修改
		E3_CmdMgrSendMessageToEntWnd(E3_GetCmdMgr(),WM_USER_CHANGELASER, (WPARAM)m_pMarker, 0);
	}

	SetTimer(STARTMARK_TIMER, 100, NULL); 

	{
		CQIniFile qini;
		CString  strFile = QGlobal::gf_GetParamPath() + _T("Custom.ini");
		qini.SetPath(strFile);
		if (qini.ReadFile())
		{
			CString str = qini.GetValue(_T("PARAM"), _T("MARKTIMECOEF"));
			if (str.GetLength() > 0)
			{
				m_markTotal.m_dRatio = QGlobal::ATOF(str);
			}
		}
	}


	if (E3_IsCameraHide())
	{
		m_buttonCamera.LoadImage(QGlobal::gf_GetResourcePath() + _T("CameraOff.png"));
	}
	else
	{
		m_buttonCamera.LoadImage(QGlobal::gf_GetResourcePath() + _T("CameraOn.png"));
	}

	if (E3_IsCameraOpen())
	{
		m_buttonCamera.ShowWindow(SW_SHOW);		
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


PMarker CDlgMark::GetMarker()
{
	return m_pMarker;
}

BOOL CDlgMark::IsMarkerLocked()
{
	return  m_nMutexCount > 0;
}
void CDlgMark::LockMarker()
{
//	TRACE("LockMarker\n");
	m_nMutexCount++;
	ASSERT(m_nMutexCount == 1);
	if (m_hMutexMarker != NULL)
	{
		WaitForSingleObject(m_hMutexMarker, INFINITE);
	}
}
void CDlgMark::UnLockMarker()
{
	
	m_nMutexCount--;
	ASSERT(m_nMutexCount == 0);
	if (m_hMutexMarker != NULL)
	{
		ReleaseMutex(m_hMutexMarker);
	}
//	TRACE("UnLockMarker\n");
}

int CDlgMark::GetMinShowWidth()
{
	CRect rectClient,rectF3, rectF4;
	GetWindowRect(rectClient);
	GetDlgItem(IDC_BUTTON_F3)->GetWindowRect(rectF3);
	GetDlgItem(IDC_BUTTON_F4)->GetWindowRect(rectF4);


	int nMinSize = 532;
	if (GetMarker() != NULL && E3_MarkerIsShowF4(GetMarker()))
	{
		nMinSize = rectF4.right - rectClient.left+4;
	}
	else
	{
		nMinSize = rectF3.right - rectClient.left + 4;
	}
	return nMinSize;
}
void CDlgMark::UpdateDevState()
{
	if (gf_GetSysParam()->GetParamInt(INT_PARAM_PROJECTVIEW))
	{
		GetDlgItem(IDC_BUTTON_F4)->SetWindowText(QGlobal::gf_Str(_T("BTNPRJ"), _T("Project(F4)")));
		GetDlgItem(IDC_BUTTON_F4)->Invalidate();
	}
	else
	{
		GetDlgItem(IDC_BUTTON_F4)->SetWindowText(QGlobal::gf_Str(_T("BTNBOX"), _T("Box(F4)")));
		GetDlgItem(IDC_BUTTON_F4)->Invalidate();
	}
	((CButton*)GetDlgItem(IDC_CHECK_OFFLINE))->SetCheck(FALSE);
	  
	LockMarker();
	PMarker pMarker = GetMarker();

	if (pMarker!=NULL && E3_MarkerIsDeviceValid(pMarker))
	{
		GetDlgItem(IDC_BUTTON_F1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_F2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_F3)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_TOTAL)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PART)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_RESETCOUNT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_F4)->EnableWindow(TRUE);

		GetDlgItem(IDC_BUTTON_F4)->ShowWindow(E3_MarkerIsShowF4(pMarker) ? SW_SHOW : SW_HIDE);

		if (E3_MarkerIsSupportOffline(pMarker) && E3_MarkerGetAxisSol(pMarker) == MOTOR_SOL_NONE  && E3_MarkerGetAxisSol(m_pMarker) != MOTOR_SOL_XYZA_FREE)
		{
			E3_MarkerEnableOffLineMode(pMarker,FALSE);
			
			GetDlgItem(IDC_CHECK_OFFLINE)->ShowWindow(SW_SHOW);
		}
		else
		{
			GetDlgItem(IDC_CHECK_OFFLINE)->ShowWindow(SW_HIDE);
		}


		if (E3_MarkerIsShowGetButton(pMarker))
		{
			GetDlgItem(IDC_BUTTON_GET)->ShowWindow(SW_SHOW);
		}
		else
		{
			GetDlgItem(IDC_BUTTON_GET)->ShowWindow(SW_HIDE);
		}

		GetDlgItem(IDC_BUTTON_CALC)->ShowWindow((E3_MarkerGetAxisSol(pMarker) == MOTOR_SOL_NONE || E3_MarkerGetAxisSol(m_pMarker) != MOTOR_SOL_XYZA_FREE) ? SW_SHOW : SW_HIDE);

		GetDlgItem(IDC_STATIC_FLYSPEED)->ShowWindow(E3_MarkerIsEnableHardFly(pMarker) );
		GetDlgItem(IDC_BUTTON_FLYSPEED)->ShowWindow(E3_MarkerIsEnableHardFly(pMarker)  );


		GetDlgItem(IDC_STATIC_LAMP_READY)->ShowWindow(E3_MarkerGetLaserReadyInputNo(pMarker) >= 0);
		GetDlgItem(IDC_STATIC_READY)->ShowWindow(E3_MarkerGetLaserReadyInputNo(pMarker) >= 0);

		((CButton*)GetDlgItem(IDC_CHECK_REDCONTOUR))->SetCheck(E3_MarkerIsShowContour(m_pMarker) != 0 ? TRUE : FALSE);

		UnLockMarker();

		//激光准备输出端口
		if (E3_MarkerGetLaserReadyOutputNo(pMarker) >= 0 && E3_MarkerGetLaserReadyOutputNo(pMarker) < 16 && !m_bHideF3)
		{
			GetDlgItem(IDC_BUTTON_POWER)->ShowWindow(SW_SHOW);
			m_lampPower.ShowWindow(SW_SHOW);
			UpdateLaserPowerOutportState();
		}
		else
		{
			GetDlgItem(IDC_BUTTON_POWER)->ShowWindow(SW_HIDE);
			m_lampPower.ShowWindow(SW_HIDE);
		}
	}
	else
	{
		UnLockMarker();
		GetDlgItem(IDC_BUTTON_F1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_F2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_F3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TOTAL)->EnableWindow(FALSE);	
		GetDlgItem(IDC_EDIT_PART)->EnableWindow(FALSE);	
		GetDlgItem(IDC_BUTTON_RESETCOUNT)->EnableWindow(FALSE);	
	 
		GetDlgItem(IDC_BUTTON_F4)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_F4)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CHECK_OFFLINE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_GET)->ShowWindow(SW_HIDE); 
		GetDlgItem(IDC_BUTTON_CALC)->ShowWindow(SW_HIDE); 


		GetDlgItem(IDC_STATIC_LAMP_READY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_READY)->ShowWindow(SW_HIDE); 

		GetDlgItem(IDC_BUTTON_POWER)->ShowWindow(SW_HIDE);
	 	
		m_lampPower.ShowWindow(SW_HIDE);
	} 

	if( !gf_GetUserMgr()->GetCurUser()->m_bEnableMark)
	{
		GetDlgItem(IDC_BUTTON_F2)->EnableWindow(FALSE);
		 
		GetDlgItem(IDC_BUTTON_F4)->EnableWindow(FALSE);
	}

	if( !gf_GetUserMgr()->GetCurUser()->m_bEnableDevParam)
	{
		GetDlgItem(IDC_BUTTON_F3)->EnableWindow(FALSE);
	}

	

	BOOL bOffline = ((CButton*)GetDlgItem(IDC_CHECK_OFFLINE))->GetCheck();
	GetDlgItem(IDC_EDIT_FILEINDEX)->ShowWindow(bOffline ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_SPIN1)->ShowWindow(bOffline ? SW_SHOW : SW_HIDE);

	UpdateFlySpeed();
}
void CDlgMark::ShowTime()
{
	GetDlgItem(IDC_EDIT_PARTTIME)->SetWindowText(m_strPartTime);
	GetDlgItem(IDC_EDIT_TOTALTIME)->SetWindowText(m_markTotal.GetShowTimeStr());
}

void CDlgMark::SetPartTimeStr(CString str)
{
	m_strPartTime = str;
}

void CDlgMark::ShowCount()
{
	CString str;
	str.Format(_T("%d"),m_nTotalCount);
	GetDlgItem(IDC_EDIT_TOTAL)->SetWindowText(str);
	str.Format(_T("%d"),m_nPartCount);
	GetDlgItem(IDC_EDIT_PART)->SetWindowText(str);
}
 
void CDlgMark::GetCurCount()
{
	CString str; 
	GetDlgItem(IDC_EDIT_TOTAL)->GetWindowText(str);
	m_nTotalCount = QGlobal::ATOI(str);
	if(m_nTotalCount<0)
	{
		m_nTotalCount = 0;
	}

 	GetDlgItem(IDC_EDIT_PART)->GetWindowText(str);
	m_nPartCount = QGlobal::ATOI(str);
	if(m_nPartCount<0)
	{
		m_nPartCount = 0;
	} 
}

LRESULT  CDlgMark::OnUsbLmcArrive(WPARAM wParam, LPARAM lParam)	
{	
	int nCard = (int)wParam;
	if(nCard>=0 && nCard<8)
	{
		LockMarker();

		if(m_pMarker!=NULL)
		{	
			if(E3_MarkerIsStillValid(m_pMarker))
			{//当前设备有效,就不管新的设备
				UnLockMarker();
				return 0;
			}				
		}

		m_pMarker = NULL;
		UnLockMarker();

	 
		LockMarker();
		m_pMarker = E3_MarkerReGetOneNewValidDev(  );//设备断开后重新连接
		if(m_pMarker!=NULL)
		{			 
			E3_MarkerSetup(m_pMarker);//初始化当前设备 
		}  
		UnLockMarker();

		UpdateMotionPanel();

		if (E3_GetCmdMgr() != NULL)
		{//激光器被修改
			E3_CmdMgrSendMessageToEntWnd(E3_GetCmdMgr(),WM_USER_CHANGELASER, (WPARAM)m_pMarker, 0);
		}

		UpdateDevState();
		 
		m_bMarkRemovedFlag = FALSE;
	}
	return 0;
}

LRESULT  CDlgMark::OnUsbLmcRemove(WPARAM wParam, LPARAM lParam)
{	
	LockMarker();
	if (m_pMarker != NULL)
	{

		m_bMarkRemovedFlag = TRUE;

		int nOldAxisSol = E3_MarkerGetAxisSol(m_pMarker);
		if (nOldAxisSol != 0)
		{
			UnLockMarker();

			gf_DlgYesNo(QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")), QGlobal::gf_Str(_T("USBREMOVE_WARN"), _T("Usb is removed,please restart software!")), TRUE);
			return 0;
		}
	}
	UnLockMarker();
	return 0;
}

LRESULT  CDlgMark::OnUserUnitChange(WPARAM wParam, LPARAM lParam)
{	
	LockMarker();
	if(m_pMarker!=NULL)
	{ 
		E3_MarkerOnChangeUnit(m_pMarker);
		E3_MarkerSetup(m_pMarker);//初始化当前设备 
		UnLockMarker();

		UpdateMotionPanel();
		UpdateDevState(); 
	}
	else
	{
		UnLockMarker();
	}
	return 0;
}

//检查是否价格对象是空的
BOOL CDlgMark::CheckIsMarkEntityEmpty()
{
	BOOL bMarkSelected = ((CButton*)GetDlgItem(IDC_CHECK_SELECTED))->GetCheck();
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if(pEM==NULL)
	{
		return  TRUE;
	}
	PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
	ASSERT(pLayer!=NULL);  


	if(bMarkSelected)
	{
		if(E3_EntMgrPickCount(pEM)<=0)
		{		 
			gf_DlgYesNo(QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")),QGlobal::gf_Str(_T("MARKSTR_NOENTITY_SELECT"), _T("No data available. Check whether the object was selected ")),TRUE);
			return TRUE;
		}
 	}
	else
	{
		if(E3_GetEntChildCnt(pLayer)<=0)
		{
			gf_DlgYesNo(QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")),QGlobal::gf_Str(_T("MARKSTR_NOENTITY"), _T("No data available. Check whether the file was loaded")),TRUE);		 
			return TRUE;
		}
	 }
	return FALSE;
}
 
void CDlgMark::OnBnClickedButtonF1()
{
	// TODO: 在此添加控件通知处理程序代码 


	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return  ;
	}
	

	GetDlgItem(IDC_BUTTON_F1)->SetFocus();
	if(m_bNowMark )
	{
		return;
	}
	LockMarker();
	if (  m_pMarker == NULL)
	{
		UnLockMarker();
		return;
	}
	UnLockMarker();

	m_bNowMark = TRUE; 

	//检查是否价格对象是空的
	if(CheckIsMarkEntityEmpty())
	{
		m_bNowMark = FALSE;
		return;
	}
	m_bSendF2Msg = FALSE;
	m_bRedLightMode = TRUE;

	LockMarker();
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_REDCONTOUR);
	E3_MarkerSetShowContour(m_pMarker,pBtn->GetCheck());

	E3_MarkerSetEM(m_pMarker,pEM);

 	CDlgMarking dlg(this);

	dlg.m_bMarkSelected = ((CButton*)GetDlgItem(IDC_CHECK_SELECTED))->GetCheck();
	dlg.m_bMarkLayer = ((CButton*)GetDlgItem(IDC_CHECK_LAYER2))->GetCheck();
	dlg.m_bContinues = ((CButton*)GetDlgItem(IDC_CHECK_CONTINUE))->GetCheck();
	dlg.m_bRedLight = TRUE;
	
	dlg.m_pMarker = m_pMarker;

	UnLockMarker();

	dlg.DoModal();

	m_bNowMark = FALSE;

	if (m_bSendF2Msg)
	{
		m_bSendF2Msg = FALSE;
		GetDlgItem(IDC_BUTTON_F2)->SetFocus();
		OnMark(TRUE);
	}
	else
	{
		LockMarker();
		E3_MarkerGotoAfterPostion(m_pMarker);
		UnLockMarker(); 
	}
}

void CDlgMark::OnBnClickedButtonF2()

{
	GetDlgItem(IDC_BUTTON_F2)->SetFocus();
	OnMark(FALSE);
}

BOOL CDlgMark::IsMarkSelected()
{
	return ((CButton*)GetDlgItem(IDC_CHECK_SELECTED))->GetCheck();
}
void CDlgMark::OnMark(BOOL bEnableFromLight, BOOL bCalcTime)
{
	// TODO: 在此添加控件通知处理程序代码
	if( !gf_GetUserMgr()->GetCurUser()->m_bEnableMark)
	{
		return  ;
	}

	PEntMgr  pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return  ;
	}
	if (m_bNowMark  )
	{
		return;
	}

	LockMarker();
	if( m_pMarker==NULL)
	{
		UnLockMarker();
		return;
	}

	UnLockMarker();


	m_bNowMark = TRUE;
	m_bRedLightMode = FALSE;
	//检查是否价格对象是空的
	if(CheckIsMarkEntityEmpty())
	{
		m_bNowMark = FALSE;
		return;
	}
	
	LockMarker();
	BOOL bOffLine = ((CButton*)GetDlgItem(IDC_CHECK_OFFLINE))->GetCheck();
	//检查激光器状态是否准备好,bOpen如果激光器没打开是否打开
	if (!bCalcTime && !bOffLine && !E3_MarkerCheckLaserState(m_pMarker,TRUE))
	{
		m_bNowMark = FALSE;
		UnLockMarker();
		return;
	} 
	UnLockMarker();

	GetCurCount();

	m_markTotal.Start();

	LockMarker();
	CDlgMarking dlg(this);

	dlg.m_bMarkSelected = ((CButton*)GetDlgItem(IDC_CHECK_SELECTED))->GetCheck();
	dlg.m_bMarkLayer = ((CButton*)GetDlgItem(IDC_CHECK_LAYER2))->GetCheck();	
	dlg.m_bContinues = ((CButton*)GetDlgItem(IDC_CHECK_CONTINUE))->GetCheck();
	dlg.m_bOffLine = ((CButton*)GetDlgItem(IDC_CHECK_OFFLINE))->GetCheck();
	dlg.m_nFileCount = m_nFileCount;
	dlg.m_bCalcTimeMode = bCalcTime;
	
	E3_MarkerSetEM(m_pMarker,pEM);

	dlg.m_pMarker = m_pMarker;

	UnLockMarker();

	dlg.DoModal();

	LockMarker();
	if (m_pMarker != NULL)
	{
		m_strPartTime = E3_MarkerGetMarkTimerStr(m_pMarker,TRUE);
	}
	UnLockMarker();
	ShowTime();
	 
	OnUpdateMotorCoor();
	
	m_bNowMark = FALSE;

	E3_EntMgrBeginPick(pEM);
	E3_EntMgrEndPick(pEM);//更新对象显示
	E3_CmdMgrInvalidate();
	
	if (bCalcTime)
	{
		LockMarker();
		if (m_pMarker != NULL)
		{
			CString strTime = CMakeClock::GetShowTimeStr((int)(E3_MarkerGetCalcTotalMarkTime(m_pMarker) * 1000));
			gf_DlgYesNo(QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")), QGlobal::gf_Str(_T("ESTIMATEDTIME"), _T("estimated time")) + _T("\n") + strTime,TRUE);
		}
		UnLockMarker();
		return;
	}
	else if (bOffLine)
	{
		LockMarker();
		if (m_pMarker != NULL)
		{
			int nFileCount = 1;
			if (dlg.m_bMarkLayer)
			{//多层加工 
				nFileCount = min(m_nFileCount, E3_GetEntChildCnt(pEM));
			} 
			E3_MarkerSendMainProgramList(m_pMarker,nFileCount);
		}
		UnLockMarker(); 
		return;
	}


	if(dlg.m_bEnableLight || bEnableFromLight)
	{//开始加工
		OnBnClickedButtonF1();
	}
	else
	{
		LockMarker();
		E3_MarkerGotoAfterPostion(m_pMarker);
		UnLockMarker();
	}
}


void CDlgMark::OnBnClickedButtonF3()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("OnBnClickedButtonF3 Start\n");

	if (m_bNowMark || m_bIsParamSetting)
	{
		return;
	}
	if (!gf_GetUserMgr()->GetCurUser()->m_bEnableDevParam)
	{
		return;
	}

	
	m_bIsParamSetting = TRUE;
	m_bNowMark = TRUE;
	
	LockMarker();

	if (m_pMarker != NULL)
	{
		QMotorMgr* pMM = (QMotorMgr*)gf_GetMotorMgr();
		int nOldAxisSol = E3_MarkerGetAxisSol(m_pMarker);
		QMotor* m_motorSave[MAX_MOTOR_COUNT];
		for (int i = 0; i < MAX_MOTOR_COUNT; i++)
		{
			m_motorSave[i] = pMM->m_motorAll[i].GetCopy();
		}


		if (E3_MarkerSetDlgParam(m_pMarker) == IDOK)
		{
			E3_MarkerSaveParam(m_pMarker);
			E3_MarkerSetup(m_pMarker);//初始化当前设备

			gf_GetMotorMgr()->SaveParam(QGlobal::gf_GetParamPath() + _T("Motors.ini"));


			//检查轴参数是否改变
			BOOL bParamChangeed = FALSE;

			if (nOldAxisSol != E3_MarkerGetAxisSol(m_pMarker))
			{
				bParamChangeed = TRUE;
			}
			else
			{
				for (int i = 0; i < MAX_MOTOR_COUNT; i++)
				{
					if (!pMM->m_motorAll[i].IsSameParam(m_motorSave[i]))
					{
						bParamChangeed = TRUE;
						break;
					}
				}
			} 
			UnLockMarker();

			UpdateMotionPanel(bParamChangeed ? FALSE : TRUE);

			if (E3_GetCmdMgr() != NULL)
			{//激光器被修改
				E3_CmdMgrSendMessageToEntWnd(E3_GetCmdMgr(),WM_USER_CHANGELASER, (WPARAM)m_pMarker, 0);
			}
			UpdateDevState();
		}
		else
		{
			UnLockMarker();
		}

		//删除保存的电机参数
		for (int i = 0; i < MAX_MOTOR_COUNT; i++)
		{
			if (m_motorSave[i] != NULL)
			{
				delete m_motorSave[i];
				m_motorSave[i] = NULL;
			}
		}
	}
	else
	{
		UnLockMarker();
	}

	m_bNowMark = FALSE;
	m_bIsParamSetting = FALSE;
	TRACE("OnBnClickedButtonF3 End\n");
}

LRESULT CDlgMark::OnUserChangeEntity_1(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_BUTTON_F2)->SetFocus();
	OnMark(FALSE);
	return 0;
}
LRESULT CDlgMark::OnUserRed(WPARAM wParam, LPARAM lParam)
{// TODO: 在此添加控件通知处理程序代码 


	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return 0;
	}


	GetDlgItem(IDC_BUTTON_F1)->SetFocus();
	if (m_bNowMark)
	{
		return 0;
	}
	LockMarker();
	if (m_pMarker == NULL)
	{
		UnLockMarker();
		return 0;
	}
	UnLockMarker();

	m_bNowMark = TRUE;

	//检查是否价格对象是空的
	if (CheckIsMarkEntityEmpty())
	{
		m_bNowMark = FALSE;
		return 0;
	}
	m_bSendF2Msg = FALSE;
	m_bRedLightMode = TRUE;

	LockMarker();
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_REDCONTOUR);
	E3_MarkerSetShowContour(m_pMarker, pBtn->GetCheck());

	E3_MarkerSetEM(m_pMarker, pEM);

	CDlgMarking dlg(this);

	dlg.m_bMarkSelected = ((CButton*)GetDlgItem(IDC_CHECK_SELECTED))->GetCheck();
	dlg.m_bMarkLayer = ((CButton*)GetDlgItem(IDC_CHECK_LAYER2))->GetCheck();
	dlg.m_bContinues = ((CButton*)GetDlgItem(IDC_CHECK_CONTINUE))->GetCheck();
	dlg.m_bRedLight = TRUE;

	dlg.m_pMarker = m_pMarker;

	UnLockMarker();

	dlg.DoModal();

	m_bNowMark = FALSE;

	if (m_bSendF2Msg)
	{
		m_bSendF2Msg = FALSE;
		GetDlgItem(IDC_BUTTON_F2)->SetFocus();
		OnMark(TRUE);
	}
	else
	{
		LockMarker();
		E3_MarkerGotoAfterPostion(m_pMarker);
		UnLockMarker();
	}
	return 0;
}

//接受数据库删除对象消息，更新列表显示
LRESULT CDlgMark::OnUserChangeEntity(WPARAM wParam, LPARAM lParam)
{
	if (gf_GetSysParam()->GetParamInt(INT_PARAM_PROJECTVIEW))
	{
		OnBnClickedButtonF4();
	}
	return 0;
}

void CDlgMark::OnBnClickedButtonF4()
{   
	if (gf_GetSysParam()->GetParamInt(INT_PARAM_PROJECTVIEW))
	{
		PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
		if (pEM == NULL)
		{
			return;
		}
		CDC* pDC = this->GetDC(); 

		BOOL bMarkSelected = ((CButton*)GetDlgItem(IDC_CHECK_SELECTED))->GetCheck();
		E3_DoubleDisplayShow(pEM, pDC,bMarkSelected);

		this->ReleaseDC(pDC);
	}
	else
	{
		OnBnClickedButtonMark3dbox();
	}
}

void CDlgMark::OnBnClickedButtonCalcTime()
{
	if (m_bNowMark)
	{
		return;
	} 
	OnMark(FALSE, TRUE); 
} 

void CDlgMark::OnBnClickedButtonReset()
{
	if(m_bNowMark)
	{
		return;
	}
	m_nPartCount = 0;
	ShowCount();
}

void CDlgMark::OnBnClickedButtonMark3dbox()
{
	if(m_bNowMark)
	{
		return;
	}

	if (!E3_MarkerIsShowF4(m_pMarker))
	{
		return;
	}

	LockMarker();

	if (m_pMarker==NULL || E3_MarkerIsEnable3D( m_pMarker) == 0)
	{
		UnLockMarker();
		return;
	}
	UnLockMarker();


	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}

	PEntity pCurLayer = E3_EntMgrGetCurLayer(pEM);
	if (pCurLayer == NULL)
		return;

	 
	Box3d box;
	if(E3_GetCurLayerMeshBox(pCurLayer,box))
	{
		m_bNowMark = TRUE;
		m_bRedLightMode = FALSE;
		  
		LockMarker();

		E3_MarkerMarkBox(m_pMarker, pEM, box, 0);
			
		UnLockMarker();

		m_bNowMark = FALSE;
	}	 
	else
	{
		gf_DlgYesNo(QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")),QGlobal::gf_Str(_T("MARK_NOMESH"), _T("No mesh available. Check whether the mesh was loaded")),TRUE); 
	}
}


static int static_nStartNum = 0;
static WORD static_wLastPortData = 0;
static int static_nFlyTimeTickNum = 0;

BOOL IsStartInportOn(PMarker pMarker,WORD data)
{
	//标刻开始输入口
	int nStartMarkPort = E3_MarkerGetStartMarkInputNo(pMarker);
	if (nStartMarkPort >= 0 && nStartMarkPort < 16)
	{//标刻开始输入口 
		WORD bit = 0x0001;
		if (nStartMarkPort> 0)
		{
			bit = bit << nStartMarkPort;
		}

		BOOL bOnMark = (data & bit) ? TRUE : FALSE;
		if (E3_MarkerGetStartMarkLowValid(pMarker))
		{//低电平有效
			bOnMark = !bOnMark;
		}

		if (bOnMark)
		{
			if (E3_MarkerGetStartMarkPulseMode(pMarker))
			{//脉冲模式
				if (E3_MarkerGetStartMarkLowValid(pMarker))
				{//低电平有效
					if ((static_wLastPortData & bit))
					{//检测到下降沿开始加工
						return TRUE;
					}
				}
				else
				{//高电平有效
					if (!(static_wLastPortData & bit))
					{//检测到上升沿开始加工
						return TRUE;
					}
				}
			}
			else
			{//电平模式  
				return TRUE;
			}
		}
	}
	return FALSE;
}



void CDlgMark::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	if (nIDEvent == STARTMARK_TIMER )
	{
		
		if (m_bIsParamSetting)
		{
			return;
		}
		if (IsMarkerLocked())
		{
			return;
		}

		LockMarker();
		if (m_pMarker == NULL)
		{
			UnLockMarker();
			return;
		}
		UnLockMarker();

		LockMarker();
		if (m_pMarker!=NULL && E3_MarkerIsEnableHardFly(m_pMarker) )
		{//飞行模式,测线体速度
			UnLockMarker();
			static_nFlyTimeTickNum++;
			if (static_nFlyTimeTickNum > 10)
			{//1s一次
				static_nFlyTimeTickNum = 0;

				UpdateFlySpeed(); 
			}
		}
		else
		{
			UnLockMarker();
		}

		if (m_bNowMark)
		{
			LockMarker();
			if (m_pMarker != NULL)
			{
				m_strPartTime = E3_MarkerGetMarkTimerStr(m_pMarker,FALSE);//不使用卡内时间，防止通信太频繁
				ShowTime();
			}

			if (m_bRedLightMode && !m_bSendF2Msg)
			{
				//标刻开始输入口
				int nStartMarkPort = E3_MarkerGetStartMarkInputNo(m_pMarker);
				if (nStartMarkPort >= 0 && nStartMarkPort < 16)
				{//标刻开始输入口
					WORD data = E3_MarkerReadInPort(m_pMarker); 
					if (IsStartInportOn(m_pMarker,data))
					{//检测开始输入口
						E3_MarkerSetCancelFlag(m_pMarker, TRUE);
						m_bSendF2Msg = TRUE;
						UnLockMarker();
						return;
					} 	 
				} 
			} 
			UnLockMarker();
		}
		else
		{ 
			if(E3_IsCameraOpen() ) 
			{
				E3_CmdMgrInvalidate();
			}

			//设备被移除
			if (m_bMarkRemovedFlag)
			{
				LockMarker();
				if (m_pMarker != NULL)
				{
					int nCard = E3_MarkerGetCardIndex(m_pMarker);
					if (nCard >= 0)
					{
						E3_MarkerClose(nCard);
					}
					m_pMarker = NULL;
					UnLockMarker();

					UpdateDevState();
					if (E3_GetCmdMgr() != NULL)
					{//激光器被修改
						E3_CmdMgrSendMessageToEntWnd(E3_GetCmdMgr(), WM_USER_CHANGELASER, (WPARAM)m_pMarker, 0);
					}
				}
				else
				{
					UnLockMarker();
				}

				m_bMarkRemovedFlag = FALSE;
				return;
			}

			WORD data = 0;
			LockMarker();
			if (m_pMarker == NULL)
			{//读输入端口
				UnLockMarker();
				return;
			}

			if (m_pMarker != NULL)
			{
				data = E3_MarkerReadInPort(m_pMarker);

				//标刻开始输入口
				int nStartMarkPort = E3_MarkerGetStartMarkInputNo(m_pMarker);
				if (nStartMarkPort  >= 0 && nStartMarkPort < 16)
				{//标刻开始输入口
					if (IsStartInportOn(m_pMarker, data))
					{//检测开始输入口
						UnLockMarker();
						OnBnClickedButtonF2();
						static_wLastPortData = data;
						return;
					}
				}

				//红光预览输入口 
				int nRedPort = E3_MarkerGetRedInputNo(m_pMarker);
				if (nRedPort >= 0 && nRedPort < 16)
				{//红光预览输入口 
					WORD bit = 0x0001;
					if (nRedPort > 0)
					{
						bit = bit << nRedPort;
					}

					BOOL bOnLight = (data & bit) ? TRUE : FALSE;
					if (E3_MarkerGetRedInputLowValid(m_pMarker))
					{
						bOnLight = !bOnLight;
					}

					if (bOnLight)
					{
						UnLockMarker();
						OnBnClickedButtonF1();
						static_wLastPortData = data;
						return;
					}
				}

				//激光准备端入口
				int nReadyInput = E3_MarkerGetLaserReadyInputNo(m_pMarker);
				if (nReadyInput >= 0 && nReadyInput < 16)
				{//激光准备端入口
					WORD bit = 0x0001;
					if (nReadyInput > 0)
					{
						bit = bit << nReadyInput;
					}

					if (E3_MarkerGetLaserReadyLowValid(m_pMarker))
					{
						data = ~data;
					}
					if (data & bit)
					{
						m_lampReady.Green();
					}
					else
					{
						m_lampReady.Off();
					}
				}

				//激光准备输出端口
				int nReadyOutput = E3_MarkerGetLaserReadyOutputNo(m_pMarker);
				if (nReadyOutput >= 0 && nReadyOutput < 16)
				{
					if (m_bHideF3)
					{//tykma的特殊需求，判断是否有加工对象
						PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr()); 
						PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
						 
						ASSERT(pLayer != NULL);

						BOOL bMarkSelected = ((CButton*)GetDlgItem(IDC_CHECK_SELECTED))->GetCheck();
						BOOL bReady = FALSE;
						if (bMarkSelected)
						{
							if (E3_EntMgrPickCount(pEM) > 0)
							{
								bReady = TRUE;
							}
						}
						else
						{
							if (E3_GetEntChildHead(pLayer) != NULL)
							{
								bReady = TRUE;
							}
						}
						BOOL on = bReady;
						WORD data = E3_MarkerGetCurOutPortData(m_pMarker);
						WORD olddata = data;
						WORD bit = 0x0001;
						bit = bit << nReadyOutput;

						if (E3_MarkerGetLaserReadyOutputLowValid(m_pMarker))
						{//反转
							on = !on;
						}
						if (on)
						{
							data |= bit;

						}
						else
						{
							data &= ~bit;

						}
						E3_MarkerWriteOutPort(m_pMarker,data);
					}
					else
					{

					}
				}
			}
			static_wLastPortData = data;
			UnLockMarker();
		}
	}
}

void CDlgMark::OnBnClickedCheckOffline()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL bOffline = ((CButton*)GetDlgItem(IDC_CHECK_OFFLINE))->GetCheck();
	GetDlgItem(IDC_EDIT_FILEINDEX)->ShowWindow(bOffline ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_SPIN1)->ShowWindow(bOffline ? SW_SHOW : SW_HIDE);
	if (m_pMarker != NULL)
	{
		E3_MarkerEnableOffLineMode(m_pMarker,bOffline);
	}
}


void CDlgMark::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta > 0)
	{
		m_nFileCount++;
		if (m_nFileCount >8)
		{
			m_nFileCount = 8;
		}
	}
	else
	{
		m_nFileCount--;
		if (m_nFileCount < 1)
		{
			m_nFileCount = 1;
		}
	}
	 CString str;
	 str.Format(_T("%d"), m_nFileCount);
	 GetDlgItem(IDC_EDIT_FILEINDEX)->SetWindowText(str);
	 
	*pResult = 0;
}


void CDlgMark::OnBnClickedButtonGet()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bNowMark)
	{
		return;
	}
	E3_MarkerGetFeedbackCurves(m_pMarker);
}

void CDlgMark::UpdateMotionPanel(BOOL bNoInitial)
{
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr()); 
	if (pEM != NULL)
	{
		LockMarker();

		E3_MarkerUpdateEmTextBuildFlag(m_pMarker, pEM);

		WORD  wIoMaskInput, wIoMaskOutput;
		E3_MarkerGetIoMask(m_pMarker, wIoMaskInput, wIoMaskOutput);
		E3_CmdMgrSetIoMask(E3_GetCmdMgr(),wIoMaskInput, wIoMaskOutput);

		CMainFrame* pMainFrame = (CMainFrame*)gf_GetMainFrame();
		if (pMainFrame != NULL)
		{
			pMainFrame->m_barEntProp.m_wndEntBase.m_pMarker = m_pMarker;
		}

		UnLockMarker();
	}


	QMotorMgr* pMM = (QMotorMgr*)gf_GetMotorMgr();
	if (pMM != NULL)
	{ 
		pMM->LoadParam(QGlobal::gf_GetParamPath() + _T("Motors.ini"));

		if (bNoInitial)
		{

		}
		else
		{
			pMM->Initial(m_pMarker,E3_MarkerGetAxisSol(m_pMarker));
		}
		LockMarker();

		BOOL bShowMotionPanel = (m_pMarker != NULL && E3_MarkerGetAxisSol(m_pMarker) != MOTOR_SOL_NONE && E3_MarkerGetAxisSol(m_pMarker) != MOTOR_SOL_XYZA_FREE);
		GetDlgItem(IDC_STATIC_MOTORPANEL)->ShowWindow(bShowMotionPanel ? SW_SHOW : SW_HIDE);
		
		m_pDlgMotionPanel->ShowWindow(bShowMotionPanel ? SW_SHOW : SW_HIDE);

		UnLockMarker();

		m_pDlgMotionPanel->UpdateParam();
	}
	else
	{
		GetDlgItem(IDC_STATIC_MOTORPANEL)->ShowWindow( SW_HIDE);
	}
}

void CDlgMark::OnPageUp()
{ 
	if (!m_bNowMark && m_pDlgMotionPanel != NULL)
	{
		m_pDlgMotionPanel->OnPageUp();
	}
}
void CDlgMark::OnPageDown()
{
	if (!m_bNowMark && m_pDlgMotionPanel != NULL)
	{
		m_pDlgMotionPanel->OnPageDown();
	}
}

void CDlgMark::OnKeyUp()
{
	if (!m_bNowMark && m_pDlgMotionPanel != NULL)
	{
		LockMarker();
		if (m_pMarker != NULL && E3_MarkerGetAxisSol(m_pMarker) != MOTOR_SOL_NONE && E3_MarkerGetAxisSol(m_pMarker) != MOTOR_SOL_XYZA_FREE)
		{
			UnLockMarker();
			m_pDlgMotionPanel->OnKeyUp();
		}
		else
		{
			UnLockMarker();
		}
	}
}
void CDlgMark::OnKeyDown()
{
	if (!m_bNowMark && m_pDlgMotionPanel != NULL)
	{
		LockMarker();
		if (m_pMarker!=NULL && E3_MarkerGetAxisSol(m_pMarker) != MOTOR_SOL_NONE && E3_MarkerGetAxisSol(m_pMarker) != MOTOR_SOL_XYZA_FREE)
		{
			UnLockMarker();
			m_pDlgMotionPanel->OnKeyDown();
		}
		else
		{
			UnLockMarker();
		}
	}
} 
void CDlgMark::OnKeyLeft()
{
	if (!m_bNowMark && m_pDlgMotionPanel != NULL)
	{
		LockMarker();
		if (m_pMarker != NULL && E3_MarkerGetAxisSol(m_pMarker) != MOTOR_SOL_NONE && E3_MarkerGetAxisSol(m_pMarker) != MOTOR_SOL_XYZA_FREE)
		{
			UnLockMarker();
			m_pDlgMotionPanel->OnKeyLeft();
		}
		else
		{
			UnLockMarker();
		}
	}
}
void CDlgMark::OnKeyRight()
{
	if (!m_bNowMark && m_pDlgMotionPanel != NULL)
	{
		LockMarker();
		if (m_pMarker != NULL && E3_MarkerGetAxisSol(m_pMarker) != MOTOR_SOL_NONE && E3_MarkerGetAxisSol(m_pMarker) != MOTOR_SOL_XYZA_FREE)
		{
			UnLockMarker();
			m_pDlgMotionPanel->OnKeyRight();
		}
		else
		{
			UnLockMarker();
		}
	}
}
void CDlgMark::OnUpdateMotorCoor()
{ 
	LockMarker();
	if (m_pDlgMotionPanel != NULL && m_pMarker!=NULL && E3_MarkerGetAxisSol(m_pMarker) != MOTOR_SOL_NONE && E3_MarkerGetAxisSol(m_pMarker) != MOTOR_SOL_XYZA_FREE)
	{
		UnLockMarker();
		m_pDlgMotionPanel->ShowCurCoor();
	}
	else
	{
		UnLockMarker();
	}
}

void CDlgMark::OnStnClickedStaticMotorpanel()
{
	// TODO: 在此添加控件通知处理程序代码
}
void CDlgMark::UpdateFlySpeed()
{
	LockMarker();
	if (m_pMarker != NULL)
	{//模拟飞行 
		if (E3_MarkerIsEnableHardFly(m_pMarker)  )
		{
			double speed;
			CString strFly = E3_MarkerGetFlySpeed(m_pMarker,0x01, speed);			

			GetDlgItem(IDC_STATIC_FLYSPEED)->SetWindowText(strFly); 
		} 
	}
	UnLockMarker();
}

void CDlgMark::OnBnClickedButtonFlyspeed()
{
	// TODO: 在此添加控件通知处理程序代码
	LockMarker();
	E3_MarkerDlgSetFlySpeed(m_pMarker);
    UnLockMarker();
	UpdateFlySpeed(); 
}

void CDlgMark::OnBnClickedButtonPower( )
{
	LockMarker();
	if (m_pMarker != NULL)
	{ 
		int nReadyOutput = E3_MarkerGetLaserReadyOutputNo(m_pMarker);
		WORD data =E3_MarkerGetCurOutPortData(m_pMarker);
		WORD olddata = data;
		WORD bit = 0x0001;
		bit = bit << nReadyOutput;

		BOOL on = (data & bit)?TRUE:FALSE;
		if (E3_MarkerGetLaserReadyOutputLowValid(m_pMarker))
		{//反转
			on = !on;
		}
		on = !on;//设置反向

		if (E3_MarkerGetLaserReadyOutputLowValid(m_pMarker))
		{//反转
			on = !on;
		}
		if (on)
		{
			data |= bit;
		}
		else
		{
			data &= ~bit;
		}
		E3_MarkerWriteOutPort(m_pMarker,data);

		if (on)
		{
			m_lampPower.Green();
		}
		else
		{
			m_lampPower.Off();
		}
	}
	UnLockMarker(); 
	UpdateLaserPowerOutportState();
}


void CDlgMark::UpdateLaserPowerOutportState()
{
	LockMarker();
	int nReadyOutput = E3_MarkerGetLaserReadyOutputNo(m_pMarker);
	if (m_pMarker != NULL&& nReadyOutput >= 0 && nReadyOutput < 16 && !m_bHideF3)
	{	 
		WORD data =E3_MarkerGetCurOutPortData(m_pMarker);
		WORD olddata = data;
		WORD bit = 0x0001;
		bit = bit << nReadyOutput;

		BOOL on = (data & bit) ? TRUE : FALSE;
		if (E3_MarkerGetLaserReadyOutputLowValid(m_pMarker))
		{//反转
			on = !on;
		} 
		if (on)
		{
			m_lampPower.Green();
		}
		else
		{
			m_lampPower.Off();
		}
	}

	UnLockMarker();
}

void CDlgMark::OnBnClickedButtonCamera()
{
	if (E3_IsCameraOpen())
	{
		if (E3_IsCameraHide())
		{
			E3_SetCameraHide(FALSE);
		}
		else
		{
			E3_SetCameraHide(TRUE);
		}
		E3_CmdMgrInvalidate();

		if (E3_IsCameraHide())
		{
			m_buttonCamera.LoadImage(QGlobal::gf_GetResourcePath() + _T("CameraOff.png"));
		}
		else
		{
			m_buttonCamera.LoadImage(QGlobal::gf_GetResourcePath() + _T("CameraOn.png"));
		}
	}
}

