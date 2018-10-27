/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CDlgMotionPanel.h
* 文件标识：
* 摘要： 
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/

#pragma once

#include "QPngButton.h"
// CDlgMotionPanel 对话框
 

class CDlgMotionPanel : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMotionPanel)

public:
	CDlgMotionPanel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMotionPanel();
 

	BOOL m_bHideFocusPos;
	BOOL m_bHideOrigin;
	BOOL m_bEnableAutoFocus;

	CQPngButton m_buttonUp;
	CQPngButton m_buttonDown;
	CQPngButton m_buttonUpZ;
	CQPngButton m_buttonDownZ;
	CQPngButton m_buttonLeft;
	CQPngButton m_buttonRight;
	CQPngButton m_buttonWrap;
	CQPngButton m_buttonAutoFocus;
	CQPngButton m_buttonPreviewSplitBox;

	CQPngButton m_buttonACCW;
	CQPngButton m_buttonACW;

	void UpdateParam( );

	void ShowFocus();
	void ShowCurCoor();
	void ShowPartHeight();
	void ShowPartDiameter();

	void MoveX(double x);
	void MoveY(double y);
	void MoveZ(double z);
	void MoveA(double a);

	void OnPageUp();
	void OnPageDown();

	void OnKeyUp();
	void OnKeyDown();
	void OnKeyLeft();
	void OnKeyRight();

	void ShowOrigin();
	void Home();

	void ShowSplitParam();

	BOOL IsHideX(PMarker pMarker, BOOL bDisableAxisA);
	BOOL IsHideY(PMarker pMarker, BOOL bDisableAxisA);


	

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MOTIONPANEL
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel(); 
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPartheight();
	afx_msg void OnBnClickedButtonFocus();
	afx_msg void OnBnClickedButtonHome();
	afx_msg void OnBnClickedButtonSplitparam();
	afx_msg void OnBnClickedButtonDownz();
	afx_msg void OnBnClickedButtonUpz();
	afx_msg void OnBnClickedButtonGoorg();
	afx_msg void OnBnClickedButtonOrg();
	afx_msg void OnBnClickedButtonACCW();
	afx_msg void OnBnClickedButtonACW();
	virtual LRESULT OnUserChangeCurLayer(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonPartdiameter();
	afx_msg void OnBnClickedButtonHandwheel();
	afx_msg void OnBnClickedButtonPreview();
	afx_msg void OnBnClickedButtonAutofocus();
	afx_msg void OnBnClickedButtonPreview2();
};
