// ConStationView.h : interface of the CConStationView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONSTATIONVIEW_H__8235DF66_BF5C_4582_8C00_7DDB9270BCB1__INCLUDED_)
#define AFX_CONSTATIONVIEW_H__8235DF66_BF5C_4582_8C00_7DDB9270BCB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Starfield.h"

class CConStationView : public CView
{
protected: // create from serialization only
	CConStationView();
	DECLARE_DYNCREATE(CConStationView)

// Attributes
private:

	HGLRC	m_hRC;
	CDC*	m_pDC;

	int width;
	int height;

	CStarfield* pStarfield;

	// Keys
	bool keyDown[256];

	// Mouse controls
	bool mouseRotatingXY;
	bool mouseRotatingZ;
	float rotX;
	float rotY;
	float rotZ;
	float zoom;

	CPoint mousePoint;
	CPoint mouseLDownPoint;
	CPoint mouseRDownPoint;

	// Selecting
	GLuint selectBuffer[100];
	GLint hits;

	// Constellation editor
	bool editing;
	bool makingLine;
	bool deletingLine;
	int prevStarNum;

public:
	CConStationDoc* GetDocument();

////int InitGL();
	bool InitializeOpenGL();
////bool SetPixelformat(HDC hdc);
	bool SetupPixelFormat();
	void GetGLInfo();

	// Drawing functions
	void DrawGround() const;
	void DrawStarfield() const;
	void DrawConstellations() const;
	void DrawStars() const;

	void DrawStar (int i) const;
	void DrawConstellation (int i) const;
	void DrawHeading() const;

	// View manipulation (draw)
	void Projection  () const;
	void Perspective () const;

	void Rotate() const;
	void RotateSeason() const;
	void RotateLatitude() const;
	void RotateTime() const;

	// View manipulation (data)
	void RotateUp   ();
	void RotateDown ();
	void RotateLeft ();
	void RotateRight();
	void ZoomIn  ();
	void ZoomOut ();
////void PerspIn ();
////void PerspOut();
	// View resets
	void ResetView ();
	void ResetZoom ();
	void ResetPersp();
	void ResetRot  ();

	void ProcessKeys();

	// Set Cursor
	void SetCur(WORD cur);

	// Selecting
	int SelectStar();
	bool Select();

	// Constellation editor
	void SwitchEditing();


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConStationView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConStationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CConStationView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEdit();
	afx_msg void OnUpdateEdit(CCmdUI* pCmdUI);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnUpdateConstellationCreate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstellationDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstellationLoad(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstellationStore(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConstellationStoreas(CCmdUI* pCmdUI);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnNewLine();
	afx_msg void OnUpdateNewLine(CCmdUI* pCmdUI);
	afx_msg void OnDelLine();
	afx_msg void OnUpdateDelLine(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ConStationView.cpp
inline CConStationDoc* CConStationView::GetDocument()
   { return (CConStationDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSTATIONVIEW_H__8235DF66_BF5C_4582_8C00_7DDB9270BCB1__INCLUDED_)
