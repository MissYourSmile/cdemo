CFLAGS = -g
LIB = -lpthread
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, obj/%.o, $(SRC))
CC = gcc
RM = rm -rf

.PHONY: all clean

all: test

test: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

obj/%.o: %.c
	@mkdir -p obj
	$(CC) -o $@ -c $^
clean:
	$(RM) $(OBJ) test obj
