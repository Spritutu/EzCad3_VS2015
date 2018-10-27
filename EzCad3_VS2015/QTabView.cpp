#include "stdafx.h"
#include "QTabView.h"
#include "QGlobal.h"
#include "Mainfrm.h"
#include "QEntView.h"
#include "SysParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
BOOL CQMFCTabCtrl::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_LBUTTONDBLCLK)
	{
		CPoint point;
		point.x =LOWORD(pMsg->lParam);
		point.y =HIWORD(pMsg->lParam);
		for (int i = 0; i < m_iTabsNum; i ++)
		{
			CMFCTabInfo* pTab = (CMFCTabInfo*) m_arTabs [i];
			ASSERT_VALID(pTab);		
			
			if (pTab->GetRect().PtInRect(point))
			{
				this->GetParent()->SendMessage(WM_USER_DBCLICK_TAB,i,0);
				return TRUE;
			}
		}
	}			
	return CMFCTabCtrl::PreTranslateMessage(pMsg);
}

IMPLEMENT_DYNCREATE(CQTabView, CView)

CQTabView::CQTabView()
{
	m_bIsReady = FALSE;
	m_nFirstActiveTab = -1;
}

CQTabView::~CQTabView()
{
}

BEGIN_MESSAGE_MAP(CQTabView, CView)
	//{{AFX_MSG_MAP(CQTabView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEACTIVATE()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(AFX_WM_CHANGE_ACTIVE_TAB, OnChangeActiveTab)	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQTabView drawing

void CQTabView::OnDraw(CDC* /*pDC*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CQTabView diagnostics

#ifdef _DEBUG
void CQTabView::AssertValid() const
{
	CView::AssertValid();
}

void CQTabView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CQTabView message handlers

int CQTabView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	// Create tabs window:
  //if (!m_wndTabs.Create( IsScrollBar () ? CBCGPTabWnd::STYLE_FLAT_SHARED_HORZ_SCROLL : CBCGPTabWnd::STYLE_FLAT,rectDummy, this, 1))
//	if (!m_wndTabs.Create( IsScrollBar () ? CMFCTabCtrl::STYLE_FLAT_SHARED_HORZ_SCROLL : CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	if (!m_wndTabs.Create(IsScrollBar() ? CMFCTabCtrl::STYLE_FLAT_SHARED_HORZ_SCROLL : CMFCTabCtrl::STYLE_3D_VS2005, rectDummy, this, 1))
 	{
	//	TRACE0("Failed to create tab window\n");
		return -1;      // fail to create
	}

	//m_wndTabs.SetFlatFrame ();
	m_wndTabs.SetTabBorderSize(0);
	//m_wndTabs.SetTabBorderSize (20);
	m_wndTabs.AutoDestroyWindow (FALSE);
	return 0;
}

//************************************************************************************
void CQTabView::OnSize(UINT nType, int cx, int cy) 
{
	//TRACE0("CQTabView::OnSize\n");
	CView::OnSize(nType, cx, cy);
	
	// Tab control should cover a whole client area:
	//m_wndTabs.SetWindowPos (NULL, -1, -1, cx + 1, cy + 3,SWP_NOACTIVATE | SWP_NOZORDER);	
//	TRACE0("m_wndTabs.SetWindowPos\n");
	m_wndTabs.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE );
}

//************************************************************************************
int CQTabView::AddView (CRuntimeClass* pViewClass, const CString& strViewLabel,  int iIndex /*= -1*/, CCreateContext* pContext/* = NULL*/)
{
	ASSERT_VALID (this);
	ASSERT (pViewClass != NULL);
	ASSERT (pViewClass->IsDerivedFrom (RUNTIME_CLASS (CView)));

	CView* pView = DYNAMIC_DOWNCAST (CView, pViewClass->CreateObject ());
	ASSERT_VALID (pView);

	if (!pView->Create (NULL, _T(""), WS_CHILD | WS_VISIBLE,CRect (0, 0, 0, 0), &m_wndTabs, (UINT) -1, pContext))
	{
		TRACE1("CQTabView:Failed to create view '%s'\n", pViewClass->m_lpszClassName);
		return -1;
	}

	CDocument* pDoc = GetDocument ();
	if (pDoc != NULL)
	{
		ASSERT_VALID (pDoc);

		BOOL bFound = FALSE;
		for (POSITION pos = pDoc->GetFirstViewPosition (); !bFound && pos != NULL;)
		{
			if (pDoc->GetNextView (pos) == pView)
			{
				bFound = TRUE;
			}
		}

		if (!bFound)
		{
			pDoc->AddView (pView);
		}
	}
	((CQEntView*)pView)->ShowRuler(gf_GetSysParam()->GetParamInt(INT_PARAM_SHOWRULER));
	m_wndTabs.InsertTab (pView, strViewLabel, iIndex);

	int nTabs = m_wndTabs.GetTabsNum ();
	return nTabs - 1;
}

