#include <iostream.h>
#include <iomanip.h>
#include <time.h>

// A COMPARISON OF SORTING ALGORITHMS
// by Anne M. Cable
// February 5, 2004
//
// This program compares the running times of a sorting algorithm
// for various array sizes.  Link the program to the desired algorithm.

#include "utilities.h"
#include "sort.h"

int main() {
    const int MIN_COORDINATE = 0;
    const int MAX_COORDINATE = 10000;
    const int INCREMENT = 100;
    double seconds;
    clock_t start_time, stop_time;

    // Test on random data.
    for (int n = MIN_COORDINATE; n <= MAX_COORDINATE; n += INCREMENT) {


	// Create an array of size n and fill it with random numbers.
        keytype * A = new keytype[n+1];
        fill(n, A);

	// Sort the array (recording the time it took.
        start_time = clock();
        sort(n,A);
        stop_time = clock();
        seconds = (double) (stop_time - start_time) / CLOCKS_PER_SEC;

	// Output the size and the time.
        cout << setw(15) << n << setw(20) << seconds << endl;

	// Return the array to free storage.
        delete [] A;
    }
}
