CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -fopenmp -O1 -ftree-vectorize

.PHONY: all clean

all: addvectors 

addvectors: addvectors.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f addvectors