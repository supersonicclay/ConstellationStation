// sort.h
// header file for all sorting routines
// by Anne M. Cable
// February 5, 2004

#ifndef SORT_H
#define SORT_H

#include "main.h"

// Types
typedef entry_t keytype;   // array elements


void fill(int n, keytype A[]);
void output(int n, const keytype S[]);
void exchange(keytype & a, keytype & b);


void sort(int n, keytype A[]);

#endif
