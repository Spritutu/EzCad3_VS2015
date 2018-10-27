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

#include "EntListBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_LIST_1	1

/////////////////////////////////////////////////////////////////////////////
// CEntListBar

CEntListBar::CEntListBar()
{
}

CEntListBar::~CEntListBar()
{
}


BEGIN_MESSAGE_MAP(CEntListBar, CDockablePane)
	//{{AFX_MSG_MAP(CEntListBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CEntListBar message handlers

int CEntListBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	 

	m_wndEntList.Create (IDD_DIALOG_ENTLIST, this);
	m_wndEntList.ShowWindow( SW_SHOW );	

	AdjustLayout();
	return 0;
}

void CEntListBar::OnSize(UINT nType, int cx, int cy) 
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}
BOOL CEntListBar::LoadState(LPCTSTR lpszProfileName, int nIndex, UINT uiID)
{
	return CDockablePane::LoadState(lpszProfileName, nIndex, uiID);
}
BOOL CEntListBar::SaveState(LPCTSTR lpszProfileName, int nIndex, UINT uiID)
{
	return CDockablePane::SaveState(lpszProfileName, nIndex, uiID);
}
BOOL  CEntListBar::DockToWindow(CDockablePane* pTargetWindow, DWORD dwAlignment, LPCRECT lpRect)
{
	return CDockablePane::DockToWindow(pTargetWindow, dwAlignment, lpRect);
}

BOOL CEntListBar::DockToFrameWindow(DWORD dwAlignment, LPCRECT lpRect , DWORD dwDockFlags, CBasePane* pRelativeBar , int nRelativeIndex , BOOL bOuterEdge )
{
	return CDockablePane::DockToFrameWindow( dwAlignment,  lpRect,  dwDockFlags ,  pRelativeBar ,  nRelativeIndex ,  bOuterEdge );

}
void CEntListBar::AdjustLayout() 
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rc;
	GetClientRect(rc);

	m_wndEntList.SetWindowPos(NULL,	rc.left + 1, rc.top + 1,rc.Width() - 2, rc.Height () - 2,SWP_NOACTIVATE | SWP_NOZORDER);  
}

void CEntListBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rectTree;
	m_wndEntList.GetWindowRect (rectTree);
	ScreenToClient (rectTree);

	rectTree.InflateRect (1, 1);
	dc.Draw3dRect (rectTree, ::GetSysColor (COLOR_3DSHADOW), ::GetSysColor (COLOR_3DSHADOW));
}

void CEntListBar::OnSetFocus(CWnd* pOldWnd) 
{
	CDockablePane::OnSetFocus(pOldWnd);
	
	m_wndEntList.SetFocus ();
	
}

void CEntListBar::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	m_wndEntList.SetCurFont();
}

void CEntListBar::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	ASSERT(1);
}