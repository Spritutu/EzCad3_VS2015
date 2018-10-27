// DialogPenbox.cpp : 实现文件
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "DialogPenbox.h"
#include "afxdialogex.h"
#include "QGlobal.h"
#include "usermessdef.h"
#include "QPropertyGridPropertyParam.h"
#include "QUser.h"
#include "..\MainFrm.h"
#include "sysparam.h"
#include "QDlg.h"
// CDialogPenbox 对话框

IMPLEMENT_DYNAMIC(CDialogPenbox, CDialogEx)

CDialogPenbox::CDialogPenbox(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogPenbox::IDD, pParent)
{
	m_nCurPenIndex = 0; 
	m_bEnablePropertyChangeHandle=FALSE;
	 
	m_pMarker=NULL;
	m_penCur = E3_PenBoxCreateAPen();
	 
}

CDialogPenbox::~CDialogPenbox()
{
	if (m_penCur != NULL)
	{
		E3_PenBoxDestroyAPen(m_penCur);
		m_penCur = NULL;
	}
}

void CDialogPenbox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCPROPERTYGRID2,  m_penParam);
	DDX_Control(pDX, IDC_LIST2, m_listPen);
	DDX_Control(pDX, IDC_BUTTON_PEN0, m_btnPen0);
	DDX_Control(pDX, IDC_BUTTON_PEN1, m_btnPen1);
	DDX_Control(pDX, IDC_BUTTON_PEN2, m_btnPen2);
	DDX_Control(pDX, IDC_BUTTON_PEN3, m_btnPen3);
	DDX_Control(pDX, IDC_BUTTON_PEN4, m_btnPen4);
	DDX_Control(pDX, IDC_BUTTON_PEN5, m_btnPen5);
	DDX_Control(pDX, IDC_BUTTON_PEN6, m_btnPen6);
	DDX_Control(pDX, IDC_BUTTON_PEN7, m_btnPen7);
	DDX_Control(pDX, IDC_BUTTON_LISTONOFF, m_btnShowOnOff);
	
}


BEGIN_MESSAGE_MAP(CDialogPenbox, CDialogEx)
	ON_WM_SIZE() 
	ON_MESSAGE(WM_USER_INITENTLIST,OnUserInitEntList)
	ON_MESSAGE(WM_USER_PICKCHANGE,OnUserPickChange)
	ON_MESSAGE(WM_USER_CHANGELASER,OnUserLaserChange)
	ON_MESSAGE(WM_USER_UNITCHANGE,OnUserUnitChange) 
	ON_NOTIFY(NM_CLICK, IDC_LIST2, OnClickListPen) 
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkListPen) 
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, OnRclickListPen)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST2, OnCustomdrawPen)
	ON_BN_CLICKED(IDC_BUTTON_PEN0, OnBnClickedPen0)
	ON_BN_CLICKED(IDC_BUTTON_PEN1, OnBnClickedPen1)
	ON_BN_CLICKED(IDC_BUTTON_PEN2, OnBnClickedPen2)
	ON_BN_CLICKED(IDC_BUTTON_PEN3, OnBnClickedPen3)
	ON_BN_CLICKED(IDC_BUTTON_PEN4, OnBnClickedPen4)
	ON_BN_CLICKED(IDC_BUTTON_PEN5, OnBnClickedPen5)
	ON_BN_CLICKED(IDC_BUTTON_PEN6, OnBnClickedPen6)
	ON_BN_CLICKED(IDC_BUTTON_PEN7, OnBnClickedPen7)
	ON_COMMAND(ID_PEN_APPLYTOPICK, OnPenApplytopick)
	ON_UPDATE_COMMAND_UI(ID_PEN_APPLYTOPICK, OnUpdatePenApplytopick) 
	ON_REGISTERED_MESSAGE( AFX_WM_PROPERTY_CHANGED, OnPropertyChanged ) 
	ON_COMMAND(ID_PEN_LOADPENBOXFROMDEFAULT, OnLoadDefaultPens)
	ON_COMMAND(ID_PEN_SETDEFAULTPENSPARAM, OnPenSetDefaultPens)
	ON_COMMAND(ID_PEN_RESETALLPENS, OnPenResetAllPens)
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY() 
	ON_MESSAGE(WM_USER_LASERPARAMCHANGED, OnUserLaserParamChanged)

	
	ON_BN_CLICKED(IDC_BUTTON_ADVANCE, &CDialogPenbox::OnBnClickedButtonAdvance)
	ON_BN_CLICKED(IDC_BUTTON_PARAMLIB, &CDialogPenbox::OnBnClickedButtonParamlib)
	ON_BN_CLICKED(IDC_BUTTON_LISTONOFF, &CDialogPenbox::OnBnClickedButtonListonoff)
END_MESSAGE_MAP()
	
