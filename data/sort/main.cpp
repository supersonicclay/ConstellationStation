

#include <iostream.h>
#include <stdio.h>
#include <fstream.h>
#include "sort.h"


entry_t catalog[120000];

// READ
void ReadLine( int index, ifstream& file )
{
	file.getline( catalog[index].line, 600 );

	sscanf( catalog[index].line, "%*41c%f", &(catalog[index].mag) );

	cout << "Read magnitude: " << catalog[index].mag << endl;
}

void ReadFile( int& size )
{
	ifstream file( "..\\new.txt" );

	size = 0;
	while( file.peek() != EOF )
	{
		ReadLine( size, file );
		++size;
	}

	file.close();
}

// WRITE
void WriteLine( int index, ofstream& file )
{
	file << catalog[index].line << endl;
}

void WriteFile( int size )
{
	ofstream file( "..\\new.txt" );

	for( int i=0; i<size; ++i )
		WriteLine( i, file );

	file.close();
}

// SORT
void SortFile( int size )
{
	sort( size, catalog );
}

// MAIN
int main()
{
	int size = sizeof( entry_t );

	ReadFile( size );
	cout << "size = " << size << endl;
//	SortFile( size );
//	WriteFile( size );

	return 0;
}