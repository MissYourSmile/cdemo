OBJ = test.o max.o min.o

test: $(OBJ)
	@echo "begin link"
	@gcc -o test $(OBJ)
	@echo "end link"
test.o: test.c
	@echo "begin complete test.c"
	@gcc -o test.o -c test.c
	@echo "end complete test.c"
max.o: max.c
	@echo "begin complete max.c"
	@gcc -o max.o -c max.c
	@echo "end complete max.c"
min.o: min.c
	@echo "begin complete min.c"
	@gcc -o min.o -c min.c
	@echo "end complete min.c"

clean:
	@echo "begin clean"
	@rm $(OBJ) test
	@echo "end clean"
