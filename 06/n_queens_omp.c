#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

int placable(int* board, int row, int col) {
    for (int i = 0; i < row; i++) {
        // check if there is a queen in the same column or diagonal
        if (board[i] == col || abs(row - i) == abs(col - board[i])) {
            return 0;
        }
    }
    return 1;
}

void calculate(int* board, int row, int N, int* solutions) {
    if (row == N) {
        #pragma omp atomic
        (*solutions)++;
        return;
    }
    
    int new_board[N];
    
    #pragma omp taskgroup
    for (int col = 0; col < N; col++) {
        if (placable(board, row, col)) {
            #pragma omp simd
            for (int i = 0; i < N; i++) {
                new_board[i] = board[i];
            }
            new_board[row] = col;
            #pragma omp task shared(solutions) if (row < 4)
            calculate(new_board, row + 1, N, solutions);
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <N>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    int N = atoi(argv[1]);
    
    // calculate the number of solutions for the given board size
    int* solutions = malloc(sizeof(int));
    *solutions = 0;
    
    int* board = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        board[i] = 0;
    }
    
    double start_time = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            calculate(board, 0, N, solutions);
        }
    }
    #pragma omp taskwait
    double end_time = omp_get_wtime();
    
    printf("Number of solutions: %d\n", *solutions);
    printf("Time: %2.4f seconds\n", end_time - start_time);
    
    free(solutions);
    free(board);
    
    return EXIT_SUCCESS;
}
