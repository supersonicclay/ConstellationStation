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
	CDateTimeCtrl	utTime;
	CDateTimeCtrl	utDate;
	CDateTimeCtrl	ltTime;
	CDateTimeCtrl	ltDate;
	//}}AFX_DATA

	COleDateTime lt;
	COleDateTime ut;
	double julian;
	float tz;
	BOOL dst;


// Methods
	void InitOptions();
	void UpdateJulianText();



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
	virtual BOOL OnInitDialog();
	afx_msg void OnDateTimeChangeLTDate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDateTimeChangeLTTime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDateTimeChangeUTDate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDateTimeChangeUTTime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimeCalc();
	afx_msg void OnTimeDST();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
