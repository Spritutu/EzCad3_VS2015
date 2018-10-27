
#pragma once

#include "DlgEntBase.h" 
//
 
 #define ENABLE_ENTBASE

/////////////////////////////////////////////////////////////////////////////
// CEntPropBar window

class CEntPropBar : public CDockablePane
{
// Construction
public:
	CEntPropBar();
	virtual BOOL DockToWindow(CDockablePane* pTargetWindow, DWORD dwAlignment, LPCRECT lpRect = NULL);
	virtual BOOL DockToFrameWindow(DWORD dwAlignment, LPCRECT lpRect = NULL, DWORD dwDockFlags = DT_DOCK_LAST, CBasePane* pRelativeBar = NULL, int nRelativeIndex = -1, BOOL bOuterEdge = FALSE);

// Attributes
 
public:
#ifdef  ENABLE_ENTBASE
 	 CDlgEntBase	m_wndEntBase;
#endif	 
	void AdjustLayout() ;
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEntPropBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEntPropBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEntPropBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

