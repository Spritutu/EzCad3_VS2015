//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2011 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// WatchBar.cpp : implementation file
//

#include "stdafx.h"

#include "DrawToolBar.h"
#include "..\resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CSegMFCToolBar2

IMPLEMENT_DYNAMIC(CSegMFCToolBar2, CMFCToolBar)

CSegMFCToolBar2::CSegMFCToolBar2()
{

}

CSegMFCToolBar2::~CSegMFCToolBar2()
{
}


BEGIN_MESSAGE_MAP(CSegMFCToolBar2, CMFCToolBar)
	ON_MESSAGE(WM_IDLEUPDATECMDUI, &CSegMFCToolBar2::OnIdleUpdateCmdUI)
END_MESSAGE_MAP()

void CSegMFCToolBar2::SetIsDlgControl(BOOL b)
{
	m_bIsDlgControl = b;
}
LRESULT CSegMFCToolBar2::OnIdleUpdateCmdUI(WPARAM wParam, LPARAM)
{
	// the style must be visible and if it is docked
	// the dockbar style must also be visible
	if ((GetStyle() & WS_VISIBLE) &&
		(m_pParentDockBar == NULL || (m_pParentDockBar->GetStyle() & WS_VISIBLE)))
	{
		CFrameWnd* pTarget = (CFrameWnd*)GetOwner();
	//	if (pTarget == NULL)
			pTarget = AFXGetParentFrame(this);
		if (pTarget != NULL)
			OnUpdateCmdUI(pTarget, (BOOL)wParam);
	} 
	return 0L;
}
/////////////////////////////////////////////////////////////////////////////
// CDrawToolBar

CDrawToolBar::CDrawToolBar()
{
}

CDrawToolBar::~CDrawToolBar()
{
}


BEGIN_MESSAGE_MAP(CDrawToolBar, CDockablePane)
	//{{AFX_MSG_MAP(CDrawToolBar)
	ON_WM_CREATE()
	ON_WM_SIZE() 
	ON_WM_SETFOCUS() 
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDrawToolBar message handlers

int CDrawToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1; 

	m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_LEFT | CBRS_TOOLTIPS | CBRS_GRIPPER | CBRS_BORDER_3D);
	m_wndToolBar.LoadToolBar(IDR_TOOLBAR_DRAW2);
	m_wndToolBar.SetIsDlgControl(TRUE);

//	m_wndToolBar.SetLockedSizes(CSize(25,25), CSize(30, 30), TRUE);
	m_wndToolBar.SetShowTooltips(TRUE);
	int image;
	UINT id;
	UINT style;
	m_wndToolBar.GetButtonInfo(1, id, style, image);
	m_wndToolBar.AdjustSizeImmediate();
	
	
//	m_wndToolBar.SetOwner(this);
//	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);
//	m_wndToolBar.OnUpdateCmdUI((CFrameWnd*)this, (WPARAM)TRUE);

	AdjustLayout();

	//CSize size = m_wndToolBar.GetButtonSize();
	//SetMinSize(CSize(size.cx+2, size.cy+2));
	 
	return 0;
}

void CDrawToolBar::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}
 
void CDrawToolBar::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rc;
	GetClientRect(rc);

 	CSize size = m_wndToolBar.GetButtonSize(); 
	CSize sizeMin;
	GetMinSize(sizeMin);
	if ((size.cx+2) != sizeMin.cx)
	{
		SetMinSize(CSize(size.cx + 2, size.cy + 2));
	}

	m_wndToolBar.SetWindowPos(NULL, rc.left , rc.top , rc.Width(), rc.Height() , SWP_NOACTIVATE | SWP_NOZORDER); 
}

 
void CDrawToolBar::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd); 
	m_wndToolBar.SetFocus(); 
}
 