#pragma once

#include "..\resource.h"
// CDlgSelUser 对话框

class CDlgSelUser : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSelUser)

public:
	CDlgSelUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSelUser();

	CComboBox m_comboUser;
// 对话框数据
	enum { IDD = IDD_DIALOG_SELUSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
