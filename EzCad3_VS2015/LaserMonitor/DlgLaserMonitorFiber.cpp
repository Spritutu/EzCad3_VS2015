// D:\项目\EzCad3_VS2015\EzCad3_VS2015\LaserMonitor\DlgLaserMonitorFiber.cpp : 实现文件
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "DlgLaserMonitorFiber.h"
#include "afxdialogex.h"
#include "QGlobal.h"
#include "..\MainFrm.h"
#include "..\Mark\MarkStd\DlgMark.h"
// CDlgLaserMonitorFiber 对话框

IMPLEMENT_DYNAMIC(CDlgLaserMonitorFiber, CDialogEx)

CDlgLaserMonitorFiber::CDlgLaserMonitorFiber(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LASER_FIBER, pParent)
{

}

CDlgLaserMonitorFiber::~CDlgLaserMonitorFiber()
{
	
}

void CDlgLaserMonitorFiber::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_STATIC_LAMP1, m_lamp1);
	DDX_Control(pDX, IDC_STATIC_LAMP2, m_lamp2);
	DDX_Control(pDX, IDC_STATIC_LAMP3, m_lamp3);  
}


BEGIN_MESSAGE_MAP(CDlgLaserMonitorFiber, CDialogEx)
	
	 
	ON_BN_CLICKED(IDC_BUTTON_PW, &CDlgLaserMonitorFiber::OnBnClickedButtonPw)
END_MESSAGE_MAP()


// CDlgLaserMonitorFiber 消息处理程序


BOOL CDlgLaserMonitorFiber::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_lamp1.Off();
	m_lamp2.Off();
	m_lamp3.Off();
	GetDlgItem(IDC_STATIC_PW)->SetWindowText(_T(""));
	GetDlgItem(IDC_BUTTON_PW)->SetWindowText(QGlobal::gf_Str(_T("PULSEWIDTH"), _T("Pulse width")));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CDlgLaserMonitorFiber::UpdateState(BOOL& bOK)
{
	 
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL || pDlg->IsMarkerLocked())
	{
		return;
	}

	pDlg->LockMarker();
	PMarker pMarker = pDlg->GetMarker();
	if (pMarker != NULL)
	{ 
		CString strError;
		BOOL bAlarm = E3_MarkerIsLaserAlarm(pMarker, strError);
		WORD state = E3_MarkerGetLaserState(pMarker);
		 
		//Bit4：MO
		//Bit5  AP
		if (state & 0x0010)
		{
			m_lamp1.Red();
		}
		else
		{
			m_lamp1.Off();
		}

		if (state & 0x0020)
		{
			m_lamp2.Red();
		}
		else
		{
			m_lamp2.Off();
		} 

		if (bAlarm)
		{ 
			m_lamp3.Red();
			SetErrorStr(strError);
		} 
		else
		{
			SetErrorStr(QGlobal::gf_Str(_T("LASERREADY"), _T("Laser ready!")));
			m_lamp3.Off();
			bOK = TRUE;
		}


		if (E3_MarkerIsEnablePulseWidth(pMarker))
		{//支持脉冲宽度 
			GetDlgItem(IDC_STATIC_PW)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BUTTON_PW)->ShowWindow(SW_SHOW);
		}
		else
		{
			GetDlgItem(IDC_STATIC_PW)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BUTTON_PW)->ShowWindow(SW_HIDE);
		}

		E3_MarkerHandleLaserFaultOutput(pMarker, bAlarm);
	}
	pDlg->UnLockMarker();
}

void CDlgLaserMonitorFiber::SetErrorStr(CString str)
{
	GetDlgItem(IDC_STATIC_LASER)->SetWindowText(str);
}

void CDlgLaserMonitorFiber::OnBnClickedButtonPw()
{
#ifdef ENABLE_MARK
	CMainFrame* pMainWnd = (CMainFrame*)gf_GetMainFrame();
	PMarker pMarker = pMainWnd->m_wndMark.GetMarker();
	if (pMarker != NULL)
	{ 
		// TODO: 在此添加控件通知处理程序代码
		if (E3_MarkerIsEnablePulseWidth(pMarker))
		{//支持脉冲宽度 
			int  nPulseWidth = E3_MarkerGetFiberPulseWidth(pMarker);
			CString strPW;
			strPW.Format(_T("%d"), nPulseWidth);
			GetDlgItem(IDC_STATIC_PW)->SetWindowText(strPW);
		}
	}
#endif
}
