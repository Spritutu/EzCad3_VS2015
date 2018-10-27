// DlgEntList.cpp : 实现文件
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "DlgEntList.h"
#include "QGlobal.h"
#include "usermessdef.h" 
#include "QGlobal.h" 
#include "Quser.h"
#include "Qdib.h"
#include "..\Ezcad3View.h"
#include "qdlg.h"  
#define SUBCMD_ORDER_PREV       0
#define SUBCMD_ORDER_NEXT       1
#define SUBCMD_ORDER_TOP        3
#define SUBCMD_ORDER_BOTTOM     4
#define SUBCMD_ORDER_SHOW       5
#define SUBCMD_ORDER_HIDE       6
#define SUBCMD_ORDER_SHOWALL    7
#define SUBCMD_ORDER_INDEX     8
// CDlgEntList 对话框


int GetEntImage(PEntity pEnt)
{
	ASSERT(pEnt!=NULL);
	int nImage = 0;
	switch(E3_GetEntType(pEnt))
	{
	case ENTTYPE_CURVE2D:
		nImage = IMAGEID_CURVE;
		break;
		case ENTTYPE_CURVE3D:
		nImage = IMAGEID_CURVE3D;
		break;
	case ENTTYPE_POINT2D:
		nImage = IMAGEID_POINT;
		break;
	case ENTTYPE_RECT2D:
		nImage = IMAGEID_RECT;
		break;
	case ENTTYPE_CIRCLE2D:
		nImage = IMAGEID_CIRCLE;
		break;
	case ENTTYPE_ELLIPSE2D:
		nImage = IMAGEID_ELLPISE;
		break;
	case ENTTYPE_POLYGON2D:
		nImage = IMAGEID_POLYGON;
		break;
	case ENTTYPE_SPIRAL2D:
		nImage = IMAGEID_SPIRAL;
				break;
	case ENTTYPE_COMBINE:
		nImage = IMAGEID_COMBINE;
		break;	
	case ENTTYPE_GROUP:
		nImage = IMAGEID_GROUP;
		break;	
	case ENTTYPE_HATCH_GROUP:
		nImage = IMAGEID_HATCHGROUP;
		break;
	case ENTTYPE_BITMAP:
		nImage = IMAGEID_BITMAP;
		break;
	case ENTTYPE_VECTORFILE:
		nImage = IMAGEID_VECTORFILE;
		break;
	case ENTTYPE_TEXT:
		nImage = IMAGEID_TEXT;
		break;
	case ENTTYPE_PATHTEXT:
		nImage = IMAGEID_PATHTEXT;
		break;
	case ENTTYPE_CIRCLETEXT:
		nImage = IMAGEID_CIRCLETEXT;
		break;
	case ENTTYPE_TIMERDELAY:
		nImage = IMAGEID_TIMER;
		break;
	case ENTTYPE_IOINPUT:
		nImage = IMAGEID_INPUT;
		break;
	case ENTTYPE_IOINPUTJUMP:
		nImage = IMAGEID_INPUTJUMP;
		break;
	case ENTTYPE_IOOUTPUT:
		nImage = IMAGEID_OUTPUT;
		break;
	case ENTTYPE_EXTAXIS:
		nImage = IMAGEID_EXTAXIS;
		break;
	case ENTTYPE_FLYMOVEDIST:
		nImage = IMAGEID_FLYDIST;
		break;
	case ENTTYPE_SUPERTEXT:
		nImage = IMAGEID_TEXT;
		break;
	case ENTTYPE_MESH3D:
		nImage = IMAGEID_MESH3D;
		break;
	case ENTTYPE_SLICE3D:
		nImage = IMAGEID_SLICE3D;
		break;
	case ENTTYPE_PROJECT3D:
		nImage = IMAGEID_PROJECT3D;
		break; 
	case ENTTYPE_INDEX:
		nImage = IMAGEID_INDEX;
		break;
	case ENTTYPE_CCD:
		nImage = IMAGEID_CCD;
		break;
	default:
		nImage = IMAGEID_UNKNOW;
		break;
	}
	return nImage;
}

IMPLEMENT_DYNAMIC(CDlgEntList, CDialog)

CDlgEntList::CDlgEntList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEntList::IDD, pParent)
{
	m_bDragging=FALSE;
	m_pDragImage = NULL;
}

CDlgEntList::~CDlgEntList()
{

}

void CDlgEntList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTCTRL_ENT, m_listEnt);
}


BEGIN_MESSAGE_MAP(CDlgEntList, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LISTCTRL_ENT, OnCustomdrawList)
	ON_NOTIFY(NM_CLICK, IDC_LISTCTRL_ENT, OnClickListEnt) 
	ON_NOTIFY(NM_DBLCLK, IDC_LISTCTRL_ENT, OnDblclkListEnt) 
	ON_NOTIFY(NM_RCLICK, IDC_LISTCTRL_ENT, OnRclickListEnt)

	ON_WM_DESTROY() 
	ON_WM_MOUSEMOVE() 
	ON_WM_LBUTTONUP()
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LISTCTRL_ENT, OnBegindragList)

	ON_MESSAGE(WM_USER_CHANGECURLAYER ,OnUserChangeEntity)	
	ON_MESSAGE(WM_USER_CHANGEENTITY ,OnUserChangeEntity)	
	ON_MESSAGE(WM_USER_PICKCHANGE,OnUserPickChange)
	ON_MESSAGE(WM_USER_PICKLOCKCHANGE,OnUserPickLockChange)

	ON_COMMAND(ID_ORDER_MOVEPREV, OnOrderPrev) 
	ON_COMMAND(ID_ORDER_MOVENEXT, OnOrderNext) 
	ON_COMMAND(ID_ORDER_MOVETOP, OnOrderTop) 
	ON_COMMAND(ID_ORDER_MOVEBOTTOM, OnOrderBottom)
	ON_COMMAND(ID_ORDER_MOVEINDEX, OnOrderIndex)
	
	ON_COMMAND(ID_ORDER_SHOW, OnOrderShow) 
	ON_COMMAND(ID_ORDER_SHOWALL, OnOrderShowAll) 
	ON_COMMAND(ID_ORDER_HIDE, OnOrderHide)  
	ON_WM_KEYDOWN()
	ON_NOTIFY(LVN_KEYDOWN, IDC_LISTCTRL_ENT, &CDlgEntList::OnKeydownListctrlEnt)
