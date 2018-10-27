
#include "stdafx.h"

#include "MarkWnd.h"
#include "..\Resource.h"
#include "..\MainFrm.h"
#include "..\EzCad3_VS2015.h"
#include "QGlobal.h" 
#include "usermessdef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CMarkWnd::CMarkWnd()
{

}

CMarkWnd::~CMarkWnd()
{
}

BEGIN_MESSAGE_MAP(CMarkWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()

	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 消息处理程序

void CMarkWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient,rectCombo;
	GetClientRect(rectClient);

	
	m_dlgMark.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CMarkWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

 
	m_dlgMark.Create(IDD_DIALOG_MARK, this);
 
	
	m_dlgMark.ShowWindow(SW_SHOW);


	AdjustLayout();


	return 0;
}

void CMarkWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

PMarker CMarkWnd::GetMarker()
{
	return m_dlgMark.GetMarker();
}

CSize CMarkWnd::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	CSize size = CDockablePane::CalcFixedLayout(bStretch, bHorz); 
	return  size;
}

int CMarkWnd::GetMinShowWidth()
{ 
	return m_dlgMark.GetMinShowWidth();
}