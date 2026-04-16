#ifndef BINOMIALS_H
#define BINOMIALS_H

#include "parameters.h"

// Represents a combination of k elements among n
typedef struct {
    int t[N];
    int a;  // a = 2 * K
    int b;  // b = N
} combination;

// Dynamic programming algorithm (quadratic)
// Returns n choose k
long long binomial_coef(int a, int b);

// Returns the combination { 0, 1, ..., k - 1 }
combination first_combination(int a, int b);

// bin contains a choice of k integers among {0,...,n-1}
// The function returns the next one in the bin array
void next_combination(combination *c);


#endif