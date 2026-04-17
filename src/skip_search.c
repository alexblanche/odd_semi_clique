#include "naive_search.h"
#include "launch_search.h"

#include <string.h>

inline check_result order(int j1, int j2) {
    
    return (check_result) {
        Combination_invalid,
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
    return (check_result) { .res = Combination_valid };
}

search_result test_combinations_skip(combination *c, long long nb) {

    for (long long j = 0; j < nb; j++) {

        const check_result cr = check_solution_with_culprits(c);
        if (cr.res == Combination_valid)
            return Solution_found;

        const enumeration_status status = next_combination_skip(c, &cr);
        if (status == Stop_enumeration)
            break;
    }

    return No_solution_found;
}