#pragma once

#include "QLamp.h"
// DlgLaserMonitorQcw 对话框

class DlgLaserMonitorQcw : public CDialogEx
{
	DECLARE_DYNAMIC(DlgLaserMonitorQcw)

public:
	DlgLaserMonitorQcw(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgLaserMonitorQcw();

	CQLamp m_lamp1;
	void SetErrorStr(CString str);
	void UpdateState(BOOL& bOK);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LASER_SPI };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonReset();
};
