// ConStation.h : main header file for the CONSTATION application
//

#if !defined(AFX_CONSTATION_H__7FAE70C2_81A3_4453_8F8B_E07257316D56__INCLUDED_)
#define AFX_CONSTATION_H__7FAE70C2_81A3_4453_8F8B_E07257316D56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols



/////////////////////////////////////////////////////////////////////////////
// Globals
typedef struct
{
	float r;
	float g;
	float b;
} CColor;

void glColor(CColor c);

extern const CColor COLOR_WHITE,
					COLOR_BLACK,
					COLOR_CROSS,
					COLOR_ACTIVESTAR,
					COLOR_NORTHSTAR,
					COLOR_CONSTLINE,
					COLOR_TERRAIN;

typedef struct
{
	GLubyte* data;
	GLuint width;
	GLuint height;
	GLuint textureID;
} Texture;

enum StateType {Viewing, AddingLine, AddingPoly, DeletingLine};

#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CConStationApp:
// See ConStation.cpp for the implementation of this class
//

class CConStationApp : public CWinApp
{
public:
	CConStationApp();

	CMainFrame* GetMainFrame() const;

// Attributes
	CSingleDocTemplate* pDocTemplate;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConStationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CConStationApp)
	afx_msg void OnAppAbout();
	afx_msg void OnStarfNewActual();
	afx_msg void OnStarfNewRandom();
	afx_msg void OnStarfOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSTATION_H__7FAE70C2_81A3_4453_8F8B_E07257316D56__INCLUDED_)
