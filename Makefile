
CC = gcc
CFLAGS = -Wall -Wextra -O0 -g -ansi -pedantic-errors -c

LD = cc
LDFLAGS = 

OBJECTS = main.o

TARGET = ./project

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

all: $(TARGET)

.PHONY: run
run: all
	$(TARGET)

.PHONY: clean
clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)

