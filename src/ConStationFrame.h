// ConStationFrame.h : interface of the CConStationFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONSTATIONFRAME_H__87C7179B_70DA_4CF0_B078_C3215E22A606__INCLUDED_)
#define AFX_CONSTATIONFRAME_H__87C7179B_70DA_4CF0_B078_C3215E22A606__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Starfield.h"
#include "Terrain.h"
#include "ConStationView.h"

#include "StarfBar.h"
#include "ConstBar.h"

class CConStationFrame : public CFrameWnd
{
// Construction	
public:
	CConStationFrame();

// Attributes
public:


// Operations
public:
	CConStationView* GetView();

	void UpdateList();


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

protected:
	CConStationView m_wndView;
	CStatusBar      m_wndStatusBar;
	CStarfBar       m_wndStarfBar;
	CConstBar       m_wndConstBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CConStationFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnConstListCloseUp();
	afx_msg void OnConstAdd();
	afx_msg void OnConstDelete();
	afx_msg void OnConstRename();
	afx_msg void OnConstHide();
	afx_msg void OnConstAddLine();
	afx_msg void OnConstAddPoly();
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
	afx_msg void OnUpdateConstAddPoly(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstDeleteLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStarfRotate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstHideAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstShowAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstShowHide(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__87C7179B_70DA_4CF0_B078_C3215E22A606__INCLUDED_)
