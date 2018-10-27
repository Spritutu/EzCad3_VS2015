/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： Box2d.h
* 文件标识： 
* 摘要： 2维包围盒类定义
*           
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/


#pragma once

 

#include "pt2d.h"
class Box3df;
class GLOABL_EXT_CLASS Box2d
{
public:
	Box2d(void);
public:
	~Box2d(void);

public:
	Pt2d a;
    Pt2d b;
public:
   
    Box2d(const double& ax,const double& ay,const double& bx,const double& by );
    Box2d(const Pt2d& p1, const Pt2d& p2 );
    Box2d(const Box2d& r);
    Box2d(const Box3df& r);
	 
	void SetBox(double ax,double ay,double bx,double by );
	void SetBox(Pt2d p1, Pt2d p2 );
	void SetBox(const Box2d& r);
	void SetBox(const Box3df& r);

	void AddPoint(const Pt2d& pt);
	void AddPoint(const double& x,const double& y);

	void  GetCornerPt(Pt2d pt[4])const;

	Pt2d  GetCenterPt()const;
	double Width()const;
	double Height()const;

	void EmptyBox();        
    void Intersect( const Box2d &r ); 
    void Union( const Box2d &r );     
	void Union( const Box3df &r );     
    void Adjust();
	void Move(const double& x,const double& y);
    
    BOOL IsContains( const Pt2d &p ,const double& err) const; 	
	BOOL IsContains( const double &x , const double &y,const double& err) const;
	
    BOOL IsEmpty() const;    
    BOOL IsIntersect( const Box2d &r ,const double& err) const ;
	BOOL IsIntersect( const Box3df &r ,const double& err) const ;
	
	BOOL IsIntersect(const double& sx,const double& sy,const double& ex,const double& ey,const double& err) const;
    BOOL IsInclude( const Box2d &r ) const;
	BOOL IsInclude(const Box2d &r,const double& err) const;

	
	Box2d  	operator +  ( const Box2d &r );
    void	operator += ( const Box2d &r );
    void	operator =  ( const Box2d &r );
    BOOL	operator == ( const Box2d &r );

	void	operator += ( const Box3df &r );

	//nSplitFlag == 0 XY方向分割
	//nSplitFlag=1 只要水平方向的包围盒 
	//nSplitFlag=2 只要垂直方向的包围盒 
	Box2d* GetSplitBox(double dSplitSize, int nSplitFlag, double dErrLen, int& nBoxCount);
};

typedef Box2d* PBox2d;