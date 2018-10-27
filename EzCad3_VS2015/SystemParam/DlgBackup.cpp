// DlgBackup.cpp : implementation file
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "dlgbackup.h"

#include "qglobal.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBackup dialog


CDlgBackup::CDlgBackup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBackup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBackup)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pParam = NULL;
}


void CDlgBackup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBackup)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBackup, CDialog)
	//{{AFX_MSG_MAP(CDlgBackup)
	ON_EN_KILLFOCUS(IDC_EDIT_SAVETIME, OnKillfocusEditSavetime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBackup message handlers

BOOL CDlgBackup::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_CHECK_BAK)->SetWindowText(QGlobal::gf_Str(_T("EVERY"),_T("Every")));
	GetDlgItem(IDC_STATIC_SAVEBAK)->SetWindowText(QGlobal::gf_Str(_T("BAKTIME"),_T("minutes,Auto save")));
	GetDlgItem(IDC_STATIC_EXPLAIN)->SetWindowText(QGlobal::gf_Str(_T("BAKEXPLAIN"),_T(" Save current data to file 'AutoSave.Ezd' in EzCad's directory every time specified.")));

	ASSERT(m_pParam!=NULL);

	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_BAK);
	pBtn->SetCheck(m_pParam ->GetParamInt(INT_PARAM_AUTOSAVE)); 
	
	CString str;
	str.Format(_T("%d"),m_pParam ->GetParamInt(INT_PARAM_AUTOSAVETIME)) ;
	GetDlgItem(IDC_EDIT_SAVETIME)->SetWindowText(str);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgBackup::OnOK() 
{
	// TODO: Add extra validation here
	
}

void CDlgBackup::OnCancel() 
{
	// TODO: Add extra cleanup here	

}

void CDlgBackup::OK()
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_BAK);
	m_pParam ->SetParamInt(INT_PARAM_AUTOSAVE,pBtn->GetCheck());

	CString str;
	GetDlgItem(IDC_EDIT_SAVETIME)->GetWindowText(str);
	int nAutoSaveTime = _ttoi(str);
	if(nAutoSaveTime < 1)
	{
		nAutoSaveTime = 1;
	}
	m_pParam ->SetParamInt(INT_PARAM_AUTOSAVETIME,nAutoSaveTime);

 

}

void CDlgBackup::OnKillfocusEditSavetime() 
{
	// TODO: Add your control notification handler code here
	
}
