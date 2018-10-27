/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CDlgLicense.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/
#if !defined(AFX_DLGLICENSE_H__6DB2E530_6B61_4E8E_9C51_915857DACBCC__INCLUDED_)
#define AFX_DLGLICENSE_H__6DB2E530_6B61_4E8E_9C51_915857DACBCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlglicense.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLicense dialog

class CDlgLicense : public CDialog
{
// Construction
public:
	CDlgLicense(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLicense)
	enum { IDD = IDD_DIALOG_LICENSE };
	CString	m_strLice;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLicense)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLicense)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLICENSE_H__6DB2E530_6B61_4E8E_9C51_915857DACBCC__INCLUDED_)
