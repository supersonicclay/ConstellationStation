//===========================================================================
// MgrTerrain.cpp
//
// CMgrTerrain
//   manager class for terrain functions.
//===========================================================================


#include "stdafx.h"
#include "ConStation.h"
#include "MgrTerrain.h"

#include "DlgOptionsTerr.h"

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
	terrain.New();
	starfield.SetModified();
	Redraw();
}

// Opens the terrain options dialog
void CMgrTerrain::Options()
{
	if( starfield.IsSpinning() )
		starfield.SwitchSpinning();

	CDlgOptionsTerr dialog;

	if( dialog.DoModal() == IDOK )
	{
		// Change terrain settings
		terrain.SetVisible( dialog.visible );
		optionsMgr.SetTerrTextured( dialog.textured );
		starfield.SetModified();
	}
	else
	{
		// Reset options
		optionsMgr.SetTerrSeason( dialog.origSeason );
		optionsMgr.SetTerrColor( dialog.origColor );
		if( dialog.roughness != dialog.origRoughness )
		{
			optionsMgr.SetTerrRoughness( dialog.origRoughness / 100.0f );
			terrain.New();
		}
	}

	Redraw();
}

// Toggles the terrain on and off
void CMgrTerrain::Toggle()
{
	terrain.SwitchVisible(); Redraw();
}