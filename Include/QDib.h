/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： DIB.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/
#pragma once

class CSerialParam;
 


typedef enum 
{
	DIB_1BPP,			//   2 color image, palette-based
	DIB_2BPP,			//   4 color image, palttte-based
	DIB_4BPP,			//  16 color image, palette-based
	DIB_4BPPRLE,		//  16 color image, palette-based, RLE compressed
	DIB_8BPP,			// 256 color image, palette-based 
	DIB_8BPPRLE,		// 256 color image, palette-based, RLE compressed

	DIB_16RGB555,		// 15 bit RGB color image, 5-5-5
	DIB_16RGB565,		// 16 bit RGB color image, 5-6-5, 1 bit unused
	DIB_24RGB888,		// 24 bit RGB color image, 8-8-8
	DIB_32RGB888,		// 32 bit RGB color image, 8-8-8, 8 bit unused

	DIB_32RGBA8888,		// 32 bit RGBA color image, 8-8-8-8

	DIB_16RGBbitfields,	// 16 bit RGB color image, non-standard bit masks, NT-only
	DIB_32RGBbitfields,	// 32 bit RGB color image, non-standard bit masks, NT-only

	DIB_JPEG,			// embedded JPEG image
	DIB_PNG				// embedded PNG image
}  DIBFormat;


//颜色变换处理函数
typedef void (*CLR_TRANSFORM_PROC)(BYTE & red, BYTE & green, BYTE & blue);



class CDibFilter;

 int gf_GetDIBPixelSize(const BITMAPINFOHEADER & bmih);
 int gf_GetDIBColorCount(const BITMAPINFOHEADER & bmih);
BITMAPINFO* gf_BitmapToDIB(HPALETTE hPal,	HBITMAP  hBmp);	


GLOABL_EXT_CLASS BOOL gf_StretchDrawBmp(HDC hDC,CBitmap* pBmp, int dx, int dy, int dw, int dh , DWORD rop); 
						
//当前不支持压缩位图
class GLOABL_EXT_CLASS  CDIB
{
public:
	DIBFormat	m_nImageFormat ;// 像素格式 
	BITMAPINFO* m_pBMI         ;//BITMAPINFOHEADER + mask + color table 

	BYTE*       m_pBits        ;//m_pBMI中像素数据位置
	RGBTRIPLE*  m_pRGBTRIPLE   ;//m_pBMI中颜色表位置
	RGBQUAD*    m_pRGBQUAD     ;//m_pBMI中颜色表位置	
	DWORD*      m_pBitFields   ;// 16, 32-bpp masks within m_pBMI
	
	int         m_nWidth       ;//位图宽度
	int         m_nHeight      ;//位图高度
	int         m_nScanWidth   ;//扫描行的字节数 
	int			m_nScanDelta   ;//到下一扫描行的间隔	
	
	int			m_nPlanes      ;//面数plane count
	int			m_nBitCount    ;//每面的位数bit per plane
	int			m_nColorDepth  ;//颜色深度bit count * plane count
	int			m_nImageSize   ;//位图的像素数组尺寸 pixel array size

	int         m_nRGBTRIPLE   ;
	int         m_nRGBQUAD     ;//位图调色板位置偏移
	int         m_nOriginOffset;//位图数据位置偏移

	int			m_nClrUsed     ;//使用的颜色数No of color in color table
	int			m_nClrImpt     ;//实际使用的颜色数Real color used	
	
	short		m_nLockTimes   ;//DIB 被锁定次数
	
public:
	CDIB();
	~CDIB();
	CDIB(const CDIB& ds);
	CDIB& operator=(const CDIB& ds);
	void  Destroy();

	WORD  GetQDibVersion() const{return 0x0100;}//v1.0

	//pDIB不需要释放,由CDIB负责释放
	BOOL  AttachDIB(BITMAPINFO* pDIB);
	BOOL  CreateDIB(HGLOBAL hGlobal);

	int  GetDIBTotalSize()const;
	//创建一个新的图像,指定尺寸和位数
	//height < 0  从上到下扫描位图
	//height > 0  从下到上扫描位图
	BOOL Create(int width, int height, int bitcount,BYTE* pBits=NULL,int dpix=300,int dpiy=300);
	
	//从DDB创建一个新的DIB图像
	BOOL Create(CBitmap* pBMP,HDC hDC);
	
    void  LockDIB();	//锁定DIB
    void  UnlockDIB();	//解锁DIB
    BOOL  FreeDIB();	//释放DIB
	
	BITMAPINFO* GetBMI() const { return m_pBMI;  }
	BYTE *      GetBits()const { return m_pBits; }

