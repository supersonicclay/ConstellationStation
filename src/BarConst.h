//===========================================================================
// BarConst.h
//
// CBarConst
//   constellation toolbar
//===========================================================================

#ifndef CS_BARCONST_H
#define CS_BARCONST_H


#include "Starfield.h"

/////////////////////////////////////////////////////////////////////////////
// CBarConst window

class CBarConst : public CToolBar
{
// Construction
public:
	CBarConst();
	BOOL Init( CWnd* pParentWnd );
	BOOL InitList();

// Attributes
public:
	CComboBox constList;

// Operations
public:

	void AddConst( CString &str );
	void DeleteConst();

	void UpdateList();

	CString GetCurConst() const;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBarConst)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBarConst();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBarConst)
	afx_msg void OnConstSelChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
