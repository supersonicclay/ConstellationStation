// sdindv.h : main header file for the SDINDV application
//

#if !defined(AFX_SDINDV_H__8E3BEB39_F6D6_4579_A9E3_A8A3D075583A__INCLUDED_)
#define AFX_SDINDV_H__8E3BEB39_F6D6_4579_A9E3_A8A3D075583A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSdindvApp:
// See sdindv.cpp for the implementation of this class
//

class CSdindvApp : public CWinApp
{
public:
	CSdindvApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSdindvApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CSdindvApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDINDV_H__8E3BEB39_F6D6_4579_A9E3_A8A3D075583A__INCLUDED_)
