
#include "stdafx.h"
#include "EzCad3_VS2015.h" 
#include "MainFrm.h" 

#include "QGlobal.h"
#include "usermessdef.h"
 

#include "QEntLayerView.h"
#include "Ezcad3View.h"
#include "Ezcad3UserId.h"
#include "QUser.h" 

#include "SystemParam\DlgSystemParam.h"
#include "QDlg.h" 
#include "QMotormgr.h" 
#include "E:\Users\25019\Documents\Visual Studio 2017\Projects\180905-EZCAD3 UI\EzCad3_VS2015\EzCad3_VS2015\Mark\MarkStd\DlgMarking.h"
#include "E:\Users\25019\Documents\Visual Studio 2017\Projects\180905-EZCAD3 UI\EzCad3_VS2015\EzCad3_VS2015\Mark\MarkStd\DlgMark.h"





CString GetMessageFullText(UINT nID) 
{
	CString strFullText = _T("");
	switch (nID)
	{
		
	case ID_FILE_NEW:
		strFullText = QGlobal::gf_Str(_T("ID_FILE_NEW"), _T("Create new file\nNew"));
		break;
	case ID_FILE_OPEN:
		strFullText = QGlobal::gf_Str(_T("ID_FILE_OPEN"), _T("Open an exist file\nOpen"));
		break;
	case ID_FILE_SAVE:
		strFullText = QGlobal::gf_Str(_T("ID_FILE_SAVE"), _T("Save active file\nSave"));
		break;
	case ID_FILE_SAVE_AS:
		strFullText = QGlobal::gf_Str(_T("ID_FILE_SAVE_AS"), _T("Save active file to new filename\nSave as"));
		break;
		/*	case ID_FILE_IMGLIB:
		strFullText = QGlobal::gf_Str(_T("ID_FILE_IMGLIB"),_T("Open image library\nImage Library"));
		break;
		*/	case ID_FILE_PRINT:
			strFullText = QGlobal::gf_Str(_T("ID_FILE_PRINT"), _T("Print active document\nPrint"));
			break;
		case ID_FILE_MRU_FILE1:
			strFullText = QGlobal::gf_Str(_T("ID_FILE_MRU_FILE1"), _T("Open the document"));
			break;
		case ID_APP_EXIT:
			strFullText = QGlobal::gf_Str(_T("ID_APP_EXIT"), _T("Exit application;prompt to save document\nExit"));
			break;
		case ID_APP_ABOUT:
			strFullText = QGlobal::gf_Str(_T("ID_APP_ABOUT"), _T("Display program infomation\nAbout"));
			break;
		case ID_FILE_SYSTEM:
			strFullText = QGlobal::gf_Str(_T("ID_SYSTEM_PARAM"), _T("Setup system parameter\nSystem parameter"));
			break;
		case ID_FILE_MACHINEPARAMETER:
			strFullText = QGlobal::gf_Str(_T("ID_FILE_MACHINEPARAMETER"), _T("Setup machine parameter\nMachine parameter"));
			break;
			
		case ID_EDIT_UNDO:
			strFullText = QGlobal::gf_Str(_T("ID_EDIT_UNDO"), _T("Undo the last operation\nUndo"));
			break;
		case ID_EDIT_REDO:
			strFullText = QGlobal::gf_Str(_T("ID_EDIT_REDO"), _T("Redo the operation\nRedo"));
			break;
		case ID_EDIT_GROUP:
			strFullText = QGlobal::gf_Str(_T("ID_EDIT_GROUP"), _T("Group the picked object\nGroup"));
			break;
		case ID_EDIT_UNGROUP:
			strFullText = QGlobal::gf_Str(_T("ID_EDIT_UNGROUP"), _T("Ungroup the object\nUngroup"));
			break;
		case ID_EDIT_UNGROUPTEXT:
			strFullText = QGlobal::gf_Str(_T("ID_EDIT_UNGROUPTEXT"), _T("Ungroup the text\nUngroup text"));
			break;
		case ID_EDIT_COMBINE:
			strFullText = QGlobal::gf_Str(_T("ID_EDIT_COMBINE"), _T("Combine the picked object\nCombine"));
			break;
		case ID_EDIT_UNCOMBINE:
			strFullText = QGlobal::gf_Str(_T("ID_EDIT_UNCOMBINE"), _T("Uncombine the object\nUnconmbine"));
			break;
		case ID_EDIT_CUT:
			strFullText = QGlobal::gf_Str(_T("ID_EDIT_CUT"), _T("Cut the object to clipboard\nCut"));
			break;
		case ID_EDIT_COPY:
			strFullText = QGlobal::gf_Str(_T("ID_EDIT_COPY"), _T("Copy the object to clipboard\nCopy"));
			break;
		case ID_EDIT_PASTE:
			strFullText = QGlobal::gf_Str(_T("ID_EDIT_PASTE"), _T("Paste from clipboard\nPaste"));
			break;
		case ID_DRAW_PICK:
			strFullText = QGlobal::gf_Str(_T("ID_TOOL_PICK"), _T("Pick tool\nPick"));
			break;
		case ID_DRAW_NODE:
			strFullText = QGlobal::gf_Str(_T("ID_TOOL_NODE"), _T("Edit node\nEdit node"));
			break;
		case ID_DRAW_PLINE:
			strFullText = QGlobal::gf_Str(_T("ID_DRAW_PLINE"), _T("Draw curve\nDraw curve"));
			break;
		case ID_DRAW_LINE:
			strFullText = QGlobal::gf_Str(_T("ID_DRAW_LINE"), _T("Draw line\nDraw line"));
			break;
		case ID_DRAW_POINT:
			strFullText = QGlobal::gf_Str(_T("ID_DRAW_POINT"), _T("Draw point\nDraw point"));
			break;
		case ID_DRAW_CIR:
			strFullText = QGlobal::gf_Str(_T("ID_DRAW_CIRCLE"), _T("Draw circle\nDraw circle"));
			break;
		case ID_DRAW_ELP:
			strFullText = QGlobal::gf_Str(_T("ID_DRAW_ELLIPSE"), _T("Draw ellipse\nDraw ellipse"));
			break;
		case ID_DRAW_RECT:
			strFullText = QGlobal::gf_Str(_T("ID_DRAW_RECT"), _T("Draw rectangle\nDraw rectangle"));
			break;
		case ID_DRAW_POLYGON:
			strFullText = QGlobal::gf_Str(_T("ID_DRAW_POLY"), _T("Draw polygen\nDraw polygen"));
			break;
		case ID_DRAW_SPIRAL:
			strFullText = QGlobal::gf_Str(_T("ID_DRAW_SPIRAL"), _T("Draw Spiral\nDraw Spiral"));
			break;
		case ID_DRAW_TEXT:
			strFullText = QGlobal::gf_Str(_T("ID_DRAW_TEXT"), _T("Draw Text\nDraw Text"));
			break;
		case ID_DRAW_BARCODE:
			strFullText = QGlobal::gf_Str(_T("ID_DRAW_BARCODE"), _T("Draw BarCode\nDraw BarCode"));
			break;
		case ID_DRAW_BARCODE1:
			strFullText = QGlobal::gf_Str(_T("ID_DRAW_BARCODE1"), _T("Draw BarCode1\nDraw BarCode"));
			break;
		case ID_DRAW_BITMAP:
			strFullText = QGlobal::gf_Str(_T("ID_DRAW_BITMAP"), _T("Draw bitmap file\nDraw bitmap file"));
			break;
		case ID_DRAW_VECTORFILE:
			strFullText = QGlobal::gf_Str(_T("ID_DRAW_VECTOR"), _T("Draw vector file\nDraw vector file"));
			break;
		case ID_DRAW_TIME:
			strFullText = QGlobal::gf_Str(_T("ID_DRAW_TIME"), _T("Draw time\nDraw time"));
			break;
		case ID_DRAW_INPUT:
			strFullText = QGlobal::gf_Str(_T("ID_DRAW_INPUT"), _T("Draw io input\nDraw io input"));
			break;
		case ID_DRAW_OUTPUT:
			strFullText = QGlobal::gf_Str(_T("ID_DRAW_OUTPUT"), _T("Draw io output\nDraw io output"));
			break;
		case ID_DRAW_ENCODERDISTANCE:
			strFullText = QGlobal::gf_Str(_T("ID_DRAW_ENCODERDISTANCE"), _T("Draw encoder distance\nDraw encoder distance"));
			break;
			
		case ID_EDIT_HATCHENT:
			strFullText = QGlobal::gf_Str(_T("ID_MODIFY_HATCH"), _T("Hatch selected\nHatch"));
			break;

		case ID_MODIFY_ARRAY:
			strFullText = QGlobal::gf_Str(_T("ID_MODIFY_ARRAY"), _T("Array selected object\nArray"));
			break;
		case ID_MODIFY_OFFSETCURVE:
			strFullText = QGlobal::gf_Str(_T("ID_MODIFY_OFFSETCURVE"), _T("Offset selected curve\nCurve"));
			break;
		case ID_MODIFY_ROTATE:
			strFullText = QGlobal::gf_Str(_T("ID_MODIFY_ROTATE"), _T("Rotate selected object\nRotate"));
			break;

		case ID_PICK_BYPEN:
			strFullText = QGlobal::gf_Str(_T("ID_PICK_BYPEN"), _T("Pick objects by pen no.\nPick by pen"));
			break;
			
			/*case ID_MODIFY_TRANSFORM:
			strFullText = QGlobal::gf_Str(_T("ID_MODIFY_TRANSFORM"),_T("Transform object\nTransform"));
			break;
			case ID_MODIFY_PLASTIC:
			strFullText = QGlobal::gf_Str(_T("ID_MODIFY_PLASTIC"),_T("Plastic object\nPlastic"));
			break;
			case ID_MODIFY_CONNECT:
			strFullText = QGlobal::gf_Str(_T("ID_MODIFY_CONNECT"),_T("Auto connect curver\nAuto connect curve"));
			break;
			case ID_MODIFY_BREAKCROSS:
			strFullText = QGlobal::gf_Str(_T("ID_MODIFY_BREAKCROSS"),_T("Break cross point\nBreak cross point"));
			break;

			*/
			case ID_MODIFY_TOCURVE:
			strFullText = QGlobal::gf_Str(_T("ID_TOGRAPH"),_T("Convert to graph\nto graph"));
			break;
			
		case ID_VIEW_TOOLBAR:
			strFullText = QGlobal::gf_Str(_T("ID_VIEW_TOOLBAR"), _T("Show or hide toolbar\nS/H toolbar"));
			break;
		case ID_VIEW_STATUS_BAR:
			strFullText = QGlobal::gf_Str(_T("ID_VIEW_STATUS_BAR"), _T("Show or hide status bar\nS/H status bar"));
			break;
		case ID_VIEW_ZOOM:
			strFullText = QGlobal::gf_Str(_T("ID_VIEW_ZOOMBAR"), _T("Show or hide zoom bar\nS/H zoom bar"));
			break;
		case ID_VIEW_DRAWBAR:
			strFullText = QGlobal::gf_Str(_T("ID_VIEW_DRAW_BAR"), _T("Show or hide draw bar\nS/H draw bar"));
			break;
		case ID_VIEW_ENTPROP:
			strFullText = QGlobal::gf_Str(_T("ID_VIEW_ENTPROP"), _T("Show or hide object property bar\nS/H object property bar"));
			break;
		case ID_VIEW_ENTLIST:
			strFullText = QGlobal::gf_Str(_T("ID_VIEW_ENTLIST"), _T("Show or hide object list bar\nS/H object list bar"));
			break;
		case ID_VIEW_MARKPARAM:
			strFullText = QGlobal::gf_Str(_T("ID_VIEW_MARKPARAM"), _T("Show or hide mark parameter bar\nS/H mark parameter bar"));
			break;

		case ID_VIEW_MARKPANEL:
			strFullText = QGlobal::gf_Str(_T("ID_VIEW_MARKPARAM"), _T("Show or hide mark parameter bar\nS/H mark parameter bar"));
			break;
		case ID_ZOOM_PAN:
			strFullText = QGlobal::gf_Str(_T("ID_ZOOM_PAN"), _T("Zoom pan\nZoom pan"));
			break;
		case ID_ZOOM_IN:
			strFullText = QGlobal::gf_Str(_T("ID_ZOOM_IN"), _T("Zoom in\nZoom in"));
			break;
		case ID_ZOOM_OUT:
			strFullText = QGlobal::gf_Str(_T("ID_ZOOM_OUT"), _T("Zoom out\nZoom out"));
			break;
		case ID_ZOOM_WND:
			strFullText = QGlobal::gf_Str(_T("ID_ZOOM_WINDOW"), _T("Zoom window\nZoom window"));
			break;
		case ID_ZOOM_ALL:
			strFullText = QGlobal::gf_Str(_T("ID_ZOOM_ALL"), _T("Zoom all object\nZoom all	"));
			break;
		case ID_ZOOM_PICK:
			strFullText = QGlobal::gf_Str(_T("ID_ZOOM_PICK"), _T("Zoom all pick object\nZoom pick"));
			break;
		case ID_ZOOM_WORKSPACE:
			strFullText = QGlobal::gf_Str(_T("ID_ZOOM_WORKSPACE"), _T("View whole workspace\nView Workspace"));
			break;
		

		case ID_TOOLBAR_MARK3:
			strFullText = QGlobal::gf_Str(_T("ID_TOOLBAR_MARK3"), _T(" MARK\nMARK BUTTON"));
			break;
		case ID_TOOLBAR_RED:
			strFullText = QGlobal::gf_Str(_T("ID_TOOLBAR_RED"), _T(" RED BUTTON\nRED BUTTON"));
			break;


		case ID_VIEW_SANPGRID:
			strFullText = QGlobal::gf_Str(_T("ID_SNAP_GRID"), _T(" Snap grid\nSnap grid"));


		case ID_VIEW_SNAPGUILDLINE:
			strFullText = QGlobal::gf_Str(_T("ID_SNAP_GUILD"), _T(" Snap guildline\nSnap guildline"));
			break;
		case ID_VIEW_SNAPOBJECT:
			strFullText = QGlobal::gf_Str(_T("ID_SNAP_OBJECT"), _T(" Snap object\nSnap object"));
			break;
		case ID_VIEW_SNAPMESHVERTEX:
			strFullText = QGlobal::gf_Str(_T("ID_SNAP_MESHVERTEX"), _T(" Snap mesh vertex\nSnap mesh vertex"));
			break;

			case ID_MODIFY_RESORT:
				strFullText = QGlobal::gf_Str(_T("RESORT_INFO"),_T("Resort\nResort"));
				break;

		case ID_CMD_PICKALL:
			strFullText = QGlobal::gf_Str(_T("TT_PICKALL"), _T("Pick all object\nPick all"));
			break;
		case ID_CMD_PICKINVERT:
			strFullText = QGlobal::gf_Str(_T("TT_PICKINVERT"), _T("Pick object inverse\nPick inverse"));

			break;
		case ID_CMD_PICKDEL:
			strFullText = QGlobal::gf_Str(_T("TT_PICKDEL"), _T("Delete picked object\nDelete object"));

			break;
		case ID_CMD_PICKLOCK:
			strFullText = QGlobal::gf_Str(_T("TT_PICKLOCK"), _T("Lock picked object\nLock"));

			break;
		case ID_CMD_PICKCEN:
			strFullText = QGlobal::gf_Str(_T("TT_PICKCEN"), _T("Put to origin\nPut to origin"));
			break;
		case ID_CMD_PICKCENX:
			strFullText = QGlobal::gf_Str(_T("TT_PICKCENX"), _T("X Put to axis Y\nX Put to axis Y"));
			break;
		case ID_CMD_PICKCENY:
			strFullText = QGlobal::gf_Str(_T("TT_PICKCENY"), _T("Y Put to axis X\nY Put to axis X"));
			break;

		case ID_CMD_PICKMIRRORX:
			strFullText = QGlobal::gf_Str(_T("TT_PICKMIRRORX"), _T("Mirror X\nMirror X"));

			break;
		case ID_CMD_PICKMIRRORY:
			strFullText = QGlobal::gf_Str(_T("TT_PICKMIRRORY"), _T("Mirror Y\nMirror Y"));

			break;
		case ID_CMD_PICKUNLOCK:
			strFullText = QGlobal::gf_Str(_T("TT_PICKUNLOCK"), _T("Unlock picked object\nUnlock"));

			break;
			/*case IDC_BUTTON_PEN:
			strFullText = QGlobal::gf_Str(_T("TT_PICKPEN"),_T("pick by pen no\npick by pen"));

			break;*/
		case ID_CMD_PICKUNLOCKALL:
			strFullText = QGlobal::gf_Str(_T("TT_PICKUNLOCKALL"), _T("Unlock all object\nUnlock all"));

			break;
		case ID_CMD_NODE_ADD:
			strFullText = QGlobal::gf_Str(_T("TT_NODE_ADD"), _T("Add node\nadd node"));

			break;
		case ID_CMD_NODE_DEL:
			strFullText = QGlobal::gf_Str(_T("TT_NODE_DEL"), _T("Delete node\nDelete node"));

			break;
		case ID_CMD_NODE_UNITE:
			strFullText = QGlobal::gf_Str(_T("TT_NODE_UNITE"), _T("Unite node\nUnite node"));

			break;
		case ID_CMD_NODE_SEPA:
			strFullText = QGlobal::gf_Str(_T("TT_NODE_SEPARATE"), _T("Separate node\nSeparate node"));

			break;
		case ID_CMD_NODE_TOLINE:
			strFullText = QGlobal::gf_Str(_T("TT_NODE_LINE"), _T("convert to line\nconvert to line"));

			break;
		case ID_CMD_NODE_TOARC:
			strFullText = QGlobal::gf_Str(_T("TT_NODE_ARC"), _T("convert to arc\nconvert to arc"));

			break;
		case ID_CMD_NODE_TOBEZ:
			strFullText = QGlobal::gf_Str(_T("TT_NODE_BEZIER"), _T("convert to urve\nconvert to curve"));

			break;

		case ID_CMD_NODE_SHARP:
			strFullText = QGlobal::gf_Str(_T("TT_NODE_SHARP"), _T("Transition sharply\nTransition sharply"));

			break;
		case ID_CMD_NODE_SMOOTH:
			strFullText = QGlobal::gf_Str(_T("TT_NODE_SMOOTH"), _T("Transition smoothly\nTransition smoothly"));

			break;
		case ID_CMD_NODE_SYS:
			strFullText = QGlobal::gf_Str(_T("TT_NODE_SYSMETRIC"), _T("Transition symmetrically\nTransition symmetrically"));

			break;
		case ID_CMD_NODE_DIR:
			strFullText = QGlobal::gf_Str(_T("TT_NODE_DIR"), _T("Change curve direction\nChange curve direction"));

			break;
		case ID_CMD_NODE_CLOSE:
			strFullText = QGlobal::gf_Str(_T("TT_NODE_CLOSE"), _T("Auto closed curve\nAuto closed curve"));

			break;
		case ID_CMD_NODE_ALIGN:
			strFullText = QGlobal::gf_Str(_T("TT_NODE_ALIGN"), _T("Node align\nNode align"));

			break;
	//	case ID_CMD_NODE_REDUCE:
	//		strFullText = QGlobal::gf_Str(_T("TT_NODE_REDUCE"), _T("Auto reduce node\nAuto reduce node"));
	//		break;
		case ID_EDIT_ADDLAYER:
			strFullText = QGlobal::gf_Str(_T("TT_ADDLAYER"), _T("Add Layer\nAdd Layer"));
			break;
		case ID_EDIT_DELLAYER:
			strFullText = QGlobal::gf_Str(_T("TT_DELLAYER"), _T("Delete Layer \nDelete Layer"));
			break;
		case ID_VIEW_SHOWRULER:
			strFullText = QGlobal::gf_Str(_T("TT_SHRULER"), _T("Show or hide ruler"));
			break;
		case ID_VIEW_SHOWGRID:
			strFullText = QGlobal::gf_Str(_T("TT_SHGRID"), _T("Show or hide grid"));
			break;
		case ID_MODIFY_ARRAYTEXT:
			strFullText = QGlobal::gf_Str(_T("TT_MODIFY_ARRAYTEXT"), _T("Array text "));
			break;
		case ID_3DVIEW_WIRE:
			strFullText = QGlobal::gf_Str(_T("ID_3DVIEW_WIRE"), _T("View wire\nView wire"));
			break;
		case ID_3DVIEW_RENDER:
			strFullText = QGlobal::gf_Str(_T("ID_3DVIEW_RENDER"), _T("View render\nView render"));
			break;
		case ID_3DVIEW_RENDERLINE:
			strFullText = QGlobal::gf_Str(_T("ID_3DVIEW_RENDERLINE"), _T("View render lines\nView render lines"));
			break;
		case ID_3DVIEW_HIDEMESH:
			strFullText = QGlobal::gf_Str(_T("ID_3DVIEW_HIDEMESH"), _T("Show or hide mesh surface\nShow or hide mesh surface"));
			break;
		case ID_3DFUN_MESH3D:
			strFullText = QGlobal::gf_Str(_T("ID_3DFUN_MESH3D"), _T("Open mesh surface\nOpen mesh surface"));
			break;
		case ID_3DFUN_SLICEMESH:
			strFullText = QGlobal::gf_Str(_T("ID_3DFUN_SLICEMESH"), _T("Slice mesh surface\nSlice mesh surface"));
			break;
		case ID_3DFUN_ROTATEMESH:
			strFullText = QGlobal::gf_Str(_T("ID_3DFUN_ROTATEMESH"), _T("Rotate mesh surface\nRotate mesh surface"));
			break;
		case ID_3DFUN_MOVEMESH:
			strFullText = QGlobal::gf_Str(_T("ID_3DFUN_MOVEMESH"), _T("Move mesh surface\nMove mesh surface"));
			break;
		case ID_3DFUN_PRJ:
		strFullText = QGlobal::gf_Str(_T("ID_3DFUN_PRJ"), _T("Project mesh surface\nProject mesh surface"));
			break;
		case ID_3DFUN_BASESHAPE:
			strFullText = QGlobal::gf_Str(_T("ID_3DFUN_BASICSHAPE"), _T("Create basic 3d shape\nCreate basic 3d shape"));
			break;
		case ID_3DFUN_BMPTOMESH:
			strFullText = QGlobal::gf_Str(_T("ID_3DFUN_BMPTOMESH"), _T("Bitmap to mesh\nBitmap to mesh"));
			break;
		case ID_3DFUN_RUN:
			strFullText = QGlobal::gf_Str(_T("ID_VIEW_3D"), _T("View 3d & 2d\nView 3d & 2d"));
			break;
		case ID_3DFUN_FREEPAINT:
			strFullText = QGlobal::gf_Str(_T("ID_3DFUN_FREEPAINT"), _T("Free paint on mesh surface\nFree paint"));
			break;
		case ID_ZOOM_3D_UP:
			strFullText = QGlobal::gf_Str(_T("ID_VIEW_3DUP"), _T("Up view\nView from up"));
			break;
		case ID_ZOOM_3D_DN:
			strFullText = QGlobal::gf_Str(_T("ID_VIEW_3DDOWN"), _T("Down view\nView from down"));
			break;
		case ID_ZOOM_3D_LEFT:
			strFullText = QGlobal::gf_Str(_T("ID_VIEW_3DLEFT"), _T("Left view\nView from left"));
			break;
		case ID_ZOOM_3D_RIGHT:
			strFullText = QGlobal::gf_Str(_T("ID_VIEW_3DRIGHT"), _T("Right view\nView from right"));
			break;
		case ID_ZOOM_3D_FR:
			strFullText = QGlobal::gf_Str(_T("ID_VIEW_3DFRONT"), _T("Front view\nView from front"));
			break;
		case ID_ZOOM_3D_BACK:
			strFullText = QGlobal::gf_Str(_T("ID_VIEW_3DBACK"), _T("Back view\nView from back"));
			break;
		case ID_ZOOM_3D_ISO:
			strFullText = QGlobal::gf_Str(_T("ID_VIEW_3DISO"), _T("Iso view\nView from iso"));
			break;
		case ID_LASRER_MATERIALPROCESS:
			strFullText = QGlobal::gf_Str(_T("TT_MATERIALPARAMASSIS"), _T("Material parameter assistant\nMaterial parameter assistant"));
			break;
		case ID_ALIGN_LEFT:
			strFullText = QGlobal::gf_Str(_T("MENU_ALIGN_LEFT"), _T("Algin left")) + _T("\n") + QGlobal::gf_Str(_T("MENU_ALIGN_LEFT"), _T("Algin left"));
			break;
		case ID_ALIGN_RIGHT:
			strFullText = QGlobal::gf_Str(_T("MENU_ALIGN_RIGHT"), _T("Algin right")) + _T("\n") + QGlobal::gf_Str(_T("MENU_ALIGN_RIGHT"), _T("Algin right"));
			break;
	 	case ID_ALIGN_HCENTER:
			strFullText = QGlobal::gf_Str(_T("MENU_ALIGN_CENTER_HOR"), _T("Algin Hor center")) + _T("\n") + QGlobal::gf_Str(_T("MENU_ALIGN_CENTER_HOR"), _T("Algin Hor center"));
			break;
		case ID_ALIGN_TOP:
			strFullText = QGlobal::gf_Str(_T("MENU_ALIGN_TOP"), _T("Algin top")) + _T("\n") + QGlobal::gf_Str(_T("MENU_ALIGN_TOP"), _T("Algin top"));
			break;
		case ID_ALIGN_BOTTOM:
			strFullText = QGlobal::gf_Str(_T("MENU_ALIGN_BOTTOM"), _T("Algin Bottom")) + _T("\n") + QGlobal::gf_Str(_T("MENU_ALIGN_BOTTOM"), _T("Algin Bottom"));
			break;
		case ID_ALIGN_VCENTER:
			strFullText = QGlobal::gf_Str(_T("MENU_ALIGN_CENTER_VER"), _T("Algin Ver center")) + _T("\n") + QGlobal::gf_Str(_T("MENU_ALIGN_CENTER_VER"), _T("Algin Ver center"));
			break;
		case ID_ALIGN_CENTER:
			strFullText = QGlobal::gf_Str(_T("MENU_ALIGN_CENTER"), _T("Algin  center")) + _T("\n") + QGlobal::gf_Str(_T("MENU_ALIGN_CENTER"), _T("Algin center"));
			break; 
	
		case ID_DRAW_GUIDELINEBOX:
			strFullText = QGlobal::gf_Str(_T("MENU_GUILDLINEBOX"), _T("Draw guideline box")) + _T("\n") + QGlobal::gf_Str(_T("MENU_GUILDLINEBOX"), _T("Draw guideline box"));
			break;

		default:
			break;
	}

	return strFullText;

}

