
#include "stdafx.h"

#include "LaserMonitorPanel.h"
#include "..\Resource.h"
#include "..\MainFrm.h"
#include "..\EzCad3_VS2015.h"
#include "QGlobal.h"

#include "usermessdef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


CLaserMonitorPanel::CLaserMonitorPanel()
{
	 
}

CLaserMonitorPanel::~CLaserMonitorPanel()
{
}

BEGIN_MESSAGE_MAP(CLaserMonitorPanel, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()

	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 消息处理程序

void CLaserMonitorPanel::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient, rectCombo;
	GetClientRect(rectClient);
	m_dlgMonitor.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CLaserMonitorPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

 
	m_dlgMonitor.Create(IDD_DIALOG_LASERMONITOR, this);
	m_dlgMonitor.ShowWindow(SW_SHOW);
	AdjustLayout(); 
	return 0;
}

void CLaserMonitorPanel::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}
CSize CLaserMonitorPanel::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	CSize size;
	size.cx = (bHorz ? 400 : 400);
	size.cy = (bHorz ? 50 : 50);
	return size;
}