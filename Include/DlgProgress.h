#pragma once

#include "..\resource.h"

class CDlgProgress;
class GLOABL_EXT_CLASS ProgressParam
{
public:

	CString m_strTitle;
	CString m_strInfo;
	BOOL m_bEnableCancel;
	BOOL m_bShowTime;
	BOOL m_bShowCount;//显示计数值
	int m_nCount;
	int m_nRatio;
	CDlgProgress* m_pDlg;

	ProgressParam()
	{
		m_bShowTime = TRUE;
		m_bEnableCancel=FALSE;
		m_bShowCount=FALSE;//显示计数值
		m_nCount=0;
		m_nRatio = 0;
		m_pDlg = NULL;
	}
};

// CDlgProgress 对话框

class GLOABL_EXT_CLASS CDlgProgress : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgProgress)

public:
	CDlgProgress(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgProgress();

// 对话框数据
	enum { IDD = IDD_DIALOG_PROGRESS };
 
	ProgressParam* m_pParam;

	BOOL m_bCancel;
	BOOL m_bQuit;

	int m_nStartTickCount;
	int m_nLastTickCount;
	CString m_strLastInfo;

	void UpdateShowInfo();
	void SetInfo(CString strInfo,int nProgressRatio);

	void CancelQuit();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
		afx_msg void OnTimer(UINT_PTR nIDEvent); 
	afx_msg void OnDestroy();
	CProgressCtrl m_ctrlProgress;
};

GLOABL_EXT_CLASS HANDLE gf_CreatProgressDlg(ProgressParam* pParam);
GLOABL_EXT_CLASS BOOL gf_SetProgressDlgInfo(ProgressParam* pParam );
GLOABL_EXT_CLASS void gf_DestroyProgressDlg(HANDLE hThread, ProgressParam* pParam);