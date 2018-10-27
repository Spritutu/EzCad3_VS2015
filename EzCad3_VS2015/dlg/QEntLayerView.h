
#pragma once


//
#include "QEntView.h"

/////////////////////////////////////////////////////////////////////////////
// CView1 view

class CQEntLayerView : public CQEntView
{
public:
	CQEntLayerView();           // protected constructor used by dynamic creation
protected:
	BOOL m_bMouseWheelInv;
	DECLARE_DYNCREATE(CQEntLayerView)

	PEntity m_pEntLayer;
	int m_nStartZoomWheelTick;
// Attributes
public:
	
// Operations
public:
	virtual PEntity GetLayer(){return m_pEntLayer;};
	void SetLayer(PEntity pEnt);
	
	virtual PEntity GetSafeLayer();

	void OnActivate();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CView1)
	public:
	virtual void OnInitialUpdate();
	virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	
// Implementation
protected:
	virtual ~CQEntLayerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CView1)
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};