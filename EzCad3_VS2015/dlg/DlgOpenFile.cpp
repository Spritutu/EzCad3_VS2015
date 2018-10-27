// DlgOpenFile.cpp : implementation file
//

#include "stdafx.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dlgs.h>
 
#include "..\EzCad3_VS2015.h"
#include "..\Ezcad3Doc.h"
#include "qglobal.h"
#include "DlgOpenFile.h"
 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/*
UINT (CALLBACK * OldOpenFileCallBackFun)(HWND hdlg,UINT uiMsg,WPARAM wParam,LPARAM lParam);

UINT CALLBACK MyFileOpenCallBackProc(HWND hdlg,      // handle to the dialog box window
							         UINT uiMsg,      // message identifier
							         WPARAM wParam,  // message parameter
							         LPARAM lParam)   // message parameter
{
	switch (uiMsg)
	{
	case WM_INITDIALOG:
		{
			SetWindowLong(hdlg, DWL_USER, lParam);
		}
		break;
	case WM_DESTROY:
		{
			LPOPENFILENAME lpOFN = (LPOPENFILENAME)GetWindowLong(hdlg, DWL_USER);
		}
		break;
	case WM_NOTIFY:
		{			
			SendMessage(hdlg,WM_NOTIFY,wParam,lParam);
		}
		break;
	default:
		break;
	}
    return (* OldOpenFileCallBackFun)( hdlg, uiMsg,  wParam, lParam);
}

*/

/////////////////////////////////////////////////////////////////////////////
// CDlgOpenFile

IMPLEMENT_DYNAMIC(CDlgOpenFile, CFileDialog)

CDlgOpenFile::CDlgOpenFile(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd,0,FALSE)
{    						    
	//m_ofn.Flags |= OFN_ENABLETEMPLATE |OFN_EXPLORER | OFN_ENABLEHOOK | OFN_HIDEREADONLY;//使用定义的模板   
	m_ofn.Flags = OFN_OVERWRITEPROMPT | OFN_ENABLESIZING | OFN_ENABLETEMPLATE |OFN_EXPLORER | OFN_ENABLEHOOK | OFN_HIDEREADONLY;//使用定义的模板   
	m_ofn.hInstance      = AfxGetResourceHandle();
    m_ofn.lpTemplateName = MAKEINTRESOURCE(IDD_DIALOG_OPENFILE);

	CString strSoftName = QGlobal::gf_Str(_T("SOFTNAME"), _T("EzCad3"));
	CString strSoftSuffix = QGlobal::gf_Str(_T("FILESUFFIX"), _T("ez3"));
	 
	CString str;
	str.Format(_T("%s files (*.%s)"), strSoftName, strSoftSuffix);	
	wsprintf(strFilter, str);
	wsprintf(strFilter + str.GetLength()+1, _T("*.%s"),  strSoftSuffix);

	if (strSoftSuffix == _T("ez3") && bOpenFileDialog)
	{
		CString str2=_T("Ezcad2 files (*.ezd)"); 
		wsprintf(strFilter + str.GetLength() + 2+ strSoftSuffix.GetLength() +2, str2);
		CString str3 = _T("*.ezd");
		wsprintf(strFilter + str.GetLength() + 2 + strSoftSuffix.GetLength() + 2 + str2.GetLength()+1, str3);
	}

	m_ofn.lpstrFilter = strFilter; 
	m_bShowPreview    = TRUE;   //显示预览图片
	m_bSavePreview    = TRUE;   //保存预览图片	
	m_bSavePick        = 0;   //保存所有对象
	      m_bBindID = FALSE;
	m_strSize    = _T("");
	m_strVersion = _T("");
	m_strAuthor  = _T("");
    m_strDate    = _T(""); 
    m_strComment = _T("");	

	m_pDibPreview = NULL;
	m_pCurDocument = NULL;
}

CDlgOpenFile::~CDlgOpenFile()
{
 

	if(m_pDibPreview!=NULL)
	{		
		delete m_pDibPreview;
		m_pDibPreview = NULL;
	}	
}


