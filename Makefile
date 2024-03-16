CC = g++
CFLAGS = -g -Wall
LIBS = -lSDL2 -lSDL2_image
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
