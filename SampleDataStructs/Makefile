all: main

ex_linked_list.o: ex_linked_list.c ex_linked_list.h
	clang -c ex_linked_list.c

ex_hash_table.o: ex_hash_table.c ex_hash_table.h ex_linked_list.o
	clang -c ex_hash_table.c 

main: main.c ex_linked_list.o ex_hash_table.o
	clang -o main main.c ex_linked_list.o ex_hash_table.o

clean: 
	rm -rf *.o

clobber: clean
	rm -rf main
