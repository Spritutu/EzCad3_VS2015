/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： QMotorMgr.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2016年3月
* 版本纪录: 创建文件
*/

#pragma once
#include "Qmotor.h"

//#define MAX_MOTOR_COUNT 4
#define MAX_MOTOR_COUNT 6

#define MAX_AXISSOLUTION_NUM 17
#define MOTOR_SOL_NONE 0
#define MOTOR_SOL_X    1
#define MOTOR_SOL_Y    2
#define MOTOR_SOL_Z    3
#define MOTOR_SOL_A    4
#define MOTOR_SOL_XY   5
#define MOTOR_SOL_XZ   6
#define MOTOR_SOL_YZ   7
#define MOTOR_SOL_XA   8
#define MOTOR_SOL_YA   9
#define MOTOR_SOL_ZA   10
#define MOTOR_SOL_XYZ  11
#define MOTOR_SOL_XZA  12
#define MOTOR_SOL_YZA  13
#define MOTOR_SOL_XYZA 14
#define MOTOR_SOL_XY_SPHERE 15
#define MOTOR_SOL_XYZA_FREE 16  //自由移动模式


#define MOTOR_X 0
#define MOTOR_Y 1
#define MOTOR_Z 2
#define MOTOR_A 3

#define MOTOR_A_AS_A  0
#define MOTOR_A_AS_Y  1
#define MOTOR_A_AS_X  2

typedef  int (*QM_EM_InitMotion)(int nFlag);
typedef  int(*QM_EM_CloseMotion)();
typedef  int(*QM_EM_SetAxisWorkMode)(int idAxis, int nMode);
typedef  int(*QM_EM_SetAxisOutMode)(int idAxis, int Mode_A, int Mode_B, int Mode_C);
typedef  int(*QM_EM_SetAxisServeOn)(int idAxis, BOOL bOn);
typedef  int(*QM_EM_SetAxisPosErrFollow)(int idAxis, int pel);
//设置反向间隙
typedef  int(*QM_EM_SetAxisBacklash)(int idAxis, int nPulse, int nTimeMs);
typedef  int(*QM_EM_SetAxisIO)(int idAxis, int PHN_flag, int Mode, int H_L_Act, int nPortIndex);
typedef  int(*QM_EM_GetAxisState)(int idAxis, int& state, int& fault);
typedef  int(*QM_EM_ResetAxisPos)(int idAxis, int offset);
typedef  int(*QM_EM_GetAxisPos)(int idAxis, int& pos);
typedef  int(*QM_EM_StopAxis)(int idAxis);
typedef  int(*QM_EM_SetAxisAccDec)(int idAxis, int minvel, int maxvel, int acc, int dec, int jerk);
typedef  int(*QM_EM_SetAxisVel)(int idAxis, int vel);
typedef  int(*QM_EM_AxisMoveTo)(int idAxis, int pos);
typedef int(*QM_EM_AxisGoHome)(int idAxis, int goHomeVel, int LeaveHomeVel, int LeaveHomePos, int LookZIndexVel, int PulseNum, int Z_IndexFlag);

 
typedef int(*QM_EM_InitHandwheel)(); 

/*SPEC: 设置指定轴为手轮的从轴(int 轴号，short 传动比系数(主轴位移pulse), short 传动比系数(从轴位移pulse), double 从轴最大速度pulse/s)。*/
/*INFO：在固高中，同时将轴0-轴3的跟随跟随加速度和减速度设置为其当前的加速度和减速度。
在9030中，手轮控制的从轴无法设定加速度和减速度。*/
/*INFO: vel参数只再固高中使用，9030无法设定轴的跟随最大速度，轴的跟随速度由转动手轮的速度和跟随PID调节系数Kp决定(0.001<Kp<1000)*/
/*INFO: 固高对手轮编码器进行4倍频，也即手轮正向转一格编码器读数增加4。
例如：要实现手轮转一格从轴移动100个脉冲，则应按照(idAxis, 1, 100/4, 0) 传入系数。
按照(idAxis, 4, 100, 0)传入系数也可以，但是因为固高startHandwheel的两个传动比系数均为short类型(范围[0-32767])
因此将传动比系数1设为最小，可实现最大的传动比上限，也即32767/1
虽然9030可接受double类型的传动比，但是因为受制于固高，该EM函数按照固高的参数类型定义*/
typedef int(*QM_EM_StartHandwheel)(int idAxis, short masterEven, short slaveEven, double vel);

