OBJ = test.o max.o min.o
CC = gcc
CFLAGS = -g
TARGET = $(patsubst %.c, %.o, $(SRC))

test: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^


.PHONY: clean

clean:
	rm *.o -rf test
