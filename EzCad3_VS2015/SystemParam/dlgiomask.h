#if !defined(AFX_DLGIOMASK_H__83F3012C_C9C5_4D5C_9221_E816573C6B9E__INCLUDED_)
#define AFX_DLGIOMASK_H__83F3012C_C9C5_4D5C_9221_E816573C6B9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgiomask.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIoMask dialog

class CDlgIoMask : public CDialog
{
// Construction
public:
	CDlgIoMask(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIoMask)
	enum { IDD = IDD_DIALOG_IOMASK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	WORD m_wMask;
	CString m_strTitle;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIoMask)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIoMask)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIOMASK_H__83F3012C_C9C5_4D5C_9221_E816573C6B9E__INCLUDED_)
