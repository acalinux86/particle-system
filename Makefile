CC = gcc
CFLAGS = -Wall -Wextra -ggdb3 -std=c17
LDFLAGS = -lm -lpthread -ldl -lGL -lGLEW -lglfw

# Source Files
SRC = $(wildcard src/*.c)
SRC_OBJECTS = $(patsubst src/%.c, obj/%.o, $(SRC))

.PHONY: all clean

all: build/main

build:
	mkdir -p build obj

# Build each src file to object file from SRC folder
obj/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c -o $@ $<

# Build main program
build/main: $(SRC_OBJECTS) main.c | build
	$(CC) $(CFLAGS) -I/usr/include/ -o $@ $^ $(LDFLAGS)

clean:
	rm -rf build/ obj/
