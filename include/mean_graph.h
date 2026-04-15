#ifndef MEAN_GRAPH_H
#define MEAN_GRAPH_H

#include <stdbool.h>

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
void print_solution(int v[], int size, int k);

// Bruteforcing the labelings
// Solution space: size labels among {0,...,2k-1}
// vertex-labelings = the "(2k) choose n"

// Returns true if a solution was found, and puts it in the v array, otherwise returns false
// n = number of vertices
bool search_for_solution(int v[], int n, int k);


#endif