END_MESSAGE_MAP()

void CDlgEntList::OnDestroy()
{
	SaveLastListWidth( );
}
// CDlgEntList 消息处理程序

void CDlgEntList::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CWnd* pList = GetDlgItem(IDC_LISTCTRL_ENT);
	if(pList!=NULL)
	{
		pList->MoveWindow(1,1,cx-2,cy-2);
	}
}
void CDlgEntList::OnOK()
{
	// TODO: Add extra validation here

}

void CDlgEntList::OnCancel()
{
	// TODO: Add extra cleanup here	

}


BOOL CDlgEntList::OnInitDialog()
{
	CDialog::OnInitDialog();	
	
	bmpShowOn.LoadBitmap(IDB_BITMAP_SHOWON);
	bmpShowOff.LoadBitmap(IDB_BITMAP_SHOWOFF);  

	 

	bmpEntType[IMAGEID_CURVE].LoadBitmap(IDB_BITMAP_ENT0);
	bmpEntType[IMAGEID_POINT].LoadBitmap(IDB_BITMAP_ENT1);
	bmpEntType[IMAGEID_RECT].LoadBitmap(IDB_BITMAP_ENT2);
	bmpEntType[IMAGEID_CIRCLE].LoadBitmap(IDB_BITMAP_ENT3);
	bmpEntType[IMAGEID_ELLPISE].LoadBitmap(IDB_BITMAP_ENT4);
	bmpEntType[IMAGEID_POLYGON].LoadBitmap(IDB_BITMAP_ENT5); 
	bmpEntType[IMAGEID_COMBINE].LoadBitmap(IDB_BITMAP_ENT6);
	bmpEntType[IMAGEID_HATCHGROUP].LoadBitmap(IDB_BITMAP_ENT7);
	bmpEntType[IMAGEID_BITMAP].LoadBitmap(IDB_BITMAP_ENT8);
	bmpEntType[IMAGEID_VECTORFILE].LoadBitmap(IDB_BITMAP_ENT9);
	bmpEntType[IMAGEID_TEXT].LoadBitmap(IDB_BITMAP_ENT10);
	bmpEntType[IMAGEID_PATHTEXT].LoadBitmap(IDB_BITMAP_ENT10); 
	bmpEntType[IMAGEID_GROUP].LoadBitmap(IDB_BITMAP_ENT12); 
	bmpEntType[IMAGEID_TIMER].LoadBitmap(IDB_BITMAP_ENT13);
	bmpEntType[IMAGEID_INPUT].LoadBitmap(IDB_BITMAP_ENT14);
	bmpEntType[IMAGEID_OUTPUT].LoadBitmap(IDB_BITMAP_ENT15); 
	bmpEntType[IMAGEID_CIRCLETEXT].LoadBitmap(IDB_BITMAP_ENT10);
	bmpEntType[IMAGEID_EXTAXIS].LoadBitmap(IDB_BITMAP_ENT16);
	bmpEntType[IMAGEID_FLYDIST].LoadBitmap(IDB_BITMAP_ENT25);
	bmpEntType[IMAGEID_SPIRAL].LoadBitmap(IDB_BITMAP_ENT19);
	bmpEntType[IMAGEID_MESH3D].LoadBitmap(IDB_BITMAP_ENT20);
	bmpEntType[IMAGEID_SLICE3D].LoadBitmap(IDB_BITMAP_ENT21);
	bmpEntType[IMAGEID_CURVE3D].LoadBitmap(IDB_BITMAP_ENT22);
	bmpEntType[IMAGEID_PROJECT3D].LoadBitmap(IDB_BITMAP_ENT23);  
  	bmpEntType[IMAGEID_UNKNOW].LoadBitmap(IDB_BITMAP_ENT24); 
	bmpEntType[IMAGEID_INDEX].LoadBitmap(IDB_BITMAP_ENT27);
	bmpEntType[IMAGEID_CCD].LoadBitmap(IDB_BITMAP_ENT26);
	bmpEntType[IMAGEID_INPUTJUMP].LoadBitmap(IDB_BITMAP_ENT28);

	InitialList(); 
	
	return TRUE;
}

 
void CDlgEntList::SetCurFont()
{
	::DeleteObject(m_fontCur.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fontCur.CreateFontIndirect(&lf);

	m_listEnt.SetFont(&m_fontCur);
	 
}


BOOL CDlgEntList::GetLastListWidth(int& bItem0,int& bItem1,int& bItem2, int& bItem3)
{
	CWinApp* pWinApp = AfxGetApp();
	
	int nItemWidth0 = pWinApp->GetProfileInt(_T("ENTLIST"),_T("ITEMWIDTH0"),0);
	int nItemWidth1 = pWinApp->GetProfileInt(_T("ENTLIST"),_T("ITEMWIDTH1"),0);
	int nItemWidth2 = pWinApp->GetProfileInt(_T("ENTLIST"),_T("ITEMWIDTH2"),0); 
	int nItemWidth3 = pWinApp->GetProfileInt(_T("ENTLIST"), _T("ITEMWIDTH3"), 0);

	if(nItemWidth0<=0 || nItemWidth1<=0 || nItemWidth2<=0 || nItemWidth3 <= 0)
	{
		return FALSE;
	}
	bItem0 = nItemWidth0;
	bItem1 = nItemWidth1;
	bItem2 = nItemWidth2;
	bItem3 = nItemWidth3;
	return TRUE;
}

void CDlgEntList::SaveLastListWidth( )
{
	CWinApp* pWinApp = AfxGetApp();
	pWinApp->WriteProfileInt(_T("ENTLIST"),_T("ITEMWIDTH0"),m_listEnt.GetColumnWidth (0) );
	pWinApp->WriteProfileInt(_T("ENTLIST"),_T("ITEMWIDTH1"),m_listEnt.GetColumnWidth (1) );
	pWinApp->WriteProfileInt(_T("ENTLIST"),_T("ITEMWIDTH2"),m_listEnt.GetColumnWidth (2) ); 
	pWinApp->WriteProfileInt(_T("ENTLIST"), _T("ITEMWIDTH3"), m_listEnt.GetColumnWidth(3));
}

void CDlgEntList::InitialList()
{
	m_listImage.Create(IDB_BITMAP_ENTTYPE, 16, 1, RGB(0,255,0));	
	//m_listImage.Create(IDB_BITMAP_ENTTYPE2, 24, 24, RGB(0,255,0));	
	m_listEnt.SetImageList (&m_listImage, LVSIL_SMALL); 

	//m_listEnt.SetFont(CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT)));  

	m_listEnt.SetExtendedStyle ( LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES);		
	SetCurFont();

	CRect rect;
	m_listEnt.GetWindowRect(&rect);	
	
	m_listEnt.InsertColumn ( 0, _T(""),  LVCFMT_LEFT, -1, 0 ); 
	m_listEnt.InsertColumn(1, QGlobal::gf_Str(_T("No"), _T("No.")), LVCFMT_LEFT, -1, 1);
	m_listEnt.InsertColumn (2, QGlobal::gf_Str(_T("NAME"),_T("Name")),  LVCFMT_LEFT, -1,1 );
	m_listEnt.InsertColumn (3, QGlobal::gf_Str(_T("TYPE"),_T("Type")),  LVCFMT_LEFT, -1,2 );
	 
	int  bItem0=40;
	int  bItem1 = 20;
	int  bItem2=100;
	int  bItem3=60;
	if(GetLastListWidth( bItem0, bItem1, bItem2, bItem3 ))
	{
		m_listEnt.SetColumnWidth ( 0, bItem0 );
		m_listEnt.SetColumnWidth ( 1, bItem1);
		m_listEnt.SetColumnWidth ( 2, bItem2 );
		m_listEnt.SetColumnWidth(3, bItem3);
	}
	else
	{
		m_listEnt.SetColumnWidth ( 0, rect.Width() * 4/22 );
		m_listEnt.SetColumnWidth(1, rect.Width()  *  2 / 22);
		m_listEnt.SetColumnWidth ( 2, rect.Width() * 10/22 );
		m_listEnt.SetColumnWidth ( 3, rect.Width() * 6/22 );
	}

	if(E3_GetCmdMgr()!=NULL)
	{
		E3_CmdMgrAddEntityWnd(E3_GetCmdMgr(), this );//告诉命令管理器当前窗口需要接收系统消息
	}

}
 
void CDlgEntList::AutoAdjustListWidth()
{
	CRect rect,rectItem0;	 
	m_listEnt.GetWindowRect(&rect);	
	ListView_GetSubItemRect(m_listEnt,0,0,LVIR_BOUNDS,&rectItem0); 
	if(rectItem0.Height()>10)
	{
		
		 CDC* pDC = this->GetDC();
		 CFont* pOldFont=(CFont*)pDC->SelectObject(&m_fontCur);
		CSize size = pDC->GetTextExtent(QGlobal::gf_Str(_T("POLYGON"),_T("Polygon")));
		pDC->SelectObject(pOldFont);  

		int nScrollBarWidht = GetSystemMetrics(SM_CXVSCROLL);
		int nItemHeight = rectItem0.Height();

		int nItemWidth0= nItemHeight*2;
		int nItemWidth2= size.cx+4;
		int nItemWidth1= rect.Width()-nItemWidth0-nItemWidth2-nScrollBarWidht-4;
		if(nItemWidth1<10)
		{
			nItemWidth1=10;
		}

		m_listEnt.SetColumnWidth ( 0, nItemWidth0 );
		m_listEnt.SetColumnWidth ( 1, nItemWidth1 );
		m_listEnt.SetColumnWidth ( 2, nItemWidth2 );
	}
}
     
void CDlgEntList::OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

	// Take the default processing unless we set this to something else below.
	*pResult = 0;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.
	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		// This is the notification message for an item.  We'll request
		// notifications before each subitem's prepaint stage.
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ((CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage)
	{
		// This is the prepaint stage for a subitem.         
		int nItem = (int)pLVCD->nmcd.dwItemSpec;
		int nSubItem = pLVCD->iSubItem;

		PEntity  pEnt = (PEntity)m_listEnt.GetItemData(nItem);
		ASSERT(pEnt != NULL);

		if (nItem < 0 || pEnt == NULL)
		{
			// Tell Windows to paint the control itself.
			*pResult = CDRF_DODEFAULT;
			return;
		}

		CString strText;
		CDC*  pDC = CDC::FromHandle(pLVCD->nmcd.hdc);
		CRect rect;
		ListView_GetSubItemRect(::GetDlgItem(m_hWnd, IDC_LISTCTRL_ENT), nItem, nSubItem, LVIR_BOUNDS, &rect);
		COLORREF	textColor = ::GetSysColor(COLOR_WINDOWTEXT);    //文本的颜色 
		BOOL bItemSelect = m_listEnt.GetItemState(nItem, LVIS_SELECTED);

		if (m_listEnt.GetItemState(nItem, LVIS_DROPHILITED))
		{//高亮
			bItemSelect = TRUE;
		}

		if (bItemSelect)
		{
			CBrush pBrush(::GetSysColor(COLOR_HIGHLIGHT));
			pDC->FillRect(&rect, &pBrush);//绘制背景
			textColor = 0x00FFFFFF & ~(textColor);	//文本颜色反转		
		}
		else
		{
			CBrush pBrush(m_listEnt.GetBkColor());
			pDC->FillRect(&rect, &pBrush);//绘制背景 	
		}


		if (nSubItem == 0)
		{
			int nImage = GetEntImage(pEnt);
			DWORD rop = bItemSelect ? SRCAND : SRCCOPY;

			CRect rectImage(rect.left, rect.top, rect.left + 2 * rect.Height(), rect.bottom);
			if (!E3_IsEntHide(pEnt))
			{
				gf_StretchDrawBmp(pLVCD->nmcd.hdc, &bmpShowOn, rectImage.left, rectImage.top, rectImage.Height(), rectImage.Height() - 2, rop);
			}
			else
			{
				gf_StretchDrawBmp(pLVCD->nmcd.hdc, &bmpShowOff, rectImage.left, rectImage.top, rectImage.Height(), rectImage.Height() - 2, rop);
			}

			rectImage.left += rectImage.Height();
			gf_StretchDrawBmp(pLVCD->nmcd.hdc, &bmpEntType[nImage], rectImage.left, rectImage.top, rectImage.Height(), rectImage.Height(), rop);

		}

		strText = m_listEnt.GetItemText(nItem, nSubItem);
		if (nSubItem == 1)
		{
			strText.Format(_T("%d"), nItem + 1);
		}
		if (!strText.IsEmpty())
		{
			pDC->SetTextColor(textColor);
			int mode = pDC->SetBkMode(TRANSPARENT); 
			pDC->ExtTextOut(rect.left + 2, rect.top + 1, ETO_CLIPPED, &rect, strText, NULL);
			pDC->SetBkMode(mode);
		}

		*pResult = CDRF_SKIPDEFAULT;//drew the item manually. The control will not draw the item.  
	}
}



//接受数据库删除对象消息，更新列表显示
LRESULT CDlgEntList::OnUserChangeEntity(WPARAM wParam, LPARAM lParam)
{
//	TRACE(_T("DlgEntList::OnUserChangeEntity\n"));
	UpdateCurEntList();
	return 0;
}


//接受数据库的选取对象改变消息，更新列表显示
LRESULT CDlgEntList::OnUserPickChange(WPARAM wParam, LPARAM lParam)
{	
//	TRACE(_T("DlgEntList::OnUserPickChange\n"));
	OnUserPickChange();
	return 0;
}

LRESULT CDlgEntList::OnUserPickLockChange(WPARAM wParam, LPARAM lParam)
{	
	return 0;
}


void CDlgEntList::UpdateCurEntList()
{
	if(E3_GetCmdMgr()==NULL)
	{
		return;
	}

	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if(pEM==NULL)
	{
		return;
	} 

	PEntity pCurLayer = E3_EntMgrGetCurLayer(pEM);
	if (pCurLayer==NULL)
		return;
	 
	int nEntIndex = 0;
	PEntity pEnt = E3_GetEntChildHead(pCurLayer);
	while(pEnt!=NULL)
	{
		if(nEntIndex<m_listEnt.GetItemCount())
		{//列表有对象信息
			CEntity* pEntItem = (CEntity*)m_listEnt.GetItemData(nEntIndex);
			if(pEntItem==pEnt)
			{//对象没变。可能参数变
				CString strName = m_listEnt.GetItemText( nEntIndex,1);
				if(strName!= E3_GetEntName(pEnt))
				{//名字改变了
					m_listEnt.SetItemText( nEntIndex,2, E3_GetEntName(pEnt));
				}
			}
			else
			{//对象已经改变
				m_listEnt.SetItemData( nEntIndex,(DWORD_PTR)pEnt);		
				m_listEnt.SetItem(nEntIndex, 0, LVIF_IMAGE , _T(""),GetEntImage(pEnt), 0, 0,0);
				m_listEnt.SetItem(nEntIndex, 2, LVIF_TEXT, E3_GetEntName(pEnt),0, 0, 0,0);
				m_listEnt.SetItemText( nEntIndex,3,E3_GetEntTypeStr(pEnt));
			}
		}
		else
		{//列表单元数不够
			m_listEnt.InsertItem(nEntIndex,_T(""),GetEntImage(pEnt));
			ASSERT(pEnt!=NULL);
			m_listEnt.SetItemData( nEntIndex,(DWORD_PTR)pEnt);			
		 
		 	m_listEnt.SetItem(nEntIndex, 2, LVIF_TEXT, E3_GetEntName(pEnt),0, 0, 0,0);
			m_listEnt.SetItemText( nEntIndex,3, E3_GetEntTypeStr(pEnt));

			PEntity pEntTest = (PEntity)m_listEnt.GetItemData(nEntIndex);
			ASSERT(pEntTest==pEnt);
		}	

		pEnt = E3_GetEntNext(pEnt);
		nEntIndex++;
	}

	while(m_listEnt.GetItemCount()> nEntIndex)
	{//删除无效的单元
		m_listEnt.DeleteItem(m_listEnt.GetItemCount()-1);
	}
	
	int nItemCoun = m_listEnt.GetItemCount();
	for(int nItem=0;nItem<nItemCoun;nItem++)
	{//验证
		pEnt = (PEntity)m_listEnt.GetItemData(nItem);
		ASSERT(pEnt!=NULL);
	}	
	m_listEnt.Invalidate();

	OnUserPickChange();
}
 
//接受数据库的选取对象改变消息，更新列表显示
void CDlgEntList::OnUserPickChange()
{	
	for(int nItem=0;nItem<m_listEnt.GetItemCount();nItem++)
	{
		PEntity pEnt = (PEntity)m_listEnt.GetItemData(nItem);
		if(pEnt==NULL)
		{
			ASSERT(0);
			return;
		}
		 

		if(E3_IsEntLock(pEnt))
		{				
			if(E3_IsEntPicked(pEnt))
			{
				if(!m_listEnt.GetItemState(nItem,LVIS_SELECTED))
				{
					m_listEnt.SetItemState(nItem,LVIS_SELECTED,LVIS_SELECTED);
				}
			}
			else
			{
				m_listEnt.SetItemState(nItem,~LVIS_SELECTED,LVIS_SELECTED);
			}
		}
		else
		{
			if(E3_IsEntPicked(pEnt))
			{//对象被选择					
				if(!m_listEnt.GetItemState(nItem,LVIS_SELECTED))
				{//单元没被选择
					m_listEnt.SetItemState(nItem,LVIS_SELECTED,LVIS_SELECTED);
				}
			}
			else
			{//对象没被选择	
				if(m_listEnt.GetItemState(nItem,LVIS_SELECTED))
				{//单元被选择
					m_listEnt.SetItemState(nItem,~LVIS_SELECTED,LVIS_SELECTED);
				}
			}
		}
	}	

	if (gf_GetCurEzcad3View() != NULL)
	{
		gf_GetCurEzcad3View()->GetActiveView()->SetFocus();
	}
}


void CDlgEntList::OnDblclkListEnt(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
	if (E3_GetCmdMgr() == NULL)
	{
		return;
	}
	if (!gf_GetUserMgr()->GetCurUser()->m_bEnableEditEntParam)
	{
		return;
	}

	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}

	LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE)pNMHDR;
	int nItemSel = temp->iItem;  //get the row number
	int nSubItem = temp->iSubItem;//get the column number

	if (nItemSel >= 0 && nItemSel < m_listEnt.GetItemCount())
	{
		PEntity pEntSel = (PEntity)m_listEnt.GetItemData(nItemSel);
		if (pEntSel != NULL)
		{
			if (nSubItem == 0)
			{//改变是否显示或隐藏
				
				E3_EntMgrChangeEntHideState(pEM, pEntSel); 

				E3_CmdMgrInvalidate();

				if (gf_GetCurEzcad3View() != NULL)
				{
					gf_GetCurEzcad3View()->Invalidate();
				}
			}
			else
			{//改变名称 
				CString str = E3_GetEntName(pEntSel);
				if (gf_DlgInputOne(this, str, QGlobal::gf_Str(_T("CHANGENAME"), _T("Change Name")), QGlobal::gf_Str(_T("NAME"), _T("Name")), _T("")) == IDOK)
				{
					E3_EntMgrChangeEntName(pEM, pEntSel, str); 
				}
			}
		}
	}
}

