/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CDlgLayerParam.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/

#pragma once


// CDlgLayerParam 对话框

class CDlgLayerParam : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLayerParam)

public:
	CDlgLayerParam(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLayerParam();

	CString m_strName;
	int m_nCount;

	int m_nStartDelayMs;
	int m_nEndDelayMs;
	BOOL m_bWaitForInput;
	WORD   m_wIoHigh;//输入IO条件为高的位
	WORD   m_wIoLow;//输入IO条件为低的位

	WORD   m_wStartOutputIoHigh;//开始输出IO条件为高的位
	WORD   m_wStartOutputIoLow;//开始输出IO条件为低的位
	WORD   m_wFinishOutputIoHigh;//开始输出IO条件为高的位
	WORD   m_wFinishOutputIoLow;//开始输出IO条件为低的位


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LAYERPARAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
