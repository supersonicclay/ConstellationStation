//===========================================================================
// ConStation.h
//
// CConStationApp
//   main header file for Constellation Station
//===========================================================================

#ifndef CS_CONSTATION_H
#define CS_CONSTATION_H


#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


#include "ConStationFrame.h"

/////////////////////////////////////////////////////////////////////////////
// CConStationApp:
// See ConStation.cpp for the implementation of this class
//

class CConStationApp : public CWinApp
{
// Construction / Destruction
public:
	CConStationApp();

	CConStationFrame* GetFrame() const;


// Attributes
protected:


// Methods
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConStationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL


// Implementation
public:
	//{{AFX_MSG(CConStationApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
