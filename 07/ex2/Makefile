CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp -O1

.PHONY: all
all: float_seq float_omp double_seq double_omp

.PHONY: clean
clean:
	$(RM) float_seq float_omp double_seq double_omp

float_seq: float_seq.c

float_omp: float_omp.c

double_seq: double_seq.c

double_omp: double_omp.c