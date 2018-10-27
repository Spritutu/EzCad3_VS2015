/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CEntShowWnd.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/
#pragma once

#include "QRuler.h"
#include "EntOpenGLWnd.h"

const int STATE_NORMAL = 0;
const int STATE_PAN = 1;
const int STATE_ROTATE = 2;

class GLOABL_EXT_CLASS CEntShowWnd : public CEntOpenGLWnd
{
public:
	CEntShowWnd();
	virtual ~CEntShowWnd();
protected:
 	CWnd*    m_pDrawWnd;
	PDrawDC m_pDrawDC;
	PEntMgr m_pEntMgr;
	PCmdMgr m_pCmdMgr;

	int m_nCurState;
	Pt2d   m_ptBase;
	BOOL m_bInitView;

protected:
	BOOL m_bShowOpenGLWnd;
public:
	int GetCurState() { return m_nCurState; }
	BOOL IsShowOpenGLWnd();
	void SetShowOpenGLWnd(BOOL b);

	BOOL IsShowOpenGLWire();
	BOOL IsHideMesh();

	//void SetShowOpenGLWire(BOOL b);
	void SetRenderMode(GlRenderMode mode);
	void HideMesh(BOOL b);
protected:
	BOOL     m_bShowRuler;
	CQRuler* m_pRulerH;
	CQRuler* m_pRulerV;
	 
	// Operations
public:
	void SetEntMgr(PEntMgr pEntMgr);
	void SetCmdMgr(PCmdMgr pCmdMgr);

	virtual PEntMgr GetEntMgr() { return m_pEntMgr; }

	PCmdMgr  GetCmdMgr()
	{
		return m_pCmdMgr;
	}
	 
	int OnCreateWnd(CWnd* pWnd);

	BOOL    IsShowRuler()const { return m_bShowRuler; };
	void    ShowRuler();
	void    HideRuler();
	void   ShowRuler(BOOL b);
	// Operations
public:

	PDrawDC    GetDrawDC()const { return m_pDrawDC; };

	virtual PEntity GetCurShowLayer()  ;

	virtual void DrawAll(PDrawDC pDrawDC, BOOL bReDrawBack, BOOL bShowFront,BOOL bShowNodeAndGuildline);

	//数据或者视图区域位置发生改变，需要重新绘制背景
	virtual void OnEntityOrViewPosHaveChange(WPARAM wParam = 0);

	//放大一倍观察
	virtual void ZoomIn();

	//缩小一倍观察
	virtual void ZoomOut();

	virtual void ZoomBox(Box2d box);

	virtual void ZoomPan(Pt2d ptMove);

public:
	virtual void    SetScrollBarRange(); //设置当前滚动条的范围

	virtual void    SetScrollBarMinMaxRange(int nBar, double dMinPos, double dMaxPos, BOOL bRedraw = TRUE); //设置当前滚动条的范围
	virtual void    SetCurScrollBarPos(int nBar, double dPos, BOOL bRedraw = TRUE);
	virtual void    SetScrollBarPos(double x, double y);//设置当前滚动条的位置
	virtual void    SetMouseLogPt(double dLogX, double dLogY) {}; //设置当前鼠标的逻辑位置 
 
protected:
	 
	void OnDraw(CDC* pDC);
	void OnWindowPosChanged( );
	void OnSize(UINT nType, int cx, int cy);
	void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	BOOL OnMouseMove(UINT nFlags, CPoint point);
	BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	BOOL OnMButtonDown(UINT nFlags, CPoint point);
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	BOOL OnMButtonUp(UINT nFlags, CPoint point);
	BOOL OnEraseBkgnd(CDC* pDC);
	BOOL OnLButtonDown(UINT nFlags, CPoint point);
	BOOL OnLButtonUp(UINT nFlags, CPoint point);
	BOOL OnRButtonDown(UINT nFlags, CPoint point);
	BOOL OnRButtonUp(UINT nFlags, CPoint point);
	BOOL OnLButtonDblClk(UINT nFlags, CPoint point);
	BOOL OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	LRESULT OnViewPortChanged(WPARAM wParam, LPARAM lParam);
	LRESULT OnCreateGuildLine(WPARAM wParam, LPARAM lParam);
};
