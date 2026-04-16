#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "mean_graph.h"
#include "parameters.h"

int main() {

    const int n = N;
    const int k = K; // ((n * (n-1)) / 2) + 1; // k = m + 1

    combination c;
    const bool res = search_for_solution(n, k, &c);

    if (res){
        printf("n = %d: a solution was found!\n", n);
        print_solution(&c);
        printf("n = %d: done\n", n);
    }
    else {
        printf("n = %d: no solution was found\n", n);
    }
    
    return EXIT_SUCCESS;
}

// Results: n = 2,...,7 are soft-mean
// n = 8 is NOT soft-mean
