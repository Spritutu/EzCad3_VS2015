// D:\项目\EzCad3_VS2015\EzCad3_VS2015\LaserMonitor\DlgLaserMonitor.cpp : 实现文件
//

#include "stdafx.h"
#include "..\\EzCad3_VS2015.h"
#include "DlgLaserMonitor.h"
#include "afxdialogex.h"
#include "usermessdef.h"
#include "..\Mark\MarkStd\DlgMark.h"

#define LASERMONITOR_TIMER 234
// CDlgLaserMonitor 对话框

IMPLEMENT_DYNAMIC(CDlgLaserMonitor, CDialogEx)

CDlgLaserMonitor::CDlgLaserMonitor(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LASERMONITOR, pParent)
{
	m_nTimeID = 0;
	m_nCurLaserType = LASER_YAG;
}

CDlgLaserMonitor::~CDlgLaserMonitor()
{
}

void CDlgLaserMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}


BEGIN_MESSAGE_MAP(CDlgLaserMonitor, CDialogEx)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_USER_CHANGELASER, OnUserLaserChange)
END_MESSAGE_MAP()


// CDlgLaserMonitor 消息处理程序

void CDlgLaserMonitor::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	if (m_nTimeID != 0)
	{
		KillTimer(m_nTimeID);
		m_nTimeID = 0;
	}
}


//接受数据库的选取对象改变消息，更新列表显示
LRESULT CDlgLaserMonitor::OnUserLaserChange(WPARAM wParam, LPARAM lParam)
{ 
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return 0;
	}
	pDlg->LockMarker();
	PMarker pMarker = pDlg->GetMarker();
 	m_nCurLaserType = E3_MarkerGetLaserType( pMarker );
	
	pDlg->UnLockMarker();

	m_dlgFiber.ShowWindow(m_nCurLaserType == LASER_FIBER?SW_SHOW:SW_HIDE);
	m_dlgSpi.ShowWindow(m_nCurLaserType == LASER_SPI ? SW_SHOW : SW_HIDE);
	m_dlgQcw.ShowWindow(m_nCurLaserType == LASER_QCW ? SW_SHOW : SW_HIDE);
	m_dlgYag.ShowWindow(m_nCurLaserType == LASER_YAG ? SW_SHOW : SW_HIDE);
	return 0;
}

BOOL CDlgLaserMonitor::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CWnd* pParentWnd = GetDlgItem(IDC_STATIC_LASER);

	 m_dlgFiber.Create(IDD_DIALOG_LASER_FIBER, pParentWnd);
	 m_dlgSpi.Create(IDD_DIALOG_LASER_SPI, pParentWnd);
	 m_dlgQcw.Create(IDD_DIALOG_LASER_QCW, pParentWnd);
	 m_dlgYag.Create(IDD_DIALOG_LASER_YAG, pParentWnd);
	 if (E3_GetCmdMgr() != NULL)
	 {
		 E3_CmdMgrAddEntityWnd(E3_GetCmdMgr(), this);
	 }
	 m_nTimeID= SetTimer(LASERMONITOR_TIMER, 1000, NULL);

	 OnUserLaserChange(0,0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CDlgLaserMonitor::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == LASERMONITOR_TIMER)
	{
		BOOL bHaveState = FALSE;
		BOOL  bOK = FALSE;

		if (m_nCurLaserType == LASER_YAG)
		{
			if (m_dlgYag.IsWindowVisible())
			{
				m_dlgYag.UpdateState(bOK);
				bHaveState = TRUE;
			}
		}
		else if (m_nCurLaserType == LASER_FIBER)
		{
			if (m_dlgFiber.IsWindowVisible())
			{
				m_dlgFiber.UpdateState(bOK);
				bHaveState = TRUE;
			}
		}
		else if (m_nCurLaserType == LASER_SPI)
		{
			if (m_dlgSpi.IsWindowVisible())
			{
				m_dlgSpi.UpdateState(bOK);
				bHaveState = TRUE;
			}
		}
		else if (m_nCurLaserType == LASER_QCW)
		{
			if (m_dlgQcw.IsWindowVisible())
			{
				m_dlgQcw.UpdateState(bOK);
				bHaveState = TRUE;
			}
		} 
		else if (m_nCurLaserType == LASER_YAG)
		{
			if (m_dlgYag.IsWindowVisible())
			{
				m_dlgYag.UpdateState(bOK);
				bHaveState = TRUE;
			}
		} 
	}
}