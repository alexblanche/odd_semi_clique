#include <stdio.h>
#include <string.h>

#include "mean_graph.h"
#include "parameters.h"
#include "binomials.h"

/* Bruteforcing the labeling of a clique to check the soft-mean property */
// m = k-1 edges in the graph : k = m+1

// Labeling function for the edges
inline int f(int a, int b) { //, int k){
    return ((a >> 1) + (b >> 1) + ((a & 1) && (b & 1))) % K;
}

typedef struct {
    int half;
    bool mod;
} f_res;

inline f_res fa(int a) { //, int k){
    return (f_res) { a >> 1, a & 1 };
}
inline int f_sum(int b, bool m) {
    return (b >> 1) + (m ? (b & 1) : 0);
}

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

// Check whether the labeling v is a solution for the soft-meanness property for the clique Kn
combination_status check_solution(const combination *c) {

    static bool seen[K];
    memset(seen, 0, K * sizeof(bool));

#define OPTIM
#ifndef OPTIM
    for (int i = 0; i < (c->b); i++) {

        for (int j = i + 1; j < (c->b); j++) {
            const int x = f(c->t[i], c->t[j]);//, (c->a) / 2);
            if (seen[x])
                return combination_invalid;
            seen[x] = true;
        }
    }
#else
    for (int i = 0; i < c->b; i++) {

        const f_res resa = fa(c->t[i]);
        for (int j = i + 1; j < c->b; j++) {
            const int x = (resa.half + f_sum(c->t[j], resa.mod)) % K;
            if (seen[x])
                return combination_invalid;
            seen[x] = true;
        }
    }
#endif
    return combination_valid;
}

inline check_result order(int j1, int j2) {
    
    return (check_result) {
        combination_invalid,
        (j1 > j2) ? j1 : j2
    };
}

typedef struct {
    int maxv;
} edge;

// Check whether the labeling v is a solution for the soft-meanness property for the clique Kn
check_result check_solution_with_culprits(const combination *c) {

    static bool seen[K];
    memset(seen, 0, K * sizeof(bool));
    static edge edges[K];
    memset(edges, 0, K * sizeof(edge));

    for (int i = 0; i < c->b; i++) {

        const f_res resa = fa(c->t[i]);
        for (int j = i + 1; j < c->b; j++) {
            const int x = (resa.half + f_sum(c->t[j], resa.mod)) % K;
            if (seen[x]) {
                return order(edges[x].maxv, j);
            }
            seen[x] = true;
            edges[x].maxv = j;
        }
    }
    return (check_result) { .res = combination_valid };
}

search_result test_combinations(combination *c, long long nb) {
    for (long long j = 0; j < nb; j++) {
        if (check_solution(c) == combination_valid)
            return Solution_found;
        next_combination(c);
    }
    return No_solution_found;
}

search_result test_combinations_skip(combination *c, long long nb) {

    bool stop = false;
    for (long long j = 0; !stop && (j < nb); j++) {
        const check_result cr = check_solution_with_culprits(c);
        if (cr.res == combination_valid)
            return Solution_found;
        stop = next_combination_skip(c, &cr);
    }
    return No_solution_found;
}

// Bruteforcing the labelings
// Solution space: size labels among {0,...,2k-1}
// vertex-labelings = the "(2k) choose n"

// Returns true if a solution was found, and puts it in the v array, otherwise returns false
// n = number of vertices
search_result search_for_solution(int n, int k, combination *c) {

    const int two_k = 2 * k;
    const long long nb_labelings = binomial_coef(two_k, n);
    const long long batch_size = 10000000LL;
    const long long nb_batches = nb_labelings / batch_size;

    *c = first_combination(two_k, n);

    // Printing progression after every batch
    for (long long i = 0; i < nb_batches; i++) {
        if (test_combinations_skip(c, batch_size) == Solution_found) // tests batch combinations
            return Solution_found;
        printf("\rChecking... %.f %%", (100.f * (i + 1)) / nb_batches);
        fflush(stdout);
    }
    printf("\n");
    return test_combinations_skip(c, nb_labelings % batch_size);
}

// Solution for n = 7
// 0, 3, 9, 15, 20, 30, 40