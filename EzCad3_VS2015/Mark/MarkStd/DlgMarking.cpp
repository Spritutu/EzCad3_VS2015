// D:\项目\Visual Studio 2008\Ezcad3\Ezcad3\Mark\DlgMarkRedLight.cpp : 实现文件
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h" 
#include "QGlobal.h"

#include "DlgMarking.h"
#include "DlgMark.h"
#include "..\MarkerErrStr.h"
#include "Usermessdef.h"

#include "QMotor.h"
#include "QMotorMgr.h"
#include "SysParam.h"
#include "Box2d.h"
#define MARK_TIMER 11

 
DWORD WINAPI ThreadMarking(LPVOID lpParam)
{
	CDlgMarking*  pDlg = (CDlgMarking*)lpParam;
	if (pDlg == NULL)
	{
		ASSERT(0);
		return 0;
	}

	int nMarkFlag = 0;
	if (pDlg->m_bMarkSelected)
	{
		nMarkFlag |= MAKRFLAG_SELECT;
	}
	if (pDlg->m_bContinues)
	{
		nMarkFlag |= MAKRFLAG_CONTMODE;
	}
	if (pDlg->m_bCalcTimeMode)
	{
		nMarkFlag |= MAKRFLAG_CALCTIMEMODE;
		nMarkFlag &= ~MAKRFLAG_CONTMODE;
	}

	PEntMgr pEM = E3_MarkerGetEM(pDlg->m_pMarker);
	int nSol = E3_MarkerGetAxisSol(pDlg->m_pMarker);

	BOOL bRedEnableMotor = TRUE;
	if (pDlg->m_bRedLight && E3_MarkerIsRedDisableMotor(pDlg->m_pMarker))
	{
		bRedEnableMotor = FALSE;
	}

	if (E3_MarkerIsEnableHardFly(pDlg->m_pMarker))
	{//使能飞行
		if (E3_MarkerIsEnableTwoEncoder(pDlg->m_pMarker))
		{//使能飞行2
			nMarkFlag |= MAKRFLAG_TWORNCODERMODE;//双编码器模式
		}
		else
		{
			nMarkFlag |= MAKRFLAG_FLYMODE;
		}
	}

	if (E3_MarkerIsEnableWeld(pDlg->m_pMarker))
	{//焊接模式
	 	nMarkFlag|=MAKRFLAG_WELD;
	}

	if (pDlg->m_bRedLight)
	{
		nMarkFlag |= MAKRFLAG_REDLIGHT;
		nMarkFlag |= MAKRFLAG_CONTMODE;
	}
	else if (!pDlg->m_bCalcTimeMode)
	{
		if (pDlg->m_bMarkLayer)
		{//多层加工
			E3_MarkerSetCancelFlag(pDlg->m_pMarker,FALSE);

			nMarkFlag &= ~MAKRFLAG_SELECT;
			nMarkFlag &= ~MAKRFLAG_CONTMODE;

			if (pDlg->m_bOffLine)
			{//脱机模式
				nMarkFlag |= MAKRFLAG_OFFLINEMODE;

				int nFileCount = min(pDlg->m_nFileCount, E3_GetEntChildCnt(E3_MarkerGetEM(pDlg->m_pMarker)));
				for (int i = 0; i < nFileCount; i++)
				{
					PEntity pCurLayer = E3_GetEntChildByIndex(E3_MarkerGetEM(pDlg->m_pMarker),i);
					if(pCurLayer != NULL)
					{
						int nErr = E3_MarkerMarkEnt(pDlg->m_pMarker, E3_MarkerGetEM(pDlg->m_pMarker), pCurLayer, nMarkFlag, NULL, 0, 0, i);
						if (nErr != MERR_SUCCESS)
						{
							pDlg->m_nMarkReturnErr = nErr;
							pDlg->m_bThreadExitFlag = TRUE;
							return 0;
						}
					}
				}

				pDlg->m_nMarkReturnErr = MERR_SUCCESS;
				pDlg->m_bThreadExitFlag = TRUE;
				return 0; 
			}
			else
			{
				WORD data = 0, data2;

				pDlg->ShowInfo2(QGlobal::gf_Str(_T("WAITFORSTARTSIGNAL"), _T("Wait for select signal!")));
				WORD  ioLow, ioHigh;

				int nSaveMarkFinishOutputNo = E3_MarkerGetMarkFinishOutputNo(pDlg->m_pMarker);
				int nSaveMarkFinishLowValid = E3_MarkerGetMarkFinishLowValid(pDlg->m_pMarker);
				int nSaveMarkFinishPulseTime = E3_MarkerGetMarkFinishPulseTime(pDlg->m_pMarker);
				//暂时屏蔽
				E3_MarkerSetMarkFinishOutputNo(pDlg->m_pMarker,-1);

				int nErr;
				while (1)
				{
					//读当前输入信号
					data = E3_MarkerReadInPort(pDlg->m_pMarker);

					PEntity pCurLayer = E3_GetEntChildByIndex(E3_MarkerGetEM(pDlg->m_pMarker), 0);
					while (pCurLayer != NULL)
					{
						WORD ioLowStart, ioHighStart, ioLowFinish, ioHighFinish;
						int  nStartDelayMs, nEndDelayMs;
						BOOL bWaitForInput;
						E3_GetEntLayerIoSet(pCurLayer, ioLowStart, ioHighStart, ioLowFinish, ioHighFinish, nStartDelayMs, nEndDelayMs, bWaitForInput);						 

						//判断当前层是否要加工
						{ 
							E3_GetEntIoSet(pCurLayer, ioLow, ioHigh );
							if (ioHigh != 0 || ioLow != 0)
							{ 
								data2 = ~data;
								if ((data & ioHigh) != ioHigh || (data2 & ioLow) != ioLow)
								{
									if (bWaitForInput)
									{//需要一直等待输入信号
										pDlg->ShowInfo2(E3_GetEntName(pCurLayer)+_T(":")+QGlobal::gf_Str(_T("WAITFORINPUT"), _T("Wait for Input")));

										//判断是否取消
										if (E3_MarkerIsCancelMark(pDlg->m_pMarker))
										{
											pDlg->m_nMarkReturnErr = MERR_SUCCESS;
											pDlg->m_bThreadExitFlag = TRUE;
											E3_MarkerSetMarkFinishOutputNo(pDlg->m_pMarker, nSaveMarkFinishOutputNo);
											return 0;
										}
										Sleep(20);
										//继续读当前输入信号
										data = E3_MarkerReadInPort(pDlg->m_pMarker);
										continue;
									}
									else
									{//忽略当前层，加工下一层
										pCurLayer = E3_GetEntNext(pCurLayer);
										continue;
									}
								}	
							}
						}

						//开始加工图层
						pDlg->ShowInfo2(E3_GetEntName(pCurLayer));
						

						//输出开始信号
						if (ioHighStart != 0 || ioLowStart != 0)
						{ 
							WORD wIOMask = ioHighStart | ioLowStart;
							WORD wOldData = E3_MarkerGetCurOutPortData(pDlg->m_pMarker);
							wOldData &= ~wIOMask;
							wOldData |= ioHighStart;
							nErr = E3_MarkerWriteOutPort(pDlg->m_pMarker, wOldData);
							if (nErr != MERR_SUCCESS)
							{
								pDlg->m_nMarkReturnErr = nErr;
								pDlg->m_bThreadExitFlag = TRUE;
								E3_MarkerSetMarkFinishOutputNo(pDlg->m_pMarker, nSaveMarkFinishOutputNo);
								return 0;
							}
						}

						//开始延时
						if (nStartDelayMs > 0)
						{
							Sleep(nStartDelayMs);
						}

						//加工当前层
						int nMarkCount = E3_GetEntMarkCnt(pCurLayer); 
						for (int i = 0; i < nMarkCount; i++)
						{
							if ((nSol != MOTOR_SOL_NONE && nSol != MOTOR_SOL_XYZA_FREE && nSol != MOTOR_SOL_Z) && bRedEnableMotor)
							{
								nErr = E3_MarkerMarkEntWithMotorSol(pDlg->m_pMarker, pEM, pCurLayer, nMarkFlag);
							}
							else
							{
								nErr = E3_MarkerMarkEnt(pDlg->m_pMarker, pEM, pCurLayer, nMarkFlag, NULL, 0, 0, pDlg->m_nFileCount);
							}

							if (nErr != MERR_SUCCESS)
							{
								pDlg->m_nMarkReturnErr = nErr;
								pDlg->m_bThreadExitFlag = TRUE;
								E3_MarkerSetMarkFinishOutputNo(pDlg->m_pMarker, nSaveMarkFinishOutputNo);
								return 0;
							}
						}

						//结束延时
						if (nEndDelayMs > 0)
						{
							Sleep(nEndDelayMs);
						}

						//输出结束信号
						if (ioHighFinish != 0 || ioLowFinish != 0)
						{
							WORD wIOMask = ioHighFinish | ioLowFinish;
							WORD wOldData = E3_MarkerGetCurOutPortData(pDlg->m_pMarker);
							wOldData &= ~wIOMask;
							wOldData |= ioHighFinish;
							nErr = E3_MarkerWriteOutPort( pDlg->m_pMarker,wOldData);
							if (nErr != MERR_SUCCESS)
							{
								pDlg->m_nMarkReturnErr = nErr;
								pDlg->m_bThreadExitFlag = TRUE;
								E3_MarkerSetMarkFinishOutputNo(pDlg->m_pMarker, nSaveMarkFinishOutputNo);
								return 0;
							}
						}
											
						//结束当前图层加工，开始下一图层
						pCurLayer = E3_GetEntNext(pCurLayer);
						if (pCurLayer != NULL)
						{
							pDlg->ShowInfo2(QGlobal::gf_Str(_T("WAITFORSTARTSIGNAL"), _T("Wait for select signal!")));
						}
					}

					if (nSaveMarkFinishOutputNo >= 0 && nSaveMarkFinishOutputNo < 16)
					{//标刻结束输出口有效
						//AfxMessageBox(_T("1111"));
						WORD bit = 0x0001;
						if (nSaveMarkFinishOutputNo>0)
						{
							bit = bit << nSaveMarkFinishOutputNo;
						}
						WORD data = E3_MarkerGetCurOutPortData(pDlg->m_pMarker);
						if (!nSaveMarkFinishLowValid)
						{
							data |= bit;
						}
						else
						{
							data &= ~bit;
						}

						E3_MarkerWriteOutPort(pDlg->m_pMarker, data);
						Sleep(nSaveMarkFinishPulseTime);

						if (nSaveMarkFinishLowValid)
						{
							data |= bit;
						}
						else
						{
							data &= ~bit;
						}
						E3_MarkerWriteOutPort(pDlg->m_pMarker, data);
					}


					Sleep(20);
					if (E3_MarkerIsCancelMark(pDlg->m_pMarker))
					{
						pDlg->m_nMarkReturnErr = MERR_SUCCESS;
						pDlg->m_bThreadExitFlag = TRUE;
						E3_MarkerSetMarkFinishOutputNo(pDlg->m_pMarker, nSaveMarkFinishOutputNo);
						return 0;
					} 

					if (!pDlg->m_bContinues)
					{
						pDlg->m_nMarkReturnErr = MERR_SUCCESS;
						pDlg->m_bThreadExitFlag = TRUE;
						E3_MarkerSetMarkFinishOutputNo(pDlg->m_pMarker, nSaveMarkFinishOutputNo);
						return 0;
					}
				}
			}
		}
		else
		{
			if (pDlg->m_bOffLine)
			{//脱机模式
				nMarkFlag |= MAKRFLAG_OFFLINEMODE;
				nMarkFlag &= ~MAKRFLAG_CONTMODE; 
			}
		}
	}



	PEntity pLayer = E3_EntMgrGetCurLayer(pEM);


	ASSERT(pLayer != NULL);
	if((nSol  != MOTOR_SOL_NONE && nSol != MOTOR_SOL_XYZA_FREE && nSol != MOTOR_SOL_Z) && bRedEnableMotor)
	{		
		pDlg->m_nMarkReturnErr = E3_MarkerMarkEntWithMotorSol(pDlg->m_pMarker, pEM, pLayer, nMarkFlag);
	}
	else
	{
		pDlg->m_nMarkReturnErr = E3_MarkerMarkEnt(pDlg->m_pMarker, pEM, pLayer, nMarkFlag, NULL, 0, 0, 0);
	}
	pDlg->m_bThreadExitFlag = TRUE;
	return 0;
}


