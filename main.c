#include <stdio.h>
#include <stdlib.h>
#include "ex_linked_list.h"
#include "ex_hash_table.h"

/* Example of hash table using linked list from lecture 14 */
/* Hash table in this example is implemented in functions  */

#define FINDME 15

int main (int argc, char ** argv)
{

	int i ;
	int elements ;
	int buckets=4 ;		// default # of buckets unless user passses in

	hash_table* my_hash_table = NULL ;
	struct_of_ints* ints_struct = NULL ;

	// sample data to store in our hash table (could get from user, file, etc.)
	int some_data [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15} ;

	// how much data do we have in static array?
	elements=sizeof(some_data)/sizeof(int) ;  // cheap trick, only works for statics

	// get # of buckets from user if they pass it in
	if (argc >= 2) buckets=atoi(argv[1]) ;



	// create hash table
	//
	my_hash_table = create_hash_table(buckets) ;

	// store sample data into hash table
	//
	for (i = 0 ; i < elements ; i++ )
		add(my_hash_table, some_data[i]) ;

	// print out hash table
	//
	print_table (my_hash_table) ;

	// verify that data in table
	//
	if (find (my_hash_table, FINDME)) printf ("DATA ITEM [%d] IS IN TABLE\n", FINDME) ;

	// free memory
	//
	delete_table (my_hash_table) ;

	return 0 ;
}