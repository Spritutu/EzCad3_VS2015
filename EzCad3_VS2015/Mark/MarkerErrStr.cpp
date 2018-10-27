#include "stdafx.h"

#include "MarkerErrStr.h"
#include "QGlobal.h"

CString     gf_GetMarkerErrStr(int errCode)
{
	CString str;
	switch(errCode)
	{
	case MERR_SUCCESS:
		return QGlobal::gf_Str(_T("ERR_SUCCESS"),_T("Success"));		
		break;
	case MERR_INVALID_CMD:
		return QGlobal::gf_Str(_T("ERR_INVALID_CMD"),_T("Invalid command"));		
		break;
		
	case MERR_INVALID_PARAM:
		return QGlobal::gf_Str(_T("ERR_INVALID_PARAM"),_T("Invalid command parameter"));		
		break;
	case MERR_CANNT_RUN:
        return QGlobal::gf_Str(_T("ERR_CANNT_RUN"),_T("Can not run at current state"));		
		break;
	case MERR_CMD_OUTTIME:
		return QGlobal::gf_Str(_T("ERR_CMD_OUTTIME"),_T("run command outtime"));		
		break;
	case MERR_INVALID_HAN:
		return QGlobal::gf_Str(_T("ERR_INVALID_HAN"),_T("Invalid device handle"));		
		break;
	case MERR_CLEARLISTFAIL: 
		return QGlobal::gf_Str(_T("ERR_CLEARLISTFAIL"),_T("Clear list failed,list is running"));		
		break;		
	case MERR_WRITELISTFAIL2:   
		return QGlobal::gf_Str(_T("ERR_WRITELISTFAIL2"),_T("Write list failed,list is full"));		
		break;		
	case MERR_USER_STOP:
		return QGlobal::gf_Str(_T("ERR_USERSTOPMARK"),_T("User stop the mark"));
		break;	
	case MERR_CONNECTHOST:
		return QGlobal::gf_Str(_T("ERR_CONNECTHOST"),_T("Connect host failed!"));
		break;	
	case MERR_DOOROPEN:
		return QGlobal::gf_Str(_T("ERR_DOOROPEN"),_T("Door is opened,please close it!"));
		break;	
	case MERR_OUTRANGE:
		return QGlobal::gf_Str(_T("ERR_OUTRANGE"),_T("Axis out range!"));
		break;	
	case MERR_NOENTITY:
		return QGlobal::gf_Str(_T("ERR_NOENTITY"), _T("No entities!"));
		break;
	case MERR_NOTHOME:
		return QGlobal::gf_Str(_T("ERR_NOTHOME"), _T("Axis not homed!"));
		break;
	case MERR_NOMESH:
		return QGlobal::gf_Str(_T("ERR_NOMESH"), _T("No mesh entities!"));
		break;
	case MERR_FAIL:
		return QGlobal::gf_Str(_T("ERR_FAIL"), _T("Failed!"));
		break; 
	case MERR_ASSERT:
		return QGlobal::gf_Str(_T("ASSERT"),_T("Assert!"));
		break;	
	case MERR_USER_AXISSTOP:
		return QGlobal::gf_Str(_T("ERR_USERSTOPMARK"), _T("User stop the mark"));;
		break;
		
	default:
		{
			str.Format(_T("%s:%d"),QGlobal::gf_Str(_T("ERR_UNKNOW"),_T("Unknow command")),errCode);
			return str;		
		}
	}
	return str;
}


void gf_ShowStopSignalMessageBox(PMarker pDev)	
{	 
	CString strDef = QGlobal::gf_Str(_T("STOPSIGNALTRIG"),_T("Stop signal trigger ! Stop marking"));
	CString str;

	if(pDev==NULL)
	{
		return;
	}
	WORD data = E3_MarkerGetStopSignal(pDev);
	for(int i=0;i<16;i++)
	{
		WORD io = 0x0001 << i;
		if(E3_MarkerGetParamStopIOHigh(pDev) & io )
		{
			if(data & io)
			{
				str += E3_MarkerGetParamStopMsg(pDev, i);
				break;
			}
		}
		else if(E3_MarkerGetParamStopIOLow(pDev)  & io )
		{
			if(~data & io)
			{
				str += E3_MarkerGetParamStopMsg(pDev,i);
				break;
			}
		}
	}
	
	if(str.GetLength()<1)
	{
		return;
	}

	AfxMessageBox(str,MB_OK|MB_ICONWARNING);				
}