// CDlgMarking 对话框

IMPLEMENT_DYNAMIC(CDlgMarking, CDialog)

CDlgMarking::CDlgMarking(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMarking::IDD, pParent)
{
     m_bMarkSelected = FALSE;	
	 m_bMarkLayer=FALSE;
	 m_bContinues = FALSE;	
	 m_pEntParent = NULL; 
	 m_pMarker = NULL;
	 m_bEnableLight = FALSE;
	 m_pCurBmp= NULL;

	 m_hThreadMark=NULL;

	 m_pDlgMark = pParent;
	 m_bRedLight = FALSE;
	 m_bCalcTimeMode = FALSE;

	 m_bOffLine = FALSE;
	 m_nFileCount =0;
	 m_bRedLightMoveState = FALSE;
}

CDlgMarking::~CDlgMarking()
{
}

void CDlgMarking::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_buttonStop);
}


BEGIN_MESSAGE_MAP(CDlgMarking, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CDlgMarking::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CDlgMarking::OnBnClickedOk)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_USER_MOTORMOVE, OnMotorMove)
END_MESSAGE_MAP()

LRESULT  CDlgMarking::OnMotorMove(WPARAM wParam, LPARAM lParam)
{
	CDlgMark* pDlgMark = (CDlgMark*)m_pDlgMark;
	if (pDlgMark != NULL)
	{
		pDlgMark->OnUpdateMotorCoor();
	}
	return 0;
}

