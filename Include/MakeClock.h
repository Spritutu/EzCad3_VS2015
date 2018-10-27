/*
* Copyright (c) 2003, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： MakeClock.h
* 摘要：	 时钟

*/

#ifndef _MAKECLOCK_H
#define _MAKECLOCK_H
  
class GLOABL_EXT_CLASS CMakeClock
{
protected:	
	BOOL m_bUseCmosTime;

	BOOL IsStart; 
	long m_lStartTime;//开始时间
	long m_lTotalTime;//总时间	

	SYSTEMTIME stStart;
public:
	CMakeClock(BOOL bUseCmosTime = FALSE);	
	double m_dRatio;
	
	void Reset();
	void GetUseTime(int& h,int& m,int& s,int& ms);
	void GetUseTime(int& h,int& m,int& s);	
	long GetTotalTime();
	void Start();
	void Pause();
	void Continue();
	BOOL IsStarted(){return IsStart;};

	CString GetShowTimeStr();

	static CString GetShowTimeStr(int nTime);
};

#endif