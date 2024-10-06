CC = g++
CFLAGS = -g -Wall -std=c++23 -I./include -I../src

SRC = points.cpp ../src/pointCounter.hpp
TARGET = ./obj/pointsTest

all: clear $(TARGET) 
	$(TARGET)

$(TARGET):
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clear:
	rm -f $(TARGET)
