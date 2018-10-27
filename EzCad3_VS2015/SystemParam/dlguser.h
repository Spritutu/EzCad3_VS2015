/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CDlgUser.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/
#if !defined(AFX_DLGUSER_H__A1A0759D_F8C7_4564_8A04_EA1E0AE0067F__INCLUDED_)
#define AFX_DLGUSER_H__A1A0759D_F8C7_4564_8A04_EA1E0AE0067F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlguser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgUser dialog
#include "sysparam.h"
#include "..\resource.h"

class CDlgUser : public CDialog
{
// Construction
public:
	CDlgUser(CWnd* pParent = NULL);   // standard constructor
	void OK();

		CSysParam* m_pParam;
// Dialog Data
	//{{AFX_DATA(CDlgUser)
	enum { IDD = IDD_DIALOG_SYS_USER };
	CListBox	m_listUser;
	BOOL m_bEnUser;
	//}}AFX_DATA
void ShowEnuser();
void UpdateUserList();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUser)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDel();
	afx_msg void OnCheckEnuser();
	afx_msg void OnButtonModify();
	afx_msg void OnDblclkListUser();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUSER_H__A1A0759D_F8C7_4564_8A04_EA1E0AE0067F__INCLUDED_)
