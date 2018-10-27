/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： Pt2d.h
* 文件标识： 
* 摘要： 2维点类定义
*           
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/

#pragma once

 

class GLOABL_EXT_CLASS Pt2d
{
public:
	Pt2d(void);
	Pt2d(const double fx,const double fy){x =fx;y=fy;};
	Pt2d(const Pt2d& ptCen,const double dLen,const double dRadAngle);
	
public:
	~Pt2d(void);

	public:
     double x;
     double y;
public:
	
	void Set(const double& fx,const double& fy){x =fx;y=fy;};

	BOOL Normalize();
	
	Pt2d operator+=( const Pt2d& pt);
	Pt2d operator-=( const Pt2d& pt);
	Pt2d operator*=( const double& factor );		
	Pt2d operator/=( const double&  dividend);
	
	Pt2d operator+(const Pt2d& pt)const;
	Pt2d operator-(const Pt2d& pt)const;
	double operator^(const Pt2d& pt)const; //叉乘

	Pt2d operator*(double scale)   const;
	Pt2d operator/(double dividend)const;

	Pt2d operator-()const; // 一元减法

	Pt2d  Rotate(const double& ang);//fAng > 0 逆时针旋转 fAng < 0 顺时针旋转
	double Length() const;
	double Distance(const Pt2d& pt) const;//求点到pt距离
	//求点到pt距离平方
	double Distance2(const Pt2d& pt) const;

	//求点到pt绝对距离
	double FabsDist(const Pt2d& pt) const;

	double GetAngle(const Pt2d& ptCen) const;//求相对点ptCen的角度 //角度为[0，PAI2]区间

	//求点到直线段的投影点,返回距离,参数t和点
	double GetProjectPt(const Pt2d& pt1,const Pt2d& pt2,double& t,Pt2d& pt)  const;

	//求点到直线段的投影点,返回 参数t 
	double GetProjectParam(const Pt2d& pt1,const Pt2d& pt2 )  const;

	//求点到直线段的点最近距离,返回参数t和距离, 0=<t<=1
	double GetDistToLineSeg(const Pt2d& pt1,const Pt2d& pt2,double& t)  const;

	//求点到直线的最近距离平方
	double GetDist2ToLine(const Pt2d& pt1,const Pt2d& pt2)const;
	//friend	 Pt2d  operator*(const double& scale,const Pt2d& pt);
};



 GLOABL_EXT_CLASS Pt2d  operator*(const double& scale,const Pt2d& pt); 
