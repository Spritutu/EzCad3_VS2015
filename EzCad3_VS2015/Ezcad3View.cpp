
// Ezcad3View.cpp : CEzcad3View 类的实现
//

#include "stdafx.h"
#include "EzCad3_VS2015.h"

#include "Ezcad3Doc.h"
#include "Ezcad3View.h"
#include "QEntLayerView.h"
#include "QGlobal.h"
#include "usermessdef.h"
 #include "DlgLayerParam.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CEzcad3View* st_pCurEzcad3View=NULL;
CEzcad3View* gf_GetCurEzcad3View()
{
	return st_pCurEzcad3View;
}

// CEzcad3View

IMPLEMENT_DYNCREATE(CEzcad3View, CQTabView)

BEGIN_MESSAGE_MAP(CEzcad3View, CQTabView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEzcad3View::OnFilePrintPreview)
	ON_WM_CREATE()	
	ON_MESSAGE(WM_USER_CHANGEENTITY ,OnUserChangeEntity)	
	ON_MESSAGE(WM_USER_CHANGECURLAYER ,OnUserChangeCurLayer)
	ON_MESSAGE(WM_USER_DBCLICK_TAB ,OnUserDBClickTab)	
	ON_REGISTERED_MESSAGE(AFX_WM_ON_MOVE_TAB, OnMoveTab)
	ON_REGISTERED_MESSAGE(AFX_WM_CHANGE_ACTIVE_TAB, OnChangeActiveTab)
	ON_REGISTERED_MESSAGE(AFX_WM_CHANGING_ACTIVE_TAB, OnChangingActiveTab)
	 
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CEzcad3View 构造/析构

CEzcad3View::CEzcad3View()
{
	// TODO: 在此处添加构造代码

}

CEzcad3View::~CEzcad3View()
{
}

BOOL CEzcad3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CQTabView::PreCreateWindow(cs);
}

// CEzcad3View 绘制

void CEzcad3View::OnDraw(CDC* /*pDC*/)
{
	CEzcad3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CEzcad3View 打印


void CEzcad3View::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CEzcad3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CEzcad3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CEzcad3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CEzcad3View::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CEzcad3View::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CEzcad3View 诊断

#ifdef _DEBUG
void CEzcad3View::AssertValid() const
{
	CQTabView::AssertValid();
}

void CEzcad3View::Dump(CDumpContext& dc) const
{
	CQTabView::Dump(dc);
}

CEzcad3Doc* CEzcad3View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEzcad3Doc)));
	return (CEzcad3Doc*)m_pDocument;
}
#endif //_DEBUG


// CEzcad3View 消息处理程序
int CEzcad3View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CQTabView::OnCreate(lpCreateStruct) == -1)
		return -1;

	st_pCurEzcad3View = this;

