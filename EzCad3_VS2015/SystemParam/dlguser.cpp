// dlguser.cpp : implementation file
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "dlguser.h" 
#include "qglobal.h"
#include "DlgPsw.h"
#include "QUser.h"

#include "DlgUserParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUser dialog


CDlgUser::CDlgUser(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgUser)
	m_bEnUser = FALSE;
	//}}AFX_DATA_INIT
	m_pParam = NULL;
}


void CDlgUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUser)
	DDX_Control(pDX, IDC_LIST_USER, m_listUser);
	DDX_Check(pDX, IDC_CHECK_ENUSER, m_bEnUser);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUser, CDialog)
	//{{AFX_MSG_MAP(CDlgUser)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_BN_CLICKED(IDC_CHECK_ENUSER, OnCheckEnuser)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnButtonModify)
	ON_LBN_DBLCLK(IDC_LIST_USER, OnDblclkListUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUser message handlers
BOOL CDlgUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	GetDlgItem(IDC_CHECK_ENUSER)->SetWindowText(QGlobal::gf_Str(_T("SOFTUSEPSW"),_T("Use the soft must enter and password ")));
	GetDlgItem(IDC_STATIC_USER)->SetWindowText(QGlobal::gf_Str(_T("USER"),_T("User")));

	GetDlgItem(IDC_BUTTON_ADD)->SetWindowText(QGlobal::gf_Str(_T("ADD"),_T("Add")));
	GetDlgItem(IDC_BUTTON_DEL)->SetWindowText(QGlobal::gf_Str(_T("DELETE"),_T("Delete")));
	GetDlgItem(IDC_BUTTON_MODIFY)->SetWindowText(QGlobal::gf_Str(_T("MODIFY"),_T("Modify")));

/*	m_listUser.AddString(QGlobal::gf_Str(_T("ADMIN"),_T("Administrator")));
	m_listUser.AddString(QGlobal::gf_Str(_T("DESIGNED"),_T("Designed")));
	m_listUser.AddString(QGlobal::gf_Str(_T("DRAFTSMAN"), _T("Draftsman")));

	
	for(int i=0;i<m_pParam->GetParamInt(INT_PARAM_WORKERNUM);i++)
	{
		m_listUser.AddString(m_pParam->GetParamString(SYS_STR_WORKNAME1+i));
	}	
	*/
	UpdateUserList();
	m_bEnUser = m_pParam->GetParamInt(INT_PARAM_ENUSERPSW);
	UpdateData(FALSE);
	ShowEnuser() ;	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgUser::OnOK() 
{
	// TODO: Add extra validation here
	
}

void CDlgUser::OnCancel() 
{
	// TODO: Add extra cleanup here	
	
}
void CDlgUser::OK()
{
	if(  gf_GetUserMgr()->GetCurUser()->IsAdmin())
			 
	{
		UpdateData();
		m_pParam->SetParamInt(INT_PARAM_ENUSERPSW,m_bEnUser);
	}
}
void CDlgUser::UpdateUserList() 
{
	m_listUser.ResetContent();

	 QUserMgr* pMgr = gf_GetUserMgr();
	 if(pMgr!=NULL)
	 {
	for(int i=0;i<pMgr->Count();i++)
	{

		m_listUser.AddString(pMgr->GetUser(i)->m_strName);
	}
	 }
}

void CDlgUser::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	QUserMgr* pMgr = gf_GetUserMgr();
	if(pMgr!=NULL)
	{ 
		QUser* pUser = new QUser();
		while(1)
		{
			CDlgUserParam dlg;
			dlg.m_pUser = pUser;
			if(dlg.DoModal()==IDOK)
			{
				if(pMgr->FindUser(pUser->m_strName))
				{//已经有了
					if(MessageBox(QGlobal::gf_Str(_T("ALREADYHAVETHISUSER"),_T("Already have this user")),QGlobal::gf_Str(_T("WARN"),_T("Warn")),MB_OKCANCEL)==IDOK)
					{
						continue;
					}
					else
					{
						delete pUser;
						return;
					} 
				}
				pMgr->AddUser(pUser);
				UpdateUserList();
				gf_SaveUserParamFile(); 
				m_listUser.SetCurSel(m_listUser.GetCount()-1);
				break;
			}
			else
			{
				delete pUser;
				return;
			}
		}
	}


/*	if(m_pParam->GetParamInt(INT_PARAM_WORKERNUM)>=MAX_WORK_NUM)
	{
		return;
	}

 	CDlgPsw dlg;
	dlg.m_bCanChangeName = TRUE;
	if(dlg.DoModal()==IDOK)
	{		
		if(QGlobal::gf_Str(_T("ADMIN"),_T("Administrator"))==dlg.m_strName)
		{
			AfxMessageBox(_T("Name is unvalid"));
			return;
		}
		if(QGlobal::gf_Str(_T("DESIGNED"),_T("Designed"))==dlg.m_strName)
		{
			AfxMessageBox(_T("Name is unvalid"));
			return;
		}
		if(QGlobal::gf_Str(_T("DRAFTSMAN"), _T("Draftsman"))==dlg.m_strName)
		{
			AfxMessageBox(_T("Name is unvalid"));
			return;
		}
		
		for(int i=0;i<m_pParam->GetParamInt(INT_PARAM_WORKERNUM);i++)
		{
			if(m_pParam->GetParamString(SYS_STR_WORKNAME1+i)==dlg.m_strName)
			{
				AfxMessageBox(_T("Name is unvalid"));
				return;
			}
		}	

		m_pParam->SetParamString(SYS_STR_WORKNAME1+m_pParam->GetParamInt(INT_PARAM_WORKERNUM),dlg.m_strName);
	m_pParam->SetParamString(SYS_STR_WORKPSW1+m_pParam->GetParamInt(INT_PARAM_WORKERNUM),dlg.m_strPsw1);

	 m_pParam->SetParamInt(INT_PARAM_WORKERNUM,m_pParam->GetParamInt(INT_PARAM_WORKERNUM)+1);
	
	}  */
}

