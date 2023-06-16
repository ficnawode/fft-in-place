UNAME_S = $(shell uname -s)

CC = gcc 
CFLAGS = -std=c11 -Wall -Wextra -pedantic -Wstrict-aliasing
LDFLAGS =-lm

SRC  = $(wildcard *.c) $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)
OBJ  = $(SRC:.c=.o)

.PHONY: all clean

all: game

dirs:
	mkdir -p ./$(BIN)

game: $(OBJ)
	$(CC) -o main $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(OBJ) main