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
	OPENFILENAME ofn;
	char filename[MAX_PATH];
	char cwd[MAX_PATH];
	char starfieldDir[MAX_PATH];


// Methods
public:
	void InitOFN( BOOL saving );


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
	afx_msg void OnStarfNewActual();
	afx_msg void OnStarfNewRandom();
	afx_msg void OnStarfOpen();
	afx_msg void OnStarfSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
