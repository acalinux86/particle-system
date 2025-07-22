CC = gcc
CFLAGS = -Wall -Wextra -ggdb3 -std=c17 -fPIC
LDFLAGS = -lm -lpthread -ldl

# Source Files
MATH_SOURCES = utils/vector2.c utils/vector3.c utils/vector4.c utils/matvec.c utils/matrix.c
MATH_LIBS = $(patsubst utils/%.c,build/lib%.so,$(MATH_SOURCES))
LIB_NAMES = vector2 vector3 vector4 matrix matvec
LINK_FLAGS = $(addprefix -l,$(LIB_NAMES))

.PHONY: all clean run

all: $(MATH_LIBS) build/main

run: build/main
	LD_LIBRARY_PATH="./build" ./build/main

build:
	mkdir -p build

# Build each shared library
build/lib%.so: utils/%.c | build
	$(CC) $(CFLAGS) -shared -o $@ $< $(LDFLAGS)

# Build main program
build/main: main.c $(MATH_LIBS) | build
	$(CC) $(CFLAGS) -o $@ $< -Lbuild $(LINK_FLAGS) $(LDFLAGS)

clean:
	rm -rf build
