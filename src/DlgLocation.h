//===========================================================================
// DlgLocation.h
//
// CDlgLocation
//   location dialog.
//===========================================================================

#ifndef CS_DLGLOCATION_H
#define CS_DLGLOCATION_H


class CDlgLocation : public CDialog
{
// Construction
public:
	CDlgLocation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLocation)
	enum { IDD = IDD_LOCATION };
	CComboBox	locationCombo;
	//}}AFX_DATA

	std::vector<location_s> locationsVec;

	location_s location;

// Methods
	void LoadLocations();
	void GetCurrentLocation();
	BOOL Search( CString t );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLocation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLocation)
	afx_msg void OnLocationSearch();
	afx_msg void OnLocationSetHome();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelChangeLocationCombo();
	afx_msg void OnChangeLocationLatitudeD();
	afx_msg void OnChangeLocationLatitudeM();
	afx_msg void OnChangeLocationLongitudeD();
	afx_msg void OnChangeLocationLongitudeM();
	afx_msg void OnLocationE();
	afx_msg void OnLocationW();
	afx_msg void OnLocationN();
	afx_msg void OnLocationS();
	afx_msg void OnChangeLocationTimezone();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
