UNAME_S = $(shell uname -s)

CC = gcc
CFLAGS = -Ivendor
LDFLAGS = vendor/GLAD/glad.o -lm -lglfw -lGL -lX11 -lXrandr -lXi -ldl -lpthread

SRC = $(wildcard src/**/*.c) $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TARGET = bin

.PHONY: all clean

all: dir lib petecraft

lib:
	cd vendor/GLAD && $(CC) -o glad.o -c glad.c

dir:
	mkdir -p ./$(TARGET)

run: all
	$(TARGET)/petecraft

petecraft: $(OBJ)
	$(CC) -o $(TARGET)/petecraft $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(TARGET) $(OBJ)