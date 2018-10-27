// dlgiocondi.cpp : implementation file
//

#include "stdafx.h"
#include "..\ezcad3.h"
#include "DlgLayerParam.h"
#include "qglobal.h"
#include "SysParam.h"
#include "EntMgr.h"
#include "CmdMgr.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLayerParam dialog


CDlgLayerParam::CDlgLayerParam(CWnd* pParent /*=NULL*/)
: CDialog(CDlgLayerParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLayerParam)

	//}}AFX_DATA_INIT
}


void CDlgLayerParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLayerParam)
	DDX_Control(pDX, IDC_COMBO_CARD, m_comboCard);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLayerParam, CDialog)
	//{{AFX_MSG_MAP(CDlgLayerParam)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDlgLayerParam::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLayerParam message handlers

BOOL CDlgLayerParam::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	WORD m_wIoHigh = m_pLayer->m_wIoHigh;
	WORD m_wIoLow = m_pLayer->m_wIoLow;

	SetDlgItemText(IDC_EDIT_NAME,m_pLayer->GetName());

	WORD wIoMask = gf_GetSysParam()->GetParamInt(INT_PARAM_INPUTIOMASK);
	for(int i=0;i<16;i++)
	{
		WORD io = 0x0001 << i;
		if(io & wIoMask)
		{				
			((CButton*)GetDlgItem(IDC_IN0+i))->SetButtonStyle(BS_AUTO3STATE);
			GetDlgItem(IDC_IN0+i)->EnableWindow(TRUE);
			if(m_wIoHigh & io)
			{
				((CButton*)GetDlgItem(IDC_IN0+i))->SetCheck(1);
			}
			else if(m_wIoLow & io)
			{
				((CButton*)GetDlgItem(IDC_IN0+i))->SetCheck(0);
			}
			else
			{
				((CButton*)GetDlgItem(IDC_IN0+i))->SetCheck(2);
			}
		}
		else
		{
			GetDlgItem(IDC_IN0+i)->EnableWindow(FALSE);
		}			
	}

	SetWindowText(QGlobal::gf_Str(_T("LAYER"),_T("Layer")));	
	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(QGlobal::gf_Str(_T("NAME"),_T("Name")));
	GetDlgItem(IDC_STATIC_CARD)->SetWindowText(QGlobal::gf_Str(_T("CARD"),_T("Card")));

	GetDlgItem(IDOK)->SetWindowText(QGlobal::gf_Str(_T("IDOK"),_T("&OK")));
	GetDlgItem(IDCANCEL)->SetWindowText(QGlobal::gf_Str(_T("IDCANCEL"),_T("&Cancel")));
	GetDlgItem(IDC_STATIC_DIGITALIO)->SetWindowText(QGlobal::gf_Str(_T("IOCTRLCONDITION"),_T("I/O Control Conditional")));


	CString str;
	for(int i=0;i<8;i++)
	{	
		str.Format(_T("%d"),i);
		
		m_comboCard.AddString( str );			
	}
	m_comboCard.SetCurSel(m_pLayer->m_nCardSn);
#ifdef  TWOHEAD_WELD  //双头焊接
#else
	GetDlgItem(IDC_STATIC_CARD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_CARD)->ShowWindow(SW_HIDE);

#endif
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLayerParam::OnOK() 
{
	// TODO: Add extra validation here
	WORD wIoMask = gf_GetSysParam()->GetParamInt(INT_PARAM_INPUTIOMASK);
	WORD m_wIoHigh = 0;
	WORD m_wIoLow  = 0;
	for(int i=0;i<16;i++)
	{
		WORD io = 0x0001 << i;
		if(io & wIoMask)
		{				
			int nCheck = ((CButton*)GetDlgItem(IDC_IN0+i))->GetCheck();
			if(nCheck==0)
			{
				m_wIoLow |= io;
			}
			else if(nCheck==1)
			{
				m_wIoHigh |= io;
			}
		}		
	}	


	CString str;
	GetDlgItemText(IDC_EDIT_NAME,str);
	
		if(gf_GetCmdMgr()==NULL)
	{
		return;
	}

	CEntMgr* pEM = gf_GetCmdMgr()->GetEM();
	if(pEM==NULL)
	{
		return;
	}
	if(pEM!=NULL)
	{
		CEntity* pLayer = pEM->GetChildHead();
		while(pLayer!=NULL)
		{
			if(pLayer !=  m_pLayer && pLayer->GetName()==str)
			{
				AfxMessageBox(QGlobal::gf_Str(_T(" LAYSERNAMESAME"),_T("The Layer name is the same as other!")));
				return;
			}

			pLayer = pLayer->GetNext();
		}
		

		pEM->BeginUndo(QGlobal::gf_Str(_T("MODIFY"),_T("Modify")));
		m_pLayer->UD_Modify(MDTYPE_SAVE_ENTITY,pEM->GetUndoMgr());
		m_pLayer->m_wIoHigh =  m_wIoHigh;
		m_pLayer->m_wIoLow =  m_wIoLow ;	
		m_pLayer->SetName(str);
		m_pLayer->m_nCardSn = m_comboCard.GetCurSel();

		pEM->EndUndo();										
	}

	CDialog::OnOK();
}

void CDlgLayerParam::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
