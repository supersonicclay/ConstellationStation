//===========================================================================
// BarStarf.h
//
// CBarStarf
//   starfield toolbar.
//===========================================================================

#ifndef CS_BARSTARF_H
#define CS_BARSTARF_H


class CBarStarf : public CToolBar
{
// Construction
public:
	CBarStarf();
	BOOL Init( CWnd* pParentWnd );
	BOOL InitDateCtrl();
	BOOL InitTimeCtrl();
	BOOL InitSpeedCtrl();


// Attributes
public:
	CDateTimeCtrl date;
	CDateTimeCtrl time;
	CComboBox speed;


// Methods
public:
	void UpdateTime();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBarStarf)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBarStarf();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBarStarf)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDateChange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimeChange(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