BEGIN_MESSAGE_MAP(CDlgOpenFile, CFileDialog)
	//{{AFX_MSG_MAP(CDlgOpenFile)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO_SAVEALL, OnRadSaveAll)
	ON_BN_CLICKED(IDC_RADIO_SAVEPICK, OnRadSavePick)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK_SHOWPRE,OnShowPreview)
	//ON_MESSAGE(WM_MY_DRAWPREVIEW,OnDrawPreview)
END_MESSAGE_MAP()

void CDlgOpenFile::DoDataExchange(CDataExchange* pDX) 
{
	// TODO: Add your specialized code here and/or call the base class
	CFileDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOpenFile)
    DDX_Check(pDX,IDC_CHECK_SHOWPRE, m_bShowPreview);
	DDX_Check(pDX,IDC_CHECK_SAVEPRE, m_bSavePreview);
	DDX_Check(pDX, IDC_CHECK_BINDID, m_bBindID); 
	DDX_Text(pDX,IDC_EDIT_FILESIZE,    m_strSize);
	DDX_Text(pDX,IDC_EDIT_FILEVER,     m_strVersion);
	DDX_Text(pDX,IDC_EDIT_FILEAUTHOR,  m_strAuthor);
	DDX_Text(pDX,IDC_EDIT_FILEDATE,    m_strDate);
	DDX_Text(pDX,IDC_EDIT_FILECOMMENT, m_strComment);

 //	DDX_Radio(pDX, IDC_RADIO_SAVEALL, m_bSavePick);
	//}}AFX_DATA_MAP
}

