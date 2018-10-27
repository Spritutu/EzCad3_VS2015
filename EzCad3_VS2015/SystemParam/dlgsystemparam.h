/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CDlgSystemParam.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/
#if !defined(AFX_DLGSYSTEMPARAM_H__630C8BB7_FDDA_4177_9562_DA418873131B__INCLUDED_)
#define AFX_DLGSYSTEMPARAM_H__630C8BB7_FDDA_4177_9562_DA418873131B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgsystemparam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSystemParam dialog
#include "DlgGeneral.h"
#include "DlgColor.h"
#include "DlgWorkSpace.h"
#include "DlgBackup.h"
#include "DlgMoveRotate.h"
//#include "DlgPlug.h"
#include "DlgLanguage.h"
#include "DlgUser.h"

#include "sysparam.h"
#include "..\resource.h"

class CDlgSystemParam : public CDialog
{
// Construction
public:
	CDlgSystemParam(CWnd* pParent = NULL);   // standard constructor

	CSysParam* m_pParam;

	HTREEITEM pItemGeneral;
	HTREEITEM pItemColor  ;
	HTREEITEM pItemWork   ;
	HTREEITEM pItemBackup ;
	HTREEITEM pItemMove   ;
	HTREEITEM pItemPlug   ;
	HTREEITEM pItemLang   ;
	HTREEITEM pItemUser   ;

	CDlgGeneral    m_dlgGeneral;
	CDlgColor      m_dlgColor;
	CDlgWorkSpace  m_dlgWork;
	CDlgBackup     m_dlgBackup;
	CDlgMoveRotate m_dlgMove;
//	CDlgPlug       m_dlgPlug; 
	CDlgLanguage   m_dlgLang;
	CDlgUser       m_dlgUser; 
	
// Dialog Data
	//{{AFX_DATA(CDlgSystemParam)
	enum { IDD = IDD_DIALOG_SYSTEMPARAM };
	CTreeCtrl	m_treeSys;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSystemParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSystemParam)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedTreeParam(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSYSTEMPARAM_H__630C8BB7_FDDA_4177_9562_DA418873131B__INCLUDED_)
