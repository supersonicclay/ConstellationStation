#if !defined(AFX_STARFBAR_H__0C6892C5_5E81_41DF_B7A8_51E5D3EE4B93__INCLUDED_)
#define AFX_STARFBAR_H__0C6892C5_5E81_41DF_B7A8_51E5D3EE4B93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StarfBar.h : header file
//

#include "Starfield.h"

/////////////////////////////////////////////////////////////////////////////
// CStarfBar window

class CStarfBar : public CToolBar
{
// Construction
public:
	CStarfBar();
	BOOL Init( CWnd* pParentWnd );
	BOOL InitDateCtrl();
	BOOL InitTimeCtrl();
	BOOL InitSpeedCtrl();

// Attributes
public:
	CDateTimeCtrl m_Date;
	CDateTimeCtrl m_Time;
	CComboBox m_Speed;

// Operations
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStarfBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStarfBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStarfBar)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARFBAR_H__0C6892C5_5E81_41DF_B7A8_51E5D3EE4B93__INCLUDED_)
