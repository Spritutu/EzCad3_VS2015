// dlggeneral.cpp : implementation file
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "dlggeneral.h"

#include "qglobal.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGeneral dialog


CDlgGeneral::CDlgGeneral(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGeneral::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGeneral)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pParam = NULL;
}


void CDlgGeneral::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGeneral)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_COMBO_UNIT,m_comboxUnit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGeneral, CDialog)
	//{{AFX_MSG_MAP(CDlgGeneral)
	ON_BN_CLICKED(IDC_BUTTON_STARTRUN, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_ENDRUN, OnButtonFinish)
	 
	//}}AFX_MSG_MAP
	
	ON_BN_CLICKED(IDC_CHECK_SHOWGRID, &CDlgGeneral::OnBnClickedCheckShowgrid)
	ON_BN_CLICKED(IDC_CHECK_SHOWFAST, &CDlgGeneral::OnBnClickedCheckShowfast)
	ON_BN_CLICKED(IDC_CHECK_SHOWDIR, &CDlgGeneral::OnBnClickedCheckShowdir)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_THREAD, &CDlgGeneral::OnDeltaposSpinThread)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_THREAD2, &CDlgGeneral::OnDeltaposSpinThread2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGeneral message handlers

BOOL CDlgGeneral::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_STATIC_UNIT   )->SetWindowText(QGlobal::gf_Str(_T("UNIT_TYPE"),_T("Unit type")));
	GetDlgItem(IDC_STATIC_GRIG   )->SetWindowText(QGlobal::gf_Str(_T("GRID_DIST"),_T("Grid distance")));
	GetDlgItem(IDC_STATIC_PASTE_X)->SetWindowText(QGlobal::gf_Str(_T("PASTE_X  "),_T("Paste X")));
	GetDlgItem(IDC_STATIC_PASTE_Y)->SetWindowText(QGlobal::gf_Str(_T("PASTE_Y  "),_T("Paste Y")));

	GetDlgItem(IDC_CHECK_SHOWGRID)->SetWindowText(QGlobal::gf_Str(_T("SHOW_GRID"),_T("Show Grid")));
	GetDlgItem(IDC_STATIC_GRID)->SetWindowText(QGlobal::gf_Str(_T("GRID"),_T("Grid")));	
	
  	GetDlgItem(IDC_STATIC_RUNSTART)->SetWindowText(QGlobal::gf_Str(_T("EXESTART"),_T("Execute when ezcad Starts ")));	
	GetDlgItem(IDC_STATIC_ENDRUN)->SetWindowText(QGlobal::gf_Str(_T("EXEFINISH"),_T("Execute when ezcad finish")));	

