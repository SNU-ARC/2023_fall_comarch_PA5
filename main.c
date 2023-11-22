#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>

#include "matmul.h"

int main(int argc, char **argv){
	if(argc < 2) {
		fprintf(stderr, "Usage: %s [input file]\n", argv[0]);
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");
	if(!fp) {
		fprintf(stderr, "Failed to open %s: ", argv[1]);
		perror((void*)0);
		return 0;
	}

	int M, N, K;
	fscanf(fp, "%d %d %d\n", &M, &N, &K);
	
	int *matmul_inputA = (int*)malloc(sizeof(int) * M * K);
	int *matmul_inputB = (int*)malloc(sizeof(int) * K * N);
	int *matmul_output = (int*)malloc(sizeof(int) * M * N);
	int *matmul_TA_output = (int*)malloc(sizeof(int) * M * N);

	for(int i = 0 ; i < M ; i++) {
		for(int j = 0 ; j < K ; j++) {
			fscanf(fp, "%d", matmul_inputA + (i * K + j));
		}
	}

    for(int i = 0 ; i < K ; i++) {
		for(int j = 0 ; j < N ; j++) {
			fscanf(fp, "%d", matmul_inputB + (i * N + j));
		}
	}

	memset(matmul_output, 0, sizeof(int) * M * N);
	memset(matmul_TA_output, 0, sizeof(int) * M * N);
	
	fclose(fp);

	//Time:
	struct timeval start, end, TA_end;

	gettimeofday(&start, NULL);
	matmul(M, N, K, matmul_inputA, matmul_inputB, matmul_output);
	gettimeofday(&end, NULL);
	matmul_TA(M, N, K, matmul_inputA, matmul_inputB, matmul_TA_output);
	gettimeofday(&TA_end, NULL);

	double your_time = ((double)(end.tv_sec - start.tv_sec)) + 
		(((double)(end.tv_usec - start.tv_usec)) / ((double)1000000.0));
	
	double TA_time = ((double)(TA_end.tv_sec - end.tv_sec)) + 
		(((double)(TA_end.tv_usec - end.tv_usec)) / ((double)1000000.0));

	for(int i = 0 ; i < M ; i++)
	{
		for(int j = 0 ; j < N ; j++)
		{
			if(matmul_output[i * N + j] != matmul_TA_output[i * N + j])
			{
				fprintf(stderr, "Data miscompare at input[%d][%d]! %d : %d\n",
					i, j, matmul_output[i * N + j], matmul_TA_output[i * N + j]);
				return 1;
			}
		}
	}

	printf("Your time: %lfs, TA time: %lfs\n", your_time, TA_time);

	printf("Performance: %f%%\n", 100.0f * TA_time / your_time);
	return 0;
}

