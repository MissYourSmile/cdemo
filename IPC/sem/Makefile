VPATH = ../

objects = create_sem rm_sem

BIN_DIR := ./bin
SRC_DIR := .

all: $(objects)

#$(BIN_DIR)/%: $(SRC_DIR)/%.c unpipc.o
$(objects):% : %.c unpipc.o
	gcc -o $@ $< unpipc.o
