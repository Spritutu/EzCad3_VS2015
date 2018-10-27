// D:\项目\EzCad3_VS2015\EzCad3_VS2015\dlg\DlgLayerParam.cpp : 实现文件
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "DlgLayerParam.h"
#include "afxdialogex.h"

#include "QGlobal.h"
#include "SysParam.h"

#include "..\MainFrm.h"

// CDlgLayerParam 对话框

IMPLEMENT_DYNAMIC(CDlgLayerParam, CDialogEx)

CDlgLayerParam::CDlgLayerParam(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LAYERPARAM, pParent)
{
	   m_wIoHigh=0;//输入IO条件为高的位
	   m_wIoLow=0;//输入IO条件为低的位
	   m_wStartOutputIoHigh = 0;//开始输出IO条件为高的位
	   m_wStartOutputIoLow = 0;//开始输出IO条件为低的位
	   m_wFinishOutputIoHigh = 0;//开始输出IO条件为高的位
	   m_wFinishOutputIoLow = 0;//开始输出IO条件为低的位 
	   m_nCount = 1;

	   m_nStartDelayMs=0;
	   m_nEndDelayMs=0;
	   m_bWaitForInput = FALSE;
}

CDlgLayerParam::~CDlgLayerParam()
{
}

void CDlgLayerParam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgLayerParam, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgLayerParam::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgLayerParam 消息处理程序


BOOL CDlgLayerParam::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(QGlobal::gf_Str(_T("LAYER"), _T("Layer")));
	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(QGlobal::gf_Str(_T("NAME"), _T("Name")));
	GetDlgItem(IDC_STATIC_COUNT)->SetWindowText(QGlobal::gf_Str(_T("COUNT"), _T("Count")));
	GetDlgItem(IDC_STATIC_DELAY1)->SetWindowText(QGlobal::gf_Str(_T("DELAY"), _T("Delay")));
	GetDlgItem(IDC_STATIC_DELAY2)->SetWindowText(QGlobal::gf_Str(_T("DELAY"), _T("Delay")));


	GetDlgItem(IDC_STATIC_DIGITALIO)->SetWindowText(QGlobal::gf_Str(_T("WAITFORINPUT"), _T("Wait for Input")));
	GetDlgItem(IDC_STATIC_STARTOUT)->SetWindowText(QGlobal::gf_Str(_T("OUTPUTWHENSTART"), _T("Output when start")));
	GetDlgItem(IDC_STATIC_STARTOUT2)->SetWindowText(QGlobal::gf_Str(_T("OUTPUTWHENFINISH"), _T("Output when finish")));
	GetDlgItem(IDC_CHECK_WAITFORINPUT)->SetWindowText(QGlobal::gf_Str(_T("WAITFORINPUT"), _T("Wait for Input")));
	
	GetDlgItem(IDOK)->SetWindowText(QGlobal::gf_Str(_T("IDOK"), _T("&OK")));
	GetDlgItem(IDCANCEL)->SetWindowText(QGlobal::gf_Str(_T("IDCANCEL"), _T("&Cancel")));


	GetDlgItem(IDC_EDIT_NAME)->SetWindowText(m_strName);

	((CButton*)GetDlgItem(IDC_CHECK_WAITFORINPUT))->SetCheck(m_bWaitForInput);
	
	WORD wIoMask = 0xFFFF;
#ifdef ENABLE_MARK
	CMainFrame* pMainWnd = (CMainFrame*)gf_GetMainFrame();
	if (pMainWnd->m_wndMark.GetMarker() != NULL)
	{
		wIoMask = E3_MarkerGetInputIoMask(pMainWnd->m_wndMark.GetMarker());
	}
#endif
	for (int i = 0; i<16; i++)
	{
		WORD io = 0x0001 << i;
		if (io & wIoMask)
		{
			GetDlgItem(IDC_IN0 + i)->EnableWindow(TRUE);
			if (m_wIoHigh & io)
			{
				((CButton*)GetDlgItem(IDC_IN0 + i))->SetCheck(1);
			}
			else if (m_wIoLow & io)
			{
				((CButton*)GetDlgItem(IDC_IN0 + i))->SetCheck(0);
			}
			else
			{
				((CButton*)GetDlgItem(IDC_IN0 + i))->SetCheck(2);
			}
		}
		else
		{
			((CButton*)GetDlgItem(IDC_IN0 + i))->SetCheck(2);
			GetDlgItem(IDC_IN0 + i)->EnableWindow(FALSE);
		}
	}

	
	WORD wOutputIoMask = 0xFFFF;
#ifdef ENABLE_MARK
	if (pMainWnd->m_wndMark.GetMarker() != NULL)
	{
		wOutputIoMask = E3_MarkerGetOutputIoMask(pMainWnd->m_wndMark.GetMarker());
	}
