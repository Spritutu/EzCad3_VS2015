/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： QEntView.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/
#pragma once
 
 
#include "EntOpenGLWnd.h" 
#include "EntShowWnd.h"


class GLOABL_EXT_CLASS CQEntView : public CView, public CEntShowWnd 
{
public:
	CQEntView();
	//protected:
	virtual ~CQEntView();
protected:
	           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CQEntView)
	 
     
protected:
	 
	 
// Operations
public:	
	BOOL m_bOnRButtonDownHandle;
	void SetEntMgr(PEntMgr pEntMgr);
	void SetCmdMgr(PCmdMgr pCmdMgr);
 
	void SetShowOpenGLWnd(BOOL b);   

	void OnActivateLayer(PEntity pCurLayer);

	virtual PEntity  GetSafeLayer(); 

	//继承CEntOpenGLWnd的GetCurShowLayer
	virtual PEntity GetCurShowLayer();

// Operations
public:	

 	void DrawAll(PDrawDC pDrawDC, BOOL bReDrawBack, BOOL bShowFront, BOOL bShowNodeAndGuildline);

	//数据或者视图区域位置发生改变，需要重新绘制背景
	virtual void OnEntityOrViewPosHaveChange(WPARAM wParam=0);

		//放大一倍观察
	virtual void ZoomIn();

	//缩小一倍观察
	virtual void ZoomOut();

	virtual void ZoomBox(Box2d box);

	virtual void ZoomPan(Pt2d ptMove);

	virtual void ZoomOpenGL(int n);
	virtual void ZoomAllOpenGL(Box3d box);

	BOOL GetPickVertex(int x,int y,Pt3df& ptPicked,Pt3df& ptPickedViewFrame);
public:
	 
	virtual void    SetMouseLogPt(double dLogX,double dLogY){}; //设置当前鼠标的逻辑位置 
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQEntView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CQEntView)		
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
 

	LRESULT OnViewPortChanged(WPARAM wParam, LPARAM lParam);
	LRESULT OnCreateGuildLine(WPARAM wParam, LPARAM lParam);
	LRESULT OnUpdateCameraFrame(WPARAM wParam, LPARAM lParam);

	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
public:
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags); 
};
 