// A program to test sorting routines.
// by Anne M. Cable
// February 5, 2004
//

#include "utilities.h"
#include "sort.h"
#include <stdlib.h>
#include <time.h>

int main()
{
	/*
	// Declare and output an array (subscripted from 1 to 7).
	keytype A[] = {0, 20, 30, 15, 4, 3, 40, 2};
	output(7, A);

	// Sort and output the same array.
	sort(7, A);
	output(7, A);
	*/

	srand( (unsigned)time(NULL) );
	int size = rand()%20;
//	int size = 9;

	keytype* A = new keytype[size];
	for( int i=0; i<size; i++ )
	{
		A[i] = rand()%50;
	}

	output(size, A);

	sort(size, A);
	output(size, A);

//	delete[] A;

	return 0;
}
