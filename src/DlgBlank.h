//===========================================================================
// DlgBlank.h
//
// CDlgBlank
//   blank dialog.
//===========================================================================

#ifndef CS_DLGBLANK_H
#define CS_DLGBLANK_H


class CDlgBlank : public CDialog
{
// Construction
public:
	CDlgBlank(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBlank)
	enum { IDD = IDD_BLANK };
	//}}AFX_DATA


// Methods


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBlank)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBlank)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
