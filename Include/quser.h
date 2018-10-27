/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： QUser.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2016年3月
* 版本纪录: 创建文件
*/


#pragma once
#include "QIniFile.h"

class GLOABL_EXT_CLASS QUser
{
public:
	CString m_strName;
	CString m_strPsw;
	BOOL m_bEnableSave;//使能保存
	BOOL m_bEnableDraw;//使能绘制
	BOOL m_bEnablePickMove;//使能选取移动
	BOOL m_bEnableEditEntParam;//使能编辑对象参数
	BOOL m_bEnableModifySysParam;//修改系统参数
	BOOL m_bEnablePenParam;//使能修笔参数
	BOOL m_bEnableDevParam;//使能设备参数 
	BOOL m_bEnableMark;//使能标刻

	QUser();
	BOOL IsAdmin();
	void CopyData(QUser* pUser);
	void SaveParam(CQIniFile& qini,CString strKey);
	void LoadParam(CQIniFile& qini,CString strKey);
};

class GLOABL_EXT_CLASS QUserMgr
{
private:
	CArray<QUser*,QUser*> m_pArrarUser;
	QUser* m_pCurUser;
public:
	void Reset();
	void Clear();
	QUserMgr();
	~QUserMgr();
	int Count();
	void SetCurUser(QUser* pUser);
	QUser* GetCurUser();

	QUser* GetUser(int i);
	QUser* FindUser(CString strName);
	void AddUser(QUser* pUser);
	QUser* RemoveUser(int i);
	int SaveParam(CString strFile );
	int LoadParam(CString strFile );
};


GLOABL_EXT_CLASS  QUserMgr* gf_GetUserMgr();
GLOABL_EXT_CLASS void gf_SetUserMgr(QUserMgr* pMgr);
GLOABL_EXT_CLASS int  gf_ReadUserParamFile();
GLOABL_EXT_CLASS  int  gf_SaveUserParamFile(); 