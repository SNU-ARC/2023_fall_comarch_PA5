#include <stdlib.h>
#include "matmul.h"

void matmul(const int M, const int N, const int K, const int *inputA, const int *inputB, int *output) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < K; k++) {
                output[i * N + j] += inputA[i * K + k] * inputB[k * N + j];
            }
        }
    }
}

