/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CEzcad3View.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/

// Ezcad3View.h : CEzcad3View 类的接口
// 
#pragma once

#include "QTabView.h"
#include "QEntView.h"
#include "EzCad3Doc.h"
#include "QEntLayerView.h"

class CEzcad3View : public CQTabView
{
protected: // 仅从序列化创建
	CEzcad3View();
	DECLARE_DYNCREATE(CEzcad3View)

// 属性
public:
	CEzcad3Doc* GetDocument() const;

// 操作
public:
	BOOL IsScrollBar () const
	{
		return TRUE;
	}

	CQEntLayerView* m_pLayerViewStartChange;
	PEntity GetActiveLayer();

	virtual void OnActivateView (CView* /*pView*/);
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CEzcad3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	virtual LRESULT OnUserChangeCurLayer(WPARAM wParam, LPARAM lParam);	
	virtual LRESULT OnUserChangeEntity(WPARAM wParam, LPARAM lParam);	
	virtual LRESULT OnUserDBClickTab(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMoveTab(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnChangeActiveTab(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnChangingActiveTab(WPARAM wp, LPARAM lp);
	 
	
protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};


CEzcad3View* gf_GetCurEzcad3View();

#ifndef _DEBUG  // Ezcad3View.cpp 中的调试版本
inline CEzcad3Doc* CEzcad3View::GetDocument() const
   { return reinterpret_cast<CEzcad3Doc*>(m_pDocument); }
#endif