void CDlgEntList::OnClickListEnt(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	OnUserSelectEntFromList();

	*pResult = 0;
}



//用户从列表控件选择对象
void CDlgEntList::OnUserSelectEntFromList()
{ 
	if(E3_GetCmdMgr()==NULL)
	{
		return;
	}
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}

	PEntity pCurLayer = E3_EntMgrGetCurLayer(pEM);
	if (pCurLayer == NULL)
		return;

	//对象选取状态
	E3_EntMgrResetPickParam(pEM);

	BOOL bStartPick = FALSE;
	CEntity* pEnt = NULL;
	for(int nItem=0;nItem<m_listEnt.GetItemCount();nItem++)
	{
		pEnt = (CEntity*)m_listEnt.GetItemData(nItem);
		ASSERT(pEnt!=NULL);	

		if(pEnt==NULL|| E3_IsEntHide(pEnt) || E3_IsEntLock(pEnt))
		{
			continue;
		}

		if(m_listEnt.GetItemState(nItem,LVIS_SELECTED))
		{//单元被选择
			if(!E3_IsEntPicked(pEnt))
			{//对象没被选择
				if(!bStartPick)
				{
					bStartPick = TRUE;
					E3_EntMgrBeginPick(pEM);						
				}
				E3_EntMgrPickEntity(pEM,pEnt, TRUE);
			}
		}
		else
		{//单元没被选择
			if(E3_IsEntPicked(pEnt))
			{//对象被选择
				if(!bStartPick)
				{
					bStartPick = TRUE;
					E3_EntMgrBeginPick(pEM);						
				}
				E3_EntMgrPickEntity(pEM, pEnt, FALSE);
			}
		}		
	}
	if(bStartPick)
	{		
		E3_EntMgrEndPick(pEM);
		 
		E3_CmdMgrInvalidate();

		if(gf_GetCurEzcad3View()!=NULL)
		{
			gf_GetCurEzcad3View()->Invalidate();
		} 
	} 
}