void CDialogPenbox::OnDestroy()
{
	SaveLastListWidth( );
}
BOOL CDialogPenbox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	bmpMarkOn.LoadBitmap(IDB_BITMAP_MARK_ON);
	bmpMarkOff.LoadBitmap(IDB_BITMAP_MARK_OFF);
  
	GetDlgItem(IDC_BUTTON_ADVANCE)->SetWindowText(QGlobal::gf_Str(_T("ADVANCE"), _T("Advance"))+_T("..."));
	GetDlgItem(IDC_BUTTON_PARAMLIB)->SetWindowText(QGlobal::gf_Str(_T("PARAMLIB"), _T("Param lib")) + _T("..."));

	
	InitPenboxList(); 
	InitPropList();		
	UpdatePenList(); 

	SetPropListFont();

	ShowCurPenParam(0);

	m_penProp.m_pParentWnd = this;
	return TRUE;
}

 
BOOL CDialogPenbox::GetLastListWidth(int& bItem0,int& bItem1,int& bItem2,int& bItem3,int& bItemProp)
{
	CWinApp* pWinApp = AfxGetApp();
	
	int nItemWidth0 = pWinApp->GetProfileInt(_T("PENBOX"),_T("ITEMWIDTH0"),0);
	int nItemWidth1 = pWinApp->GetProfileInt(_T("PENBOX"),_T("ITEMWIDTH1"),0);
	int nItemWidth2 = pWinApp->GetProfileInt(_T("PENBOX"),_T("ITEMWIDTH2"),0); 
	int nItemWidth3 = pWinApp->GetProfileInt(_T("PENBOX"),_T("ITEMWIDTH3"),0); 
	int nItemWidth4 = pWinApp->GetProfileInt(_T("PENBOX"),_T("PENPROPWIDTH"),0); 
	 
	if(nItemWidth0<=0 || nItemWidth1<=0 || nItemWidth2<=0|| nItemWidth3<=0|| nItemWidth3<=0)
	{
		return FALSE;
	}
	bItem0 = nItemWidth0;
	bItem1 = nItemWidth1;
	bItem2 = nItemWidth2;
	bItem3 = nItemWidth3;
	bItemProp= nItemWidth4;
	return TRUE;
}

void CDialogPenbox::SaveLastListWidth( )
{
	CWinApp* pWinApp = AfxGetApp();

	pWinApp->WriteProfileInt(_T("PENBOX"),_T("ITEMWIDTH0"),m_listPen.GetColumnWidth (0) );
 	pWinApp->WriteProfileInt(_T("PENBOX"),_T("ITEMWIDTH1"),m_listPen.GetColumnWidth (1) );
 	pWinApp->WriteProfileInt(_T("PENBOX"),_T("ITEMWIDTH2"),m_listPen.GetColumnWidth (2) ); 
	pWinApp->WriteProfileInt(_T("PENBOX"),_T("ITEMWIDTH3"),m_listPen.GetColumnWidth (3) ); 

	pWinApp->WriteProfileInt(_T("PENBOX"),_T("PENPROPWIDTH"),m_penParam.GetLeftColumnWidth ( ) ); 

}

