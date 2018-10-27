/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CQStaticBmp.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2016年3月
* 版本纪录: 创建文件
*/


#if !defined(AFX_QSTATICBMP_H__AB0C890B_8CF9_4A02_AB9B_BB0036821A6A__INCLUDED_)
#define AFX_QSTATICBMP_H__AB0C890B_8CF9_4A02_AB9B_BB0036821A6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// qstaticbmp.h : header file
//
 
/////////////////////////////////////////////////////////////////////////////
// CQStaticBmp window

class GLOABL_EXT_CLASS CQStaticBmp : public CWnd
{
// Construction
public:
	CQStaticBmp();

	BOOL m_bFitWnd;
	CBitmap m_bitmap;

	BOOL LoadBitmapsFile(CString bmpfile);
	BOOL LoadBitmaps(CString lpszBitmap);
	BOOL LoadBitmaps(UINT nBitmap);



// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQStaticBmp)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CQStaticBmp();

	// Generated message map functions
protected:
	//{{AFX_MSG(CQStaticBmp)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QSTATICBMP_H__AB0C890B_8CF9_4A02_AB9B_BB0036821A6A__INCLUDED_)