void CMainFrame::InitMenuText()
{ 

	if (!E3_IsLicenceEnable3D())
	{
		m_wndToolBar.RemoveButton(m_wndToolBar.CommandToIndex(ID_3DFUN_RUN));
		m_wndToolBar.RecalcLayout(); 
		m_wndToolBar.AdjustLayout();
	}

	//关闭3d功能工具条显示
	ShowPane(&m_wnd3dFunBar, FALSE, FALSE, FALSE);
	ShowPane(&m_wndZooml3dBar, FALSE, FALSE, FALSE);	
	ShowPane(&m_wndNodeCmdBar, FALSE, FALSE, FALSE);

	int nFilePos = 0, nEditPos = 1, nDrawPos = 2, nModiPos = 3, nViewPos = 4, nLaserFun = 5, nHelpPos = 6;

	CMFCToolBarButton* pFileMenu = (CMFCToolBarButton*)m_wndMenuBar.GetMenuItem(nFilePos);
	CMFCToolBarButton* pEditMenu = (CMFCToolBarButton*)m_wndMenuBar.GetMenuItem(nEditPos);
	CMFCToolBarButton* pDrawMenu = (CMFCToolBarButton*)m_wndMenuBar.GetMenuItem(nDrawPos);
	CMFCToolBarButton* pModiMenu = (CMFCToolBarButton*)m_wndMenuBar.GetMenuItem(nModiPos);
	CMFCToolBarButton* pViewMenu = (CMFCToolBarButton*)m_wndMenuBar.GetMenuItem(nViewPos);
	CMFCToolBarButton* pLaserFunMenu = (CMFCToolBarButton*)m_wndMenuBar.GetMenuItem(nLaserFun);
	CMFCToolBarButton* pHelpMenu = (CMFCToolBarButton*)m_wndMenuBar.GetMenuItem(nHelpPos);

	if (pFileMenu != NULL)
	{
		pFileMenu->m_strText = QGlobal::gf_Str(_T("MENU_FILE"), _T("&File"));
	}
	if (pEditMenu != NULL)
	{
		pEditMenu->m_strText = QGlobal::gf_Str(_T("MENU_EDIT"), _T("&Edit"));

	}
	if (pDrawMenu != NULL)
	{
		pDrawMenu->m_strText = QGlobal::gf_Str(_T("MENU_DRAW"), _T("&Draw"));
	}
	if (pModiMenu != NULL)
	{
		pModiMenu->m_strText = QGlobal::gf_Str(_T("MENU_MODI"), _T("&Modify"));
	}
	if (pViewMenu != NULL)
	{
		pViewMenu->m_strText = QGlobal::gf_Str(_T("MENU_VIEW"), _T("&View"));
	}
	if (pLaserFunMenu != NULL)
	{
		pLaserFunMenu->m_strText = QGlobal::gf_Str(_T("MENU_LASER"), _T("&Laser"));
	}
	if (pHelpMenu != NULL)
	{
		pHelpMenu->m_strText = QGlobal::gf_Str(_T("MENU_HELP"), _T("&Help"));
	}
	 
	m_wndMenuBar.AdjustLayout();

#ifdef  WELD_MODE  //焊接模式

	//for(int iIndex = 0 ; iIndex< m_wndToolBar.GetCount();iIndex++)
	//{
	//	CMFCToolBarButton* pButton = (CMFCToolBarButton*) m_wndToolBar.GetButton(iIndex);
	//	if(pButton->m_nID == ID_EDIT_HATCHENT)
	//	{
	//		m_wndToolBar.RemoveButton(iIndex);//删除hatch
	//		break;
	//	}		
	//}
	//
#endif


}

