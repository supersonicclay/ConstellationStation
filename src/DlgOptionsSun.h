//===========================================================================
// DlgOptionsSun.h
//
// CDlgOptionsSun
//   sun options dialog.
//===========================================================================

#ifndef CS_DLGOPTIONSSUN_H
#define CS_DLGOPTIONSSUN_H


class CDlgOptionsSun : public CDialog
{
// Construction
public:
	CDlgOptionsSun(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsSun)
	enum { IDD = IDD_OPTIONS_SUN };
	BOOL	visible;
	BOOL	sunshine;
	//}}AFX_DATA


// Methods
	void InitOptions();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsSun)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsSun)
	virtual BOOL OnInitDialog();
	afx_msg void OnSunVisible();
	afx_msg void OnSunDefaults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
