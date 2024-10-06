MAKEFLAGS += -j

CC = g++
CFLAGS = -g -Wall -std=c++23 -I./include -I/usr/include/SDL2
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf
SRCDIR = ./src
OBJDIR = ./obj

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

all: clear game 
	./game 

game: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)


clear:
	rm -f game $(OBJS)
