//===========================================================================
// CSView.h
//
// CCSView
//   forwards input events to CInput and directs CGraphics.
//===========================================================================

#ifndef CS_CSVIEW_H
#define CS_CSVIEW_H


class CCSView : public CWnd
{
// Construction
public:
	CCSView();


// Attributes
private:


// Methods
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSView)
	public:
	virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
	protected:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCSView();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCSView)
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnTimer( UINT nIDEvent );
	afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
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

#endif
