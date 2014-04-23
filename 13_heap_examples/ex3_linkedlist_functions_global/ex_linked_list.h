#ifndef EX_LINKED_LIST_H
#define EX_LINKED_LIST_H

struct struct_of_ints {
	int value ;
	struct struct_of_ints *next ;
} ;

struct struct_of_ints* create_list(int value) ;
struct struct_of_ints* add_to_list(int value) ;
int                    delete_from_list(int value) ;
void				   delete_list() ;
struct struct_of_ints* search_list(int value) ;
void                   print_list () ;

#endif