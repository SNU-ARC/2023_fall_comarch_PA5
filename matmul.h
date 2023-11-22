#ifndef MATMUL_H
#define MATMUL_H

void matmul(const int M, const int N, const int K, const int *inputA, const int *inputB, int *output);
void matmul_TA(const int M, const int N, const int K, const int *inputA, const int *inputB, int *output);

#endif
