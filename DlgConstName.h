#if !defined(AFX_DLGCONSTNAME_H__387271FD_AFF9_4627_8023_2303D331FA41__INCLUDED_)
#define AFX_DLGCONSTNAME_H__387271FD_AFF9_4627_8023_2303D331FA41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CDlgConstName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgConstName dialog

class CDlgConstName : public CDialog
{
// Construction
public:
	CDlgConstName( CWnd* pParent = NULL );   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgConstName)
	enum { IDD = IDD_CONST_NAME };
	CString	m_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgConstName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Operations
public:
	void SetConstName( CString name );

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgConstName)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONSTNAME_H__387271FD_AFF9_4627_8023_2303D331FA41__INCLUDED_)
