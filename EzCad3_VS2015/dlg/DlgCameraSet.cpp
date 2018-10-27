// D:\项目\EzCad3_VS2015\EzCad3_VS2015\dlg\DlgCameraSet.cpp : 实现文件
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "..\EzCad3_VS2015\dlg\DlgCameraSet.h"
#include "afxdialogex.h"
#include "QGlobal.h"
#include "Ezcaddef.h"
// CDlgCameraSet 对话框

IMPLEMENT_DYNAMIC(CDlgCameraSet, CDialogEx)

CDlgCameraSet::CDlgCameraSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CAMERASET, pParent)
{
	m_bMirrorX = FALSE;
	m_bMirrorY = FALSE;
	m_dX = 0.0;
	m_dY = 0.0;
	m_dH = 0.0;
	m_dW = 0.0;
	m_nExpo = 100;
}

CDlgCameraSet::~CDlgCameraSet()
{
}

void CDlgCameraSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Check(pDX, IDC_CHECK_MIRRORX, m_bMirrorX);
	DDX_Check(pDX, IDC_CHECK_MIRRORY, m_bMirrorY);
	DDX_Text(pDX, IDC_EDIT_LB_X, m_dX);
	DDX_Text(pDX, IDC_EDIT_LB_Y, m_dY);
	DDX_Text(pDX, IDC_EDIT_H, m_dH);
	DDX_Text(pDX, IDC_EDIT_W, m_dW);
	DDX_Control(pDX, IDC_SLIDER_EXPO, m_sliderExpo);
}


BEGIN_MESSAGE_MAP(CDlgCameraSet, CDialogEx) 
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_EXPO, OnReleasedcaptureSlider1)
	ON_BN_CLICKED(IDOK, &CDlgCameraSet::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgCameraSet 消息处理程序

 


void CDlgCameraSet::OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	m_nExpo = m_sliderExpo.GetPos();

	CString str;
	str.Format(_T("%d"), m_nExpo);
	SetDlgItemText(IDC_STATIC_EXPO2, str);

	UpdateData(FALSE);

	*pResult = 0;
}


BOOL CDlgCameraSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString strName = E3_GetCameraName();
	if (strName.GetLength() > 5 && strName.Left(5) == _T("MV-CA"))
	{
	//	AfxMessageBox(_T("OK"));

		m_sliderExpo.SetRange(0, 10000);
	}
	else
	{
	//	AfxMessageBox(strName);

		m_sliderExpo.SetRange(0, 255);
	}

	m_sliderExpo.SetPos(m_nExpo);

	SetWindowText(QGlobal::gf_Str(_T("CAMERA"), _T("Camera")));

	SetDlgItemText(IDC_CHECK_MIRRORX, QGlobal::gf_Str(_T("WIDTH"), _T("Mirror"))+_T(" X"));
	SetDlgItemText(IDC_CHECK_MIRRORY, QGlobal::gf_Str(_T("WIDTH"), _T("Mirror")) + _T(" Y"));


	GetDlgItem(IDC_STATIC_LEFTCORNER)->SetWindowText(QGlobal::gf_Str(_T("LB_CORNER"), _T("Left bottom corner")));
	GetDlgItem(IDC_STATIC_SIZE)->SetWindowText(QGlobal::gf_Str(_T("SIZE"), _T("Size")));
	 

	SetDlgItemText(IDC_STATIC_H, QGlobal::gf_Str(_T("HEIGHT"), _T("Height")));
	SetDlgItemText(IDC_STATIC_W, QGlobal::gf_Str(_T("WIDTH"), _T("Width")));

	SetDlgItemText(IDC_STATIC_EXPO, QGlobal::gf_Str(_T("EXPOSURE"), _T("Exposure")));

	CString str;
	str.Format(_T("%d"), m_nExpo);
	SetDlgItemText(IDC_STATIC_EXPO2, str);
		

	SetDlgItemText(IDC_STATIC_UNIT1, QGlobal::gf_GetUnitStr());
	SetDlgItemText(IDC_STATIC_UNIT2, QGlobal::gf_GetUnitStr());
	SetDlgItemText(IDC_STATIC_UNIT3, QGlobal::gf_GetUnitStr());
	SetDlgItemText(IDC_STATIC_UNIT4, QGlobal::gf_GetUnitStr());

	GetDlgItem(IDOK)->SetWindowText(QGlobal::gf_Str(_T("IDOK"), _T("&OK")));
	GetDlgItem(IDCANCEL)->SetWindowText(QGlobal::gf_Str(_T("IDCANCEL"), _T("&Cancel")));
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgCameraSet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
