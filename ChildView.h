// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__67736910_2821_4A60_8A76_875D092DAAC8__INCLUDED_)
#define AFX_CHILDVIEW_H__67736910_2821_4A60_8A76_875D092DAAC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Starfield.h"

/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
private:
    HGLRC	m_hRC;		// Rendering Context
    CDC*	m_pDC;			// GDI Device Context

	int width;
	int height;

	CStarfield* pStarfield;

	// Keyboard controls
	BOOL keyDown [256];

	// Mouse controls
	BOOL mouseRotating;
	float rotX;
	float rotY;
	float zoom;

	CPoint mouseLDownPoint;
	CPoint mouseRDownPoint;

// Operations
public:
	int InitializeOpenGL();
	BOOL SetupPixelFormat();
	void GetGLInfo();
////void ReSizeGLScene();

	// Drawing functions
	void DrawStarfield () const;
	void DrawStar (int i) const;
////void DrawConstellation(int i) const;

	void ProcessKeys();

	// View manipulation
	void ResetView  ();
	void RotateUp   ();
	void RotateDown ();
	void RotateLeft ();
	void RotateRight();
	void ZoomIn ();
	void ZoomOut();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__67736910_2821_4A60_8A76_875D092DAAC8__INCLUDED_)
