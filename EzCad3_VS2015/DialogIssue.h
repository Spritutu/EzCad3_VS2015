#pragma once


// CDialogIssue 对话框

class CDialogIssue : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogIssue)

public:
	CDialogIssue(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogIssue();

	int m_nMarkerId;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ISSUE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSavetofile();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonEmail();
};
