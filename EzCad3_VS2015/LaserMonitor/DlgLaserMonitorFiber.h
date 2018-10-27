#pragma once
#include "QLamp.h"

// CDlgLaserMonitorFiber 对话框

class CDlgLaserMonitorFiber : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLaserMonitorFiber)

public:
	CDlgLaserMonitorFiber(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLaserMonitorFiber();

	void UpdateState(BOOL& bOK );

	CQLamp m_lamp1;
	CQLamp m_lamp2;
	CQLamp m_lamp3;
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
