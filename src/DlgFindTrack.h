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
	void FindCurrentlyTracked();
	void FillRADec( ra_s& ra, dec_s& dec );
	void FindConst();
	void TrackConst();
	void FindStar();
	void TrackStar();
	void FindRADec();
	void TrackRADec();


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
	afx_msg void OnFind();
	afx_msg void OnTrack();
	afx_msg void OnEnableConst();
	afx_msg void OnEnableStar();
	afx_msg void OnEnableRADec();
	afx_msg void OnChangeRAH();
	afx_msg void OnChangeRAM();
	afx_msg void OnChangeDecD();
	afx_msg void OnChangeDecM();
	afx_msg void OnStopTracking();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