// CDlgMarking 消息处理程序
void CDlgMarking::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(m_pMarker!=NULL)
	{
		E3_MarkerSetCancelFlag(m_pMarker,TRUE );
	}
}
 
void CDlgMarking::OnCancel() 
{
	// TODO: Add extra cleanup here	
	if(m_pMarker!=NULL)
	{
		E3_MarkerSetCancelFlag(m_pMarker, TRUE);
	}
	
}

void CDlgMarking::OnOK() 
{
	// TODO: Add extra validation here
	
	//	CDialog::OnOK();
}

void CDlgMarking::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if(m_hThreadMark!=NULL)
	{
		CloseHandle(m_hThreadMark);		
		m_hThreadMark=NULL;
	}


	if(m_pCurBmp != NULL)
	{
		m_pCurBmp->DeleteObject();
		delete m_pCurBmp;
		m_pCurBmp = NULL;
	}
	//m_pMarker->SetShowTextWnd( NULL );		
}

void CDlgMarking::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CDlgMarking::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnOK();
}
void CDlgMarking::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==MARK_TIMER)
	{		
		if (m_bRedLight && m_bRedLightMoveState)
		{
			if (m_bThreadExitFlag)
			{//线程已经退出
				if (m_nMarkReturnErr == MERR_USER_STOP)
				{
					TranformEnt();
					m_bRedLightMoveState = FALSE;
					m_bThreadExitFlag = FALSE;
					DWORD dwThread;
					m_hThreadMark = CreateThread(NULL, 0, ThreadMarking, this, 0, &dwThread);
					return;
					return;
				}
			}
			else
			{
				return;
			}
		}

		int nPartCount = E3_MarkerGetAlreadyMarkPartCount(m_pMarker);//已经加工的零件数目
		CDlgMark* pDlgMark = (CDlgMark*)m_pDlgMark;
		if(pDlgMark != NULL && (m_nStartPartCount + nPartCount) != pDlgMark->m_nPartCount)
		{
			pDlgMark->m_nPartCount = m_nStartPartCount + nPartCount;
			pDlgMark->ShowCount();
		}
		
		//得到显示信息
		CString strMsg;  
		if (E3_MarkerGetShowMsg(m_pMarker,strMsg))
		{
			ShowInfo(strMsg);
		}


		if(m_bThreadExitFlag)
		{//线程已经退出
			if(m_nMarkReturnErr == MERR_SUCCESS && !m_bRedLight)
			{
				if(!m_bContinues && pDlgMark->m_nTotalCount != 0 && !m_bCalcTimeMode)
				{
					if(pDlgMark->m_nPartCount < pDlgMark->m_nTotalCount) 
					{//没到设定的加工总数，继续加工
						m_nStartPartCount = pDlgMark->m_nPartCount;
						m_bThreadExitFlag = FALSE;  
						DWORD dwThread;
						m_hThreadMark = CreateThread(NULL,0,ThreadMarking,this,0,&dwThread);  
						return;
					}
					else 
					{
						if(E3_MarkerIsAutoResetCount(m_pMarker))
						{//使能加工到总数后自动复位
							if(pDlgMark->m_nPartCount >= pDlgMark->m_nTotalCount)
							{//复位
								pDlgMark->m_nPartCount = 0;
								pDlgMark->ShowCount();
							}
						} 
					}
				}
			}
			else if (m_nMarkReturnErr != MERR_SUCCESS && m_nMarkReturnErr != MERR_USER_STOP)
			{
				KillTimer(MARK_TIMER);
				if (m_nMarkReturnErr == MERR_STOPSIGNAL)
				{
					gf_ShowStopSignalMessageBox(m_pMarker);
				}
				else
				{
					MessageBox(gf_GetMarkerErrStr(m_nMarkReturnErr), QGlobal::gf_Str(_T("WARN"), _T("Warn")), MB_OK | MB_ICONERROR);
				}
				CDialog::OnCancel();
				return;
			}

			KillTimer(MARK_TIMER);
			CDialog::OnCancel();
			return;
		} 
	}
	
	CDialog::OnTimer(nIDEvent);
}


