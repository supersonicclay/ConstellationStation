#if !defined(AFX_SHOWHIDEDLG_H__F1F9C38A_0D99_4413_8314_818EF5B90CE7__INCLUDED_)
#define AFX_SHOWHIDEDLG_H__F1F9C38A_0D99_4413_8314_818EF5B90CE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowHideDlg.h : header file
//

#include "Starfield.h"
#include "Constellation.h"


/////////////////////////////////////////////////////////////////////////////
// CShowHideDlg dialog

class CShowHideDlg : public CDialog
{
// Construction
public:
	CShowHideDlg(CWnd* pParent = NULL);   // standard constructor

	CStarfield* GetStarfield() const;

private:
// Members
	CListBox m_List;
	CConstellation* constellations;
	int numConstellations;
	int numCurConstellation;

// Dialog Data
	//{{AFX_DATA(CShowHideDlg)
	enum { IDD = IDD_SHOW_HIDE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowHideDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL



// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShowHideDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeConstList();
	afx_msg void OnShowAll();
	afx_msg void OnHideAll();
	afx_msg void OnInvert();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWHIDEDLG_H__F1F9C38A_0D99_4413_8314_818EF5B90CE7__INCLUDED_)
