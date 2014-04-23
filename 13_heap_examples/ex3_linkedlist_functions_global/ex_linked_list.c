#include <stdio.h>
#include <stdlib.h>
#include "ex_linked_list.h"

/* notice, this linked list manipulates global pointers */
/* this isn't the best implementation if you wish to have
   more than 1 linked list instance in main () */

struct struct_of_ints *head = NULL ;
struct struct_of_ints *curr = NULL ;

struct struct_of_ints* create_list(int value)
{
	printf ("creating list\n") ;
	struct struct_of_ints* ptr =
		malloc(sizeof(struct struct_of_ints));

	if (ptr == NULL)
	{
		fprintf (stderr, "ERROR: create_list: malloc failed") ;
		return NULL ;
	}

	ptr->value = value ;
	ptr->next  = NULL ;

	head = curr = ptr ;
	return ptr ;

}


struct struct_of_ints* add_to_list(int value)
{
	struct struct_of_ints* ptr = NULL ;

	// see if list exists, if not, create & return
	if (head == NULL)
		return (create_list(value)) ;

	// list already existed, allocate memory for new node
	ptr = malloc(sizeof(struct struct_of_ints));

	if (ptr == NULL)
	{
		fprintf (stderr, "ERROR: add_to_list: malloc failed") ;
		return NULL ;
	}

	// populate newly allocated memory with value
	ptr->value = value ;
	ptr->next = NULL ;

	// update list
	curr->next = ptr ; // add new node to list
	curr = ptr ;	   // reset CURR = last node in list

	return ptr ;

}


struct struct_of_ints* search_list(int value)
{
	/* searches for 1st instance of value
	   a weak search mechanism at best.
	   returns 1st node that matches search
	*/

	struct struct_of_ints* ptr = head ;
	struct struct_of_ints* tmp = NULL ;

	while(ptr != NULL)
	{
		if(ptr->value == value) {
			return ptr ;
		} else {
			ptr = ptr->next ;
		}
	}

	return NULL ;
}


int delete_from_list(int value)
{
	struct struct_of_ints *ptr = head ;
	struct struct_of_ints *prev = NULL ;
	int found = 0 ;

	// traverse list, searching each node for "value"
	while(ptr != NULL)
	{
		if(ptr->value == value) {
			found = 1 ;
			break ;
		} else {
			prev = ptr ;
			ptr = ptr->next ;
		}
	}

	if (found == 0 ) return 1 ;  // return if nothing found

	// perform surgery, removing found node from list
	if (prev !=NULL)
		prev->next = ptr->next ;
	if (ptr == curr)
		curr = prev ;
	else if (ptr == head)
		head = ptr->next ;

	// release memory of found node
	free (ptr) ;
	ptr = NULL ;

	return 0 ;
}

void delete_list()
{
	struct struct_of_ints *ptr = NULL ;

	// must free node by node
	// but don't accidentally delete head node!
	while (head != NULL )
	{
		ptr = head ;
		head = ptr->next ;
		free (ptr) ;
	}

}

void print_list ()
{
	struct struct_of_ints* ptr = head ;
	int i = 0 ;

	printf ("\n----------PRINTING LIST BEGIN----------\n" );
	while (ptr != NULL )
	{
		printf ("NODE[%d]=[%d] \n", i, ptr->value ) ;
		ptr = ptr->next ;
		i++ ;
	}

	printf ("----------PRINTING LIST END------------\n" );

	return ;
}
