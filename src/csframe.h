//===========================================================================
// CSFrame.h
//
// CCSFrame
//   handles (forwards) most non-view related commands and messages.
//===========================================================================

#ifndef CS_CSFRAME_H
#define CS_CSFRAME_H

#include "CSView.h"

#include "BarStarf.h"
#include "BarConst.h"


class CCSFrame : public CFrameWnd
{
// Construction	
public:
	CCSFrame();


// Attributes
protected:

	// Child view
	CCSView view;

	// Toolbars
	CStatusBar statusBar;
	CBarStarf  starfBar;
	CBarConst  constBar;


// Methods
public:
	CCSView* GetView();

	CBarConst* GetConstBar();
	CBarStarf* GetStarfBar();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSFrame)
	public:
	virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCSFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CCSFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnClose();
	afx_msg void OnAppAbout();
	afx_msg void OnStarfNewActual();
	afx_msg void OnStarfNewRandom();
	afx_msg void OnStarfOpen();
	afx_msg void OnStarfSave();
	afx_msg void OnStarfSaveAs();
	afx_msg void OnStarfRotate();
	afx_msg void OnStarsToggle();
	afx_msg void OnConstAdd();
	afx_msg void OnConstDelete();
	afx_msg void OnConstRename();
	afx_msg void OnConstAddLine();
	afx_msg void OnConstDeleteLine();
	afx_msg void OnConstToggle();
	afx_msg void OnConstLinesToggle();
	afx_msg void OnTerrNew();
	afx_msg void OnSunToggle();
	afx_msg void OnSunshineToggle();
	afx_msg void OnTerrToggle();
	afx_msg void OnOptionsGeneral();
	afx_msg void OnOptionsTime();
	afx_msg void OnOptionsLocation();
	afx_msg void OnOptionsStar();
	afx_msg void OnOptionsConst();
	afx_msg void OnOptionsSun();
	afx_msg void OnOptionsTerr();
	afx_msg void OnOptionsColor();
	afx_msg void OnOptionsText();
	afx_msg void OnViewFindTrack();
	afx_msg void OnAnimPrev();
	afx_msg void OnAnimRev();
	afx_msg void OnAnimPause();
	afx_msg void OnAnimPlay();
	afx_msg void OnAnimNext();
	afx_msg void OnUpdateStarfRotate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStarsToggle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstList(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstAdd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstRename(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstAddLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstDeleteLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstToggle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstLinesToggle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTerrToggle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSunToggle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSunshineToggle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewFindTrack(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAnimPrev(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAnimRev(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAnimPause(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAnimPlay(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAnimNext(CCmdUI* pCmdUI);
	afx_msg void OnPopupConstCenter();
	afx_msg void OnPopupConstTrack();
	afx_msg void OnPopupConstInfo();
	afx_msg void OnPopupStarCenter();
	afx_msg void OnPopupStarTrack();
	afx_msg void OnPopupStarInfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