void CDialogPenbox::SetPropListFont()
{
	::DeleteObject(m_fontProp.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fontProp.CreateFontIndirect(&lf);

	m_listPen.SetFont(&m_fontProp);
	m_penParam.SetFont(&m_fontProp);
}


void CDialogPenbox::InitPenboxList()
{	
	m_btnShowOnOff.SetShow(!gf_GetSysParam()->GetParamInt(DOUBLE_PARAM_NUDGESMALLDIST));

	m_listPen.SetExtendedStyle ( LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES);		
	m_listPen.InsertColumn ( 0, QGlobal::gf_Str(_T("PENNO"),_T("Pen No")), LVCFMT_LEFT, -1, 0 );	
	m_listPen.InsertColumn ( 1, QGlobal::gf_Str(_T("NAME"),_T("Name")), LVCFMT_LEFT, -1, 1 );	
	m_listPen.InsertColumn ( 2, QGlobal::gf_Str(_T("COLOR"),_T("Color")) , LVCFMT_LEFT, -1, 2 );	
	m_listPen.InsertColumn ( 3, QGlobal::gf_Str(_T("ONOFF"),_T("On/Off")) , LVCFMT_LEFT, -1,3 );

	CRect rect;
	m_listPen.GetWindowRect(&rect);	
		
	int  bItem0=rect.Width() * 4/20;
	int  bItem1=rect.Width() * 8/20;
	int  bItem2=rect.Width() * 3/20;
	int  bItem3=rect.Width() * 3/20;
	int   bItem4;  
	if(GetLastListWidth( bItem0, bItem1, bItem2,bItem3,bItem4) )
	{
		m_listPen.SetColumnWidth ( 0, bItem0 );
		m_listPen.SetColumnWidth ( 1, bItem1);
		m_listPen.SetColumnWidth ( 2, bItem2 );
		m_listPen.SetColumnWidth ( 3, bItem3 );
	}
	else
	{
		m_listPen.SetColumnWidth ( 0, rect.Width() * 4/20 );
		m_listPen.SetColumnWidth ( 1, rect.Width() * 8/20 );
		m_listPen.SetColumnWidth ( 2, rect.Width() * 3/20 );
		m_listPen.SetColumnWidth ( 3, rect.Width() *3/20 );
	}

	if(E3_GetCmdMgr()!=NULL)
	{
		E3_CmdMgrAddEntityWnd(E3_GetCmdMgr(), this );//告诉命令管理器当前窗口需要接收系统消息
	}
}
void CDialogPenbox::OnCustomdrawPen ( NMHDR* pNMHDR, LRESULT* pResult )
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );

	// Take the default processing unless we set this to something else below.
	*pResult = 0;
	 
	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.
	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		 //TRACE("ITEM\n");
	}
	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		// This is the notification message for an item.  We'll request
		// notifications before each subitem's prepaint stage.
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		// TRACE("ITEM_SUBITEM\n");
	}
	else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{
		//TRACE("CDDS_ITEMPREPAINT | CDDS_SUBITEM\n");
		// This is the prepaint stage for a subitem.         
		int nItem    = (int)pLVCD->nmcd.dwItemSpec;
		int nSubItem = pLVCD->iSubItem;
		
		PEntMgr pEM =E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());

		PPenBox pPenBox = E3_EntMgrGetPenBox(pEM);
		 
		if(nItem < 0 || pPenBox==NULL ||pLVCD->nmcd.uItemState==0  )//pLVCD->nmcd.uItemState==0  加上这个防止鼠标移到到控件导致绘制会丢失子项
		{
			// Tell Windows to paint the control itself.
			 
			*pResult = CDRF_DODEFAULT; 
			return;
		}	 

	 

		CString strText;
		CDC*  pDC = CDC::FromHandle ( pLVCD->nmcd.hdc );		
		CRect rect;		
		CString str;
		ListView_GetSubItemRect(::GetDlgItem (m_hWnd,IDC_LIST2),nItem,nSubItem,LVIR_BOUNDS,&rect);
		
		COLORREF	textColor=::GetSysColor( COLOR_WINDOWTEXT );    //文本的颜色 
		BOOL bItemSelect = m_listPen.GetItemState(nItem,LVIS_SELECTED);
		if(bItemSelect)
		{	
			CBrush pBrush(::GetSysColor(COLOR_HIGHLIGHT)  );
			pDC->FillRect (&rect,&pBrush);//绘制背景
			textColor= 0x00FFFFFF & ~( textColor );	//文本颜色反转		
		}
		else  
		{			 
			CBrush pBrush(m_listPen.GetBkColor() );
			 pDC->FillRect (&rect,&pBrush);//绘制背景 	
		}

		DWORD rop = bItemSelect ? SRCAND:SRCCOPY; 
		PMarkPen pMarkPen = E3_PenBoxGetPen(pPenBox, nItem);
		if(nSubItem ==0)
		{
			CRect rectImage(rect.left,rect.top,rect.left+2*rect.Height(),rect.bottom);
		 
			DWORD rop = bItemSelect ? SRCAND:SRCCOPY; 

			
			if(E3_PenBoxIsPenMark(pMarkPen))
			{
				gf_StretchDrawBmp(pLVCD->nmcd.hdc,&bmpMarkOn,rectImage.left+1,rectImage.top+1 ,rectImage.Height()-2,rectImage.Height()-2,rop);
			}
			else
			{
				gf_StretchDrawBmp(pLVCD->nmcd.hdc,&bmpMarkOff,rectImage.left+1,rectImage.top+1 ,rectImage.Height()-2,rectImage.Height()-2,rop);
			}  

			rect.left+=rect.Height();
			//TRACE("0\n");
		}  
		else if(nSubItem ==1)
		{
			//TRACE("1\n");
		}
		else if(nSubItem ==2)
		{ 
			CBrush brush(E3_PenBoxGetPenColor(pMarkPen));
			CBrush* oldbrush = pDC->SelectObject (&brush);			
			rect.DeflateRect(1,1);
			pDC->Rectangle (rect);		
			pDC->SelectObject (oldbrush); 
//			TRACE("2\n");
		} 
		else if(nSubItem ==3)
		{
			//TRACE("3\n");
		}
		else
		{
			//TRACE("Error\n");
		}
		 
		
		strText = m_listPen.GetItemText(nItem,nSubItem);
		if(	!strText.IsEmpty())
		{
			pDC->SetTextColor (textColor);
			int mode =pDC->SetBkMode(TRANSPARENT);//设置文字输出模式为透明背景	
			pDC->TextOut(rect.left+4,rect.top+1,strText);
			pDC->SetBkMode(mode); 
		}  
		else
		{
			 
		}
		 
		*pResult = CDRF_SKIPDEFAULT;//drew the item manually. The control will not draw the item.  
	}
	else
	{
		 
	} 
}

void CDialogPenbox::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialogEx::OnMouseMove(nFlags, point);
}

// CDialogPenbox 消息处理程序
void CDialogPenbox::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	AutoLayout();
}

