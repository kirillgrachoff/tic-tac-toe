CC=g++
XFLAGS=-std=c++17 -DX
OFLAGS=-std=c++17 -DO

all: O X

O: makeMove.cpp
	$(CC) $(OFLAGS) -o O $^

X: makeMove.cpp
	$(CC) $(XFLAGS) -o X $^
