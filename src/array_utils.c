#include "array_utils.h"

#include <stdio.h>

void print_array (int t[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", t[i]);
	}
	printf("\n");
}