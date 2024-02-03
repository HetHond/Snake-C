CC=gcc
LIBS=-lncurses
DEPS=snake.h world.h utils.h
OBJ=build/main.o build/snake.o build/world.o build/utils.o

# VPATH is used to specify directories where make should look for the prerequisites
VPATH=src

build/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# The target for making the snake executable
snake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# The target for cleaning the build directory
clean:
	rm -f build/*.o snake
