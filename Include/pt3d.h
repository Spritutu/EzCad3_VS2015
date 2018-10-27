/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： Pt3d.h
* 文件标识： 
* 摘要：     3维点类定义
*           
* 版本：2.0
* 作    者：qy
* 完成日期：2005年5月21日
* 版本纪录: 创建文件
*/
#ifndef POINT3D_H
#define POINT3D_H

#include <math.h>
 
class GLOABL_EXT_CLASS Pt3d
{
public:
     double x;
     double y;
	 double z;
public:
	Pt3d();	
	Pt3d(const double fx,const double fy,const double fz){x =fx;y=fy;z=fz;};
	void Set(const double& fx,const double& fy,const double& fz){x =fx;y=fy;z=fz;};

	BOOL Normalize();
	
	Pt3d operator+=( const Pt3d& pt);
	Pt3d operator-=( const Pt3d& pt);
	Pt3d operator*=( const double& factor );		
	Pt3d operator/=( const double&  dividend);
	
	Pt3d operator+(const Pt3d& pt)const;
	Pt3d operator-(const Pt3d& pt)const;
	double operator*(const Pt3d& pt)const; //点乘
	Pt3d operator^(const Pt3d& pt)const; //叉乘

	Pt3d operator*(double scale)   const;
	Pt3d operator/(double dividend)const;

	Pt3d operator-()const; // 一元减法

 	double Length() const;
	//求点到pt距离
	double Distance(const Pt3d& pt) const;
	double Distance2(const Pt3d& pt) const;
	
	//求点到pt绝对距离
	double FabsDist(const Pt3d& pt) const;

	friend	GLOABL_EXT_CLASS Pt3d  operator*(const double& scale,const Pt3d& pt); 

};
 


inline Pt3d  operator*(const double& scale,const Pt3d& pt)
{
	return Pt3d(scale * pt.x , scale * pt.y, scale * pt.z);
}


#endif