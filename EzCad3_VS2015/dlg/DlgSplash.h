 
#pragma once
 
#include "..\resource.h"	
/////////////////////////////////////////////////////////////////////////////
// CDlgSplash dialog

class   CDlgSplash : public CDialog
{
// Construction
public:
	CDlgSplash(CWnd* pParent = NULL);   // standard constructor
	void OK();

	CBitmap  m_bmpView;

// Dialog Data
	//{{AFX_DATA(CDlgSplash)
	enum { IDD = IDD_DIALOG_SPLASH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	void ShowSplash(CWnd* pParent);
	void HideSplash();

	BOOL LoadBitmap( CString bmpfile );
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSplash)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSplash)
	virtual BOOL OnInitDialog();
	virtual void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
 