#pragma once
 
// CDlgEntList 对话框
#include "..\resource.h"

const int IMAGEID_CURVE   = 0;
const int IMAGEID_POINT   = 1;
const int IMAGEID_RECT    = 2;
const int IMAGEID_CIRCLE  = 3;
const int IMAGEID_ELLPISE = 4;
const int IMAGEID_POLYGON = 5;
const int IMAGEID_COMBINE = 6;
const int IMAGEID_HATCHGROUP = 7;
const int IMAGEID_BITMAP     = 8;
const int IMAGEID_VECTORFILE = 9;
const int IMAGEID_TEXT   = 10;
const int IMAGEID_PATHTEXT   = 11;
const int IMAGEID_GROUP   = 12;
const int IMAGEID_TIMER  = 13;
const int IMAGEID_INPUT   =14;
const int IMAGEID_OUTPUT   =15;
const int IMAGEID_CIRCLETEXT   = 16;
const int IMAGEID_EXTAXIS = 17;
const int IMAGEID_FLYDIST = 18;
const int IMAGEID_SPIRAL = 19;
const int IMAGEID_MESH3D =20; 
const int IMAGEID_SLICE3D =21; 
const int IMAGEID_CURVE3D =22; 
const int IMAGEID_PROJECT3D =23; 
const int IMAGEID_INDEX = 24;
const int IMAGEID_CCD = 25;
const int IMAGEID_INPUTJUMP = 26;
const int IMAGEID_UNKNOW= 27; 


class CDlgEntList : public CDialog
{
	DECLARE_DYNAMIC(CDlgEntList)

public:
	CDlgEntList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgEntList();
	// 对话框数据
	enum { IDD = IDD_DIALOG_ENTLIST };
	 
	CListCtrl	m_listEnt;
	CImageList  m_listImage;	
	CBitmap		bmpShowOn;
	CBitmap		bmpShowOff;

	CBitmap		bmpEntType[IMAGEID_UNKNOW+1];
 
	BOOL m_bDragging;
	int         m_nDragIndex;
	int         m_nDropIndex;
	CImageList* m_pDragImage;

	CFont m_fontCur;
	void SetCurFont();
	void InitialList();
	void OnUserPickChange();
	void UpdateCurEntList();
	//用户从列表控件选择对象
	void OnUserSelectEntFromList();

	void ChangeOrder(int subCmd, int param=0);
	void OnShow(BOOL bAll) ;
	void MoveAllSelectItemTo(int nItemIndex);

	BOOL GetLastListWidth(int& bItem0,int& bItem1,int& bItem2, int& bItem3);
	void SaveLastListWidth( );
	void AutoAdjustListWidth();
protected:

	virtual void OnOK();
	virtual void OnCancel();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持 
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point); 
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBegindragList(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCustomdrawList(NMHDR*, LRESULT*);
	afx_msg void OnClickListEnt(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListEnt(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListEnt(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	virtual LRESULT OnUserChangeEntity(WPARAM wParam, LPARAM lParam);	
	virtual LRESULT OnUserPickChange(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnUserPickLockChange(WPARAM wParam, LPARAM lParam);	 

	afx_msg void OnOrderPrev(); 
	afx_msg void OnOrderNext(); 
	afx_msg void OnOrderTop(); 
	afx_msg void OnOrderBottom();
	afx_msg void OnOrderIndex();
	afx_msg void OnOrderShow(); 
	afx_msg void OnOrderShowAll(); 
	afx_msg void OnOrderHide();
public:
	virtual BOOL OnInitDialog(); 

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeydownListctrlEnt(NMHDR *pNMHDR, LRESULT *pResult);
};
