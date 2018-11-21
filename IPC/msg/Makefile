VPATH = ../
CFLAGS = -g -Wall -Werror
SRC = $(wildcard *.c)
TARGET = $(patsubst %.c, %, $(SRC))
CC = gcc
.PHONY: all clean

all: $(TARGET)

%: %.c unpipc.o
	@echo begin build $@
	@$(CC) $(CFLAGS) -o $@ $^
	@echo build $@ finish
unpipc.o: unpipc.c
	@echo begin build $@
	@$(CC) $(CFLAGS) -o $@ -c $^
	@echo build $@ finish

.PHONY: clean install
clean:
	@$(RM) mymsg
	@$(RM) $(TARGET)
	@echo clean finish

install:
	@touch mymsg
	@echo install finish
