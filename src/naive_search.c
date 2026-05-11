#include <stdio.h>
#include <string.h>

#include "launch_search.h"
#include "naive_search.h"

/* Bruteforcing the labeling of a clique to check the soft-mean property */
// m = k-1 edges in the graph : k = m+1

// Check whether the labeling v is a solution for the soft-meanness property for the clique Kn
combination_status check_solution(const combination *c) {

    static bool seen[K];
    memset(seen, 0, K * sizeof(bool));

#define OPTIM
#ifndef OPTIM
    for (int i = 0; i < c->b; i++) {

        for (int j = i + 1; j < c->b; j++) {
            const int x = f(c->t[i], c->t[j]);//, (c->a) / 2);
            if (seen[x])
                return Combination_invalid;
            seen[x] = true;
        }
    }
#else
    for (int i = 0; i < c->b; i++) {

        const f_res resa = fa(c->t[i]);
        for (int j = i + 1; j < c->b; j++) {
            const int x = (resa.half + f_sum(c->t[j], resa.mod)) % K;
            if (seen[x])
                return Combination_invalid;
            seen[x] = true;
        }
    }
#endif
    return Combination_valid;
}


search_result test_combinations_naive(combination *c, long long nb) {
    for (long long j = 0; j < nb; j++) {
        if (check_solution(c) == Combination_valid)
            return Solution_found;
        next_combination(c);
    }
    return No_solution_found;
}