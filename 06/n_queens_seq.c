#include<stdlib.h>
#include<stdio.h>
#include<omp.h>

int placable(int* board, int row, int col) {
    for (int i = 0; i < row; i++) {
        // check if there is a queen in the same column or diagonal
        if (board[i] == col || abs(row - i) == abs(col - board[i])) {
            return 0;
        }
    }
    return 1;
}

int calculate(int* board, int row, int N) {
    if (row == N) {
        return 1;
    }
    int solutions = 0;
    for (int col = 0; col < N; col++) {
        if (placable(board, row, col)) {
            board[row] = col;
            solutions += calculate(board, row + 1, N);
            board[row] = 0;
        }
    }
    return solutions;
}


int main(int argc, char** argv) {
    if(argc < 2) {
        printf("Usage: %s <N>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int N = 0;
    if (argc > 1) {
        N = atoi(argv[1]);
    }

    int solutions = 0;
    int* board = malloc(sizeof(int)  * N * N);
    for (int i = 0; i < N * N; i++) {
        board[i] = 0;
    }

    double start_time = omp_get_wtime();
    
    solutions = calculate(board, 0, N);

    double end_time = omp_get_wtime();

    printf("Number of solutions: %d\n", solutions);

    printf("Time: %2.4f seconds\n", end_time - start_time);

    return EXIT_SUCCESS;
}


