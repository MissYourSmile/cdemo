test: test.o max.o min.o
	gcc -o test test.o max.o min.o

test.o: test.c
	gcc -o test.o -c test.c

max.o: max.c
	gcc -o max.o -c max.c

min.o: min.c
	gcc -o min.o -c min.c

.PHONY: clean

clean:
	rm *.o -rf test
