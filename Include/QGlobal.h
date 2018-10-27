/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： QGlobal.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/

#pragma once
 

class CEntity;
class CEntMgr;
class Pt2d;

const int USERTYPE_ADMIN=0;
const int USERTYPE_DESIGN=1;
const int USERTYPE_WORK=2;
const int USERTYPE_DRAFTSMAN=3;

GLOABL_EXT_CLASS  void gf_SetMainFrame(CFrameWnd* pWnd);
GLOABL_EXT_CLASS  CFrameWnd* gf_GetMainFrame();

class  GLOABL_EXT_CLASS QGlobal
{
public:
	static CString     gf_GetEzdFileSuffix();

	static void        gf_SetClipboardFormat(UINT nFormat);
	static UINT        gf_GetClipboardFormat();

	//两字节字符转为双字节字符
	static WORD        gf_CharToDoubleByte(const BYTE s[3]); 
	static char*       gf_StrToCharDelBuf(CString str);
	static BOOL        IsDemoVersion();
	static int         gf_UnicodeToAnsi(LPWSTR lpWideCharStr, char* AnsiStr, int AnsiSize); 
	static int         gf_AnsiToUnicode(char* pAnsiStr, LPWSTR lpWideCharStr, int wideSize);

	static CString     gf_CharToStr(char* pCharStr);

	static double      ATOF(TCHAR* pWideStr);
	static double      ATOF(CString str);
	static int         ATOI(CString str);

	static void        Log(CString strLog);

	static CString     gf_Str(CString strID, CString strDefault);
	static void        gf_SetWorkPath(const CString& szPath);
	static CString     gf_GetWorkPath();

	static CString     gf_GetFontPath();//得到当前字体目录
	static CString     gf_GetLangPath();//得到当前语言文件目录
	static CString     gf_GetParamPath();
	static CString     gf_GetResourcePath();
	static CString     gf_GetCorFilePath();

	static CString     gf_GetCurUserName();//得到当前用户名字
	static void        gf_SetCurUserName(CString str);//设置当前用户名字


	static BOOL  IsFileExist(CString strFile);
	static CString GetFileName(CString strFile);

	static BOOL        gf_InitLanguage();

	//计算一个字符串有多少行字符串
	static int gf_GetLineNum(CString strText);

	//得到一个字符串中指定行的字符串
	static CString gf_GetLineNoStr(int lineno, const CString& strText, BOOL& bIsEnd);

	static CString gf_LoadAllLineStr(CString filename);

	static CString gf_LoadLineNoStrFromFile(int lineno, CString filename, BOOL& bIsEnd, int& nFileLineNum);

	static BOOL gf_IsValidLangFile(CString file);
	static void gf_SetLanguageFileName(CString str);
	static CString gf_GetLanguageFileName();

	//在指定目录查找指定文件，返回找到的文件数及文件名称
	static int gf_FindAllFileInPath(CString szFindFileName, CString szPath, int maxFile, CString* szFile);


	//通过ODBC直接读取Excel文件
	static int gf_ReadFromExcel(CString strExcelFile, CString strSheetName, CString strFieldName, int index, CString& strValue, BOOL& bIsEnd);
	static int gf_ReadFieldFromExcel(CString strExcelFile, CString strSheetName, CStringArray& arrayFieldName);

	static CBitmap* gf_DrawPrevBitmap(CWnd* pWnd, int nBMPWIDTH, int nBMPHEIGHT, CEntity* pEnt, int nDrawFlag, CEntMgr* pEM);



	static CString gf_GetUnitStr();//得到系统长度单位名字
	static CString gf_GetUnitStrOfM();//得到系统长度单位名字
	
	static CString gf_GetSpeedUnitStr();

	static CString gf_GetUnitStr(int nUnit);//得到系统长度单位名字
	static CString gf_GetUnitStrOfM(int nUnit);//得到系统长度单位*0.001名字
	
	static CString gf_GetLenStr(double dValue);//得到系统长度显示字符串
	static CString gf_GetIntStr(int nValue);

	//得到指定单位类型的指定毫米长度，
	static double gf_GetUnitLenFromMM(double dLenMM, int nUnitType);

	//删除小数点后的0
	static void  gf_StrDelZeroAfterDot(CString& str);

	static COLORREF gf_GetXORColor(COLORREF clr);

	static BOOL  InputWnd_GetPoint(CString str, Pt2d& pt, Pt2d ptPre);

	

	static BOOL gf_InitUsbMonitor(CWnd* pWndMonitor);
	static void gf_CloseUsbMonitor();
	static CWnd* gf_GetUsbMonitor();

	static void        gf_SetCurFileName(CString file);
	static CString     gf_GetCurFileName();

	static CString gf_GetFileExtStr(CString szfile);//得到文件名的后缀

	//0590-05FF 希伯莱字母 
	//0600-06FF 阿拉伯字母 
	static BOOL gf_IsFromLeftToRightLangChar(TCHAR ch);
	static BOOL gf_IsReadFromLeftToRightLang(CString strLine);

	static CString gf_ChangeOrderChar(CString strLine);
	//得到正确的字符顺序的字符串
	static CString gf_GetRightOrderString(CString String);

	//ASCii字符串转为双字节字符
	static int gf_AsciiToDoubleByte(CString String, WCHAR* strbuf, int len);

	static void gf_LoadTxtFile(CString filename, CStringArray& strArray);

	//是否字符串全是数字
	static BOOL gf_IsDigitalString(CString str);
	static BOOL gf_IsUtf8String(CString str);
	static BYTE* gf_UnicodeToUtf8(CString str, int& nSize);

	//得到指定语言代码
	static BYTE* gf_GetStrLangPageByte(int nLangPage, CString strText, int& nLen);

	static void MakeDialogOkCancelBtnToCenter(CDialogEx* pDialog);

	static BOOL gf_MemToFile(CMemFile& memFile, CFile& file);
	static BYTE*  gf_RealWholeBigFile(CString strFile, ULONGLONG& ullSize);

	static int gf_GetCpuProcessorCount();
};


const int SOUND_SUCCESS = 1;      //成功
const int SOUND_FAILURE = 2;      //失败
const int SOUND_WARN = 3;      //警告
GLOABL_EXT_CLASS void   gf_Sound(int bSoundType);

GLOABL_EXT_CLASS void   gf_SleepMs(int ms);