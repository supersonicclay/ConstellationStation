//===========================================================================
// DlgOptionsColor.h
//
// CDlgOptionsColor
//   color options dialog.
//===========================================================================

#ifndef CS_DLGOPTIONSCOLOR_H
#define CS_DLGOPTIONSCOLOR_H


class CDlgOptionsColor : public CDialog
{
// Construction
public:
	CDlgOptionsColor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsColor)
	enum { IDD = IDD_OPTIONS_COLOR };
	BOOL	starColored;
	//}}AFX_DATA

	color_s constLabels;
	color_s constSelLabels;
	color_s constNorm;
	color_s constSel;
	color_s constActive;
	color_s starLabels;
	color_s constStar;
	color_s dirLabels;

	color_s origConstLabels;
	color_s origConstSelLabels;
	color_s origConstNorm;
	color_s origConstSel;
	color_s origConstActive;
	color_s origStarLabels;
	color_s origConstStar;
	color_s origDirLabels;

	// Color preview brush
	CBrush colorBrush;


// Methods
	void InitOptions();

	color_s SelectColor( color_s& origColor );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsColor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsColor)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnColorConstLabels();
	afx_msg void OnColorConstSelLabels();
	afx_msg void OnColorConstNorm();
	afx_msg void OnColorConstSel();
	afx_msg void OnColorConstActive();
	afx_msg void OnColorStarLabels();
	afx_msg void OnColorStarConst();
	afx_msg void OnColorDirLabels();
	afx_msg void OnColorDefaults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
