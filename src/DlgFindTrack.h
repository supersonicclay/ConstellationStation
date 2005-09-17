//===========================================================================
// DlgFindTrack.h
//
// CDlgFindTrack
//   find and track dialog.
//===========================================================================

#ifndef CS_DLGFINDTRACK_H
#define CS_DLGFINDTRACK_H


class CDlgFindTrack : public CDialog
{
// Construction
public:
	CDlgFindTrack(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFindTrack)
	enum { IDD = IDD_FINDTRACK };
	CButton	stopTrackingButton;
	CEdit	raSDControl;
	CEdit	decSDControl;
	CEdit	raSControl;
	CEdit	raMControl;
	CEdit	raHControl;
	CEdit	decSControl;
	CEdit	decMControl;
	CEdit	decDControl;
	CComboBox	starControl;
	CComboBox	constControl;
	//}}AFX_DATA


// Methods


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFindTrack)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFindTrack)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindConst();
	afx_msg void OnTrackConst();
	afx_msg void OnFindStar();
	afx_msg void OnTrackStar();
	afx_msg void OnFindRaDec();
	afx_msg void OnTrackRaDec();
	afx_msg void OnStopTracking();
	afx_msg void OnChangeRAH();
	afx_msg void OnChangeRAM();
	afx_msg void OnChangeRAS();
	afx_msg void OnChangeRASD();
	afx_msg void OnChangeDecD();
	afx_msg void OnChangeDecM();
	afx_msg void OnChangeDecS();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