BOOL CMainFrame::OnShowPopupMenu(CMFCPopupMenu* pMenuPopup)
{
	if (pMenuPopup != NULL)
	{ 
		CMFCToolBarMenuButton* pParentButton = pMenuPopup->GetParentButton();
		 
		if (pParentButton != NULL)
		{

			if (pParentButton->m_strText == QGlobal::gf_Str(_T("MENU_FILE"), _T("&File")))
			{
				if (!E3_IsLicenceDynFocus())
				{//动态聚焦
					pMenuPopup->RemoveItem(pMenuPopup->GetMenuBar()->CommandToIndex(ID_FILE_PROJECTPARAM));
				}
				if (!m_bShowMachineParam)
				{
					pMenuPopup->RemoveItem(pMenuPopup->GetMenuBar()->CommandToIndex(ID_FILE_MACHINEPARAMETER));
				} 
				int nMenuCount = pMenuPopup->GetMenuItemCount();
				CMFCToolBarMenuButton* pBtn ;
				for (int i = 0; i < nMenuCount; i++)
				{
					pBtn = pMenuPopup->GetMenuItem(i);
					if (pBtn->m_strText == _T("Recent files"))
					{
						pBtn->m_strText = QGlobal::gf_Str(_T("RECENTFILES"), _T("Recent files 1"));
					} 
				} 
			}
			else if (pParentButton->m_strText == QGlobal::gf_Str(_T("MENU_DRAW"), _T("&Draw")))
			{
				if (m_bHideExtAxis)
				{
					BOOL bHide = TRUE;
					PMarker pMarker = NULL;
					CDlgMark* pDlg = gf_GetDlgMark();
					if (pDlg != NULL)
					{
						pDlg->LockMarker();
						pMarker = pDlg->GetMarker();
						if (pMarker != NULL && E3_MarkerGetAxisSol(pMarker) == MOTOR_SOL_XYZA_FREE)
						{
							bHide = FALSE;
						}
						pDlg->UnLockMarker();
					}
					if (bHide)
					{
						pMenuPopup->RemoveItem(pMenuPopup->GetMenuBar()->CommandToIndex(ID_DRAW_EXTAXIS));
					}
				}
				if (m_bHideEntEncoder)
				{
					pMenuPopup->RemoveItem(pMenuPopup->GetMenuBar()->CommandToIndex(ID_DRAW_ENCODERDISTANCE));
				}
				if (m_bHideEntIndex)
				{
					pMenuPopup->RemoveItem(pMenuPopup->GetMenuBar()->CommandToIndex(ID_DRAW_INDEX));
				}
				if (m_bHideEntCCD)
				{
					pMenuPopup->RemoveItem(pMenuPopup->GetMenuBar()->CommandToIndex(ID_DRAW_CCD));
				}
				if (m_bHideEntJump)
				{
					pMenuPopup->RemoveItem(pMenuPopup->GetMenuBar()->CommandToIndex(ID_DRAW_INPUTJUMP));
				}
				 
			}
			else if (pParentButton->m_strText == QGlobal::gf_Str(_T("MENU_EDIT"), _T("&Edit")))
			{
				int nMenuCount = pMenuPopup->GetMenuItemCount();

				CMFCToolBarMenuButton* pBtn = pMenuPopup->GetMenuItem(0);
				for (int i = 0; i < nMenuCount; i++)
				{
					pBtn = pMenuPopup->GetMenuItem(i);
					if (pBtn->m_strText == _T("Pick"))
					{
						pBtn->m_strText = QGlobal::gf_Str(_T("PICK"), _T("Pick"));
					}
					else if (pBtn->m_strText == _T("Node"))
					{
						pBtn->m_strText = QGlobal::gf_Str(_T("NODE"), _T("Node"));
					}
				}

				if (E3_IsLicenceEnWeld())
				{//焊接模式 
					pMenuPopup->RemoveItem(pMenuPopup->GetMenuBar()->CommandToIndex(ID_EDIT_HATCHENT));
				}
			}
			else if (pParentButton->m_strText == QGlobal::gf_Str(_T("MENU_MODI"), _T("&Modify")))
			{
				int nMenuCount = pMenuPopup->GetMenuItemCount();

				CMFCToolBarMenuButton* pBtn = pMenuPopup->GetMenuItem(0);
				for (int i = 0; i < nMenuCount; i++)
				{
					pBtn = pMenuPopup->GetMenuItem(i);
					if (pBtn->m_strText == _T("Distortion"))
					{
						pBtn->m_strText = QGlobal::gf_Str(_T("PLASTIC"), _T("Plastic"));
					}
					else if (pBtn->m_strText == _T("Align"))
					{
						pBtn->m_strText = QGlobal::gf_Str(_T("ALIGN"), _T("Align"));
					}
					else if (pBtn->m_strText == _T("Curve edit"))
					{
						pBtn->m_strText = QGlobal::gf_Str(_T("CURVEEDIT"), _T("Curve edit"));
					}
					else if (pBtn->m_strText == _T("Mesh edit"))
					{
						pBtn->m_strText = QGlobal::gf_Str(_T("MESHEDIT"), _T("Mesh edit"));
					}
				}
			}
			else if (pParentButton->m_strText == QGlobal::gf_Str(_T("MENU_VIEW"), _T("&View")))
			{
				if (!E3_IsLicenceEnable3D())
				{ //没有3d模式
					pMenuPopup->RemoveItem(pMenuPopup->GetMenuBar()->CommandToIndex(ID_VIEW_ZOOM3D));
				}


				int nMenuCount = pMenuPopup->GetMenuItemCount();
				CMFCToolBarMenuButton* pBtn = pMenuPopup->GetMenuItem(0);
				int nAppIndex = -1;
				for (int i = 0; i < nMenuCount; i++)
				{
					pBtn = pMenuPopup->GetMenuItem(i);
					if (pBtn->m_strText == _T("Zoom"))
					{
						pBtn->m_strText = QGlobal::gf_Str(_T("ZOOM"), _T("Zoom"));
					}
					if (pBtn->m_strText == _T("Application appearance"))
					{
						pBtn->m_strText = QGlobal::gf_Str(_T("APPAPPEARANCE"), _T("Application appearance"));
						nAppIndex = i;
					}
				} 
				
				if (m_bHideShowSol && nAppIndex >=0)
				{
					pMenuPopup->RemoveItem(nAppIndex); 
				}
			}
		}
	}
	return CFrameWndEx::OnShowPopupMenu(pMenuPopup);
}


// For customizing the default messages on the status bar
void CMainFrame::GetMessageString(UINT nID, CString& rMessage) const 
{
	rMessage = GetMessageFullText(nID);
	AfxExtractSubString(rMessage, rMessage, 0, _T('\n'));
}

