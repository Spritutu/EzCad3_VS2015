
#include "stdafx.h"
#include "..\Ezcad3View.h"
#include "QEntLayerView.h"
#include "..\resource.h"
#include "QGlobal.h"
#include "QIniFile.h" 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CQEntLayerView
#define TIMER_WHEEL 367 
IMPLEMENT_DYNCREATE(CQEntLayerView, CQEntView)

CQEntLayerView::CQEntLayerView()
{
	m_pEntLayer=NULL;

	if (E3_GetCmdMgr() != NULL)
	{
	 	SetEntMgr(E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr()));
		SetCmdMgr(E3_GetCmdMgr());
	}	  

	m_bMouseWheelInv = FALSE;

	{
		CQIniFile qini;
		CString  strFile = QGlobal::gf_GetParamPath() + _T("Custom.ini");
		qini.SetPath(strFile);
		if (qini.ReadFile())
		{
			CString str = qini.GetValue(_T("PARAM"), _T("MOUSEWHEELINV"));
			if (str.GetLength() > 0)
			{
				m_bMouseWheelInv = QGlobal::ATOI(str)==0?FALSE:TRUE;
			}
		}
	}
}

CQEntLayerView::~CQEntLayerView()
{
	
}


BEGIN_MESSAGE_MAP(CQEntLayerView, CQEntView)
	//{{AFX_MSG_MAP(CQEntLayerView)
	ON_WM_DESTROY()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_HSCROLL()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQEntLayerView drawing
void CQEntLayerView::OnDestroy()
{
	KillTimer(TIMER_WHEEL);
	CQEntView::OnDestroy();
}
void CQEntLayerView::OnDraw(CDC* pDC)
{
	CQEntView::OnDraw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CQEntLayerView diagnostics

#ifdef _DEBUG
void CQEntLayerView::AssertValid() const
{
	CQEntView::AssertValid();
}

void CQEntLayerView::Dump(CDumpContext& dc) const
{
	CQEntView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CQEntLayerView message handlers

void CQEntLayerView::OnInitialUpdate() 
{
	CQEntView::OnInitialUpdate();

	
	//SetScrollSizes (MM_TEXT, CSize (1000, 1000));

	CMFCTabCtrl* pTabWnd =(CMFCTabCtrl*)GetParent ();
	ASSERT_VALID (pTabWnd);

	pTabWnd->SynchronizeScrollBar ();


	SetTimer(TIMER_WHEEL, 500, NULL); 
}

void CQEntLayerView::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
	CQEntView::OnWindowPosChanging(lpwndpos);
	
	// Hide horizontal scrollbar:
	ShowScrollBar (SB_HORZ, FALSE);
	ModifyStyle (WS_HSCROLL, 0, SWP_DRAWFRAME);
}

void CQEntLayerView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* /*pScrollBar*/) 
{
	CMFCTabCtrl* pTabWnd =(CMFCTabCtrl*)GetParent ();
	ASSERT_VALID (pTabWnd);

	CQEntView::OnHScroll(nSBCode, nPos, pTabWnd->GetScrollBar ());
}

CScrollBar* CQEntLayerView::GetScrollBarCtrl(int nBar) const
{
	if (nBar == SB_HORZ)
	{
		CMFCTabCtrl* pTabWnd =(CMFCTabCtrl*)GetParent ();
	ASSERT_VALID (pTabWnd);

		return pTabWnd->GetScrollBar ();
	}
	
	return CQEntView::GetScrollBarCtrl(nBar);
}

BOOL CQEntLayerView::OnEraseBkgnd(CDC*  pDC ) 
{ 
	 return CQEntView::OnEraseBkgnd(pDC);
}

//得到安全有效的对象根，有些情况下当前根已经被删除
PEntity CQEntLayerView::GetSafeLayer()
{
	PEntMgr  pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if(pEM==NULL)
	{
		return NULL;
	}
	if(  m_pEntLayer==NULL)
	{
		return NULL;
	}
	//从数据管理器中检查是当前指定层是否有效
	if (E3_EntMgrIsLayerExist(pEM,m_pEntLayer))
	{
		return m_pEntLayer;
	}
	return NULL;
}

void CQEntLayerView::SetLayer(PEntity pEnt)
{
	m_pEntLayer=pEnt;
}

void CQEntLayerView::OnSize(UINT nType, int cx, int cy)
{
	//TRACE(" CQEntLayerView::OnSize\n");

	CQEntView::OnSize(nType, cx, cy);

}

