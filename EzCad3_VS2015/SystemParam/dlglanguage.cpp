// dlglanguage.cpp : implementation file
//

#include "stdafx.h"
#include "..\EzCad3_VS2015.h"
#include "dlglanguage.h"

#include "qglobal.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLanguage dialog


CDlgLanguage::CDlgLanguage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLanguage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLanguage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nValidNum = 0;
		m_pParam = NULL;
}


void CDlgLanguage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLanguage)
	DDX_Control(pDX, IDC_COMBO_LANG, m_comboLang);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLanguage, CDialog)
	//{{AFX_MSG_MAP(CDlgLanguage)	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLanguage message handlers

BOOL CDlgLanguage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_STATIC_LANGUAGE)->SetWindowText(QGlobal::gf_Str(_T("NEXTVALID"),_T("The change will be valid at next start")));
	
	// TODO: Add extra initialization here
	 
	//在指定目录查找指定文件,返回找到的文件数及文件名称
	CString szPath = QGlobal::gf_GetLangPath();	
	CString  szLangName[100];
	int nFileNum = QGlobal::gf_FindAllFileInPath(_T("*.ini"),szPath,100,szLangName);
	if(nFileNum<=0)
	{
		return FALSE;
	}

	
	int i;
	for( i=0;i<nFileNum;i++)
	{
		if(QGlobal::gf_IsValidLangFile(szLangName[i]))
		{
			m_szValidLangName[m_nValidNum] = szLangName[i];
			m_nValidNum++;
		}		
	}
	if(m_nValidNum<=0)
	{
		return FALSE;
	}

	CString strFile = m_pParam->GetParamString(SYS_STR_LANGFILE); 
	ASSERT(strFile.GetLength() > 0); 

	CString strUp;
	CString szValue;
	DWORD dwSize = 1000;
	BOOL bFindEng = FALSE;
	for(i=0;i<m_nValidNum;i++)
	{//寻找匹配的语言		
		GetPrivateProfileString(_T("EZCAD"),_T("DESCRIBABLE"),_T("NULL"),szValue.GetBuffer(dwSize),dwSize,m_szValidLangName[i]);
		szValue.ReleaseBuffer();
		szValue.Replace(_T("\\n"),_T("\n"));	//替换回换行符号
		m_comboLang.AddString(szValue);
		strUp = szValue.MakeUpper();
		
		if (strUp == _T("ENGLISH"))
		{
			bFindEng = TRUE;
		}
		if(strFile == m_szValidLangName[i])
		{
			m_comboLang.SetCurSel(i); 
		}
	}
 
	if (!bFindEng)
	{
		m_comboLang.AddString(_T("English"));
	}

	if(_tcscmp(m_pParam->GetParamString(SYS_STR_LANGFILE),EZCAD_DEFAULT_LANGFILE)==0)
	{
		m_comboLang.SetCurSel(m_nValidNum);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgLanguage::OnOK() 
{
	// TODO: Add extra validation here
	
}

void CDlgLanguage::OnCancel() 
{
	// TODO: Add extra cleanup here	

}

void CDlgLanguage::OK()
{	
	int n = m_comboLang.GetCurSel();
	if(n >=0 && n < m_nValidNum)
	{
		CString strFile = m_pParam->GetParamString(SYS_STR_LANGFILE); 
		ASSERT(strFile.GetLength() > 0); 
		if(strFile != m_szValidLangName[n])
		{//换了语言
			m_pParam->SetParamString(SYS_STR_LANGFILE,m_szValidLangName[n]);

			CString szValue;
			DWORD dwSize = 1000;
			GetPrivateProfileString(_T("EZCAD"),_T("LANGUAGE"),_T("NULL"),szValue.GetBuffer(dwSize),dwSize,m_szValidLangName[n]);
			szValue.ReleaseBuffer();
			szValue.Replace(_T("\\n"),_T("\n"));	//替换回换行符号

			//得到当前操作系统的语言版本
			WORD lang_id = ::GetSystemDefaultLangID();
			BYTE primary = PRIMARYLANGID( lang_id );
			BYTE sublang = SUBLANGID( lang_id );
			if(szValue == EZCAD_LANG_CHINESE_SIMP)
			{
				primary = LANG_CHINESE;
				sublang = SUBLANG_CHINESE_SIMPLIFIED;
			}
			else if(szValue == EZCAD_LANG_CHINESE_TRAD)
			{
				primary = LANG_CHINESE;
				sublang = SUBLANG_CHINESE_TRADITIONAL;
			}
			else 
			{
				primary = LANG_ENGLISH;
				sublang = SUBLANG_ENGLISH_US;
			}			
			
			m_pParam->SetParamInt(INT_PARAM_PRIMARYLANGID,primary); //主语言ID
			m_pParam->SetParamInt(INT_PARAM_SUBLANGID,sublang); //子语言ID	
		}
	}
	else if( n >=m_nValidNum)
	{
		m_pParam->SetParamInt(INT_PARAM_PRIMARYLANGID,LANG_ENGLISH); //主语言ID
		m_pParam->SetParamInt(INT_PARAM_SUBLANGID,SUBLANG_ENGLISH_US); //子语言ID	
		m_pParam->SetParamString(SYS_STR_LANGFILE,EZCAD_DEFAULT_LANGFILE);
	}
}
