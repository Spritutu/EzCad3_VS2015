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

#ifndef MATRIX3D_H
#define MATRIX3D_H


class Pt3d; 
class Pt3df; 
class Pt2d;
class Pt2df;

class GLOABL_EXT_CLASS  CMatrix3d 
{
public:
    double x[4][4];
public:

    CMatrix3d(){Identity();};
	CMatrix3d(double* pMtx);
	~CMatrix3d();

	void Identity();//构造单位矩阵
	
	// |M| *= |A| 矩阵相乘
	CMatrix3d& operator*= (const CMatrix3d& A);		

	//矩阵求逆	
	CMatrix3d GetInverse() const;

	//构造平移矩阵	
    CMatrix3d Move(const double& fx,const double& fy,const double& fz);
	
	//构造比例缩放矩阵 相对原点放缩
	CMatrix3d Scale(const double& fScaleX,const double& fScaleY,const double& fScaleZ);
	//构造比例缩放矩阵 相对pt放缩
	CMatrix3d Scale(const double& ptX,const double& ptY,const double& ptZ,const double& fScaleX,const double& fScaleY,const double& fScaleZ);
	
	//构造绕X轴旋转Angle角度矩阵(顺时针为+)
	CMatrix3d RotateX(const double& fRadAngle);

	//构造绕X轴旋转Angle角度矩阵(顺时针为+)
	CMatrix3d RotateY(const double& fRadAngle);

	//构造绕Z轴旋转Angle角度矩阵(顺时针为+)
	CMatrix3d RotateZ(const double& fRadAngle);

	//构造绕点(fx,fy)旋转Angle角度矩阵
	CMatrix3d RotateZ(const double& ptX,const double& ptY,const double& fRadAngle);
 
	//构造绕轴ptAxis(必须为单位矩阵) 旋转指定角度矩阵
	CMatrix3d RotateAxis(const double& ptAxisX,const double& ptAxisY,const double& ptAxisZ,const double& fRadAngle);
 
	
	//构造相对X轴对称矩阵
	CMatrix3d MirrorX();
	//构造相对Y轴对称矩阵
	CMatrix3d MirrorY();
	//构造相对Y轴对称矩阵
	CMatrix3d MirrorZ();
	
	//构造转置矩阵
	CMatrix3d Transpose();

	friend GLOABL_EXT_CLASS CMatrix3d operator*(const CMatrix3d& A,const CMatrix3d& B);	
	friend GLOABL_EXT_CLASS Pt3d operator*(const CMatrix3d& M,const Pt3d& pt);	
	friend GLOABL_EXT_CLASS Pt3d operator*(const Pt3d& pt,const CMatrix3d& M);	
	friend GLOABL_EXT_CLASS Pt3df operator*(const Pt3df& pt,const CMatrix3d& M);	
};

// M = A * B 矩阵相乘
GLOABL_EXT_CLASS CMatrix3d operator*(const CMatrix3d& A,const CMatrix3d& B);
GLOABL_EXT_CLASS Pt3d operator*(const CMatrix3d& M,const Pt3d& pt);	
GLOABL_EXT_CLASS Pt3d operator*(const Pt3d& pt,const CMatrix3d& M);	

GLOABL_EXT_CLASS Pt3d operator*(const CMatrix3d& M, const Pt2d& pt);
GLOABL_EXT_CLASS Pt3d operator*(const Pt2d& pt, const CMatrix3d& M);
GLOABL_EXT_CLASS Pt3df operator*(const Pt2df& pt, const CMatrix3d& M);
 
#endif