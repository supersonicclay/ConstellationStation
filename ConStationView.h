// ConStationView.h : interface of the CConStationView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONSTATIONVIEW_H__8235DF66_BF5C_4582_8C00_7DDB9270BCB1__INCLUDED_)
#define AFX_CONSTATIONVIEW_H__8235DF66_BF5C_4582_8C00_7DDB9270BCB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConStationDoc.h"

#include "Starfield.h"

class CConStationView : public CView
{
protected: // create from serialization only
	CConStationView();
	DECLARE_DYNCREATE( CConStationView )

// Attributes
private:

	HGLRC	m_hRC;
	CDC*	m_pDC;

	int width;
	int height;

// Textures
	texture_t starTex;
	texture_t skyTex;

	GLUquadricObj* skySphere;

// Sun
	GLUquadricObj* sunSphere;
	float sunPos[3];

// Input
	// Keys
	BOOL keyDown[256];

	// Mouse controls
	BOOL mouseRotatingXY;
	BOOL mouseRotatingZ;

	CPoint mousePoint;
	CPoint mouseLDownPoint;
	CPoint mouseRDownPoint;
///	ACTIVE LINE
///	CPoint prevStarPoint;

// Selecting
	enum SelectType {Star, Line};
	GLuint selectBuffer[100];
	GLint hits;

// Constellation editor
	int prevStarNum;
	int firstStarNum;

// Operations
public:

// Initialization
	BOOL InitializeOpenGL();
	BOOL SetupPixelFormat();
	BOOL LoadTextures();
///	BOOL LoadTGA( texture_t &texture, char* filename );

	void SetTerrainOffset();

// Drawing functions
	void Redraw();
	void DrawCurConstellation( CDC* pDC );
	void DrawTerrain() const;
	void PositionTerrain() const;
	void DrawSky() const;
	void DrawSun() const;
	void DrawStarfield() const;
	void DrawStars() const;
	void DrawStar (int i) const;
	void DrawConstellations() const;
	void DrawConstellation (int i) const;
	void DrawHeading() const;
///	ACTIVE LINE
///	void DrawActiveLine() const;

	// View manipulation
	void Projection  () const;
	void Perspective () const;

	void RotateXY() const;
	void RotateSeason() const;
	void RotateLatitude() const;
	void RotateTime() const;

	BOOL IsRotating() const;

// Input
	void ProcessKeys();

// Selecting
	void ClearFirstStar();
	int SelectStar();
	int SelectConstLine();
	BOOL Select( SelectType selection );

// Set Cursor
	void SetCur( WORD cur );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConStationView)
	public:
	virtual void OnDraw( CDC* pDC );  // overridden to draw this view
	virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConStationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CConStationView)
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnTimer( UINT nIDEvent );
	afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnRButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnRButtonUp( UINT nFlags, CPoint point );
	afx_msg BOOL OnMouseWheel( UINT nFlags, short zDelta, CPoint pt );
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	afx_msg BOOL OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSTATIONVIEW_H__8235DF66_BF5C_4582_8C00_7DDB9270BCB1__INCLUDED_)
