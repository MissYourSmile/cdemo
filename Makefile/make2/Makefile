test: test.o max.o min.o
	gcc -o test test.o max.o min.o
test.o: test.c
max.o: max.c
min.o: min.c

.PHONY: clean
clean:
	rm *.o -rf test
