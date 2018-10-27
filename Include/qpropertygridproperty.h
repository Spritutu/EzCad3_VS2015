/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CQPropertyGridMapProperty.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2016年3月
* 版本纪录: 创建文件
*/
#pragma once


 

 
  
class GLOABL_EXT_CLASS CQPropertyGridIOMask : public CMFCPropertyGridProperty
{
	DECLARE_DYNAMIC(CQPropertyGridIOMask)

	// Construction
public:

	CQPropertyGridIOMask(const CString& strName, WORD wMask, LPCTSTR lpszDescr = NULL);
	virtual ~CQPropertyGridIOMask();

	// Overrides
public:
	WORD m_wMask;
	BOOL m_bShowCurState;
	WORD m_wState;
	CString m_strName;
	CString m_strPrefix;
	virtual void OnClickButton(CPoint point);

	virtual CString FormatProperty();

	// Attributes
protected:

};


class GLOABL_EXT_CLASS CQPropertyGridMapProperty : public CMFCPropertyGridProperty
{
	DECLARE_DYNAMIC(CQPropertyGridMapProperty)

// Construction
public:

	CQPropertyGridMapProperty(const CString& strName, const CString& strFolderName, LPCTSTR lpszDescr = NULL);
	virtual ~CQPropertyGridMapProperty();

// Overrides
public:
	CString m_strTitle;
	BOOL m_bCurrent;
	double dPowerMap[11];
	double dCurrentMap[11][2];

	virtual void OnClickButton(CPoint point);
	
	virtual CString FormatProperty();
	
// Attributes
protected:
	
};

class GLOABL_EXT_CLASS CQPropertyGridCtrl: public CMFCPropertyGridCtrl
{
public:
	void SetColumnWidth(INT value){m_nLeftColumnWidth=value;};
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual void OnSpinDeltaPos(NMHDR* /*pNMHDR*/, LRESULT* pResult); 

    void OnSize(UINT nType, int cx, int cy);

 	virtual void OnDraw(CDC* pDC);
  
	DECLARE_MESSAGE_MAP()

}; 

class GLOABL_EXT_CLASS CQPropertyGridProperty : public CMFCPropertyGridProperty
{
	DECLARE_DYNAMIC(CQPropertyGridProperty)
public:
		friend class CQPropertyGridProperty;

	CQPropertyGridProperty(CString strName, CString strDesc,CString strValue); 
	CQPropertyGridProperty(CString strName );

	
	CSpinButtonCtrl* CreateSpinControl2(CRect rectSpin);

	virtual BOOL OnEdit(LPPOINT lptClick);
	virtual BOOL IsValueChanged() const;
	virtual CString FormatProperty();
	virtual BOOL OnEditKillFocus() ;
	virtual BOOL TextToVar(const CString& strText);

	void SetValue(double value);

	void SetValue(double value,double dMin,double dMax,double dInc,int nDigial);

	double m_dValue;
	double m_dMinRange;
	double m_dMaxRange;
	double m_dInc;
	int m_nDigial;

};


class GLOABL_EXT_CLASS CQPropertyGridPortProperty : public CMFCPropertyGridProperty
{
	DECLARE_DYNAMIC(CQPropertyGridPortProperty)
public:
		friend class CQPropertyGridProperty;
private:
	WORD m_wMask;
		 
public:

	void SetMask(WORD wMask);

	CQPropertyGridPortProperty(CString strName, CString strDesc,int nPort,WORD wMask);
	~CQPropertyGridPortProperty(); 

	void SetPort(int nPort);

	int GetCurPort();

};


class GLOABL_EXT_CLASS CQPropertyGridPortStateProperty : public CMFCPropertyGridProperty
{
	DECLARE_DYNAMIC(CQPropertyGridPortStateProperty)
public:
		friend class CQPropertyGridProperty;
private:
 
public:
	CQPropertyGridPortStateProperty(CString strName, CString strDesc,int nPort);
	~CQPropertyGridPortStateProperty(); 

	void SetState(int nPort);

	int GetState();

};