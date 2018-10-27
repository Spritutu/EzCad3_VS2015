// D:\项目\EzCad3_VS2015\EzCad3_VS2015\LaserMonitor\DlgLaserMonitorQcw.cpp : 实现文件
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "DlgLaserMonitorQcw.h"
#include "afxdialogex.h"
#include "..\Mark\MarkStd\DlgMark.h"
#include "QGlobal.h"
// DlgLaserMonitorQcw 对话框

IMPLEMENT_DYNAMIC(DlgLaserMonitorQcw, CDialogEx)

DlgLaserMonitorQcw::DlgLaserMonitorQcw(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LASER_SPI, pParent)
{

}

DlgLaserMonitorQcw::~DlgLaserMonitorQcw()
{
}

void DlgLaserMonitorQcw::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_LAMP1, m_lamp1);
	 
}


BEGIN_MESSAGE_MAP(DlgLaserMonitorQcw, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_RESETERR, &DlgLaserMonitorQcw::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// DlgLaserMonitorQcw 消息处理程序

BOOL DlgLaserMonitorQcw::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_lamp1.Off();
	GetDlgItem(IDC_BUTTON_RESETERR)->SetWindowText(QGlobal::gf_Str(_T("RESET"), _T("Reset")));
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
void DlgLaserMonitorQcw::SetErrorStr(CString str)
{
	GetDlgItem(IDC_STATIC_LASER)->SetWindowText(str);
}

static int st_nTempTick = 30;

void DlgLaserMonitorQcw::UpdateState(BOOL& bOK)
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
		if (bAlarm)
		{
			m_lamp1.Red();
			SetErrorStr(strError);
		}
		else
		{
			SetErrorStr(QGlobal::gf_Str(_T("LASERREADY"), _T("Laser ready!")));
			m_lamp1.Off();
			bOK = TRUE;
		}
		E3_MarkerHandleLaserFaultOutput(pMarker, bAlarm);
		if (pMarker != NULL)
		{
			st_nTempTick++;
			if (st_nTempTick > 30)
			{
				st_nTempTick = 0;

				double dTemp = E3_MarkerGetLaserTemp(pMarker);
				CString str;
				str.Format(_T("%s%.1f℃"), QGlobal::gf_Str(_T("TEMPERATURE"), _T("Temperature")), dTemp);
				GetDlgItem(IDC_STATIC_TEMP)->SetWindowText(str);
			}
		}
	}
	pDlg->UnLockMarker();
}

#include "..\MainFrm.h" 
void DlgLaserMonitorQcw::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
#ifdef ENABLE_MARK
	CMainFrame* pMainWnd = (CMainFrame*)gf_GetMainFrame();
	PMarker pMarker = pMainWnd->m_wndMark.GetMarker();
	if (pMarker != NULL)
	{
		E3_MarkerResetLaserError(pMarker);
	}
#endif
}
