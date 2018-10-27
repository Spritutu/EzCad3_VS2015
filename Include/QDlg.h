/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： QDlg.h
* 文件标识：
* 摘要： 
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/


#pragma once
 
 

GLOABL_EXT_CLASS int gf_DlgInputOne(CWnd* pParent,CString& strText,CString strTitle,CString strPrompt=_T(""),CString strUnit=_T(""));

GLOABL_EXT_CLASS int gf_DlgYesNo(CString strTitle, CString strPrompt,BOOL bHideCancel=FALSE);
GLOABL_EXT_CLASS int gf_DlgYesNo2(CString strTitle, CString strPrompt, BOOL bHideCancel, CString strCamcel);
GLOABL_EXT_CLASS int gf_DlgImportBmp(CString& strFileName);

GLOABL_EXT_CLASS int gf_DlgImportVector(CString& strFileName);

GLOABL_EXT_CLASS int gf_DlgProjectEnt(int& nProjectMode, BOOL& bDownProject, BOOL& bRemoveNoInter, BOOL& bCylinderX, double& dLimetZ, double& dCylinderDiameter, double& m_dAlignOffset);

GLOABL_EXT_CLASS int gf_DlgPenParamLib(CWnd* pParent, PMarkParam pPenParam, PMarker pMarker , CString& strPenName);
GLOABL_EXT_CLASS int gf_DlgPenAdvance(PMarker pMarker);

GLOABL_EXT_CLASS int gf_DlgShowIoState(int nIoState);

GLOABL_EXT_CLASS int gf_DlgOnFileProjectParam(PMarker pMarker);