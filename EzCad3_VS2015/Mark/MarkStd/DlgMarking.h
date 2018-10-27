/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CDlgMarking.h
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
#include "Matrix2d.h"

// CDlgMarking 对话框

class CDlgMarking : public CDialog
{
	DECLARE_DYNAMIC(CDlgMarking)

public:
	CDlgMarking(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMarking();

// 对话框数据
	enum { IDD = IDD_DIALOG_MARKING };
	CQPngButton m_buttonStop;

	CWnd*  m_pDlgMark;
	HANDLE m_hThreadMark;
	BOOL   m_bThreadExitFlag;
	int    m_nMarkReturnErr;

	BOOL     m_bRedLight;
	BOOL     m_bRedLightMoveState;
	void TranformEnt();

	BOOL     m_bMarkSelected;	
	BOOL     m_bContinues;
	BOOL     m_bMarkLayer;
	BOOL     m_bCalcTimeMode;
	BOOL     m_bOffLine;


	int m_nFileCount;
	 int m_nStartPartCount;

	PEntity m_pEntParent; 
	PMarker m_pMarker;
	CBitmap* m_pCurBmp;

	BOOL m_bEnableLight; 
	CMatrix2d m_mtxChangeEnt;
	int m_nChangeTranType;
	void ShowInfo(CString str);
	void ShowInfo2(CString str);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	LRESULT  OnMotorMove(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnDestroy();	
	afx_msg void OnClose();
};

