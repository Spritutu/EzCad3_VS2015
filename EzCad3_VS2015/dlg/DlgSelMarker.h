#pragma once


// CDlgSelMarker 对话框

class CDlgSelMarker : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSelMarker)

public:
	int m_nSelIndex;
	PMarker m_markerBuf[8];

	CListBox m_listboxMarker;
	CDlgSelMarker(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSelMarker();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SELMARKER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeListMarker();
	afx_msg void OnLbnDblclkListMarker();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
