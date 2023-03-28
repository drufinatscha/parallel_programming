
CC=gcc
CFLAGS=-fopenmp -g -std=c99 -Wall -Wextra -pedantic 

all: implementation1 implementation2 

implementation1: implementation1.c
	$(CC) $(CFLAGS) -o implementation1 implementation1.c

implementation2: implementation2.c
	$(CC) $(CFLAGS) -o implementation2 implementation2.c


clean:
	rm -f implementation1 implementation2 

