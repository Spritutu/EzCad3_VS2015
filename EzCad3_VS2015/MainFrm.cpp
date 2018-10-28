
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "EzCad3_VS2015.h"

#include "MainFrm.h"
#include "usermessdef.h"
#include "Ezcad3userid.h"
#include "QGlobal.h"
#include "QIniFile.h"
#include "SysParam.h"
#include "afxdockingpanesrow.h" 
#include "E:\Users\25019\Documents\Visual Studio 2017\Projects\180905-EZCAD3 UI\EzCad3_VS2015\EzCad3_VS2015\Mark\MarkStd\DlgMark.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
 

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_TIMER()
	  
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()
	ON_MESSAGE(WM_SETMESSAGESTRING, OnSetMessageString)


	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, &CMainFrame::OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &CMainFrame::OnUpdateFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &CMainFrame::OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, &CMainFrame::OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, &CMainFrame::OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_APP_EXIT, &CMainFrame::OnUpdateFileExit)

	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR, &CMainFrame::OnUpdateToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STATUS_BAR, &CMainFrame::OnUpdateToolbarStatus)
	 
	ON_COMMAND(ID_VIEW_ZOOM, &CMainFrame::OnViewZoom)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM, &CMainFrame::OnUpdateViewZoom)
	ON_COMMAND(ID_EDIT_COPY, &CMainFrame::OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &CMainFrame::OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, &CMainFrame::OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, &CMainFrame::OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, &CMainFrame::OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &CMainFrame::OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, &CMainFrame::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CMainFrame::OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, &CMainFrame::OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CMainFrame::OnUpdateEditRedo)
	ON_COMMAND(ID_EDIT_ADDLAYER, &CMainFrame::OnEditAddlayer)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ADDLAYER, &CMainFrame::OnUpdateEditAddlayer)
	ON_COMMAND(ID_EDIT_DELLAYER, &CMainFrame::OnEditDellayer)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELLAYER, &CMainFrame::OnUpdateEditDellayer)
	ON_COMMAND(ID_EDIT_COMBINE, &CMainFrame::OnEditCombine)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COMBINE, &CMainFrame::OnUpdateEditCombine)
	ON_COMMAND(ID_EDIT_UNCOMBINE, &CMainFrame::OnEditUncombine)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNCOMBINE, &CMainFrame::OnUpdateEditUncombine)
	ON_COMMAND(ID_EDIT_GROUP, &CMainFrame::OnEditGroup)
	ON_UPDATE_COMMAND_UI(ID_EDIT_GROUP, &CMainFrame::OnUpdateEditGroup)
	ON_COMMAND(ID_EDIT_UNGROUP, &CMainFrame::OnEditUngroup)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNGROUP, &CMainFrame::OnUpdateEditUngroup)
	ON_COMMAND(ID_EDIT_UNGROUPTEXT, &CMainFrame::OnEditUngroupText)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNGROUPTEXT, &CMainFrame::OnUpdateEditUngroupText)

	
	ON_COMMAND(ID_ZOOM_WND, OnZoomWnd)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_WND, OnUpdateZoomWnd)
	ON_COMMAND(ID_ZOOM_PAN, OnZoomPan)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_PAN, OnUpdateZoomPan)
	ON_COMMAND(ID_ZOOM_IN, OnZoomIn)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_IN, OnUpdateZoomIn)
	ON_COMMAND(ID_ZOOM_ALL, OnZoomAll)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_ALL, OnUpdateZoomAll)
	ON_COMMAND(ID_ZOOM_PICK, OnZoomPick)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_PICK, OnUpdateZoomPick)
	ON_COMMAND(ID_ZOOM_WORKSPACE, OnZoomWorkspace)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_WORKSPACE, OnUpdateZoomWorkspace)
	ON_COMMAND(ID_ZOOM_OUT, OnZoomOut)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_OUT, OnUpdateZoomOut)
	ON_COMMAND(ID_TEST_BUTTON3, OnTestButton)
	ON_UPDATE_COMMAND_UI(ID_TEST_BUTTON3, OnUpdateTestButton)
	ON_COMMAND(ID_TOOLBAR_MARK3, OnTestButton)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_MARK3, OnUpdateTestButton)
	ON_COMMAND(ID_TEST_RED, OnTestRed)
	ON_UPDATE_COMMAND_UI(ID_TEST_RED, OnUpdateTestRed)
	ON_COMMAND(ID_TOOLBAR_RED, OnTestRed)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_RED, OnUpdateTestRed)
	ON_COMMAND(ID_VIEW_DRAWBAR, OnViewDrawBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DRAWBAR, &CMainFrame::OnUpdateViewDrawBar)
	ON_COMMAND(ID_VIEW_ALIGN, OnViewAlignBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALIGN, &CMainFrame::OnUpdateViewAlignBar)

	
	ON_COMMAND(ID_VIEW_ENTLIST, &CMainFrame::OnViewEntList)
	ON_COMMAND(ID_VIEW_ENTPROP, &CMainFrame::OnViewEntProp)

	ON_UPDATE_COMMAND_UI(ID_VIEW_ENTLIST, &CMainFrame::OnUpdateViewEntList)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ENTPROP, &CMainFrame::OnUpdateViewEntProp)

	
	ON_COMMAND(ID_VIEW_ZOOM3D, &CMainFrame::OnViewZoom3d) 
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM3D, &CMainFrame::OnUpdateViewZoom3d)
	 ON_COMMAND(ID_VIEW_MARKPARAM, &CMainFrame::OnViewMarkParam)
	ON_COMMAND(ID_VIEW_MARKPANEL, &CMainFrame::OnViewMarkPanel) 
	ON_UPDATE_COMMAND_UI(ID_VIEW_MARKPARAM, &CMainFrame::OnUpdateViewMarkParam)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MARKPANEL, &CMainFrame::OnUpdateViewMarkPanel)
 
	ON_COMMAND(ID_LASRER_LASERMONITOR, &CMainFrame::OnViewLaserMonitor)
	ON_UPDATE_COMMAND_UI(ID_LASRER_LASERMONITOR, &CMainFrame::OnUpdateViewLaserMonitor)

	ON_COMMAND(ID_DRAW_BITMAP, &CMainFrame::OnDrawBitmap)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BITMAP, &CMainFrame::OnUpdateDrawBitmap)
	ON_COMMAND(ID_DRAW_CIR, &CMainFrame::OnDrawCir)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIR, &CMainFrame::OnUpdateDrawCir)
	ON_COMMAND(ID_DRAW_ELP, &CMainFrame::OnDrawElp)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ELP, &CMainFrame::OnUpdateDrawElp)
	ON_COMMAND(ID_DRAW_INPUT, &CMainFrame::OnDrawInput)
	ON_UPDATE_COMMAND_UI(ID_DRAW_INPUT, &CMainFrame::OnUpdateDrawInput)
	ON_COMMAND(ID_DRAW_LINE, &CMainFrame::OnDrawLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, &CMainFrame::OnUpdateDrawLine)
	ON_COMMAND(ID_DRAW_OUTPUT, &CMainFrame::OnDrawOutput)
	ON_UPDATE_COMMAND_UI(ID_DRAW_OUTPUT, &CMainFrame::OnUpdateDrawOutput)
	ON_COMMAND(ID_DRAW_PLINE, &CMainFrame::OnDrawPline)
	ON_UPDATE_COMMAND_UI(ID_DRAW_PLINE, &CMainFrame::OnUpdateDrawPline)
	ON_COMMAND(ID_DRAW_POINT, &CMainFrame::OnDrawPoint)
	ON_UPDATE_COMMAND_UI(ID_DRAW_POINT, &CMainFrame::OnUpdateDrawPoint)
	ON_COMMAND(ID_DRAW_POLYGON, &CMainFrame::OnDrawPolygon)
	ON_UPDATE_COMMAND_UI(ID_DRAW_POLYGON, &CMainFrame::OnUpdateDrawPolygon)
	ON_COMMAND(ID_DRAW_RECT, &CMainFrame::OnDrawRect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECT, &CMainFrame::OnUpdateDrawRect)
	ON_COMMAND(ID_DRAW_SPIRAL, &CMainFrame::OnDrawSpiral)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SPIRAL, &CMainFrame::OnUpdateDrawSpiral)
	ON_COMMAND(ID_DRAW_TEXT, &CMainFrame::OnDrawText)
	ON_UPDATE_COMMAND_UI(ID_DRAW_TEXT, &CMainFrame::OnUpdateDrawText)
	ON_COMMAND(ID_DRAW_TIME, &CMainFrame::OnDrawTime)
	ON_UPDATE_COMMAND_UI(ID_DRAW_TIME, &CMainFrame::OnUpdateDrawTime)
	ON_COMMAND(ID_DRAW_VECTORFILE, &CMainFrame::OnDrawVectorfile)
	ON_UPDATE_COMMAND_UI(ID_DRAW_VECTORFILE, &CMainFrame::OnUpdateDrawVectorfile)
	ON_COMMAND(ID_DRAW_PICK, &CMainFrame::OnDrawPick)
	ON_UPDATE_COMMAND_UI(ID_DRAW_PICK, &CMainFrame::OnUpdateDrawPick)
	ON_COMMAND(ID_DRAW_NODE, &CMainFrame::OnDrawNode)
	ON_UPDATE_COMMAND_UI(ID_DRAW_NODE, &CMainFrame::OnUpdateDrawNode)
	ON_COMMAND(ID_DRAW_BARCODE, &CMainFrame::OnDrawBarcode)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BARCODE, &CMainFrame::OnUpdateDrawBarcode)
	ON_COMMAND(ID_DRAW_BARCODE1, OnDrawBarcode1)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BARCODE1, OnUpdateDrawBarcode1)
	ON_COMMAND(ID_DRAW_BARCODE2, OnDrawBarcode2)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BARCODE2, OnUpdateDrawBarcode2)
	ON_COMMAND(ID_DRAW_BARCODE3, OnDrawBarcode3)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BARCODE3, OnUpdateDrawBarcode3)
	ON_COMMAND(ID_DRAW_COOR, &CMainFrame::OnDrawCoor)
	ON_UPDATE_COMMAND_UI(ID_DRAW_COOR, &CMainFrame::OnUpdateDrawCoor)
	ON_COMMAND(ID_DRAW_CLOSE, &CMainFrame::OnDrawClose)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CLOSE, &CMainFrame::OnUpdateDrawClose)
	ON_COMMAND(ID_DRAW_FINISH, &CMainFrame::OnDrawFinish)
	ON_UPDATE_COMMAND_UI(ID_DRAW_FINISH, &CMainFrame::OnUpdateDrawFinish)
	ON_COMMAND(ID_DRAW_EXTAXIS, &CMainFrame::OnDrawExtaxis)
	ON_UPDATE_COMMAND_UI(ID_DRAW_EXTAXIS, &CMainFrame::OnUpdateDrawExtaxis)
 	ON_COMMAND(ID_DRAW_ENCODERDISTANCE, &CMainFrame::OnDrawEncoder)
 	ON_UPDATE_COMMAND_UI(ID_DRAW_ENCODERDISTANCE, &CMainFrame::OnUpdateDrawEncoder)
	ON_COMMAND(ID_DRAW_INDEX, &CMainFrame::OnDrawIndex)
	ON_UPDATE_COMMAND_UI(ID_DRAW_INDEX, &CMainFrame::OnUpdateDrawIndex)
	ON_COMMAND(ID_DRAW_CCD, &CMainFrame::OnDrawCCD)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CCD, &CMainFrame::OnUpdateDrawCCD)
	ON_COMMAND(ID_DRAW_INPUTJUMP, &CMainFrame::OnDrawInputJump)
	ON_UPDATE_COMMAND_UI(ID_DRAW_INPUTJUMP, &CMainFrame::OnUpdateDrawInputJump)
	 
	ON_COMMAND(ID_CMD_PICKALL, &CMainFrame::OnCmdPickAll)
	ON_UPDATE_COMMAND_UI(ID_CMD_PICKALL, &CMainFrame::OnUpdateCmdPickAll)
	ON_COMMAND(ID_CMD_PICKINVERT, &CMainFrame::OnCmdPickInvert)
	ON_UPDATE_COMMAND_UI(ID_CMD_PICKINVERT, &CMainFrame::OnUpdateCmdPickInvert)
	ON_COMMAND(ID_CMD_PICKDEL, &CMainFrame::OnCmdPickDel)
	ON_UPDATE_COMMAND_UI(ID_CMD_PICKDEL, &CMainFrame::OnUpdateCmdPickDel)
	ON_COMMAND(ID_CMD_PICKLOCK, &CMainFrame::OnCmdPickLock)
	ON_UPDATE_COMMAND_UI(ID_CMD_PICKLOCK, &CMainFrame::OnUpdateCmdPickLock)
	ON_COMMAND(ID_CMD_PICKUNLOCK, &CMainFrame::OnCmdPickUnLock)
	ON_UPDATE_COMMAND_UI(ID_CMD_PICKUNLOCK, &CMainFrame::OnUpdateCmdPickUnLock)
	ON_COMMAND(ID_CMD_PICKUNLOCKALL, &CMainFrame::OnCmdPickUnLockAll)
	ON_UPDATE_COMMAND_UI(ID_CMD_PICKUNLOCKALL, &CMainFrame::OnUpdateCmdPickUnLockAll)
	ON_COMMAND(ID_CMD_PICKCEN, &CMainFrame::OnCmdPickCen)
	ON_UPDATE_COMMAND_UI(ID_CMD_PICKCEN, &CMainFrame::OnUpdateCmdPickCen)
	ON_COMMAND(ID_CMD_PICKCENX, &CMainFrame::OnCmdPickCenX)
	ON_UPDATE_COMMAND_UI(ID_CMD_PICKCENX, &CMainFrame::OnUpdateCmdPickCenX)
	ON_COMMAND(ID_CMD_PICKCENY, &CMainFrame::OnCmdPickCenY)
	ON_UPDATE_COMMAND_UI(ID_CMD_PICKCENY, &CMainFrame::OnUpdateCmdPickCenY)
	ON_COMMAND(ID_CMD_PICKMIRRORX, &CMainFrame::OnCmdPickMirrorX)
	ON_UPDATE_COMMAND_UI(ID_CMD_PICKMIRRORX, &CMainFrame::OnUpdateCmdPickMirrorX)
	ON_COMMAND(ID_CMD_PICKMIRRORY, &CMainFrame::OnCmdPickMirrorY)
	ON_UPDATE_COMMAND_UI(ID_CMD_PICKMIRRORY, &CMainFrame::OnUpdateCmdPickMirrorY)
	ON_COMMAND(ID_MODIFY_ARRAY, OnModifyArray)
	ON_UPDATE_COMMAND_UI(ID_MODIFY_ARRAY, OnUpdateModifyArray)
	ON_COMMAND(ID_MODIFY_ROTATE, OnModifyRotate)
	ON_UPDATE_COMMAND_UI(ID_MODIFY_ROTATE, OnUpdateModifyRotate)
	ON_COMMAND(ID_MODIFY_RESORT, OnModifyResort)
	ON_UPDATE_COMMAND_UI(ID_MODIFY_RESORT, OnUpdateModifyResort) 
	ON_COMMAND(ID_PICK_BYPEN, OnCmdPickByPen)
	ON_UPDATE_COMMAND_UI(ID_PICK_BYPEN, OnUpdateCmdPickByPen) 
	ON_COMMAND(ID_FILE_PROJECTPARAM, &CMainFrame::OnFileProjectParam)
	ON_UPDATE_COMMAND_UI(ID_FILE_PROJECTPARAM, &CMainFrame::OnUpdateFileProjectParam) 
	ON_COMMAND(ID_FILE_SYSTEM, &CMainFrame::OnFileSystem)
	ON_UPDATE_COMMAND_UI(ID_FILE_SYSTEM, &CMainFrame::OnUpdateFileSystem) 
	ON_COMMAND(ID_FILE_MACHINEPARAMETER, &CMainFrame::OnDeviceParam)
	ON_UPDATE_COMMAND_UI(ID_FILE_MACHINEPARAMETER, &CMainFrame::OnUpdateDeviceParam) 
	ON_COMMAND(ID_EDIT_HATCHENT, &CMainFrame::OnEditHatch)
	ON_UPDATE_COMMAND_UI(ID_EDIT_HATCHENT, &CMainFrame::OnUpdateEditHatch) 
	ON_COMMAND(ID_CMD_NODE_ADD, &CMainFrame::OnCmdNodeAdd)
	ON_UPDATE_COMMAND_UI(ID_CMD_NODE_ADD, &CMainFrame::OnUpdateCmdNodeAdd)
	ON_COMMAND(ID_CMD_NODE_ALIGN, &CMainFrame::OnCmdNodeAlign)
	ON_UPDATE_COMMAND_UI(ID_CMD_NODE_ALIGN, &CMainFrame::OnUpdateCmdNodeAlign)
	ON_COMMAND(ID_CMD_NODE_CLOSE, &CMainFrame::OnCmdNodeClose)
	ON_UPDATE_COMMAND_UI(ID_CMD_NODE_CLOSE, &CMainFrame::OnUpdateCmdNodeClose)
	ON_COMMAND(ID_CMD_NODE_DEL, &CMainFrame::OnCmdNodeDel)
	ON_UPDATE_COMMAND_UI(ID_CMD_NODE_DEL, &CMainFrame::OnUpdateCmdNodeDel)
	ON_COMMAND(ID_CMD_NODE_SEPA, &CMainFrame::OnCmdNodeSepa)
	ON_UPDATE_COMMAND_UI(ID_CMD_NODE_SEPA, &CMainFrame::OnUpdateCmdNodeSepa)
	ON_COMMAND(ID_CMD_NODE_SHARP, &CMainFrame::OnCmdNodeSharp)
	ON_UPDATE_COMMAND_UI(ID_CMD_NODE_SHARP, &CMainFrame::OnUpdateCmdNodeSharp)
	ON_COMMAND(ID_CMD_NODE_SMOOTH, &CMainFrame::OnCmdNodeSmooth)
	ON_UPDATE_COMMAND_UI(ID_CMD_NODE_SMOOTH, &CMainFrame::OnUpdateCmdNodeSmooth)
	ON_COMMAND(ID_CMD_NODE_TOARC, &CMainFrame::OnCmdNodeToarc)
	ON_UPDATE_COMMAND_UI(ID_CMD_NODE_TOARC, &CMainFrame::OnUpdateCmdNodeToarc)
	ON_COMMAND(ID_CMD_NODE_TOBEZ, &CMainFrame::OnCmdNodeTobez)
	ON_UPDATE_COMMAND_UI(ID_CMD_NODE_TOBEZ, &CMainFrame::OnUpdateCmdNodeTobez)
	ON_COMMAND(ID_CMD_NODE_TOLINE, &CMainFrame::OnCmdNodeToline)
	ON_UPDATE_COMMAND_UI(ID_CMD_NODE_TOLINE, &CMainFrame::OnUpdateCmdNodeToline)
	ON_COMMAND(ID_CMD_NODE_UNITE, &CMainFrame::OnCmdNodeUnite)
	ON_UPDATE_COMMAND_UI(ID_CMD_NODE_UNITE, &CMainFrame::OnUpdateCmdNodeUnite)
	ON_COMMAND(ID_CMD_NODE_DIR, &CMainFrame::OnCmdNodeDir)
	ON_UPDATE_COMMAND_UI(ID_CMD_NODE_DIR, &CMainFrame::OnUpdateCmdNodeDir)
	ON_COMMAND(ID_CMD_NODE_SYS, &CMainFrame::OnCmdNodeSys)
	ON_UPDATE_COMMAND_UI(ID_CMD_NODE_SYS, &CMainFrame::OnUpdateCmdNodeSys) 
	ON_WM_CLOSE() 
	ON_COMMAND(ID_3DFUN_RUN, OnZoom3d)
	ON_UPDATE_COMMAND_UI(ID_3DFUN_RUN, OnUpdateZoom3d)
	ON_COMMAND(ID_ZOOM_3D_UP, OnZoom3dUp)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_3D_UP, OnUpdateZoom3dUp)
	ON_COMMAND(ID_ZOOM_3D_DN, OnZoom3dDown)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_3D_DN, OnUpdateZoom3dDown)
	ON_COMMAND(ID_ZOOM_3D_LEFT, OnZoom3dLeft)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_3D_LEFT, OnUpdateZoom3dLeft)
	ON_COMMAND(ID_ZOOM_3D_RIGHT, OnZoom3dRight)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_3D_RIGHT, OnUpdateZoom3dRight)
	ON_COMMAND(ID_ZOOM_3D_FR, OnZoom3dFront)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_3D_FR, OnUpdateZoom3dFront)
	ON_COMMAND(ID_ZOOM_3D_BACK, OnZoom3dBack)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_3D_BACK, OnUpdateZoom3dBack)
	ON_COMMAND(ID_ZOOM_3D_ISO, OnZoom3dIso)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_3D_ISO, OnUpdateZoom3dIso)

	ON_COMMAND(ID_3DFUN_MESH3D, OnDrawMesh3d)
	ON_UPDATE_COMMAND_UI(ID_3DFUN_MESH3D, OnUpdateDrawMesh3d)
	ON_COMMAND(ID_3DFUN_SLICE3D, OnFun3dSlice)
	ON_UPDATE_COMMAND_UI(ID_3DFUN_SLICE3D, OnUpdateFun3dSlice)

	ON_COMMAND(ID_3DVIEW_WIRE, On3DViewWire)
	ON_UPDATE_COMMAND_UI(ID_3DVIEW_WIRE, OnUpdate3DViewWire)
	ON_COMMAND(ID_3DVIEW_RENDER, On3DViewRender)
	ON_UPDATE_COMMAND_UI(ID_3DVIEW_RENDER, OnUpdate3DViewRender)
	ON_COMMAND(ID_3DVIEW_RENDERLINE, On3DViewRenderLine)
	ON_UPDATE_COMMAND_UI(ID_3DVIEW_RENDERLINE, OnUpdate3DViewRenderLine)
	ON_COMMAND(ID_3DVIEW_HIDEMESH, On3DViewHideMesh)
	ON_UPDATE_COMMAND_UI(ID_3DVIEW_HIDEMESH, OnUpdate3DViewHideMesh)

	ON_COMMAND(ID_3DFUN_SLICEMESH, OnFun3dSliceMesh)
	ON_UPDATE_COMMAND_UI(ID_3DFUN_SLICEMESH, OnUpdateFun3dSliceMesh)

	ON_COMMAND(ID_3DFUN_ROTATEMESH, OnFun3dRotateMesh)
	ON_UPDATE_COMMAND_UI(ID_3DFUN_ROTATEMESH, OnUpdateFun3dRotateMesh)
	ON_COMMAND(ID_3DFUN_MOVEMESH, OnFun3dMoveMesh)
	ON_UPDATE_COMMAND_UI(ID_3DFUN_MOVEMESH, OnUpdateFun3dMoveMesh)
	ON_COMMAND(ID_3DFUN_PRJ, OnFun3dPrj)
	ON_UPDATE_COMMAND_UI(ID_3DFUN_PRJ, OnUpdateFun3dPrj)
	ON_COMMAND(ID_3DFUN_BASESHAPE, OnFun3dBasicShape)
	ON_UPDATE_COMMAND_UI(ID_3DFUN_BASESHAPE, OnUpdateFun3dBasicShape)
	ON_COMMAND(ID_3DFUN_BMPTOMESH, OnFun3dBmpToMesh)
	ON_UPDATE_COMMAND_UI(ID_3DFUN_BMPTOMESH, OnUpdateFun3dBmpToMesh)
	ON_COMMAND(ID_3DFUN_FREEPAINT, OnFun3dFreePaint)
	ON_UPDATE_COMMAND_UI(ID_3DFUN_FREEPAINT, OnUpdateFun3dFreePaint)
		 
	ON_MESSAGE(WM_USER_NODECMD, OnUserRunNode)
	ON_MESSAGE(WM_USER_SHOW3DCMD, OnUserRun3DView)
	ON_MESSAGE(WM_USER_STATUSPANEL, OnUserChangeStatusText)

		
	ON_UPDATE_COMMAND_UI(ID_APP_ABOUT, OnUpdateAbout)

	ON_COMMAND(ID_VIEW_SANPGRID, &CMainFrame::OnViewSnapGrid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SANPGRID, &CMainFrame::OnUpdateViewSnapGrid)
	ON_COMMAND(ID_VIEW_SNAPGUILDLINE, &CMainFrame::OnViewSnapGL)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SNAPGUILDLINE, &CMainFrame::OnUpdateViewSnapGL)
	ON_COMMAND(ID_VIEW_SNAPOBJECT, &CMainFrame::OnViewSnapObject)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SNAPOBJECT, &CMainFrame::OnUpdateViewSnapObject)
	ON_COMMAND(ID_VIEW_SNAPMESHVERTEX, &CMainFrame::OnViewSnapMeshVertex)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SNAPMESHVERTEX, &CMainFrame::OnUpdateViewSnapMeshVertex)

	ON_COMMAND(ID_VIEW_SHOWRULER, &CMainFrame::OnViewShowRuler)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHOWRULER, &CMainFrame::OnUpdateViewShowRuler)
	ON_COMMAND(ID_VIEW_SHOWGRID, &CMainFrame::OnViewShowGrid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHOWGRID, &CMainFrame::OnUpdateViewShowGrid)

	ON_COMMAND(ID_MODIFY_ARRAYTEXT, &CMainFrame::OnArrayText)
	ON_UPDATE_COMMAND_UI(ID_MODIFY_ARRAYTEXT, &CMainFrame::OnUpdateArrayText)
	ON_COMMAND(ID_MODIFY_OFFSETCURVE, &CMainFrame::OnOffsetCurve)
	ON_UPDATE_COMMAND_UI(ID_MODIFY_OFFSETCURVE, &CMainFrame::OnUpdateOffsetCurve)
	ON_COMMAND(ID_MODIFY_TOCURVE, &CMainFrame::OnCmdToCurve)
	ON_UPDATE_COMMAND_UI(ID_MODIFY_TOCURVE, &CMainFrame::OnUpdateCmdToCurve)

	ON_COMMAND(ID_LASRER_MATERIALPROCESS, &CMainFrame::OnCmdLaserProcess)
	ON_UPDATE_COMMAND_UI(ID_LASRER_MATERIALPROCESS, &CMainFrame::OnUpdateCmdLaserProcess)
	ON_COMMAND(ID_DISTORTION_WELD, &CMainFrame::OnCmdDistortionWeld)
	ON_UPDATE_COMMAND_UI(ID_DISTORTION_WELD, &CMainFrame::OnUpdateCmdDistortionWeld)
	ON_COMMAND(ID_DISTORTION_TRIM, &CMainFrame::OnCmdDistortionTrim)
	ON_UPDATE_COMMAND_UI(ID_DISTORTION_TRIM, &CMainFrame::OnUpdateCmdDistortionTrim)
	ON_COMMAND(ID_DISTORTION_INTERSECT, &CMainFrame::OnCmdDistortionInter)
	ON_UPDATE_COMMAND_UI(ID_DISTORTION_INTERSECT, &CMainFrame::OnUpdateCmdDistortionInter)

	ON_COMMAND(ID_ALIGN_LEFT, OnAlignLeft)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_LEFT, OnUpdateAlignLeft)
	ON_COMMAND(ID_ALIGN_HCENTER, OnAlignHCenter)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_HCENTER, OnUpdateAlignHCenter)		
	ON_COMMAND(ID_ALIGN_RIGHT, OnAlignRight)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_RIGHT, OnUpdateAlignRight)

	ON_COMMAND(ID_ALIGN_TOP, OnAlignTop)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_TOP, OnUpdateAlignTop)
	ON_COMMAND(ID_ALIGN_VCENTER, OnAlignVCenter)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_VCENTER, OnUpdateAlignVCenter)		
	ON_COMMAND(ID_ALIGN_BOTTOM, OnAlignBottom)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_BOTTOM, OnUpdateAlignBottom)

	ON_COMMAND(ID_ALIGN_CENTER, OnAlignCenter)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_CENTER, OnUpdateAlignCenter)	
	ON_COMMAND(ID_MODIFY_TRIM, OnTrim)
	ON_UPDATE_COMMAND_UI(ID_MODIFY_TRIM, OnUpdateTrim)
	 
	ON_COMMAND(ID_CURVEEDIT_AUTOCONNECT, OnModifyCurveConnect)
	ON_UPDATE_COMMAND_UI(ID_CURVEEDIT_AUTOCONNECT, OnUpdateModifyCurveConnect)
	ON_COMMAND(ID_CURVEEDIT_BREADCROSSPOINT, OnModifyBreakCross)
	ON_UPDATE_COMMAND_UI(ID_CURVEEDIT_BREADCROSSPOINT, OnUpdateModifyBreakCross)
	ON_COMMAND(ID_MESHEDIT_MERGECLOSEVERTICES, OnModifyMeshMergeCloseVertex)
	ON_UPDATE_COMMAND_UI(ID_MESHEDIT_MERGECLOSEVERTICES, OnUpdateModifyMeshMergeCloseVertex)

	ON_COMMAND(ID_RESORT_SORTBYX, OnSortByX)
	ON_UPDATE_COMMAND_UI(ID_RESORT_SORTBYX, OnUpdateSortByX)
	ON_COMMAND(ID_RESORT_SORTBYY, OnSortByY)
	ON_UPDATE_COMMAND_UI(ID_RESORT_SORTBYY, OnUpdateSortByY)
	ON_COMMAND(ID_RESORT_SORTREVERSE, OnSortReverse)
	ON_UPDATE_COMMAND_UI(ID_RESORT_SORTREVERSE, OnUpdateSortReverse)
	ON_COMMAND(ID_RESORT_FINISH, OnSortFinish)
	ON_UPDATE_COMMAND_UI(ID_RESORT_FINISH, OnUpdateSortFinish) 
	ON_COMMAND(ID_MODIFY_CURVETOPOINTS, OnCurveToPoints)
	ON_UPDATE_COMMAND_UI(ID_MODIFY_CURVETOPOINTS, OnUpdateCurveToPoints)  
	ON_COMMAND(ID_DRAW_GUIDELINEBOX, OnDrawGuideLineBox)
	ON_UPDATE_COMMAND_UI(ID_DRAW_GUIDELINEBOX, OnUpdateDrawGuideLineBox) 
	ON_COMMAND(IDB_MENU_CAMERA, OnCameraSet)
	ON_UPDATE_COMMAND_UI(IDB_MENU_CAMERA, OnUpdateCameraSet)