	CSize GetSize()      const { return CSize(m_nWidth, m_nHeight); }
	CRect GetRect()      const { return CRect(CPoint(0, 0), GetSize());}
	int   GetWidth()     const { return m_nWidth;     } 
	int   GetHeight()    const { return m_nHeight;    }
	int   GetScanWidth() const { return m_nScanWidth; }
	int   GetBitCount()  const { return m_nBitCount;  }
	

	void  GetDIBDpm(LONG& lDpmX,LONG& lDpmY);

	bool  IsCompressed() const 
	{
		return (m_nImageFormat == DIB_4BPPRLE) ||
			   (m_nImageFormat == DIB_8BPPRLE) ||
			   (m_nImageFormat == DIB_JPEG) ||
			   (m_nImageFormat == DIB_PNG);
	}

	//使图像的m_nScanDelta为正
	void ChangeScanDeltaToPositive();
	void ChangeScanDeltaToNegative();

	//像素处理
	DWORD GetPixelIndex(const int& x, const int& y) const;
	BOOL  SetPixelIndex(const int& x, const int& y, const DWORD& index);

	void  GetPixelColor(const int& x, const int& y,COLORREF& clr)const;//得到指定点的颜色
	int   GetPixelGrayLever(const int& x, const int& y)const;//得到指定点的灰度
 
	//灰度化处理
	BOOL  ToGreyScale();

	//发亮处理
	BOOL  ToLighten(double bright,double contrast=0.0);
	
	BOOL  ColorTransform(CLR_TRANSFORM_PROC map);

	BOOL  MirrorX();//X镜像    
	BOOL  MirrorY();//Y镜像

	//旋转
	CDIB  Rotated(float radians,COLORREF bkClr = RGB(0,0,0));
	
	BOOL  ConvertTo256();  //把当前(2,4,16)色图象转为256色图
	BOOL  ConvertTo24Bit();  //把当前图象转为24位图
public:

	BOOL  LoadBMP(LPCTSTR lpszPathName);
	BOOL  LoadBMP(HINSTANCE hInst, LPCTSTR lpResourceName);
	BOOL  LoadBMP(HINSTANCE hInst, UINT uID) { return LoadBMP(hInst, MAKEINTRESOURCE(uID)); };
//图像存储
	BOOL  SaveBMP(LPCTSTR lpszPathName);

	BOOL  LoadPCX(LPCTSTR lpszPathName);
	BOOL  LoadTGA(LPCTSTR lpszPathName);
	BOOL  LoadGIF(LPCTSTR lpszPathName);
	BOOL  LoadJPG(LPCTSTR lpszPathName);
	BOOL  LoadPNG(LPCTSTR lpszPathName);
	BOOL  LoadTIF(LPCTSTR lpszPathName);

	BOOL  LoadImageFile(CString lpszPathName);

	BOOL  LoadImageFileByGdiPlus(LPCTSTR lpszPathName);

	BOOL  ReadDIB(CFile& file);
	BOOL  SaveDIB(CFile& file);
public:

	BOOL  SpatialFilter(CDibFilter& filter);//空间过滤器

	CDIB* ConvertSize(int newWidth,int newHeight);

	void  FloydSteinbergDither();
	void  StuckiDither();
	void  JarvisDither();
	void  BayerDither();

	void  HalfTone();
public:
	BOOL   DrawDIB(CDC& dc, const CRect* rcDst=NULL, const CRect* rcSrc=NULL, DWORD rop = SRCCOPY);	
	
	BOOL MyDrawDIB(CDC& dc, const CRect* rcDst=NULL, const CRect* rcSrc=NULL, CPalette* pPal=NULL);	

	int DrawDIB(HDC hDC, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, DWORD rop)
	{
		if ( m_pBMI )
		{
			::SetStretchBltMode(hDC, COLORONCOLOR);			
			//::SetStretchBltMode(hDC, HALFTONE);			
			//::SetStretchBltMode(hDC, WHITEONBLACK);			
		
			return ::StretchDIBits(hDC, dx, dy, dw, dh, sx, sy, sw, sh,m_pBits, m_pBMI, DIB_RGB_COLORS, rop);
		}
		else
			return GDI_ERROR;
	}

	int SetDIB(HDC hDC, int dx, int dy, int firstscan, int scanno, const BYTE * pBits)
	{
		if ( m_pBMI )
			return ::SetDIBitsToDevice(hDC, 
					dx, dy, m_nWidth, m_nHeight, 0, 0, firstscan, scanno, 
					pBits, m_pBMI, DIB_RGB_COLORS);
		else
			return GDI_ERROR;
	}

