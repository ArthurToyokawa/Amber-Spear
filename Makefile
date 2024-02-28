CC = g++
CFLAGS = -g -Wall
LIBS = -lSDL2 -lSDL2_image

main: main.o game.o
	$(CC) $(CFLAGS) -o main main.o game.o $(LIBS)
	./main

main.o: main.cpp game.hpp
	$(CC) $(CFLAGS) -c main.cpp

game.o: game.cpp game.hpp
	$(CC) $(CFLAGS) -c game.cpp
