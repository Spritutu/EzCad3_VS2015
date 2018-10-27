/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CDialogPenbox.h
* 文件标识：
* 摘要：  
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/
#pragma once

#include "..\resource.h"
// CDialogPenbox 对话框

 
#include "PenParamPropSet.h" 
#include "QPropertyGridProperty.h"
#include "ColorButton.h"
#include "QDIB.h"

class CDialogPenbox : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogPenbox)

public:
	CDialogPenbox(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogPenbox();

	// 对话框数据
	enum { IDD = IDD_DIALOG_PENBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnPropertyChanged( WPARAM wparam, LPARAM lparam ); 
	afx_msg LRESULT OnUserInitEntList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserPickChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserLaserChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserUnitChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserLaserParamChanged(WPARAM wParam, LPARAM lParam);

	afx_msg void OnCustomdrawPen(NMHDR*, LRESULT*);
	afx_msg void OnClickListPen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListPen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListPen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedPen0();
	afx_msg void OnBnClickedPen1();
	afx_msg void OnBnClickedPen2();
	afx_msg void OnBnClickedPen3();
	afx_msg void OnBnClickedPen4();
	afx_msg void OnBnClickedPen5();
	afx_msg void OnBnClickedPen6();
	afx_msg void OnBnClickedPen7();
	afx_msg void OnPenApplytopick();
	afx_msg void OnUpdatePenApplytopick(CCmdUI* pCmdUI); 
	afx_msg void OnLoadDefaultPens();
	afx_msg void OnPenSetDefaultPens();
	afx_msg void OnPenResetAllPens();

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();

	virtual void OnOK();
	virtual void OnCancel();
public:
	virtual BOOL OnInitDialog();
public:
	
	CListCtrl m_listPen;
	CShowHideButton m_btnShowOnOff;
	CColorButton m_btnPen0;
	CColorButton m_btnPen1;
	CColorButton m_btnPen2;
	CColorButton m_btnPen3;
	CColorButton m_btnPen4;
	CColorButton m_btnPen5;
	CColorButton m_btnPen6;
	CColorButton m_btnPen7;
	BOOL m_bShowPenList;
	CBitmap		bmpMarkOn;
	CBitmap		bmpMarkOff;
	CFont m_fontProp;
	CQPropertyGridCtrl m_penParam;
	PMarker m_pMarker;

	PMarkPen m_penCur;
	BOOL m_bEnablePropertyChangeHandle;//使能属性改变消息处理

	int m_nCurPenIndex;
	
	CPenParamPropSet m_penProp; 

	void AutoLayout();

	void ShowCurPenParam(int nPen);
	void UpdateCurPenParam();
	void UpdateCurPenParamToPenBox();
	void UpdateAllBtnColor();
	void UpdatePenList();
	void SetPropListFont();
	void SaveLastListWidth();
	BOOL GetLastListWidth(int& bItem0,int& bItem1,int& bItem2,int& bItem3,int& bItemProp);

	//更新当前笔列表的选择状态且检查名字是否正确
	void UpdatePenListSelectStateAndCheckName() ;

	//应用当前笔号到选择对象
	void AppltPenToSelEnt(int nPen);
	//把当前笔参数复制到笔盒中
	void SetCurPenParamToPenbox();

	void InitPenboxList();
	//初始化属性参数表
	void InitPropList(); 
	afx_msg void OnBnClickedButtonAdvance();
	afx_msg void OnBnClickedButtonParamlib();
	
	afx_msg void OnBnClickedButtonListonoff();
};
