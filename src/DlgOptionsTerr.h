//===========================================================================
// DlgOptionsTerr.h
//
// CDlgOptionsTerr
//   terrain options dialog.
//===========================================================================

#ifndef CS_DLGOPTIONSTERR_H
#define CS_DLGOPTIONSTERR_H


class CDlgOptionsTerr : public CDialog
{
// Construction
public:
	CDlgOptionsTerr( CWnd* pParent = NULL );

// Dialog Data
	//{{AFX_DATA(CDlgOptionsTerr)
	enum { IDD = IDD_OPTIONS_TERR };
	CEdit	colorPrev;
	BOOL	visible;
	BOOL	textured;
	int		roughnessX100;
	CSliderCtrl	roughnessSlider;
	CListBox	seasonsListBox;
	//}}AFX_DATA

	season_e season;
	color_s winColor;
	color_s sprColor;
	color_s sumColor;
	color_s falColor;

	int origRoughnessX100;
	season_e origSeason;
	color_s origWinColor;
	color_s origSprColor;
	color_s origSumColor;
	color_s origFalColor;

	// Brush for color preview
	CBrush colorBrush;


// Methods
	void InitOptions();
	void UpdateRoughnessTxt();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsTerr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsTerr)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTerrNew();
	afx_msg void OnTerrColor();
	afx_msg void OnSeasonChange();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTerrTextured();
	afx_msg void OnTerrDefaults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
