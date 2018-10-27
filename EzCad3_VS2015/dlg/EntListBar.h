
#if !defined(AFX_WATCHBAR_H__31A1AF6B_7EB0_11D3_95C6_00A0C9289F1B__INCLUDED_)
#define AFX_WATCHBAR_H__31A1AF6B_7EB0_11D3_95C6_00A0C9289F1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WatchBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEntListBar window
#include "DlgEntList.h"
class CEntListBar : public CDockablePane
{
// Construction
public:
	CEntListBar();

	virtual BOOL LoadState(LPCTSTR lpszProfileName = NULL, int nIndex = -1, UINT uiID = (UINT)-1);
	virtual BOOL SaveState(LPCTSTR lpszProfileName = NULL, int nIndex = -1, UINT uiID = (UINT)-1);
	virtual BOOL DockToWindow(CDockablePane* pTargetWindow, DWORD dwAlignment, LPCRECT lpRect = NULL);
	virtual BOOL DockToFrameWindow(DWORD dwAlignment, LPCRECT lpRect = NULL, DWORD dwDockFlags = DT_DOCK_LAST, CBasePane* pRelativeBar = NULL, int nRelativeIndex = -1, BOOL bOuterEdge = FALSE);

// Attributes
protected:
	
	CDlgEntList m_wndEntList;
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEntListBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEntListBar();
	void AdjustLayout() ;
	// Generated message map functions
protected:
	//{{AFX_MSG(CEntListBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WATCHBAR_H__31A1AF6B_7EB0_11D3_95C6_00A0C9289F1B__INCLUDED_)
