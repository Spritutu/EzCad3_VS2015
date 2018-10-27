#pragma once

#include "QUser.h"
// CDlgUserParam 对话框

class CDlgUserParam : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgUserParam)

public:
	QUser* m_pUser; 
	BOOL m_bDisableName;
	CDlgUserParam(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgUserParam();

// 对话框数据
	enum { IDD = IDD_DIALOG_USERPARAM };
	virtual void OnOK();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
