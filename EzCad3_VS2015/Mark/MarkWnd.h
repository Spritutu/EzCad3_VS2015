/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CMarkWnd.h
* 文件标识：
* 摘要： 
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/

#pragma once

#include "MarkStd\\DlgMark.h"
 
class CMarkWnd : public CDockablePane
{
// 构造
public:
	CMarkWnd();

	void AdjustLayout();

 
	CDlgMark m_dlgMark;
 

	PMarker GetMarker();

	int GetMinShowWidth();
// 属性
public:
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
// 实现
public:
	virtual ~CMarkWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);	

	DECLARE_MESSAGE_MAP()
	
};

