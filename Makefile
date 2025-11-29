# Super simple Advent of Code Makefile
# Usage: make day1 input.txt 42

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -O2 -Ilib

DAY     := $(firstword $(MAKECMDGOALS))
SRC     := $(DAY)/main.c
DIST    := $(DAY)/dist
TARGET  := $(DIST)/main

RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))

.PHONY: $(DAY) clean

$(DAY):
	@mkdir -p $(DIST)
	$(CC) $(CFLAGS) lib/*.c $(SRC) -o $(TARGET)
	@./$(TARGET) $(DAY)/$(RUN_ARGS)

$(eval $(RUN_ARGS):;)

clean:
	rm -rf day*/dist
