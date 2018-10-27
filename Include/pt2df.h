/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： Pt2df.h
* 文件标识： 
* 摘要： 2维点类定义
*           
* 版本：3.0
* 作    者：qy
* 完成日期：201年3月
* 版本纪录: 创建文件
*/

#pragma once
 
class GLOABL_EXT_CLASS Pt2df
{
public:
	Pt2df(void);
	Pt2df(const float fx,const float fy){x =fx;y=fy;};
	Pt2df(const Pt2df& ptCen,const float dLen,const float dRadAngle);
public:
	~Pt2df(void);

	public:
     float x;
     float y;
public:
	
	void Set(const float& fx,const float& fy){x =fx;y=fy;};

	BOOL Normalize();
	
	Pt2df operator+=( const Pt2df& pt);
	Pt2df operator-=( const Pt2df& pt);
	Pt2df operator*=( const float& factor );		
	Pt2df operator/=( const float&  dividend);
	
	Pt2df operator+(const Pt2df& pt)const;
	Pt2df operator-(const Pt2df& pt)const;
	float operator^(const Pt2df& pt)const; //叉乘

	Pt2df operator*(float scale)   const;
	Pt2df operator/(float dividend)const;

	Pt2df operator-()const; // 一元减法

	Pt2df  Rotate(const float& ang);//fAng > 0 逆时针旋转 fAng < 0 顺时针旋转
	float Length() const;
	float Distance(const Pt2df& pt) const;//求点到pt距离

	//求点到pt绝对距离
	float FabsDist(const Pt2df& pt) const;

	float GetAngle(const Pt2df& ptCen) const;//求相对点ptCen的角度 //角度为[0，PAI2]区间

	//求点到直线段的投影点,返回距离,参数t和点
	float GetProjectPt(const Pt2df& pt1,const Pt2df& pt2,float& t,Pt2df& pt)  const;

	//求点到直线段的投影点,返回 参数t 
	float GetProjectParam(const Pt2df& pt1,const Pt2df& pt2 )  const;

	//求点到直线段的点最近距离,返回参数t和距离, 0=<t<=1
	float GetDistToLineSeg(const Pt2df& pt1,const Pt2df& pt2,float& t)  const;

	//求点到直线的最近距离平方
	float GetDist2ToLine(const Pt2df& pt1,const Pt2df& pt2)const;
	//friend	 Pt2df  operator*(const float& scale,const Pt2df& pt);

	float GetDistToLine(const Pt2df& p1,const Pt2df& p2)const;
};



 GLOABL_EXT_CLASS Pt2df  operator*(const float& scale,const Pt2df& pt); 