void CDialogPenbox::AutoLayout()
{
	if(this->m_hWnd!=NULL && m_penParam.m_hWnd!=NULL)
	{	 
		CRect rcWnd , rcBtnListOnOff, rcClient,rcWndList,rectWndPen,rcClientBtn,rectItem, rcAdvanceBtn, rcParamLibBtn;

		GetClientRect(rcClient); 
		
		GetDlgItem(IDC_BUTTON_LISTONOFF)->GetClientRect(rcBtnListOnOff);		
			 
		m_btnPen0.GetClientRect(rcClientBtn); 
		GetDlgItem(IDC_BUTTON_ADVANCE)->GetClientRect(rcAdvanceBtn);
		GetDlgItem(IDC_BUTTON_PARAMLIB)->GetClientRect(rcParamLibBtn);
		ListView_GetSubItemRect(::GetDlgItem (m_hWnd,IDC_LIST2),0,0,LVIR_BOUNDS,&rectItem);

		int nEdge = 1;	
		int nWidth = rcClient.Width()-2*nEdge; 
		int nListHeight = (int)(rectItem.Height()*9.5);
		//int nBtnTop=nEdge+nListHeight+nEdge;
		
		int nBtnTop = nEdge; 
		
		//显示列表
		m_listPen.SetWindowPos(NULL, nEdge, nBtnTop, nWidth, nListHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	 
		 if (!gf_GetSysParam()->GetParamInt(DOUBLE_PARAM_NUDGESMALLDIST))
		{//显示列表
			nBtnTop += nListHeight + 1;
		} 

		GetDlgItem(IDC_BUTTON_LISTONOFF)->SetWindowPos(NULL, nEdge, nBtnTop, nWidth, rcBtnListOnOff.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
		nBtnTop += rcBtnListOnOff.Height() + 1;

		//显示笔按钮
		m_btnPen0.SetWindowPos(NULL, nEdge,nBtnTop,rcClientBtn.Width(),rcClientBtn.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
		m_btnPen1.SetWindowPos(NULL, nEdge+(rcClientBtn.Width()+nEdge),nBtnTop,rcClientBtn.Width(),rcClientBtn.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
		m_btnPen2.SetWindowPos(NULL, nEdge+2*(rcClientBtn.Width()+nEdge),nBtnTop,rcClientBtn.Width(),rcClientBtn.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
		m_btnPen3.SetWindowPos(NULL, nEdge+3*(rcClientBtn.Width()+nEdge),nBtnTop,rcClientBtn.Width(),rcClientBtn.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
		m_btnPen4.SetWindowPos(NULL, nEdge+4*(rcClientBtn.Width()+nEdge),nBtnTop,rcClientBtn.Width(),rcClientBtn.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
		m_btnPen5.SetWindowPos(NULL, nEdge+5*(rcClientBtn.Width()+nEdge),nBtnTop,rcClientBtn.Width(),rcClientBtn.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
		m_btnPen6.SetWindowPos(NULL, nEdge+6*(rcClientBtn.Width()+nEdge),nBtnTop,rcClientBtn.Width(),rcClientBtn.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
		m_btnPen7.SetWindowPos(NULL, nEdge+7*(rcClientBtn.Width()+nEdge),nBtnTop,rcClientBtn.Width(),rcClientBtn.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	 
		if (!E3_MarkerIsHidePenButton(m_pMarker))
		{
			nBtnTop += rcClientBtn.Height() + nEdge;
		}

		//显示属性参数
		int nPropBottom = rcClient.bottom - 2 * nEdge - rcAdvanceBtn.Height();
		if (nPropBottom<= nBtnTop)
		{
			nPropBottom = nBtnTop + 1;
		}

		m_penParam.SetWindowPos(NULL, nEdge, nBtnTop, nWidth, nPropBottom - nBtnTop, SWP_NOACTIVATE | SWP_NOZORDER);
		m_penParam.AdjustLayout();
		m_penParam.Invalidate();
		 
		GetDlgItem(IDC_BUTTON_ADVANCE)->SetWindowPos(NULL, nEdge, nPropBottom + nEdge, rcAdvanceBtn.Width(), rcAdvanceBtn.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
		GetDlgItem(IDC_BUTTON_PARAMLIB)->SetWindowPos(NULL, nEdge+ rcAdvanceBtn.Width()+ nEdge, nPropBottom + nEdge, rcParamLibBtn.Width(), rcParamLibBtn.Height(), SWP_NOACTIVATE | SWP_NOZORDER); 		
	}
}
  
//初始化参数属性表
void CDialogPenbox::InitPropList()
{
	m_bEnablePropertyChangeHandle = FALSE;
	m_penParam.RemoveAll();
	m_penParam.SetVSDotNetLook();
	m_penParam.EnableHeaderCtrl(FALSE);
	m_penParam.MarkModifiedProperties(); //着重显示更改过的部分
	m_penParam.SetBoolLabels(QGlobal::gf_Str(_T("TRUE"), _T("TRUE")), QGlobal::gf_Str(_T("FALSE"), _T("FALSE")));
	m_penParam.SetGroupNameFullWidth(TRUE);

	m_penParam.ModifyStyle(0, WS_BORDER);

	if (E3_MarkerIsShowDecArea(m_pMarker))
	{
		m_penParam.EnableDescriptionArea(TRUE);
	}
	else
	{
		m_penParam.EnableDescriptionArea(FALSE);
	}

	int  bItem0, bItem1, bItem2, bItem3, bItem4;
	if (GetLastListWidth(bItem0, bItem1, bItem2, bItem3, bItem4) && bItem4 > 10)
	{
		m_penParam.SetColumnWidth(bItem4);
	}
	else
	{
		CRect rect;
		m_penParam.GetWindowRect(&rect);
		m_penParam.SetColumnWidth(rect.Width() * 7 / 10);
	}

	//创建笔参数列表
	//CreatePenParamList();

	m_penProp.m_pPenGridCtrl = &m_penParam;
	m_penProp.m_pPenCur = m_penCur;
	m_penProp.CreatePenParamList();

	if (E3_PenBoxIsPenUseDefParam(m_penCur))
	{
		PMarkParam pParam = E3_PenBoxGetParamLibDefParam( );
		if (pParam != NULL)
		{
			E3_PenBoxSetPenParam(m_penCur, pParam); 
		}
	}
	if (!gf_GetUserMgr()->GetCurUser()->m_bEnablePenParam)
	{
		GetDlgItem(IDC_MFCPROPERTYGRID2)->EnableWindow(FALSE);
		GetDlgItem(IDC_LIST2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PEN0)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PEN1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PEN2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PEN3)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PEN4)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PEN5)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PEN6)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PEN7)->EnableWindow(FALSE);
	}

	if (E3_MarkerIsEnableWeld(m_pMarker))
	{//使能焊接
		GetDlgItem(IDC_BUTTON_ADVANCE)->ShowWindow(SW_HIDE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_ADVANCE)->ShowWindow(SW_SHOW);
	}

	int nState = SW_SHOW;
	if (E3_MarkerIsHidePenButton(m_pMarker))
	{
		nState = SW_HIDE;
	}
	GetDlgItem(IDC_BUTTON_PEN0)->ShowWindow(nState);
	GetDlgItem(IDC_BUTTON_PEN1)->ShowWindow(nState);
	GetDlgItem(IDC_BUTTON_PEN2)->ShowWindow(nState);
	GetDlgItem(IDC_BUTTON_PEN3)->ShowWindow(nState);
	GetDlgItem(IDC_BUTTON_PEN4)->ShowWindow(nState);
	GetDlgItem(IDC_BUTTON_PEN5)->ShowWindow(nState);
	GetDlgItem(IDC_BUTTON_PEN6)->ShowWindow(nState);
	GetDlgItem(IDC_BUTTON_PEN7)->ShowWindow(nState);


	
	GetDlgItem(IDC_LIST2)->ShowWindow(!gf_GetSysParam()->GetParamInt(DOUBLE_PARAM_NUDGESMALLDIST));

	m_bEnablePropertyChangeHandle = TRUE;
}



//接受数据库的增加对象消息，更新列表显示
LRESULT CDialogPenbox::OnUserInitEntList(WPARAM wParam, LPARAM lParam)
{
	UpdatePenList();	
	ShowCurPenParam(0); 
	return 0;
}

//接受数据库的选取对象改变消息，更新列表显示
LRESULT CDialogPenbox::OnUserPickChange(WPARAM wParam, LPARAM lParam)
{	
	PEntMgr  pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());

	if(pEM==NULL)
	{
		return 0;
	}
	
	WORD wEntType=0;
	int nPick = E3_EntMgrPickCount(pEM);

	if(nPick>0)
	{			 
		PEntity pEnt = E3_EntMgrGetPickHead(pEM);

		int nPen = E3_GetEntPenNo(pEnt);

		 ShowCurPenParam( nPen);
	} 
	
	 UpdatePenListSelectStateAndCheckName();	
	return 0;
}

//接受数据库的选取对象改变消息，更新列表显示
LRESULT CDialogPenbox::OnUserLaserChange(WPARAM wParam, LPARAM lParam)
{	
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());

	if(pEM==NULL)
	{
		return 0;
	}

	m_pMarker = (PMarker)wParam; 
	E3_CmdMgrSetShowMsg(E3_GetCmdMgr(), _T("")); 

	if(m_pMarker!=NULL)
	{ 
		m_penProp.m_nCurLaserType = E3_MarkerGetLaserType(m_pMarker);
		m_penProp.m_pMarker = m_pMarker;
		if (E3_MarkerIsTestMode(m_pMarker))
		{
			E3_CmdMgrSetShowMsg(E3_GetCmdMgr(), _T("Marking is disabled")); 
		}
	} 
	else
	{ 
		E3_CmdMgrSetShowMsg(E3_GetCmdMgr(), _T("Marking is disabled")); 
	}  

	if(E3_MarkerIsDemo(m_pMarker))
	{//demo版本
		E3_CmdMgrSetShowMsg(E3_GetCmdMgr(), _T("Demo version-only for evaluation")); 
	}
	
	InitPropList();
	UpdateCurPenParam();
#ifdef ENABLE_MARK 
	if (m_pMarker != NULL)
	{
		E3_MarkerSetLaserParamOut(m_pMarker, E3_PenBoxGetPenParam(m_penProp.m_pPenCur));
	} 
#endif
	return 0;
}
	
//接受数据库的选取对象改变消息，更新列表显示
LRESULT CDialogPenbox::OnUserUnitChange(WPARAM wParam, LPARAM lParam)
{
	E3_PenBoxOnChangeUnit(m_penCur);
	InitPropList();
	return 0;
}

//显示指定笔参数
void CDialogPenbox::ShowCurPenParam(int nPen)
{
	PEntMgr pEM =  E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());

	if(pEM==NULL)
	{
		return  ;
	}
	 

	PPenBox pPenBox = E3_EntMgrGetPenBox( pEM );
	PMarkPen pPen = E3_PenBoxGetPen(pPenBox,nPen);
	if(pPen==NULL)
	{
		return;
	}

	m_nCurPenIndex = nPen;
	E3_PenBoxCopyPenParam(m_penCur,pPen);
	m_penProp.m_nCurPenIndex = m_nCurPenIndex;

	UpdateCurPenParam();
}

//更新当前笔参数
void CDialogPenbox::UpdateCurPenParam()
{	
	m_bEnablePropertyChangeHandle=FALSE;
	m_penProp.UpdateCurPenParam();
	 
	UpdateAllBtnColor();
	
	m_bEnablePropertyChangeHandle=TRUE;
}

//更新当前笔列表的选择状态且检查名字是否正确 
void CDialogPenbox::UpdatePenListSelectStateAndCheckName() 
{
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());

	if (pEM == NULL)
	{
		return;
	}

	PPenBox pPenBox = E3_EntMgrGetPenBox(pEM);

 	
	BOOL bChange=FALSE;
	for(int i=0;i<MAX_PEN_NUM;i++)	 
	{
		//检查名字
		PMarkPen pMarkPen = E3_PenBoxGetPen(pPenBox,i);
	 	if(m_listPen.GetItemText ( i, 1)!= E3_PenBoxGetPenName(pMarkPen))
		{
			if(!bChange)
			{
				m_listPen.SetRedraw(FALSE);//大数据量更新前，禁止绘制
				bChange=TRUE;
			}
			m_listPen.SetItemText ( i, 1, E3_PenBoxGetPenName(pMarkPen));
		}

		if(i==m_nCurPenIndex)
		{
			if(	!m_listPen.GetItemState(i,LVIS_SELECTED) )
			{	
				if(!bChange)
				{
					m_listPen.SetRedraw(FALSE);//大数据量更新前，禁止绘制
					bChange=TRUE;
				}
				m_listPen.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);	
			}
			m_listPen.EnsureVisible(i,FALSE);
		}
		else
		{
			if(	m_listPen.GetItemState(i,LVIS_SELECTED) )
			{	
				if(!bChange)
				{
					m_listPen.SetRedraw(FALSE);//大数据量更新前，禁止绘制
					bChange=TRUE;
				}
				m_listPen.SetItemState( i,0,LVIS_SELECTED);	
			}
		} 
	}
	if(bChange)
	{//有更新
		m_listPen.SetRedraw(TRUE);  
		m_listPen.Invalidate();
	}
}

void CDialogPenbox::UpdateAllBtnColor()
{
	PEntMgr pEM =  E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());

	if(pEM==NULL)
	{
		return  ;
	}
	 
	PPenBox pPenBox = E3_EntMgrGetPenBox(pEM);

	m_btnPen0.m_clrBtn = E3_PenBoxGetPenColor(E3_PenBoxGetPen(pPenBox,0));
	m_btnPen0.Invalidate();

	m_btnPen1.m_clrBtn = E3_PenBoxGetPenColor(E3_PenBoxGetPen(pPenBox, 1));
	m_btnPen1.Invalidate();
	
	m_btnPen2.m_clrBtn = E3_PenBoxGetPenColor(E3_PenBoxGetPen(pPenBox, 2));
	m_btnPen2.Invalidate();
	
	m_btnPen3.m_clrBtn = E3_PenBoxGetPenColor(E3_PenBoxGetPen(pPenBox, 3));
	m_btnPen3.Invalidate();
	
	m_btnPen4.m_clrBtn = E3_PenBoxGetPenColor(E3_PenBoxGetPen(pPenBox, 4));
	m_btnPen4.Invalidate();
	
	m_btnPen5.m_clrBtn = E3_PenBoxGetPenColor(E3_PenBoxGetPen(pPenBox,5));
	m_btnPen5.Invalidate();
	
	m_btnPen6.m_clrBtn = E3_PenBoxGetPenColor(E3_PenBoxGetPen(pPenBox, 6));
	m_btnPen6.Invalidate();
	
	m_btnPen7.m_clrBtn = E3_PenBoxGetPenColor(E3_PenBoxGetPen(pPenBox, 7));
	m_btnPen7.Invalidate();	
}