void CDlgEntList::OnRclickListEnt(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	if (!gf_GetUserMgr()->GetCurUser()->m_bEnableEditEntParam)
	{
		return;
	}

	if (m_bDragging)
	{
		*pResult = 1;
		return;
	}

	HWND hWnd1 = ::GetDlgItem(m_hWnd, IDC_LIST2);
	LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE)pNMHDR;

	int nItem = temp->iItem;  //get the row number
	int nSubItem = temp->iSubItem;//get the column number

	if (E3_GetCmdMgr() == NULL)
	{
		return;
	}
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}

	if (nItem < 0)
	{
		return;
	}

	CMenu RightMenu;
	RightMenu.LoadMenu(IDR_MENU_ORDER);

	CMenu* pMenu = RightMenu.GetSubMenu(0);
	if (pMenu == NULL)
		return;
	pMenu->ModifyMenu(ID_ORDER_MOVEPREV, MF_BYCOMMAND, ID_ORDER_MOVEPREV, QGlobal::gf_Str(_T("MOVETOPREV"), _T("Move to previous")));
	pMenu->ModifyMenu(ID_ORDER_MOVENEXT, MF_BYCOMMAND, ID_ORDER_MOVENEXT, QGlobal::gf_Str(_T("MOVETONEXT"), _T("Move to next")));
	pMenu->ModifyMenu(ID_ORDER_MOVETOP, MF_BYCOMMAND, ID_ORDER_MOVETOP, QGlobal::gf_Str(_T("MOVETOTOP"), _T("Move to top")));
	pMenu->ModifyMenu(ID_ORDER_MOVEBOTTOM, MF_BYCOMMAND, ID_ORDER_MOVEBOTTOM, QGlobal::gf_Str(_T("MOVETOBOTTOM"), _T("Move to bottom")));
	pMenu->ModifyMenu(ID_ORDER_MOVEINDEX, MF_BYCOMMAND, ID_ORDER_MOVEINDEX, QGlobal::gf_Str(_T("MOVETOINDEX"), _T("Move to index")));
	pMenu->ModifyMenu(ID_ORDER_SHOW, MF_BYCOMMAND, ID_ORDER_SHOW, QGlobal::gf_Str(_T("SHOW"), _T("Show")));
	pMenu->ModifyMenu(ID_ORDER_SHOWALL, MF_BYCOMMAND, ID_ORDER_SHOWALL, QGlobal::gf_Str(_T("SHOWALL"), _T("Show all")));
	pMenu->ModifyMenu(ID_ORDER_HIDE, MF_BYCOMMAND, ID_ORDER_HIDE, QGlobal::gf_Str(_T("HIDE"), _T("Hide")));

	CPoint point = temp->ptAction;
	ClientToScreen(&point);
	pMenu->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y, this);

	*pResult = 1;
}
 


void CDlgEntList::OnOrderPrev() 
{
	ChangeOrder(SUBCMD_ORDER_PREV);

} 
 
void CDlgEntList::OnOrderNext() 
{
	ChangeOrder(SUBCMD_ORDER_NEXT);
} 

void CDlgEntList::OnOrderTop() 
{
	ChangeOrder(SUBCMD_ORDER_TOP);
}
 
void CDlgEntList::OnOrderBottom() 
{
	ChangeOrder(SUBCMD_ORDER_BOTTOM);
} 

void CDlgEntList::OnOrderIndex()
{
	if (E3_GetCmdMgr() == NULL)
	{
		return;
	}

	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}

	PEntity pCurLayer = E3_EntMgrGetCurLayer(pEM);
	if (pCurLayer == NULL)
		return;
	PEntity pEnt = E3_GetEntChildHead(pCurLayer);

	int index = 0;
	while (pEnt != NULL)
	{
		if (E3_IsEntPicked(pEnt))
		{
			break;			
		}
		index++;
		pEnt = E3_GetEntNext(pEnt);
	}

 
	CString str;
	str.Format(_T("%d"), index+1);
	if (gf_DlgInputOne(this, str, QGlobal::gf_Str(_T("MOVETOINDEX"), _T("Move to index")), QGlobal::gf_Str(_T("No"), _T("No.")), _T("")) == IDOK)
	{ 
		index = QGlobal::ATOI(str);
		if (index < 0)
		{
			index = 1;
		}
		ChangeOrder(SUBCMD_ORDER_INDEX, index-1);
	}	
}


void CDlgEntList::OnOrderShow() 
{ 
	OnShow(FALSE);
}
void CDlgEntList::OnOrderShowAll() 
{ 
	OnShow(TRUE);
}
void CDlgEntList::OnShow(BOOL bAll) 
{ 
	if(E3_GetCmdMgr()==NULL)
	{
		return;
	}
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}

	PEntity pCurLayer = E3_EntMgrGetCurLayer(pEM);
	if (pCurLayer == NULL)
		return;

	POSITION pos;
	int nItem =-1;
	if(bAll)
	{
		nItem=0;
	}
	else
	{
		pos = m_listEnt.GetFirstSelectedItemPosition();
		nItem = m_listEnt.GetNextSelectedItem(pos);
	}

	if(nItem >= 0||bAll )
	{
		E3_EntMgrResetPickParam(pEM);
		E3_EntMgrBeginPick(pEM);

		E3_EntMgrBeginUndo(pEM,QGlobal::gf_Str(_T("MODIFY"),_T("Modify"))); 
		if(bAll)
		{
			PEntity pEntSel = E3_GetEntChildHead(pCurLayer);
			while(pEntSel !=NULL)
			{
				E3_EntMgrUDModify(pEM, pEntSel);
				E3_EntHide(pEntSel,FALSE);			 		 
				E3_EntMgrPickEntity(pEM, pEntSel, TRUE);
				pEntSel = E3_GetEntNext(pEntSel); 
			} 
		}
		else
		{
			CEntity* pEntSel;
			while(nItem >= 0)
			{
				pEntSel = (CEntity*)m_listEnt.GetItemData(nItem);
				E3_EntMgrUDModify(pEM, pEntSel);
				E3_EntHide(pEntSel, FALSE);
				E3_EntMgrPickEntity(pEM, pEntSel, TRUE);
				nItem = m_listEnt.GetNextSelectedItem(pos);
			} 
		}
		  
		E3_EntMgrEndUndo(pEM); 
		E3_EntMgrEndPick(pEM);
		E3_CmdMgrInvalidate();
	} 
}
 
void CDlgEntList::OnOrderHide() 
{
	if(E3_GetCmdMgr()==NULL)
	{
		return;
	}
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}

	PEntity pCurLayer = E3_EntMgrGetCurLayer(pEM);
	if (pCurLayer == NULL)
		return;

	POSITION pos = m_listEnt.GetFirstSelectedItemPosition();
	int nItem = m_listEnt.GetNextSelectedItem(pos);
	if(nItem >= 0)
	{
		E3_EntMgrResetPickParam(pEM);
		E3_EntMgrBeginPick(pEM); 
		E3_EntMgrBeginUndo(pEM,QGlobal::gf_Str(_T("MODIFY"),_T("Modify"))); 
		
		while(nItem >= 0)
		{
			CEntity* pEntSel = (CEntity*)m_listEnt.GetItemData(nItem);
			E3_EntMgrUDModify(pEM,pEntSel);
			E3_EntHide(pEntSel,TRUE);
			nItem = m_listEnt.GetNextSelectedItem(pos);
		} 
		  
		E3_EntMgrEndUndo(pEM); 
		E3_EntMgrEndPick(pEM);
		E3_CmdMgrInvalidate();
	} 

} 


