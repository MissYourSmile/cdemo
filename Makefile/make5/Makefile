CFLAGS = -g -Wall -Werror
SRC = $(wildcard *.c)
TARGET = $(patsubst %.c, %, $(SRC))

.PHONY: all clean

all: $(TARGET)

%: %.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	$(RM) $(TARGET)
