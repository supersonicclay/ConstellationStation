//===========================================================================
// DlgOptionsConst.h
//
// CDlgOptionsConst
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
	int		lineWidth;
	//}}AFX_DATA


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
	afx_msg void OnConstDefaults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
