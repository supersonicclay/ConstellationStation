// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__87C7179B_70DA_4CF0_B078_C3215E22A606__INCLUDED_)
#define AFX_MAINFRM_H__87C7179B_70DA_4CF0_B078_C3215E22A606__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Starfield.h"
#include "Terrain.h"
#include "ConStationView.h"

#include "ConstBar.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE( CMainFrame )

// Attributes
public:



// Operations
public:
	CConStationView* GetView() const;
	CStarfield* GetStarfield() const;
	CTerrain* GetTerrain() const;

	StateType GetState() const;
	void SetState( StateType state ) const;

	void UpdateList();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CConstBar	m_wndConstBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnConstListCloseUp();
	afx_msg void OnConstAdd();
	afx_msg void OnConstDelete();
	afx_msg void OnConstRename();
	afx_msg void OnConstHide();
	afx_msg void OnConstAddLine();
	afx_msg void OnConstAddPoly();
	afx_msg void OnConstDeleteLine();
	afx_msg void OnStarfRotate();
	afx_msg void OnUpdateConstList(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstAdd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstRename(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstHide(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstAddLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstAddPoly(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstDeleteLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStarfRotate(CCmdUI* pCmdUI);
	afx_msg void OnShowHide();
	afx_msg void OnViewHideAll();
	afx_msg void OnViewShowAll();
	afx_msg void OnOptionsTerrain();
	afx_msg void OnOptionsLocation();
	afx_msg void OnUpdateOptionsTerrain(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsLocation(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__87C7179B_70DA_4CF0_B078_C3215E22A606__INCLUDED_)
