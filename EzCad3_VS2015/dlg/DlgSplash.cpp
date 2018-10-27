// dlgsplash.cpp : implementation file
//
// 修改纪录
//LWJ:2005-5-13  缩放窗口使其 Client Area 与位图尺寸相同

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "dlgsplash.h"
#include "qGlobal.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSplash dialog


CDlgSplash::CDlgSplash(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSplash::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSplash)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	QGlobal::Log(_T("CDlgSplash::CDlgSplash 1"));
}


void CDlgSplash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSplash)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSplash, CDialog)
	//{{AFX_MSG_MAP(CDlgSplash)
	ON_WM_TIMER()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSplash message handlers

BOOL CDlgSplash::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(LoadBitmap(QGlobal::gf_GetWorkPath()+_T("res\\Logo.bmp")))
	{
		return TRUE;
	}
	if(!LoadBitmap(QGlobal::gf_GetWorkPath()+_T("Logo.bmp")))
	{
		//m_bmpView.LoadBitmap(IDB_BITMAP_SPLASH);
	} 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDlgSplash::LoadBitmap( CString bmpfile )
{	
	HANDLE handle = LoadImage(NULL,bmpfile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	if(handle == NULL)
	{
		return FALSE;
	}
	
	HGDIOBJ hObject = m_bmpView.Detach();
	if(hObject != NULL)
	{
		DeleteObject(hObject);
	}
	
	return m_bmpView.Attach( handle );
}

void CDlgSplash::OnPaint()
{  	
 	CPaintDC dc(this); // device context for painting

		CRect rectClient;
		GetClientRect(&rectClient);
		BITMAP bm;
		m_bmpView.GetBitmap(&bm);
		
		CSize sizeBg(bm.bmWidth,bm.bmHeight);
		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap *pbmOld = dcMem.SelectObject(&m_bmpView);
		
		::SetStretchBltMode(dc, COLORONCOLOR);	
		
		dc.StretchBlt(rectClient.left,rectClient.top,rectClient.Width (),rectClient.Height (),&dcMem,0,0,sizeBg.cx,sizeBg.cy,SRCCOPY);
	
		dcMem.SelectObject(pbmOld);
		dcMem.DeleteDC();
 
}

void CDlgSplash::ShowSplash(CWnd* pParent)
{	 
	if (Create(CDlgSplash::IDD,pParent))
	{
		if(m_bmpView.m_hObject!=NULL)
		{
 		//resize
		BITMAP bm;
		m_bmpView.GetBitmap(&bm);
		SetWindowPos(NULL,0,0,bm.bmWidth,bm.bmHeight,SWP_HIDEWINDOW);
 		CenterWindow();
		ShowWindow(SW_SHOW);
		UpdateWindow();
		}
	}
}

void CDlgSplash::HideSplash()
{
	if (GetSafeHwnd() != NULL)
	{
		SetTimer(1, 250, NULL);
	}
}

void CDlgSplash::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	QGlobal::Log(_T("CDlgSplash::OnTimer 1"));

	KillTimer(1);
	DestroyWindow();

	QGlobal::Log(_T("CDlgSplash::OnTimer 2"));
	if(AfxGetMainWnd()!=NULL)
	{
		AfxGetMainWnd()->UpdateWindow();
			QGlobal::Log(_T("CDlgSplash::OnTimer 3"));
	}
		QGlobal::Log(_T("CDlgSplash::OnTimer 4"));
	CDialog::OnTimer(nIDEvent);
}
