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
	alpha = s.alpha;
	color = s.color;
	altitude = s.altitude;
	azimuth = s.azimuth;
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
	altitude = 0.0f;
	azimuth = 0.0f;

	radius = DEF_SUN_RADIUS;
	color = DEF_SUN_COLOR;

	UpdatePosFromRADec();
	UpdateVerts();

	timeMat.identity();
}


/////////////////////////////////////////////////////////////////////////////
// Gets

color_s		CDataSun::GetColor()	{	return color;		}
matrix44*	CDataSun::GetTimeMat()	{	return &timeMat;	}



/////////////////////////////////////////////////////////////////////////////
// Methods

void CDataSun::UpdateTimeMat()
{
	timeMat  = RotateRadMatrix44( 'y', -DegToRad(azimuth) ) * RotateRadMatrix44( 'x', DegToRad(altitude) );
}



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

double dblmod( double x, int m ) /// Needs to go in global. Is there already one in MFC?
{
	return (int)x%m+(x-(int)x);
}

double jd( int y, int m, int d, int h, int n ) /// ugly
{
	double u = h + n/60.0;
	return (367*y) - (int)((7/4.0)*((int)((m+9)/12.0)+y))+(int)(275*m/9.0)+d-730531.5+(u/24);
}

double alt( int y, int m, int d, int h, int n, int s, float lat, float lon ) /// ugly
{
	double j = jd( y, m, d, h, n );
	double T=j/36525;
	double k=PI/180.0;
	double M=357.5291+35999.0503*T-0.0001559*T*T-0.00000045*T*T*T;
	M=dblmod(M, 360);
	double Lo=280.46645+36000.76983*T+0.0003032*T*T;
	Lo=dblmod(Lo, 360);
	double DL=(1.9146-0.004817*T-0.000014*T*T)*sin(k*M)+(0.019993-0.000101*T)*sin(k*2*M)+0.00029*sin(k*3*M);
	double L=Lo+DL;
	double eps=23.43999-0.013*T;
	double delta=(1/k)*asin(sin(L*k)*sin(eps*k));
	double RA=(1/k)*atan2(cos(eps*k)*sin(L*k),cos(L*k));
	RA=dblmod(RA+360, 360);
	double GMST=280.46061837+360.98564736629*j+0.000387933*T*T-T*T*T/38710000;
	GMST=dblmod(GMST+360, 360);
	double LMST=GMST+lon;
	double H=LMST-RA;
	double eqt=(Lo-RA)*4;
	double alt=(1/k)*asin(sin(lat*k)*sin(delta*k)+cos(lat*k)*cos(delta*k)*cos(H*k));
	return alt;
}

double azm( int y, int m, int d, int h, int n, int s, float lat, float lon )
{
	///var uu=ut(ho,mi,zo);
	double j = jd( y, m, d, h, n );
	double T=j/36525;
	double k=PI/180.0;
	double M=357.5291+35999.0503*T-0.0001559*T*T-0.00000045*T*T*T;
	M=dblmod(M, 360);
	double Lo=280.46645+36000.76983*T+0.0003032*T*T;
	Lo=dblmod(Lo, 360);
	double DL=(1.9146-0.004817*T-0.000014*T*T)*sin(k*M)+(0.019993-0.000101*T)*sin(k*2*M)+0.00029*sin(k*3*M);
	double L=Lo+DL;
	double eps=23.43999-0.013*T;
	double delta=(1/k)*asin(sin(L*k)*sin(eps*k));
	double RA=(1/k)*atan2(cos(eps*k)*sin(L*k),cos(L*k));
	RA=dblmod(RA+360, 360);
	double GMST=280.46061837+360.98564736629*j+0.000387933*T*T-T*T*T/38710000;
	GMST=dblmod(GMST+360, 360);
	double LMST=GMST+lon;
	double H=LMST-RA;
	double eqt=(Lo-RA)*4;
	double azm=(1/k)*atan2(-sin(H*k),cos(lat*k)*tan(delta*k)-sin(lat*k)*cos(H*k));
	azm=dblmod(azm+360, 360);

	return azm;
}

/// Other sun calculators
// http://aa.usno.navy.mil/data
// http://www.jgiesen.de/astro/astroJS/riseset/index.htm

