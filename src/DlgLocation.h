#if !defined(AFX_DLGLOCATION_H__0BC7A832_E07C_4582_818B_918B61B622D7__INCLUDED_)
#define AFX_DLGLOCATION_H__0BC7A832_E07C_4582_818B_918B61B622D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLocation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLocation dialog

class CDlgLocation : public CDialog
{
// Construction
public:
	CDlgLocation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLocation)
	enum { IDD = IDD_LOCATION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


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
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOCATION_H__0BC7A832_E07C_4582_818B_918B61B622D7__INCLUDED_)
