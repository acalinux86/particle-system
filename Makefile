CC = gcc
CFLAGS = -Wall -Wextra -ggdb3 -std=c17 -I/usr/include/
LDFLAGS = -lm -lpthread -ldl -lGL -lGLEW -lglfw

# Source Files
MATH_SOURCES = utils/vector2.c utils/vector3.c utils/vector4.c utils/matvec.c utils/matrix.c
MATH_OBJECTS = $(patsubst utils/%.c, build/%.o, $(MATH_SOURCES))

.PHONY: all clean

all: build/main

build:
	mkdir -p build

# Build each shared library
build/%.o: utils/%.c | build
	$(CC) $(CFLAGS) -c -o $@ $<

# Build main program
build/main: $(MATH_OBJECTS) main.c file.c | build
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf build/
