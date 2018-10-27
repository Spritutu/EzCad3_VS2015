// dlgsystemparam.cpp : implementation file
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "dlgsystemparam.h"
#include "qglobal.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSystemParam dialog


CDlgSystemParam::CDlgSystemParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSystemParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSystemParam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pParam = NULL;
}


void CDlgSystemParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSystemParam)
	DDX_Control(pDX, IDC_TREE_SYSPARAM, m_treeSys);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSystemParam, CDialog)
	//{{AFX_MSG_MAP(CDlgSystemParam)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_SYSPARAM, OnSelchangedTreeParam)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDlgSystemParam::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSystemParam message handlers

BOOL CDlgSystemParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ASSERT(m_pParam!=NULL);
	// TODO: Add extra initialization here
	SetWindowText(QGlobal::gf_Str(_T("SYSTEMPARAM"),_T("System parameter")));
	pItemGeneral= m_treeSys.InsertItem (QGlobal::gf_Str(_T("GENERAL"),_T("General")));
	pItemColor  = m_treeSys.InsertItem (QGlobal::gf_Str(_T("COLOR"),_T("Color")));
	pItemWork   = m_treeSys.InsertItem (QGlobal::gf_Str(_T("WORKSPACE"),_T("WorkSpace")));
	pItemBackup = m_treeSys.InsertItem (QGlobal::gf_Str(_T("AUTOSAVE"),_T("AutoSave")));
	pItemMove   = m_treeSys.InsertItem (QGlobal::gf_Str(_T("MOVEROTATE"),_T("Move rotate")));
	//pItemPlug   = m_treeSys.InsertItem (QGlobal::gf_Str(_T("PLUGMGR"),_T("Plug manager")));
	pItemUser   = m_treeSys.InsertItem (QGlobal::gf_Str(_T("USERMGR"),_T("User manager" )));	//Must be always English
	
	pItemLang   = m_treeSys.InsertItem (_T("Language"));	//Must be always English


	m_dlgGeneral.m_pParam = m_pParam;
	m_dlgColor.m_pParam = m_pParam;
	m_dlgWork.m_pParam = m_pParam;
	m_dlgBackup.m_pParam = m_pParam;

	m_dlgMove.m_pParam = m_pParam;
	m_dlgUser.m_pParam = m_pParam;
	//m_dlgPlug.m_pParam = m_pParam;
	
	m_dlgLang.m_pParam = m_pParam;
	

	CWnd* pWnd = GetDlgItem(IDC_STATIC_PARAM);
	ASSERT(pWnd!=NULL);
	m_dlgGeneral.Create( IDD_DIALOG_SYS_GENERAL, pWnd); 
	m_dlgColor.Create( IDD_DIALOG_SYS_COLOR, pWnd); 
	m_dlgWork.Create( IDD_DIALOG_SYS_WORKSPACE, pWnd); 
	m_dlgBackup.Create( IDD_DIALOG_SYS_BACKUP, pWnd); 
	m_dlgMove.Create( IDD_DIALOG_SYS_MOVEROTATE, pWnd);
	m_dlgUser.Create( IDD_DIALOG_SYS_USER, pWnd); 
	//m_dlgPlug.Create( IDD_DIALOG_SYS_PLUG, pWnd); 
	
	m_dlgLang.Create( IDD_DIALOG_SYS_LANG, pWnd); 
		
	m_dlgGeneral.ShowWindow ( SW_SHOW );

	GetDlgItem(IDOK)->SetWindowText(QGlobal::gf_Str(_T("IDOK"),_T("&Ok")));
	GetDlgItem(IDCANCEL)->SetWindowText(QGlobal::gf_Str(_T("IDCANCEL"),_T("&Cancel")));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSystemParam::OnSelchangedTreeParam(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	if(pNMTreeView->itemNew.hItem == pItemGeneral)
	{
		m_dlgGeneral.ShowWindow ( SW_SHOW );
		m_dlgColor.ShowWindow ( SW_HIDE );
		m_dlgWork.ShowWindow ( SW_HIDE );
		m_dlgBackup.ShowWindow ( SW_HIDE );
		m_dlgMove.ShowWindow ( SW_HIDE );
	//	m_dlgPlug.ShowWindow ( SW_HIDE );
		
		m_dlgUser.ShowWindow ( SW_HIDE );
		m_dlgLang.ShowWindow ( SW_HIDE );	
	}
	else if(pNMTreeView->itemNew.hItem == pItemColor)
	{
		m_dlgGeneral.ShowWindow ( SW_HIDE );
		m_dlgColor.ShowWindow ( SW_SHOW );
		m_dlgWork.ShowWindow ( SW_HIDE );
		m_dlgBackup.ShowWindow ( SW_HIDE );
		m_dlgMove.ShowWindow ( SW_HIDE );
	//	m_dlgPlug.ShowWindow ( SW_HIDE );
		
		
		m_dlgUser.ShowWindow ( SW_HIDE );
		m_dlgLang.ShowWindow ( SW_HIDE );	
	}
	else if(pNMTreeView->itemNew.hItem == pItemWork)
	{
		m_dlgGeneral.ShowWindow ( SW_HIDE );
		m_dlgWork.ShowWindow ( SW_SHOW );
		m_dlgColor.ShowWindow ( SW_HIDE );
		m_dlgBackup.ShowWindow ( SW_HIDE );
		m_dlgMove.ShowWindow ( SW_HIDE );
	//m_dlgPlug.ShowWindow ( SW_HIDE );
		
		
		m_dlgLang.ShowWindow ( SW_HIDE );
		m_dlgUser.ShowWindow ( SW_HIDE ); 
	}
	else if(pNMTreeView->itemNew.hItem == pItemBackup)
	{
		m_dlgWork.ShowWindow ( SW_HIDE );
		m_dlgGeneral.ShowWindow ( SW_HIDE );
		m_dlgBackup.ShowWindow ( SW_SHOW );
		m_dlgColor.ShowWindow ( SW_HIDE );
		m_dlgMove.ShowWindow ( SW_HIDE );
	//	m_dlgPlug.ShowWindow ( SW_HIDE );
		
		m_dlgLang.ShowWindow ( SW_HIDE );	
		m_dlgUser.ShowWindow ( SW_HIDE );
	}
	else if(pNMTreeView->itemNew.hItem == pItemMove)
	{
		m_dlgMove.ShowWindow ( SW_SHOW );
		m_dlgColor.ShowWindow ( SW_HIDE );
		m_dlgBackup.ShowWindow ( SW_HIDE );
		
		m_dlgWork.ShowWindow ( SW_HIDE );
		m_dlgGeneral.ShowWindow ( SW_HIDE );
		m_dlgLang.ShowWindow ( SW_HIDE );
		m_dlgUser.ShowWindow ( SW_HIDE );
	//	m_dlgPlug.ShowWindow ( SW_HIDE ); 
	}
	else if(pNMTreeView->itemNew.hItem == pItemPlug)
	{
//		m_dlgPlug.ShowWindow ( SW_SHOW );
		m_dlgColor.ShowWindow ( SW_HIDE );
		m_dlgBackup.ShowWindow ( SW_HIDE );
		m_dlgMove.ShowWindow ( SW_HIDE );
		m_dlgWork.ShowWindow ( SW_HIDE );
		m_dlgGeneral.ShowWindow ( SW_HIDE );
		m_dlgLang.ShowWindow ( SW_HIDE );
		m_dlgUser.ShowWindow ( SW_HIDE );
	}
	else if(pNMTreeView->itemNew.hItem == pItemUser)
	{

		m_dlgUser.ShowWindow ( SW_SHOW );

		m_dlgColor.ShowWindow ( SW_HIDE );
		m_dlgBackup.ShowWindow ( SW_HIDE );
		m_dlgMove.ShowWindow ( SW_HIDE );
		m_dlgWork.ShowWindow ( SW_HIDE );
		m_dlgGeneral.ShowWindow ( SW_HIDE );
	//	m_dlgPlug.ShowWindow ( SW_HIDE );
		m_dlgLang.ShowWindow ( SW_HIDE );
	}
	else if(pNMTreeView->itemNew.hItem == pItemLang)
	{
		m_dlgLang.ShowWindow ( SW_SHOW );
		m_dlgColor.ShowWindow ( SW_HIDE );
		m_dlgBackup.ShowWindow ( SW_HIDE );
		m_dlgMove.ShowWindow ( SW_HIDE );
		m_dlgWork.ShowWindow ( SW_HIDE );
		m_dlgGeneral.ShowWindow ( SW_HIDE );
	//	m_dlgPlug.ShowWindow ( SW_HIDE );	
		m_dlgUser.ShowWindow ( SW_HIDE );
	}

	
	*pResult = 0;
}

void CDlgSystemParam::OnOK() 
{
	// TODO: Add extra validation here
	m_dlgGeneral.OK();
	m_dlgColor.OK();
	m_dlgWork.OK();
	m_dlgBackup.OK();	
	m_dlgMove.OK();
//	m_dlgPlug.OK();	
	m_dlgLang.OK();
	m_dlgUser.OK();
	CDialog::OnOK();
}

void CDlgSystemParam::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}


void CDlgSystemParam::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
//	CDialog::OnOK();
	OnOK();
}
