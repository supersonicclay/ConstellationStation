//===========================================================================
// DlgConstName.h
//
// CDlgConstName
//   constellation name dialog
//===========================================================================

#ifndef CS_DLGCONSTNAME_H
#define CS_DLGCONSTNAME_H


/////////////////////////////////////////////////////////////////////////////
// CDlgConstName dialog

class CDlgConstName : public CDialog
{
// Construction
public:
	CDlgConstName( CWnd* pParent = NULL );   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgConstName)
	enum { IDD = IDD_CONST_NAME };
	CString	name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgConstName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Operations
public:
	void SetConstName( CString name );

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgConstName)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