LRESULT CMainFrame::OnSetMessageString(WPARAM wParam, LPARAM lParam)
{
	LRESULT retval = CFrameWnd::OnSetMessageString(wParam, lParam);

	//re-define the funciton

	LPCTSTR lpsz = NULL;
	CString strMessage;

	if (wParam == AFX_IDS_IDLEMESSAGE)	//means clear the status bar text
	{
		//E3_GetCmdMgr()->ShowTip();	//display 'Ready';
		return 0;
	}
	else if (lParam != 0) //指向一个字符串
	{
		ASSERT(wParam == 0); // can't have both an ID and a string
		lpsz = (LPCTSTR)lParam; // set an explicit string
	}
	else if (wParam != 0)//一个字符串资源IDS
	{
		//打印预览时映射SC_CLOSE成AFX_IDS_PREVIEW_CLOSE;
		//if (wParam == AFX_IDS_SCCLOSE && m_lpfnCloseProc != NULL)
		//wParam = AFX_IDS_PREVIEW_CLOSE;

		//得到资源ID所标识的字符串		
		strMessage = GetMessageFullText((UINT)wParam);
		AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
		lpsz = (LPCTSTR)strMessage;
	}
	else
		return 0;

	//设置状态栏文本
	if (GetMessageBar() != NULL)
	{
		GetMessageBar()->SetWindowText(lpsz);
	}
	return 0;

}
 

void CMainFrame::OnUpdateFileNew(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_FILE_NEW"), _T("&New")));
}
void CMainFrame::OnUpdateFileOpen(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_FILE_OPEN"), _T("&Open")));
}
void CMainFrame::OnUpdateFileSave(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_FILE_SAVE"), _T("&Save")));
}
void CMainFrame::OnUpdateFileSaveAs(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_FILE_SAVE_AS"), _T("Save &As...")));
}


void CMainFrame::OnUpdateFileExit(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_APP_EXIT"), _T("E&xit")));
}
void CMainFrame::OnUpdateFilePrint(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_FILE_PRINT"), _T("Print...")));
}
void CMainFrame::OnUpdateToolbar(CCmdUI *pCmdUI)
{
	
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_VIEW_TOOLBAR"), _T("&System bar")));
	pCmdUI->SetCheck(m_wndToolBar.IsVisible());
}
void CMainFrame::OnUpdateToolbarStatus(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_VIEW_STATUS_BAR"), _T("&Status Bar")));
	pCmdUI->SetCheck(m_wndStatusBar.IsVisible());
}


void CMainFrame::OnEditCopy()
{
	// TODO: 在此添加命令处理程序代码	
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_COPY, 0);
	}
}

void CMainFrame::OnUpdateEditCopy(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_EDIT_COPY"), _T("&Copy")));

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_COPY));
	}
}

void CMainFrame::OnEditCut()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_CUT, 0);
	}
}

void CMainFrame::OnUpdateEditCut(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_EDIT_CUT"), _T("Cu&t")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_CUT));
	}
}

void CMainFrame::OnEditPaste()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_PASTE, 0);
	}
}

void CMainFrame::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_EDIT_PASTE"), _T("&Paste")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_PASTE));
	}
}

void CMainFrame::OnEditUndo()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("UNDO"), 0, 0);
	}
}

void CMainFrame::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (E3_GetCmdMgr() == NULL)
	{
		return;
	}

	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}

	if (pEM != NULL)
	{
		CString Undo1;
		Undo1.Format(_T("%s %s"), QGlobal::gf_Str(_T("UNDO"), _T("Undo")), E3_EntMgrGetLastUndoName(pEM));
		pCmdUI->SetText(Undo1);
	}

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("UNDO"), 0));
	}
}

void CMainFrame::OnEditRedo()
{
	// TODO: 在此添加命令处理程序代码

	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("REDO"), 0, 0);
	}
}

void CMainFrame::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (E3_GetCmdMgr() == NULL)
	{
		return;
	}

	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}

	if (pEM != NULL)
	{
		CString Undo1;
		Undo1.Format(_T("%s %s"), QGlobal::gf_Str(_T("REDO"), _T("Redo")), E3_EntMgrGetLastRedoName(pEM));
		pCmdUI->SetText(Undo1);
	}


	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("REDO"), 0));
	}
}

void CMainFrame::OnEditAddlayer()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("LAYER"), SUBCMD_LAYER_ADD, 0);
	}
}

void CMainFrame::OnUpdateEditAddlayer(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("ADDLAYER"), _T("Add Layer")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("LAYER"), SUBCMD_LAYER_ADD));
	}
}

void CMainFrame::OnEditDellayer()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("LAYER"), SUBCMD_LAYER_DEL, 0);
	}
}

void CMainFrame::OnUpdateEditDellayer(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("DELLAYER"), _T("Delete Layer")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("LAYER"), SUBCMD_LAYER_DEL));
	}
}

void CMainFrame::OnEditCombine()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_COMBINE, 0);
	}
}

void CMainFrame::OnUpdateEditCombine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("COMBINE"), _T("Combine")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_COMBINE));
	}
}

void CMainFrame::OnEditUncombine()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_UNCOMBINE, 0);
	}
}

void CMainFrame::OnUpdateEditUncombine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("UNCOMBINE"), _T("UnCombine")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_UNCOMBINE));
	}
}

void CMainFrame::OnEditGroup()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_GROUP, 0);
	}
}

void CMainFrame::OnUpdateEditGroup(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("GROUP"), _T("Group")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_GROUP));
	}
}

void CMainFrame::OnEditUngroup()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_UNGROUP, 0);
	}
}

void CMainFrame::OnUpdateEditUngroup(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("UNGROUP"), _T("unGroup")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_UNGROUP));
	}
}
void CMainFrame::OnEditUngroupText()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_UNGROUPTEXT, 0);
	}
}

void CMainFrame::OnUpdateEditUngroupText(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("UNGROUPTEXT"), _T("UnGroup Text")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_UNGROUPTEXT));
	}
}
void CMainFrame::OnZoomWnd()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_WINDOW, NULL);
	}
}

void CMainFrame::OnUpdateZoomWnd(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CString strMessage = QGlobal::gf_Str(_T("ID_ZOOM_WINDOW"), _T("Zoom window\nZoom window"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);


	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_WINDOW));
		int nSubCmd;
		CString cmdName = E3_CmdMgrGetCurCmd(E3_GetCmdMgr(), nSubCmd);

		if ( _tcscmp(cmdName, _T("ZOOM")) == 0)
		{
	 		if (nSubCmd == SUBCMD_ZOOM_WINDOW)
				pCmdUI->SetCheck(TRUE);
			else
				pCmdUI->SetCheck(FALSE);
		}
		else
			pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnZoomPan()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_PAN, NULL);
	}
}

void CMainFrame::OnUpdateZoomPan(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CString strMessage = QGlobal::gf_Str(_T("ID_ZOOM_PAN"), _T("Zoom pan\nZoom pan"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_PAN));
		int nSubCmd;
		CString cmdName = E3_CmdMgrGetCurCmd(E3_GetCmdMgr(), nSubCmd);

		if ( _tcscmp(cmdName, _T("ZOOM")) == 0)
		{ 
			if (nSubCmd == SUBCMD_ZOOM_PAN)
				pCmdUI->SetCheck(TRUE);
			else
				pCmdUI->SetCheck(FALSE);
		}
		else
			pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnZoomIn()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_IN, NULL);
	}
}

void CMainFrame::OnUpdateZoomIn(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CString strMessage = QGlobal::gf_Str(_T("ID_ZOOM_IN"), _T("Zoom in\nZoom in"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);


	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_IN));
	}
}

void CMainFrame::OnZoomAll()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_ALL, NULL);
	}
}

void CMainFrame::OnUpdateZoomAll(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CString strMessage = QGlobal::gf_Str(_T("ID_ZOOM_ALL"), _T("Zoom all object\nZoom all	"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);


	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_ALL));
	}
}

void CMainFrame::OnZoomPick()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_PICK, NULL);
	}
}

void CMainFrame::OnUpdateZoomPick(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CString strMessage = QGlobal::gf_Str(_T("ID_ZOOM_PICK"), _T("Zoom all pick object\nZoom pick"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_PICK));
	}
}

void CMainFrame::OnZoomWorkspace()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_WORKSPACE, NULL);
	}
}

void CMainFrame::OnUpdateZoomWorkspace(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CString strMessage = QGlobal::gf_Str(_T("ID_ZOOM_WORKSPACE"), _T("View whole workspace\nView Workspace"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_WORKSPACE));
	}
}

void CMainFrame::OnZoomOut()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_OUT, NULL);
	}
}

void CMainFrame::OnUpdateZoomOut(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here	
	CString strMessage = QGlobal::gf_Str(_T("ID_ZOOM_OUT"), _T("Zoom out\nZoom out"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_OUT));
	}
}


void CMainFrame::OnTestButton()
{
	CDlgMark* pDlg = gf_GetDlgMark();
	::SendMessage(pDlg->GetSafeHwnd(), WM_USER_CHANGEENTITY_1, 0,0);

		
	
}
void CMainFrame::OnUpdateTestButton(CCmdUI* pCmdUI)
{
	
}
void CMainFrame::OnTestRed()
{
	CDlgMark* pDlg = gf_GetDlgMark();
	::SendMessage(pDlg->GetSafeHwnd(), WM_USER_Red, 0, 0);



}
void CMainFrame::OnUpdateTestRed(CCmdUI* pCmdUI)
{

}

void CMainFrame::OnViewZoom()
{
	// TODO: 在此添加命令处理程序代码
//	if (m_wndZoomlBar.IsWindowVisible())
//		ShowPane(&m_wndZoomlBar, FALSE, FALSE, FALSE);
//	else
//		ShowPane(&m_wndZoomlBar, TRUE, FALSE, FALSE);
}
void CMainFrame::OnUpdateViewZoom(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
//	pCmdUI->SetText(QGlobal::gf_Str(_T("ZOOM"), _T("Zoom")));
//	pCmdUI->Enable();
//	if (m_wndZoomlBar.m_hWnd != NULL)
//		pCmdUI->SetCheck(m_wndZoomlBar.IsVisible());
}

void CMainFrame::OnViewDrawBar()
{
	// TODO: 在此添加命令处理程序代码
#ifdef USE_DRAWTOOL_BAR
	if (m_wndDraw.IsWindowVisible())
		ShowPane(&m_wndDraw, FALSE, FALSE, FALSE);
	else
		ShowPane(&m_wndDraw, TRUE, FALSE, FALSE);
#else
	if (m_wndDrawBar.IsWindowVisible())
		ShowPane(&m_wndDrawBar, FALSE, FALSE, FALSE);
	else
		ShowPane(&m_wndDrawBar, TRUE, FALSE, FALSE);
#endif
}
void CMainFrame::OnUpdateViewDrawBar(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("DRAW"), _T("Draw")));
	pCmdUI->Enable();
#ifdef USE_DRAWTOOL_BAR
	if (m_wndDraw.m_hWnd != NULL)
		pCmdUI->SetCheck(m_wndDraw.IsVisible());
#else
	if (m_wndDrawBar.m_hWnd != NULL)
		pCmdUI->SetCheck(m_wndDrawBar.IsVisible());
#endif
}

void CMainFrame::OnViewAlignBar()
{
	// TODO: 在此添加命令处理程序代码
	if (m_wndAlignBar.IsWindowVisible())
		ShowPane(&m_wndAlignBar, FALSE, FALSE, FALSE);
	else
		ShowPane(&m_wndAlignBar, TRUE, FALSE, FALSE);
}

void CMainFrame::OnUpdateViewAlignBar(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("ALIGN"), _T("Align")));
	pCmdUI->Enable();
	if (m_wndAlignBar.m_hWnd != NULL)
		pCmdUI->SetCheck(m_wndAlignBar.IsVisible());

}


void CMainFrame::OnViewEntList()
{
	// TODO: 在此添加命令处理程序代码
#ifdef ENABLE_ENTLIST 
	if (m_barEntList.IsWindowVisible())
		ShowPane(&m_barEntList, FALSE, FALSE, FALSE);
	else
		ShowPane(&m_barEntList, TRUE, FALSE, FALSE);
#endif
}
void CMainFrame::OnUpdateViewEntList(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_VIEW_ENTLIST"), _T("Entitys list")));
	pCmdUI->Enable();
#ifdef ENABLE_ENTLIST 
	if (m_barEntList.m_hWnd != NULL)
		pCmdUI->SetCheck(m_barEntList.IsVisible());
#endif
}
void CMainFrame::OnViewEntProp()
{
	// TODO: 在此添加命令处理程序代码
#ifdef	ENABLE_ENTLPROP
	if (m_barEntProp.IsWindowVisible())
		ShowPane(&m_barEntProp, FALSE, FALSE, FALSE);
	else
		ShowPane(&m_barEntProp, TRUE, FALSE, FALSE);
#endif
}
void CMainFrame::OnUpdateViewEntProp(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_VIEW_ENTPROP"), _T("Entitys property")));
	pCmdUI->Enable();
#ifdef	ENABLE_ENTLPROP
	if (m_barEntProp.m_hWnd != NULL)
		pCmdUI->SetCheck(m_barEntProp.IsVisible());
#endif
}


