#ifndef MAIN__H
#define MAIN__H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


struct line_t
{
	float mag;
	char text[500];
};

const bool operator<( const line_t& l1, const line_t& l2 )
{
	return l1.mag < l2.mag;
}

typedef vector<line_t> lineVec_t;
typedef lineVec_t::iterator lineVecItor_t;


void ReadFile();
void ReadLine( fstream& file );

void MagDist();

void WriteFile();
void WriteLine( fstream& file, lineVecItor_t itor );


#endif
