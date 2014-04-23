#include <stdio.h>
#include <stdlib.h>
#include "ex_linked_list.h"

struct_of_ints* add_to_list (struct_of_ints *head_node, int value)
{
	/* adds node to the end of the linked list */
	/* if list doesn't exist, creates 1st node */

	struct_of_ints *new_node  ;
	struct_of_ints *prev_node ;
	struct_of_ints *curr_node = head_node ;

	// allocate memory
	new_node = malloc (sizeof(struct_of_ints)) ;

	if (new_node == NULL) {
		fprintf(stderr, "ERROR: add_to_list: malloc failed") ;
		return NULL ;
	}

	// populate new "last" node
	new_node->value = value ;
	new_node->next = NULL ;

	// return new_node if linked list doesn't exist yet
	if (head_node == NULL)
		return new_node ;

	// otherwise, find the end of the list
	while (curr_node != NULL) {
		prev_node = curr_node ;
		curr_node = curr_node->next ;
	}

	// then add to the list
	prev_node->next = new_node ;

	return new_node ;
}


struct_of_ints* search_list(struct_of_ints *head_node, int value)
{

	/* searches list for 1st instance of value
	   returns node containing that value      */

	struct_of_ints *curr_node = head_node ;

	// traverse entire list until 1st instance of value is found
	while(curr_node != NULL)
	{
		if(curr_node->value == value) {
			return curr_node ;
		} else {
			curr_node = curr_node->next ;
		}
	}

	// if list is empty or value isn't found, return NULL
	return NULL;

}


struct_of_ints* delete_from_list(struct_of_ints *head_node, int value)
{
	/* deletes node with value passed in
	   returns head_node */

	struct_of_ints *curr_node = head_node ;
	struct_of_ints *prev_node = head_node ;
	int found = 0 ;

	// traverse list until curr_node has value
	while(curr_node != NULL)
	{
		if(curr_node->value == value) {
			found = 1 ;
			break ;
		} else {
			prev_node = curr_node ;
			curr_node = curr_node->next ;
		}
	}

	if (found == 1 ) {
		// if found, perform surgery
		prev_node->next = curr_node->next ;

		// repoint head_node if we're deleting it
		if (curr_node == head_node)
			head_node = curr_node->next ;

		// finally, we can free node
		free (curr_node) ;
		curr_node = NULL ;
	}

	return head_node ;

}


struct_of_ints* delete_list (struct_of_ints *head_node)
{
	/* deletes all nodes
	   don't really need this function,
	   could do all of it from main */

	while (head_node != NULL ) {
		head_node=delete_from_list (head_node, head_node->value) ;
	}

	return head_node ;
}


void print_list (struct_of_ints *head_node)
{
	int i = 0 ;
	struct_of_ints *curr_node=head_node  ;

	printf ("\n----------PRINTING LIST BEGIN----------\n" );
	while (curr_node != NULL )
	{
		printf ("NODE[%d]=[%d] \n", i, curr_node->value ) ;
		curr_node = curr_node->next ;
		i++ ;
	}

	printf ("----------PRINTING LIST END------------\n" );

	return ;
}

/* function useful for printing out linked list as if it was array */
void print_list_simple (struct_of_ints *head_node)
{

	struct_of_ints *curr_node=head_node  ;

	while (curr_node != NULL )
	{
		printf ("{%d} ", curr_node->value ) ;
		curr_node = curr_node->next ;
	}

	return ;

}