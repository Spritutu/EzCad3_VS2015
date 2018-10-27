/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CQRuler.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2016年3月
* 版本纪录: 创建文件
*/

#ifndef QRULER_H
#define QRULER_H

/////////////////////////////////////////////////////////////////////////////
// CQRuler window

const int RULERTYPE_TOP    = 0;
const int RULERTYPE_BOTTOM = 1;
const int RULERTYPE_LEFT   = 2;
const int RULERTYPE_RIGHT  = 3;


const int RULERATTR_HIDEHEAD  = 0x0001;//隐藏头
const int RULERATTR_HIDETAIL  = 0x0002;//隐藏尾

//const int RULER_PIXEL_SIZE         = 20 ;   //标尺尺寸(象素)            
//const int RULER_PIXEL_GRADUATION_10= 12 ;   //十等分刻度长度(象素)
//const int RULER_PIXEL_GRADUATION_5 = 10 ;   //五等分刻度长度(象素)
//const int RULER_PIXEL_GRADUATION_1 = 7  ;   //1等分刻度长度(象素)
const int RULER_PIXEL_MIN_DIST_10        = 40 ;   //十等分主刻度最小距离(象素)

  

class GLOABL_EXT_CLASS CQRuler : public CWnd
{
// Construction
public:
	CQRuler();

// Attributes
public:
	int      m_nRulerType        ;//标尺的类型 
	int      m_nRulerAttrib      ;//标尺的属性

	COLORREF m_clrRulerBK        ;//标尺背景颜色
	COLORREF m_clrRulerBox       ;//标尺边框颜色
	COLORREF m_clrRulerGraduation;//标尺刻度颜色
	COLORREF m_clrRulerCursor    ;//标尺光标颜色

	int   m_nPixWndSize          ;//标尺的象素尺寸

	double m_dLogStart            ;//标尺的逻辑开始坐标
    double m_dLogEnd              ;//标尺的逻辑结束坐标 
    double m_dLogSize             ;//标尺的逻辑坐标范围 = m_dLogEnd - m_dLogStart

	double m_dGraduationNum10     ;//标尺的十等分刻度个数
    double m_dGraduationNum5      ;//标尺的五等分刻度个数

	double m_dLogGraduationSize10 ;//标尺的十等分刻度逻辑尺寸
	
    double m_dPixGraduationSize10 ;//标尺的十等分刻度象素距离
	double m_dPixGraduationSize   ;//标尺的分刻度象素距离

	
    double m_dLogGraduationStart  ;//计算标尺第一主刻度起始逻辑位置
	double m_dPixMainGradOffset   ;//标尺第一个十等分刻度偏移的象素距离

	double m_dLastPos;            


	BOOL   m_bMouseMove;
	BOOL   m_bCapture;
// Operations
public:
	BOOL CreateRuler(int rulerType, CWnd* pParentWnd, UINT nID);

	int  GetRulerType()const{return m_nRulerType;}
	void SetRulerType(int rulerType)
    {
        m_nRulerType   = rulerType;
    }

	int  GetRulerAttrib()const{return m_nRulerAttrib;}
	void SetRulerAttrib(int rulerAttrib)
	{
		m_nRulerAttrib = rulerAttrib;
	}

	void SetRulerRange(double fStart,double fEnd,BOOL bRedraw);//设置标尺的逻辑范围
	void SetRulerPos(double pos);//设置光标位置

	void ReCalcRulerParam();//计算标尺的所有参数

	void DrawTicker(CDC* pDC, CRect rulerRect);

    void DrawCursorPos(double pos);


	void OnParentPosChanged();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQRuler)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CQRuler();

	// Generated message map functions
protected:
	//{{AFX_MSG(CQRuler)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif