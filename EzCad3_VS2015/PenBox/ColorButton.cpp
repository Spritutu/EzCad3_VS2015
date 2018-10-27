

#include "stdafx.h"
#include "..\EzCad3_VS2015.h" 
#include "QGlobal.h"
#include "ColorButton.h"
CColorButton::CColorButton()
{
	m_clrBtn = RGB(0,0,0);
}

CColorButton::~CColorButton()
{
}


BEGIN_MESSAGE_MAP(CColorButton, CButton)
	//{{AFX_MSG_MAP(CColorButton)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorButton message handlers


void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{		
	UINT uStyle = DFCS_BUTTONPUSH;	
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
		uStyle |= DFCS_PUSHED;
		
	CRect rect = lpDrawItemStruct->rcItem;

	rect.DeflateRect(1,1,1,1); 

	// Draw the button frame.
	::DrawFrameControl(lpDrawItemStruct->hDC, &rect,DFC_BUTTON, uStyle);
	
	CBrush bsh(m_clrBtn);
	
	rect.DeflateRect(2,2,2,2);
	::FillRect(lpDrawItemStruct->hDC,&rect,bsh);	
}



CShowHideButton::CShowHideButton()
{
	m_bShowOnOff = TRUE;
}

CShowHideButton::~CShowHideButton()
{
}


BEGIN_MESSAGE_MAP(CShowHideButton, CButton)
	//{{AFX_MSG_MAP(CColorButton)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorButton message handlers
void CShowHideButton::SetShow(BOOL b)
{
	m_bShowOnOff = b;
	SetImage(m_bShowOnOff ? IDB_LISTSHOW_ON: IDB_LISTSHOW_OFF);
	Invalidate();
}

