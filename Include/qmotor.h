/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： QMotor.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2016年3月
* 版本纪录: 创建文件
*/

#pragma once

#define MOTOR_ERR_SUCCESS 0
#define MOTOR_ERR_FAULT   1  //故障
#define MOTOR_ERR_NOTHOME 2  //没有回零
#define MOTOR_ERR_MINLIMIT 3   
#define MOTOR_ERR_MAXLIMIT 4  

#define MOTOR_ERR_USERSTOP 10  

#define MOTOR_MIN_MOVEDIST 0.0001  


#define MOTOR_FAULT_LIMIT_NEG1  0x0001
#define MOTOR_FAULT_LIMIT_POS1  0x0002
#define MOTOR_FAULT_LIMIT_NEG2  0x0010
#define MOTOR_FAULT_LIMIT_POS2  0x0020
#define MOTOR_FAULT_LIMIT_NEG3  0x0100
#define MOTOR_FAULT_LIMIT_POS3  0x0200
#define MOTOR_FAULT_LIMIT_NEG4  0x1000
#define MOTOR_FAULT_LIMIT_POS4  0x2000


#include "QIniFile.h"
#include "DlgProgress.h"

class QMotorMgr;
class GLOABL_EXT_CLASS QMotor
{
public:
	QMotorMgr* m_pQM;
	BOOL m_bEnable;
	BOOL m_bInvert; 	
	BOOL m_bOutNeg;//1=共阴极输出
	int m_nAxisId;
	BOOL   m_bRotaryAxis;
	double m_dDistPerRound;//转一圈的距离
	double m_dPulsePerRound;//电机一转脉冲数
	double m_dMinVel;//最小速度
	double m_dMaxVel;//最大速度 
	double m_dAcceleration;
	double m_dDeceleration;

	double m_dBacklash;//反向间隙

	BOOL m_bEnFeedback;
	double m_dPosErrFollow;
	  
	double m_dCmdPos;//命令位置 
	double m_dRefPos;//参考位置=校正后的命令位置 
   
	BOOL   m_bSAcc;
	double m_dJerk;
	
	BOOL m_bEnableSoftLimit;
	double m_dMinSoftLimit;
	double m_dMaxSoftLimit;

	BOOL   m_bEnableHome;
	BOOL   m_bAlreadyHome;
	BOOL   m_bHomeLowValid;
	BOOL   m_bHomeDirPos;//正向回零
	BOOL m_bHomeFindIndex;
	double m_dHomePos;//零点的坐标
	double m_dHomingFindVel;//找零点速度
	double m_dHomingLeaveVel;//离开零点速度
	BOOL m_bHomeFinishGotoPos;
	double m_dHomeFinishGotoPos;

	BOOL m_bEnableLimit;
	BOOL m_bLimitLowValid;

	BOOL m_bMarkFinishGotoStartPoint;



	double m_dVelocityDir;//当前移动方向

	QMotor();

	virtual void CopyAllParam(QMotor* pMotor);

	double GetCmdPos() { return m_dCmdPos; }

	virtual double GetFbPos();
 
	//回零后调用复位坐标 
	virtual void Reset();

	int PosToPulse(double pos);
	double PulseToPos(int pulse);

	virtual BOOL IsFault(DWORD& dwErrorCode);
	virtual BOOL IsMoving();

	virtual double CmdPosToRefPos(double dCmdPos);
	virtual void RefreshPos();
	virtual int GoPos(PMarker pMarker,double dPos, double dSpeed, BOOL bWaitFinish=TRUE);
	virtual int GoPos(PMarker pMarker,double dPos, BOOL bWaitFinish, double dSpdRatio);
	virtual int Home(PMarker pMarker, BOOL bWaitFinish = TRUE);

	virtual int WaitForMoveFinish(PMarker pMarker, ProgressParam* pProgressParam);


	virtual void ShowParamAxis(CMFCPropertyGridProperty* pGroup, CString strUnit);
	virtual void GetParamAxis(CMFCPropertyGridProperty* pGroup );

	//反向间隙补偿
	virtual double CompBacklash(double dPos);
	 
	void Load(CQIniFile& qini, CString strName);
	void Save(CQIniFile& qini, CString strName);
	QMotor* GetCopy();

	BOOL IsSameParam(QMotor* pMotor);
};