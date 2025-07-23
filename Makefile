CC = gcc
CFLAGS = -Wall -Wextra -ggdb3 -std=c17
LDFLAGS = -lm -lpthread -ldl -lGL -lGLEW -lglfw

# Source Files
MATH_SOURCES = $(wildcard utils/*.c)
MATH_OBJECTS = $(patsubst utils/%.c, build/%.o, $(MATH_SOURCES))

.PHONY: all clean

all: build/main

build:
	mkdir -p build

# Build each shared library
build/%.o: utils/%.c | build
	$(CC) $(CFLAGS) -c -o $@ $<

# Build main program
build/main: $(MATH_OBJECTS) main.c | build
	$(CC) $(CFLAGS) -I/usr/include/ -o $@ $^ $(LDFLAGS)

clean:
	rm -rf build/
