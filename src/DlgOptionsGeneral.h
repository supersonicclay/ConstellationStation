//===========================================================================
// DlgOptionsGeneral.h
//
// CDlgOptionsGeneral
//   general options dialog.
//===========================================================================

#ifndef CS_DLGOPTIONSGENERAL_H
#define CS_DLGOPTIONSGENERAL_H


class CDlgOptionsGeneral : public CDialog
{
// Construction
public:
	CDlgOptionsGeneral(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsGeneral)
	enum { IDD = IDD_OPTIONS_GENERAL };
	//}}AFX_DATA


// Methods


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsGeneral)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
