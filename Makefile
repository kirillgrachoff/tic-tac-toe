CC=g++
XFLAGS=-std=c++17 -DX
OFLAGS=-std=c++17 -DO

all: O X

O: src/makeMove.cpp
	$(CC) $(OFLAGS) -o O $^

X: src/makeMove.cpp
	$(CC) $(XFLAGS) -o X $^
