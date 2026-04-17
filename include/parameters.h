#ifndef PARAM_H
#define PARAM_H

#define N 8
#define K (((N * (N - 1)) / 2) + 1) // k = m + 1


typedef enum {
    Combination_valid, Combination_invalid
} combination_status;

typedef struct {
    combination_status res;
    int max_culprit;
} check_result;

#endif