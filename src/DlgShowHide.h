//===========================================================================
// DlgShowHide.h
//
// CDlgShowHide
//   show / hide list dialog
//===========================================================================

#ifndef CS_DLGSHOWHIDE_H
#define CS_DLGSHOWHIDE_H


#include "Starfield.h"
#include "Constellation.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgShowHide dialog

class CDlgShowHide : public CDialog
{
// Construction
public:
	CDlgShowHide( CWnd* pParent = NULL );
	~CDlgShowHide();

private:
// Members
	CListBox list;

// Dialog Data
	//{{AFX_DATA(CDlgShowHide)
	enum { IDD = IDD_SHOW_HIDE };
	//}}AFX_DATA


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
	afx_msg void OnSelchangeConstList();
	afx_msg void OnShowAll();
	afx_msg void OnHideAll();
	afx_msg void OnInvert();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
