#ifndef _MyDocManager_h
#define _MyDocManager_h

class CMyDocManager : public CDocManager
{
	DECLARE_DYNAMIC(CMyDocManager)
public:	
   
	virtual BOOL DoPromptFileName(CString& fileName, UINT nIDSTitle,DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate);
};


#endif