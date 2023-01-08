CC=gcc
CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++11 -ggdb -DNDEBUG
LIBS=-lFestival -lestbase -lestools -leststring -lncurses -lasound -fopenmp
SOURCES=utilities.c bintree.c akinator.cpp main.c
EXECUTABLE=akinator

all:
	$(CXX) $(CXXFLAGS) $(LIBS) $(SOURCES) -o $(EXECUTABLE)

.PHONY: clean
clean:
	rm *.png *.dot *.out $(EXECUTABLE)

.PHONY: run
run:
	./$(EXECUTABLE)
