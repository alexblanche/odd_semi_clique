#ifndef MEAN_GRAPH_H
#define MEAN_GRAPH_H

#include <stdbool.h>

#include "binomials.h"
#include "launch_search.h"

// Optimization of f computation

typedef struct {
    int half;
    bool mod;
} f_res;

inline f_res fa(int a) {
    return (f_res) { a >> 1, a & 1 };
}
inline int f_sum(int b, bool m) {
    return (b >> 1) + (m ? (b & 1) : 0);
}

search_result test_combinations_naive(combination *c, long long nb);

#endif