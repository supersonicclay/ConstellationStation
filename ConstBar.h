#if !defined(AFX_CONSTBAR_H__0C6892C5_5E81_41DF_B7A8_51E5D3EE4B93__INCLUDED_)
#define AFX_CONSTBAR_H__0C6892C5_5E81_41DF_B7A8_51E5D3EE4B93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConstBar.h : header file
//

#include "Starfield.h"

/////////////////////////////////////////////////////////////////////////////
// CConstBar window

class CConstBar : public CToolBar
{
// Construction
public:
	CConstBar();
	BOOL Init(CWnd* pParentWnd);
	BOOL InitList();

// Attributes
public:
	CComboBox m_List;

// Operations
public:

	void AddConst(CString &str);
	void DeleteConst();

	void UpdateList(CString* names, int numConstellations, int numCurrent);
	void ClearList();


	CString GetCurConst() const;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConstBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConstBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CConstBar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSTBAR_H__0C6892C5_5E81_41DF_B7A8_51E5D3EE4B93__INCLUDED_)
