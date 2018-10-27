/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CDlgLanguage.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/
#if !defined(AFX_DLGLANGUAGE_H__B797199C_CE74_4861_843D_BC6887223552__INCLUDED_)
#define AFX_DLGLANGUAGE_H__B797199C_CE74_4861_843D_BC6887223552__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlglanguage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLanguage dialog
#include "sysparam.h"
#include "..\resource.h"

class CDlgLanguage : public CDialog
{
// Construction
public:
	CDlgLanguage(CWnd* pParent = NULL);   // standard constructor

	int m_nValidNum;
	CString  m_szValidLangName[100];

	CSysParam* m_pParam;

	void OK();

// Dialog Data
	//{{AFX_DATA(CDlgLanguage)
	enum { IDD = IDD_DIALOG_SYS_LANG };
	CComboBox	m_comboLang;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLanguage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLanguage)
	virtual BOOL OnInitDialog();
		virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLANGUAGE_H__B797199C_CE74_4861_843D_BC6887223552__INCLUDED_)
