//===========================================================================
// DlgOptionsConst.h
//
// CDlgOptionsCosnt
//   constellation options dialog.
//===========================================================================

#ifndef CS_DLGOPTIONSCONST_H
#define CS_DLGOPTIONSCONST_H


class CDlgOptionsConst : public CDialog
{
// Construction
public:
	CDlgOptionsConst(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsConst)
	enum { IDD = IDD_OPTIONS_CONST };
	CComboBox	lineWidthControl;
	BOOL	visible;
	BOOL	daylight;
	BOOL	labeled;
	BOOL	starsColored;
	int		lineWidth;
	//}}AFX_DATA

	color_s normColor;
	color_s selColor;
	color_s activeColor;
	color_s starColor;
	color_s origNormColor;
	color_s origSelColor;
	color_s origActiveColor;
	color_s origStarColor;

	// Color preview brush
	CBrush colorBrush;


// Methods
	void InitOptions();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsConst)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsConst)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnConstNormColor();
	afx_msg void OnConstSelColor();
	afx_msg void OnConstActiveColor();
	afx_msg void OnConstStarColor();
	afx_msg void OnConstStarsColored();
	afx_msg void OnConstDefaults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
