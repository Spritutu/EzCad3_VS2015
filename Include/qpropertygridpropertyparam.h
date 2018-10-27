/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CQPropertyGridParamProperty.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2016年3月
* 版本纪录: 创建文件
*/
#pragma once
 

 class CPenToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};
  
 class CQPropertyGridBigButtonProperty : public CMFCPropertyGridProperty
{
 
	DECLARE_DYNAMIC(CQPropertyGridBigButtonProperty)

// Construction
public:

	CQPropertyGridBigButtonProperty(const CString& strName, const CString& strFolderName, LPCTSTR lpszDescr = NULL);
	virtual ~CQPropertyGridBigButtonProperty();

	virtual void AdjustButtonRect();
// Overrides
public:
	virtual void OnDrawValue(CDC* pDC, CRect rect);
	virtual void OnClickButton(CPoint point);
	virtual void OnDrawButton(CDC* pDC, CRect rectButton);
	PMarkParam m_pMarkParam;
// Attributes
protected:
	
};

 class CQPropertyGridParamProperty : public CMFCPropertyGridProperty
{
	DECLARE_DYNAMIC(CQPropertyGridParamProperty)

// Construction
public:

	CQPropertyGridParamProperty(const CString& strName, const CString& strFolderName, LPCTSTR lpszDescr = NULL);
	virtual ~CQPropertyGridParamProperty();

// Overrides
public:
		virtual void AdjustInPlaceEditRect(CRect& rectEdit, CRect& rectSpin);
  	virtual void OnDrawValue(CDC* pDC, CRect rect);
	virtual void OnClickButton(CPoint point);

	int m_nParamType;//=0 笔号  =1 焊接波形 =2 圆弧

	BOOL m_bAdvanceParam;
	BOOL m_bWeldWave;

	PMarkParam m_pMarkParam;
	int m_nCurLaserType;
// Attributes
protected:
	
};

 