
#include "stdafx.h"
#include "PenboxBar.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_LIST_1	1

/////////////////////////////////////////////////////////////////////////////
// CPenboxBar

CPenboxBar::CPenboxBar()
{
}

CPenboxBar::~CPenboxBar()
{
}


BEGIN_MESSAGE_MAP(CPenboxBar, CDockablePane)
	//{{AFX_MSG_MAP(CPenboxBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
 	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPenboxBar message handlers

int CPenboxBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_wndPenbox.Create (IDD_DIALOG_PENBOX, this);
	m_wndPenbox.ShowWindow( SW_SHOW );	 
	  
	return 0;
}

void CPenboxBar::OnSize(UINT nType, int cx, int cy) 
{
	CDockablePane::OnSize(nType, cx, cy);

	AdjustLayout();
	
}
void CPenboxBar::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rc;
	GetClientRect(rc);
 
	// 选项卡控件应覆盖整个工作区: 
	m_wndPenbox.SetWindowPos(NULL, rc.left + 1, rc.top + 1, rc.Width() - 2, rc.Height() - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}
void CPenboxBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting 
}

void CPenboxBar::OnSetFocus(CWnd* pOldWnd) 
{
	CDockablePane::OnSetFocus(pOldWnd); 
}


void CPenboxBar::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection); 
}
 