BOOL CDlgMarking::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_bRedLight)
	{
	 	ShowInfo(QGlobal::gf_Str(_T("LIGHTING"), _T("Lighting...")));
	}
	else if (m_bCalcTimeMode)
	{
		ShowInfo(QGlobal::gf_Str(_T("CALCULATING"), _T("Calculating...")));
	}
	else
	{
		ShowInfo(QGlobal::gf_Str(_T("MARKING"), _T("Marking...")));
	}
	m_buttonStop.LoadImage(QGlobal::gf_GetResourcePath() + _T("Stop.png"));
	m_buttonStop.SetWindowText(_T(""));
	 
	CDlgMark* pDlgMark = (CDlgMark*)m_pDlgMark;
 	m_nStartPartCount = pDlgMark->m_nPartCount;


	if(m_pMarker!=NULL)
	{
		E3_MarkerSetOwnWnd(m_pMarker,this); 
	}
	
 	if(m_bMarkLayer)
	{
		GetDlgItem(IDC_STATIC_INFO2)->ShowWindow(SW_SHOW); 
	}
	
	m_bThreadExitFlag = FALSE;  

	DWORD dwThread;
	m_hThreadMark = CreateThread(NULL,0,ThreadMarking,this,0,&dwThread); 
	
	SetTimer(MARK_TIMER, 100, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
} 