void CMainFrame::OnDrawBitmap()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_BMP, 0);
	}
}

void CMainFrame::OnUpdateDrawBitmap(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_DRAW_BMPFILE"), _T("&Bitmap File")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_BMP));

	}
}

void CMainFrame::OnDrawCir()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_CIR, 0);
	}
}

void CMainFrame::OnUpdateDrawCir(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_DRAW_CIRCLE"), _T("&Circle")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_CIR));
		int nSubCmd;
		CString cmdName = E3_CmdMgrGetCurCmd(E3_GetCmdMgr(), nSubCmd);

		if ( _tcscmp(cmdName, _T("DRAW")) == 0 && nSubCmd == SUBCMD_DRAW_CIR)
			pCmdUI->SetCheck(TRUE);
		else
			pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnDrawElp()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_ELP, 0);
	}
}

void CMainFrame::OnUpdateDrawElp(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_DRAW_ELLIPSE"), _T("&Ellipse")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_ELP));
		int nSubCmd;
		CString cmdName = E3_CmdMgrGetCurCmd(E3_GetCmdMgr(), nSubCmd);
		if ( _tcscmp(cmdName, _T("DRAW")) == 0 && nSubCmd == SUBCMD_DRAW_ELP)
			pCmdUI->SetCheck(TRUE);
		else
			pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnDrawInput()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_INPUT, 0);
	}
}

void CMainFrame::OnUpdateDrawInput(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_DRAW_INPUT"), _T("&Input IO")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_INPUT));
	}
}

void CMainFrame::OnDrawLine()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_LINE, 0);
	}
}

void CMainFrame::OnUpdateDrawLine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_DRAW_LINE"), _T("&Line")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_LINE));
		int nSubCmd;
		CString cmdName = E3_CmdMgrGetCurCmd(E3_GetCmdMgr(), nSubCmd);
		if ( _tcscmp(cmdName, _T("DRAW")) == 0 && nSubCmd == SUBCMD_DRAW_LINE)
			pCmdUI->SetCheck(TRUE);
		else
			pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnDrawOutput()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_OUTPUT, 0);
	}
}

void CMainFrame::OnUpdateDrawOutput(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_DRAW_OUTPUT"), _T("&Onput IO")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_OUTPUT));
	}
}

void CMainFrame::OnDrawPline()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_BEZIER, 0);
	}
}

void CMainFrame::OnUpdateDrawPline(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_DRAW_CURVE"), _T("Cu&rve")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_BEZIER));
		int nSubCmd;
		CString cmdName = E3_CmdMgrGetCurCmd(E3_GetCmdMgr(), nSubCmd);

		if ( _tcscmp(cmdName, _T("DRAW")) == 0 && nSubCmd == SUBCMD_DRAW_BEZIER)
			pCmdUI->SetCheck(TRUE);
		else
			pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnDrawPoint()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{

		PMarker pMarker = NULL;
#ifdef ENABLE_MARK
		CDlgMark* pDlg = gf_GetDlgMark();
		if (pDlg != NULL)
		{
			pDlg->LockMarker();
			pMarker = pDlg->GetMarker();
			pDlg->UnLockMarker();
		} 
#endif
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_POINT, (INT_PTR)pMarker);

	}
}

void CMainFrame::OnUpdateDrawPoint(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码	
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_DRAW_POINT"), _T("&Point")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_POINT));
		int nSubCmd;
		CString cmdName = E3_CmdMgrGetCurCmd(E3_GetCmdMgr(), nSubCmd);

		if ( _tcscmp(cmdName, _T("DRAW")) == 0 && nSubCmd == SUBCMD_DRAW_POINT)
			pCmdUI->SetCheck(TRUE);
		else
			pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnDrawPolygon()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_POLYGON, 0);
	}
}

void CMainFrame::OnUpdateDrawPolygon(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_DRAW_POLY"), _T("Poly&gon")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_POLYGON));
		int nSubCmd; 
		CString cmdName = E3_CmdMgrGetCurCmd(E3_GetCmdMgr(), nSubCmd);
		if ( _tcscmp(cmdName, _T("DRAW")) == 0 && nSubCmd == SUBCMD_DRAW_POLYGON)
			pCmdUI->SetCheck(TRUE);
		else
			pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnDrawRect()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_RECT, 0);
	}
}

void CMainFrame::OnUpdateDrawRect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_DRAW_RECT"), _T("&Rect")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_RECT));
		int nSubCmd;
		CString cmdName = E3_CmdMgrGetCurCmd(E3_GetCmdMgr(), nSubCmd);
		if ( _tcscmp(cmdName, _T("DRAW")) == 0 && nSubCmd == SUBCMD_DRAW_RECT)
			pCmdUI->SetCheck(TRUE);
		else
			pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnDrawSpiral()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_SPIRAL, 0);
	}
}

void CMainFrame::OnUpdateDrawSpiral(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("SPIRAL"), _T("Spiral")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_SPIRAL));
	}
}

void CMainFrame::OnDrawText()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_TEXT, 0);
	}
}

void CMainFrame::OnUpdateDrawText(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_DRAW_TEXT"), _T("&Text")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_TEXT));
	}
}

void CMainFrame::OnDrawTime()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_TIMER, 0);
	}
}

void CMainFrame::OnUpdateDrawTime(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_DRAW_TIMER"), _T("Ti&me")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_TIMER));
	}
}

void CMainFrame::OnDrawVectorfile()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_VECTOR, 0);
	}
}

void CMainFrame::OnUpdateDrawVectorfile(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_DRAW_VECTORFILE"), _T("&Vector File")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_VECTOR));
	}
}

void CMainFrame::OnDrawPick()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), 0, 0);
	}
}

void CMainFrame::OnUpdateDrawPick(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("PICK"), _T("Pick")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), 0));
		int nSubCmd;
		CString cmdName = E3_CmdMgrGetCurCmd(E3_GetCmdMgr(), nSubCmd);

		if (  _tcscmp(cmdName, _T("PICK")) == 0)
			pCmdUI->SetCheck(TRUE);
		else
			pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnDrawNode()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("NODE"), 0, 0);
	}
}

void CMainFrame::OnUpdateDrawNode(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("NODE"), _T("Node")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("NODE"), 0));
		int nSubCmd;
		CString cmdName = E3_CmdMgrGetCurCmd(E3_GetCmdMgr(), nSubCmd);

		if (  _tcscmp(cmdName, _T("NODE")) == 0)
			pCmdUI->SetCheck(TRUE);
		else
			pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnDrawBarcode()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_BARCODE, 0);
			
	}
	
}

void CMainFrame::OnDrawBarcode1()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(), _T("DRAW"), SUBCMD_DRAW_BARCODE, 1);

	}
	   
}

void CMainFrame::OnUpdateDrawBarcode(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("BARCODE"), _T("BarCode")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_BARCODE));
	}
}

void CMainFrame::OnUpdateDrawBarcode1(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("BARCODE"), _T("BarCode")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(), _T("DRAW"), SUBCMD_DRAW_BARCODE));
	}
}

void CMainFrame::OnDrawCoor()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_COOR, 0);
	}
}

void CMainFrame::OnUpdateDrawCoor(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_COOR));
	}
}

void CMainFrame::OnDrawClose()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_CLOSE, 0);
	}
}

void CMainFrame::OnUpdateDrawClose(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_CLOSE));
	}
}
void CMainFrame::OnDrawFinish()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_FINISH, 0);
	}
}

void CMainFrame::OnUpdateDrawFinish(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_FINISH));
	}
}
void CMainFrame::OnDrawExtaxis()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_EXTAXIS, 0);
	}
}

void CMainFrame::OnUpdateDrawExtaxis(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_DRAW_EXTAXIS"), _T("E&xtAxis")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_EXTAXIS));
	}
}

void CMainFrame::OnDrawEncoder()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_ENCODER, 0);
	}
}

void CMainFrame::OnUpdateDrawEncoder(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("ENCODERDIST"), _T("Encoder distance")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_ENCODER));
	}
}



void CMainFrame::OnDrawIndex()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_INDEX, 0);
	}
}

void CMainFrame::OnUpdateDrawIndex(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("INDEX"), _T("Index")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_INDEX));
	}
}


void CMainFrame::OnDrawCCD()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_CCD, 0);
	}
}

void CMainFrame::OnUpdateDrawCCD(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("CCD"), _T("CCD")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_CCD));
	}
}
void CMainFrame::OnDrawInputJump()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_INPUTJUMP, 0);
	}
}

void CMainFrame::OnUpdateDrawInputJump(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("INPUTJUMP"), _T("Input jump")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DRAW"), SUBCMD_DRAW_INPUTJUMP));
	}
}

void CMainFrame::OnCmdPickAll()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_ALL, 0);
	}
}

void CMainFrame::OnUpdateCmdPickAll(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_PICKALL"), _T("Pick All"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_ALL));
	}
}
void CMainFrame::OnCmdPickInvert()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_INVERSE, 0);
	}
}

void CMainFrame::OnUpdateCmdPickInvert(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_PICKINVERT"), _T("Pick Invert"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_INVERSE));
	}
}
void CMainFrame::OnCmdPickDel()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_DEL, 0);
	}
}

void CMainFrame::OnUpdateCmdPickDel(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_PICKDEL"), _T("Pick Delete"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_DEL));
	}
}

void CMainFrame::OnCmdPickLock()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_LOCK, 0);
	}
}

void CMainFrame::OnUpdateCmdPickLock(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_PICKLOCK"), _T("Pick Lock"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_LOCK));
	}
}

void CMainFrame::OnCmdPickUnLock()
{
	// TODO: 在此添加命令处理程序代码

	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_UNLOCK, 0);
	}
}

void CMainFrame::OnUpdateCmdPickUnLock(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_PICKUNLOCK"), _T("Pick UnLock"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_UNLOCK));
	}
}

void CMainFrame::OnCmdPickUnLockAll()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_UNLOCKALL, 0);
	}
}

void CMainFrame::OnUpdateCmdPickUnLockAll(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_PICKUNLOCKALL"), _T("Pick UnLock All"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_UNLOCKALL));
	}
}
void CMainFrame::OnCmdPickCen()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_CENTER, 0);
	}
}

void CMainFrame::OnUpdateCmdPickCen(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_PICKCEN"), _T("Pick To Center"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_CENTER));
	}
}
void CMainFrame::OnCmdPickCenX()
{
	// TODO: 在此添加命令处理程序代码



	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_CENTER_X, 0);
	}
}

void CMainFrame::OnUpdateCmdPickCenX(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_PICKCENX"), _T("Pick To Center x"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_CENTER_X));
	}
}
void CMainFrame::OnCmdPickCenY()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_CENTER_Y, 0);
	}
}

void CMainFrame::OnUpdateCmdPickCenY(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_PICKCENY"), _T("Pick To Center Y"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_CENTER_Y));
	}
}
void CMainFrame::OnCmdPickMirrorX()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_MIRRORX, 0);
	}
}

void CMainFrame::OnUpdateCmdPickMirrorX(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_PICKMIRRORX"), _T("X Mirror"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_MIRRORX));
	}
}
void CMainFrame::OnCmdPickMirrorY()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_MIRRORY, 0);
	}
}

void CMainFrame::OnUpdateCmdPickMirrorY(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_PICKMIRRORY"), _T("Y Mirror"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_MIRRORY));
	}
}
void CMainFrame::OnDeviceParam()
{
#ifdef ENABLE_MARK
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		return;
	}
	pDlg->LockMarker();
	PMarker pMarker = pDlg->GetMarker();

	if (E3_MarkerIsDeviceValid(pMarker))
	{
		pDlg->UnLockMarker();
		pDlg->OnBnClickedButtonF3();
	}
	else
	{
		pDlg->UnLockMarker();
	}
#endif
}

