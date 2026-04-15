#include "binomials.h"
#include "parameters.h"

// Returns n choose k
#include <stdio.h>

// Dynamic programming algorithm (quadratic)
long long binomial_coef(int n, int k) {
	if (k > n - k){
        k = n - k;
	}
	// n = 2 * K, k = N
	#define SIZE (2 * K + 1)
	long long mem[SIZE][SIZE];
	mem[0][0] = 1;
	for(int i = 0; i < n + 1; i++) {
		mem[i][0] = 1;
		mem[i][i] = 1;
	}
    for(int i = 1; i < n + 1; i++) {
        for(int j = 1; j < i; j++) {
            mem[i][j] = mem[i-1][j-1] + mem[i-1][j];
        }
    }
    return mem[n][k];
}


// Puts the array {0, 1, ..., k - 1} in the array res
void first_binomial(int k, int res[]){
	for(int i = 0; i < k; i++) {
		res[i] = i;
	}
}


// bin contains a choice of k integers among {0,...,n-1}
// The function returns the next one in the bin array
void next_binomial(int k, int n, int bin[]) {
	
	int i = k - 1;
	const int val = n - k + i;
	while (i >= 0 && bin[i] >= val)
		i--;
	if (i < 0)
		return;
	// in this case bin[i+1, ..., k-1] = n-1-(k-1-i), ..., n-2,n-1
	// n-1-(k-1-i) = n-k+i
	const int a = bin[i] + 1;
	const int bound = k - i;
	int *p = bin + i;
	for (int j = 0; j < bound; j++)
		p[j] = a + j;
}

