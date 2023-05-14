CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp -O2

.PHONY: all
all: n_queens_seq n_queens_omp

.PHONY: clean
clean:
	$(RM) n_queens_seq n_queens_omp

n_queens_seq: n_queens_seq.c

n_queens_omp: n_queens_omp.c