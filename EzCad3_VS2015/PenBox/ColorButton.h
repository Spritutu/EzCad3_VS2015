/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CColorButton.h
* 文件标识：
* 摘要：  
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/
#pragma once

#include "..\Resource.h"

// CDlgPenColor 对话框
class CColorButton : public CButton
{
// Construction
public:
	CColorButton();

	COLORREF m_clrBtn; 
public:
	virtual ~CColorButton();

	void SetColor(COLORREF clrPen)
	{
		m_clrBtn = clrPen;
		Invalidate();
	}
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	// Generated message map functions
protected:
	//{{AFX_MSG(CColorButton)
	//afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

class CShowHideButton : public CMFCButton
{
	// Construction
public:
	CShowHideButton();
	 
	BOOL m_bShowOnOff;
public:
	virtual ~CShowHideButton();

	void SetShow(BOOL b);
	 
	// Generated message map functions
protected:
	//{{AFX_MSG(CColorButton)
	//afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};