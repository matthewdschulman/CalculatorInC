#include <stdio.h>
#include "ex_linked_list.h"

#define LIST_LEN 10
#define SEARCH 5

int main ()
{

	int i = 0 ;
	struct_of_ints *my_list = NULL ;

	print_list (my_list) ;

	// populate list
	//
	printf ("\nPopulating list with %d nodes\n", LIST_LEN) ;

	for (i = 0; i<LIST_LEN ; i++ ) {
		if (my_list == NULL) {
			my_list = add_to_list(my_list, i) ;	// 1st call to add_to_list creates list
		}
		else {
			add_to_list(my_list, i) ;  			// subsequent calls add to end of list
		}
	}

	print_list (my_list) ;


	// search list
	//
	printf ("\nSearching list for value %d\n", SEARCH ) ;

	if   (search_list (my_list, SEARCH) != NULL) printf("FOUND IT!\n") ;
	else printf("NOT FOUND\n") ;


	// delete one item from list, prove it was found
	//
	printf ("\nDeleting value %d from list\n", SEARCH ) ;
	my_list = delete_from_list(my_list, SEARCH) ;

	printf ("\nSearching list for value %d\n", SEARCH ) ;
	if   (search_list (my_list, SEARCH) != NULL) printf("FOUND IT!\n") ;
	else printf("NOT FOUND\n") ;

	print_list (my_list) ;


	// free all memory - destroy list
	//
	my_list = delete_list(my_list) ;

	print_list (my_list) ;

	return 0 ;
}