END_MESSAGE_MAP()
	static UINT indicators[] =
	{
		ID_SEPARATOR,           // status line indicator
		ID_SEPARATOR,           // coordinate	
		ID_SEPARATOR,           // snap grid
		ID_SEPARATOR,           // snap guild	
		ID_SEPARATOR,           // snap object	 
	};

// CMainFrame 构造/析构

	CMainFrame::CMainFrame()
	{
		// TODO: 在此添加成员初始化代码
		theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
		m_pDlgSplash = new CDlgSplash;
		m_bShowMachineParam = FALSE;
		m_bHideExtAxis = FALSE;

		m_bHideEntEncoder = FALSE;
		m_bHideEntIndex = FALSE;
		m_bHideEntCCD = FALSE;
		m_bHideEntJump = FALSE;
		m_bHideShowSol = FALSE;
	}

CMainFrame::~CMainFrame()
{ 
	gf_SaveSysParamFile();

	if (m_pDlgSplash != NULL)
	{
		delete m_pDlgSplash;
		m_pDlgSplash = NULL;
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	QGlobal::Log(_T("MF_ShowSplash 1"));
	m_pDlgSplash->ShowSplash(this);
	QGlobal::Log(_T("MF_ShowSplash 2"));


	if (!m_wndMenuBar.Create(this))
	{
	//	TRACE0("未能创建菜单栏\n");
		return -1;      // 未能创建
	}
 	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY); 
	// 防止菜单栏在激活时获得焦点
	CMFCPopupMenu::SetForceMenuFocus(FALSE);
	m_wndMenuBar.SetRecentlyUsedMenus(FALSE);
	 

	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||		
	//	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME_256))
		
	if (!m_wndToolBar.Create(this,
		WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, IDR_TOOLBAR_SYS) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR_SYS))
	{
	//	TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	m_wndToolBar.SetWindowText(QGlobal::gf_Str(_T("STANDARD"), _T("Standrad")));

	 
	CString strTitle;
#ifndef USE_DRAWTOOL_BAR
	if (!m_wndDrawBar.Create(this,
		WS_CHILD | WS_VISIBLE | CBRS_LEFT | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE | CBRS_SIZE_DYNAMIC | CBRS_GRIPPER | CBRS_BORDER_3D, IDR_TOOLBAR_DRAW) ||
		//!m_wndDrawBar.LoadToolBar(IDR_TOOLBAR_DRAW))
		!m_wndDrawBar.LoadToolBar (IDR_TOOLBAR_DRAW, 0, 0, FALSE, 0,0, IDB_BITMAP_DRAW24))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	strTitle = QGlobal::gf_Str(_T("DRAW"), _T("Draw"));
	m_wndDrawBar.SetWindowText(strTitle);
#endif
	if (!m_wndZooml3dBar.Create(this,
		WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE | CBRS_SIZE_DYNAMIC | CBRS_GRIPPER | CBRS_BORDER_3D, IDR_TOOLBAR_ZOOM3D) ||
		!m_wndZooml3dBar.LoadToolBar(IDR_TOOLBAR_ZOOM3D))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	strTitle = QGlobal::gf_Str(_T("ZOOM"), _T("Zoom")) + _T("3D");
	m_wndZooml3dBar.SetWindowText(strTitle);
	

	
	

	if (!m_wnd3dFunBar.Create(this,
		WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE | CBRS_SIZE_DYNAMIC | CBRS_GRIPPER | CBRS_BORDER_3D, 
		IDR_TOOLBAR_3DFUN) ||
		!m_wnd3dFunBar.LoadToolBar(IDR_TOOLBAR_3DFUN))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	strTitle = QGlobal::gf_Str(_T("3DFUN"), _T("3D function"));
	m_wnd3dFunBar.SetWindowText(strTitle);



	if (!m_wndPickCmdBar.Create(this,
		WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE | CBRS_SIZE_DYNAMIC | CBRS_GRIPPER | CBRS_BORDER_3D, 
		IDR_TOOLBAR_CMDPICK) ||
		!m_wndPickCmdBar.LoadToolBar(IDR_TOOLBAR_CMDPICK))
		//!m_wndPickCmdBar.LoadToolBar (IDR_TOOLBAR_CMDPICK, 0, 0, FALSE, 0,0, IDB_BITMAP_PICK))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	m_wndPickCmdBar.SetWindowText(QGlobal::gf_Str(_T("PICK"), _T("Pick")));
	if (!m_wndMarkBar.Create(this,
		WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY  | CBRS_SIZE_DYNAMIC |
		CBRS_GRIPPER | CBRS_BORDER_3D,
		IDR_TOOLBAR_MARK2) ||
		!m_wndMarkBar.LoadToolBar(IDR_TOOLBAR_MARK2))
			{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	m_wndMarkBar.SetWindowText(QGlobal::gf_Str(_T("Mark"), _T("Mark")));
	

	if (!m_wndNodeCmdBar.Create(this,
		WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE | CBRS_SIZE_DYNAMIC |
		CBRS_GRIPPER | CBRS_BORDER_3D,
		IDR_TOOLBAR_CMDNODE) ||
		!m_wndNodeCmdBar.LoadToolBar(IDR_TOOLBAR_CMDNODE))
		//!m_wndNodeCmdBar.LoadToolBar (IDR_TOOLBAR_CMDNODE, 0, 0, FALSE, 0,0, IDB_BITMAP_NODE))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	m_wndNodeCmdBar.SetWindowText(QGlobal::gf_Str(_T("NODE"), _T("Node")));
	QGlobal::Log(_T("MF_6"));




	if (!m_wndAlignBar.Create(this,
		WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE | CBRS_SIZE_DYNAMIC |
		CBRS_GRIPPER | CBRS_BORDER_3D,
		IDR_TOOLBAR_CMDNODE) ||
		!m_wndAlignBar.LoadToolBar(IDR_TOOLBAR_ALIGN))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	m_wndAlignBar.SetWindowText(QGlobal::gf_Str(_T("ALIGN"), _T("Align")));

 	 
	// 允许用户定义的工具栏操作: 
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	int nPaneWidth = 100;
	{
		CDC* pDC = m_wndStatusBar.GetDC();
		CSize size;
		CString strSample = _T("-1234.0000,-1234.0000");
		size = pDC->GetTextExtent(strSample, strSample.GetLength());
		nPaneWidth = size.cx;
		m_wndStatusBar.ReleaseDC(pDC);
	}
	m_wndStatusBar.SetPaneInfo(1, ID_USER_INDICATOR_COOR, SBPS_NORMAL, nPaneWidth);
	m_wndStatusBar.SetPaneInfo(2, ID_USER_INDICATOR_SNAPGRID, SBPS_NORMAL, 2 * nPaneWidth / 3);
	m_wndStatusBar.SetPaneInfo(3, ID_USER_INDICATOR_SNAPGUILD, SBPS_NORMAL, 2 * nPaneWidth / 3);
	m_wndStatusBar.SetPaneInfo(4, ID_USER_INDICATOR_SNAPOBJECT, SBPS_NORMAL, 2*nPaneWidth / 3);
	QGlobal::Log(_T("MF_8"));

	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);


	// TODO: 如果您不希望工具栏和菜单栏可停靠，请删除这五行
 	m_wndMenuBar.EnableDocking(CBRS_ALIGN_TOP);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY); 
