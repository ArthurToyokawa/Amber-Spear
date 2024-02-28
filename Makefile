CC = g++
CFLAGS = -g -Wall
LIBS = -lSDL2 -lSDL2_image

main: main.o game.o
	$(CC) $(CFLAGS) -o game main.o game.o $(LIBS)
	./game

main.o: ./src/main.cpp ./src/game.hpp
	$(CC) $(CFLAGS) -c ./src/main.cpp

game.o: ./src/game.cpp ./src/game.hpp
	$(CC) $(CFLAGS) -c ./src/game.cpp
