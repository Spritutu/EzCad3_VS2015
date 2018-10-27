/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CDlgPsw.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/
#if !defined(AFX_DLGPSW_H__2891A103_8FAB_4049_9931_DE1DBE2A527A__INCLUDED_)
#define AFX_DLGPSW_H__2891A103_8FAB_4049_9931_DE1DBE2A527A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgpsw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPsw dialog

class CDlgPsw : public CDialog
{
// Construction
public:
	CDlgPsw(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPsw)
	enum { IDD = IDD_DIALOG_PSW };
	CString	m_strPsw1;
	CString	m_strPsw2;
	CString	m_strName;
	//}}AFX_DATA

	BOOL m_bCanChangeName;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPsw)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPsw)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPSW_H__2891A103_8FAB_4049_9931_DE1DBE2A527A__INCLUDED_)
