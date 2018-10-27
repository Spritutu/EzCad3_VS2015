#pragma once


// CDlgEntBase 对话框
#include "..\resource.h"
#include "box2d.h" 
 

class GLOABL_EXT_CLASS CDlgEntBase : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgEntBase)

public:
	CDlgEntBase(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgEntBase();
	// 对话框数据
	enum { IDD = IDD_DIALOG_ENTBASE };
	PMarker m_pMarker;
	CFont m_fontCur;
	CPtrArray m_arrayEntDlg;

	BOOL m_bKeepSizeScale;
	double m_dWHScale;
	WORD m_wIoHigh;
	WORD m_wIoLow;
	int m_nPos;

	BOOL   m_bModifyGeneral;
	BOOL   m_bModifyEnt;
	BOOL   m_bEntScaleModify;


	BOOL    m_bFirstY;
	BOOL    m_bBidir;
	int		m_nArrayX;
	int		m_nArrayY;
	double	m_dArrayDistX;
	double	m_dArrayDistY;
	int     m_nCount;

	CString m_strOldPosX;
	CString m_strOldPosY;
	CString m_strOldPosZ;
	CString m_strOldPosA;
	CString m_strOldSizeX;
	CString m_strOldSizeY;

	double m_dOldZ;
	double m_dOldA;
	
	CMFCButton	m_buttonLock;
	CMFCButton	m_buttonPos;
 
	double	m_dPosX;
	double	m_dPosY;
	double	m_dPosZ;
	double	m_dPosA;
	double	m_dSizeX;
	double	m_dSizeY;

	BOOL m_bChangeAllChildEntZToSame;//改变所有对象z值为同一个
	BOOL m_bSetMaxZAsZCoor;//设置最大Z为基准Z

	void UpdateText();
	void UpdateEnt();
	
	void OnChangeEditPosx();
	void OnChangeEditPosy();
	void OnChangeEditPosz();
	void OnChangeEditPosa();
	void OnChangeEditSizex();
	void OnChangeEditSizey();
	void OnChangeEditCount();

	void OnButtonLockscale();
	void OnButtonApply();

	void ShowPos(BOOL bUpdateXY);
	void CalcPos(double& x,double& y,Box2d b);

	virtual void OnOK ();
	virtual void OnCancel ();

	void SetCurFont();

	 
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual LRESULT OnUserChangeEntity(WPARAM wParam, LPARAM lParam);	
	virtual LRESULT OnUserPickChange(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnUserPickLockChange(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnUserUnitChange(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnUserEntModify(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButtonPos();
	afx_msg void OnBnClickedButtonArray();
	afx_msg void OnBnClickedButtonIo();
	afx_msg void OnDestroy();
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
