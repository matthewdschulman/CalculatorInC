all: main

hash_table.o: hash_table.c hash_table.h
	clang -c hash_table.c

main: main.c hash_table.o
	clang -o main main.c hash_table.o

clean:
	rm -rf *.o

clobber: clean
	rm -rf main
