#include <stdio.h>
#include "ex_linked_list.h"

#define LIST_LEN 10

int main ()
{

	int i = 0 ;
	int search = 5 ;

	print_list () ;


	// populate list
	printf ("\nPopulating list with %d nodes\n", LIST_LEN) ;

	for (i = 0; i<LIST_LEN ; i++ )
		add_to_list (i) ;

	print_list () ;


	// search list
	printf ("\nSearching list for value %d\n", search ) ;

	if (search_list (search) != NULL) printf("FOUND IT!\n") ;
	else printf("NOT FOUND\n") ;

	// delete one item from list
	printf ("\nDeleting value %d from list\n", search ) ;
	delete_from_list(search) ;

	printf ("\nSearching list for value %d\n", search ) ;

	if (search_list (search) != NULL) printf("FOUND IT!\n") ;
	else printf("NOT FOUND\n") ;

	print_list () ;

	// free all memory - destroy list
	delete_list() ;
	print_list () ;

	return 0 ;
}