//	QGlobal::gf_SetActiveView(this);

	//m_wndTabs.EnableAutoColor(TRUE);
	//m_wndTabs.ModifyTabStyle(CBCGPTabWnd::STYLE_3D_ONENOTE);

	// TODO:  在此添加您专用的创建代码
	if(E3_GetCmdMgr()!=NULL)
	{
		E3_CmdMgrAddEntityWnd(E3_GetCmdMgr(), this );//告诉命令管理器当前窗口需要接收系统消息
	}

	OnUserChangeEntity(0,0);
	return 0;
}
LRESULT CEzcad3View::OnUserDBClickTab(WPARAM wParam, LPARAM lParam)
{
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr()); 
 
	int nTab = (int)wParam;
	if(nTab>=0 && nTab<m_wndTabs.GetTabsNum() && pEM != NULL)
	{
		CQEntLayerView* pOldView = (CQEntLayerView*)m_wndTabs.GetTabWnd(nTab);
		ASSERT(pOldView->m_pEntLayer!=NULL);
		if(pOldView->m_pEntLayer!=NULL)
		{
			CDlgLayerParam dlg(this);
			dlg.m_nCount = E3_GetEntMarkCnt(pOldView->m_pEntLayer);
			dlg.m_strName = E3_GetEntName(pOldView->m_pEntLayer);
			E3_GetEntIoSet(pOldView->m_pEntLayer, dlg.m_wIoLow, dlg.m_wIoHigh);

			E3_GetEntLayerIoSet(pOldView->m_pEntLayer,dlg.m_wStartOutputIoLow, dlg.m_wStartOutputIoHigh, dlg.m_wFinishOutputIoLow, dlg.m_wFinishOutputIoHigh,dlg.m_nStartDelayMs,dlg.m_nEndDelayMs, dlg.m_bWaitForInput);
			 
			if (dlg.DoModal() == IDOK)
			{
				PEntity pLayer = E3_GetEntChildHead(pEM);
				while (pLayer != NULL)
				{
					if (pLayer != pOldView->m_pEntLayer && E3_GetEntName(pLayer) == dlg.m_strName)
					{
						AfxMessageBox(QGlobal::gf_Str(_T(" LAYSERNAMESAME"), _T("The Layer name is the same as other!")));
						return 0;
					}

					pLayer = E3_GetEntNext(pLayer);
				} 

				E3_EntMgrBeginUndo(pEM, QGlobal::gf_Str(_T("MODIFY"), _T("Modify")));
				E3_EntMgrUDModify(pEM, pOldView->m_pEntLayer);

				E3_SetEntIoSet(pOldView->m_pEntLayer, dlg.m_wIoLow, dlg.m_wIoHigh);
				E3_SetEntLayerIoSet(pOldView->m_pEntLayer, dlg.m_wStartOutputIoLow, dlg.m_wStartOutputIoHigh, dlg.m_wFinishOutputIoLow, dlg.m_wFinishOutputIoHigh, dlg.m_nStartDelayMs, dlg.m_nEndDelayMs,dlg.m_bWaitForInput);

				E3_SetEntName(pOldView->m_pEntLayer,dlg.m_strName);
				E3_SetEntMarkCnt(pOldView->m_pEntLayer, dlg.m_nCount);
				E3_EntMgrEndUndo(pEM);
			}
		}
	}	 
	return 0;
}

LRESULT CEzcad3View::OnUserChangeCurLayer(WPARAM wParam, LPARAM lParam)
{
//	TRACE0("CEzcad3View::OnUserChangeCurLayer\n");
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if(pEM==NULL)
	{
		return 0;
	} 

	PEntity pLayer = E3_EntMgrGetCurLayer(pEM);
	if(pLayer!=NULL)
	{
		for(int i=0;i<m_wndTabs.GetTabsNum();i++)
		{
			CQEntLayerView* pOldView = (CQEntLayerView*)m_wndTabs.GetTabWnd(i);
			if(pOldView->m_pEntLayer == pLayer)
			{
				SetActiveView(i); 
				return 0;
			}
		}		
	}
	return 0;
}

//接受数据库删除对象消息，更新列表显示
LRESULT CEzcad3View::OnUserChangeEntity(WPARAM wParam, LPARAM lParam)
{
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return 0;
	}

	CQEntLayerView* pSaveView = (CQEntLayerView*)GetActiveView();
	PEntity pSaveActiveEnt = NULL;
	if(pSaveView!=NULL)
	{
		pSaveActiveEnt = pSaveView->GetLayer();
	}

	if(m_wndTabs.GetTabsNum()< E3_GetEntChildCnt(pEM))
	{
		while(m_wndTabs.GetTabsNum()< E3_GetEntChildCnt(pEM))
		{			
			AddView (RUNTIME_CLASS(CQEntLayerView), _T(""));
		}
	}
	else if(m_wndTabs.GetTabsNum()>E3_GetEntChildCnt(pEM))
	{
		while(m_wndTabs.GetTabsNum()>E3_GetEntChildCnt(pEM))
		{
			CQEntLayerView* pOldView = (CQEntLayerView*)m_wndTabs.GetTabWnd(m_wndTabs.GetTabsNum()-1);

			RemoveView(m_wndTabs.GetTabsNum()-1);

			if(pOldView!=NULL)
			{
				pOldView->SetLayer(NULL);
				pOldView->DestroyWindow();
			}
		}
	}

	CString strLable;
	int nTab=0;
	int nSelTab=0;
	PEntity pEnt = E3_GetEntChildHead(pEM); 
	while(pEnt!=NULL)
	{
		m_wndTabs.GetTabLabel(nTab,strLable);
		if(E3_GetEntName(pEnt)!=strLable)
		{
			m_wndTabs.SetTabLabel(nTab, E3_GetEntName(pEnt));
		}

		CQEntLayerView* pLayerView = (CQEntLayerView*)m_wndTabs.GetTabWnd(nTab);
		if(pLayerView->GetLayer()!=pEnt)
		{
			pLayerView->SetLayer(pEnt);
		}

		if(pSaveActiveEnt==pEnt)
		{
			nSelTab = nTab;
		}

		nTab++;
		pEnt = E3_GetEntNext( pEnt );
	}
	
	if (m_wndTabs.GetTabsNum() > 0)
	{
		SetActiveView(nSelTab);
		CQEntLayerView* pLayerView = (CQEntLayerView*)m_wndTabs.GetTabWnd(nSelTab);
		if (pLayerView != NULL)
		{
			OnActivateView(pLayerView);
		}
	}
	return 0;
}


