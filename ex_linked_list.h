#ifndef EX_LINKED_LIST_H
#define EX_LINKED_LIST_H

/* using typedef simplifies syntax a bit */
typedef struct struct_of_ints_struct struct_of_ints ;

struct struct_of_ints_struct {
	int value ;
	struct struct_of_ints_struct *next ;
} ;

/* Each function requires head_pointer to be passed in.
   Makes functions more like functions than methods
   meaning, more reusable to maintain more than one
   linked list of struct_of_ints type */

struct_of_ints* add_to_list      (struct_of_ints *head_node, int value) ;
struct_of_ints* search_list      (struct_of_ints *head_node, int value) ;
struct_of_ints* delete_from_list (struct_of_ints *head_node, int value) ;
struct_of_ints* delete_list      (struct_of_ints *head_node) ;
void            print_list       (struct_of_ints *head_node) ;
void 			print_list_simple(struct_of_ints *head_node) ;

#endif