src = $(wildcard *.c */*.c)

LDFLAGS += -lraylib

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

build:
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/megabrank $(src) $(LDFLAGS)

clean:
	rm -r bin/
