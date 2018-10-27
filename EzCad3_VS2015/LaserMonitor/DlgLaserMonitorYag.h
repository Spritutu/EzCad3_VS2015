#pragma once
#include "QLamp.h"

// CDlgLaserMonitorYag 对话框

class CDlgLaserMonitorYag : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLaserMonitorYag)

public:
	CDlgLaserMonitorYag(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLaserMonitorYag();

	void UpdateState(BOOL& bOK );

	CQLamp m_lamp1;

	BOOL m_bReady;

	void SetErrorStr(CString str);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LASER_FIBER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public: 
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPw();
};
