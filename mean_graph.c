#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "binomials.c"

/* Bruteforcing the labeling of a clique to check the soft-mean property */
// m = k-1 edges in the graph : k = m+1

// Labeling function for the edges
int f(int a, int b, int k){
    return (((a+b)/2) % k);
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
    for(int i=1; i < size; i++){
        printf(", %d", v[i]);
    }
    printf("\n Edges:\n");
    for(int i=0; i<size; i++){
        for(int j=i+1; j<size; j++){
            printf("%d - %d : f(%d,%d) = %d \n", v[i], v[j], v[i], v[j], f(v[i],v[j],k));
        }
    }
}

// Check whether the labeling v is a solution for the soft-meanness property for the clique Kn
bool check_solution(int v[], int size, int k){
    bool seen[k];
    for (int i=0; i<k; i++){
        seen[i] = false;
    }
    int x;
    for(int i=0; i<size; i++){
        for(int j=i+1; j<size; j++){
            x = f(v[i],v[j],k);
            if (seen[x]){
                return false;
            }
            else {
                seen[x] = true;
            }
        }
    }
    return true;
}

// Bruteforcing the labelings
// Solution space: size labels among {0,...,2k-1}
// vertex-labelings = the "(2k) choose n"

// Returns true if a solution was found, and puts it in the v array, otherwise returns false
// n = number of vertices
bool search_for_solution(int v[], int n, int k){
	int nb_labelings = n_choose_k(2*k,n);
	first_binomial(n,v);
	for (int i = 0; i<nb_labelings; i++){
        if (check_solution(v,n,k)){
            return true;
        }
        else {
            next_binomial(n,2*k,v);
        }
		printf("Checking... %d / %d ",i+1,nb_labelings);
        print_array(v,n);
	}
    return false;
}

int main(void){
    int n = 7;
    int k = ((n*(n-1))/2)+1; // m = |E(K5)| = 10, k = m+1
    //int v[5] = {0,3,5,10,18};
    // bool b = check_solution(v,n,k);
    int v[n];
    print_array(v,n);
    bool b = search_for_solution(v,n,k);
    if (b){
        printf("A solution was found!\n");
        print_solution(v,n,k);
    }
    else {
        printf("No solution was found.");
    }
    return EXIT_SUCCESS;
}