CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c11 -O2 -DNDEBUG
SOURCES=utilities.c bintree.c akinator.c main.c
EXECUTABLE=akinator

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

.PHONY: clean
clean:
	rm *.png *.dot *.out $(EXECUTABLE)

.PHONY: run
run:
	./$(EXECUTABLE)
