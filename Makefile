CC = gcc
CFLAGS = -Wall -Wextra -ggdb3 -std=c17
LDFLAGS = -lm -lpthread -ldl -lGL -lGLEW -lglfw

# Utils Files
UTILS_SOURCES = $(wildcard utils/*.c)
UTILS_OBJECTS = $(patsubst utils/%.c, obj/%.o, $(UTILS_SOURCES))

# Source Files
SRC = $(wildcard src/*.c)
SRC_OBJECTS = $(patsubst src/%.c, obj/%.o, $(SRC))

.PHONY: all clean

all: build/main

build:
	mkdir -p build obj

# Build each src file to object file from UTILS folder
obj/%.o: utils/%.c | build
	$(CC) $(CFLAGS) -c -o $@ $<

# Build each src file to object file from SRC folder
obj/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c -o $@ $<

# Build main program
build/main: $(UTILS_OBJECTS) $(SRC_OBJECTS) main.c | build
	$(CC) $(CFLAGS) -I/usr/include/ -o $@ $^ $(LDFLAGS)

clean:
	rm -rf build/ obj/
