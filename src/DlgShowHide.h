//===========================================================================
// DlgShowHide.h
//
// CDlgShowHide
//   show / hide constellation list dialog.
//===========================================================================

#ifndef CS_DLGSHOWHIDE_H
#define CS_DLGSHOWHIDE_H


class CDlgShowHide : public CDialog
{
// Construction
public:
	CDlgShowHide( CWnd* pParent = NULL );
	~CDlgShowHide();


// Dialog Data
	//{{AFX_DATA(CDlgShowHide)
	enum { IDD = IDD_SHOW_HIDE };
	CListBox list;
	//}}AFX_DATA


// Methods


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgShowHide)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgShowHide)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelChange();
	afx_msg void OnShowAll();
	afx_msg void OnHideAll();
	afx_msg void OnInvert();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
