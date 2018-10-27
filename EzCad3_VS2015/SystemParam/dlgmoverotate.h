/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CDlgMoveRotate.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/
#if !defined(AFX_DLGMOVEROTATE_H__5DD53934_21B0_421B_BC2E_33AFA21662A3__INCLUDED_)
#define AFX_DLGMOVEROTATE_H__5DD53934_21B0_421B_BC2E_33AFA21662A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgmoverotate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMoveRotate dialog
#include "sysparam.h"
#include "..\resource.h"

class CDlgMoveRotate : public CDialog
{
// Construction
public:
	CDlgMoveRotate(CWnd* pParent = NULL);   // standard constructor
	void OK();
CSysParam* m_pParam;
// Dialog Data
	//{{AFX_DATA(CDlgMoveRotate)
	enum { IDD = IDD_DIALOG_SYS_MOVEROTATE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMoveRotate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMoveRotate)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMOVEROTATE_H__5DD53934_21B0_421B_BC2E_33AFA21662A3__INCLUDED_)
