libmax.so: max.o
	gcc -shared -o $@ $^
	@cp $@ /lib64
max.o: max.c
	gcc -o $@ -c $^

remove: 
	rm libmax.so /lib64/libmax.so -f
