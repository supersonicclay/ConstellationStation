//===========================================================================
// DlgStarInfo.h
//
// CDlgStarInfo
//   star info dialog.
//===========================================================================

#ifndef CS_DLGSTARINFO_H
#define CS_DLGSTARINFO_H


class CDlgStarInfo : public CDialog
{
// Construction
public:
	CDlgStarInfo( CDataStar* s, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgStarInfo)
	enum { IDD = IDD_STARINFO };
	//}}AFX_DATA

	CDataStar* star;


// Methods


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgStarInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgStarInfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
