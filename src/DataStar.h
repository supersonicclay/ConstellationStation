//===========================================================================
// DataStar.h
//
// CDataStar
//   star data.
//===========================================================================

#ifndef CS_DATASTAR_H
#define CS_DATASTAR_H


class CDataStar : public CObject
{
DECLARE_SERIAL( CDataStar )

// Construction / Destruction
public:
	CDataStar();
	CDataStar( const CDataStar& s );
	~CDataStar();

	void Init();

	const CDataStar& operator=( const CDataStar& s );
	void Serialize( CArchive& ar );


// Attributes
private:
	ra_s ra;
	dec_s dec;
	float mag;
	float x, y, z;
	color_s color;
	float radius;


// Methods
public:

// Gets
	float GetMag() const;
	color_s GetColor() const;
	float GetRadius() const;
	float GetX() const;
	float GetY() const;
	float GetZ() const;
	float GetTheta() const;
	float GetPhi() const;

// Sets
	void SetMag( float mag_ );
	void SetColor( color_s color_ );
	void SetColorFromMag();
	void SetRadiusFromMag();
	void SetX( float x_ );
	void SetY( float y_ );
	void SetZ( float z_ );
	void SetRA( ra_s ra_ );
	void SetDec( dec_s dec_ );
	void SetRA( unsigned short hour,
				unsigned short minute,
				float second );
	void SetDec( BOOL positive,
				 unsigned short degree,
				 unsigned short minute,
				 float second );
	void SetRADecFromXYZ();
	void SetXYZFromRADec();

// Methods
	void Randomize();
	void PickXYZ();
	void PickLocation();
	void PickMag();
};

// CDataStar vector
typedef std::vector<CDataStar> star_v;
typedef star_v::iterator star_vi;

#endif

