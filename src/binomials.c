#include "binomials.h"
#include "parameters.h"

// Returns n choose k
#include <stdio.h>

// Dynamic programming algorithm (quadratic)
// Assumes, k != 0, n >= 2
long long binomial_coef(int n, int k) {
	
	k = (k > n - k) ? (n - k) : k;
	
	// n = 2 * K, k = N
	// size = n + 1
	// no need to go above mem[k]
	static long long mem[N + 1];
	
	for(int i = 0; i < k + 1; i++)
		mem[i] = 1;

    for(int i = 1; i < n; i++) {
        for(int j = k; j > 0; j--) {
            mem[j] += mem[j-1];
        }
    }
    return mem[k] + mem[k - 1];
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

