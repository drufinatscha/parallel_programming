#include<stdlib.h>
#include<stdio.h>
#include<omp.h>


#define SIZE 2048
#define REPETITIONS 1000000

int main() {
    float a[SIZE], b[SIZE], c[SIZE];
    
    // Initialize the vectors
    for (int i = 0; i < SIZE; ++i) {
        a[i] = 0.0f;
        b[i] = 1.0f;
        c[i] = 2.0f;
    }

    double start_time = omp_get_wtime();

    for (int run = 0; run < REPETITIONS; ++run) {
        #pragma omp simd
        for (int i = 0; i < SIZE; ++i) {
            a[i] += b[i] * c[i];
        }
    }

    double end_time = omp_get_wtime();
    printf("%2.4f\n", end_time - start_time);

    // Output the results
    for (int i = 0; i < SIZE; ++i) {
        if(a[i]!=2000000.0f) {
            printf("%2.4f ",a[i]);
        }
    }

    
    return EXIT_SUCCESS;
}