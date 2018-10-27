/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： PenParamPropSet.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/

#pragma once
  
class GLOABL_EXT_CLASS CPenParamPropSet
{
public:
	CWnd*    m_pParentWnd;
	PMarker  m_pMarker;
	PMarkPen m_pPenCur;
	int      m_nCurPenIndex;	

	BOOL m_bEnableBasicParam;//使能显示基本参数 

	BOOL m_bDisShowCountParam;
	BOOL m_bDisShowDelayParam;
	BOOL m_bDisShowJumpParam;
	BOOL m_bDisShowSkyWriteParam;
	BOOL m_bDisShowPowerRampParam;
	BOOL m_bDisShowSpeedRampParam;
	BOOL m_bDisShowOptmizeParam;
	BOOL m_bDisShowWobbleParam;
	BOOL m_bDisShowOtherParam;

	

	int  m_nCurLaserType; //当前激光器类型
	BOOL m_bEnableShowSpecialWave;//使能特殊波形显示 
	BOOL m_bEnablePropertyChangeHandle;//使能属性改变消息处理
	
	CMFCPropertyGridCtrl* m_pPenGridCtrl;

	CMFCPropertyGridProperty* m_pGroupPenBasic;
	CMFCPropertyGridProperty* m_pGroupPenMark;
	CMFCPropertyGridProperty* m_pGroupPenLaser;
	CMFCPropertyGridProperty* m_pGroupPenDelay;
	CMFCPropertyGridProperty* m_pGroupPenJump;
	CMFCPropertyGridProperty* m_pGroupPenOptmize;
	CMFCPropertyGridProperty* m_pGroupPenWobble; 
	CMFCPropertyGridProperty* m_pGroupPenOther;
	CMFCPropertyGridProperty* m_pGroupPenPowerRamp;
	CMFCPropertyGridProperty* m_pGroupPenSpeedRamp;
	CMFCPropertyGridProperty* m_pGroupPenSkyWrite;

	int m_nFiberLaserPWCount;
	int m_nFiberLaserPWValue[256];
	CString m_strFiberLaserPWName[256];
public:
	CPenParamPropSet();

	 	//创建笔参数列表
	void CreatePenParamList();
	//创建基础参数列表
	void CreatePenParamListBasic();
	//创建标刻参数列表
	void CreatePenParamListMark();
	//创建激光参数列表
	void CreatePenParamListLaser();
	//创建延时参数列表
	void CreatePenParamListDelay();
	//创建跳转参数列表
	void CreatePenParamListJump();
	//创建优化参数列表
	void CreatePenParamListOptmize();
	//创建抖动参数列表
	void CreatePenParamListWobble();
	//创建其他参数列表
	void CreatePenParamListOther();
	//创建Ramp列表
	void CreatePenParamListPowerRamp();
	void CreatePenParamListSpeedRamp();
	void CreatePenParamListSkyWrite();

	//更新当前笔参数
	void UpdateCurPenParam();

	//更新基础参数列表
	void UpdatePenParamListBasic();
	//更新标刻参数列表
	void UpdatePenParamListMark();
	//更新激光参数列表
	void UpdatePenParamListLaser();
	//更新延时参数列表
	void UpdatePenParamListDelay();
	//更新跳转参数列表
	void UpdatePenParamListJump();
	//更新优化参数列表
	void UpdatePenParamListOptmize();
	void UpdatePenParamListWobble();
	void UpdatePenParamListOther();
	void UpdatePenParamListPowerRamp();
	void UpdatePenParamListSpeedRamp();
	void UpdatePenParamListSkyWrite();
	
	void OnPropertyChanged(CMFCPropertyGridProperty * pProperty); 
	void OnPropertyChangedPenBasic(CMFCPropertyGridProperty * pProperty); 
	void OnPropertyChangedPenMark(CMFCPropertyGridProperty * pProperty);
	void OnPropertyChangedPenLaser(CMFCPropertyGridProperty * pProperty); 
	void OnPropertyChangedPenDelay(CMFCPropertyGridProperty * pProperty);
	void OnPropertyChangedPenJump(CMFCPropertyGridProperty * pProperty);
	void OnPropertyChangedPenOptmize(CMFCPropertyGridProperty * pProperty);
	void OnPropertyChangedPenWobble(CMFCPropertyGridProperty * pProperty);
	void OnPropertyChangedPenOther(CMFCPropertyGridProperty * pProperty);
	void OnPropertyChangedPenPowerRamp(CMFCPropertyGridProperty * pProperty);
	void OnPropertyChangedPenSpeedRamp(CMFCPropertyGridProperty * pProperty);

	void OnPropertyChangedPenSkyWrite(CMFCPropertyGridProperty * pProperty);
	void ReadFiberLaserPWFile();
	int  GetCurPenPWIndex();
};




