//===========================================================================
//
//
//===========================================================================

#ifndef CS_DLGOPTIONSCONST_H
#define CS_DLGOPTIONSCONST_H


/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsConst dialog

class CDlgOptionsConst : public CDialog
{
// Construction
public:
	CDlgOptionsConst(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsConst)
	enum { IDD = IDD_OPTIONS_CONST };
	BOOL	visible;
	BOOL	labeled;
	//}}AFX_DATA

	color_s normColor;
	color_s selColor;
	color_s activeColor;
	color_s origNormColor;
	color_s origSelColor;
	color_s origActiveColor;

	// Color preview brush
	CBrush colorBrush;

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
	afx_msg void OnConstNormColor();
	afx_msg void OnConstSelColor();
	afx_msg void OnConstActiveColor();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
