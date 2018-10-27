/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： EzCad3_VS2015.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/

// EzCad3_VS2015.h : EzCad3_VS2015 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号

#define ENABLE_CMD

// CEzCad3_VS2015App:
// 有关此类的实现，请参阅 EzCad3_VS2015.cpp
//
class CQSingleDocTemplate : public CSingleDocTemplate
{
public:
	CQSingleDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
		CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass);

	void ChangeDocStr();
};

class CEzCad3_VS2015App : public CWinAppEx
{
public:
	CEzCad3_VS2015App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	void   InititalQKernal();
	void   CloseQKernal();

	BOOL ShowAgreeLicence();

	void SetEz3DocToReg();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();
	afx_msg void OnFileOpen();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEzCad3_VS2015App theApp;
