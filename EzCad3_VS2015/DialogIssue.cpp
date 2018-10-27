// D:\项目\EzCad3_VS2015\EzCad3_VS2015\DialogIssue.cpp : 实现文件
//

#include "stdafx.h"
#include "EzCad3_VS2015.h"
#include "DialogIssue.h"
#include "afxdialogex.h"
#include "qglobal.h"

// CDialogIssue 对话框

IMPLEMENT_DYNAMIC(CDialogIssue, CDialogEx)

CDialogIssue::CDialogIssue(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ISSUE, pParent)
{
	m_nMarkerId = 0;
}

CDialogIssue::~CDialogIssue()
{
}

void CDialogIssue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogIssue, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVETOFILE, &CDialogIssue::OnBnClickedButtonSavetofile)
	ON_BN_CLICKED(IDCANCEL, &CDialogIssue::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_EMAIL, &CDialogIssue::OnBnClickedButtonEmail)
END_MESSAGE_MAP()

#include "mapi.h"   
// CDialogIssue 消息处理程序
void SendMail(CString strEmailAddress,CString strSubject,CString strMsg,CString strSender,CString strFile )
{ 
	//装入MAPI32.DLL动态库
	HMODULE hMod = LoadLibrary(_T("MAPI32.DLL"));
	if (hMod == NULL)
	{
		AfxMessageBox(AFX_IDP_FAILED_MAPI_LOAD);
		return;
	}

	//获取发送邮件的函数地址
	ULONG(PASCAL *lpfnSendMail)(ULONG, ULONG, MapiMessage*, FLAGS, ULONG);
	(FARPROC&)lpfnSendMail = GetProcAddress(hMod, "MAPISendMail");

	if (lpfnSendMail == NULL)
	{
		AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
		return;
	}


	char* pstrEmailAddress = QGlobal::gf_StrToCharDelBuf(strEmailAddress);
	char* pstrSubject = QGlobal::gf_StrToCharDelBuf(strSubject);
	char* pstrMsg = QGlobal::gf_StrToCharDelBuf(strMsg);
	char* pstrSender = QGlobal::gf_StrToCharDelBuf(strSender);
	char* pstrFile = QGlobal::gf_StrToCharDelBuf(strFile);


	int nFileCount =1;   //有多少个附件需要发送

										  //分配内存保存附件信息 不能使用静态数组，因为不知道要发送附件的个数
	MapiFileDesc* pFileDesc = (MapiFileDesc*)malloc(sizeof(MapiFileDesc) * nFileCount);
	memset(pFileDesc, 0, sizeof(MapiFileDesc) * nFileCount); 

	//分配内存保存附件文件路径
	TCHAR* pTchPath = (TCHAR*)malloc(MAX_PATH * nFileCount);

	CString szText;
	for (int i = 0; i < nFileCount; i++)
	{
		TCHAR* p = pTchPath + MAX_PATH * i;  
		(pFileDesc + i)->nPosition = (ULONG)-1;
		(pFileDesc + i)->lpszPathName = pstrFile;
		(pFileDesc + i)->lpszFileName = pstrFile;
	}

	//收件人结构信息
	MapiRecipDesc recip;
	memset(&recip, 0, sizeof(MapiRecipDesc));
	recip.lpszAddress = pstrEmailAddress;
	recip.ulRecipClass = MAPI_TO;
	recip.lpszName = pstrSender;

	//邮件结构信息
	MapiMessage message;
	memset(&message, 0, sizeof(message));
	message.nFileCount = nFileCount;                         //文件个数
	message.lpFiles = pFileDesc;                          //文件信息
	message.nRecipCount = 1;                                  //收件人个数
	message.lpRecips = &recip;                             //收件人
	message.lpszSubject = pstrSubject;           //主题
	message.lpszNoteText = pstrMsg;              //正文内容

															   //保存本程序窗口指针，因为发完邮件后要返回本程序的窗口
	CWnd* pParentWnd = CWnd::GetSafeOwner(NULL, NULL);

	//发送邮件
	int nError = lpfnSendMail(0, 0, &message, MAPI_LOGON_UI | MAPI_DIALOG, 0); 
	if (nError != SUCCESS_SUCCESS && nError != MAPI_USER_ABORT
		&& nError != MAPI_E_LOGIN_FAILURE)
	{
		AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND);
	}

	//返回程序
	pParentWnd->SetActiveWindow();

	//不要忘了释放分配的内存
	delete[] pstrEmailAddress  ;
	delete[] pstrSubject ;
	delete[] pstrMsg  ;
	delete[] pstrSender  ;
	delete[] pstrFile ;


	free(pFileDesc);
	free(pTchPath);
	FreeLibrary(hMod);
}

void CDialogIssue::OnBnClickedButtonSavetofile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString szExt;
	CString szFilter;
	szExt = _T("issue");
	szFilter = _T("Issue files(*.issue)|*.issue||");
	CFileDialog dlg(FALSE, szExt,_T("Problem.issue"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
	if (dlg.DoModal() == IDOK)
	{
		CString strFileName = dlg.GetPathName();
		CString strEzdFile = QGlobal::gf_GetCurFileName();
		CString strDec;
		GetDlgItem(IDC_EDIT_DESC)->GetWindowText(strDec);
		E3_PackageIssueFile(0, strFileName, strEzdFile, strDec, m_nMarkerId);
	}	
	OnBnClickedCancel();
}


BOOL CDialogIssue::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
//	GetDlgItem(IDOK)->SetWindowText(QGlobal::gf_Str(_T("IDOK"), _T("&OK")));
	GetDlgItem(IDCANCEL)->SetWindowText(QGlobal::gf_Str(_T("IDCANCEL"), _T("&Cancel")));

	SetWindowText(QGlobal::gf_Str(_T("ISSUE"), _T("Issue")));
	GetDlgItem(IDC_STATIC_DESCRIPTION)->SetWindowText(QGlobal::gf_Str(_T("DESCRIPTION"), _T("Description")));
	GetDlgItem(IDC_BUTTON_SAVETOFILE)->SetWindowText(QGlobal::gf_Str(_T("SAVETOFILE"), _T("Save to file")));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogIssue::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CDialogIssue::OnBnClickedButtonEmail()
{
	// TODO: 在此添加控件通知处理程序代码
 	CString strFileName = QGlobal::gf_GetWorkPath() + _T("Temp.issue");
	CString strEzdFile = QGlobal::gf_GetCurFileName();
	CString strDec;
	GetDlgItem(IDC_EDIT_DESC)->GetWindowText(strDec);
	E3_PackageIssueFile(0, strFileName, strEzdFile, strDec, m_nMarkerId);
	SendMail(_T("6397423@qq.com"), _T("Problem"), _T("This is a test"), _T("q"), strEzdFile);
}
