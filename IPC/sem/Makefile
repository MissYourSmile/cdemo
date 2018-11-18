VPATH = ../
CFLAGS = -g -Wall -Werror
SRC = $(wildcard *.c)
TARGET = $(patsubst %.c, %, $(SRC))
CC = gcc
.PHONY: all clean

all: $(TARGET)

%: %.c unpipc.o
	$(CC) $(CFLAGS) -o $@ $^
unpipc.o: unpipc.c
clean:
	$(RM) $(TARGET)
