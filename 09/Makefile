CFLAGS = -std=gnu11 -Wextra -O2 -fopenmp -ftree-vectorize -fopt-info-vec-all-internals

.PHONY: all
all: analysis

.PHONY: clean
clean:
	$(RM) analysis

analysis: analysis.c
	$(CC) $(CFLAGS) $^ -o $@