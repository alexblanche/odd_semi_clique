#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "parameters.h"
#include "binomials.h"

/* Bruteforcing the labeling of a clique to check the soft-mean property */
// m = k-1 edges in the graph : k = m+1

// Labeling function for the edges
inline int f(int a, int b /* , int k */){
    return (((a + b) / 2) % K);
}
 
// Prints a solution with the format:
/*
Vertices : 0, 3, 5, 10, 18
 Edges:
0 - 3 : f(0,3) = 1 
0 - 5 : f(0,5) = 2 
...
*/
void print_solution(int v[], int size, int k){
    printf("Vertices: %d", v[0]);
    for(int i = 1; i < size; i++){
        printf(", %d", v[i]);
    }
    printf("\nEdges:\n");
    for(int i = 0; i<size; i++) {
        for(int j = i + 1; j < size; j++) {
            printf("%2d - %2d: f(%2d,%2d) = %2d \n", v[i], v[j], v[i], v[j], f(v[i],v[j] /* ,k */));
        }
    }
}

// Check whether the labeling v is a solution for the soft-meanness property for the clique Kn
bool check_solution(int v[], int size, int k) {

    static bool seen[K];
    memset(seen, false, sizeof(bool));

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            const int x = f(v[i], v[j] /*, k */);
            if (seen[x])
                return false;
            seen[x] = true;
        }
    }
    return true;
}

// Bruteforcing the labelings
// Solution space: size labels among {0,...,2k-1}
// vertex-labelings = the "(2k) choose n"

// Returns true if a solution was found, and puts it in the v array, otherwise returns false
// n = number of vertices
bool search_for_solution(int v[], int n, int k) {

    const int two_k = 2 * k;
    const long long nb_labelings = binomial_coef(two_k, n);
    const long long step = 10000000;
    const long long nblabred = nb_labelings / step;
    first_binomial(n,v);
    
    for (long long i = 0; i < nblabred; i++) {
        
        for (long long j = 0; j < step; j++) {
            if (check_solution(v, n, k))
                return true;
            
            next_binomial(n, two_k, v);
        }

        printf("\rChecking... %.f %%", (100.f * (i+1)) / nblabred);
        fflush(stdout);

    }
    printf("\n");

    const int remaining = nb_labelings % step;
    for (int j = 0; j < remaining; j++) {
        if (check_solution(v, n, k))
            return true;
        next_binomial(n, two_k, v);
    }
    return false;
}