//更新当前笔列表
void CDialogPenbox::UpdatePenList()
{
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());

	if (pEM == NULL)
	{
		return;
	}

	PPenBox pPenBox = E3_EntMgrGetPenBox(pEM);

	m_listPen.SetRedraw(FALSE);//大数据量更新前，禁止绘制

	m_listPen.DeleteAllItems();
	  
	CString str;

	for(int i=0;i<MAX_PEN_NUM;i++)	
	{
		str.Format(_T("%d"),i);
		m_listPen.InsertItem ( i, str );
		PMarkPen pMarkPen = E3_PenBoxGetPen(pPenBox, i);
	 
		str.Format(_T("%s"), E3_PenBoxGetPenName(pMarkPen));
		m_listPen.SetItemText ( i, 1,str);

		if(E3_PenBoxIsPenMark(pMarkPen))
		{
			m_listPen.SetItemText ( i, 3,QGlobal::gf_Str(_T("ON"),_T("On")));		
		}
		else
		{
			m_listPen.SetItemText ( i, 3,QGlobal::gf_Str(_T("OFF"),_T("Off")));		
		}	
	}
	m_listPen.SetItemState( 0,LVIS_SELECTED,LVIS_SELECTED);	 

	m_listPen.SetRedraw(TRUE);//大数据量更新后，可以绘制
	m_listPen.Invalidate();
}

