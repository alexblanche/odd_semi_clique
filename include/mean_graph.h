#ifndef MEAN_GRAPH_H
#define MEAN_GRAPH_H

#include <stdbool.h>

#include "binomials.h"

/* Bruteforcing the labeling of a clique to check the soft-mean property */
// m = k-1 edges in the graph : k = m+1

// Prints a solution with the format:
/*
Vertices : 0, 3, 5, 10, 18
 Edges:
0 - 3 : f(0,3) = 1 
0 - 5 : f(0,5) = 2 
...
*/
void print_solution(const combination *c);

// Bruteforcing the labelings
// Solution space: size labels among {0,...,2k-1}
// vertex-labelings = the "(2k) choose n"

typedef enum {
    Solution_found, No_solution_found
} search_result;

// Returns true if a solution was found, and puts it in the c combination, otherwise returns false
search_result search_for_solution(int n, int k, combination *c);

#endif