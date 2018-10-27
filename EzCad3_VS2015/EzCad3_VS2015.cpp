
// EzCad3_VS2015.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "EzCad3_VS2015.h"
#include "MainFrm.h"
#include "version.h"

#include "Ezcad3Doc.h"
#include "Ezcad3View.h"  
#include "QGlobal.h"
#include "SysParam.h" 
#include "DlgLicense.h" 
#include "SysParam.h"
#include "DlgSelUser.h"
#include "MyDocManager.h"
#include "QPngButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAXPATHLEN 1000
// CEzCad3_VS2015App

BEGIN_MESSAGE_MAP(CEzCad3_VS2015App, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CEzCad3_VS2015App::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CEzCad3_VS2015App::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CEzCad3_VS2015App 构造

CEzCad3_VS2015App::CEzCad3_VS2015App()
{
	m_bHiColorIcons = TRUE; 

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("EzCad3_VS2015.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


void CEzCad3_VS2015App::OnFileOpen()
{
	CWinAppEx::OnFileOpen();
}
// 唯一的一个 CEzCad3_VS2015App 对象

CEzCad3_VS2015App theApp;

CQSingleDocTemplate::CQSingleDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
	CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass):CSingleDocTemplate( nIDResource,  pDocClass,pFrameClass,  pViewClass)
{
}



void CQSingleDocTemplate::ChangeDocStr()
{
	if (!m_strDocStrings.IsEmpty())
	{
		CString strSoftName = QGlobal::gf_Str(_T("SOFTNAME"), _T("EzCad3"));
		CString strSoftSuffix = QGlobal::gf_Str(_T("FILESUFFIX"), _T("ez3"));

		if (!strSoftName.IsEmpty())
		{
		 	m_strDocStrings.Replace(_T("EzCad3"), strSoftName);
		}
		if (!strSoftSuffix.IsEmpty())
		{
		 	m_strDocStrings.Replace(_T("ez3"), strSoftSuffix);
		}
	}
}

HANDLE st_hMutexOne = NULL;
// CEzCad3_VS2015App 初始化
BOOL CEzCad3_VS2015App::InitInstance()
{ 
	st_hMutexOne = CreateMutex(NULL, TRUE, _T("EzCadV3Instance"));
	BOOL bFound = FALSE;
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		bFound = TRUE;
	if (st_hMutexOne != NULL)
	{
		ReleaseMutex(st_hMutexOne);
	}
	if (bFound == TRUE)
	{
		st_hMutexOne = NULL;

		//得到当前操作系统的语言版本
		WORD lang_id = ::GetSystemDefaultLangID();
		BYTE primary = PRIMARYLANGID(lang_id);
		BYTE sublang = SUBLANGID(lang_id);

		CString str = _T("Software is open!");

		if (primary == LANG_CHINESE)
		{
			if (sublang == SUBLANG_CHINESE_SIMPLIFIED)
			{
				str = _T("已经有一个Ezcad3软件实例在运行!");
			}
		}

		AfxMessageBox(str);
		return FALSE;
	}


	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要 AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("BJJCZ"));
	 
	InititalQKernal();//初始化QKernal

	m_pszAppName = _tcsdup(QGlobal::gf_Str(_T("SOFTNAME"), _T("EzCad3"))); // save non-localized name
 
	int nSoftVer = GetProfileInt(_T("Version"), _T("Soft"), 0);
	int nInterfaceVer = GetProfileInt(_T("Version"), _T("Interface"), 0);
	int nBuildVer = GetProfileInt(_T("Version"), _T("Build"), 0); 

    if (nInterfaceVer != INTERFACE_VERSION || nBuildVer != BUILD_VERSION )
	{//界面版本变了，需要重新设置，删除旧的注册表		
		CleanState();//删除旧的信息
	}

	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
	//CSingleDocTemplate* pDocTemplate;
	//pDocTemplate = new CSingleDocTemplate(
	CQSingleDocTemplate * pDocTemplate;
	pDocTemplate = new CQSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CEzcad3Doc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
#ifdef USE_EZCADVIEW2  
		RUNTIME_CLASS(CEzcad3View2));
#else
		RUNTIME_CLASS(CEzcad3View));
