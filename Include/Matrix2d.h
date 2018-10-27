/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CMatrix2d.h
* 文件标识： 
* 摘要： 2维变换矩阵类定义
*           
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/

#pragma once



//  
//   [a  d  g]
//   [b  e  h]  
//   [c  f  i]  
//  
//   [a d] 
//   [b e] 是缩放，旋转，对称，错切变换 
//

//   [c f] 是平移变换 

//   [g]
//   [h]   是投影变换 

//变换类型
const int TRANSFORM_NO    = 0;            //无
const int TRANSFORM_MOVE  = 0x0001;            //移动
const int TRANSFORM_SCALE = 0x0002;            //放缩
const int TRANSFORM_MIRROR= 0x0004;            //镜像
const int TRANSFORM_ROTATE= 0x0008;            //旋转
const int TRANSFORM_SHEAR = 0x0010;            //错切
const int TRANSFORM_MIX   = 0x00FF;            //混合
class Pt2d;
class Pt3d;
class Box2d;

 
class GLOABL_EXT_CLASS CMatrix2d 
{
public:
    double x[3][3];
public:
	CMatrix2d(double* pBuf);
    CMatrix2d(){Identity();};
	~CMatrix2d();

	void Set(double* pBuf);
	void Get(double  mtx[9]);
	void Identity();//构造单位矩阵
	
	// |M| *= |A| 矩阵相乘
	CMatrix2d& operator*= (const CMatrix2d& A);		

	//矩阵求逆	
	CMatrix2d GetInverse() const;

	//构造平移矩阵	
    CMatrix2d Move(const double& fx,const double& fy);
	
	//构造比例缩放矩阵 相对原点放缩
	CMatrix2d Scale(const double& fScaleX,const double& fScaleY);
	//构造比例缩放矩阵 相对pt放缩
	CMatrix2d Scale(const double& ptX,const double& ptY,const double& fScaleX,const double& fScaleY);
	
	//构造绕原点旋转Angle角度矩阵(顺时针为+)
	CMatrix2d Rotate(const double& fRadAngle);
	//构造绕点(fx,fy)旋转Angle角度矩阵
	CMatrix2d Rotate(const double& ptX,const double& ptY,const double& fRadAngle);

	//构造相对X轴对称矩阵
	CMatrix2d MirrorX();
	//构造相对Y轴对称矩阵
	CMatrix2d MirrorY();
	//构造相对原点对称矩阵
	CMatrix2d MirrorOrigin();
	//构造相对直线(x1,y1),(x2,y2)对称矩阵
	CMatrix2d Mirror(const double& x1,const double& y1,const double& x2,const double& y2);

	//构造错切矩阵
	CMatrix2d ShearX(const double& xShear,const double& yShear,const double& fRadAngle);
	CMatrix2d ShearY(const double& xShear,const double& yShear,const double& fRadAngle);

	//构造转置矩阵
	CMatrix2d Transpose();

	 

};

// M = A * B 矩阵相乘
GLOABL_EXT_CLASS CMatrix2d operator*(const CMatrix2d& A,const CMatrix2d& B);
GLOABL_EXT_CLASS Pt2d operator*(const CMatrix2d& M,const Pt2d& pt);	
GLOABL_EXT_CLASS Pt2d operator*(const Pt2d& pt,const CMatrix2d& M);	

GLOABL_EXT_CLASS Box2d operator*(const CMatrix2d& M,const Box2d& b);	
GLOABL_EXT_CLASS Box2d operator*(const Box2d& b,const CMatrix2d& M);	

GLOABL_EXT_CLASS  Pt3d operator*(const CMatrix2d& M,const Pt3d& pt);	
GLOABL_EXT_CLASS Pt3d operator*(const Pt3d& pt,const CMatrix2d& M);	
