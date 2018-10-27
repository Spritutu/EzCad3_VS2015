

#include "stdafx.h"

#include "EntPropBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_LIST_1	1

/////////////////////////////////////////////////////////////////////////////
// CEntPropBar

CEntPropBar::CEntPropBar()
{
}

CEntPropBar::~CEntPropBar()
{
}


BEGIN_MESSAGE_MAP(CEntPropBar, CDockablePane)
	//{{AFX_MSG_MAP(CEntPropBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CEntPropBar message handlers
BOOL  CEntPropBar::DockToWindow(CDockablePane* pTargetWindow, DWORD dwAlignment, LPCRECT lpRect)
{
	return CDockablePane::DockToWindow(pTargetWindow, dwAlignment, lpRect);
}

BOOL CEntPropBar::DockToFrameWindow(DWORD dwAlignment, LPCRECT lpRect, DWORD dwDockFlags, CBasePane* pRelativeBar, int nRelativeIndex, BOOL bOuterEdge)
{
	return CDockablePane::DockToFrameWindow(dwAlignment, lpRect, dwDockFlags, pRelativeBar, nRelativeIndex, bOuterEdge);

}
int CEntPropBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

#ifdef  ENABLE_ENTBASE
	
		//m_wndEntBase.CreateEx(CWnd::FromHandle(m_hWnd));
	m_wndEntBase.Create (IDD_DIALOG_ENTBASE, this);
	
	  m_wndEntBase.ShowWindow( SW_SHOW );	
#endif

	AdjustLayout(); 
	return 0;
}

void CEntPropBar::OnSize(UINT nType, int cx, int cy) 
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CEntPropBar::AdjustLayout() 
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

#ifdef  ENABLE_ENTBASE
	CRect rc;
	GetClientRect(rc);
 	m_wndEntBase.SetWindowPos(NULL,rc.left + 1, rc.top + 1,rc.Width() - 2, rc.Height () - 2,SWP_NOACTIVATE | SWP_NOZORDER); 
#endif 
}

void CEntPropBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
#ifdef  ENABLE_ENTBASE
	CRect rectTree;
	m_wndEntBase.GetWindowRect (rectTree);
	
	ScreenToClient (rectTree);

	rectTree.InflateRect (1, 1);
	dc.Draw3dRect (rectTree, ::GetSysColor (COLOR_3DSHADOW), ::GetSysColor (COLOR_3DSHADOW));
#endif
}

void CEntPropBar::OnSetFocus(CWnd* pOldWnd) 
{
	CDockablePane::OnSetFocus(pOldWnd);
#ifdef  ENABLE_ENTBASE
	m_wndEntBase.SetFocus ();
#endif	 
}
