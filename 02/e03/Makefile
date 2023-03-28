CFLAGS = -Wall -Wextra -Werror -std=gnu11 -O2 -fopenmp
LDFLAGS = -lpthread

.PHONY: all clean

all: exercise3

clean:
	rm exercise3

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)