void CDialogPenbox::OnClickListPen(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	PEntMgr  pEM =  E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr()); 
	if(pEM==NULL)
	{
		return ;
	}
	POSITION pos = m_listPen.GetFirstSelectedItemPosition();
	int nItem = m_listPen.GetNextSelectedItem(pos);
	if(nItem >= 0)
	{
		int nPick = E3_EntMgrPickCount(pEM);
		if(nPick<=0)
		{
			ShowCurPenParam(nItem);			
		}			
	}

	*pResult = 0;
}


void CDialogPenbox::OnDblclkListPen(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	*pResult = 0;
	PEntMgr  pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());

	if (pEM == NULL)
	{
		return;
	}
	
	HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST2);
	LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
	
	int nItem    = temp->iItem;  //get the row number
    int nSubItem = temp->iSubItem;//get the column number
	
	PPenBox pPenBox = E3_EntMgrGetPenBox(pEM);

	if(nItem < 0 || pPenBox==NULL)
	{
		return ;	
	}
	PMarkPen pPen = E3_PenBoxGetPen(pPenBox, nItem);

	if(nSubItem==0|| nSubItem==1 || nSubItem==3)
	{ 
		E3_PenBoxSetPenMark(pPen,!E3_PenBoxIsPenMark(pPen));

		if(E3_PenBoxIsPenMark(pPen))
		{
			m_listPen.SetItemText (nItem, 3,QGlobal::gf_Str(_T("ON"),_T("On")));		
		}
		else
		{
			m_listPen.SetItemText (nItem, 3,QGlobal::gf_Str(_T("OFF"),_T("Off")));		
		}
		m_listPen.Invalidate();
	}
	else if(nSubItem==2)
	{
		CColorDialog dlg;
		dlg.m_cc.Flags |= CC_RGBINIT;
		dlg.m_cc.Flags |= CC_FULLOPEN;
		dlg.m_cc.Flags |= CC_ANYCOLOR;		
		dlg.m_cc.rgbResult = E3_PenBoxGetPenColor(pPen) ;
		if (dlg.DoModal() == IDOK)
		{			
			E3_PenBoxSetPenColor(pPen,dlg.GetColor());
			m_listPen.Invalidate();
			UpdateAllBtnColor(); 
		}
	}
  
}

