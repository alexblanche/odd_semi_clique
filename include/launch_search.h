#ifndef SEARCH_H
#define SEARCH_H

#include "binomials.h"

// Labeling function for the edges
inline int f (int a, int b) { // , int k) {
    return ((a >> 1) + (b >> 1) + ((a & 1) && (b & 1))) % K;
}


// Prints a solution with the format:
/*
Vertices : 0, 3, 5, 10, 18
 Edges:
0 - 3 : f(0,3) = 1 
0 - 5 : f(0,5) = 2 
...
*/
void print_solution(const combination *c);

typedef enum {
    Solution_found, No_solution_found
} search_result;

typedef enum {
    Naive, Skip
} search_type;

// Bruteforcing the labelings
// Solution space: n labels among {0,...,2k-1}
// vertex-labelings = the "(2k) choose n"

// Returns true if a solution was found, and puts it in the c combination, otherwise returns false
search_result search_for_solution(int n, int k, combination *c, search_type type);

#endif