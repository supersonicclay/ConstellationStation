#if !defined(AFX_DLGTIME_H__E3FCD0DF_AE70_412B_AA11_BD6D87FE715C__INCLUDED_)
#define AFX_DLGTIME_H__E3FCD0DF_AE70_412B_AA11_BD6D87FE715C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTime dialog

class CDlgTime : public CDialog
{
// Construction
public:
	CDlgTime(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTime)
	enum { IDD = IDD_TIME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


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
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTIME_H__E3FCD0DF_AE70_412B_AA11_BD6D87FE715C__INCLUDED_)
