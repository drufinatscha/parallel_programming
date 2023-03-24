CFLAGS = -Wall -Wextra -Werror -std=gnu11 -fopenmp

.PHONY: all clean

all: slow medium fast

clean:
	rm slow medium fast

%: %.c
	$(CC) $(CFLAGS) -o $@ $<