void CQEntLayerView::OnActivate()
{ 
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if(pEM==NULL)
	{
		return;
	}

	PEntity pCurLayer = CQEntLayerView::GetSafeLayer();
	if(pCurLayer==NULL)
	{
		return ;
	}

	CQEntView::OnActivateLayer(pCurLayer); 
}

void CQEntLayerView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CQEntView::OnRButtonDown(nFlags, point);

	CEntMgr* pEM = (CEntMgr*)E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}
	if ( !m_bOnRButtonDownHandle)
	{	 
		int subCmd;
		if (E3_CmdMgrGetCurCmd(E3_GetCmdMgr(),  subCmd) == "PICK")
		{
			CMenu RightMenu;
			RightMenu.LoadMenu(IDR_MENU_PICK);

			CMenu* pMenu = RightMenu.GetSubMenu(0);
			if (pMenu == NULL)
				return  ; 
		 
			//CCommand* LastRunCommand[2];
			//int subCmd[2];
			//E3_GetCmdMgr()->GetLastRunCommand(LastRunCommand, subCmd);
			//if (LastRunCommand[0] != NULL)
			//{
			//	pMenu->InsertMenu(0, MF_SEPARATOR | MF_BYPOSITION);

			//	//CString item = "重复命令(&2): ";
			//	CString item = QGlobal::gf_Str(_T("CMD_REPEAT2"), _T("Repeat command2")) + _T(":");
			//	if (LastRunCommand[1] != NULL)
			//	{
			//		item += LastRunCommand[1]->GetSubCmdName(subCmd[1]);
			//		pMenu->InsertMenu(0, MF_STRING | MF_BYPOSITION, ID_USER_RUN_LAST_CMD2, item);
			//	}

			//	//item = "重复命令(&1): ";
			//	item = QGlobal::gf_Str(_T("CMD_REPEAT1"), _T("Repeat command1")) + _T(":");
			//	item += LastRunCommand[0]->GetSubCmdName(subCmd[0]);
			//	pMenu->InsertMenu(0, MF_STRING | MF_BYPOSITION, ID_USER_RUN_LAST_CMD, item);
			//}

			pMenu->ModifyMenu(ID_EDIT_CUT, MF_BYCOMMAND, ID_EDIT_CUT, QGlobal::gf_Str(_T("MENU_EDIT_CUT"), _T("Cu&t\tCtrl+X")));
			pMenu->ModifyMenu(ID_EDIT_COPY, MF_BYCOMMAND, ID_EDIT_COPY, QGlobal::gf_Str(_T("MENU_EDIT_COPY"), _T("&Copy\tCtrl+C")));
			pMenu->ModifyMenu(ID_EDIT_PASTE, MF_BYCOMMAND, ID_EDIT_PASTE, QGlobal::gf_Str(_T("MENU_EDIT_PASTE"), _T("&Paste\tCtrl+V")));


			pMenu->ModifyMenu(ID_VIEW_SNAPGRID, MF_BYCOMMAND, ID_VIEW_SNAPGRID, QGlobal::gf_Str(_T("MENU_VIEW_SNAPGRID"), _T("Snap G&rid\tF7")));
			pMenu->ModifyMenu(ID_VIEW_SNAPGUILDLINE, MF_BYCOMMAND, ID_VIEW_SNAPGUILDLINE, QGlobal::gf_Str(_T("MENU_VIEW_SNAPGUILD"), _T("Snap &Guild Line\tF8")));
			pMenu->ModifyMenu(ID_VIEW_SNAPOBJECT, MF_BYCOMMAND, ID_VIEW_SNAPOBJECT, QGlobal::gf_Str(_T("MENU_VIEW_SNAPOBJECT"), _T("Snap &Entity\tF9")));


			if (E3_IsCameraOpen()  )
			{ 
				pMenu->InsertMenu(0, MF_STRING, IDB_MENU_CAMERA, QGlobal::gf_Str(_T("CAMERA"), _T("Camera")));
			}


			gf_GetMainFrame()->GetActiveView()->ClientToScreen(&point);

			pMenu->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y, gf_GetMainFrame());
			return;
		}
		else if (E3_CmdMgrGetCurCmd(E3_GetCmdMgr(), subCmd) == "DRAW")
		{
			CMenu RightMenu;
			RightMenu.LoadMenu(IDR_MENU_DRAW);

			CMenu* pMenu = RightMenu.GetSubMenu(0);
			if (pMenu == NULL)
				return  ;

			pMenu->ModifyMenu(ID_DRAW_COOR, MF_BYCOMMAND, ID_DRAW_COOR, QGlobal::gf_Str(_T("MENU_COOR"), _T("&Input coordinate")));
			pMenu->ModifyMenu(ID_DRAW_CLOSE, MF_BYCOMMAND, ID_DRAW_CLOSE, QGlobal::gf_Str(_T("MENU_CLOSEFINISH"), _T("&Close and finish")));
			pMenu->ModifyMenu(ID_DRAW_FINISH, MF_BYCOMMAND, ID_DRAW_FINISH, QGlobal::gf_Str(_T("MENU_FINISH"), _T("&Finish")));

			if (subCmd == SUBCMD_DRAW_POINT)
			{
				pMenu->DeleteMenu(ID_DRAW_CLOSE, MF_BYCOMMAND);
			}
			else if (subCmd == SUBCMD_DRAW_BEZIER)
			{
				pMenu->DeleteMenu(ID_DRAW_COOR, MF_BYCOMMAND);
			}

			gf_GetMainFrame()->GetActiveView()->ClientToScreen(&point);
			pMenu->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y, gf_GetMainFrame());
		}
		else if (E3_CmdMgrGetCurCmd(E3_GetCmdMgr(), subCmd) == "RESORT")
		{
			CMenu RightMenu;
			RightMenu.LoadMenu(IDR_MENU_SORT);

			CMenu* pMenu = RightMenu.GetSubMenu(0);
			if (pMenu == NULL)
				return  ;

			pMenu->ModifyMenu(ID_RESORT_SORTBYX, MF_BYCOMMAND, ID_RESORT_SORTBYX, QGlobal::gf_Str(_T("MENU_SORT_BYX"), _T("Sort by X")));
			pMenu->ModifyMenu(ID_RESORT_SORTBYY, MF_BYCOMMAND, ID_RESORT_SORTBYY, QGlobal::gf_Str(_T("MENU_SORT_BYY"), _T("Sort by Y")));
			pMenu->ModifyMenu(ID_RESORT_SORTREVERSE, MF_BYCOMMAND, ID_RESORT_SORTREVERSE, QGlobal::gf_Str(_T("MENU_SORT_REVERSE"), _T("Sort reverse")));
			pMenu->ModifyMenu(ID_RESORT_FINISH, MF_BYCOMMAND, ID_RESORT_FINISH, QGlobal::gf_Str(_T("MENU_FINISH"), _T("Finish")));

			gf_GetMainFrame()->GetActiveView()->ClientToScreen(&point);

			pMenu->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y, gf_GetMainFrame());
			 
		}
	}
    
}

