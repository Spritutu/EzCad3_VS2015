// D:\项目\EzCad3_VS2015\EzCad3_VS2015\dlg\DlgSelMarker.cpp : 实现文件
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "DlgSelMarker.h"
#include "afxdialogex.h"
#include "QGlobal.h"

// CDlgSelMarker 对话框

IMPLEMENT_DYNAMIC(CDlgSelMarker, CDialogEx)

CDlgSelMarker::CDlgSelMarker(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SELMARKER, pParent)
{
	for (int i = 0; i < 8; i++)
	{
		 m_markerBuf[i] = NULL;
	}
	m_nSelIndex = 0;
}

CDlgSelMarker::~CDlgSelMarker()
{
}

void CDlgSelMarker::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MARKER, m_listboxMarker);
}


BEGIN_MESSAGE_MAP(CDlgSelMarker, CDialogEx)

	
	ON_LBN_SELCHANGE(IDC_LIST_MARKER, &CDlgSelMarker::OnLbnSelchangeListMarker)
	ON_LBN_DBLCLK(IDC_LIST_MARKER, &CDlgSelMarker::OnLbnDblclkListMarker)
	ON_BN_CLICKED(IDOK, &CDlgSelMarker::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSelMarker 消息处理程序


void CDlgSelMarker::OnLbnSelchangeListMarker()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgSelMarker::OnLbnDblclkListMarker()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedOk();
}


BOOL CDlgSelMarker::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(QGlobal::gf_Str(_T("PLSCHOOSECARD"), _T("Please choose the card you want to use")));
	GetDlgItem(IDOK)->SetWindowText(QGlobal::gf_Str(_T("IDOK"), _T("&OK")));
	GetDlgItem(IDCANCEL)->SetWindowText(QGlobal::gf_Str(_T("IDCANCEL"), _T("&Cancel")));


	CString str;
	int nSn;
	for (int i = 0; i < 8; i++)
	{
		if (m_markerBuf[i] != NULL)
		{
			nSn = E3_MarkerGetSN(m_markerBuf[i]);
			str.Format(_T("%d:SN=%d"),i+1, nSn);
			m_listboxMarker.AddString(str);
		}
		else
		{
			break;
		}
	}  
	m_listboxMarker.SetCurSel(m_nSelIndex);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgSelMarker::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nSelIndex = m_listboxMarker.GetCurSel( );
	CDialogEx::OnOK();
}