#ifndef USE_DRAWTOOL_BAR
	m_wndDrawBar.EnableDocking(CBRS_ALIGN_ANY);
#endif
	m_wndZooml3dBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wnd3dFunBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndPickCmdBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndNodeCmdBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndAlignBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndMarkBar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);

 	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);  
	DockPane(&m_wnd3dFunBar);	

#ifndef USE_DRAWTOOL_BAR		
	//标准工具条停靠到缩放工具条左边
	DockPaneLeftOf(&m_wndToolBar, &m_wnd3dFunBar);
	DockPane(&m_wndDrawBar);  
#endif
	
	DockPane(&m_wndZooml3dBar);

#ifndef USE_DRAWTOOL_BAR		
	DockPaneLeftOf(&m_wndDrawBar, &m_wndZooml3dBar);
#endif
	DockPane(&m_wndPickCmdBar);
	DockPane(&m_wndAlignBar);
	DockPaneLeftOf(&m_wndPickCmdBar, &m_wndAlignBar);
	DockPane(&m_wndNodeCmdBar);
	DockPane(&m_wndMarkBar);
	DockPaneLeftOf(&m_wndMarkBar, &m_wndAlignBar);
	

#ifdef  USE_TOOLBAR_FIXEDSIZE     //使用固定尺寸工具条
	if (CMFCToolBar::IsLargeIcons())
	{
		CMFCToolBar::SetLargeIcons(TRUE);
	}
	GetGlobalData()->EnableRibbonImageScale(FALSE);
	//CMFCToolBar::SetSizes(CSize(32, 32), CSize(30, 30));
