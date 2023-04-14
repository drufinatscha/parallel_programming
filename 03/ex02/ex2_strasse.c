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

void add_matrices(int **a, int **b, int **c, long n){
	#pragma omp parallel for schedule(dynamic, 4) shared(n, a, b, c)
	for (long i = 0; i < n; ++i) {
		for (long j = 0; j < n; ++j) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}

void subtract_matrices(int **a, int **b, int **c, long n){
	#pragma omp parallel for schedule(dynamic, 4) shared(n, a, b, c)
	for (long i = 0; i < n; ++i) {
		for (long j = 0; j < n; ++j) {
			c[i][j] = a[i][j] - b[i][j];
		}
	}
}

void strasse_algorithm(int **a, int **b, int **c, long n){
	if (n <= 64) {
		#pragma omp parallel for schedule(dynamic, 4) shared(n, a, b, c)
		for (long i = 0; i < n; ++i) {
			for (long j = 0; j < n; ++j) {
				c[i][j] = 0;
				for (long k = 0; k < n; ++k) {
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}
		return;
	}
	long new_n = n / 2;
	int **a11 = malloc(sizeof(*a11) * new_n);
	int **a12 = malloc(sizeof(*a12) * new_n);
	int **a21 = malloc(sizeof(*a21) * new_n);
	int **a22 = malloc(sizeof(*a22) * new_n);
	int **b11 = malloc(sizeof(*b11) * new_n);
	int **b12 = malloc(sizeof(*b12) * new_n);
	int **b21 = malloc(sizeof(*b21) * new_n);
	int **b22 = malloc(sizeof(*b22) * new_n);
	int **c11 = malloc(sizeof(*c11) * new_n);
	int **c12 = malloc(sizeof(*c12) * new_n);
	int **c21 = malloc(sizeof(*c21) * new_n);
	int **c22 = malloc(sizeof(*c22) * new_n);
	int **m1 = malloc(sizeof(*m1) * new_n);
	int **m2 = malloc(sizeof(*m2) * new_n);
	int **m3 = malloc(sizeof(*m3) * new_n);
	int **m4 = malloc(sizeof(*m4) * new_n);
	int **m5 = malloc(sizeof(*m5) * new_n);
	int **m6 = malloc(sizeof(*m6) * new_n);
	int **m7 = malloc(sizeof(*m7) * new_n);
	int **a_result = malloc(sizeof(*a_result) * new_n);
	int **b_result = malloc(sizeof(*b_result) * new_n);

	for (long i = 0; i < new_n; ++i) {
		a11[i] = calloc(new_n, sizeof(int));
		a12[i] = calloc(new_n, sizeof(int));
		a21[i] = calloc(new_n, sizeof(int));
		a22[i] = calloc(new_n, sizeof(int));
		b11[i] = calloc(new_n, sizeof(int));
		b12[i] = calloc(new_n, sizeof(int));
		b21[i] = calloc(new_n, sizeof(int));
		b22[i] = calloc(new_n, sizeof(int));
		c11[i] = calloc(new_n, sizeof(int));
		c12[i] = calloc(new_n, sizeof(int));
		c21[i] = calloc(new_n, sizeof(int));
		c22[i] = calloc(new_n, sizeof(int));
		m1[i] = calloc(new_n, sizeof(int));
		m2[i] = calloc(new_n, sizeof(int));
		m3[i] = calloc(new_n, sizeof(int));
		m4[i] = calloc(new_n, sizeof(int));
		m5[i] = calloc(new_n, sizeof(int));
		m6[i] = calloc(new_n, sizeof(int));
		m7[i] = calloc(new_n, sizeof(int));
		a_result[i] = calloc(new_n, sizeof(int));
		b_result[i] = calloc(new_n, sizeof(int));
	}

	for (long i = 0; i < new_n; ++i) {
    	for (long j = 0; j < new_n; ++j) {
        	a_result[i][j] = 0;
        	b_result[i][j] = 0;
    	}
	}
	

	// split matrices
	for (long i = 0; i < new_n; ++i) {
		for (long j = 0; j < new_n; ++j) {
			a11[i][j] = a[i][j];
			a12[i][j] = a[i][j + new_n];
			a21[i][j] = a[i + new_n][j];
			a22[i][j] = a[i + new_n][j + new_n];
			b11[i][j] = b[i][j];
			b12[i][j] = b[i][j + new_n];
			b21[i][j] = b[i + new_n][j];
			b22[i][j] = b[i + new_n][j + new_n];
		}
	}

	// calculate m1 to m7
	add_matrices(a11, a22, a_result, new_n);
	add_matrices(b11, b22, b_result, new_n);
	strasse_algorithm(a_result, b_result, m1, new_n);

	add_matrices(a21, a22, a_result, new_n);
	strasse_algorithm(a_result, b11, m2, new_n);

	subtract_matrices(b12, b22, b_result, new_n);
	strasse_algorithm(a11, b_result, m3, new_n);

	subtract_matrices(b21, b11, b_result, new_n);
	strasse_algorithm(a22, b_result, m4, new_n);

	add_matrices(a11, a22, a_result, new_n);
	strasse_algorithm(a_result, b22, m5, new_n);

	subtract_matrices(a21, a11, a_result, new_n);
	add_matrices(b11, b12, b_result, new_n);
	strasse_algorithm(a_result, b_result, m6, new_n);

	subtract_matrices(a12, a22, a_result, new_n);
	add_matrices(b21, b22, b_result, new_n);
	strasse_algorithm(a_result, b_result, m7, new_n);

	// calculate c11 to c22
	add_matrices(m1, m4, a_result, new_n);
	subtract_matrices(a_result, m5, b_result, new_n);
	add_matrices(b_result, m7, c11, new_n);

	add_matrices(m3, m5, c12, new_n);

	add_matrices(m2, m4, c21, new_n);

	subtract_matrices(m1, m2, a_result, new_n);
	add_matrices(a_result, m3, b_result, new_n);
	add_matrices(b_result, m6, c22, new_n);

	// join matrices
	#pragma omp parallel for 
	for (long i = 0; i < new_n; ++i) {
		for (long j = 0; j < new_n; ++j) {
			c[i][j] = c11[i][j];
			c[i][j + new_n] = c12[i][j];
			c[i + new_n][j] = c21[i][j];
			c[i + new_n][j + new_n] = c22[i][j];
		}
	}

	// free memory
	free(a11);
	free(a12);
	free(a21);
	free(a22);
	free(b11);
	free(b12);
	free(b21);
	free(b22);
	free(c11);
	free(c12);
	free(c21);
	free(c22);
	free(m1);
	free(m2);
	free(m3);
	free(m4);
	free(m5);
	free(m6);
	free(m7);
	free(a_result);
	free(b_result);
}

int main(int argc, char **argv) {
	// handle input
	if (argc != 2) {
		fprintf(stderr, "Error: usage: %s <n>\n", argv[0]);
		return EXIT_FAILURE;
	}
	errno = 0;
	char *str = argv[1];
	char *endptr;
	long n = strtol(str, &endptr, 0);
	if (errno != 0) {
		perror("strtol");
		return EXIT_FAILURE;
	}
	if (endptr == str) {
		fprintf(stderr, "Error: no digits were found!\n");
		return EXIT_FAILURE;
	}
	if (n < 0) {
		fprintf(stderr, "Error: matrix size must not be negative!\n");
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

	double start_time = omp_get_wtime();
#pragma omp parallel shared(n, a, b, c)
	{
		strasse_algorithm(a, b, c, n);

		// sum of matrix c
#pragma omp parallel for shared(n, a, b, c, local_res) 
		for (long i = 0; i < n; ++i) {
			for (long j = 0; j < n; ++j) {
				local_res[omp_get_thread_num()] += c[i][j];
			}
		}
	}
	unsigned long res = 0;
	for (int l = 0; l < omp_get_num_threads(); ++l) {
		res += local_res[l];
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