
// Ezcad3Doc.cpp : CEzcad3Doc 类的实现
//

#include "stdafx.h"
#include "EzCad3_VS2015.h"
#include "Ezcad3Doc.h"

#include "QGlobal.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
 

// CEzcad3Doc

IMPLEMENT_DYNCREATE(CEzcad3Doc, CDocument)

BEGIN_MESSAGE_MAP(CEzcad3Doc, CDocument)
		ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
END_MESSAGE_MAP()


// CEzcad3Doc 构造/析构

CEzcad3Doc::CEzcad3Doc()
{
	// TODO: 在此添加一次性构造代码
	m_nExportMode = EXPORT_PREIMAGE;
}

CEzcad3Doc::~CEzcad3Doc()
{
}

BOOL CEzcad3Doc::OnNewDocument()
{
	m_strAuthor = _T("");
	m_strDate = _T("");
	m_strComment = _T("");

	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	if(E3_GetCmdMgr()!=NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(), _T("PICK"),SUBCMD_PICK_NEWFILE,0);
	}
	
	SetModifiedFlag(FALSE);  
	if(E3_GetCmdMgr()!=NULL)
	{ 		
		PEntMgr pEM =  E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
		if(pEM !=NULL)
		{
			E3_SetEntMgrModifyFlag(pEM,FALSE);
		}
	}
	 
	return TRUE;
}
  
BOOL CEzcad3Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	if(E3_GetCmdMgr()!=NULL)
	{
		m_strOpenFileName = lpszPathName;

		CEzcadDocParam doc;
		doc.m_strOpenFileName = this->m_strOpenFileName;
		doc.m_nExportMode = this->m_nExportMode;
		doc.m_strDate = this->m_strDate;
		doc.m_strComment = this->m_strComment;

		 
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_OPENFILE, (INT_PTR)(&doc));

		this->m_strOpenFileName = doc.m_strOpenFileName;
		this->m_nExportMode = doc.m_nExportMode;
		this->m_strDate = doc.m_strDate;
		this->m_strComment = doc.m_strComment;  
	}
	SetPathName(lpszPathName,TRUE);

	SetModifiedFlag(FALSE);  
	if(E3_GetCmdMgr()!=NULL)
	{ 
		PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr()); 
		if(pEM !=NULL)
		{
			E3_SetEntMgrModifyFlag( pEM, FALSE); 
		}
	}	 
	return TRUE;
}

BOOL CEzcad3Doc::SaveModified()
{  
	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM != NULL && E3_EntMgrGetModifyFlag(pEM))
	{
		 SetModifiedFlag(TRUE); 
	} 

	if (!IsModified())
		return TRUE;        // ok to continue
	
	// get name/title of document
	CString name;
	if (m_strPathName.IsEmpty())
	{
		// get name based on caption
		name = m_strTitle;
		if (name.IsEmpty())
			VERIFY(name.LoadString(AFX_IDS_UNTITLED));
	}
	else
	{
		// get name based on file title of path name
		name = m_strPathName;
/*		if (afxData.bMarked4)
		{
			AfxGetFileTitle(m_strPathName, name.GetBuffer(_MAX_PATH), _MAX_PATH);
			name.ReleaseBuffer();
		}*/
	}
	
	CString prompt;
	AfxFormatString1(prompt, AFX_IDP_ASK_TO_SAVE, name);
	switch (AfxMessageBox(prompt, MB_YESNOCANCEL, AFX_IDP_ASK_TO_SAVE))
	{
	case IDCANCEL:
		return FALSE;       // don't continue
		
	case IDYES:
		// If so, either Save or Update, as appropriate
		if (!DoFileSave())
			return FALSE;       // don't continue
		break;
		
	case IDNO:
		// If not saving changes, revert the document
		{
		if (E3_GetCmdMgr() != NULL)
		{
			PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
			if (pEM != NULL)
			{
				E3_SetEntMgrModifyFlag(pEM, FALSE);
			}
		}
		}
		break;
		
	default:
		ASSERT(FALSE);
		break;
	}
	return TRUE;    // keep going
}
BOOL CEzcad3Doc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	CWaitCursor wait;
	if(E3_GetCmdMgr()!=NULL)
	{
		m_strSaveFileName = lpszPathName;

		CEzcadDocParam doc;
		doc.m_strSaveFileName = this->m_strSaveFileName;
		doc.m_nExportMode = this->m_nExportMode;
		doc.m_strDate = this->m_strDate;
		doc.m_strComment = this->m_strComment;
		E3_CmdMgrRunCmd(E3_GetCmdMgr(), _T("PICK"), SUBCMD_PICK_SAVEFILE, (INT_PTR)(&doc)); 
	}
	
	SetModifiedFlag(FALSE);  
	if (E3_GetCmdMgr() != NULL)
	{
		PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
		if (pEM != NULL)
		{
			E3_SetEntMgrModifyFlag(pEM, FALSE);
		}
	}
	
	return TRUE;
}

// CEzcad3Doc 序列化

void CEzcad3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	
	}
	else
	{
		
	}
}

void CEzcad3Doc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_FILE_SAVE"),_T("&Save")));
	if(E3_GetCmdMgr()!=NULL)
	{ 
		BOOL b = E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_SAVEFILE);
		//ASSERT(b);
		pCmdUI->Enable(b);
		return;
	}
	pCmdUI->Enable(FALSE); 
}

void CEzcad3Doc::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here 
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_FILE_SAVE_AS"),_T("Save &As...")));
 
	if(E3_GetCmdMgr()!=NULL)
	{ 
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(), _T("PICK"),SUBCMD_PICK_SAVEFILE ));
		return;
	}
	pCmdUI->Enable(FALSE); 
}


// CEzcad3Doc 诊断

#ifdef _DEBUG
void CEzcad3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEzcad3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEzcad3Doc 命令
