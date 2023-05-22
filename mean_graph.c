#include <stdio.h>
#include <stdbool.h>

/* Bruteforcing the labeling of a clique to check the soft-mean property */

// m = k-1 edges in the graph : k = m+1

int f(int a, int b, int k){
    return (((a+b)/2) % k);
}

/*
typedef struct { 
    int v[];
    int size;
} clique;
*/
 

void print_solution(int v[], int size, int k){
    printf("Sommets : %d", v[0]);
    for(int i=1; i < size; i++){
        printf(", %d", v[i]);
    }
    printf("\n Arêtes :\n");
    for(int i=0; i<size; i++){
        for(int j=i+1; j<size; j++){
            printf("%d - %d : f(%d,%d) = %d \n", v[i], v[j], v[i], v[j], f(v[i],v[j],k));
        }
    }
}

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

// TODO
// Bruteforcing the labelings
// Solution space: size labels among {0,...,2k-1}

// Puts the next labeling in the v array
void next_labeling(int v[], int size, int k){
    /*for (int i = size-1; i>=0; i--){
        
    }*/
    return;
}

// Returns true if a solution was found, and puts it in the v array, otherwise returns false
bool search_for_solution(int v[], int size, int k){
    return false;
}

int main(void){
    // correct labeling for K5
    int v5[5] = {0,3,5,10,18};
    int k = 11;
    //print_solution(v5, 5, 11);

    if (check_solution(v5,5,k)){
        printf("True");
        print_solution(v5, 5, k);
    }
    else{
        printf("False");
    }

    return 0;
}