#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PERROR fprintf(stderr, "%s:%d: error: %s\n", __FILE__, __LINE__, strerror(errno))
#define PERROR_GOTO(label) \
    do { \
        PERROR; \
        goto label; \
    } while (0)

#define INIT_ARRAY(arr, label) \
    do { \
        if (!(arr)) PERROR_GOTO(label); \
        for (long i = 0; i < n; ++i) { \
            (arr)[i] = malloc(sizeof(**(arr)) * n); \
            if (!(arr)[i]) PERROR_GOTO(label); \
        } \
    } while (0)

void free_2d_array(int **arr, long len) {
    if (!arr) {
        return;
    }
    for (long i = 0; i < len; ++i) {
        if (!arr[i]) {
            break;
        }
        free(arr[i]);
    }
    free(arr);
}

int main(int argc, char **argv) {
    // handle input
    if (argc != 3) {
        fprintf(stderr, "Error: usage: %s <n> <t>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *str = argv[1];
    char *endptr;
    long n = strtol(str, &endptr, 0);

    if (endptr == str) {
        fprintf(stderr, "Error: no digits were found!\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Error: matrix size must not be negative!\n");
        return EXIT_FAILURE;
    }

    long threads = strtol(argv[2], &endptr, 0);

    if (endptr == str) {
        fprintf(stderr, "Error: no digits were found!\n");
        return EXIT_FAILURE;
    }

    if (threads < 0) {
        fprintf(stderr, "Error: thread amount must not be negative!\n");
        return EXIT_FAILURE;
    }

    // allocate memory
    int status = EXIT_FAILURE;
    int **a = malloc(sizeof(*a) * n);
    INIT_ARRAY(a, error_a);
    int **b = malloc(sizeof(*b) * n);
    INIT_ARRAY(b, error_b);
    int **c = malloc(sizeof(*c) * n);
    INIT_ARRAY(c, error_c);
    unsigned *local_res = malloc(omp_get_max_threads() * sizeof(*local_res));
    if (!local_res) PERROR_GOTO(error_c);
    status = EXIT_SUCCESS;

    // fill matrix
    srand(7);
    for (long i = 0; i < n; ++i) {
        for (long j = 0; j < n; ++j) {
            a[i][j] = rand();
            b[i][j] = rand();
        }
    }

    unsigned long res = 0;
    omp_set_num_threads((int) threads);
    double start_time = omp_get_wtime();
#pragma omp parallel shared(n, a, b, c)
    {
#pragma omp for
        for (long i = 0; i < n; ++i) {
            for (long k = 0; k < n; ++k) {
                for (long j = 0; j < n; ++j) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
#pragma omp for
        for (long i = 0; i < n; ++i) {
            for (long j = 0; j < n; ++j) {
                local_res[omp_get_thread_num()] += c[i][j];
            }
        }
#pragma omp for reduction(+:res)
        for (int l = 0; l < omp_get_num_threads(); ++l) {
            res += local_res[l];
        }
    }
    double end_time = omp_get_wtime();
    printf("res: %lu, time: %2.2f seconds\n", res, end_time - start_time);

    // cleanup
    free(local_res);
    error_c:
    free_2d_array(c, n);
    error_b:
    free_2d_array(b, n);
    error_a:
    free_2d_array(a, n);
    return status;
}