m_comboxUnit.AddString(QGlobal::gf_Str(_T("MM"),_T("mm")));
	m_comboxUnit.AddString(QGlobal::gf_Str(_T("INCH"),_T("inch")));   
 
	GetDlgItem(IDC_CHECK_SHOWFAST)->SetWindowText(QGlobal::gf_Str(_T("SHOWFAST"), _T("Show fast")));
	GetDlgItem(IDC_CHECK_SHOWDIR)->SetWindowText(QGlobal::gf_Str(_T("SHOWDIR"), _T("Show direction")));
	GetDlgItem(IDC_STATIC_MAXTHREAD)->SetWindowText(QGlobal::gf_Str(_T("MAXTHREADCNT"), _T("Max thread count")));
	GetDlgItem(IDC_STATIC_MESHSOL)->SetWindowText(QGlobal::gf_Str(_T("MESHRESOL"), _T("Mesh resolution")));

	CString strUnit;
	if(m_pParam ->GetParamInt(INT_PARAM_UNITTYPE)==UNIT_MM)
	{
		strUnit = QGlobal::gf_Str(_T("MM"),_T("mm"));
		m_comboxUnit.SetCurSel(0);
	}
	else
	{
		strUnit = QGlobal::gf_Str(_T("INCH"),_T("inch"));
		m_comboxUnit.SetCurSel(1);
	}

	GetDlgItem(IDC_STATIC_UNIT1)->SetWindowText(strUnit);	  
	GetDlgItem(IDC_STATIC_UNIT2)->SetWindowText(strUnit);	  
	GetDlgItem(IDC_STATIC_UNIT3)->SetWindowText(strUnit);	  


	CString str;	
	 
	GetDlgItem(IDC_EDIT_GRID)->SetWindowText(QGlobal::gf_GetLenStr(m_pParam->GetParamDouble(DOUBLE_PARAM_GRIDDIST)));
	GetDlgItem(IDC_EDIT_PASTEX)->SetWindowText(QGlobal::gf_GetLenStr(m_pParam->GetParamDouble(DOUBLE_PARAM_PASTEOFFSETX)));
	GetDlgItem(IDC_EDIT_PASTEY)->SetWindowText(QGlobal::gf_GetLenStr(m_pParam->GetParamDouble(DOUBLE_PARAM_PASTEOFFSETY)));

	GetDlgItem(IDC_EDIT_MAXTHREAD)->SetWindowText(QGlobal::gf_GetLenStr(m_pParam->GetParamInt(INT_PARAM_CALCTHREADCNT)));

	GetDlgItem(IDC_EDIT_MESHSOL)->SetWindowText(QGlobal::gf_GetLenStr(m_pParam->GetParamInt(INT_PARAM_RECTMESHRESOL)));

	
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_SHOWGRID);
	pBtn->SetCheck( m_pParam->GetParamInt(INT_PARAM_SHOWGRID));
 	 
	pBtn = (CButton*)GetDlgItem(IDC_CHECK_SHOWFAST);
	pBtn->SetCheck(m_pParam->GetParamInt(INT_PARAM_FASTSHOW));

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_SHOWDIR);
	pBtn->SetCheck(m_pParam->GetParamInt(INT_PARAM_SHOWCURVEDIR));
 


	GetDlgItem(IDC_EDIT_STARTRUN)->SetWindowText(m_pParam->GetParamString(SYS_STR_EXE_START_FILE));
	GetDlgItem(IDC_EDIT_ENDRUN)->SetWindowText(m_pParam->GetParamString(SYS_STR_EXE_ENDT_FILE));

	 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgGeneral::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	CString szExt;
	CString szFilter;
	szExt=_T("exe");
	szFilter=_T("execute files(*.exe)|*.exe||");
	CFileDialog dlg(TRUE, szExt,m_pParam->GetParamString(SYS_STR_EXE_START_FILE),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	if(dlg.DoModal()==IDOK)
	{
		m_pParam->SetParamString(SYS_STR_EXE_START_FILE,dlg.GetPathName());
		GetDlgItem(IDC_EDIT_STARTRUN)->SetWindowText(m_pParam->GetParamString(SYS_STR_EXE_START_FILE));

	}
}
void CDlgGeneral::OnButtonFinish() 
{
	// TODO: Add your control notification handler code here
	CString szExt;
	CString szFilter;
	szExt=_T("exe");
	szFilter=_T("execute files(*.exe)|*.exe||");
	CFileDialog dlg(TRUE, szExt,m_pParam->GetParamString(SYS_STR_EXE_ENDT_FILE),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	if(dlg.DoModal()==IDOK)
	{
		// 获得文件名称
	 	m_pParam->SetParamString(SYS_STR_EXE_ENDT_FILE,dlg.GetPathName()); 
		GetDlgItem(IDC_EDIT_ENDRUN)->SetWindowText(m_pParam->GetParamString(SYS_STR_EXE_ENDT_FILE));
	}
}



void CDlgGeneral::OnOK() 
{
	// TODO: Add extra validation here
	
}

void CDlgGeneral::OnCancel() 
{
	// TODO: Add extra cleanup here	

}

void CDlgGeneral::OK()
{
	if(m_comboxUnit.GetCurSel() == 0)	
	{
		m_pParam->SetParamInt(INT_PARAM_UNITTYPE,UNIT_MM); 
	}
	else
	{
		m_pParam->SetParamInt(INT_PARAM_UNITTYPE,UNIT_INCH); 
	}
	

	CString str;
	GetDlgItem(IDC_EDIT_GRID)->GetWindowText(str);
	m_pParam->SetParamDouble(DOUBLE_PARAM_GRIDDIST,QGlobal::ATOF(str));
	GetDlgItem(IDC_EDIT_PASTEX)->GetWindowText(str);
	m_pParam->SetParamDouble(DOUBLE_PARAM_PASTEOFFSETX,QGlobal::ATOF(str));
	GetDlgItem(IDC_EDIT_PASTEY)->GetWindowText(str);
	m_pParam->SetParamDouble(DOUBLE_PARAM_PASTEOFFSETY,QGlobal::ATOF(str));

	GetDlgItem(IDC_EDIT_MAXTHREAD)->GetWindowText(str);
	int n = QGlobal::ATOI(str);
	if (n < 1)
	{
		n = 1;
	}
	else if (n >128)
	{
		n = 128;
	}
	m_pParam->SetParamInt(INT_PARAM_CALCTHREADCNT,n);
	 

	GetDlgItem(IDC_EDIT_MESHSOL)->GetWindowText(str);
	  n = QGlobal::ATOI(str);
	if (n <0)
	{
		n = 0;
	}
	else if (n >3)
	{
		n = 3;
	}
	m_pParam->SetParamInt(INT_PARAM_RECTMESHRESOL, n);


 	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_SHOWGRID);
	m_pParam->SetParamInt(INT_PARAM_SHOWGRID,pBtn->GetCheck( ));
 
	pBtn = (CButton*)GetDlgItem(IDC_CHECK_SHOWFAST);
	m_pParam->SetParamInt(INT_PARAM_FASTSHOW, pBtn->GetCheck());
	 

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_SHOWDIR);
	m_pParam->SetParamInt(INT_PARAM_SHOWCURVEDIR, pBtn->GetCheck());
	 


	GetDlgItem(IDC_EDIT_STARTRUN)->GetWindowText(str);
	m_pParam->SetParamString(SYS_STR_EXE_START_FILE,str);
	 
	GetDlgItem(IDC_EDIT_ENDRUN)->GetWindowText(str);
	m_pParam->SetParamString(SYS_STR_EXE_ENDT_FILE,str);
}

 

