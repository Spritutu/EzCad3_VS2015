#if !defined(AFX_DLGMARKADVANCE_H__B746921F_649F_4F16_9239_4FB5D5F8B8DD__INCLUDED_)
#define AFX_DLGMARKADVANCE_H__B746921F_649F_4F16_9239_4FB5D5F8B8DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgmarkadvance.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMarkAdvance dialog

class CDlgMarkAdvance : public CDialog
{
// Construction
public:
	CDlgMarkAdvance(CWnd* pParent = NULL);   // standard constructor

	double m_dJumpSpeed;
	int    m_nJumpPosTC;
	int    m_nJumpDistTC;

	double m_dEndComp;
	double m_dAccDist;
	double m_dPointTime; 
		

	BOOL   m_bPulsePointMode;
	int    m_nPulseNum;

	BOOL   m_bYagOptimizeMode;
	BOOL   m_bYagOptimizeInterlace;

	BOOL   m_bWobble;
	double m_dWobbleDiameter;
	double m_dWobbleDist;

	//Ä©Î²¼Óµã
	BOOL   m_bEndAddPt;
	int    m_nEndPointNum;
	double   m_dEndPointDist;
	double  m_dEndPointTime;
	int    m_nEndPointCyc;

// Dialog Data
	//{{AFX_DATA(CDlgMarkAdvance)
	enum { IDD = IDD_DIALOG_MARKADVANCE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMarkAdvance)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMarkAdvance)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnCheckPulse();
	afx_msg void OnCheckOptim();
	
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMARKADVANCE_H__B746921F_649F_4F16_9239_4FB5D5F8B8DD__INCLUDED_)
