//===========================================================================
// DlgTime.h
//
// CDlgTime
//   time dialog.
//===========================================================================

#ifndef CS_DLGTIME_H
#define CS_DLGTIME_H


class CDlgTime : public CDialog
{
// Construction
public:
	CDlgTime(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTime)
	enum { IDD = IDD_TIME };
	//}}AFX_DATA


// Methods


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTime)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
