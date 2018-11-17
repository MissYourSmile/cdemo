VPATH = ../
all:ser cli
ser:ser.o unpipc.o
	gcc -o ser ser.o unpipc.o
cli:cli.o unpipc.o 
	gcc -o cli cli.o unpipc.o
ser.o:ser.c
	gcc -o ser.o -c ser.c
cli.o:cli.c
	gcc -o cli.o -c cli.c 


.PHONY : clean remove

clean:
	rm -rf *.o
remove:
	rm -rf write_fifo read_fifo ser cli
