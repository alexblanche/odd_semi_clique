#include <stdio.h>

// Returns n choose k
int n_choose_k(int n, int k) {
	if (k == 0 || k == n){
	   	return 1;
	}
	else {
		return n_choose_k(n-1, k-1) + n_choose_k(n-1, k);
	}
}


/*
6 choose 4
0123 0234 1234 2345
0124 0235 1235
0125 0245 1245
0134 0345 1345
0135
0145
*/


// Puts the array {0,1,...,k-1} in the array res
void first_binomial(int k, int res[]){
	for(int i=0; i<k; i++){
		res[i] = i;
	}
}


// bin contains a choice of k integers among {0,...,n-1}
// The function returns the next one in the bin array
void next_binomial(int k, int n, int bin[]){
	for(int i = k-1; i >= 0; i--){
		if (bin[i] <  n-k+i){
			// in this case bin[i+1,...,k-1] = n-1-(k-1-i),...,n-2,n-1
			// n-1-(k-1-i) = n-k+i
			bin[i] += 1;
			int a = bin[i];
			for(int j = i+1; j<k; j++){
				a++;
				bin[j] = a;
			}
			return;
		}
	}
}


// prints the array t under the format :
// {12,3,4,18} -> 12 3 4 18
void print_array(int t[], int size){
	for(int i = 0; i<size; i++){
		printf("%d ",t[i]);
	}
	printf("\n");
}

int main(){
	int n = 5;
	int k = 3;
	int nchk = n_choose_k(n,k);
	int bin[k];
	first_binomial(k,bin);
	print_array(bin,k);
	for (int i = 0; i<nchk-1; i++){
		next_binomial(k,n,bin);
		print_array(bin,k);
	}
	return 0;
}







