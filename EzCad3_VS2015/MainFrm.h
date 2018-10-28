/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： CMainFrame.h
* 文件标识：
* 摘要：CMainFrame 类的接口
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/

// MainFrm.h : CMainFrame 类的接口
//

#pragma once

 
#include "dlg\DlgSplash.h"

#define ENABLE_PENBOX
 #define ENABLE_MARK
#define ENABLE_ENTLIST
#define ENABLE_ENTLPROP

#ifdef ENABLE_PENBOX
#include "PenBox\PenboxBar.h"
#endif

#ifdef ENABLE_ENTLIST
#include "EntListBar.h"
#endif

#ifdef ENABLE_ENTLPROP
#include "EntPropBar.h"
#endif
#include "LaserMonitor\\LaserMonitorPanel.h"

#ifdef ENABLE_MARK
#include "Mark\MarkWnd.h"
#endif

#include "TipsMessageText.h"
#include "DrawToolBar.h"

#define USE_DRAWTOOL_BAR     //使用垂直工具条
#define USE_TOOLBAR_FIXEDSIZE     //使用固定尺寸工具条


#define SAVETIMER 222





class CQMFCMenuBar : public CMFCMenuBar
{//运行模式会，有时候会死机
public:
	BOOL LoadState(LPCTSTR lpszProfileName, int nIndex, UINT uiID)
	{
		return TRUE;
	}
};

class CQToolBar : public CMFCToolBar
{
public:
#ifdef  USE_TOOLBAR_FIXEDSIZE     //使用固定尺寸工具条
	virtual BOOL LoadState(LPCTSTR lpszProfileName = NULL, int nIndex = -1, UINT uiID = (UINT)-1) 
	{
		BOOL b =  CMFCToolBar::LoadState( lpszProfileName ,  nIndex,  uiID );
		if (m_bLargeIconsAreEnbaled)
		{
			m_bLargeIconsAreEnbaled = FALSE;
			m_sizeCurButton = m_sizeButton;

			m_sizeCurImage = m_sizeImage;
		}
	 	return b;
	}
#endif
	virtual BOOL OnUserToolTip(CMFCToolBarButton* pButton, CString& strTTText) const
	{
		strTTText = GetMessageFullText(pButton->m_nID);
		AfxExtractSubString(strTTText, strTTText, 1, _T('\n'));
		return TRUE;
	} 
};


class CMainFrame : public CFrameWndEx
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:
	BOOL m_bShowMachineParam;
	BOOL m_bHideExtAxis;
	BOOL m_bHideEntEncoder;
	BOOL m_bHideEntIndex;
	BOOL m_bHideEntCCD;
	BOOL m_bHideEntJump;
	BOOL m_bHideShowSol;
	
	CDlgSplash* m_pDlgSplash;
// 操作
public:

#ifdef USE_DRAWTOOL_BAR
	CDrawToolBar  m_wndDraw;
#else
	CQToolBar       m_wndDrawBar;

#endif

#ifdef ENABLE_MARK
	CMarkWnd          m_wndMark;
#endif 

#ifdef ENABLE_ENTLIST
	CEntListBar m_barEntList;
#endif

#ifdef	ENABLE_ENTLPROP
	CEntPropBar m_barEntProp;
#endif

#ifdef ENABLE_PENBOX
	CPenboxBar m_barPenBox;
#endif

	CLaserMonitorPanel m_panelLaserMonitor;
	int m_nCurTimer;
	void InitMenuText();
	virtual BOOL OnShowPopupMenu(CMFCPopupMenu* /*pMenuPopup*/);
	void ShowSnapStr();
	void RemoveSpacingOfToolBar();
// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

	void OnUpdateFrameTitle(BOOL bAddToTitle);
	// For customizing the default messages on the status bar
	virtual void GetMessageString(UINT nID, CString& rMessage) const;

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  
	CQMFCMenuBar m_wndMenuBar; 
	CQToolBar       m_wndToolBar; 

	CQToolBar       m_wndZooml3dBar;
	CQToolBar       m_wnd3dFunBar;
	CQToolBar       m_wndAlignBar;
	CQToolBar       m_wndMarkBar;

	CQToolBar       m_wndPickCmdBar;
	CQToolBar       m_wndNodeCmdBar;

	CMFCStatusBar     m_wndStatusBar;  
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);  
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg LRESULT OnSetMessageString(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileExit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolbar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolbarStatus(CCmdUI* pCmdUI);

	afx_msg void OnViewZoom(); 
	afx_msg void OnUpdateViewZoom(CCmdUI* pCmdUI);
	afx_msg void OnZoomWnd();
	afx_msg void OnUpdateZoomWnd(CCmdUI* pCmdUI);
	afx_msg void OnZoomPan();
	afx_msg void OnUpdateZoomPan(CCmdUI* pCmdUI);
	afx_msg void OnZoomIn();
	afx_msg void OnUpdateZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnZoomAll();
	afx_msg void OnUpdateZoomAll(CCmdUI* pCmdUI);
	afx_msg void OnZoomPick();
	afx_msg void OnUpdateZoomPick(CCmdUI* pCmdUI);
	afx_msg void OnZoomWorkspace();
	afx_msg void OnUpdateZoomWorkspace(CCmdUI* pCmdUI);
	afx_msg void OnZoomOut();
	afx_msg void OnUpdateZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnTestButton();
	afx_msg void OnUpdateTestButton(CCmdUI* pCmdUI);
	afx_msg void OnTestRed();
	afx_msg void OnUpdateTestRed(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI *pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI *pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
	afx_msg void OnEditAddlayer();
	afx_msg void OnUpdateEditAddlayer(CCmdUI *pCmdUI);
	afx_msg void OnEditDellayer();
	afx_msg void OnUpdateEditDellayer(CCmdUI *pCmdUI);
	afx_msg void OnEditCombine();
	afx_msg void OnUpdateEditCombine(CCmdUI *pCmdUI);
	afx_msg void OnEditUncombine();
	afx_msg void OnUpdateEditUncombine(CCmdUI *pCmdUI);
	afx_msg void OnEditGroup();
	afx_msg void OnUpdateEditGroup(CCmdUI *pCmdUI);
	afx_msg void OnEditUngroup();
	afx_msg void OnUpdateEditUngroup(CCmdUI *pCmdUI);
	afx_msg void OnEditUngroupText();
	afx_msg void OnUpdateEditUngroupText(CCmdUI *pCmdUI);

 	afx_msg void OnViewZoom3d();
	afx_msg void OnViewDrawBar();
	afx_msg void OnViewAlignBar(); 
	afx_msg void OnViewEntList();
	afx_msg void OnViewEntProp();
 	afx_msg void OnViewMarkParam();
 	afx_msg void OnViewMarkPanel();
	afx_msg void OnViewLaserMonitor();

	afx_msg void OnUpdateViewZoom3d(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewDrawBar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewAlignBar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewEntList(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewEntProp(CCmdUI* pCmdUI);
 	afx_msg void OnUpdateViewMarkParam(CCmdUI* pCmdUI);
 	afx_msg void OnUpdateViewMarkPanel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewLaserMonitor(CCmdUI* pCmdUI);


	afx_msg void OnDrawBitmap();
	afx_msg void OnUpdateDrawBitmap(CCmdUI *pCmdUI);
	afx_msg void OnDrawCir();
	afx_msg void OnUpdateDrawCir(CCmdUI *pCmdUI);
	afx_msg void OnDrawElp();
	afx_msg void OnUpdateDrawElp(CCmdUI *pCmdUI);
	afx_msg void OnDrawInput();
	afx_msg void OnUpdateDrawInput(CCmdUI *pCmdUI);
	afx_msg void OnDrawLine();
	afx_msg void OnUpdateDrawLine(CCmdUI *pCmdUI);
	afx_msg void OnDrawOutput();
	afx_msg void OnUpdateDrawOutput(CCmdUI *pCmdUI);
	afx_msg void OnDrawPline();
	afx_msg void OnUpdateDrawPline(CCmdUI *pCmdUI);
	afx_msg void OnDrawPoint();
	afx_msg void OnUpdateDrawPoint(CCmdUI *pCmdUI);
	afx_msg void OnDrawPolygon();
	afx_msg void OnUpdateDrawPolygon(CCmdUI *pCmdUI);
	afx_msg void OnDrawRect();
	afx_msg void OnUpdateDrawRect(CCmdUI *pCmdUI);
	afx_msg void OnDrawSpiral();
	afx_msg void OnUpdateDrawSpiral(CCmdUI *pCmdUI);
	afx_msg void OnDrawText();
	afx_msg void OnUpdateDrawText(CCmdUI *pCmdUI);
	afx_msg void OnDrawTime();
	afx_msg void OnUpdateDrawTime(CCmdUI *pCmdUI);
	afx_msg void OnDrawVectorfile();
	afx_msg void OnUpdateDrawVectorfile(CCmdUI *pCmdUI);
	afx_msg void OnDrawPick();
	afx_msg void OnUpdateDrawPick(CCmdUI *pCmdUI);
	afx_msg void OnDrawNode();
	afx_msg void OnUpdateDrawNode(CCmdUI *pCmdUI);
	afx_msg void OnDrawBarcode();
	afx_msg void OnUpdateDrawBarcode(CCmdUI *pCmdUI);
	afx_msg void OnDrawBarcode1();
	afx_msg void OnUpdateDrawBarcode1(CCmdUI *pCmdUI);
	afx_msg void OnDrawBarcode2();
	afx_msg void OnUpdateDrawBarcode2(CCmdUI *pCmdUI);
	afx_msg void OnDrawBarcode3();
	afx_msg void OnUpdateDrawBarcode3(CCmdUI *pCmdUI);
	afx_msg void OnDrawCoor();
	afx_msg void OnUpdateDrawCoor(CCmdUI *pCmdUI);
	afx_msg void OnDrawClose();
	afx_msg void OnUpdateDrawClose(CCmdUI *pCmdUI);
	afx_msg void OnDrawFinish();
	afx_msg void OnUpdateDrawFinish(CCmdUI *pCmdUI);
	afx_msg void OnDrawExtaxis();
	afx_msg void OnUpdateDrawExtaxis(CCmdUI *pCmdUI);
	afx_msg void OnDrawEncoder();
	afx_msg void OnUpdateDrawEncoder(CCmdUI *pCmdUI);
	afx_msg void OnDrawIndex();
	afx_msg void OnUpdateDrawIndex(CCmdUI *pCmdUI);
	afx_msg void OnDrawCCD();
	afx_msg void OnUpdateDrawCCD(CCmdUI *pCmdUI);
	afx_msg void OnDrawInputJump();
	afx_msg void OnUpdateDrawInputJump(CCmdUI *pCmdUI); 
	afx_msg void OnCmdPickAll();
	afx_msg void OnUpdateCmdPickAll(CCmdUI *pCmdUI);
	afx_msg void OnCmdPickInvert();
	afx_msg void OnUpdateCmdPickInvert(CCmdUI *pCmdUI);
	afx_msg void OnCmdPickDel();
	afx_msg void OnUpdateCmdPickDel(CCmdUI *pCmdUI);
	afx_msg void OnCmdPickLock();
	afx_msg void OnUpdateCmdPickLock(CCmdUI *pCmdUI);
	afx_msg void OnCmdPickUnLock();
	afx_msg void OnUpdateCmdPickUnLock(CCmdUI *pCmdUI);
	afx_msg void OnCmdPickUnLockAll();
	afx_msg void OnUpdateCmdPickUnLockAll(CCmdUI *pCmdUI);
	afx_msg void OnCmdPickCen();
	afx_msg void OnUpdateCmdPickCen(CCmdUI *pCmdUI);
	afx_msg void OnCmdPickCenX();
	afx_msg void OnUpdateCmdPickCenX(CCmdUI *pCmdUI);
	afx_msg void OnCmdPickCenY();
	afx_msg void OnUpdateCmdPickCenY(CCmdUI *pCmdUI);
	afx_msg void OnCmdPickMirrorX();
	afx_msg void OnUpdateCmdPickMirrorX(CCmdUI *pCmdUI);
	afx_msg void OnCmdPickMirrorY();
	afx_msg void OnUpdateCmdPickMirrorY(CCmdUI *pCmdUI);
	afx_msg void OnFileSystem();
	afx_msg void OnUpdateFileSystem(CCmdUI *pCmdUI);
	afx_msg void OnFileProjectParam();
	afx_msg void OnUpdateFileProjectParam(CCmdUI *pCmdUI);
	afx_msg void OnEditHatch();
	afx_msg void OnUpdateEditHatch(CCmdUI *pCmdUI);
	afx_msg void OnDeviceParam();
	afx_msg void OnUpdateDeviceParam(CCmdUI *pCmdUI);


	afx_msg void OnZoom3d();
	afx_msg void OnUpdateZoom3d(CCmdUI* pCmdUI);
	afx_msg void OnZoom3dUp();
	afx_msg void OnUpdateZoom3dUp(CCmdUI* pCmdUI);
	afx_msg void OnZoom3dDown();
	afx_msg void OnUpdateZoom3dDown(CCmdUI* pCmdUI);
	afx_msg void OnZoom3dLeft();
	afx_msg void OnUpdateZoom3dLeft(CCmdUI* pCmdUI);
	afx_msg void OnZoom3dRight();
	afx_msg void OnUpdateZoom3dRight(CCmdUI* pCmdUI);
	afx_msg void OnZoom3dFront();
	afx_msg void OnUpdateZoom3dFront(CCmdUI* pCmdUI);
	afx_msg void OnZoom3dBack();
	afx_msg void OnUpdateZoom3dBack(CCmdUI* pCmdUI);
	afx_msg void OnZoom3dIso();
	afx_msg void OnUpdateZoom3dIso(CCmdUI* pCmdUI);
	afx_msg void OnDrawMesh3d();
	afx_msg void OnUpdateDrawMesh3d(CCmdUI* pCmdUI);
	afx_msg void On3DViewWire();
	afx_msg void OnUpdate3DViewWire(CCmdUI* pCmdUI);
	afx_msg void On3DViewRender();
	afx_msg void OnUpdate3DViewRender(CCmdUI* pCmdUI);
	afx_msg void On3DViewRenderLine();
	afx_msg void OnUpdate3DViewRenderLine(CCmdUI* pCmdUI);
	afx_msg void On3DViewHideMesh();
	afx_msg void OnUpdate3DViewHideMesh(CCmdUI* pCmdUI);
	afx_msg void OnFun3dSlice();
	afx_msg void OnUpdateFun3dSlice(CCmdUI* pCmdUI);
	afx_msg void OnFun3dSliceMesh();
	afx_msg void OnUpdateFun3dSliceMesh(CCmdUI* pCmdUI);
	afx_msg void OnFun3dRotateMesh();
	afx_msg void OnUpdateFun3dRotateMesh(CCmdUI* pCmdUI);
	afx_msg void OnFun3dMoveMesh();
	afx_msg void OnUpdateFun3dMoveMesh(CCmdUI* pCmdUI);
	afx_msg void OnFun3dPrj();
	afx_msg void OnUpdateFun3dPrj(CCmdUI* pCmdUI);
	afx_msg void OnFun3dBasicShape();
	afx_msg void OnUpdateFun3dBasicShape(CCmdUI* pCmdUI);
	afx_msg void OnFun3dBmpToMesh();
	afx_msg void OnUpdateFun3dBmpToMesh(CCmdUI* pCmdUI);
	afx_msg void OnFun3dFreePaint();
	afx_msg void OnUpdateFun3dFreePaint(CCmdUI* pCmdUI);
	
	afx_msg void OnModifyArray();
	afx_msg void OnUpdateModifyArray(CCmdUI* pCmdUI);
	afx_msg void OnModifyRotate();
	afx_msg void OnUpdateModifyRotate(CCmdUI* pCmdUI);

	afx_msg void OnUpdateAbout(CCmdUI* pCmdUI); 

	afx_msg void OnViewSnapObject();
	afx_msg void OnUpdateViewSnapObject(CCmdUI *pCmdUI);
	afx_msg void OnViewSnapMeshVertex();
	afx_msg void OnUpdateViewSnapMeshVertex(CCmdUI *pCmdUI);
	afx_msg void OnViewSnapGL();
	afx_msg void OnUpdateViewSnapGL(CCmdUI *pCmdUI);
	afx_msg void OnViewSnapGrid();
	afx_msg void OnUpdateViewSnapGrid(CCmdUI *pCmdUI);

	afx_msg void OnViewShowRuler();
	afx_msg void OnUpdateViewShowRuler(CCmdUI *pCmdUI);
	afx_msg void OnViewShowGrid();
	afx_msg void OnUpdateViewShowGrid(CCmdUI *pCmdUI);

	afx_msg void OnArrayText();
	afx_msg void OnUpdateArrayText(CCmdUI *pCmdUI);
	afx_msg void OnOffsetCurve();
	afx_msg void OnUpdateOffsetCurve(CCmdUI *pCmdUI);


	afx_msg void OnCmdNodeAdd();
	afx_msg void OnUpdateCmdNodeAdd(CCmdUI *pCmdUI);
	afx_msg void OnCmdNodeAlign();
	afx_msg void OnUpdateCmdNodeAlign(CCmdUI *pCmdUI);
	afx_msg void OnCmdNodeClose();
	afx_msg void OnUpdateCmdNodeClose(CCmdUI *pCmdUI);
	afx_msg void OnCmdNodeDel();
	afx_msg void OnUpdateCmdNodeDel(CCmdUI *pCmdUI);
	afx_msg void OnCmdNodeSepa();
	afx_msg void OnUpdateCmdNodeSepa(CCmdUI *pCmdUI);
	afx_msg void OnCmdNodeSharp();
	afx_msg void OnUpdateCmdNodeSharp(CCmdUI *pCmdUI);
	afx_msg void OnCmdNodeSmooth();
	afx_msg void OnUpdateCmdNodeSmooth(CCmdUI *pCmdUI);
	afx_msg void OnCmdNodeToarc();
	afx_msg void OnUpdateCmdNodeToarc(CCmdUI *pCmdUI);
	afx_msg void OnCmdNodeTobez();
	afx_msg void OnUpdateCmdNodeTobez(CCmdUI *pCmdUI);
	afx_msg void OnCmdNodeToline();
	afx_msg void OnUpdateCmdNodeToline(CCmdUI *pCmdUI);
	afx_msg void OnCmdNodeUnite();
	afx_msg void OnUpdateCmdNodeUnite(CCmdUI *pCmdUI);
	afx_msg void OnCmdNodeDir();
	afx_msg void OnUpdateCmdNodeDir(CCmdUI *pCmdUI); 
	afx_msg void OnCmdNodeSys();
	afx_msg void OnUpdateCmdNodeSys(CCmdUI *pCmdUI);
	afx_msg void OnCmdLaserProcess();
	afx_msg void OnUpdateCmdLaserProcess(CCmdUI *pCmdUI);
	afx_msg void OnCmdDistortionWeld();
	afx_msg void OnUpdateCmdDistortionWeld(CCmdUI *pCmdUI);
	afx_msg void OnCmdDistortionTrim();
	afx_msg void OnUpdateCmdDistortionTrim(CCmdUI *pCmdUI);
	afx_msg void OnCmdDistortionInter();
	afx_msg void OnUpdateCmdDistortionInter(CCmdUI *pCmdUI);
	afx_msg void OnCmdToCurve();
	afx_msg void OnUpdateCmdToCurve(CCmdUI *pCmdUI);
	
	afx_msg void OnAlignLeft();
	afx_msg void OnUpdateAlignLeft(CCmdUI *pCmdUI);
	afx_msg void OnAlignHCenter();
	afx_msg void OnUpdateAlignHCenter(CCmdUI *pCmdUI);
	afx_msg void OnAlignRight();
	afx_msg void OnUpdateAlignRight(CCmdUI *pCmdUI);
	
	afx_msg void OnAlignTop();
	afx_msg void OnUpdateAlignTop(CCmdUI *pCmdUI);
	afx_msg void OnAlignVCenter();
	afx_msg void OnUpdateAlignVCenter(CCmdUI *pCmdUI);
	afx_msg void OnAlignBottom();
	afx_msg void OnUpdateAlignBottom(CCmdUI *pCmdUI);

	afx_msg void OnAlignCenter();
	afx_msg void OnUpdateAlignCenter(CCmdUI *pCmdUI);
	afx_msg void OnCmdPickByPen();
	afx_msg void OnUpdateCmdPickByPen(CCmdUI *pCmdUI);

	afx_msg void OnTrim();
	afx_msg void OnUpdateTrim(CCmdUI *pCmdUI);
	
	afx_msg void OnModifyCurveConnect();
	afx_msg void OnUpdateModifyCurveConnect(CCmdUI *pCmdUI);
	afx_msg void OnModifyBreakCross();
	afx_msg void OnUpdateModifyBreakCross(CCmdUI *pCmdUI);
	afx_msg void OnModifyMeshMergeCloseVertex();
	afx_msg void OnUpdateModifyMeshMergeCloseVertex(CCmdUI *pCmdUI);
	afx_msg void OnModifyResort();
	afx_msg void OnUpdateModifyResort(CCmdUI *pCmdUI); 
	afx_msg void OnSortByX();
	afx_msg void OnUpdateSortByX(CCmdUI *pCmdUI);
	afx_msg void OnSortByY();
	afx_msg void OnUpdateSortByY(CCmdUI *pCmdUI);
	afx_msg void OnSortReverse();
	afx_msg void OnUpdateSortReverse(CCmdUI *pCmdUI);
	afx_msg void OnSortFinish();
	afx_msg void OnUpdateSortFinish(CCmdUI *pCmdUI);
	afx_msg void OnCurveToPoints();
	afx_msg void OnUpdateCurveToPoints(CCmdUI *pCmdUI);
	afx_msg void OnDrawGuideLineBox();
	afx_msg void OnUpdateDrawGuideLineBox(CCmdUI *pCmdUI);
	afx_msg void OnCameraSet();
	afx_msg void OnUpdateCameraSet(CCmdUI *pCmdUI);
	LRESULT OnUserChangeStatusText(WPARAM wParam, LPARAM lParam);
	LRESULT OnUserRunNode(WPARAM wParam, LPARAM lParam);
	LRESULT OnUserRun3DView(WPARAM wParam, LPARAM lParam);
		afx_msg void OnClose(); 
		afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows(); 
};


