all: cli ser

cli: cli.c
	g++ -o cli cli.c

ser: ser.c
	g++ -o ser ser.c

.PHONY: clean

clean:
	rm -f ser cli
