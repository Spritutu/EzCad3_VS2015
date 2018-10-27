/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CQStaticColorBar.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2016年3月
* 版本纪录: 创建文件
*/

#pragma once

 

class GLOABL_EXT_CLASS CQStaticColorBar : public CWnd
{
private:
	COLORREF m_clrColor;
	CWnd*    m_pParent;
public:	
	void SetParant(CWnd* pParent);
	void SetColor(COLORREF color);
	COLORREF GetColor();

// Construction
public:	
	CQStaticColorBar(CWnd* pParent=NULL);
	CQStaticColorBar(COLORREF color,CWnd* pParent=NULL);
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(QStaticColorBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CQStaticColorBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(QStaticColorBar)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