#else
	 
	double dblScale = GetGlobalData()->GetRibbonImageScale();	
 	CMFCToolBar::SetSizes(CSize((int)(32* dblScale), (int)(32* dblScale)), CSize(30, 30));

#endif	
	 

	 
	// 创建停靠窗口
	if (!CreateDockingWindows())
	{
		TRACE0("未能创建停靠窗口\n");
		return -1;
	}

	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook); 

	// 启用菜单个性化(最近使用的命令)
	// TODO: 定义您自己的基本命令，确保每个下拉菜单至少有一个基本命令。
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);
	lstBasicCommands.AddTail(ID_SORTING_SORTALPHABETIC);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYTYPE);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYACCESS);
	lstBasicCommands.AddTail(ID_SORTING_GROUPBYTYPE);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);
    
	QGlobal::Log(_T("MF_15"));
	E3_CmdMgrSetStatusWnd(E3_GetCmdMgr(),&m_wndStatusBar);

#ifdef  ENABLE_CMD
	E3_CmdMgrRunCmd(E3_GetCmdMgr(),_T("PICK"), 0, 0);
#endif

	E3_CmdMgrAddEntityWnd(E3_GetCmdMgr(), this);//告诉命令管理器当前窗口需要接收系统消息	
	QGlobal::Log(_T("MF_16"));
	ShowSnapStr(); 
	QGlobal::Log(_T("MF_17")); 
	{
		CQIniFile qini;
		CString  strFile = QGlobal::gf_GetParamPath() + _T("Custom.ini");
		qini.SetPath(strFile);
		if (qini.ReadFile())
		{
			CString str = qini.GetValue(_T("PARAM"), _T("HIDEF3"));
			m_bShowMachineParam = qini.GetValueI(_T("PARAM"), _T("HIDEF3"))!=0 ? TRUE:FALSE;
			m_bHideExtAxis = qini.GetValueI(_T("PARAM"), _T("HIDEEXTAXIS")) != 0 ? TRUE : FALSE; 
			m_bHideEntEncoder = qini.GetValueI(_T("PARAM"), _T("HIDEENCODER")) != 0 ? TRUE : FALSE;
			m_bHideEntIndex = qini.GetValueI(_T("PARAM"), _T("HIDEENTINDEX")) != 0 ? TRUE : FALSE;
			m_bHideEntCCD = qini.GetValueI(_T("PARAM"), _T("HIDEENTCCD")) != 0 ? TRUE : FALSE;
			m_bHideEntJump = qini.GetValueI(_T("PARAM"), _T("HIDEENTJUMP")) != 0 ? TRUE : FALSE; 
			m_bHideShowSol = qini.GetValueI(_T("PARAM"), _T("HIDESHOWSOL")) != 0 ? TRUE : FALSE; 
		}
	}


	m_nCurTimer = 0;
	SetTimer(SAVETIMER, 60000, NULL); 
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE; 
	return TRUE;
}

