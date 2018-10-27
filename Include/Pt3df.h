/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： Pt3df.h
* 文件标识：
* 摘要： 
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/

//Pt3df的Float版本，防止3d数据量太大
#pragma once

#include <math.h>
 
class GLOABL_EXT_CLASS Pt3df
{
public:
     float x;
     float y;
	 float z;
public:
	Pt3df();	
	Pt3df(const double fx,const double fy,const double fz){x = (float)fx;y= (float)fy;z= (float)fz;};
	void Set(const double& fx,const double& fy,const double& fz){x = (float)fx;y= (float)fy;z= (float)fz;};

	Pt3df(const float fx,const float fy,const float fz){x =fx;y=fy;z=fz;};
	void Set(const float& fx,const float& fy,const float& fz){x =fx;y=fy;z=fz;};

	BOOL Normalize();
	
	Pt3df operator+=( const Pt3df& pt);
	Pt3df operator-=( const Pt3df& pt);
	Pt3df operator*=( const float& factor );		
	Pt3df operator/=( const float&  dividend);
	
	Pt3df operator+(const Pt3df& pt)const;
	Pt3df operator-(const Pt3df& pt)const;
	double operator*(const Pt3df& pt)const; //点乘
	Pt3df operator^(const Pt3df& pt)const; //叉乘

	Pt3df operator*(float scale)   const;
	Pt3df operator/(float dividend)const;

	Pt3df operator-()const; // 一元减法

 	float Length() const;
	//求点到pt距离
	float Distance(const Pt3df& pt) const;
		
	//求点到pt绝对距离
	float FabsDist(const Pt3df& pt) const;
	 
	Pt3df	CrossProduct(const Pt3df& v) const;

	float  DistToLine(const Pt3df& p0, const Pt3df& p1);

	friend	GLOABL_EXT_CLASS Pt3df  operator*(const float& scale,const Pt3df& pt); 

};
 


inline Pt3df  operator*(const float& scale,const Pt3df& pt)
{
	return Pt3df(scale * pt.x , scale * pt.y, scale * pt.z);
}
 