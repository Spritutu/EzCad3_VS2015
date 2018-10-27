#pragma once
 
#include "QOpenGlWnd.h"

class GLOABL_EXT_CLASS CEntOpenGLWnd :	public QOpenGlWnd
{
public:
	 
	BOOL m_bHideMesh;//是否隐藏曲面
	  
	void DrawEntNode(PEntity pEntNodePick );

	void DrawInfo( CDC* pDC);
	void DrawPickFrame(CDC* pDC, Box3d& box3d);
	void DrawLine3d(CDC* pDC, Pt3d pt1, Pt3d pt2, CMatrix3d& mtxPrj);

	virtual PEntity GetCurShowLayer();
	virtual PPenBox GetPenbox();

	//重新绘制所有对象
	virtual void glDrawAllObject(WORD wDrawFlag = 0);
	

	//绘制所有，bReDrawBack是否重新绘制背景对象
	virtual void glDrawAll(CDC* pDC, BOOL bReDrawBack = TRUE);

	CEntOpenGLWnd(void);
	~CEntOpenGLWnd(void); 
};


class CEntity;
class GLOABL_EXT_CLASS CShowEntOpenGLWnd : public CWnd, public QOpenGlWnd
{

private:
	// OpenGL-specific
	HGLRC m_hListRC;        // OpenGL 的渲染环境	

	unsigned int m_nListOpenGL;
	BOOL m_bListDone;

	CEntity* m_pShowEnt;
	BOOL m_bCaptureCursor;
	int m_nCurState;
public:
	CEntity*  GetShowEnt();
	void SetShowEnt(CEntity* pEnt);
	BOOL   IsCaptureCursor()const { return m_bCaptureCursor; };

	void    SetListDone(BOOL b);
	void	BuiltList();
	int GetCurState() 
	{
		return m_nCurState;
	}
	void CaptureCursor();
	void ReleaseCursor();
	//重新绘制所有对象
	virtual void glDrawAllObject(WORD wDrawFlag = 0);

	CShowEntOpenGLWnd();
	~CShowEntOpenGLWnd();
	DECLARE_DYNCREATE(CShowEntOpenGLWnd)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	afx_msg void OnPaint();
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

