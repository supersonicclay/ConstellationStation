//===========================================================================
// CSApp.h
//
// CCSApp
//   main header file for Constellation Station application.
//===========================================================================

#ifndef CS_CSAPP_H
#define CS_CSAPP_H

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

#include "CSFrame.h"


class CCSApp : public CWinApp
{
// Construction / Destruction
public:
	CCSApp();


// Attributes
protected:


// Methods
public:
	CCSFrame* GetFrame();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL


// Implementation
public:
	//{{AFX_MSG(CCSApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
