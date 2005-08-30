//===========================================================================
// DataSun.cpp
//
// CDataSun
//   star data.
//===========================================================================


#include "stdafx.h"
#include "CSApp.h"
#include "DataSun.h"

IMPLEMENT_SERIAL( CDataSun, CDataStar, 1 )


/////////////////////////////////////////////////////////////////////////////
// Construction / Destruction

CDataSun::CDataSun()
{
	Init();
}

CDataSun::CDataSun( const CDataSun& s )
{
	*this = s;
}

CDataSun::~CDataSun()
{
}

const CDataSun& CDataSun::operator=( const CDataSun& s )
{
	ra = s.ra;
	dec = s.dec;
	phi = s.phi;
	theta = s.theta;
	center = s.center;
	trVert = s.trVert;
	tlVert = s.tlVert;
	blVert = s.blVert;
	brVert = s.brVert;
	mag = s.mag;
	radius = s.radius;
	rotTime = s.rotTime;
	alpha = s.alpha;
	color = s.color;
	timeMat = s.timeMat;
	return *this;
}

void CDataSun::Init()
{
	ra.hour = 12;
	ra.minute = 0;
	ra.second = 0.0f;
	dec.positive = TRUE;
	dec.degree = 0;
	dec.minute = 0;
	dec.second = 0.0f;

	radius = DEF_SUN_RADIUS;
	color = DEF_SUN_COLOR;

	UpdatePosFromRADec();
	UpdateVerts();

	rotTime = 0.0f;
	timeMat.identity();
}


/////////////////////////////////////////////////////////////////////////////
// Gets

color_s		CDataSun::GetColor()	{	return color;		}
float		CDataSun::GetRotTime()	{	return rotTime;		}
matrix44*	CDataSun::GetTimeMat()	{	return &timeMat;	}



/////////////////////////////////////////////////////////////////////////////
// Methods

double azimuth( double j, float lat, float lon )
{
	double T=j/36525;
	double k=PI/180.0;
	int M=357.5291+35999.0503*T-0.0001559*T*T-0.00000045*T*T*T;
	M=M % 360;
	int Lo=280.46645+36000.76983*T+0.0003032*T*T;
	Lo=Lo % 360;
	double DL=(1.9146-0.004817*T-0.000014*T*T)*sin(k*M)+(0.019993-0.000101*T)*sin(k*2*M)+0.00029*sin(k*3*M);
	double L=Lo+DL;
	double eps=23.43999-0.013*T;
	double delta=(1/k)*asin(sin(L*k)*sin(eps*k));
	double RA=(1/k)*atan2(cos(eps*k)*sin(L*k),cos(L*k));
	RA=(RA+360) % 360;
	double GMST=280.46061837+360.98564736629*j+0.000387933*T*T-T*T*T/38710000;
	GMST=(GMST+360) % 360;
	double LMST=GMST+lg;
	double H=LMST-RA;
	double eqt=(Lo-RA)*4;
	double azm=(1/k)*atan2(-sin(H*k),cos(la*k)*tan(delta*k)-sin(la*k)*cos(H*k));
	azm=(azm+360) % 360;

	return azm;
}

double altitude( double j, float lat, float lon )
{
	double T=j/36525;
	double k=PI/180.0;
	int M=357.5291+35999.0503*T-0.0001559*T*T-0.00000045*T*T*T;
	M=M % 360;
	int Lo=280.46645+36000.76983*T+0.0003032*T*T;
	Lo=Lo % 360;
	double DL=(1.9146-0.004817*T-0.000014*T*T)*sin(k*M)+(0.019993-0.000101*T)*sin(k*2*M)+0.00029*sin(k*3*M);
	L=Lo+DL;
	double eps=23.43999-0.013*T;
	double delta=(1/k)*asin(sin(L*k)*sin(eps*k));
	double RA=(1/k)*atan2(cos(eps*k)*sin(L*k),cos(L*k));
	RA=(RA+360) % 360;
	double GMST=280.46061837+360.98564736629*j+0.000387933*T*T-T*T*T/38710000;
	GMST=(GMST+360) % 360;
	double LMST=GMST+lg;
	double H=LMST-RA;
	double eqt=(Lo-RA)*4;
	double alt=(1/k)*asin(sin(la*k)*sin(delta*k)+cos(la*k)*cos(delta*k)*cos(H*k));
	return alt;
}