void CMainFrame::OnUpdateDeviceParam(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_FILE_MACHINE"), _T("Machine parameter..")));
#ifdef ENABLE_MARK
	CDlgMark* pDlg = gf_GetDlgMark();
	if (pDlg == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	pDlg->LockMarker();
	PMarker pMarker = pDlg->GetMarker();

	if (E3_MarkerIsDeviceValid(pMarker))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	pDlg->UnLockMarker();
#endif
}



void CMainFrame::OnFileSystem()
{
	// TODO: 在此添加命令处理程序代码
 	E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), 0, 0);

	if (E3_GetCmdMgr() == NULL)
	{
		return;
	}

	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM == NULL)
	{
		return;
	}

	CSysParam* pSysParam = gf_GetSysParam();
	if (pSysParam != NULL)
	{
		CSysParam* pTemp = new CSysParam();
		memcpy(pTemp, pSysParam, sizeof(CSysParam));
		CDlgSystemParam dlg(this);
		dlg.m_pParam = pTemp;
		if (dlg.DoModal() == IDOK)
		{
			int nOldUnitType = pSysParam->GetParamInt(INT_PARAM_UNITTYPE);
			memcpy(pSysParam, pTemp, sizeof(CSysParam));
			if (nOldUnitType != pSysParam->GetParamInt(INT_PARAM_UNITTYPE))
			{
				double dScale = 1.0;
				if (pSysParam->GetParamInt(INT_PARAM_UNITTYPE) == UNIT_MM)
					dScale = 25.4;
				else
					dScale = 1 / 25.4;
				pSysParam->ChangeLengthUnit(dScale);

				E3_EntMgrOnChangeUnit(pEM, pSysParam, dScale);


				E3_CmdMgrOnMessage(E3_GetCmdMgr(),CM_NOTIFY_UNITCHANGE, 0, 0);
			}
			E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_WORKSPACE, 0);

#ifdef ENABLE_PENBOX
			m_barPenBox.m_wndPenbox.SendMessage(WM_USER_PICKCHANGE,0,0);
#endif

			gf_SaveSysParamFile();
		}
		delete pTemp;
		pTemp = NULL;
	} 
}

void CMainFrame::OnUpdateFileSystem(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码	
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_FILE_SYSTEM"), _T("System parameter..")));

	if (E3_GetCmdMgr() != NULL)
	{
		if (!gf_GetUserMgr()->GetCurUser()->IsAdmin() && !gf_GetUserMgr()->GetCurUser()->m_bEnableModifySysParam)
		{
			pCmdUI->Enable(FALSE);
		}
		else
		{
			pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), 0));
		}
	}
}
 
void CMainFrame::OnFileProjectParam()
{ 
#ifdef ENABLE_MARK
	if (gf_DlgOnFileProjectParam(m_wndMark.m_dlgMark.GetMarker()) == IDOK)
	{
		m_wndMark.m_dlgMark.UpdateDevState();
	}
#endif
}

void CMainFrame::OnUpdateFileProjectParam(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码	
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_FILE_PROJECTPARAM"), _T("Project parameter"))+_T("..."));
#ifdef ENABLE_MARK
	if (E3_GetCmdMgr() != NULL)
	{
		if (!gf_GetUserMgr()->GetCurUser()->IsAdmin() && !gf_GetUserMgr()->GetCurUser()->m_bEnableModifySysParam)
		{
			pCmdUI->Enable(FALSE);
		}
		else
		{
			pCmdUI->Enable(TRUE);
		}
	}
#endif
}



void CMainFrame::OnEditHatch()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("HATCH"), 0, 0);
	}
}

void CMainFrame::OnUpdateEditHatch(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("HATCH"), _T("Hatch...")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("HATCH"), 0));
	}
}


void CMainFrame::OnViewZoom3d()
{
	// TODO: 在此添加命令处理程序代码
	if (m_wndZooml3dBar.IsWindowVisible())
	{
		ShowPane(&m_wndZooml3dBar, FALSE, FALSE, FALSE);
	}
	else
	{
		ShowPane(&m_wndZooml3dBar, TRUE, FALSE, FALSE);
		RemoveSpacingOfToolBar();
	}
}
void CMainFrame::OnUpdateViewZoom3d(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("ZOOM"), _T("Zoom")) + _T("3D"));

	if (!E3_IsLicenceEnable3D())
	{ //没有3d模式
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable();
	}
	if (m_wndZooml3dBar.m_hWnd != NULL)
		pCmdUI->SetCheck(m_wndZooml3dBar.IsVisible());
}



void CMainFrame::OnViewMarkParam()
{
	// TODO: 在此添加命令处理程序代码
#ifdef ENABLE_PENBOX
	if (m_barPenBox.IsWindowVisible())
		ShowPane(&m_barPenBox, FALSE, FALSE, FALSE);
	else
		ShowPane(&m_barPenBox, TRUE, FALSE, FALSE);
#endif
}
void CMainFrame::OnUpdateViewMarkParam(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("PENBOX"), _T("Penbox")));
	pCmdUI->Enable();
#ifdef ENABLE_PENBOX
	if (m_barPenBox.m_hWnd != NULL)
		pCmdUI->SetCheck(m_barPenBox.IsVisible());
#endif
}
void CMainFrame::OnViewMarkPanel()
{
	// TODO: 在此添加命令处理程序代码
#ifdef ENABLE_MARK
	if (m_wndMark.IsWindowVisible())
		ShowPane(&m_wndMark, FALSE, FALSE, FALSE);
	else
		ShowPane(&m_wndMark, TRUE, FALSE, FALSE);
#endif
}
void CMainFrame::OnUpdateViewMarkPanel(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("MARK"), _T("Mark")));
	pCmdUI->Enable();
#ifdef ENABLE_MARK
	if (m_wndMark.m_hWnd != NULL)
		pCmdUI->SetCheck(m_wndMark.IsVisible());
#endif
}


void CMainFrame::OnViewLaserMonitor()
{
	// TODO: 在此添加命令处理程序代码
 
	if (m_panelLaserMonitor.IsWindowVisible())
		ShowPane(&m_panelLaserMonitor, FALSE, FALSE, FALSE);
	else
		ShowPane(&m_panelLaserMonitor, TRUE, FALSE, FALSE);
 
}
void CMainFrame::OnUpdateViewLaserMonitor(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(QGlobal::gf_Str(_T("LASERMONITOR"), _T("Laser monitor")));
	pCmdUI->Enable();  
	pCmdUI->SetCheck(m_panelLaserMonitor.IsVisible());
}

void CMainFrame::OnZoom3d()
{
	if (E3_IsLicenceEnable3D())
	{
		if (E3_GetCmdMgr() != NULL)
		{
			E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_RUN, NULL);
		}
	}
}
void CMainFrame::OnUpdateZoom3d(CCmdUI* pCmdUI)
{
	CString strMessage = QGlobal::gf_Str(_T("ID_VIEW_3D"), _T("View 3d & 2d\nView 3d & 2d"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_RUN));

		pCmdUI->SetCheck(FALSE);
	}
}
void CMainFrame::OnZoom3dUp()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_UP, NULL);
	}
}
void CMainFrame::OnUpdateZoom3dUp(CCmdUI* pCmdUI)
{
	CString strMessage = QGlobal::gf_Str(_T("ID_VIEW_3DUP"), _T("Up view\nView from up"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_UP));
		pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnZoom3dDown()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_DOWN, NULL);
	}
}
void CMainFrame::OnUpdateZoom3dDown(CCmdUI* pCmdUI)
{
	CString strMessage = QGlobal::gf_Str(_T("ID_VIEW_3DDOWN"), _T("Down view\nView from down"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_DOWN));
		pCmdUI->SetCheck(FALSE);
	}
}
void CMainFrame::OnZoom3dLeft()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_LEFT, NULL);
	}
}
void CMainFrame::OnUpdateZoom3dLeft(CCmdUI* pCmdUI)
{
	CString strMessage = QGlobal::gf_Str(_T("ID_VIEW_3DLEFT"), _T("Left view\nView from left"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_LEFT));
		pCmdUI->SetCheck(FALSE);
	}
}
void CMainFrame::OnZoom3dRight()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_RIGHT, NULL);
	}
}
void CMainFrame::OnUpdateZoom3dRight(CCmdUI* pCmdUI)
{
	CString strMessage = QGlobal::gf_Str(_T("ID_VIEW_3DRIGHT"), _T("Right view\nView from right"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_RIGHT));
		pCmdUI->SetCheck(FALSE);
	}
}
void CMainFrame::OnZoom3dFront()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_FRONT, NULL);
	}
}
void CMainFrame::OnUpdateZoom3dFront(CCmdUI* pCmdUI)
{
	CString strMessage = QGlobal::gf_Str(_T("ID_VIEW_3DFRONT"), _T("Front view\nView from front"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_FRONT));
		pCmdUI->SetCheck(FALSE);
	}
}
void CMainFrame::OnZoom3dBack()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_BACK, NULL);
	}
}
void CMainFrame::OnUpdateZoom3dBack(CCmdUI* pCmdUI)
{
	CString strMessage = QGlobal::gf_Str(_T("ID_VIEW_3DBACK"), _T("Back view\nView from back"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_BACK));
		pCmdUI->SetCheck(FALSE);
	}
}
void CMainFrame::OnZoom3dIso()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_ISO, NULL);
	}
}
void CMainFrame::OnUpdateZoom3dIso(CCmdUI* pCmdUI)
{
	CString strMessage = QGlobal::gf_Str(_T("ID_VIEW_3DISO"), _T("Iso view\nView from iso"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_ISO));
		pCmdUI->SetCheck(FALSE);
	}
}
void CMainFrame::OnDrawMesh3d()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_MESH3D, NULL);
	}
}
void CMainFrame::OnUpdateDrawMesh3d(CCmdUI* pCmdUI)
{
	//pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_DRAW_MESH3D"),_T("&Mesh 3d")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_MESH3D));
	}
}

void CMainFrame::OnFun3dSlice()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_SLICE3D, NULL);
	}
}
void CMainFrame::OnUpdateFun3dSlice(CCmdUI* pCmdUI)
{
	pCmdUI->SetText(QGlobal::gf_Str(_T("SLICEFILE"), _T("Slc file")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_SLICE3D));
	}
}

void CMainFrame::OnFun3dSliceMesh()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_SLICEMESH, NULL);
	}
}
void CMainFrame::OnUpdateFun3dSliceMesh(CCmdUI* pCmdUI)
{
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_3DFUN_SLICEMESH"), _T("Slice Mesh")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_SLICEMESH));
	}
}

void CMainFrame::OnFun3dRotateMesh()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_ROTATEMESH, NULL);
	}
}
void CMainFrame::OnUpdateFun3dRotateMesh(CCmdUI* pCmdUI)
{
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_3DFUN_ROTATEMESH"), _T("Rotate Mesh")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_ROTATEMESH));
	}
}


void CMainFrame::OnFun3dMoveMesh()
{
	
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_MOVEMESH, NULL);
	}
}
void CMainFrame::OnUpdateFun3dMoveMesh(CCmdUI* pCmdUI)
{
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_3DFUN_MOVEMESH"), _T("Move Mesh")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_MOVEMESH));
	}
}

void CMainFrame::On3DViewWire()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_WIRE, NULL);
	}
}
void CMainFrame::OnUpdate3DViewWire(CCmdUI* pCmdUI)
{
	//pCmdUI->SetText(QGlobal::gf_Str(_T("VIEWWIRE"), _T("View wire")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_WIRE));
	}
}
void CMainFrame::On3DViewRender()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_RENDER, NULL);
	}
}
void CMainFrame::OnUpdate3DViewRender(CCmdUI* pCmdUI)
{
	//pCmdUI->SetText(QGlobal::gf_Str(_T("VIEWRENDER"), _T("View render")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_RENDER));
	}
}
void CMainFrame::On3DViewRenderLine()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_RENDERLINE, NULL);
	}
}
void CMainFrame::OnUpdate3DViewRenderLine(CCmdUI* pCmdUI)
{
//	pCmdUI->SetText(QGlobal::gf_Str(_T("VIEWRENDERLINES"), _T("View render lines")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_RENDERLINE));
	}
}

void CMainFrame::On3DViewHideMesh()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_HIDEMESH, NULL);
	}
}
void CMainFrame::OnUpdate3DViewHideMesh(CCmdUI* pCmdUI)
{
	//pCmdUI->SetText(QGlobal::gf_Str(_T("HIDEMESH"),_T("Hide mesh")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ZOOM"), SUBCMD_ZOOM_3D_HIDEMESH));
	}
}


