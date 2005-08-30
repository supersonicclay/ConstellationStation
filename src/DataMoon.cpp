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

double PrimerGiro( double x )/// Ugly, but oh well.
{
	x= x- 360 * floor ( x / 360);
	return x;
}

void CDataMoon::UpdateRADec()
{
	//  http://users.zoominternet.net/~matto/Java/Moon's%20Position.htm

	// luna
	double T = (julian- 2415020) / 36525;
	double T2 = T * T;
	double T3 = T2 * T;
	double L1 = 270.434164 + 481267.8831 * T - .001133 * T2 + .0000019 * T3;
	double M = 358.475833 + 35999.0498 * T - .00015 * T2 - .0000033 * T3;
	double M1 = 296.104608 + 477198.8491 * T + .009192 * T2 + .0000144 * T3;
	double D = 350.737486 + 445267.1142 * T - .001436 * T2 + .0000019 * T3;
	double F = 11.250889 + 483202.0251 * T - .003211 * T2 - .0000003 * T3;
	double OM = 259.183275 - 1934.142 * T + .002078 * T2 + .0000022 * T3;
	OM = OM * PI / 180;

	L1 = L1 + .000233 * sin((51.2 + 20.2 * T) * PI / 180);
	double S = .003964 * sin((346.56 + 132.87 * T - .0091731 * T2) * PI / 180);
	L1 = L1 + S + .001964 * sin(OM);
	M = M - .001778 * sin((51.2 + 20.2 * T) * PI / 180);
	M1 = M1 + .000817 * sin((51.2 + 20.2 * T) * PI / 180);
	M1 = M1 + S + .002541 * sin(OM);
	D = D + .002011 * sin((51.2 + 20.2 * T) * PI / 180);
	D = D + S + .001964 * sin(OM);
	F = F + S - .024691 * sin(OM);
	F = F - .004328 * sin(OM + (275.05 - 2.3 * T) * PI / 180);
	double EX = 1 - .002495 * T - .00000752 * T2;
	OM = OM * 180 / PI;
	L1 = PrimerGiro(L1);
	M = PrimerGiro(M);
	M1 = PrimerGiro(M1);
	D = PrimerGiro(D);
	F = PrimerGiro(F);
	OM = PrimerGiro(OM);
	M = M * PI / 180;
	M1 = M1 * PI / 180;
	D = D * PI / 180;
	F = F * PI / 180;

	// longitude
	double L=L1+ 6.28875 * sin(M1) + 1.274018 * sin(2 * D - M1) + .658309 * sin(2 * D);
	L= L + .213616 * sin(2 * M1) - EX * .185596 * sin(M) - .114336 * sin(2 * F);
	L= L + .058793 * sin(2 * D - 2 * M1) + EX * .057212 * sin(2 * D - M - M1) + .05332 * sin(2 * D + M1);
	L = L + EX * .045874 * sin(2 * D - M) + EX * .041024 * sin(M1 - M) - .034718 * sin(D);
	L = L - EX * .030465 * sin(M + M1) + .015326 * sin(2 * D - 2 * F) - .012528 * sin(2 * F + M1);
	L = L - .01098 * sin(2 * F - M1) + .010674 * sin(4 * D - M1) + .010034 * sin(3 * M1);
	L = L + .008548 * sin(4 * D - 2 * M1) - EX * .00791 * sin(M - M1 + 2 * D) - EX * .006783 * sin(2 * D + M);
	L = L + .005162 * sin(M1 - D) + EX * .005 * sin(M + D) + EX * .004049 * sin(M1 - M + 2 * D);
	L = L + .003996 * sin(2 * M1 + 2 * D) + .003862 * sin(4 * D) + .003665 * sin(2 * D - 3 * M1);
	L = L + EX * .002695 * sin(2 * M1 - M) + .002602 * sin(M1 - 2 * F - 2 * D) + EX * .002396 * sin(2 * D - M - 2 * M1);
	L = L - .002349 * sin(M1 + D) + EX * EX * .002249 * sin(2 * D - 2 * M) - EX * .002125 * sin(2 * M1 + M);
	L = L - EX * EX * .002079 * sin(2 * M) + EX * EX * .002059 * sin(2 * D - M1 - 2 * M) - .001773 * sin(M1 + 2 * D - 2 * F);
	L = L + EX * .00122 * sin(4 * D - M - M1) - .00111 * sin(2 * M1 + 2 * F) + .000892 * sin(M1 - 3 * D);
	L = L - EX * .000811 * sin(M + M1 + 2 * D) + EX * .000761 * sin(4 * D - M - 2 * M1) + EX * EX*.000717 * sin(M1 - 2 * M);
	L = L + EX * EX * .000704 * sin(M1 - 2 * M - 2 * D) + EX * .000693 * sin(M - 2 * M1 + 2 * D) + EX * .000598 * sin(2 * D - M - 2 * F) + .00055 * sin(M1 + 4 * D);
	L = L + .000538 * sin(4 * M1) + EX * .000521 * sin(4 * D - M) + .000486 * sin(2 * M1 - D);
	L = L - .001595 * sin(2 * F + 2 * D);

	// latitude
	double B = 5.128189 * sin(F) + .280606 * sin(M1 + F) + .277693 * sin(M1 - F) + .173238 * sin(2 * D - F);
	B = B + .055413 * sin(2 * D + F - M1) + .046272 * sin(2 * D - F - M1) + .032573 * sin(2 * D + F);
	B = B + .017198 * sin(2 * M1 + F) + 9.266999E-03 * sin(2 * D + M1 - F) + .008823 * sin(2 * M1 - F);
	B = B + EX * .008247 * sin(2 * D - M - F) + .004323 * sin(2 * D - F - 2 * M1) + .0042 * sin(2 * D + F + M1);
	B = B + EX * .003372 * sin(F - M - 2 * D) + EX * .002472 * sin(2 * D + F - M - M1) + EX * .002222 * sin(2 * D + F - M);
	B = B + .002072 * sin(2 * D - F - M - M1) + EX * .001877 * sin(F - M + M1) + .001828 * sin(4 * D - F - M1);
	B = B - EX * .001803 * sin(F + M) - .00175 * sin(3 * F) + EX * .00157 * sin(M1 - M - F) - .001487 * sin(F + D) - EX * .001481 * sin(F + M + M1) + EX * .001417 * sin(F - M - M1) + EX * .00135 * sin(F - M) + .00133 * sin(F - D);
	B = B + .001106 * sin(F + 3 * M1) + .00102 * sin(4 * D - F) + .000833 * sin(F + 4 * D - M1);
	B = B + .000781 * sin(M1 - 3 * F) + .00067 * sin(F + 4 * D - 2 * M1) + .000606 * sin(2 * D - 3 * F);
	B = B + .000597 * sin(2 * D + 2 * M1 - F) + EX * .000492 * sin(2 * D + M1 - M - F) + .00045 * sin(2 * M1 - F - 2 * D);
	B = B + .000439 * sin(3 * M1 - F) + .000423 * sin(F + 2 * D + 2 * M1) + .000422 * sin(2 * D - F - 3 * M1);
	B = B - EX * .000367 * sin(M + F + 2 * D - M1) - EX * .000353 * sin(M + F + 2 * D) + .000331 * sin(F + 4 * D);
	B = B + EX * .000317 * sin(2 * D + F - M + M1) + EX * EX * .000306 * sin(2 * D - 2 * M - F) - .000283 * sin(M1 + 3 * F);
	double W1 = .0004664 * cos(OM * PI / 180);
	double W2 = .0000754 * cos((OM + 275.05 - 2.3 * T) * PI / 180);
	double BT = B * (1 - W1 - W2);

	// parallax
	double P = .950724 + .051818 * cos(M1) + .009531 * cos(2 * D - M1) + .007843 * cos(2 * D) + .002824 * cos(2 * M1) + .000857 * cos(2 * D + M1) + EX * .000533 * cos(2 * D - M) + EX * .000401 * cos(2 * D - M - M1);
	P = P + .000173 * cos(3 * M1) + .000167 * cos(4 * D - M1) - EX * .000111 * cos(M) + .000103 * cos(4 * D - 2 * M1) - .000084 * cos(2 * M1 - 2 * D) - EX * .000083 * cos(2 * D + M) + .000079 * cos(2 * D + 2 * M1);
	P = P + .000072 * cos(4 * D) + EX * .000064 * cos(2 * D - M + M1) - EX * .000063 * cos(2 * D + M - M1);
	P = P + EX * .000041 * cos(M + D) + EX * .000035 * cos(2 * M1 - M) - .000033 * cos(3 * M1 - 2 * D);
	P = P - .00003 * cos(M1 + D) - .000029 * cos(2 * F - 2 * D) - EX * .000029 * cos(2 * M1 + M);
	P = P + EX * EX * .000026 * cos(2 * D - 2 * M) - .000023 * cos(2 * F - 2 * D + M1) + EX * .000019 * cos(4 * D - M - M1);
	double P1 = P * 60;
	B = BT * PI / 180;
	double LM = L * PI / 180;

	double R=10800/(PI*P1);

	double Z = (julian - 2415020.5) / 365.2422;
	double OB=23.452294 -(.46845 * Z+ 5.9E-07 * Z*Z)/3600;
	OB = OB * PI / 180;
	double DC =asin(sin(B) * cos(OB) + cos(B) * sin(OB) * sin(LM));
	double AR =acos(cos(B) * cos(LM) / cos(DC));
	if (LM > PI) {
		AR = 2 * PI - AR;
		}
	B=B*180/PI;
	LM=LM*180/PI;
	AR = AR * 12 / PI;
	DC=DC*180/PI;

/*
	// Convert right ascension to structure
	ra_s ra;
	ra.hour = (int)AR;
	AR -= ra.hour;
	ra.minute = (int)(AR*60);
	AR -= ra.minute/60.0;
	ra.second = AR*3600;
	ra.hour %= 24;/// can I do this?

	// Convert declination to structure
	dec_s dec;
	dec.positive = DC>=0;
	dec.degree = (int)DC;
	DC -= dec.degree;
	dec.minute = (int)(DC*60);
	DC -= dec.minute/60.0;
	dec.second = (int)(DC*3600);
	dec.degree %= 360;
///*//


	/// convert to structures  
	double H=floor(AR);
	M=floor((AR - floor(AR)) * 60);
	S=((AR -floor(AR)) * 60 - M) * 60;

	if (DC<0) D = -DC;
	else      D = DC;
//	D = abs(DC);    /// (makes M1 & S1 always 0)
	double G1;
	if (DC>0) {
		G1=floor(D);
		} else {
		G1=(-1)*floor(D);
		}
	M1=floor((D - floor(D)) * 60);
	double S1 = ((D - floor(D)) * 60 - M1) * 60;
	if (DC<0) {
		M1=-M1;
		S1=-S1;
		}

	ra_s ra = { H, M, S };
	dec_s dec = {G1, M1, S1};

	sun.SetRA(ra);
	sun.SetDec(dec);
	sun.UpdatePosFromRADec();
	sun.UpdateVerts();

}
///*/

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