void CDataSun::UpdatePosition( int year, int month, int day, int hour, int minute, int second, float lat, float lon )
{
	altitude = alt(year,month,day,hour,minute,second,lat,lon);
	azimuth  = azm(year,month,day,hour,minute,second,lat,lon);

	phi = DegToRad( -altitude-90 );
	theta = DegToRad( -azimuth+180 );

	if( phi < 0.0f )
		phi+=PI;
	if( theta < 0.0f )
		theta+=PI2;

	SetXYZFromPhiTheta();

	// Sun altitude/azimuth calculator from
	// http://www.jgiesen.de/astro/astroJS/SunPositionCalculator.htm
	/*
	function ut(h,m,z)
	{
		return (h-z+m/60);
	}

	function jd(y,m,d,u)
	{
		return (367*y)-Math.floor((7/4)*(Math.floor((m+9)/12)+y))+Math.floor(275*m/9)+d-730531.5+(u/24)
	}

	function azimuth(lg,la,ye,mo,da,ho,mi,zo)
	{
		with (Math) {

			var uu=ut(ho,mi,zo);
			var jj=jd(ye,mo,da,uu);
			var T=jj/36525;
			var k=PI/180.0;
			var M=357.5291+35999.0503*T-0.0001559*T*T-0.00000045*T*T*T
			M=M % 360
			var Lo=280.46645+36000.76983*T+0.0003032*T*T
			Lo=Lo % 360
			var DL=(1.9146-0.004817*T-0.000014*T*T)*sin(k*M)+(0.019993-0.000101*T)*sin(k*2*M)+0.00029*sin(k*3*M)
			var L=Lo+DL
			var eps=23.43999-0.013*T
			var delta=(1/k)*asin(sin(L*k)*sin(eps*k))
			var RA=(1/k)*atan2(cos(eps*k)*sin(L*k),cos(L*k))
			RA=(RA+360) % 360
			var GMST=280.46061837+360.98564736629*jj+0.000387933*T*T-T*T*T/38710000
			GMST=(GMST+360) % 360
			var LMST=GMST+lg
			var H=LMST-RA
			var eqt=(Lo-RA)*4
			var azm=(1/k)*atan2(-sin(H*k),cos(la*k)*tan(delta*k)-sin(la*k)*cos(H*k))
			azm=(azm+360) % 360

			return azm
		}
	}

	function altitude(lg,la,ye,mo,da,ho,mi,zo)
	{
		with (Math) {
			var uu=ut(ho,mi,zo);
			var jj=jd(ye,mo,da,uu);
			var T=jj/36525;
			var k=PI/180.0;
			var M=357.5291+35999.0503*T-0.0001559*T*T-0.00000045*T*T*T
			M=M % 360
			var Lo=280.46645+36000.76983*T+0.0003032*T*T
			Lo=Lo % 360
			var DL=(1.9146-0.004817*T-0.000014*T*T)*sin(k*M)+(0.019993-0.000101*T)*sin(k*2*M)+0.00029*sin(k*3*M)
			L=Lo+DL
			var eps=23.43999-0.013*T
			var delta=(1/k)*asin(sin(L*k)*sin(eps*k))
			var RA=(1/k)*atan2(cos(eps*k)*sin(L*k),cos(L*k))
			RA=(RA+360) % 360
			var GMST=280.46061837+360.98564736629*jj+0.000387933*T*T-T*T*T/38710000
			GMST=(GMST+360) % 360
			var LMST=GMST+lg
			var H=LMST-RA
			var eqt=(Lo-RA)*4
			var alt=(1/k)*asin(sin(la*k)*sin(delta*k)+cos(la*k)*cos(delta*k)*cos(H*k))
			return alt;
		}
	}

	function settoday()
	{
		today=new Date()
		thisyear=today.getYear()
		if (thisyear<=1900) thisyear=thisyear+1900 // for Netscape on Mac
		thismonth=today.getMonth()+1
		thisday=today.getDate()
		thishour=today.getHours()
		thisminute=today.getMinutes()
		offset=today.getTimezoneOffset()
		if (offset>=1380) offset=offset-1440  // for Netscape on Mac
		thiszone=-offset/60

		document.sunform.year.value=thisyear;
		document.sunform.month.value=thismonth;
		document.sunform.day.value=thisday;document.sunform.hour.value=thishour;
		document.sunform.min.value=thisminute;
		document.sunform.zone.value=thiszone;
	}

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

		var k=Math.PI/180.0;
		lg=lg+lgmi/60
		la=la+lami/60
		lgo=lg
		lao=la
		aa=180.0


		if (ewv=="West") { lg=-1.0*lg }
		if (nsv=="South") { la=-1.0*la; aa=0.0 }

		var alt=altitude(lg,la,ye,mo,da,ho,mi,zo)
		var azm=azimuth(lg,la,ye,mo,da,ho,mi,zo)

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


/////////////////////////////////////////////////////////////////////////////
// Serialization

void CDataSun::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if( ar.IsLoading() )
	{
		ar >> ra.hour >> ra.minute >> ra.second
		   >> dec.positive >> dec.degree >> dec.minute >> dec.second
		   >> altitude >> azimuth
		   >> mag >> center.x >> center.y >> center.z
		   >> radius
		   >> alpha
		   >> color;
	}
	else
	{
		ar << ra.hour << ra.minute << ra.second
		   << dec.positive << dec.degree << dec.minute << dec.second
		   << altitude << azimuth
		   << mag << center.x << center.y << center.z
		   << radius
		   << alpha
		   << color;
	}
}

