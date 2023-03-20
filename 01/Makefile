CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -fopenmp

.PHONY: all
all: slow medium fast

.PHONY: clean
clean:
	$(RM) slow medium fast

slow: slow.c
	$(CC) $(CFLAGS) -o $@ $^ #-lrt

medium: medium.c
	$(CC) $(CFLAGS) -o $@ $^ #-lrt

fast: fast.c
	$(CC) $(CFLAGS) -o $@ $^ #-lrt