void CDialogPenbox::OnRclickListPen(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	
	HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST2);
	LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
	
	int nItem    = temp->iItem;  //get the row number
    int nSubItem = temp->iSubItem;//get the column number
	
	PEntMgr  pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());

	if(pEM==NULL)
	{
		return ;
	}
	PPenBox pPenBox = E3_EntMgrGetPenBox(pEM);	
	if(nItem < 0 || pPenBox==NULL)
	{
		return ;	
	}
	
	CMenu RightMenu;
	RightMenu.LoadMenu(IDR_MENU_PEN);
	
	CMenu* pMenu = RightMenu.GetSubMenu(0);
	if (pMenu == NULL)
		return;	
	
  	pMenu->ModifyMenu(ID_PEN_APPLYTOPICK,MF_BYCOMMAND,ID_PEN_APPLYTOPICK,QGlobal::gf_Str(_T("APPLYTOPICK"),_T("Apply to pick object"))); 
	pMenu->ModifyMenu(ID_PEN_RESETALLPENS,MF_BYCOMMAND,ID_PEN_RESETALLPENS,QGlobal::gf_Str(_T("RESETALLPENS"),_T("Reset all pens")));  
	pMenu->ModifyMenu(ID_PEN_LOADPENBOXFROMDEFAULT,MF_BYCOMMAND,ID_PEN_LOADPENBOXFROMDEFAULT,QGlobal::gf_Str(_T("LOADPENBOXFROMDEF"),_T("Load default penbox"))); 
	pMenu->ModifyMenu(ID_PEN_SETDEFAULTPENSPARAM,MF_BYCOMMAND,ID_PEN_SETDEFAULTPENSPARAM,QGlobal::gf_Str(_T("SAVEASPENBOXTODEF"),_T("Save as default penbox"))); 
	CPoint point = temp->ptAction;
	ClientToScreen(&point);
	pMenu->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN,point.x,point.y,this);
	*pResult =1;
}

void CDialogPenbox::UpdateCurPenParamToPenBox()
{
	PEntMgr  pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());

	if(pEM==NULL)
	{
		return ;
	}
	PPenBox pPenBox = E3_EntMgrGetPenBox(pEM);
	PMarkPen pPen = E3_PenBoxGetPen(pPenBox,m_nCurPenIndex);
	
	E3_PenBoxCopyPenParam(pPen, m_penCur);
}


void CDialogPenbox::OnBnClickedPen0()
{
	AppltPenToSelEnt(0);	
}

void CDialogPenbox::OnBnClickedPen1()
{
	AppltPenToSelEnt(1);	
}

void CDialogPenbox::OnBnClickedPen2()
{
	AppltPenToSelEnt(2);	
}

void CDialogPenbox::OnBnClickedPen3()
{
	AppltPenToSelEnt(3);	
}

void CDialogPenbox::OnBnClickedPen4()
{
	AppltPenToSelEnt(4);	
}

void CDialogPenbox::OnBnClickedPen5()
{
	AppltPenToSelEnt(5);	
}

void CDialogPenbox::OnBnClickedPen6()
{
	AppltPenToSelEnt(6);	
}

void CDialogPenbox::OnBnClickedPen7()
{
	AppltPenToSelEnt(7);	
}
void CDialogPenbox::OnOK()
{
	// TODO: Add extra validation here

}

void CDialogPenbox::OnCancel()
{
	// TODO: Add extra cleanup here	

}

void CDialogPenbox::AppltPenToSelEnt(int nPen)
{
	if(nPen<0)
	{
		return;
	}
	PEntMgr  pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if(pEM==NULL)
	{
		return ;
	}


	int nPick = E3_EntMgrPickCount(pEM);
	if(nPick<=0)
	{
		ShowCurPenParam(nPen); 
	}
	else
	{		
		short nCtrl = GetKeyState(VK_CONTROL);	
		BOOL bCtrl  =   nCtrl & 0x8000 ?  TRUE : FALSE ;	

		TagPickItem* pItemList = new TagPickItem[nPick];
		nPick = E3_EntMgrCopyPickList(pEM,pItemList,nPick);
		 
		E3_EntMgrBeginUndo(pEM,QGlobal::gf_Str(_T("MODIFY"),_T("Modify")));
		E3_EntMgrBeginPick(pEM);

		for(int i = 0; i < nPick; i++)
		{					
			E3_SetEntPenUD(pEM,pItemList[i].m_pPicked,nPen,!bCtrl ); 
		}	

		E3_EntMgrEndPick(pEM);
		E3_EntMgrEndUndo(pEM);
		delete[] pItemList;			

		E3_CmdMgrInvalidate( );
	}
}

//把当前笔参数复制到笔盒中 
void CDialogPenbox::SetCurPenParamToPenbox()
{
	PEntMgr  pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if(pEM==NULL)
	{
		return ;
	}

	PPenBox pPenBox = E3_EntMgrGetPenBox(pEM);
	
	PMarkPen pPen = E3_PenBoxGetPen(pPenBox,m_nCurPenIndex);

	E3_PenBoxCopyPenParam(pPen, m_penCur);
	UpdateCurPenParam();
	UpdatePenListSelectStateAndCheckName();
}
 
