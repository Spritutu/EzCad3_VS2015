/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CQPngButton.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/
#pragma once

#include <GdiPlus.h> 
#include <gdiplusHeaders.h>
#include <gdiplusGraphics.h>

using namespace Gdiplus;
class GLOABL_EXT_CLASS CQPngButton : public CButton
{
private:
	Image* m_pImgBtn;
public:
	void DrawButton(CDC *pDC, CRect rectBtn);
	// Construction
public:
	CQPngButton(CWnd* pParent = NULL);
	void LoadImage(CString strFile);
	 
 	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQPngButton)
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CQPngButton();

	// Overrides
public:
 	// Generated message map functions
protected:
	//{{AFX_MSG(CQPngButton) 
	afx_msg void OnPaint();
 	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