//SPEC: 读取手轮IO，获取所选轴及倍率档位。
typedef int(*QM_EM_ReadHandwheelIO)(int& idAxis, int& gearLevel);

//SPEC: 停止从轴的电子齿轮跟随模式。
typedef int(*QM_EM_EndHandwheel)(short idAxis);


#define QM_ERR_SUCCESS      0
#define QM_ERR_FAIL         1
#define QM_ERR_OPENFAIL     2 
#define QM_ERR_NOFUNCTION   3 
#define QM_ERR_AXISID       4

class GLOABL_EXT_CLASS QMotorMgr
{
public:
	PMarker m_pMarker;
	int m_nUnitType;
	int m_nErrCode;
	QMotor m_motorAll[MAX_MOTOR_COUNT];

	int m_nLastSpd[MAX_MOTOR_COUNT];

	double m_dStepDist; 
	double m_dFocusPos; 

	BOOL m_bTableMoveX;//X轴是平台移动
	BOOL m_bTableMoveY;//Y轴是平台移动

	int m_nAasMode;//0是正常旋转，1是Y轴，2是X轴
	double m_dOriginX;
	double m_dOriginY;
	double m_dOriginZ;
	double m_dOriginA;

	int m_nAxisMoveDelayMs;	
	BOOL m_bEnableHandwheel;

	BOOL m_bMotorUseInterSoftInvert;//电机是否使用内部软反转
public:
	BOOL m_bSolAMark360;
	int  m_nSolAMarkCount;
	double  m_dSolAMarkAngle;

public:
	QMotorMgr();
	~QMotorMgr();

	virtual void CopyAllParam(QMotorMgr* pMgr);
	virtual void Close();

	virtual BOOL LoadParam(CString strFile);
	virtual BOOL SaveParam(CString strFile);

	virtual BOOL Initial(PMarker pMarker,int nSolu);
	BOOL UpdateAxisParam(int axis);

	virtual BOOL ResetAxisPos(int idAxis, double dOffset);
	virtual int GetPulsePos(int nAxisId) ;

	virtual BOOL IsFault(int nAxisId,DWORD& dwErrorCode);
	virtual BOOL IsMoving(int nAxisId);

	QMotor* GetMotor(int nAxis) { return &m_motorAll[nAxis]; }

	//校正
	virtual double CmdPosToRefPos(int nAxisId, double dCmdPos);
	virtual double RefPosToCmdPos(int nAxisId, double dRefPos);

	virtual int MoveTo(int nAxisId, int pos, int spd);
	virtual int Home( int nAxisId, int spdHome,int spdLeave, int LeaveHomePos, int LookZIndexVel, int PulseNum, int Z_IndexFlag);

	virtual void StopAxis(int nAxisId);


	virtual int HomeAllAxis(PMarker pMarker);
	virtual int GotoPos(PMarker pMarker, double x,double y,double z,double a,BOOL& isHasMoved, double dSpdRatio);

	virtual int GotoPos(PMarker pMarker, double x, double y, double z,double dSpdRatio );

	virtual BOOL InitialHandwheel( );
	virtual BOOL EndHandwheel(int nAxisId);
	virtual BOOL GetHandwheelIO(int& idAxis, int& gearLevel);

	virtual int SetHandwheelSlaveAxis(int nAxisId,double dGearRatio);

	virtual void ShowHandwheelDialog();

	virtual void OnChangeUnitType(int nUnitType);

	virtual BOOL GetAxisStatus(int axis, WORD& wStatus) { return FALSE; };
};


GLOABL_EXT_CLASS QMotorMgr* gf_GetMotorMgr();
void gf_SetMotorMgr(QMotorMgr* pMM);

GLOABL_EXT_CLASS CString gf_GetMotorErrStr(int nErr);
GLOABL_EXT_CLASS int gf_MotorErrToMERR(int nMotorErr);

GLOABL_EXT_CLASS CString gf_GetMotorSolName(int nSol);

GLOABL_EXT_CLASS int gf_RemoveSolAxisA(int nSol);