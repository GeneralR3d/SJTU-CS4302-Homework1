#include <omp.h>
#include <stdio.h>

#define M 6  // Example input dimensions
#define N 6
#define K 3  // Example filter dimensions

void convolution(float input[M][N], float filter[K][K], float output[M-K+1][N-K+1]) {
    int i, j, x, y;
    
    // Parallelizing the convolution with OpenMP
    #pragma omp parallel for collapse(2) private(i, j, x, y) reduction(+:output[:M-K+1][:N-K+1])
    for (i = 0; i <= M - K; i++) {
        for (j = 0; j <= N - K; j++) {
            output[i][j] = 0;  // Initialize the output element
            for (x = 0; x < K; x++) {
                for (y = 0; y < K; y++) {
                    output[i][j] += input[i + x][j + y] * filter[x][y];  // Dot product
                }
            }
        }
    }
}

int main() {
    float input[M][N] = {
        {1, 1, 1, 0, 0, 0},
        {0, 1, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 0},
        {0, 0, 0, 1, 1, 1},
        {0, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 1}
    };

    float filter[K][K] = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1}
    };

    float output[M-K+1][N-K+1] = {0};  // Output matrix

    convolution(input, filter, output);

    // Printing the output
    for (int i = 0; i < M-K+1; i++) {
        for (int j = 0; j < N-K+1; j++) {
            printf("%f ", output[i][j]);
        }
        printf("\n");
    }

    return 0;
}
