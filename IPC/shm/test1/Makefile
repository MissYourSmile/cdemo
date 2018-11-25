VPATH = ../
CFLAGS = -g -Wall -Werror
SRC = $(wildcard *.c)
TARGET = $(patsubst %.c, ./bin/%, $(SRC))
CC = gcc
.PHONY: all clean

all: $(TARGET)

./bin/%: %.c unpipc.o
	@mkdir -p bin
	@echo begin build $@
	@$(CC) $(CFLAGS) -o $@ $^
	@echo build $@ finish
unpipc.o: unpipc.c
	@echo begin build $@
	@$(CC) $(CFLAGS) -o $@ -c $^
	@echo build $@ finish

.PHONY: clean install
clean:
	@$(RM) $(TARGET)
	@rm -rf bin
	@echo clean finish

install:
	@touch bin/mysem bin/myshm
	@echo install finish
