// ConStationDoc.h : interface of the CConStationDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONSTATIONDOC_H__687400CC_D8B2_4B17_9F1A_0F81523AAE64__INCLUDED_)
#define AFX_CONSTATIONDOC_H__687400CC_D8B2_4B17_9F1A_0F81523AAE64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Starfield.h"
#include "Terrain.h"

class CConStationDoc : public CDocument
{
DECLARE_DYNCREATE( CConStationDoc )

protected: // create from serialization only
	CConStationDoc();

// Attributes
private:
	CStarfield* starfield;
	CTerrain* terrain;

// Operations
public:
	CStarfield* GetStarfield() const;
	CTerrain* GetTerrain() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConStationDoc)
	public:
	virtual void Serialize( CArchive& ar );
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConStationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CConStationDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSTATIONDOC_H__687400CC_D8B2_4B17_9F1A_0F81523AAE64__INCLUDED_)
