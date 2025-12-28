src = $(shell find . -name '*.c' ! -path './bin/*')

INCLUDES = -Isrc/
LDFLAGS += -lraylib -lm

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

build:
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/megabrank $(src) $(LDFLAGS)

run: build
	./bin/megabrank

clean:
	rm -r bin/