void CDlgGeneral::OnBnClickedCheckEnprojectview()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgGeneral::OnBnClickedCheckShowgrid()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgGeneral::OnBnClickedCheckShowfast()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgGeneral::OnBnClickedCheckShowdir()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgGeneral::OnDeltaposSpinThread(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CString str;
	GetDlgItem(IDC_EDIT_MAXTHREAD)->GetWindowText(str);
	int n = QGlobal::ATOI(str);
	

	if (pNMUpDown->iDelta > 0)
	{
		if (n <= 4)
		{
			n--;
		}
		else
		{
			n -= 4;
		}
	}
	else
	{
		if (n < 4)
		{
			n++;
		}
		else
		{
			n += 4;
		}		
	}

	if (n < 1)
	{
		n = 1;
	}
	else if (n >128)
	{
		n = 128;
	}
	str.Format(_T("%d"), n);
	GetDlgItem(IDC_EDIT_MAXTHREAD)->SetWindowText(str);
}


void CDlgGeneral::OnDeltaposSpinThread2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CString str;
	GetDlgItem(IDC_EDIT_MESHSOL)->GetWindowText(str);
	int n = QGlobal::ATOI(str);


	if (pNMUpDown->iDelta > 0)
	{
		n --;
	}
	else
	{ 
		n++; 
	}

	if (n < 0)
	{
		n = 0;
	}
	else if (n >3)
	{
		n = 3;
	}
	str.Format(_T("%d"), n);
	GetDlgItem(IDC_EDIT_MESHSOL)->SetWindowText(str);
}