#endif
	for (int i = 0; i<16; i++)
	{
		WORD io = 0x0001 << i;
		if (io & wOutputIoMask)
		{
			GetDlgItem(IDC_IN16 + i)->EnableWindow(TRUE);
			if (m_wStartOutputIoHigh & io)
			{
				((CButton*)GetDlgItem(IDC_IN16 + i))->SetCheck(1);
			}
			else if (m_wStartOutputIoLow & io)
			{
				((CButton*)GetDlgItem(IDC_IN16 + i))->SetCheck(0);
			}
			else
			{
				((CButton*)GetDlgItem(IDC_IN16 + i))->SetCheck(2);
			}
		}
		else
		{
			((CButton*)GetDlgItem(IDC_IN16 + i))->SetCheck(2);
			GetDlgItem(IDC_IN16 + i)->EnableWindow(FALSE);
		}
	}

	for (int i = 0; i<16; i++)
	{
		WORD io = 0x0001 << i;
		if (io & wOutputIoMask)
		{
			GetDlgItem(IDC_IN32 + i)->EnableWindow(TRUE);
			if (m_wFinishOutputIoHigh & io)
			{
				((CButton*)GetDlgItem(IDC_IN32 + i))->SetCheck(1);
			}
			else if (m_wFinishOutputIoLow & io)
			{
				((CButton*)GetDlgItem(IDC_IN32 + i))->SetCheck(0);
			}
			else
			{
				((CButton*)GetDlgItem(IDC_IN32 + i))->SetCheck(2);
			}
		}
		else
		{
			((CButton*)GetDlgItem(IDC_IN32 + i))->SetCheck(2);
			GetDlgItem(IDC_IN32 + i)->EnableWindow(FALSE);
		}
	}

	CString str;
	str.Format(_T("%d"),m_nCount);
	GetDlgItem(IDC_EDIT_COUNT)->SetWindowText(str);

	str.Format(_T("%d"), m_nStartDelayMs);
	GetDlgItem(IDC_EDIT_DELAY1)->SetWindowText(str);
	str.Format(_T("%d"), m_nEndDelayMs);
	GetDlgItem(IDC_EDIT_DELAY2)->SetWindowText(str);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgLayerParam::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	WORD wIoMask = 0xFFFF;
	CMainFrame* pMainWnd = (CMainFrame*)gf_GetMainFrame();
#ifdef ENABLE_MARK
	if (pMainWnd->m_wndMark.GetMarker() != NULL)
	{
		wIoMask = E3_MarkerGetInputIoMask(pMainWnd->m_wndMark.GetMarker());
	}
#endif
	m_wIoHigh = 0;
	 m_wIoLow = 0;
	for (int i = 0; i<16; i++)
	{
		WORD io = 0x0001 << i;
		if (io & wIoMask)
		{
			int nCheck = ((CButton*)GetDlgItem(IDC_IN0 + i))->GetCheck();
			if (nCheck == 0)
			{
				m_wIoLow |= io;
			}
			else if (nCheck == 1)
			{
				m_wIoHigh |= io;
			}
		}
	}

	
	WORD wOutputIoMask = 0xFFFF;
#ifdef ENABLE_MARK
	if (pMainWnd->m_wndMark.GetMarker() != NULL)
	{
		wOutputIoMask = E3_MarkerGetOutputIoMask(pMainWnd->m_wndMark.GetMarker());
	}
#endif
	m_wStartOutputIoHigh = 0;
	m_wStartOutputIoLow = 0;
	for (int i = 0; i < 16; i++)
	{
		WORD io = 0x0001 << i;
		if (io & wOutputIoMask)
		{
			int nCheck = ((CButton*)GetDlgItem(IDC_IN16 + i))->GetCheck();
			if (nCheck == 0)
			{
				m_wStartOutputIoLow |= io;
			}
			else if (nCheck == 1)
			{
				m_wStartOutputIoHigh |= io;
			}
		}
	}


	m_wFinishOutputIoHigh = 0;
	m_wFinishOutputIoLow = 0;
	for (int i = 0; i < 16; i++)
	{
		WORD io = 0x0001 << i;
		if (io & wOutputIoMask)
		{
			int nCheck = ((CButton*)GetDlgItem(IDC_IN32 + i))->GetCheck();
			if (nCheck == 0)
			{
				m_wFinishOutputIoLow |= io;
			}
			else if (nCheck == 1)
			{
				m_wFinishOutputIoHigh |= io;
			}
		}
	}


	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(m_strName);

	CString str;
	GetDlgItem(IDC_EDIT_COUNT)->GetWindowText(str); 
	m_nCount = QGlobal::ATOI(str);
	if (m_nCount < 1)
	{
		m_nCount = 1;
	} 


	GetDlgItem(IDC_EDIT_DELAY1)->GetWindowText(str);
	m_nStartDelayMs = QGlobal::ATOI(str);
	if (m_nStartDelayMs < 0)
	{
		m_nStartDelayMs = 0;
	}

	GetDlgItem(IDC_EDIT_DELAY2)->GetWindowText(str);
	m_nEndDelayMs = QGlobal::ATOI(str);
	if (m_nEndDelayMs < 0)
	{
		m_nEndDelayMs = 0;
	}

	m_bWaitForInput = ((CButton*)GetDlgItem(IDC_CHECK_WAITFORINPUT))->GetCheck();

 
	CDialogEx::OnOK();
}