LRESULT CDialogPenbox::OnPropertyChanged(WPARAM wparam,LPARAM lparam )
{
	if(!m_bEnablePropertyChangeHandle)
	{
		return 0;
	}
	// Parameters:
	// [in] wparam: the control ID of the CMFCPropertyGridCtrl that changed.
	// [in] lparam: pointer to the CMFCPropertyGridProperty that changed.	
    CMFCPropertyGridProperty* pProperty = ( CMFCPropertyGridProperty * ) lparam; 
    m_penProp.OnPropertyChanged(pProperty);
    
	//把当前笔参数复制到笔盒中
	SetCurPenParamToPenbox();

	PEntMgr  pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM != NULL)
	{
		E3_SetEntMgrModifyFlag(pEM, TRUE);
	}

	return  0  ;  
}


void CDialogPenbox::OnPenApplytopick() 
{
	// TODO: Add your command handler code here
	POSITION pos = m_listPen.GetFirstSelectedItemPosition();
	int nItem = m_listPen.GetNextSelectedItem(pos);
	if(nItem < 0)
	{
		return ;	
	}

	AppltPenToSelEnt(nItem);
}

void CDialogPenbox::OnUpdatePenApplytopick(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	PEntMgr  pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr()); 
	if(pEM==NULL)
	{
		pCmdUI->Enable(FALSE);
		return ;
	}

	pCmdUI->Enable(E3_EntMgrPickCount(pEM)>0);
}

void CDialogPenbox::OnLoadDefaultPens() 
{
	PEntMgr  pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if(pEM==NULL)
	{
		return  ;
	}
	 

	PPenBox pPenBox = E3_EntMgrGetPenBox(pEM);
	 if(pPenBox==NULL)
	{
		return;
	}

	 E3_PenBoxLoadDefault(pPenBox);

	UpdatePenList();
	UpdateAllBtnColor();
	ShowCurPenParam(m_nCurPenIndex); 
}

void CDialogPenbox::OnPenSetDefaultPens() 
{
	PEntMgr  pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if(pEM==NULL)
	{
		return  ;
	}
	 

	PPenBox pPenBox = E3_EntMgrGetPenBox(pEM);
	 if(pPenBox==NULL)
	{
		return;
	}

	 E3_PenBoxSaveToDefault(pPenBox);
	 
}


void CDialogPenbox::OnPenResetAllPens() 
{
	PEntMgr  pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if(pEM==NULL)
	{
		return  ;
	}
	 

	PPenBox pPenBox = E3_EntMgrGetPenBox(pEM);
	 if(pPenBox==NULL)
	{
		return;
	}
	 E3_PenBoxIniDefaultPen(pPenBox);

	UpdatePenList();
	UpdateAllBtnColor();

	ShowCurPenParam(m_nCurPenIndex); 
}


//接受数据库的增加对象消息，更新列表显示
LRESULT CDialogPenbox::OnUserLaserParamChanged(WPARAM wParam, LPARAM lParam)
{ 
#ifdef ENABLE_MARK
	CMainFrame* pMainWnd = (CMainFrame*)gf_GetMainFrame();
	if (pMainWnd!=NULL && pMainWnd->m_wndMark.GetMarker() != NULL)
	{
		E3_MarkerSetLaserParamOut(pMainWnd->m_wndMark.GetMarker(), E3_PenBoxGetPenParam(m_penProp.m_pPenCur));
	} 
#endif
	return 0;
}

void CDialogPenbox::OnBnClickedButtonAdvance()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pMarker == NULL)
	{
		return;
	} 
	if (gf_DlgPenAdvance(m_pMarker) == IDOK)
	{
		InitPropList();
		SendMessage(WM_SIZE);

		m_penProp.CreatePenParamList();
		UpdateCurPenParam(); 

		if (E3_MarkerIsShowDecArea(m_pMarker))
		{
			m_penParam.EnableDescriptionArea(TRUE);
		}
		else
		{
			m_penParam.EnableDescriptionArea(FALSE);
		}
	}
}


void CDialogPenbox::OnBnClickedButtonParamlib()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pMarker == NULL)
	{
		return;
	}
	PEntMgr  pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}
	CString  strPenName;

	if (gf_DlgPenParamLib(this, E3_PenBoxGetPenParam(m_penCur), m_pMarker, strPenName) == IDOK)
	{
		PMarkParam pParam = E3_PenBoxGetParamLibFindParam(strPenName);
		if (pParam != NULL)
		{ 
			PPenBox pPenBox = E3_EntMgrGetPenBox(pEM);
			PMarkPen pPen = E3_PenBoxGetPen(pPenBox,m_nCurPenIndex);
			if (pPen == NULL)
			{
				return;
			}
			E3_PenBoxSetPenUseDefParam(pPen, FALSE);
			E3_PenBoxSetPenParam(pPen, pParam);

			UpdatePenList(); 
			ShowCurPenParam(m_nCurPenIndex);

			SendMessage(WM_USER_LASERPARAMCHANGED, 0, 0);
		}
	} 
}


void CDialogPenbox::OnBnClickedButtonListonoff()
{
	// TODO: 在此添加控件通知处理程序代码
	gf_GetSysParam()->SetParamInt(DOUBLE_PARAM_NUDGESMALLDIST,gf_GetSysParam()->GetParamInt(DOUBLE_PARAM_NUDGESMALLDIST)?0:1);

	m_btnShowOnOff.SetShow(!gf_GetSysParam()->GetParamInt(DOUBLE_PARAM_NUDGESMALLDIST));
	GetDlgItem(IDC_LIST2)->ShowWindow(!gf_GetSysParam()->GetParamInt(DOUBLE_PARAM_NUDGESMALLDIST));
	AutoLayout();
}
