/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： Box3d.h
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
#include "pt3d.h"
#include "Box2d.h"
#include "Matrix3d.h"

class GLOABL_EXT_CLASS Box3d
{
public:
	Box3d(void);
public:
	~Box3d(void);

public:
	Pt3d a;
    Pt3d b;
public:
   
    Box3d(const double& ax,const double& ay,const double& az,const double& bx,const double& by,const double& bz );
    Box3d(const Pt3d& p1, const Pt3d& p2 );
    Box3d(const Box3d& r);
	Box3d(const Box2d& r, const double& z);
	Box2d GetBox2d();
	void SetBox(double ax,double ay,double az,double bx,double by,double bz );
	void SetBox(Pt3d p1, Pt3d p2 );
	void SetBox(const Box3d& r);
	void AddPoint(const Pt3d& pt);
	void AddPoint(const double& x,const double& y ,const double& z);

	void  GetCornerPt(Pt3d pt[8])const;

	Pt3d  GetCenterPt()const;
	double Width()const;
	double Height()const;
	double HeightZ()const;

	void EmptyBox();        
    void Intersect( const Box3d &r ); 
    void Union( const Box3d &r );     
    void Adjust();
	void Move(const double& x,const double& y,const double& z);
    
    BOOL IsContains( const Pt3d &p ,const double& err) const; 	
	BOOL IsContains( const double &x , const double &y,const double &z,const double& err) const;
	
	BOOL IsContains(const double &x, const double &y, const CMatrix3d& mtxProject, const double& err) const;

    BOOL IsEmpty() const;    
    BOOL IsIntersect( const Box3d &r ,const double& err) const ;
	BOOL IsInclude( const Box3d &r ) const;
         
	Box3d  	operator +  ( const Box3d &r );
    void	operator += ( const Box3d &r );
    void	operator =  ( const Box3d &r );
    BOOL	operator == ( const Box3d &r );

	//得到3d包围盒的2d投影包围盒
	Box2d  Box3d::GetProjectBox2d(const CMatrix3d& mtxProject) const;
	void GetCorners(Pt3d ptCorners[8]) const;
};
