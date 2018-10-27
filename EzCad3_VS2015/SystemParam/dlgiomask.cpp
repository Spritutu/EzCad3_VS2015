// dlgiomask.cpp : implementation file
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "dlgiomask.h"
#include "global.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIoMask dialog


CDlgIoMask::CDlgIoMask(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIoMask::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIoMask)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_wMask = 0;
}


void CDlgIoMask::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIoMask)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIoMask, CDialog)
	//{{AFX_MSG_MAP(CDlgIoMask)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIoMask message handlers

BOOL CDlgIoMask::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	((CButton*)GetDlgItem(IDC_IN0))->SetCheck(m_wMask&0x01);
	((CButton*)GetDlgItem(IDC_IN1))->SetCheck(m_wMask&0x02);
	((CButton*)GetDlgItem(IDC_IN2))->SetCheck(m_wMask&0x04);
	((CButton*)GetDlgItem(IDC_IN3))->SetCheck(m_wMask&0x08);
	((CButton*)GetDlgItem(IDC_IN4))->SetCheck(m_wMask&0x10);
	((CButton*)GetDlgItem(IDC_IN5))->SetCheck(m_wMask&0x20);
	((CButton*)GetDlgItem(IDC_IN6))->SetCheck(m_wMask&0x40);
	((CButton*)GetDlgItem(IDC_IN7))->SetCheck(m_wMask&0x80);
	((CButton*)GetDlgItem(IDC_IN8))->SetCheck(m_wMask&0x100);
	((CButton*)GetDlgItem(IDC_IN9))->SetCheck(m_wMask&0x200);
	((CButton*)GetDlgItem(IDC_IN10))->SetCheck(m_wMask&0x400);
	((CButton*)GetDlgItem(IDC_IN11))->SetCheck(m_wMask&0x800);
	((CButton*)GetDlgItem(IDC_IN12))->SetCheck(m_wMask&0x1000);
	((CButton*)GetDlgItem(IDC_IN13))->SetCheck(m_wMask&0x2000);
	((CButton*)GetDlgItem(IDC_IN14))->SetCheck(m_wMask&0x4000);
	((CButton*)GetDlgItem(IDC_IN15))->SetCheck(m_wMask&0x8000);


	SetWindowText(m_strTitle);

	GetDlgItem(IDOK)->SetWindowText(gf_Str(_T("IDOK"),_T("&OK")));
	GetDlgItem(IDCANCEL)->SetWindowText(gf_Str(_T("IDCANCEL"),_T("&Cancel")));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgIoMask::OnOK() 
{
	// TODO: Add extra validation here
	m_wMask = 0;
	if(((CButton*)GetDlgItem(IDC_IN0))->GetCheck())
	{
		m_wMask |= 0x01;
	}
	if(((CButton*)GetDlgItem(IDC_IN1))->GetCheck())
	{
		m_wMask |= 0x02;
	}
	if(((CButton*)GetDlgItem(IDC_IN2))->GetCheck())
	{
		m_wMask |= 0x04;
	}
	if(((CButton*)GetDlgItem(IDC_IN3))->GetCheck())
	{
		m_wMask |= 0x08;
	}

	if(((CButton*)GetDlgItem(IDC_IN4))->GetCheck())
	{
		m_wMask |= 0x010;
	}
	if(((CButton*)GetDlgItem(IDC_IN5))->GetCheck())
	{
		m_wMask |= 0x020;
	}
	if(((CButton*)GetDlgItem(IDC_IN6))->GetCheck())
	{
		m_wMask |= 0x040;
	}
	if(((CButton*)GetDlgItem(IDC_IN7))->GetCheck())
	{
		m_wMask |= 0x080;
	}
	
	if(((CButton*)GetDlgItem(IDC_IN8))->GetCheck())
	{
		m_wMask |= 0x0100;
	}
	if(((CButton*)GetDlgItem(IDC_IN9))->GetCheck())
	{
		m_wMask |= 0x0200;
	}
	if(((CButton*)GetDlgItem(IDC_IN10))->GetCheck())
	{
		m_wMask |= 0x0400;
	}
	if(((CButton*)GetDlgItem(IDC_IN11))->GetCheck())
	{
		m_wMask |= 0x0800;
	}

	if(((CButton*)GetDlgItem(IDC_IN12))->GetCheck())
	{
		m_wMask |= 0x1000;
	}
	if(((CButton*)GetDlgItem(IDC_IN13))->GetCheck())
	{
		m_wMask |= 0x2000;
	}
	if(((CButton*)GetDlgItem(IDC_IN14))->GetCheck())
	{
		m_wMask |= 0x4000;
	}
	if(((CButton*)GetDlgItem(IDC_IN15))->GetCheck())
	{
		m_wMask |= 0x8000;
	}

	CDialog::OnOK();
}