PEntity CEzcad3View::GetActiveLayer()
{
	CQEntLayerView* pView= (CQEntLayerView*)GetActiveView ();
	if(pView==NULL)
	{
		return NULL;
	}
	return pView->GetLayer();
}

void CEzcad3View::OnActivateView (CView* pView)
{
	CQEntLayerView* pLayerView= (CQEntLayerView*)pView;
	if(pLayerView==NULL)
	{
		return ;
	}

	pLayerView->OnActivate();
}

LRESULT CEzcad3View::OnMoveTab(WPARAM wp, LPARAM lp)
{//移动了tab

	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return 0;
	}

	int nOldTab = (int)wp;	
	int nNewTab = (int)lp;	

	if(nOldTab==nNewTab)
	{
		ASSERT(0);
		return 0;
	}

	//互换nOldTab和nNewTab位置的对象
	PEntity pEnt1 = E3_GetEntChildByIndex(pEM,nOldTab);
	PEntity pEnt2 = E3_GetEntChildByIndex(pEM,nNewTab);
	if(pEnt1==NULL || pEnt2==NULL)
	{
		
		return 0;
	}

	E3_EntMgrBeginUndo(pEM,QGlobal::gf_Str(_T("CHANGEORDER"),_T("Change Order")));
	if(nOldTab < nNewTab)
	{//向后移动
		PEntity pEnt = E3_GetEntNext(pEnt2);
		E3_EntMgrUDMoveToAfter(pEM,pEnt1,pEnt2);
	}
	else
	{//向前移动
		PEntity pEnt = E3_GetEntPrev(pEnt2);
		E3_EntMgrUDMoveToBefore(pEM, pEnt1,pEnt2);
	}	

	E3_EntMgrEndUndo(pEM);
		
	CQEntLayerView* pLayerView = (CQEntLayerView*)m_wndTabs.GetTabWnd(nNewTab);
	if(pLayerView!=NULL)
	{
		OnActivateView(pLayerView);
	}
	return 0;
}
LRESULT CEzcad3View::OnChangeActiveTab(WPARAM wp, LPARAM lp)
{	
	CQEntLayerView* pLayerView = (CQEntLayerView*)m_wndTabs.GetTabWnd((int)wp);
	
	if(pLayerView!=NULL && pLayerView!=m_pLayerViewStartChange)
	{
		m_pLayerViewStartChange = pLayerView;
		pLayerView->OnActivate();
	}
	return 0;
}
LRESULT CEzcad3View::OnChangingActiveTab(WPARAM wp, LPARAM lp)
{
	
	CQEntLayerView* m_pLayerViewStartChange = (CQEntLayerView*)m_wndTabs.GetTabWnd((int)wp);
	return 0;
	
}

void CEzcad3View::OnInitialUpdate()
{
	CQTabView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	
}


 
 