// ConStation.h : main header file for the CONSTATION application
//

#if !defined(AFX_CONSTATION_H__8D8892BA_D9F3_4336_81AE_33C7A477F388__INCLUDED_)
#define AFX_CONSTATION_H__8D8892BA_D9F3_4336_81AE_33C7A477F388__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "Starfield.h"


/////////////////////////////////////////////////////////////////////////////
// GLOBALS

typedef struct
{
	float r;
	float g;
	float b;
} CColor;

void glColor(CColor c);

extern const CColor WHITE, BLACK, RED, GREEN, BLUE;



/////////////////////////////////////////////////////////////////////////////
// CConStationApp:
// See ConStation.cpp for the implementation of this class
//

class CConStationApp : public CWinApp
{
public:
	CConStationApp();

// Attributes
private:
	CStarfield* starfield;

// Operations
public:
	CStarfield* GetStarfield();
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
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSTATION_H__8D8892BA_D9F3_4336_81AE_33C7A477F388__INCLUDED_)
