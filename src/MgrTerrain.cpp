//===========================================================================
// MgrTerrain.cpp
//
// CMgrTerrain
//   manager class for terrain functions.
//===========================================================================


#include "stdafx.h"
#include "ConStation.h"
#include "MgrTerrain.h"

#include "DlgTerrain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CMgrTerrain::CMgrTerrain()
{
}

CMgrTerrain::~CMgrTerrain()
{
}


/////////////////////////////////////////////////////////////////////////////
// Methods

// Generate a new terrain with the same settings
void CMgrTerrain::New()
{
	terrain.MakeTerrain();
	Redraw();
}

// Open the terrain options dialog
void CMgrTerrain::Options()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

	float r = terrain.GetRoughness();
	color_s c = terrain.GetColor();

	CDlgTerrain dialog( r, c );

	dialog.DoModal();

	if( !dialog.needsUpdate )
		return;

	terrain.MakeTerrain();
	Redraw();
}