BOOL CDlgOpenFile::OnInitDialog() 
{
	CFileDialog::OnInitDialog();
	GetDlgItem(IDC_CHECK_SHOWPRE)->SetWindowText(QGlobal::gf_Str(_T("CHECK_SHOWPRE"),_T("Show preview")));
	GetDlgItem(IDC_CHECK_SAVEPRE)->SetWindowText(QGlobal::gf_Str(_T("CHECK_SAVEPRE"),_T("Save preview")));
	GetDlgItem(IDC_STATIC_SAVETYPE)->SetWindowText(QGlobal::gf_Str(_T("STATIC_SAVETYPE"),_T("Save type")));
	GetDlgItem(IDC_RADIO_SAVEALL)->SetWindowText(QGlobal::gf_Str(_T("RADIO_SAVEALL"),_T("Save all")));
	GetDlgItem(IDC_RADIO_SAVEPICK)->SetWindowText(QGlobal::gf_Str(_T("RADIO_SAVEPICK"),_T("Save pick")));
	GetDlgItem(IDC_IMFILE_FILEINFO)->SetWindowText(QGlobal::gf_Str(_T("FILEINFO"),_T("File information")));
	GetDlgItem(IDC_IMFILE_SIZE)->SetWindowText(QGlobal::gf_Str(_T("SIZE"),_T("Size")));
	GetDlgItem(IDC_IMFILE_VERSION)->SetWindowText(QGlobal::gf_Str(_T("VERSION"),_T("Version")));
	GetDlgItem(IDC_IMFILE_AUTHOR)->SetWindowText(QGlobal::gf_Str(_T("AUTHOR"),_T("Author")));
	GetDlgItem(IDC_IMFILE_DATE)->SetWindowText(QGlobal::gf_Str(_T("DATE"),_T("Date")));
	GetDlgItem(IDC_IMFILE_COMMENT)->SetWindowText(QGlobal::gf_Str(_T("COMMENT"),_T("Comment")));
	GetDlgItem(IDC_CHECK_BINDID)->SetWindowText(QGlobal::gf_Str(_T("BINDID"), _T("Bind ID")));

	((CButton*)GetDlgItem(IDC_RADIO_SAVEALL))->SetCheck(!m_bSavePick);
	((CButton*)GetDlgItem(IDC_RADIO_SAVEPICK))->SetCheck(m_bSavePick);

	if(m_bOpenFileDialog)
	{//文件打开方式		
  		GetDlgItem(IDC_CHECK_SHOWPRE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_SAVEPRE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_BINDID)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_EDIT_FILEAUTHOR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FILEDATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FILECOMMENT)->EnableWindow(FALSE);

		GetDlgItem(IDC_STATIC_SAVETYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO_SAVEALL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO_SAVEPICK)->ShowWindow(SW_HIDE);
	}
	else
	{
		GetDlgItem(IDC_CHECK_SHOWPRE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_SAVEPRE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_BINDID)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_EDIT_FILEAUTHOR)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FILEDATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FILECOMMENT)->EnableWindow(TRUE);

		GetDlgItem(IDC_STATIC_SAVETYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_SAVEALL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_SAVEPICK)->ShowWindow(SW_SHOW);		
	}


	if (m_pCurDocument != NULL)
	{
		CEzcad3Doc* pdoc = (CEzcad3Doc*)m_pCurDocument;
		m_strAuthor = pdoc->m_strAuthor;
		m_strDate = pdoc->m_strDate;
		m_strComment = pdoc->m_strComment;

		if (pdoc->m_nExportMode & EXPORT_PREIMAGE)
			m_bSavePreview = TRUE;   //保存预览图片	
		else
			m_bSavePreview = FALSE;   //保存预览图片	

		 //保存所有选择对象
		if (pdoc->m_nExportMode & EXPORT_SELECT)
			m_bSavePick = TRUE;
		else
			m_bSavePick = FALSE;

		if (pdoc->m_nExportMode & EXPORT_BINDID)
			m_bBindID = TRUE;
		else
			m_bBindID = FALSE;
		


		((CButton*)GetDlgItem(IDC_RADIO_SAVEALL))->SetCheck(!m_bSavePick);
		((CButton*)GetDlgItem(IDC_RADIO_SAVEPICK))->SetCheck(m_bSavePick);

	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgOpenFile::OnRadSaveAll()
{
	if(m_bOpenFileDialog)
	{//文件打开方式
		return;
	}
 
}

void CDlgOpenFile::OnRadSavePick()
{
	if(m_bOpenFileDialog)
	{//文件打开方式
		return;
	}
	 
	UpdateData();
}

void CDlgOpenFile::OnShowPreview()
{
    UpdateData();
    //PostMessage(WM_MY_DRAWPREVIEW,NULL,NULL);  有错
	Invalidate();//2004.10.26 qy modify
}

void CDlgOpenFile::OnDrawPreview( )
{
	if(m_bOpenFileDialog==FALSE)
	{//文件保存状态
		return;   
	}

    CWnd* pWnd = GetDlgItem(IDC_STATIC_PREVIEW);
	if(pWnd==NULL)
		return;    
 //   DrawPreview(pWnd,m_pPreview_Bitmap);
	DrawPreview(pWnd,m_pDibPreview);
	
    return;
}
#include "qdib.h"
void CDlgOpenFile::DrawPreview(CWnd* pWnd,CBitmap* pBitmap)
{
	if (pWnd == NULL)
		return;

    CRect rect;
    pWnd->GetClientRect(rect);
    rect.InflateRect(-2,-2);
    
    CClientDC previewDC(pWnd);
	
    CRgn pRgn;
    pRgn.CreateRectRgnIndirect(rect);
    previewDC.SelectClipRgn(&pRgn);
	
    if(!m_bShowPreview || pBitmap == NULL || m_bOpenFileDialog==FALSE)
    {//不显示预览图片 或 图片为空 或 是保存状态
        CBrush Brsh(GetSysColor(COLOR_BTNFACE));
        previewDC.FillRect(rect,&Brsh);	
    }
    else
    {//显示预览图片		
        CBrush Brsh(GetSysColor(COLOR_BTNFACE));
        previewDC.FillRect(rect,&Brsh);		
	
	    CDC CompatibleDC;
        CompatibleDC.CreateCompatibleDC(&previewDC);		

        CBitmap* old;
        BITMAP BitInfo;
        pBitmap->GetObject(sizeof(BITMAP),&BitInfo);

		old = CompatibleDC.SelectObject(pBitmap);

		
		int newWidth  = rect.Width(); 
		int newHeight = rect.Height();
		if(newWidth <=0)
			newWidth = 1;
		if(newHeight <=0)
			newHeight = 1;

		long OldScale  = newWidth/newHeight;
		if(OldScale < 1)
			OldScale = 1;
		
		if(BitInfo.bmWidth <= rect.Width() &&  BitInfo.bmHeight <=rect.Height())
		{
			newWidth  = BitInfo.bmWidth;
			newHeight = BitInfo.bmHeight;
		}
		else 
		{			
			int nMapScale = 1;
			if(BitInfo.bmHeight > 0)
				nMapScale = BitInfo.bmWidth / BitInfo.bmHeight;
			if(nMapScale == 0)
				nMapScale = 1;

			if(OldScale > nMapScale)
			{
				newWidth = newHeight * nMapScale;
				if(newWidth < 0)
					newWidth = 1;				
			}
			else
			{
				newHeight = newWidth / nMapScale;
				if(newHeight < 0)
					newHeight = 1;
			}
		}       

		if(newWidth > rect.Width())
			newWidth = rect.Width();
		if(newHeight > rect.Height())
			newHeight = rect.Height();		
		
	
		::SetStretchBltMode(previewDC.m_hDC, COLORONCOLOR);	
		BOOL b = previewDC.StretchBlt(rect.Width()/2-newWidth/2,rect.Height()/2-newHeight/2,newWidth,newHeight,&CompatibleDC,0,0,BitInfo.bmWidth,BitInfo.bmHeight,SRCCOPY);
	
        CompatibleDC.SelectObject(old);
    }
}

void CDlgOpenFile::DrawPreview(CWnd* pWnd,CDIB* pDib)
{
	if (pWnd == NULL)
		return;
	
    CRect rect;
    pWnd->GetClientRect(rect);
    rect.InflateRect(-2,-2);
    
    CClientDC previewDC(pWnd);
	
    CRgn pRgn;
    pRgn.CreateRectRgnIndirect(rect);
    previewDC.SelectClipRgn(&pRgn);
	
    if(!m_bShowPreview || pDib == NULL || m_bOpenFileDialog==FALSE)
    {//不显示预览图片 或 图片为空 或 是保存状态
        CBrush Brsh(GetSysColor(COLOR_BTNFACE));
        previewDC.FillRect(rect,&Brsh);	
    }
    else
    {//显示预览图片		
        CBrush Brsh(GetSysColor(COLOR_BTNFACE));
        previewDC.FillRect(rect,&Brsh);				
     	
		int newWidth  = rect.Width(); 
		int newHeight = rect.Height();
		if(newWidth <=0)
			newWidth = 1;
		if(newHeight <=0)
			newHeight = 1;
		
		long OldScale  = newWidth/newHeight;
		if(OldScale < 1)
			OldScale = 1;
		
		if(pDib->m_nWidth <= rect.Width() &&  pDib->m_nHeight <=rect.Height())
		{
			newWidth  = pDib->m_nWidth;
			newHeight = pDib->m_nHeight;
		}
		else 
		{			
			int nMapScale = 1;
			if(pDib->m_nHeight > 0)
				nMapScale = pDib->m_nWidth / pDib->m_nHeight;
			if(nMapScale == 0)
				nMapScale = 1;
			
			if(OldScale > nMapScale)
			{
				newWidth = newHeight * nMapScale;
				if(newWidth < 0)
					newWidth = 1;				
			}
			else
			{
				newHeight = newWidth / nMapScale;
				if(newHeight < 0)
					newHeight = 1;
			}
		}       
		
		if(newWidth > rect.Width())
			newWidth = rect.Width();
		if(newHeight > rect.Height())
			newHeight = rect.Height();				
		
		::SetStretchBltMode(previewDC.m_hDC, HALFTONE);			
		POINT lefttop;
		lefttop.x = rect.Width()/2-newWidth/2;
		lefttop.y = rect.Height()/2-newHeight/2;
		CRect rc(lefttop,CSize(newWidth,newHeight));
		pDib->DrawDIB(previewDC,&rc);        
    }
}

void CDlgOpenFile::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CWnd* pWnd = GetDlgItem(IDC_STATIC_PREVIEW);
	if (pWnd)
	{
		OnDrawPreview();
	}
}
int GetFileSize(CString szFileName)
{
	CFile file;
	if (file.Open(szFileName, CFile::modeRead))
	{
		int nLen = file.GetLength();
		file.Close();
		return nLen;
	}
	return 0;
}
BOOL CDlgOpenFile::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRet = CFileDialog::OnNotify(wParam, lParam, pResult);

	LPOFNOTIFY pofn = (LPOFNOTIFY)lParam;
	switch(pofn->hdr.code)
	{
		case CDN_SELCHANGE:			 
			{	
				if(m_bOpenFileDialog)
				{//文件打开方式
				 
					if(m_pDibPreview!=NULL)
					{						
						delete m_pDibPreview;
						m_pDibPreview = NULL;
					}
					
					//20180815
					WCHAR szFile[MAX_PATH] = { 0 };
					int nChars = CommDlg_OpenSave_GetFilePathW(GetParent()->GetSafeHwnd(), szFile, sizeof(szFile));
					if (nChars <= sizeof(szFile))
					{ 
						long nSize = GetFileSize(szFile) / 1024;
						if (nSize <= 0)
						{
							m_strSize.Format(_T("%ldB"), nSize);
						}
						else
						{
							float fM = (float)nSize / 1024.0f;
							if (fM > 1.0f)
								m_strSize.Format(_T("%.2fMB"), fM);
							else
								m_strSize.Format(_T("%ldK"), nSize);
						}
						UpdateData(FALSE);

						CString szFileName;
						szFileName.Format(_T("%s"), szFile);

						CString szAuthorName,szDrawTime,szNotes;
						if(E3_GetEzdFileInfo(szFileName,szAuthorName,szDrawTime,szNotes)==0)
						{
							m_strAuthor  = szAuthorName;
							m_strDate    = szDrawTime;
							m_strComment = szNotes;	
							UpdateData(FALSE);
						}

						//读取预览图象
						if (m_bShowPreview)
						{							
					 		m_pDibPreview = E3_GetDibPreview(szFileName);  
						}						
					}
					OnDrawPreview();
				}
			}
			break;
		case CDN_FOLDERCHANGE:
			//OnDrawPreview();
			break;
		case CDN_TYPECHANGE://文件类型改变

			//m_nFilterIndex = pofn->lpOFN->nFilterIndex;//获取当前文件过滤器类型索引

			//FileTypeChange();
			break;
		case CDN_FILEOK:// The 'OK' pushbutton has been pressed.
			{
				UpdateData(TRUE);

				if (m_pCurDocument != NULL)
				{
			 		m_bSavePick = ((CButton*)GetDlgItem(IDC_RADIO_SAVEPICK))->GetCheck();

					CEzcad3Doc* pdoc = (CEzcad3Doc*)m_pCurDocument;
					 
					pdoc->m_strAuthor = m_strAuthor;
					pdoc->m_strDate = m_strDate;
					pdoc->m_strComment = m_strComment;

					if (m_bSavePreview)
					{
						pdoc->m_nExportMode |= EXPORT_PREIMAGE;   //保存预览图片	
					}
					else
					{
						pdoc->m_nExportMode &= ~EXPORT_PREIMAGE;   //保存预览图片	
					}


					if (m_bSavePick)
					{
						pdoc->m_nExportMode |= EXPORT_SELECT;     //保存所有选择对象
					}
					else
					{
						pdoc->m_nExportMode &= ~EXPORT_SELECT;     //保存所有选择对象
					}


					if (m_bBindID)
					{
						pdoc->m_nExportMode |= EXPORT_BINDID;     
					}
					else
					{
						pdoc->m_nExportMode &= ~EXPORT_BINDID;    
					}
					
				}
			}			
			break;
		default:
			break;
	}
    return bRet;
}


