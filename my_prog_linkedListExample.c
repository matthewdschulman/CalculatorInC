#include <stdio.h>
#include <stdlib.h>

int main () {

	struct struct_of_ints {
		int value ;
		struct struct_of_ints *next ;
	} ;


	/* allocate 1 element list (head of list) */
	struct struct_of_ints *my_list = 
		malloc (sizeof (struct struct_of_ints) ) ;


	/* dummy pointer used for deleting nodes */
	struct struct_of_ints *temp = NULL ;

	/* fill 1st element in list */
	my_list->value = 1    ;	// “->” special syntax access field
	my_list->next  = NULL ;	// of struct through pointer

	/* lets add one to the list */
	my_list->next = 
		malloc (sizeof (struct struct_of_ints) ) ;

	/* fill 2nd element in list */
	my_list->next->value = 2 ;
	my_list->next->next = NULL ;

	/* add a 3rd to the list */
	my_list->next->next =
		malloc (sizeof (struct struct_of_ints) ) ;

	/* fill 3rd element in list */
	my_list->next->next->value = 3 ;
	my_list->next->next->next = NULL ;


	/* print out list */
	printf ("my_list[0]=%d\n", my_list->value ) ;
	printf ("my_list[1]=%d\n", my_list->next->value ) ;
	printf ("my_list[2]=%d\n", my_list->next->next->value ) ;


	// delete element #2 
	printf ("\ndeleting 2nd node\n" ) ;
	temp = my_list->next ;	// holds address of 2nd element
	my_list->next = my_list->next->next ;
	free (temp) ;

	// print out resulting list 
	printf ("my_list[0]=%d\n", my_list->value ) ;
	printf ("my_list[1]=%d\n", my_list->next->value ) ;
		

	/* free list elements */
	//free (my_list->next->next ) ; // uncomment if node 2 doesn't get deleted
	free (my_list->next ) ;	
	free (my_list ) ; // this must be the last free (not first)

	/* alternatively, could have used while loop, looking for null to delete (or print) */

}
