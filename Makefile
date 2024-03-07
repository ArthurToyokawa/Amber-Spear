CC = g++
CFLAGS = -g -Wall
LIBS = -lSDL2 -lSDL2_image

main: main.o game.o gameObject.o map.o textureManager.o 
	$(CC) $(CFLAGS) -o game main.o game.o map.o gameObject.o textureManager.o $(LIBS)
	./game

main.o: ./src/main.cpp ./src/game.hpp
	$(CC) $(CFLAGS) -c ./src/main.cpp

game.o: ./src/game.cpp ./src/game.hpp ./src/textureManager.cpp ./src/ECS/ECS.hpp ./src/ECS/components.hpp
	$(CC) $(CFLAGS) -c ./src/game.cpp

gameObject.o: ./src/gameObject.cpp ./src/gameObject.hpp ./src/textureManager.cpp
	$(CC) $(CFLAGS) -c ./src/gameObject.cpp

map.o: ./src/map.cpp ./src/map.hpp ./src/textureManager.cpp
	$(CC) $(CFLAGS) -c ./src/map.cpp

textureManager.o: ./src/textureManager.cpp ./src/textureManager.hpp
	$(CC) $(CFLAGS) -c ./src/textureManager.cpp
