// D:\项目\EzCad3_VS2015\EzCad3_VS2015\LaserMonitor\DlgLaserMonitorFiber.cpp : 实现文件
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "DlgLaserMonitorYag.h"
#include "afxdialogex.h"
#include "QGlobal.h"
#include "..\MainFrm.h"
#include "..\Mark\MarkStd\DlgMark.h"
// CDlgLaserMonitorYag 对话框

IMPLEMENT_DYNAMIC(CDlgLaserMonitorYag, CDialogEx)

CDlgLaserMonitorYag::CDlgLaserMonitorYag(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LASER_FIBER, pParent)
{
	m_bReady = FALSE;
}

CDlgLaserMonitorYag::~CDlgLaserMonitorYag()
{
	
}

void CDlgLaserMonitorYag::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_STATIC_LAMP1, m_lamp1); 
}


BEGIN_MESSAGE_MAP(CDlgLaserMonitorYag, CDialogEx) 
	ON_BN_CLICKED(IDC_BUTTON_ENABLE, &CDlgLaserMonitorYag::OnBnClickedButtonPw)
END_MESSAGE_MAP()


// CDlgLaserMonitorYag 消息处理程序


BOOL CDlgLaserMonitorYag::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_lamp1.Off();  
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CDlgLaserMonitorYag::UpdateState(BOOL& bOK)
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
		WORD state = E3_MarkerGetLaserState(pMarker);	
		state &= 0x0F;
		BOOL bAlarm = FALSE;
		if (state == 0x0F)
		{
			m_bReady = TRUE;
			m_lamp1.Green();
		}
		else
		{
			bAlarm = TRUE;
			m_bReady = FALSE;
			m_lamp1.Off();
		}

		E3_MarkerHandleLaserFaultOutput(pMarker, bAlarm);
	}
	pDlg->UnLockMarker();
}

void CDlgLaserMonitorYag::SetErrorStr(CString str)
{
	GetDlgItem(IDC_STATIC_LASER)->SetWindowText(str);
}

void CDlgLaserMonitorYag::OnBnClickedButtonPw()
{
#ifdef ENABLE_MARK
	CMainFrame* pMainWnd = (CMainFrame*)gf_GetMainFrame();
	PMarker pMarker = pMainWnd->m_wndMark.GetMarker();
	if (pMarker != NULL)
	{
		E3_MarkerSetLaserStartUp(pMarker, m_bReady?FALSE:TRUE);		
	}
#endif
}
