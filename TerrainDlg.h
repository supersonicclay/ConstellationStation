#if !defined(AFX_TERRAINDLG_H__E9B06D25_EB9A_4544_AE71_FD1BDDA3B920__INCLUDED_)
#define AFX_TERRAINDLG_H__E9B06D25_EB9A_4544_AE71_FD1BDDA3B920__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Terrain.h"

// TerrainDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTerrainDlg dialog

class CTerrainDlg : public CDialog
{
// Construction
public:
	CTerrainDlg( int roughness, CWnd* pParent = NULL );

	CTerrain* GetTerrain() const;

// Dialog Data
	//{{AFX_DATA(CTerrainDlg)
	enum { IDD = IDD_TERRAIN };
	CSliderCtrl	m_RoughnessSlider;
	int		m_Roughness;
	CString	m_RoughnessTxt;
	//}}AFX_DATA

	BOOL needsUpdate;
	int lastRoughness;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTerrainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTerrainDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnNewTerrain();
	afx_msg void OnColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TERRAINDLG_H__E9B06D25_EB9A_4544_AE71_FD1BDDA3B920__INCLUDED_)
