#include "binomials.h"
#include "parameters.h"

#include <stdio.h>

// Returns a choose b
// Dynamic programming algorithm (quadratic)
// Assumes, b != 0, b >= 2
long long binomial_coef(int a, int b) {
	
	b = (b > a - b) ? (a - b) : b;
	
	// a = 2 * K, b = N
	// size = a + 1
	// no need to go above mem[b]
	static long long mem[N + 1];
	for(int i = 0; i < b + 1; i++)
		mem[i] = 1;

	for (int i = 1; i < b; i++) {
		for(int j = i; j > 0; j--)
            mem[j] += mem[j-1];
	}
    for(int i = b; i < a - 1; i++) {
        for(int j = b; j > 0; j--)
            mem[j] += mem[j-1];
    }
    return mem[b] + mem[b - 1];
}


// Returns the combination { 0, 1, ..., b - 1 }
combination first_combination(int a, int b) {
	combination c;
	c.a = a;
	c.b = b;
	for (int i = 0; i < c.b; i++)
		c.t[i] = i;
	return c;
}


// bin contains a choice of b integers among { 0, ..., a-1 }
// The function returns the next one in the c->t array
void next_combination(combination *c) {
	
	int i = (c->b) - 1;
	while (i >= 0 && c->t[i] >= ((c->a) - (c->b) + i))
		i--;
	if (i < 0)
		return;
		
	// in this case t[i+1, ..., k-1] = n-1-(k-1-i), ..., n-2,n-1
	// n-1-(k-1-i) = n-k+i
	const int x = c->t[i] + 1;
	const int bound = c->b - i;
	int *p = c->t;
	for (int j = 0; j < bound; j++)
		p[i + j] = x + j;
}

