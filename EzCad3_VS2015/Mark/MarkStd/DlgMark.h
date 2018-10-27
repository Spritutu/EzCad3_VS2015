/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CDlgMark.h
* 文件标识：
* 摘要：  
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/

#pragma once

#include "..\..\resource.h"
#include "QPngButton.h"
#include "..\DlgMotionPanel.h"
#include "QLamp.h"
#include "MakeClock.h"

#define KEYHOOK

// CDlgMark 对话框
 
class CDlgMark : public CDialog
{
	DECLARE_DYNAMIC(CDlgMark)

public:
	CDlgMark(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMark();

private:
	PMarker m_pMarker;

	int m_nMutexCount;
	HANDLE m_hMutexMarker; 
public:
	BOOL IsMarkerLocked();
	PMarker GetMarker();
	void LockMarker();
	void UnLockMarker();
public:
	CQPngButton m_buttonF1; 
	CQPngButton m_buttonF2;
	CQPngButton m_buttonF3;
	CQPngButton m_buttonF4;
	CQPngButton m_buttonCamera;
	

	CQLamp m_lampReady;
	CQLamp m_lampPower;
	BOOL m_bRedLightMode;
	BOOL m_bSendF2Msg;

	
	BOOL m_bNowMark;

	BOOL m_bMarkRemovedFlag;
	
	BOOL m_bIsParamSetting;

	CMakeClock m_markTotal;
	 
	CString m_strPartTime;
	
	BOOL IsMarkSelected();

	BOOL m_bHideF3;


	CDlgMotionPanel* m_pDlgMotionPanel;

	int GetMinShowWidth();
	int m_nTotalCount;
	int m_nPartCount;
	int m_nFileCount;
	void ShowCount();
	void GetCurCount();
	void ShowTime();
	void SetPartTimeStr(CString str);

	void OnMark(BOOL bEnableFromLight,BOOL bCalcTime=FALSE);
	//检查是否价格对象是空的
	BOOL CheckIsMarkEntityEmpty();

// 对话框数据
	enum { IDD = IDD_DIALOG_MARK };
	 
	void UpdateDevState();
	void UpdateMotionPanel(BOOL bNoInitial = FALSE);

	void OnPageUp();
	void OnPageDown();

	void OnKeyUp();
	void OnKeyDown();
	void OnKeyLeft();
	void OnKeyRight();

	void OnUpdateMotorCoor();
	void UpdateFlySpeed();
	void UpdateLaserPowerOutportState();
	 
protected:
	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	
	LRESULT  OnUsbLmcArrive(WPARAM wParam, LPARAM lParam)	;
	LRESULT  OnUsbLmcRemove(WPARAM wParam, LPARAM lParam)	;
	LRESULT  OnUserUnitChange(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButtonF1();
	afx_msg void OnBnClickedButtonF2();
	afx_msg void OnBnClickedButtonF22();
	afx_msg void OnBnClickedButtonF3();
	afx_msg void OnBnClickedButtonF4();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonMark3dbox(); 
	afx_msg void OnBnClickedButtonCalcTime();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheckOffline();
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnStnClickedStaticMotorpanel();
	afx_msg void OnBnClickedButtonFlyspeed();
	afx_msg void OnBnClickedButtonPower();
	afx_msg void OnBnClickedButtonCamera();
	virtual LRESULT OnUserChangeEntity(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnUserChangeEntity_1(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnUserRed(WPARAM wParam, LPARAM lParam);
}; 


#ifdef KEYHOOK
CDlgMark* gf_GetDlgMark();
#endif