void CDlgEntList::ChangeOrder(int subCmd,int param)
{
	if(E3_GetCmdMgr()==NULL)
	{
		return;
	}

	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}

	PEntity pCurLayer = E3_EntMgrGetCurLayer(pEM);
	if (pCurLayer == NULL)
		return;

	int nPick = E3_EntMgrPickCount(pEM);
	if(nPick > 0)
	{		
		//拷贝被选对象列表,其序列与数据库中的对象顺序一致
		TagPickItem* pItemList = new TagPickItem[nPick];

		nPick = E3_EntMgrCopyPickList(pEM,pItemList, nPick);

		E3_EntMgrBeginPick(pEM);
		E3_EntMgrBeginUndo(pEM,QGlobal::gf_Str(_T("CHANGEORDER"),_T("Change Order")));	 
			
		if(subCmd==SUBCMD_ORDER_PREV)
		{
			PEntity pEntPrev = E3_GetEntPrev(pItemList[0].m_pPicked);
			if(pEntPrev!=NULL)
			{
				E3_EntMgrUDMoveToBefore(pEM, pItemList[0].m_pPicked, pEntPrev); 
			}
		}
		else if(subCmd==SUBCMD_ORDER_NEXT)
		{
			PEntity pEntNext = E3_GetEntNext(pItemList[nPick-1].m_pPicked);
			if(pEntNext!=NULL)
			{
				E3_EntMgrUDMoveToAfter(pEM, pItemList[0].m_pPicked, pEntNext); 			
			}
		}
		else if(subCmd==SUBCMD_ORDER_TOP)
		{			
			PEntity pEntHead = E3_GetEntChildHead(pCurLayer);
			if(pEntHead!=pItemList[0].m_pPicked)
			{
				E3_EntMgrUDMoveToBefore(pEM, pItemList[0].m_pPicked, pEntHead); 
			}
		}
		else if(subCmd==SUBCMD_ORDER_BOTTOM)
		{
			PEntity pEntTail = E3_GetEntChildTail(pCurLayer);
			if(pEntTail!=pItemList[0].m_pPicked)
			{
				E3_EntMgrUDMoveToAfter(pEM, pItemList[0].m_pPicked, pEntTail); 
			}			
		} 
		else if (subCmd == SUBCMD_ORDER_INDEX)
		{
			PEntity pEnt = E3_GetEntChildHead(pCurLayer);
			int i = 0;
			while (pEnt != NULL)
			{
				if (!E3_IsEntPicked(pEnt))
				{
					if (param== 0 || i==param)
					{
						break;
					}
					i++;
				}
				pEnt = E3_GetEntNext(pEnt); 
			}		 
			if (pEnt == NULL)
			{
				pEnt = E3_GetEntChildTail(pCurLayer);
				if (pEnt != pItemList[0].m_pPicked)
				{ 
					E3_EntMgrUDMoveToAfter(pEM, pItemList[0].m_pPicked, pEnt);
				}
			}
			else if (pEnt != pItemList[0].m_pPicked)
			{
				E3_EntMgrUDMoveToBefore(pEM, pItemList[0].m_pPicked, pEnt);
			} 
		}		
		

		PEntity pEntFirst = pItemList[0].m_pPicked;
		for(int i=1;i<nPick;i++)
		{
			E3_EntMgrUDMoveToAfter(pEM, pItemList[0].m_pPicked, pEntFirst); 								
			pEntFirst = pItemList[i].m_pPicked;			
		}

		delete[] pItemList;
		E3_EntMgrEndUndo(pEM);
		E3_EntMgrEndPick(pEM);	
	}
}


void CDlgEntList::OnBegindragList(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (!gf_GetUserMgr()->GetCurUser()->m_bEnableEditEntParam)
	{
		return;
	}

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_nDragIndex = pNMListView->iItem;

	POINT pt;
	int nOffset = -10; //offset in pixels for drag image (positive is up and to the left; neg is down and to the right)
	if (m_listEnt.GetSelectedCount() > 1) //more than one item is selected
		pt.x = nOffset;
	pt.y = nOffset;

	m_pDragImage = m_listEnt.CreateDragImage(m_nDragIndex, &pt);
	ASSERT(m_pDragImage != NULL); //make sure it was created

	CBitmap bitmap;
	if (m_listEnt.GetSelectedCount() > 1) //more than 1 item in list is selected		
		bitmap.LoadBitmap(IDB_BITMAP_DRAG_MUL);
	else
		bitmap.LoadBitmap(IDB_BITMAP_DRAG_ONE);
	m_pDragImage->Replace(0, &bitmap, &bitmap);

	m_pDragImage->BeginDrag(0, CPoint(nOffset, nOffset - 4));
	m_pDragImage->DragEnter(GetDesktopWindow(), pNMListView->ptAction);

	m_bDragging = TRUE;

	SetCapture();

	*pResult = 0;
}


