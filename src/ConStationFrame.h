//===========================================================================
// ConStationFrame.h
//
// CConStationFrame
///   contains all toolbars and dialogs. Forwards commands.
//===========================================================================

#ifndef CS_CONSTATIONFRAME_H
#define CS_CONSTATIONFRAME_H


#include "Starfield.h"
#include "Terrain.h"
#include "ConStationView.h"

#include "BarStarf.h"
#include "BarConst.h"

class CConStationFrame : public CFrameWnd
{
// Construction	
public:
	CConStationFrame();

// Attributes
protected:

	// Child view
	CConStationView view;

	// Toolbars
	CStatusBar      statusBar;
	CBarStarf       starfBar;
	CBarConst       constBar;

// Operations
public:
	CConStationView* GetView();

	CBarConst* GetConstBar();
	CBarStarf* GetStarfBar();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConStationFrame)
	public:
	virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConStationFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CConStationFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnConstAdd();
	afx_msg void OnConstDelete();
	afx_msg void OnConstRename();
	afx_msg void OnConstHide();
	afx_msg void OnConstAddLine();
	afx_msg void OnConstDeleteLine();
	afx_msg void OnConstShowHide();
	afx_msg void OnConstHideAll();
	afx_msg void OnConstShowAll();
	afx_msg void OnStarfRotate();
	afx_msg void OnTerrainNew();
	afx_msg void OnOptionsTerrain();
	afx_msg void OnOptionsLocation();
	afx_msg void OnUpdateConstList(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstAdd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstRename(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstHide(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstAddLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstDeleteLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStarfRotate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstHideAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstShowAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstShowHide(CCmdUI* pCmdUI);
	afx_msg void OnOptionsTime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
