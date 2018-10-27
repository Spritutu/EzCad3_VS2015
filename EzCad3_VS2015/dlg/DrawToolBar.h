 
#pragma once 

/////////////////////////////////////////////////////////////////////////////
// CEntListBar window

#include "..\TipsMessageText.h"

// CDialogDrawTool ¶Ô»°¿ò
class CSegMFCToolBar2 : public CMFCToolBar
{
	DECLARE_DYNAMIC(CSegMFCToolBar2)

public:
	CSegMFCToolBar2();
	virtual ~CSegMFCToolBar2();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
public:
	void SetIsDlgControl(BOOL b);

	virtual BOOL OnUserToolTip(CMFCToolBarButton* pButton, CString& strTTText) const
	{
		strTTText = GetMessageFullText(pButton->m_nID);
		AfxExtractSubString(strTTText, strTTText, 1, _T('\n'));
		return TRUE;
	}
};



class CDrawToolBar : public CDockablePane
{
	// Construction
public:
	CDrawToolBar();

	CSegMFCToolBar2 m_wndToolBar; 
 
	// Attributes
protected:
	 
	// Operations
public:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEntListBar)
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CDrawToolBar();
	void AdjustLayout();
	// Generated message map functions
protected:
	//{{AFX_MSG(CEntListBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy); 
	afx_msg void OnSetFocus(CWnd* pOldWnd); 
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
 