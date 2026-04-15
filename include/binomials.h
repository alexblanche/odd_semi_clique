#ifndef BINOMIALS_H
#define BINOMIALS_H

// Dynamic programming algorithm (quadratic)
// Returns n choose k
long long binomial_coef(int n, int k);

// Puts the array {0,1,...,k-1} in the array res
void first_binomial(int k, int res[]);

// bin contains a choice of k integers among {0,...,n-1}
// The function returns the next one in the bin array
void next_binomial(int k, int n, int bin[]);


#endif