//************************************************************************************
LRESULT CQTabView::OnChangeActiveTab (WPARAM wp, LPARAM)
{
	if (!m_bIsReady)
	{
		m_nFirstActiveTab = (int) wp;
		return 0;
	}
	 
		CFrameWnd* pFrame =gf_GetMainFrame();
		if(pFrame==NULL)
		{
			return 0;
		}
ASSERT_VALID (pFrame);

	int iTabNum = (int) wp;
	if (iTabNum >= 0)
	{
		CView* pView = DYNAMIC_DOWNCAST (CView, m_wndTabs.GetTabWnd (iTabNum));
		ASSERT_VALID (pView);

		pFrame->SetActiveView (pView);

		OnActivateView (pView);
	}
	else
	{
		pFrame->SetActiveView (NULL);

		OnActivateView (NULL);
	}

	return 0; 
}

//************************************************************************************
int CQTabView::FindTab (HWND hWndView) const
{
	ASSERT_VALID (this);

	for (int i = 0; i < m_wndTabs.GetTabsNum (); i++)
	{
		if (m_wndTabs.GetTabWnd (i)->GetSafeHwnd () == hWndView)
		{
			return i;
		}
	}
	return -1;
}

//************************************************************************************
BOOL CQTabView::RemoveView (int iTabNum)
{
	ASSERT_VALID (this);
	return m_wndTabs.RemoveTab (iTabNum);
}

//************************************************************************************
BOOL CQTabView::SetActiveView (int iTabNum)
{
	//TRACE0("CQTabView::SetActiveView\n");
	ASSERT_VALID (this);
	return m_wndTabs.SetActiveTab (iTabNum);
}

//************************************************************************************
CView* CQTabView::GetActiveView () const
{
	ASSERT_VALID (this);

	int iActiveTab = m_wndTabs.GetActiveTab ();
	if (iActiveTab < 0)
	{
		return NULL;
	}

	return DYNAMIC_DOWNCAST (CView, m_wndTabs.GetTabWnd (iActiveTab));
}

int CQTabView::GetViewCount()
{
	ASSERT_VALID (this);
	return m_wndTabs.GetTabsNum();
}
	
CView* CQTabView::GetView(int iTabNum) 
{
	ASSERT_VALID (this);
	return DYNAMIC_DOWNCAST (CView, m_wndTabs.GetTabWnd (iTabNum));
}

//****************************************************************************************
class CInternalTabView : public CView
{
	friend class CQTabView;
};

int CQTabView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
	//TRACE0("CQTabView::OnMouseActivate\n");
 	CView* pCurrView = GetActiveView ();
//	if (pCurrView == NULL)
	{
		return CView::OnMouseActivate (pDesktopWnd, nHitTest, message);
	}

	int nResult = CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
	if (nResult == MA_NOACTIVATE || nResult == MA_NOACTIVATEANDEAT)
		return nResult;   // frame does not want to activate

	//CFrameWnd* pParentFrame = BCGPGetParentFrame(this);
	CFrameWnd* pParentFrame =gf_GetMainFrame();
	if (pParentFrame != NULL)
	{
		// eat it if this will cause activation
		ASSERT(pParentFrame == pDesktopWnd || pDesktopWnd->IsChild(pParentFrame));

		// either re-activate the current view, or set this view to be active
		CView* pView = pParentFrame->GetActiveView();
		HWND hWndFocus = ::GetFocus();
		if (pView == pCurrView &&
			pCurrView->m_hWnd != hWndFocus && !::IsChild(pCurrView->m_hWnd, hWndFocus))
		{
			// re-activate this view
			((CInternalTabView*)pCurrView)->OnActivateView(TRUE, pCurrView, pCurrView);
		}
		else
		{
			// activate this view
			pParentFrame->SetActiveView(pCurrView);
		}
	}

	return nResult;
}

//****************************************************************************************
void CQTabView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	m_bIsReady = TRUE;
	OnChangeActiveTab (m_nFirstActiveTab, 0);
}

void CQTabView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonDblClk(nFlags, point);
}