void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	CString strFileName = QGlobal::gf_GetCurFileName();
	if (strFileName.IsEmpty())
	{
		strFileName = QGlobal::gf_Str(_T("NOTITLE"), _T("No title"));
	}

	CString strTitle;
	strTitle.Format(_T("%s-%s"), QGlobal::gf_Str(_T("SOFTNAME"), _T("Ezcad3")), strFileName);
	SetWindowText(strTitle);
}

BOOL CMainFrame::CreateDockingWindows()
{  	
 //
	//if (!m_wndDraw.Create(QGlobal::gf_Str(_T("DRAW"), _T("Draw")), this, CRect(0, 0, 40, 300),
	//	TRUE,
	//	IDR_TOOLBAR_DRAW2,
	//	WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	//{
	//	TRACE0("Failed to create Laser Monitor bar\n");
	//	return FALSE;      // fail to create
	//}
	//m_wndDraw.EnableDocking(CBRS_ALIGN_ANY);
	//DockPane(&m_wndDraw);


	//return TRUE;

	int nPenBoxBarWidth = 200;
	int nEntPropBarWidth = 200;
	int nMarkBarHeight = 100;

	int nScreenPixelX = ::GetSystemMetrics(SM_CXSCREEN);
	if (nScreenPixelX>=1920)
	{
		nPenBoxBarWidth = 310;
		nEntPropBarWidth = 205;
		nMarkBarHeight = 160;
	}
	else if (nScreenPixelX>1366)
	{
		nPenBoxBarWidth = 310;
		nEntPropBarWidth = 280;
		nMarkBarHeight = 150;
	}
	

#ifdef ENABLE_ENTLIST 
	if (!m_barEntList.Create(QGlobal::gf_Str(_T("MENU_VIEW_ENTLIST"), _T("Entitys list")), this, CRect(0, 0, nEntPropBarWidth, 100),
		TRUE,
		ID_ENTITY_LIST,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Entitys list bar\n");
		return FALSE; // 未能创建
	}
#endif
#ifdef	ENABLE_ENTLPROP	
	if (!m_barEntProp.Create(QGlobal::gf_Str(_T("MENU_VIEW_ENTPROP"), _T("Entitys property")), this, CRect(0, 0, nEntPropBarWidth, 300),
		TRUE,
		ID_ENTITY_PROP,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Entitys list bar\n");
		return FALSE;      // fail to create
	}
#endif
#ifdef ENABLE_PENBOX	 
	// 创建属性窗口 ID_BAR_PENBOX 
	if (!m_barPenBox.Create(QGlobal::gf_Str(_T("PENBOX"), _T("Penbox")), this, CRect(0, 0, nPenBoxBarWidth, 200), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
	TRACE0("未能创建“属性”窗口\n");
	return FALSE; // 未能创建
	}
#endif

	

#ifdef ENABLE_MARK
	// 创建属性窗口
	if (!m_wndMark.Create(QGlobal::gf_Str(_T("MARK"), _T("Mark")), this, CRect(0, 0, 200, nMarkBarHeight), TRUE, IDR_MARK_WND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“Mark”窗口\n");
		return FALSE; // 未能创建
	}
#endif

	if (!m_panelLaserMonitor.Create(QGlobal::gf_Str(_T("LASERMONITOR"), _T("Laser Monitor")), this, CRect(0, 0, nEntPropBarWidth, nMarkBarHeight),
		TRUE,
		ID_LASERMONITOR,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Laser Monitor bar\n");
		return FALSE;      // fail to create
	}


#ifdef USE_DRAWTOOL_BAR
	if (!m_wndDraw.Create(QGlobal::gf_Str(_T("DRAW"), _T("Draw")), this, CRect(0, 0, 40, 300),
		TRUE,
		ID_DRAW_TOOL,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Laser Monitor bar\n");
		return FALSE;      // fail to create
	}
#endif	



	QGlobal::Log(_T("MF_14"));
#ifdef	ENABLE_ENTLPROP	
	m_barEntProp.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_barEntProp);
#endif

#ifdef ENABLE_ENTLIST 
	m_barEntList.EnableDocking(CBRS_ALIGN_ANY);
	//Put m_barEntList to m_barEntProp top
	if (!m_barEntList.DockToWindow(&m_barEntProp, CBRS_ALIGN_TOP))
	{
		DockPane(&m_barEntList, AFX_IDW_DOCKBAR_LEFT);
	}
#endif
	 
#ifdef USE_DRAWTOOL_BAR	
	m_wndDraw.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndDraw);
#endif

#ifdef ENABLE_PENBOX	 
	m_barPenBox.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_barPenBox);
#endif
	  

#ifdef ENABLE_MARK  
	m_wndMark.SetMinSize(CSize(0, 90));
	m_wndMark.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMark);
	
	m_panelLaserMonitor.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_panelLaserMonitor);
 	m_panelLaserMonitor.DockToWindow(&m_wndMark, CBRS_ALIGN_RIGHT); 
#endif 	 
	
	 
	return TRUE;
}
 

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序
 

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

//	m_wndOutput.UpdateFonts();
	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}
