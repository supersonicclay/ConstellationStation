//===========================================================================
// DlgOptionsText.h
//
// CDlgOptionsText
//   text options dialog.
//===========================================================================

#ifndef CS_DLGOPTIONSTEXT_H
#define CS_DLGOPTIONSTEXT_H


class CDlgOptionsText : public CDialog
{
// Construction
public:
	CDlgOptionsText(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsText)
	enum { IDD = IDD_OPTIONS_TEXT };
	//}}AFX_DATA

	LOGFONT constFont, origConstFont;
	LOGFONT starFont, origStarFont;
	LOGFONT dirFont, origDirFont;


// Methods
	void InitOptions();
	BOOL SelectFont( LOGFONT* f );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsText)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsText)
	virtual BOOL OnInitDialog();
	afx_msg void OnTextConstFont();
	afx_msg void OnTextStarFont();
	afx_msg void OnTextDirFont();
	afx_msg void OnTextDefaults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
