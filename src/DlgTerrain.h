#if !defined(AFX_DLGTERRAIN_H__E9B06D25_EB9A_4544_AE71_FD1BDDA3B920__INCLUDED_)
#define AFX_DLGTERRAIN_H__E9B06D25_EB9A_4544_AE71_FD1BDDA3B920__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Terrain.h"

// CDlgTerrain.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CDlgTerrain dialog

class CDlgTerrain : public CDialog
{
public:
	CDlgTerrain( float roughness_, color_s color_, CWnd* pParent = NULL );

// Dialog Data
	//{{AFX_DATA(CDlgTerrain)
	enum { IDD = IDD_TERRAIN };
	//}}AFX_DATA

	int		roughness;
	color_s color;

	CSliderCtrl	roughnessSlider;
	CString	roughnessTxt;

	BOOL needsUpdate;
	int lastRoughness;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTerrain)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTerrain)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnNewTerrain();
	afx_msg void OnColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTERRAIN_H__E9B06D25_EB9A_4544_AE71_FD1BDDA3B920__INCLUDED_)
