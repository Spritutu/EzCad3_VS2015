/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CDlgBackup.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/
#if !defined(AFX_DLGBACKUP_H__8B454184_FDC5_4491_87EB_DB55593F14CA__INCLUDED_)
#define AFX_DLGBACKUP_H__8B454184_FDC5_4491_87EB_DB55593F14CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgbackup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBackup dialog
#include "sysparam.h"
#include "..\resource.h"

class CDlgBackup : public CDialog
{
// Construction
public:
	CDlgBackup(CWnd* pParent = NULL);   // standard constructor
	void OK();
	
		CSysParam* m_pParam;
// Dialog Data
	//{{AFX_DATA(CDlgBackup)
	enum { IDD = IDD_DIALOG_SYS_BACKUP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBackup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBackup)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnKillfocusEditSavetime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBACKUP_H__8B454184_FDC5_4491_87EB_DB55593F14CA__INCLUDED_)
