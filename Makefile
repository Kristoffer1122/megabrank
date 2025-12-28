src = $(wildcard *.c */*.c */*/*.c */*/*/*.c)

LDFLAGS += -lraylib -lm

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

build:
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/megabrank $(src) $(LDFLAGS)

clean:
	rm -r bin/
