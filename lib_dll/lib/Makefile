libmin.a: min.o
	ar -cr $@ $^
	@cp -p $@ /lib64
min.o: min.c
	gcc -o min.o -c min.c

remove:
	rm libmin.a /lib64/libmin.a -f