// http://aa.usno.navy.mil/data
// http://www.jgiesen.de/astro/astroJS/riseset/index.htm
void CDataSun::UpdateRADec( double j, float lat, float lon )
{
	// http://www.jgiesen.de/astro/astroJS/SunPositionCalculator.htm

	int twr = -6;
	int tws = -6;
	double k = PI/180.0;

	float lgo=lon;
	float lao=lat;
	float aa=180.0;

	double alt=altitude( j, lat, lon );
	double azm=azimuth( j, lat, lon );


/*

function sunpos()
{

	var lg=1.0*document.sunform.longitude.value;
	var lgmi=1.0*document.sunform.longmin.value;
	var la=1.0*document.sunform.latitude.value;
	var lami=1.0*document.sunform.latmin.value;
	var ye=1.0*document.sunform.year.value;
	var mo=1.0*document.sunform.month.value;
	var da=1.0*document.sunform.day.value;
	var ho=1.0*document.sunform.hour.value;
	var mi=1.0*document.sunform.min.value;
	var zo=1.0*document.sunform.zone.value;
	var twr=1.0*document.sunform.twilightr.value;
	var tws=1.0*document.sunform.twilights.value;
	var ewv=document.sunform.ew.options[document.sunform.ew.selectedIndex].value;
	var nsv=document.sunform.ns.options[document.sunform.ns.selectedIndex].value;

	lg=lg+lgmi/60
	la=la+lami/60


	if (ewv=="West") { lg=-1.0*lg }
	if (nsv=="South") { la=-1.0*la; aa=0.0 }


	h1=0
	m=0
	alt1=altitude(lg,la,ye,mo,da,h1,m,zo)
	azm1=azimuth(lg,la,ye,mo,da,h1,m,zo)
	s=-0.8333

	// find midday interval
	for (var h=0; h<24; h++){
		h2=h
		azm2=azimuth(lg,la,ye,mo,da,h2,m,zo)
		if ((azm1<=180)&&(azm2>=180)){
			ha1=h1
			ha2=h2
		}
		h1=h2
		azm1=azm2
	}
	// find exact midday time
	mino=1.0;
	for (h=ha1; h<ha2; h++){
		for (m=0; m<60; m++){
			azmo=azimuth(lg,la,ye,mo,da,h,m,zo)
			dfo=Math.abs(aa-azmo)
			if (dfo<=mino) {
				mino=dfo
				hno=h
				mno=m
			}
		}
	}

	mday=""

	altnoon=altitude(lg,la,ye,mo,da,hno,mno,zo);
	if (altnoon<s){ mday="nigth" }


	hr="does not occur"
	mr=""
	hs="does not occur"
	ms=""
	htwr="does not occur"
	mtwr=""
	htws="does not occur"
	mtws=""

	mintwr=0.1;
	minr=0.1

	for (h=0; h<=hno; h++){
		for (m=0; m<60; m++){
			if (60*h+m< 60*hno+mno){
				altr=altitude(lg,la,ye,mo,da,h,m,zo)

				dftwr=Math.abs(twr-altr)
				if (dftwr<=mintwr) {
					mintwr=dftwr
					htwr=h
					mtwr=m
				}

				if (altnoon > s){
					dfr=Math.abs(s-altr)
					if (dfr<=minr) {
						minr=dfr
						hr=h
						mr=m
					}
				}

			}
		}
	}


	mins=0.1;
	mintws=0.1;

	for (h=hno; h<24; h++){
		for (m=0; m<60; m++){
			if (60*h+m >= 60*hno+mno){
				alts=altitude(lg,la,ye,mo,da,h,m,zo)

				if(altnoon>s){
					dfs=Math.abs(s-alts)
					if (dfs<=mins) {
						mins=dfs
						hs=h
						ms=m
					}
				}


				dftws=Math.abs(tws-alts)
				if (dftws<=mintws) {
					mintws=dftws
					htws=h
					mtws=m
				}
			}
		}
	}



	cikti="Sun Position Calculator\r(C) 2001, Senol Gulgonul\r\r";
	cikti=cikti+"Location: "+frm(lgo)+" deg "+ewv+", "+frm(lao)+" deg "+nsv+"\r";
	cikti=cikti+"Date: "+ye+"/"+mo+"/"+da+", "+ho+" hr:"+mi+" min, "+zo+"hr GMT \r";
	cikti=cikti+"Twilight morning "+twr+" deg, evening "+tws+" deg"+"\r\r";

	//cikti=cikti+"altnoon:\t"+altnoon+":"+s+"\r\r";

	cikti=cikti+"altitude:\t"+frm(alt)+" deg\r";
	cikti=cikti+"azimuth:\t"+frm(azm)+" deg\r\r";

	cikti=cikti+"morning twilight :\t"+htwr+":"+mtwr+"\r";
	cikti=cikti+"sun rise:\t\t"+hr+":"+mr+"\r";
	cikti=cikti+"midday:\t\t\t"+hno+":"+mno+" "+mday+"\r";
	cikti=cikti+"sun set:\t\t"+hs+":"+ms+"\r";
	cikti=cikti+"evening twilight:\t"+htws+":"+mtws+"\r";


	document.sunform.result.value=cikti;
}
*/

}

void CDataSun::AdjRotTime( float delta )
{
	rotTime += delta;

	// Keep rotTime between 0 and 2*PI
	if( rotTime < 0.0f )
		rotTime += PI2;
	if( rotTime > PI2 )
        rotTime -= PI2;

	UpdateTimeMat();
}

void CDataSun::UpdateTimeMat()
{
	timeMat.identity();
	timeMat = RotateRadMatrix44( 'y', rotTime );
}


/////////////////////////////////////////////////////////////////////////////
// Serialization

void CDataSun::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	CSDebug( "Shouldn't be serializing a sun", "CDataSun::Serialize" );
	return;

	if( ar.IsLoading() )
	{
		ar >> ra.hour >> ra.minute >> ra.second
		   >> dec.positive >> dec.degree >> dec.minute >> dec.second
		   >> mag >> center.x >> center.y >> center.z
		   >> radius
		   >> alpha
		   >> color;
	}
	else
	{
		ar << ra.hour << ra.minute << ra.second
		   << dec.positive << dec.degree << dec.minute << dec.second
		   << mag << center.x << center.y << center.z
		   << radius
		   << alpha
		   << color;
	}
}

