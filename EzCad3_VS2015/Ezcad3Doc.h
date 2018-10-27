/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CEzcad3Doc.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/

// Ezcad3Doc.h : CEzcad3Doc 类的接口
//


#pragma once


class CEzcad3Doc : public CDocument
{
protected: // 仅从序列化创建
	CEzcad3Doc();
	DECLARE_DYNCREATE(CEzcad3Doc)

// 属性
public:
	int     m_nExportMode;
	CString m_strAuthor;
	CString m_strDate;
	CString m_strComment;

	CString m_strOpenFileName;
	CString m_strSaveFileName;
// 操作
public:
	 
// 重写
public:
	 virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName); 

	virtual void Serialize(CArchive& ar);
	 
	virtual BOOL SaveModified();
// 实现
public:
	virtual ~CEzcad3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};