void CMainFrame::RemoveSpacingOfToolBar()
{
 
	//20180325去除水平工具条之间的空间
	CDockSite* pHortDockSite = this->GetDockingManager()->FindDockSite(CBRS_ALIGN_TOP, TRUE);
	if (pHortDockSite != NULL)
	{
		for (POSITION pos = pHortDockSite->GetDockSiteRowsList().GetHeadPosition(); pos != NULL;)
		{
			CDockingPanesRow* pDockingPanesRow = DYNAMIC_DOWNCAST(CDockingPanesRow, pHortDockSite->GetDockSiteRowsList().GetNext(pos));
			ASSERT_VALID(pDockingPanesRow);
			int nPaneCount = pDockingPanesRow->GetPaneCount();
			if (nPaneCount > 1)
			{//需要检查两个工具条中间是否有空
				CPane* pLastPanel = NULL;
				CRect rectVitualCur, rectVitualLast;
				for (POSITION pos = pDockingPanesRow->GetPaneList().GetHeadPosition(); pos != NULL;)
				{
					CPane* pBar = DYNAMIC_DOWNCAST(CPane, pDockingPanesRow->GetPaneList().GetNext(pos));
					if (pBar != NULL && pBar->IsVisible())
					{
						pBar->GetVirtualRect(rectVitualCur);
						if (pLastPanel != NULL)
						{
							int nOffset = rectVitualCur.left - rectVitualLast.right;
							if (nOffset>1)
							{
								rectVitualCur.left -= nOffset;
								rectVitualCur.right -= nOffset;
								this->ScreenToClient(rectVitualCur);
								pBar->MoveWindow(rectVitualCur);
								pBar->RecalcLayout();
							}
						}
						pLastPanel = pBar;
						rectVitualLast = rectVitualCur;
					}
				}
				pHortDockSite->RecalcLayout();
			}
		}
	}
 
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// 基类将执行真正的工作
	QGlobal::Log(_T("LoadFrame 1"));

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	QGlobal::Log(_T("LoadFrame 2")); 

	InitMenuText(); 

#ifdef  USE_TOOLBAR_FIXEDSIZE     //使用固定尺寸工具条
	int nScreenPixelX = ::GetSystemMetrics(SM_CXSCREEN);

	if (CMFCToolBar::IsLargeIcons())
	{
		CMFCToolBar::SetLargeIcons(FALSE);
	}
	
	CRect rect;
	double dblScale = GetGlobalData()->GetRibbonImageScale();
	if (GetGlobalData()->IsRibbonImageScaleEnabled())
	{
		GetGlobalData()->EnableRibbonImageScale(FALSE);
	} 
	CSize size = m_wndToolBar.GetButtonSize();
	if (nScreenPixelX > 1920)
	{
		CMFCToolBar::SetSizes(CSize(36, 36), CSize(30, 30));
	}
	else if (nScreenPixelX > 800)
	{
		CMFCToolBar::SetSizes(CSize(32, 32), CSize(30, 30));
	}
	else
	{
		GetGlobalData()->EnableRibbonImageScale(TRUE);
		
		CMFCToolBar::SetSizes(CSize(30, 30), CSize(30, 30));
	}
	//m_wndMarkBar.SetSizes(CSize(96, 32), CSize(32, 32));
	this->RecalcLayout();
	size = m_wndToolBar.GetButtonSize();
	

#endif

#ifdef ENABLE_ENTLIST	
	//注意list和prop都停靠在一边，系统分配大小的时候先从上到下分配
	if (m_barEntList.m_hWnd!=NULL && !m_barEntList.IsFloating() && !m_barEntProp.IsFloating())
	{//恢复上次的列表窗口大小
		int nSaveHeight = m_barEntList.m_rectSavedDockedRect.Height();
		m_barEntList.GetWindowRect(rect);
		if (nSaveHeight != rect.Height())
		{ 
			rect.bottom = rect.top + nSaveHeight;
			this->ScreenToClient(rect);
			m_barEntList.MoveWindow(rect);
		}
	}
#endif

#ifdef ENABLE_MARK
	//注意Monitor和Mark都停靠在一边，系统分配大小的时候先从上到下分配
	if (m_panelLaserMonitor.m_hWnd != NULL && !m_panelLaserMonitor.IsFloating() && !m_wndMark.IsFloating())
	{//恢复上次的列表窗口大小		
	 	m_wndMark.GetWindowRect(rect);
		if (m_wndMark.m_rectSavedDockedRect.Width() != rect.Width() 
		 || m_wndMark.m_rectSavedDockedRect.Width() != rect.Height()
			|| rect.Width()<m_wndMark.GetMinShowWidth())
		{//恢复上次的列表窗口大小 
			int nWidth = m_wndMark.m_rectSavedDockedRect.Width();
			if (nWidth < m_wndMark.GetMinShowWidth())
			{
				nWidth = m_wndMark.GetMinShowWidth();
			}
			rect.right = rect.left + nWidth;
			rect.bottom = rect.top + m_wndMark.m_rectSavedDockedRect.Height();
			this->ScreenToClient(rect);
			m_wndMark.MoveWindow(rect);
		}
	}
#endif

	RemoveSpacingOfToolBar();
	 
	return TRUE;
}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWndEx::OnSettingChange(uFlags, lpszSection);
	//m_wndOutput.UpdateFonts();
}
#include "Ezcad3View.h"
static BOOL bAutoSaving = FALSE;
void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default	
	if (bAutoSaving)
		return;

	if (nIDEvent == SAVETIMER)
	{
		m_nCurTimer++;

		CSysParam* pSysParam = gf_GetSysParam();
		if (pSysParam!=NULL && pSysParam->GetParamInt(INT_PARAM_AUTOSAVE)!=0 && m_nCurTimer >= pSysParam->GetParamInt(INT_PARAM_AUTOSAVETIME))
		{
			 //自动保存时间到		
				m_nCurTimer = 0;
				PEntMgr pEM = E3_GetEntMgrFromCmdMgr(E3_GetCmdMgr());
				if (pEM != NULL && E3_EntMgrGetModifyFlag(pEM))
				{
					//显示自动保存提示 
					bAutoSaving = TRUE;

					if (E3_GetCmdMgr() != NULL)
					{
						CString strOldTip = E3_CmdMgrShowTip(E3_GetCmdMgr(), QGlobal::gf_Str(_T("AUTOSAVEFILE"), _T("Auto Saving file...")));
						CWaitCursor wait;
						CEzcadDocParam doc;
						doc.m_strSaveFileName = QGlobal::gf_GetWorkPath() + _T("AUTOSAVE.") + QGlobal::gf_Str(_T("FILESUFFIX"), _T("EZD"));
						doc.m_nExportMode = EXPORT_PREIMAGE;
						E3_CmdMgrRunCmd(E3_GetCmdMgr(), _T("PICK"), SUBCMD_PICK_SAVEFILE, (INT_PTR)(&doc));
						E3_CmdMgrShowTip(E3_GetCmdMgr(), strOldTip);
					}
				}
			 
		}
	}

	bAutoSaving = FALSE;
	CFrameWndEx::OnTimer(nIDEvent);
}