void CMainFrame::OnFun3dPrj()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_PRJ, NULL);
	}
}
void CMainFrame::OnUpdateFun3dPrj(CCmdUI* pCmdUI)
{
	//pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_3DFUN_PROJECT"),_T("Project")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_PRJ));
	}
}
void CMainFrame::OnFun3dFreePaint()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_FREEPAINT, NULL);
		 
	}
}

void CMainFrame::OnUpdateFun3dFreePaint(CCmdUI* pCmdUI)
{
 	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_FREEPAINT));
	}
}
void CMainFrame::OnFun3dBasicShape()
{
	if (E3_GetCmdMgr() != NULL)
	{
		  
		 E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_BASICSHAPE, NULL);
	}
}
void CMainFrame::OnUpdateFun3dBasicShape(CCmdUI* pCmdUI)
{ 
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_BASICSHAPE));
	}
}
void CMainFrame::OnFun3dBmpToMesh()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_BMPTOMESH, NULL);
	}
}
void CMainFrame::OnUpdateFun3dBmpToMesh(CCmdUI* pCmdUI)
{
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_BMPTOMESH));
	}
}


LRESULT CMainFrame::OnUserRunNode(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)
	{
	//	this->ShowPane(&m_wndPickCmdBar, FALSE, FALSE, FALSE);
		this->ShowPane(&m_wndNodeCmdBar, TRUE, FALSE, TRUE);
	}
	else
	{
		this->ShowPane(&m_wndNodeCmdBar, FALSE, FALSE, FALSE);
	//	this->ShowPane(&m_wndPickCmdBar, TRUE, FALSE, TRUE);
	}
	return 0;
}
LRESULT CMainFrame::OnUserRun3DView(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)
	{
		this->ShowPane(&m_wnd3dFunBar, TRUE, FALSE, TRUE);
		this->ShowPane(&m_wndZooml3dBar, TRUE, FALSE, TRUE);
		RemoveSpacingOfToolBar();
	}
	else
	{
		this->ShowPane(&m_wnd3dFunBar, FALSE, FALSE, FALSE);
		this->ShowPane(&m_wndZooml3dBar, FALSE, FALSE, FALSE);
	}
	return 0;
}

LRESULT CMainFrame::OnUserChangeStatusText(WPARAM wParam, LPARAM lParam)
{
	m_wndStatusBar.SetPaneText((int)wParam, E3_CmdMgrGetStatusPanelText(E3_GetCmdMgr(), (int)wParam));
	return 0;
}


void CMainFrame::OnModifyArray()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_ARRAY, NULL);
	}
}

void CMainFrame::OnUpdateModifyArray(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetText(QGlobal::gf_Str(_T("ARRAY"), _T("Array")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_ARRAY));
	}
}

void CMainFrame::OnModifyResort()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(), _T("RESORT"), SUBCMD_RESORT_1, NULL);
	}
}

void CMainFrame::OnUpdateModifyResort(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetText(QGlobal::gf_Str(_T("RESORT"), _T("Resort")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(), _T("RESORT"), SUBCMD_RESORT_1));
	}
}
void CMainFrame::OnModifyRotate()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_ROTATEENT, NULL);
	}
}

void CMainFrame::OnUpdateModifyRotate(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetText(QGlobal::gf_Str(_T("ROTATE"), _T("Rotate")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_ROTATEENT));
	}
}

void CMainFrame::OnArrayText()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ARRAYTEXT"), SUBCMD_MODIFY_ARRAY, NULL);
	}
}
void CMainFrame::OnUpdateArrayText(CCmdUI *pCmdUI)
{
	CString strMessage = QGlobal::gf_Str(_T("ARRAYTEXT"), _T("Array text"));
	pCmdUI->SetText(strMessage);
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ARRAYTEXT"), 0));
	}
}


void CMainFrame::OnOffsetCurve()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("OFFSET"), 0, NULL);
	}
}
void CMainFrame::OnUpdateOffsetCurve(CCmdUI *pCmdUI)
{
	 CString strMessage = QGlobal::gf_Str(_T("OFFSET"), _T("Offset"));
	pCmdUI->SetText(strMessage);
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("OFFSET"), 0));
	}
}


void CMainFrame::OnCmdToCurve()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("MODIFY"), SUBCMD_MODIFY_TOCURVE, NULL);
	}
}
void CMainFrame::OnUpdateCmdToCurve(CCmdUI *pCmdUI)
{
	CString strMessage = QGlobal::gf_Str(_T("TOCURVE"), _T("To curve"));
	pCmdUI->SetText(strMessage);
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("MODIFY"), SUBCMD_MODIFY_TOCURVE));
	}
}

void CMainFrame::OnUpdateAbout(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_ABOUT"), _T("About")));
}

void CMainFrame::OnViewSnapGrid()
{
	gf_GetSysParam()->SetParamInt(INT_PARAM_SNAPGRID, !gf_GetSysParam()->GetParamInt(INT_PARAM_SNAPGRID));

	ShowSnapStr();
}
void CMainFrame::OnUpdateViewSnapGrid(CCmdUI *pCmdUI)
{
	CString	strMessage = QGlobal::gf_Str(_T("MENU_VIEW_SNAPGRID"), _T("Snap G&rid\tF7"));
	pCmdUI->SetText(strMessage);
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(gf_GetSysParam()->GetParamInt(INT_PARAM_SNAPGRID));
}

void CMainFrame::OnViewSnapGL()
{
	gf_GetSysParam()->SetParamInt(INT_PARAM_SNAPGUILDLIINE, !gf_GetSysParam()->GetParamInt(INT_PARAM_SNAPGUILDLIINE));

	ShowSnapStr();
}
void CMainFrame::OnUpdateViewSnapGL(CCmdUI *pCmdUI)
{
	CString strMessage = QGlobal::gf_Str(_T("MENU_VIEW_SNAPGUILD"), _T("Snap &Guild Line\tF8"));
	pCmdUI->SetText(strMessage);
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(gf_GetSysParam()->GetParamInt(INT_PARAM_SNAPGUILDLIINE));
}


void CMainFrame::OnViewSnapObject()
{
	// TODO: Add your command handler code here
	gf_GetSysParam()->SetParamInt(INT_PARAM_SNAPENTITY, !gf_GetSysParam()->GetParamInt(INT_PARAM_SNAPENTITY));

	ShowSnapStr();
}
void CMainFrame::OnUpdateViewSnapObject(CCmdUI *pCmdUI)
{
	CString strMessage = QGlobal::gf_Str(_T("MENU_VIEW_SNAPOBJECT"), _T("Snap &Entity\tF9"));
	pCmdUI->SetText(strMessage);
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(gf_GetSysParam()->GetParamInt(INT_PARAM_SNAPENTITY));
}

void CMainFrame::OnViewSnapMeshVertex()
{
	// TODO: Add your command handler code here
	gf_GetSysParam()->SetParamInt(INT_PARAM_SNAPMESHVERTEX, !gf_GetSysParam()->GetParamInt(INT_PARAM_SNAPMESHVERTEX));
	//ShowSnapStr();
}

void CMainFrame::OnUpdateViewSnapMeshVertex(CCmdUI *pCmdUI)
{
	CString strMessage = QGlobal::gf_Str(_T("ID_SNAP_MESHVERTEX"), _T(" Snap mesh vertex\nSnap mesh vertex"));
	int n = strMessage.Find(_T('\n'));
	if (n > 0)
	{
		strMessage = strMessage.Left(n);
	}
	pCmdUI->SetText(strMessage);
 

	pCmdUI->Enable(TRUE);
 	pCmdUI->SetCheck(gf_GetSysParam()->GetParamInt(INT_PARAM_SNAPMESHVERTEX));
}


void CMainFrame::OnViewShowRuler()
{
	gf_GetSysParam()->SetParamInt(INT_PARAM_SHOWRULER, !gf_GetSysParam()->GetParamInt(INT_PARAM_SHOWRULER));
	CEzcad3View* pEzcad3View = gf_GetCurEzcad3View();
	if (pEzcad3View != NULL && E3_GetCmdMgr() != NULL)
	{
		for (int i = 0; i<pEzcad3View->GetViewCount(); i++)
		{
			CView* pView = pEzcad3View->GetView(i);
			((CQEntView*)pView)->ShowRuler(gf_GetSysParam()->GetParamInt(INT_PARAM_SHOWRULER));
		}
		pEzcad3View->GetActiveView()->Invalidate();
	}

}
void CMainFrame::OnUpdateViewShowRuler(CCmdUI *pCmdUI)
{
	CString strMessage = QGlobal::gf_Str(_T("MENU_VIEW_RULER"), _T("Show ruler"));
	pCmdUI->SetText(strMessage);
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(gf_GetSysParam()->GetParamInt(INT_PARAM_SHOWRULER));
}


void CMainFrame::OnViewShowGrid()
{
	// TODO: Add your command handler code here
	gf_GetSysParam()->SetParamInt(INT_PARAM_SHOWGRID, !gf_GetSysParam()->GetParamInt(INT_PARAM_SHOWGRID));
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrDraw(E3_GetCmdMgr(), TRUE);
	}

}
void CMainFrame::OnUpdateViewShowGrid(CCmdUI *pCmdUI)
{
	CString strMessage = QGlobal::gf_Str(_T("MENU_VIEW_GRID"), _T("Show grid"));
	pCmdUI->SetText(strMessage);
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(gf_GetSysParam()->GetParamInt(INT_PARAM_SHOWGRID));
}



void CMainFrame::ShowSnapStr()
{
	if (E3_GetCmdMgr() == NULL)
	{
		return;
	}

	CString str;
	if (gf_GetSysParam()->GetParamInt(INT_PARAM_SNAPENTITY))
	{
		str = _T("F9") + QGlobal::gf_Str(_T("OBJECT"), _T("Object")) + _T(":") + QGlobal::gf_Str(_T("ON"), _T("On"));
	}
	else
	{
		str = _T("F9") + QGlobal::gf_Str(_T("OBJECT"), _T("Object")) + _T(":") + QGlobal::gf_Str(_T("OFF"), _T("Off"));
	}
	E3_CmdMgrShowSnapObject(E3_GetCmdMgr(),str);


	if (gf_GetSysParam()->GetParamInt(INT_PARAM_SNAPGUILDLIINE))
	{
		str = _T("F8") + QGlobal::gf_Str(_T("GUIDELINE"), _T("Guildline")) + _T(":") + QGlobal::gf_Str(_T("ON"), _T("On"));
	}
	else
	{
		str = _T("F8") + QGlobal::gf_Str(_T("GUIDELINE"), _T("Guildline")) + _T(":") + QGlobal::gf_Str(_T("OFF"), _T("Off"));
	}
	E3_CmdMgrShowSnapGuildLine(E3_GetCmdMgr(),str);


	if (gf_GetSysParam()->GetParamInt(INT_PARAM_SNAPGRID))
	{
		str = _T("F7") + QGlobal::gf_Str(_T("GRID"), _T("Snap Grid")) + _T(":") + QGlobal::gf_Str(_T("ON"), _T("On"));
	}
	else
	{
		str = _T("F7") + QGlobal::gf_Str(_T("GRID"), _T("Snap Grid")) + _T(":") + QGlobal::gf_Str(_T("OFF"), _T("Off"));
	}
	E3_CmdMgrShowSnapGrid(E3_GetCmdMgr(),str);

}




void CMainFrame::OnCmdNodeAdd()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_ADD, 0);
	}
}

void CMainFrame::OnUpdateCmdNodeAdd(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码 
	CString strMessage = QGlobal::gf_Str(_T("TT_NODE_ADD"), _T("Node add"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_ADD));
	}
}

void CMainFrame::OnCmdNodeAlign()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_ALIGN, 0);
	}
}

void CMainFrame::OnUpdateCmdNodeAlign(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_NODE_ALIGN"), _T("Node Align"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_ALIGN));
	}
}

void CMainFrame::OnCmdNodeClose()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_CLOSE, 0);
	}
}

void CMainFrame::OnUpdateCmdNodeClose(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_NODE_CLOSE"), _T("Node Close"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_CLOSE));
	}
}

void CMainFrame::OnCmdNodeDel()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_DEL, 0);
	}
}

void CMainFrame::OnUpdateCmdNodeDel(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_NODE_DEL"), _T("Node Delete"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_DEL));
	}

}


void CMainFrame::OnCmdNodeSepa()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_SEPARATE, 0);
	}
}

void CMainFrame::OnUpdateCmdNodeSepa(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_NODE_SEPARATE"), _T("Node Separate"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_SEPARATE));
	}
}

void CMainFrame::OnCmdNodeSharp()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_SHARP, 0);
	}
}

