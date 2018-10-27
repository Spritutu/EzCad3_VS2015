// dlgcolor.cpp : implementation file
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "dlgcolor.h"
#include "qglobal.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgColor dialog


CDlgColor::CDlgColor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgColor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgColor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pParam = NULL;
}


void CDlgColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgColor)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_STATIC_CLR_BK,m_scbBK     );
	DDX_Control(pDX,IDC_STATIC_CLR_PAPER,m_scbPaper  );
	DDX_Control(pDX,IDC_STATIC_CLR_GUIDE,m_scbGuide  );
	DDX_Control(pDX,IDC_STATIC_CLR_GRID,m_scbGrid  );
	 
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgColor, CDialog)
	//{{AFX_MSG_MAP(CDlgColor)
	//}}AFX_MSG_MAP 
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgColor message handlers

BOOL CDlgColor::OnInitDialog() 
{
	CDialog::OnInitDialog();
 

	GetDlgItem(IDC_STATIC_BK)->SetWindowText(QGlobal::gf_Str(_T("BK"),_T("Background")));
	GetDlgItem(IDC_STATIC_PAPER)->SetWindowText(QGlobal::gf_Str(_T("WORKSPACE"),_T("Workspace")));
	GetDlgItem(IDC_STATIC_GUIDE)->SetWindowText(QGlobal::gf_Str(_T("GUIDELINE"),_T("Guildline")));
	GetDlgItem(IDC_STATIC_GRID)->SetWindowText(QGlobal::gf_Str(_T("GRID"),_T("Grid")));

	// TODO: Add extra initialization here
		ASSERT(m_pParam!=NULL);

	m_scbBK.SetColor( m_pParam->GetParamClr(SYS_CLR_BACKGROUND ));
	m_scbPaper.SetColor( m_pParam->GetParamClr(SYS_CLR_WORKSPACE));
	m_scbGuide.SetColor( m_pParam->GetParamClr(SYS_CLR_GUILDLINE));
	m_scbGrid.SetColor( m_pParam->GetParamClr(SYS_CLR_GRIDLINE));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgColor::OnOK() 
{
	// TODO: Add extra validation here
	
}

void CDlgColor::OnCancel() 
{
	// TODO: Add extra cleanup here	

}

void CDlgColor::OK()
{
	m_pParam->SetParamClr(SYS_CLR_BACKGROUND, m_scbBK.GetColor());
	m_pParam->SetParamClr(SYS_CLR_WORKSPACE, m_scbPaper.GetColor());
	m_pParam->SetParamClr(SYS_CLR_GUILDLINE,  m_scbGuide.GetColor());
	m_pParam->SetParamClr(SYS_CLR_GRIDLINE, m_scbGrid.GetColor( ));
}

 