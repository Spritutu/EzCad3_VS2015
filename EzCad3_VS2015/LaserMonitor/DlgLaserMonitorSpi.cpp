// D:\项目\EzCad3_VS2015\EzCad3_VS2015\LaserMonitor\DlgLaserMonitorSpi.cpp : 实现文件
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "DlgLaserMonitorSpi.h"
#include "afxdialogex.h"
#include "..\Mark\MarkStd\DlgMark.h"
#include "QGlobal.h"
// DlgLaserMonitorSpi 对话框

IMPLEMENT_DYNAMIC(DlgLaserMonitorSpi, CDialogEx)

DlgLaserMonitorSpi::DlgLaserMonitorSpi(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LASER_SPI, pParent)
{

}

DlgLaserMonitorSpi::~DlgLaserMonitorSpi()
{
}

void DlgLaserMonitorSpi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_LAMP1, m_lamp1);
	 
}


BEGIN_MESSAGE_MAP(DlgLaserMonitorSpi, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_MONITOR, &DlgLaserMonitorSpi::OnBnClickedButtonMonitor)
END_MESSAGE_MAP()


// DlgLaserMonitorSpi 消息处理程序

BOOL DlgLaserMonitorSpi::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_lamp1.Off();
	 

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
void DlgLaserMonitorSpi::SetErrorStr(CString str)
{
	GetDlgItem(IDC_STATIC_LASER)->SetWindowText(str);
}
void DlgLaserMonitorSpi::UpdateState(BOOL& bOK)
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
		if (!bAlarm)
		{
			m_lamp1.Off();
			SetErrorStr(QGlobal::gf_Str(_T("LASERREADY"), _T("Laser ready!")));
			bOK = TRUE;
		}
		else
		{ 
			m_lamp1.Red();
			SetErrorStr(strError);
		}

		E3_MarkerHandleLaserFaultOutput(pMarker, bAlarm);
	}
	pDlg->UnLockMarker();
}
#include "..\MainFrm.h"
#include "QDlg.h"
void DlgLaserMonitorSpi::OnBnClickedButtonMonitor()
{
	// TODO: 在此添加控件通知处理程序代码
#ifdef ENABLE_MARK
	CMainFrame* pMainWnd = (CMainFrame*)gf_GetMainFrame();
	PMarker pMarker = pMainWnd->m_wndMark.GetMarker();
	if (pMarker != NULL)
	{		
		gf_DlgShowIoState(E3_MarkerGetLaserState(pMarker));
	}
#endif
}