#endif
	if (!pDocTemplate)
		return FALSE;
	//用自己的DocManager代替默认的DocManager
	if (m_pDocManager == NULL)
	{
		m_pDocManager = new CMyDocManager();
	}

	pDocTemplate->ChangeDocStr();

	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	QGlobal::Log(_T("Ezcad3_1"));
	if (!E3_IsLicenceOk())
	{		
		AfxMessageBox(QGlobal::gf_Str(_T("SOFTLICENCEISUNVALID"), _T("Software licence is invalid!")));
		return FALSE;
	}

	QGlobal::Log(_T("Ezcad3_2"));
	if (gf_GetSysParam() != NULL && gf_GetSysParam()->GetParamInt(INT_PARAM_ENUSERPSW))
	{//需要选择用户
		CDlgSelUser dlgUser;
		if (dlgUser.DoModal() != IDOK)
		{
			return FALSE;
		}
	}
	QGlobal::Log(_T("Ezcad3_3"));
	
	// 调度在命令行中指定的命令。  如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	QGlobal::Log(_T("Ezcad3_4"));
	// 唯一的一个窗口已初始化，因此显示它并对其进行更新

	m_pMainWnd->ShowWindow(SW_MAXIMIZE);
	m_pMainWnd->UpdateWindow();
	gf_SetMainFrame((CFrameWnd*)m_pMainWnd);


	QGlobal::Log(_T("Ezcad3_5"));

	WriteProfileInt(_T("Version"), _T("Soft"), SOFT_VERSION);//保存版本信息
	WriteProfileInt(_T("Version"), _T("Interface"), INTERFACE_VERSION);//保存版本信息
	WriteProfileInt(_T("Version"), _T("Build"), BUILD_VERSION);//保存版本信息
  

	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_WORKSPACE, 0);
	}

	QGlobal::Log(_T("Ezcad3_6"));
	
	if (gf_GetMainFrame() != NULL)
	{
		((CMainFrame*)gf_GetMainFrame())->InitMenuText();
		((CMainFrame*)gf_GetMainFrame())->m_pDlgSplash->HideSplash();
		((CMainFrame*)gf_GetMainFrame())->m_barEntProp.m_wndEntBase.m_pMarker = ((CMainFrame*)gf_GetMainFrame())->m_wndMark.m_dlgMark.GetMarker();
	}
	QGlobal::Log(_T("Ezcad3_7"));

	if (!ShowAgreeLicence())
	{
		return FALSE;
	}

	QGlobal::Log(_T("Ezcad3_8"));

	SetEz3DocToReg();

	QGlobal::Log(_T("Ezcad3_9"));

	CString strRun = gf_GetSysParam()->GetParamString(SYS_STR_EXE_START_FILE);
	if (strRun.GetLength()>0)
	{ 
		char* pStr = QGlobal::gf_StrToCharDelBuf(strRun);
		WinExec(pStr, SW_SHOW);
		delete[] pStr;
	}
	return TRUE;
}

void CEzCad3_VS2015App::SetEz3DocToReg()
{
	TCHAR path[MAXPATHLEN];
	TCHAR drive[MAXPATHLEN];
	TCHAR dir[MAXPATHLEN];
	TCHAR fname[MAXPATHLEN];
	TCHAR ext[MAXPATHLEN];
	GetModuleFileName(m_hInstance, path, MAXPATHLEN);
	_wsplitpath_s(path, drive, dir, fname, ext);

	CString strParam;
	strParam .Format(_T("%s \"%%1\""), path);


	QGlobal::Log(_T("reg .ez3"));

	HKEY hKEY;//定义有关的hKEY,在查询结束时要关闭
			  //打开与路径 data_Set相关的hKEY
	LPCTSTR data_Set = _T(".ez3\\");
	//访问注册表，hKEY则保存此函数所打开的键的句柄
	long lret = ::RegCreateKey(HKEY_CLASSES_ROOT, data_Set, &hKEY);
	if (lret == ERROR_SUCCESS)
	{//如果打开hKEY,则中止程序的执行
	 //查询有关的数据	
		QGlobal::Log(_T("reg .ez3 Ok"));

		TCHAR name[255] = _T("EzCad3.Document");
		LPBYTE dataaddr = (LPBYTE)name;
		QGlobal::Log(_T("reg EzCad3.Document"));

		int nErr = ::RegSetValueEx(hKEY, _T(""), NULL, REG_SZ, dataaddr, 250);
		if (nErr != ERROR_SUCCESS)
		{ 
			QGlobal::Log(_T("reg EzCad3.Document fail"));
		  
		}
		::RegCloseKey(hKEY);//关闭打开的hKEY
		QGlobal::Log(_T("reg EzCad3.Document Ok"));
							//查询有关的数据		
		data_Set = _T("EzCad3.Document\\shell\\open\\command\\");
		lret = ::RegCreateKey(HKEY_CLASSES_ROOT, data_Set, &hKEY);
		if (lret == ERROR_SUCCESS)
		{//如果打开hKEY,则中止程序的执行 
			wcscpy_s(name, strParam);
			LPBYTE dataaddr = (LPBYTE)name; 
			if (::RegSetValueEx(hKEY, _T(""), NULL, REG_SZ, dataaddr, 250) != ERROR_SUCCESS)
			{
				QGlobal::Log(strParam + _T("fail")); 
			}
			::RegCloseKey(hKEY);//关闭打开的hKEY
		}
	}
	else
	{
		QGlobal::Log(_T("reg .ez3 fail"));
	}
}


BOOL CEzCad3_VS2015App::ShowAgreeLicence()
{  
	int bHaveAgree = GetProfileInt(_T("License"), _T("Enable"), 0);
	
	if (!bHaveAgree)
	{//没有同意过
		CDlgLicense dlgLicense;
		dlgLicense.m_strLice = QGlobal::gf_LoadAllLineStr(QGlobal::gf_GetWorkPath() + _T("res\\license.txt"));
		if (dlgLicense.DoModal() == IDCANCEL)
		{//不同意 
			return FALSE;
		}
		else
		{//同意
			WriteProfileInt(_T("License"), _T("Enable"),1);  
		}
	} 
	return TRUE;
}

int CEzCad3_VS2015App::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);
	if (gf_GetSysParam() != NULL)
	{
		CString strRun = gf_GetSysParam()->GetParamString(SYS_STR_EXE_ENDT_FILE);
		if (strRun.GetLength() > 0)
		{
			char* pStr = QGlobal::gf_StrToCharDelBuf(strRun);
			WinExec(pStr, SW_SHOW);
			delete[] pStr;
		} 
	}

	CloseQKernal();

	if (st_hMutexOne != NULL)
	{
		CloseHandle(st_hMutexOne);
		st_hMutexOne = NULL;
	}
	
	return CWinAppEx::ExitInstance();
}



// CEzcad3App 消息处理程序
void CEzCad3_VS2015App::InititalQKernal()
{ 
	TCHAR path[MAXPATHLEN];
	TCHAR drive[MAXPATHLEN];
	TCHAR dir[MAXPATHLEN];
	TCHAR fname[MAXPATHLEN];
	TCHAR ext[MAXPATHLEN];
	GetModuleFileName(m_hInstance, path, MAXPATHLEN);
	_wsplitpath_s(path, drive, dir, fname, ext);
	CString szPath;
	szPath = drive;
	szPath += dir;
	 
	E3_InitialKernal(szPath);//初始化内核
	
}


void   CEzCad3_VS2015App::CloseQKernal()
{ 
	E3_CloseKernal(); 
}

// CEzCad3_VS2015App 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
	CQPngButton m_buttonIssue;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedIssue();
	
	afx_msg void OnClose();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ISSUE, m_buttonIssue);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK1, &CAboutDlg::OnNMClickSyslink1)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ISSUE, OnBnClickedIssue)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(QGlobal::gf_Str(_T("ABOUT"), _T("About")) + _T(" ") + QGlobal::gf_Str(_T("SOFTNAME"), _T("EZCAD")));
	GetDlgItem(IDC_STATIC_COMPANY)->SetWindowText(QGlobal::gf_Str(_T("COMPANY"), _T("BJJCZ")));

	m_buttonIssue.LoadImage(QGlobal::gf_GetResourcePath() + _T("Issue.png"));


	CString strVer = QGlobal::gf_Str(_T("SOFTNAME"), _T("EZCAD")) + _T(" ") + QGlobal::gf_Str(_T("SOFTVERSION"), _T("3.0.0"));
	CString strBuild;
	strBuild.Format(_T(" Build:%d"), BUILD_VERSION);
	
	GetDlgItem(IDC_SOFTVERSION)->SetWindowText(strVer+ strBuild);


	GetDlgItem(IDC_SYSLINK1)->SetWindowText(_T("<a>") + QGlobal::gf_Str(_T("WEBSIBE"), _T("")) + _T("</a>"));
	GetDlgItem(IDC_ABOUT_LAW)->SetWindowText(QGlobal::gf_Str(_T("ABOUT_LAW"), _T("Warning: this computer program is protected by copyright law and international treaties. Unauthorized reproduction or distribution of this program, or any portion of it, may result in severe civil and criminal penalties, and will be prosecuted to the maximum extent possible under the law.")));
	GetDlgItem(IDOK)->SetWindowText(QGlobal::gf_Str(_T("IDOK"), _T("&Ok")));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CAboutDlg::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CString strURL = QGlobal::gf_Str(_T("WEBSIBE"), _T(""));
	if (!strURL.IsEmpty())
	{
		ShellExecute(m_hWnd, NULL, strURL, NULL, NULL, SW_SHOW);
	}
}

// 用于运行对话框的应用程序命令
void CEzCad3_VS2015App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CEzCad3_VS2015App 自定义加载/保存方法

void CEzCad3_VS2015App::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CEzCad3_VS2015App::LoadCustomState()
{
}

void CEzCad3_VS2015App::SaveCustomState()
{
}

// CEzCad3_VS2015App 消息处理程序





void CAboutDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnMouseMove(nFlags, point);
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	

	CDialogEx::OnOK();
}
#include "DialogIssue.h"
void CAboutDlg::OnBnClickedIssue()
{ 
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (E3_EntMgrGetModifyFlag(pEM))
	{
		AfxMessageBox(QGlobal::gf_Str(_T("CURFILEMODIFYPLSSAVEIT"), _T("The current file has been modified, please save it first!")));
		OnBnClickedOk();
		return;
	}

	CDialogIssue dlg;
	
	if (gf_GetMainFrame() != NULL)
	{
		PMarker pMarker = ((CMainFrame*)gf_GetMainFrame())->m_wndMark.m_dlgMark.GetMarker();
		if (pMarker != NULL)
		{
			dlg.m_nMarkerId = E3_MarkerGetSN(pMarker);
		}
	}
	dlg.DoModal();

	OnBnClickedOk();
}

void CAboutDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
	CDialogEx::OnOK();
}