void CDlgMarking::ShowInfo(CString str)
{
	SetWindowText(str);
	SetDlgItemText(IDC_STATIC_INFO,str);	
}
 
void CDlgMarking::ShowInfo2(CString str)
{ 
	SetDlgItemText(IDC_STATIC_INFO2, str);
}


BOOL CDlgMarking::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class  
	if (m_bRedLight &&  !m_bRedLightMoveState)
	{//红光预览
		if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN)
		{
			short nCtrl = GetKeyState(VK_CONTROL);
			BOOL bCtrl = nCtrl & 0x8000 ? TRUE : FALSE;
			switch (pMsg->wParam)
			{
			case VK_LEFT:
			case VK_RIGHT:
			case VK_UP:
			case VK_DOWN:
			case VK_PRIOR:		//PAGE_UP	
			case VK_NEXT:		//PAGE_DOWN:
								//if(bCtrl)
			{ 
				m_nChangeTranType = TRANSFORM_MOVE;
				if (pMsg->wParam == VK_LEFT)
				{ 
					m_mtxChangeEnt.Move(-gf_GetSysParam()->GetParamDouble(DOUBLE_PARAM_NUDGESMALLDIST), 0);
				}
				else if (pMsg->wParam == VK_RIGHT)
				{
					m_mtxChangeEnt.Move(gf_GetSysParam()->GetParamDouble(DOUBLE_PARAM_NUDGESMALLDIST), 0);
				}
				else if (pMsg->wParam == VK_UP)
				{
					m_mtxChangeEnt.Move(0, gf_GetSysParam()->GetParamDouble(DOUBLE_PARAM_NUDGESMALLDIST));
				}
				else if (pMsg->wParam == VK_DOWN)
				{
					m_mtxChangeEnt.Move(0, -gf_GetSysParam()->GetParamDouble(DOUBLE_PARAM_NUDGESMALLDIST));
				}
				else
				{
					Box2d bb= E3_EntMgrGetBox(E3_MarkerGetEM(m_pMarker), m_bMarkSelected);
					if (pMsg->wParam == VK_PRIOR)
					{
						m_mtxChangeEnt.Scale(bb.GetCenterPt().x, bb.GetCenterPt().y, 1.1, 1.1);
					}
					else
					{
						m_mtxChangeEnt.Scale(bb.GetCenterPt().x, bb.GetCenterPt().y, 0.90909, 0.90909);
					}
					m_nChangeTranType = TRANSFORM_SCALE;
				}
				m_bRedLightMoveState = TRUE;
				if (m_pMarker != NULL)
				{
					E3_MarkerSetCancelFlag(m_pMarker, TRUE);
				} 
				return TRUE;
			}
			break;
			default:
				break;
			}
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgMarking::TranformEnt()
{
	if (m_pMarker == NULL)
	{
		return;
	}
	PEntMgr pEM = E3_MarkerGetEM(m_pMarker);
	PEntity pCurLayer = E3_EntMgrGetCurLayer(pEM);
	if (pCurLayer == NULL)
	{
		return;
	}

	E3_EntMgrTransformAllUD(pEM, pCurLayer, m_bMarkSelected, m_mtxChangeEnt, m_nChangeTranType); 

	E3_CmdMgrInvalidate();	
}

