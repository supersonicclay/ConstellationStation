
// Sort routine for star catalog

#include "main.h"

lineVec_t lines;

int main()
{
	ReadFile();

//	sort( lines.begin(), lines.end() );

	MagDist();

//	WriteFile();

	return 0;
}

void MagDist()
{
	int i;
	int mags[16];
	int totalMags = 0;

	for( i=0; i<16; ++i )
		mags[i] = 0;

	for( lineVecItor_t line = lines.begin(); line != lines.end(); ++line )
	{
		if( (*line).mag < 0 )
			++mags[0];
		else if( (*line).mag < 1 )
			++mags[1];
		else if( (*line).mag < 2 )
			++mags[2];
		else if( (*line).mag < 3 )
			++mags[3];
		else if( (*line).mag < 4 )
			++mags[4];
		else if( (*line).mag < 5 )
			++mags[5];
		else if( (*line).mag < 6 )
			++mags[6];
		else if( (*line).mag < 7 )
			++mags[7];
		else if( (*line).mag < 8 )
			++mags[8];
		else if( (*line).mag < 9 )
			++mags[9];
		else if( (*line).mag < 10 )
			++mags[10];
		else if( (*line).mag < 11 )
			++mags[11];
		else if( (*line).mag < 12 )
			++mags[12];
		else if( (*line).mag < 13 )
			++mags[13];
		else if( (*line).mag < 14 )
			++mags[14];
		else if( (*line).mag < 15 )
			++mags[15];
	}

	for( i = 0; i<16; ++i )
		cout << "Mag: " << i << "\t\tCount: " << mags[i] << endl;
}

void ReadFile()
{
	fstream file;
	file.open( "hip_main.txt", fstream::in );

	while( file.peek() != EOF )
	{
		ReadLine( file );
	}

	file.close();
}

void ReadLine( fstream& file )
{
	line_t line;
	char buffer[500];

	file.getline( buffer, 500 );

	sscanf( buffer, "%*41c%f", &line.mag );

	strncpy( line.text, buffer, 500 );

	lines.push_back(line);
}


void WriteFile()
{
	fstream file;
	file.open( "new.txt", fstream::out );

	for( lineVecItor_t i = lines.begin(); i != lines.end(); ++i )
	{
		WriteLine( file, i );
	}

	file.close();
}

void WriteLine( fstream& file, lineVecItor_t itor )
{
	file << (*itor).text << endl;
}
