#pragma once
 
	
 

/////////////////////////////////////////////////////////////////////////////
// CDlgLayerParam dialog
#include "..\resource.h"
#include "EntLayer.h"
class CDlgLayerParam : public CDialog
{
// Construction
public:
	CDlgLayerParam(CWnd* pParent = NULL);   // standard constructor
	CEntLayer* m_pLayer;

// Dialog Data
	//{{AFX_DATA(CDlgLayerParam)
	enum { IDD = IDD_DIALOG_LAYERPARAM};
	CComboBox	m_comboCard;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLayerParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLayerParam)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