void CMainFrame::OnUpdateCmdNodeSharp(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_NODE_SHARP"), _T("Node Sharp"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);


	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_SHARP));
	}
}

void CMainFrame::OnCmdNodeSmooth()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_SMOOTH, 0);
	}
}

void CMainFrame::OnUpdateCmdNodeSmooth(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_NODE_SMOOTH"), _T("Node Smooth"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_SMOOTH));
	}
}

void CMainFrame::OnCmdNodeToarc()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_TOARC, 0);
	}
}

void CMainFrame::OnUpdateCmdNodeToarc(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_NODE_ARC"), _T("To Arc"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_TOARC));
	}
}

void CMainFrame::OnCmdNodeTobez()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_TOBEZ, 0);
	}
}

void CMainFrame::OnUpdateCmdNodeTobez(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_NODE_BEZIER"), _T("To Bezier"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_TOBEZ));
	}
}

void CMainFrame::OnCmdNodeToline()
{
	// TODO: 在此添加命令处理程序代码


	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_TOLINE, 0);
	}
}

void CMainFrame::OnUpdateCmdNodeToline(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_NODE_LINE"), _T("To Line"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_TOLINE));
	}
}

void CMainFrame::OnCmdNodeUnite()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_UNITE, 0);
	}
}

void CMainFrame::OnUpdateCmdNodeUnite(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_NODE_UNITE"), _T("Node Unite"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_UNITE));
	}
}
void CMainFrame::OnCmdNodeDir()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_DIR, 0);
	}
}
void CMainFrame::OnUpdateCmdNodeDir(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_NODE_DIR"), _T("Node Dir"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_DIR));
	}
}
void CMainFrame::OnCmdNodeSys()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_SYS, 0);
	}
}
void CMainFrame::OnUpdateCmdNodeSys(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CString strMessage = QGlobal::gf_Str(_T("TT_NODE_SYSMETRIC"), _T("Node Sysmetric"));
	AfxExtractSubString(strMessage, strMessage, 0, _T('\n'));
	pCmdUI->SetText(strMessage);

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("NODE"), SUBCMD_NODE_SYS));
	}
}
void CMainFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	KillTimer(SAVETIMER);


	PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
	if (pEM != NULL && E3_EntMgrGetModifyFlag(pEM))
	{
		if (gf_GetCurEzcad3View() != NULL)
		{
			CDocument* pDoc = gf_GetCurEzcad3View()->GetDocument();
			if (pDoc != NULL)
			{
				pDoc->SetModifiedFlag(TRUE);
			}
		}
	}
	CFrameWndEx::OnClose();
}

void CMainFrame::OnCmdLaserProcess()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{		 
		if (gf_GetUserMgr()->GetCurUser()->m_bEnableMark)
		{
#ifdef ENABLE_MARK
			CMainFrame* pMainFrame = (CMainFrame*)gf_GetMainFrame();
			if (pMainFrame->m_wndMark.m_dlgMark.GetMarker() != NULL)
			{
				if (E3_MarkerIsDeviceValid(pMainFrame->m_wndMark.m_dlgMark.GetMarker()))
				{
					PMarker pMarker = pMainFrame->m_wndMark.m_dlgMark.GetMarker();

					E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("MATERIALPROCESS"), 0, (INT_PTR)pMarker);
				}
			}
#endif
		}

#ifdef  ENABLE_PENBOX	

		if ( m_barPenBox.m_wndPenbox.m_nCurPenIndex == 0)
			
		{
			m_barPenBox.m_wndPenbox.ShowCurPenParam(0);
		}
#endif
	}
}
void CMainFrame::OnUpdateCmdLaserProcess(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
 
	pCmdUI->SetText(QGlobal::gf_Str(_T("MATERIALPARAMASSIS"), _T("Material parameter assistant")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("MATERIALPROCESS"), 0));
	}
}

void CMainFrame::OnCmdDistortionWeld()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DISTORTION"), SUBCMD_WELD, 0);
	}
}
void CMainFrame::OnUpdateCmdDistortionWeld(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码

	pCmdUI->SetText(QGlobal::gf_Str(_T("WELD"), _T("Weld")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DISTORTION"), SUBCMD_WELD));
	}
}


void CMainFrame::OnCmdDistortionTrim()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DISTORTION"), SUBCMD_TRIM, 0);
	}
}
void CMainFrame::OnUpdateCmdDistortionTrim(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码

	pCmdUI->SetText(QGlobal::gf_Str(_T("TRIM"), _T("Trim")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DISTORTION"), SUBCMD_TRIM));
	}
}

void CMainFrame::OnCmdDistortionInter()
{
	// TODO: 在此添加命令处理程序代码
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("DISTORTION"), SUBCMD_INTER, 0);
	}
}
void CMainFrame::OnUpdateCmdDistortionInter(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码

	pCmdUI->SetText(QGlobal::gf_Str(_T("INTERSECT"), _T("Intersect")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("DISTORTION"), SUBCMD_INTER));
	}
}


void CMainFrame::OnAlignLeft()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ALIGN"), SUBCMD_ALIGN_LEFT, NULL);
	}
}

void CMainFrame::OnUpdateAlignLeft(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_ALIGN_LEFT"), _T("Algin Left")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ALIGN"), SUBCMD_ALIGN_LEFT));
	}
}

void CMainFrame::OnAlignHCenter()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ALIGN"), SUBCMD_ALIGN_HCEN, NULL);
	}
}

void CMainFrame::OnUpdateAlignHCenter(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_ALIGN_CENTER_HOR"), _T("Algin center H")));
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ALIGN"), SUBCMD_ALIGN_HCEN));
	}
}

void CMainFrame::OnAlignRight()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ALIGN"), SUBCMD_ALIGN_RIGHT, NULL);
	}
}

void CMainFrame::OnUpdateAlignRight(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_ALIGN_RIGHT"), _T("Algin right")));

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ALIGN"), SUBCMD_ALIGN_RIGHT));
	}
}



void CMainFrame::OnAlignTop()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ALIGN"), SUBCMD_ALIGN_TOP, NULL);
	}
}

void CMainFrame::OnUpdateAlignTop(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_ALIGN_TOP"), _T("Algin top")));

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ALIGN"), SUBCMD_ALIGN_TOP));
	}
}

void CMainFrame::OnAlignVCenter()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ALIGN"), SUBCMD_ALIGN_VCEN, NULL);
	}
}

void CMainFrame::OnUpdateAlignVCenter(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_ALIGN_CENTER_VER"), _T("Algin center V")));

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ALIGN"), SUBCMD_ALIGN_VCEN));
	}
}

void CMainFrame::OnAlignBottom()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ALIGN"), SUBCMD_ALIGN_BOTTOM, NULL);
	}
}

void CMainFrame::OnUpdateAlignBottom(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_ALIGN_BOTTOM"), _T("Algin bottom")));

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ALIGN"), SUBCMD_ALIGN_BOTTOM));
	}
}

void CMainFrame::OnAlignCenter()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("ALIGN"), SUBCMD_ALIGN_CEN, NULL);
	}
}

void CMainFrame::OnUpdateAlignCenter(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_ALIGN_CENTER"), _T("Algin center")));

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("ALIGN"), SUBCMD_ALIGN_CEN));
	}
}
void CMainFrame::OnCmdPickByPen()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_BYPEN, NULL);
	}
}

void CMainFrame::OnUpdateCmdPickByPen(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetText(QGlobal::gf_Str(_T("PICK_PEN"), _T("Pick by pen")));

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("PICK"), SUBCMD_PICK_BYPEN));
	}
} 

void CMainFrame::OnTrim()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("TRIM"), 0, NULL);
	}
}
void CMainFrame::OnUpdateTrim(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetText(QGlobal::QGlobal::gf_Str(_T("TRIM"), _T("Trim")));

	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("TRIM"), 0));
	}
}



void CMainFrame::OnModifyCurveConnect()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("CURVEEDIT"), SUBCMD_AUTOCONNECT, NULL);
	}
}

void CMainFrame::OnUpdateModifyCurveConnect(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->SetText(QGlobal::gf_Str(_T("MENU_AUTOCONNECT"), _T("Auto connect")));

		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("CURVEEDIT"), SUBCMD_AUTOCONNECT));
	}
}

void CMainFrame::OnModifyBreakCross()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("CURVEEDIT"), SUBCMD_BREAKCROSS, NULL);
	}
}

void CMainFrame::OnUpdateModifyBreakCross(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->SetText(QGlobal::gf_Str(_T("BREAKCROSSPOINT"), _T("Break cross point")));

		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("CURVEEDIT"), SUBCMD_BREAKCROSS));
	}
}


void CMainFrame::OnModifyMeshMergeCloseVertex()
{
	// TODO: Add your command handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_MERGECLOSEVTX, NULL);
	}
}

void CMainFrame::OnUpdateModifyMeshMergeCloseVertex(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->SetText(QGlobal::gf_Str(_T("MERGECLOSEVERTICES"), _T("Merge close vertices")));

		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(),_T("FUN3D"), SUBCMD_3DFUN_MERGECLOSEVTX));
	}
}

void CMainFrame::OnSortByX()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(), _T("RESORT"), SUBCMD_RESORT_BYX, NULL);
	}
}
void CMainFrame::OnUpdateSortByX(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}
void CMainFrame::OnSortByY()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(), _T("RESORT"), SUBCMD_RESORT_BYY, NULL);
	}
}
void CMainFrame::OnUpdateSortByY(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}
void CMainFrame::OnSortReverse()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(), _T("RESORT"), SUBCMD_RESORT_REVERSE, NULL);
	}
}
void CMainFrame::OnUpdateSortReverse(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}
void CMainFrame::OnSortFinish()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(), _T("RESORT"), SUBCMD_RESORT_FINISH, NULL);
	}
}
void CMainFrame::OnUpdateSortFinish(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}
void CMainFrame::OnCurveToPoints()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(), _T("DRAW"), SUBCMD_DRAW_CURVETOPT, NULL);
	}
}
void CMainFrame::OnUpdateCurveToPoints(CCmdUI *pCmdUI)
{
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->SetText(QGlobal::gf_Str(_T("CURVETOPTS"), _T("Curve to points"))); 
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(), _T("DRAW"), SUBCMD_DRAW_CURVETOPT));
	}
}

void CMainFrame::OnDrawGuideLineBox()
{
	if (E3_GetCmdMgr() != NULL)
	{
		E3_CmdMgrRunCmd(E3_GetCmdMgr(), _T("GUILDLINE"), SUBCMD_GUIDELINE_BOX, NULL);
	}
}
void CMainFrame::OnUpdateDrawGuideLineBox(CCmdUI *pCmdUI)
{
	if (E3_GetCmdMgr() != NULL)
	{
		pCmdUI->SetText(QGlobal::gf_Str(_T("GUILDLINEBOX"), _T("Guideline box")));
		pCmdUI->Enable(E3_CmdMgrIsCmdEnable(E3_GetCmdMgr(), _T("GUILDLINE"), SUBCMD_GUIDELINE_BOX));
	}
}

#include "DlgCameraSet.h"


 
void CMainFrame::OnCameraSet()
{ 
	BOOL bMirrorX, bMirrorY;
	int nExpo, nLight, nConstr;
	double dCornX1,  dCornY1,  dCornX2,  dCornY2;

	E3_GetCameraParam( bMirrorX, bMirrorY,  nExpo,  nLight,  nConstr,  dCornX1,  dCornY1,  dCornX2,  dCornY2);
	CDlgCameraSet dlg(this);
	dlg.m_bMirrorX = bMirrorX;
	dlg.m_bMirrorY = bMirrorY;
	dlg.m_dX = dCornX1;
	dlg.m_dY = dCornY1;
	dlg.m_nExpo = nExpo;
	dlg.m_dW = dCornX2 - dCornX1;
	dlg.m_dH = dCornY2 - dCornY1;
	if (dlg.DoModal() == IDOK)
	{
		bMirrorX = dlg.m_bMirrorX;
		bMirrorY = dlg.m_bMirrorY;
		dCornX1 = dlg.m_dX;
		dCornY1 = dlg.m_dY;
		dCornX2 = dlg.m_dW + dlg.m_dX;
		dCornY2 = dlg.m_dH + dlg.m_dY;
		nExpo = dlg.m_nExpo   ; 
	} 

	E3_SetCameraParam(bMirrorX, bMirrorY, nExpo, nLight, nConstr, dCornX1, dCornY1, dCornX2, dCornY2);
}

void CMainFrame::OnUpdateCameraSet(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE); 
} 