BOOL CQEntLayerView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bMouseWheelInv)
	{//反转
		zDelta = zDelta > 0 ? -1 : 1;
	}
	if (m_bShowOpenGLWnd)
	{
		if ( m_pDrawDC != NULL && !E3_DrawDCIsCaptureCursor(m_pDrawDC))
		{//滚轮放缩观察		
		//	TRACE("Wheel\n");
			if (zDelta > 0)
			{
				SetOpenGLScale(GetOpenGLScale() *  1.1);
			}
			else
			{
				SetOpenGLScale(GetOpenGLScale() *  0.9);
			}

			SetupProjectMatrix();
			Invalidate();
			return TRUE;
		}
	}
	else
	{
		if (m_pDrawDC != NULL && !E3_DrawDCIsCaptureCursor(m_pDrawDC))
		{//滚轮放缩观察		 
			if (E3_GetCmdMgr() != NULL)
			{
				m_nStartZoomWheelTick = ::GetTickCount();
				E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_WHEEL, zDelta);
				m_nStartZoomWheelTick = ::GetTickCount();
			}
			return TRUE;
		}
	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CQEntLayerView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_WHEEL && (int)::GetTickCount()>(m_nStartZoomWheelTick+500))
	{
		if (E3_GetCmdMgr() != NULL)
		{
			int subCmd;
			CString strCmd = E3_CmdMgrGetCurCmd(E3_GetCmdMgr(), subCmd);  
			if (strCmd == _T("ZOOM") && subCmd == SUBCMD_ZOOM_WHEEL)
			{
				E3_CmdMgrStopCurCmd(E3_GetCmdMgr());
			} 
		}
	}
}