void CDlgEntList::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bDragging)
	{//正在拖拉		
		CPoint pt(point);	//get our current mouse coordinates
		ClientToScreen(&pt); //convert to screen coordinates
		m_pDragImage->DragMove(pt); //move the drag image to those coordinates
		// Unlock window updates (this allows the dragging image to be shown smoothly)
		m_pDragImage->DragShowNolock(false);

		//// Get the CWnd pointer of the window that is under the mouse cursor
		CWnd* pDropWnd = WindowFromPoint (pt);
		ASSERT(pDropWnd); //make sure we have a window

		//// If we drag outside current window we need to adjust the highlights displayed
		if (pDropWnd != &m_listEnt)
		{//If we drag out of the CListCtrl altogether				
			
			for(int i = 0; i <  m_listEnt.GetItemCount(); i++)
			{
				if(m_listEnt.GetItemState(i,LVIS_DROPHILITED))
				{//高亮
					m_listEnt.SetItemState(i, 0, LVIS_DROPHILITED);
					m_listEnt.RedrawItems(i, i);
				}				
			}			
			
			SetCursor(LoadCursor(NULL, IDC_NO));
		}
		else
		{
			// Get the item that is below cursor
			UINT uFlags;
			int nDropIndex = m_listEnt.HitTest(point, &uFlags);

			if(nDropIndex >=0)
			{
				for(int i = 0; i <  m_listEnt.GetItemCount(); i++)
				{
					if(nDropIndex==i)
					{
						if(!m_listEnt.GetItemState(i,LVIS_DROPHILITED))
						{//没高亮
							m_listEnt.SetItemState(i, LVIS_DROPHILITED, LVIS_DROPHILITED);
							m_listEnt.RedrawItems(i, i);							
						}
					}
					else
					{
						if(m_listEnt.GetItemState(i,LVIS_DROPHILITED))
						{//高亮
							m_listEnt.SetItemState(i, 0, LVIS_DROPHILITED);
							m_listEnt.RedrawItems(i, i);
						}
					}								
					m_listEnt.UpdateWindow();
				}	
			}		
		
			SetCursor(LoadCursor(NULL, IDC_ARROW));
		}
		// Lock window updates
		m_pDragImage->DragShowNolock(true);
	}
		
	CDialog::OnMouseMove(nFlags, point);
}


void CDlgEntList::OnLButtonUp(UINT nFlags, CPoint point) 
{ 
	if (m_bDragging)
	{
		 ReleaseCapture ();
		
	    m_bDragging = FALSE;
		
		// End dragging image
		m_pDragImage->DragLeave (GetDesktopWindow ());
		m_pDragImage->EndDrag ();
		delete m_pDragImage; //must delete it because it was created at the beginning of the drag
		m_pDragImage = NULL;

		int nItemSel=-1;
		for(int i = 0; i <  m_listEnt.GetItemCount(); i++)
		{
			if(m_listEnt.GetItemState(i,LVIS_DROPHILITED))
			{//高亮
				nItemSel = i;
				m_listEnt.SetItemState(i, 0, LVIS_DROPHILITED);
				m_listEnt.RedrawItems(i, i);
			}				
		}	
		MoveAllSelectItemTo(nItemSel);
	} 
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgEntList::MoveAllSelectItemTo(int nItemIndex)
{
	if(E3_GetCmdMgr()==NULL)
	{
		return;
	}

	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}

	PEntity pCurLayer = E3_EntMgrGetCurLayer(pEM);
	if (pCurLayer == NULL)
		return;

	if(nItemIndex>=0)
	{//移动到此单元处
		if(!m_listEnt.GetItemState(nItemIndex,LVIS_SELECTED))
		{//此单元未被选择
			CTypedPtrArray<CPtrArray,CEntity*> arrayPicked;//常规选择对象数组	
			for(int nItem = 0; nItem <  m_listEnt.GetItemCount(); nItem++)
			{
				if(m_listEnt.GetItemState(nItem,LVIS_SELECTED))
				{
					CEntity* pEnt = (CEntity*)m_listEnt.GetItemData(nItem);
					ASSERT(pEnt!=NULL);
					//ASSERT(E3_IsEntPicked(pEnt));						
					arrayPicked.Add(pEnt);
				}
			}

			CEntity* pEntSel = (CEntity*)m_listEnt.GetItemData(nItemIndex);
			
			E3_EntMgrBeginPick(pEM);
			
			E3_EntMgrBeginUndo(pEM,QGlobal::gf_Str(_T("CHANGEORDER"),_T("Change Order")));				
			for(int i=0;i<arrayPicked.GetSize();i++)
			{//把所有对象移动到选择对象后面
				CEntity* pEnt = arrayPicked.GetAt(i);				
				E3_EntMgrUDMoveToBefore(pEM, pEnt, pEntSel);
			}					
			E3_EntMgrEndUndo(pEM);

			E3_EntMgrEndPick(pEM);
		}
	}
}


void CDlgEntList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CDlgEntList::OnKeydownListctrlEnt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	short nCtrl = GetKeyState(VK_CONTROL);
	BOOL bCtrl = nCtrl & 0x8000 ? TRUE : FALSE;

	PCmdMgr pCM = E3_GetCmdMgr();
	if (pCM != NULL)
	{
		if (pLVKeyDow->wVKey == VK_DELETE)
		{

			//gf_GetCmdMgr()->OnKeyDown(VK_DELETE, 1, 0);
			E3_CmdMgrRunCmd(pCM,_T("PICK"), SUBCMD_PICK_DEL, 0);
		}
		else if (bCtrl && pLVKeyDow->wVKey == _T('C'))
		{
			if (E3_CmdMgrIsCmdEnable(pCM, _T("PICK"), SUBCMD_PICK_COPY))
			{
				E3_CmdMgrRunCmd(pCM, _T("PICK"), SUBCMD_PICK_COPY, 0);
			}
		}
		else if (bCtrl && pLVKeyDow->wVKey == _T('V'))
		{
			if (E3_CmdMgrIsCmdEnable(pCM, _T("PICK"), SUBCMD_PICK_PASTE))
			{
				E3_CmdMgrRunCmd(pCM,_T("PICK"), SUBCMD_PICK_PASTE, 0);
			}
		}
		else if (bCtrl && pLVKeyDow->wVKey == _T('X'))
		{
			if (E3_CmdMgrIsCmdEnable(pCM, _T("PICK"), SUBCMD_PICK_CUT))
			{
				E3_CmdMgrRunCmd(pCM,_T("PICK"), SUBCMD_PICK_CUT, 0);
			}
		}
	}
}