void CDlgUser::OnButtonDel() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_listUser.GetCurSel();
	QUserMgr* pMgr = gf_GetUserMgr();
	if(pMgr!=NULL)
	{ 
		QUser* pUser = pMgr->GetUser(nSel);
		if(!pUser->IsAdmin())
		{
			pMgr->RemoveUser(nSel);
			delete pUser;
			UpdateUserList();
			gf_SaveUserParamFile(); 
		}

	}

	/*if(nSel == 0 || nSel == 1 || nSel == 2)
	{
		return;
	}
	else if(m_pParam->GetParamInt(INT_PARAM_WORKERNUM)>0)
	{
		m_listUser.DeleteString(nSel);
		nSel-=3;

		for(int i = nSel+1; i < m_pParam->GetParamInt(INT_PARAM_WORKERNUM);i++)
		{
			m_pParam->SetParamString(SYS_STR_WORKNAME1+i-1,m_pParam->GetParamString(SYS_STR_WORKNAME1+i));
			m_pParam->SetParamString(SYS_STR_WORKPSW1+i-1,m_pParam->GetParamString(SYS_STR_WORKPSW1+i));

 		}
		m_pParam->SetParamInt(INT_PARAM_WORKERNUM,m_pParam->GetParamInt(INT_PARAM_WORKERNUM)-1);
	}*/

}

void CDlgUser::OnButtonModify() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_listUser.GetCurSel();

	QUserMgr* pMgr = gf_GetUserMgr();
	if(nSel>=0 && pMgr!=NULL)
	{ 
		CDlgUserParam dlg;
		dlg.m_bDisableName=TRUE;
		dlg.m_pUser = pMgr->GetUser(nSel);
		if(dlg.DoModal()==IDOK)
		{
			UpdateUserList();
			gf_SaveUserParamFile(); 
			m_listUser.SetCurSel(nSel);
		}

	}

	/*CDlgPsw dlg;
	if(nSel == 0 )
	{
		dlg.m_bCanChangeName = FALSE;
	}
	else if(nSel == 1)
	{
		dlg.m_bCanChangeName = FALSE;
	}
	else if(nSel == 2)
	{
		dlg.m_bCanChangeName = FALSE;
	}
	else
	{
		dlg.m_bCanChangeName = TRUE;
	}
	m_listUser.GetText(nSel,dlg.m_strName );
	if(dlg.DoModal()==IDOK)
	{		
		if( nSel == 0 )
		{
			m_pParam->SetParamString(SYS_STR_PSW_ADMIN,dlg.m_strPsw1);
			 
		}
		else if( nSel == 1 )
		{
			m_pParam->SetParamString(SYS_STR_PSW_DESIGNER,dlg.m_strPsw1);
		}
		else if(nSel == 2)
		{
			m_pParam->SetParamString(SYS_STR_PSW_DRAFT,dlg.m_strPsw1);
		}
		else
		{		
			if(m_pParam->GetParamString(SYS_STR_WORKNAME1+nSel-3)!=dlg.m_strName)
			{
				m_pParam->SetParamString(SYS_STR_WORKNAME1+nSel-3,dlg.m_strName);
			 
		 
				m_listUser.DeleteString(nSel);
				m_listUser.InsertString(nSel,dlg.m_strName);		
			}
			m_pParam->SetParamString(SYS_STR_WORKPSW1+nSel-3,dlg.m_strPsw1);
		}
	}*/
}

void CDlgUser::OnCheckEnuser() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ShowEnuser() ;	
}

void CDlgUser::ShowEnuser() 
{
	// TODO: Add your control notification handler code here
	if( gf_GetUserMgr()->GetCurUser()->IsAdmin()) 
	{
		GetDlgItem(IDC_CHECK_ENUSER)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_CHECK_ENUSER)->EnableWindow(FALSE);
	}

	if(m_bEnUser &&  gf_GetUserMgr()->GetCurUser()->IsAdmin())
	{			
		GetDlgItem(IDC_LIST_USER)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_ADD)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_DEL)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_MODIFY)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_LIST_USER)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_DEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_MODIFY)->EnableWindow(FALSE);
	}		
}


void CDlgUser::OnDblclkListUser() 
{
	// TODO: Add your control notification handler code here
	OnButtonModify();
}
