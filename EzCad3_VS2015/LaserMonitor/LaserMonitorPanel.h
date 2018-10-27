#pragma once

 

#include "DlgLaserMonitor.h"

class CLaserMonitorPanel : public CDockablePane
{
// 构造
public:
	CDlgLaserMonitor m_dlgMonitor;

	CLaserMonitorPanel();

	void AdjustLayout();
	  
// 属性
public:
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
// 实现
public:
	virtual ~CLaserMonitorPanel();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	
	DECLARE_MESSAGE_MAP()
	
};

