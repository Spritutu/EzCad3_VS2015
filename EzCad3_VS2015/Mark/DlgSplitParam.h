/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CDlgSplitParam.h
* 文件标识：
* 摘要：  
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/

#pragma once


// CDlgSplitParam 对话框

class CDlgSplitParam : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSplitParam)

public:
	CDlgSplitParam(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSplitParam();
	BOOL  m_bHideX;
	BOOL  m_bHideY;
	BOOL  m_bShowDisableA;


	int  m_nSplitModeX;
	double m_dSplitSizeX;

	int  m_nSplitModeY;
	double m_dSplitSizeY;
	int m_nSplitAttrib;

	BOOL m_bKeepEntOrder;
 
	BOOL m_bCylinderWrap;
	BOOL m_bSphereWrap;
	BOOL m_bRevolveWrap;
	BOOL m_bSplitByGLB;
	BOOL  m_bDisableAxisA;


	CComboBox	m_comboModeX;
	CComboBox	m_comboModeY;

	BOOL m_bNoCutEntity;
	BOOL m_bShowCylinderWrap;

	BOOL m_bShowSphereWrap;

	BOOL m_bUseSplitCenAsMarkingCen;
	void UpdataModeX();
	void UpdataModeY();

	BOOL m_bEnableA;
	BOOL m_bMark360;
	int  m_nMarkCount;
	double  m_dMarkAngle;

	void UpdateWrapType();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SPLITPARAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public: 
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheckKeeporder();
	afx_msg void OnCbnSelchangeComboMode();
	afx_msg void OnCbnSelchangeComboModeY();
	afx_msg void OnBnClickedCheckRevolvewarp();
	afx_msg void OnBnClickedCheckSpherewarp();
	afx_msg void OnBnClickedCheckCylinderwarp(); 
	afx_msg void OnBnClickedButtonCount();
	afx_msg void OnBnClickedButtonAngle();
	afx_msg void OnBnClickedCheck360();
	afx_msg void OnBnClickedCheckDisableaxisa();
};
