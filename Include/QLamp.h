/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： QLamp.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/

#ifndef QLAMP_H
#define QLAMP_H
#include "QStaticBmp.h"

#define LAMP_GRAY   0 
#define LAMP_GREEN  1
#define LAMP_RED    2
 
class GLOABL_EXT_CLASS  CQLamp : public CQStaticBmp
{
public:
	CQLamp();
	~CQLamp();
	BOOL m_bFlash;
	UINT_PTR  m_nTimeID;
	int  m_nLastState;
	int  m_nFlashState;

	void Red();	
	void Green();	
	void Off();
	void SetFlash(BOOL bFlash,int nFlashClr);

	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQLamp)
	//}}AFX_VIRTUAL
	
	// Implementation
public:

	
	// Generated message map functions
protected:
	//{{AFX_MSG(CQLamp)
	afx_msg void OnTimer(UINT_PTR nIDEvent);
		afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif