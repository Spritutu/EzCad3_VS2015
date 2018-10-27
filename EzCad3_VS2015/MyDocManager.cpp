#include "Stdafx.h"
#include "MyDocManager.h"
#include "DlgOpenFile.h"
#include "qglobal.h"
 
//得到文件名称 - used for open and save as
BOOL CMyDocManager::DoPromptFileName(CString& fileName, UINT nIDSTitle, DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate)
{  
	CDlgOpenFile dlg(bOpenFileDialog);

	POSITION pos =GetFirstDocTemplatePosition()  ;
	CDocTemplate* pDocTemp = GetNextDocTemplate( pos);
	 
	POSITION rPos = pDocTemp->GetFirstDocPosition() ;
	CDocument* pDoc = pDocTemp->GetNextDoc(rPos) ;
	dlg.m_pCurDocument = pDoc;

	if (dlg.DoModal() == IDOK)
	{
		fileName = dlg.GetPathName();
		if (fileName.Find(_T('.')) < 0)
		{
			CString strSoftSuffix = QGlobal::gf_Str(_T("FILESUFFIX"), _T("ez3"));
			fileName = fileName + _T(".") + strSoftSuffix;
		}
		return TRUE;
	}
	return FALSE;
}

#ifdef AFX_INIT_SEG
#pragma code_seg(AFX_INIT_SEG)
#endif

IMPLEMENT_DYNAMIC(CMyDocManager, CDocManager)