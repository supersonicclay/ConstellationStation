
//===============
// sort.cpp
//
// CLaY Anderson
// CS451
//===============

#include "sort.h"


/*
#include <iostream.h>
#include <iomanip.h>
#include <stdlib.h>
#include <time.h>

void fill(int n, keytype A[]) {
    for (index i = 0; i < n; i++)
        A[i] = rand();
}

void output(int n, const keytype S[]) {
    for (index i = 0; i < n; i++)
        cout << setw(8) << S[i];
    cout << endl;
}
*/

void exchange(keytype& a, keytype& b) {
    keytype temp = a;
    a = b;
    b = temp;
}

void partition( int low, int high, int& pivotpoint, keytype A[] )
{
	int i, j;
	keytype pivotitem;
	
	pivotitem = A[low];
	j = low;
	for( i=low+1; i<=high; ++i )
	{
		if( A[i] < pivotitem)
		{
			j++;
			exchange( A[i], A[j] );
		}
	}

	pivotpoint = j;
	exchange( A[low], A[pivotpoint] );	
}

void quicksort( int low, int high, keytype A[] )
{
	int pivotpoint;

	if( low < high )
	{
		partition( low, high, pivotpoint, A );
		quicksort( low, pivotpoint-1, A );
		quicksort( pivotpoint+1, high, A );
	}
}


void sort( int n, keytype A[] )
{
	quicksort( 0, n-1, A );
}
