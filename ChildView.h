// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__47020E0B_A6BF_4DC6_81A5_BBEB3415FFE9__INCLUDED_)
#define AFX_CHILDVIEW_H__47020E0B_A6BF_4DC6_81A5_BBEB3415FFE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCStar class
class CStar : public CObject
{
private:
	float x, y, z;
////	float r, g, b;
	float brightness;
public:
	CStar ();
	CStar (float x_, float y_, float z_, float brightness_=0.0f);
	~CStar();

	float GetX(), GetY(), GetZ();
	float GetBrightness();
////CColor GetColor();

	void SetX (float x_);
	void SetY (float y_);
	void SetZ (float z_);
////void SetColor (CColor c);
////void SetColor (float r, float g, float b);
	void SetBrightness (float brightness_);

	void Randomize();

////void Draw() const;
};


/////////////////////////////////////////////////////////////////////////////
// CCConstellation class
class CConstellation : public CObject
{
private:
	
public:
	CConstellation();
	~CConstellation();

	void Draw() const;

};


/////////////////////////////////////////////////////////////////////////////
// CCStarfield class
class CStarfield : public CObject
{
private:
	CStar *stars;
	CConstellation *constellations;

	int numStars;

////CStar* starMouseOver;

public:
	CStarfield();
	~CStarfield();

	void SetupStars();

	CStar* GetStar(int i) const;
	int GetNumStars() const;

/*
	float GetZoom() const;
	float GetRotX() const;
	float GetRotY() const;
////CStar* GetStarMouseOver() const;

	void SetRotX(float rotX_);
	void SetRotY(float rotY_);
////void SetStarMouseOver(CStar* s);

	void ResetView  ();
	void RotateUp   ();
	void RotateDown ();
	void RotateLeft ();
	void RotateRight();
	void ZoomIn ();
	void ZoomOut();
*/


////void Draw() const;
};


/////////////////////////////////////////////////////////////////////////////
// CChildView window
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

	HGLRC m_hRC;	//Rendering Context
	CDC* m_pDC;		//Device Context

	int width;
	int height;

	CStarfield starfield;

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
	BOOL InitializeOpenGL();	//Initialize OpenGL
	BOOL SetupPixelFormat();	//Set up the Pixel Format

	int  DrawGLScene   () const;
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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
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

typedef struct
{
	float r;
	float g;
	float b;
} CColor;

void glColor(CColor c);

extern const CColor WHITE, BLACK, RED, GREEN, BLUE;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__47020E0B_A6BF_4DC6_81A5_BBEB3415FFE9__INCLUDED_)
