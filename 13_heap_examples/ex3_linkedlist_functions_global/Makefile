all: ex_linked_list.o main

ex_linked_list.o: ex_linked_list.c ex_linked_list.h
	clang -c ex_linked_list.c

main: main.c ex_linked_list.o
	clang -o main main.c ex_linked_list.o

clean: 
	rm -rf *.o

clobber: clean
	rm -rf main
