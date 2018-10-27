/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： QOpenGlWnd.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2016年3月
* 版本纪录: 创建文件
*/
#pragma once
 
 
#include "Matrix3d.h"
#include "pt3d.h"
#include "Box3d.h"

class CSegMFCToolBar : public CMFCToolBar
{
	DECLARE_DYNAMIC(CSegMFCToolBar)

public:
	CSegMFCToolBar();
	virtual ~CSegMFCToolBar();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
public:
	void SetIsDlgControl(BOOL b);
};

enum GlRenderMode
{
	Wire,
	Fill,
    FillLines
};
class GLOABL_EXT_CLASS QOpenGlWnd  
{
public:
	CPoint m_ptOpenGLBase;
	CPoint m_ptOpenGLLast;
	//BOOL m_bWireFrame;      //显示线框

	GlRenderMode m_modeRender;
protected: 
	 
	 
	 
	CDC* m_pViewDC;  
	HGLRC m_hViewRC;        // OpenGL 的渲染环境	

	 
	Pt3d m_ptEye;  // 眼睛的位置
	Pt3d m_ptCenter;  // 观察中心
	Pt3d m_ptUp;  // 观察的正向
	double m_dScale;  // 缩放比例

	Pt3d m_ptSaveEye;  // 眼睛的位置
	Pt3d m_ptSaveCenter;  // 观察中心
	Pt3d m_ptSaveUp;  // 观察的正向

	double m_dRange[2];  // 视口显示范围
	int    m_nWidth;  // 窗口宽	
	int	   m_nHeight;  // 窗口高	
		 

	COLORREF m_clrPickBox;

protected:
	 
	HBITMAP m_hOldBmp;
	HBITMAP m_hBmpDIB;

	int    m_nBmpWidth;  // 窗口宽	
	int	   m_nBmpHeight;  // 窗口高
public:
 
	BOOL CreateOpenglDib(int w, int h);

	void SetRenderMode(GlRenderMode mode);
	GlRenderMode GetRenderMode() { return m_modeRender; }
protected:
 
	void DrawLine(CDC *pDC, CPoint base, CPoint point, COLORREF nColor, int nPenWidth);
	void DrawBox(CDC *pDC, CPoint base, CPoint point, COLORREF nColor);
	void DrawDragRectXOR(CDC *pDC, CPoint base, CPoint point);
	void DrawPoint(CDC *pDC, CPoint point, COLORREF nColor, int nPenWidth);
	// Construction
public:
	QOpenGlWnd();

	virtual ~QOpenGlWnd();
	CDC* GetViewDC(){return m_pViewDC;	}
	HGLRC GetViewRC() { return m_hViewRC; }
 

	int GetWndWidth() { return m_nWidth; }
	int GetWndHeight() { return m_nHeight; }

	Pt3d GetEyePt() { return m_ptEye; }
	Pt3d GetCenterPt() { return m_ptCenter; }
	Pt3d GetUpPt() { return m_ptUp; }
	 

	void SetOpenGLScale(double dScale);
	double GetOpenGLScale() { return m_dScale; }
	void DestroyAllOpenGl();
	void SaveCurViewPos();
	void LoadSaveViewPos();
	Pt3d GetOpenGLCenter();

	virtual  void SetLight();
	virtual  void SetMaterial();

 	void OpenGLUpdateSize(int cx, int cy);
	//初始化渲染环境
	void SetupRender();
	//设置投影矩阵
	void SetupProjectMatrix();


	CMatrix3d GetProjectMatrix();
	void GetTransMatrix(float fMatrix[4][4]);

	CPoint GetScreenCoor(Pt3d ptReal);
	Pt3d   GetRealCoor(CPoint ptScreen);

	BOOL Normalize(double pt[3]);
	void VProduct(double vec[3], double Vec[3], double rtvec[3]);
	 
	//根据屏幕点坐标得到移动的3维向量
	Pt3d GetMoveDistFromScreenXY(CPoint ptBase, CPoint point);

	void OnViewTop();
	void OnViewFront();
	void OnViewLeft();
	void OnViewRight();
	void OnViewIso();
	void OnViewBottom();
	void OnViewBack();
	void ZoomOpenGL(int n);

	void ZoomWnd(CPoint point1, CPoint point2);
	void ZoomIn();
	void ZoomOut();
	void ZoomUp(Pt3d ptCen);
	void ZoomAll(Box3d box);


	//更改视图到新的基准点 nState=0 平移 nState=1 旋转
	void OnChangeViewPos(UINT nFlags, CPoint point, int nState);
public:
	virtual void DrawStart();
	virtual void DrawEnd();
public:
	virtual void glDrawWorkPlane();

	//重新绘制所有对象
	virtual void glDrawAllObject(WORD wDrawFlag=0) {};
	//绘制所有，bReDrawBack是否重新绘制背景对象
	virtual void glDrawAll(CDC* pDC, BOOL bReDrawBack = TRUE);
	 
};
 