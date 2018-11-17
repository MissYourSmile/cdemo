VPATH = ../
test:test.o unpipc.o
	gcc -o test test.o unpipc.o
test.o:test.c
	gcc -o test.o -c test.c

.PHONY: clean
	
clean:
	rm *.o
