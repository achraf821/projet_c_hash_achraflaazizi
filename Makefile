CC = gcc
CFLAGS = -std=c17 -O2 -Wall -Wextra -Isrc
LIBS = -lcrypto
SRCS = src/main.c src/generate.c src/lookup.c src/hash.c src/hashtable.c
OBJ = $(SRCS:.c=.o)


all: prog


prog: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)


clean:
	rm -f src/*.o prog


.PHONY: all clean