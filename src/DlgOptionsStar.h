//===========================================================================
// DlgOptionsStar.h
//
// CDlgOptionsStar
//   star options dialog.
//===========================================================================

#ifndef CS_DLGOPTIONSSTAR_H
#define CS_DLGOPTIONSSTAR_H


class CDlgOptionsStar : public CDialog
{
// Construction
public:
	CDlgOptionsStar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsStar)
	enum { IDD = IDD_OPTIONS_STAR };
	BOOL	visible;
	BOOL	daylight;
	BOOL	labeled;
	BOOL	textured;
	BOOL	colored;
	int		limMagX10;
	int		size;
	int		sContrast;
	int		cContrast;
	CSliderCtrl	sizeSlider;
	CSliderCtrl	sContrastSlider;
	CSliderCtrl cContrastSlider;
	CSliderCtrl	limMagSlider;
	//}}AFX_DATA

	int origLimMagX10;


// Methods
	void InitOptions();
	void UpdateLimMagTxt();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsStar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsStar)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnStarsDefaults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