	//创建与屏幕兼容的HBITMAP
	HBITMAP ConvertToDDB(HDC hDC);

public:
	//数据引入/存储
	virtual BOOL Serialize(CSerialParam& Param);
};


class CDibFilter
{
protected:
	int m_nHalf;//(n-1)/2,一般n=3时，m_nHalf=1
private:
	virtual BYTE Kernel(BYTE* pPixel,int dx,int dy) = 0;
public:
	int GetHalf()const {return m_nHalf;}
	CDibFilter (){m_nHalf = 1;}

	virtual ~CDibFilter(){}
	virtual void Filter8bpp (BYTE* pDst, BYTE* pSrc,int nWidth,int ndy);
	virtual void Filter24bpp(BYTE* pDst, BYTE* pSrc,int nWidth,int ndy);
	virtual void Filter32bpp(BYTE* pDst, BYTE* pSrc,int nWidth,int ndy);
};

//8位图象变换
inline void CDibFilter::Filter8bpp (BYTE* pDst, BYTE* pSrc,int nWidth,int dy)
{
	memcpy(pDst ,pSrc ,m_nHalf);
	pDst+= m_nHalf;
	pSrc+= m_nHalf;
	for(int i = nWidth - 2 * m_nHalf; i > 0 ; i--)
	{
		*pDst ++ = Kernel( pSrc++ , 1 ,dy );
	}
	memcpy(pDst ,pSrc ,m_nHalf);
}

//24位图象变换
inline void CDibFilter::Filter24bpp (BYTE* pDst, BYTE* pSrc,int nWidth,int dy)
{
	memcpy(pDst ,pSrc ,m_nHalf*3);
	pDst+= m_nHalf * 3;
	pSrc+= m_nHalf * 3;
	for(int i = nWidth - 2 * m_nHalf; i > 0 ; i--)
	{
		*pDst ++ = Kernel( pSrc++ , 3 ,dy );
		*pDst ++ = Kernel( pSrc++ , 3 ,dy );
		*pDst ++ = Kernel( pSrc++ , 3 ,dy );
	}
	memcpy(pDst ,pSrc ,m_nHalf*3);
}

//32位图象变换
inline void CDibFilter::Filter32bpp (BYTE* pDst, BYTE* pSrc,int nWidth,int dy)
{
	memcpy(pDst ,pSrc ,m_nHalf*4);
	pDst+= m_nHalf * 4;
	pSrc+= m_nHalf * 4;
	for(int i = nWidth - 2 * m_nHalf; i > 0 ; i--)
	{
		*pDst ++ = Kernel( pSrc++ , 4 ,dy );
		*pDst ++ = Kernel( pSrc++ , 4 ,dy );
		*pDst ++ = Kernel( pSrc++ , 4 ,dy );
		*pDst ++ = *pSrc++ ;//拷贝alpha通道
	}
	memcpy(pDst ,pSrc ,m_nHalf*4);
}

class CDibFilter33 : public CDibFilter
{
public:
	int  k00,k01,k02;//系数矩阵
	int  k10,k11,k12;
	int  k20,k21,k22;
	int  nWeight;//权值
	int  nAdd;   //常量
	BOOL bCheckbound;//检查边界
public:
	CDibFilter33(int m00, int m01, int m02,
		         int m10, int m11, int m12,
				 int m20, int m21, int m22,
				 int  weight,
				 int  add,
				 BOOL checkbound = TRUE)
	{
		k00 = m00;
		k01 = m01;
		k02 = m02;//系数矩阵
		k10 = m10;
		k11 = m11;
		k12 = m12;
		k20 = m20;
		k21 = m21;
		k22 = m22;
		ASSERT(weight!=0);
		nWeight = weight;//权值
		nAdd = add;   //常量
		bCheckbound = checkbound;//检查边界
	}
public:
	virtual BYTE Kernel(BYTE * pPixel, int dx, int dy)
	{
		int rslt = ( pPixel[-dy-dx] * k00 + pPixel[-dy] * k01 + pPixel[-dy+dx] * k02 +
			         pPixel[   -dx] * k10 + pPixel[0]   * k11 + pPixel[   +dx] * k12 +
			         pPixel[ dy-dx] * k20 + pPixel[dy]  * k21 + pPixel[ dy+dx] * k22 ) / nWeight + nAdd;

		if ( bCheckbound )
		{
			if ( rslt < 0 )
				return 0;
			else if ( rslt > 255 )
				return 255;
		}
		return (BYTE)rslt;
	}
};

int gf_GetPixelGray(CDIB* pDib,int nBmpX,int nBmpY);
