CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp -O2

.PHONY: all
all: merge_sort_seq merge_sort_omp

.PHONY: clean
clean:
	$(RM) merge_sort_seq merge_sort_omp

merge_sort_seq: merge_sort_seq.c

merge_sort_omp: merge_sort_omp.c