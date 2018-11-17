OBJ = test.o max.o min.o
CC = gcc
CFLAGS = -g

test: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

test.o: test.c
	$(CC) $(CFLAGS) -o $@ -c $^
max.o: max.c
	$(CC) $(CFLAGS) -o $@ -c $^
min.o: min.c
	$(CC) $(CFLAGS) -o $@ -c $^

.PHONY: clean

clean:
	rm *.o -rf test
