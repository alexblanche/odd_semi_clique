#include "launch_search.h"

#include <stdio.h>

#include "naive_search.h"
#include "skip_search.h"

// Prints a solution with the format:
/*
Vertices : 0, 3, 5, 10, 18
 Edges:
0 - 3 : f(0,3) = 1 
0 - 5 : f(0,5) = 2 
...
*/
void print_solution(const combination *c){
    const int *v = c->t;
    printf("Vertices: %d", v[0]);
    for(int i = 1; i < c->b; i++){
        printf(", %d", v[i]);
    }
    printf("\nEdges:\n");
    for(int i = 0; i < c->b; i++) {
        for(int j = i + 1; j < c->b; j++) {
            printf("%2d - %2d: f(%2d,%2d) = %2d \n",
                v[i], v[j], v[i], v[j], f(v[i], v[j]));//, (c->a / 2)));
        }
    }
}

// Bruteforcing the labelings
// Solution space: size labels among {0,...,2k-1}
// vertex-labelings = the "(2k) choose n"

// Returns true if a solution was found, and puts it in the v array, otherwise returns false
// n = number of vertices
search_result search_for_solution(int n, int k, combination *c, search_type type) {

    const int two_k = 2 * k;
    const long long nb_labelings = binomial_coef(two_k, n);
    const long long batch_size = 10000000LL;
    const long long nb_batches = nb_labelings / batch_size;

    *c = first_combination(two_k, n);

    // Choice of brute-force function
    search_result (* test_function)(combination *, long long) =
        (type == Skip) ? test_combinations_skip : test_combinations_naive;

    // Printing progression after every batch
    for (long long i = 0; i < nb_batches; i++) {
        if (test_function(c, batch_size) == Solution_found) // tests batch combinations
            return Solution_found;
        printf("\rChecking... %.f %%", (100.f * (i + 1)) / nb_batches);
        fflush(stdout);
    }
    printf("\n");
    return test_function(c, nb_labelings % batch_size);
}

// Solution for n = 7
// 0, 3, 9, 15, 20, 30, 40