/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CPenboxBar.h
* 文件标识：
* 摘要： 
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/

#pragma once

#include "DialogPenbox.h"
//

/////////////////////////////////////////////////////////////////////////////
// CPenboxBar window

class CPenboxBar : public CDockablePane
{
// Construction
public:
	CPenboxBar();

// Attributes
public:
	 CDialogPenbox	m_wndPenbox;
	 void AdjustLayout();
// Operations
public: 
// Implementation
public:
	virtual ~CPenboxBar();

	// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
		 
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

