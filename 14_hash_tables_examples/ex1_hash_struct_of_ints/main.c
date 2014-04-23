#include <stdio.h>
#include "ex_linked_list.h"

/* Example of hash table using linked list from lecture 14 */
/* Hash table in this example is defined entirely in main  */

#define BUCKETS 15   // play with this to get a feel for the buckets/data ratio
#define FINDME 15

int main ()
{

	int i ;
	int bucket ;
	int elements ;
	int load_factor ;

	struct_of_ints* my_hash_table [BUCKETS] ;  // simply an array of pointers to linked lists

	// sample data to store in our hash table (could get from user, file, etc.)
	int some_data [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15} ;

	// how much data do we have in static array?
	elements=sizeof(some_data)/sizeof(int) ;  // cheap trick, only works for statics


	// initialize buckets to empty
	//
	for (i = 0 ; i < BUCKETS ; i++ )
		my_hash_table[i] = NULL ;

	// store sample data into hash table
	//
	for (i = 0 ; i < elements ; i++ )
	{
		// apply "hash function" to find appropriate bucket
		bucket = some_data[i] % BUCKETS ;  // very simple mapping (data MOD buckets)

		// insert data into hash table
		if (my_hash_table [bucket] == NULL) {
			// if bucket is empty, 'create' list for appropriate bucket
			my_hash_table[bucket] = add_to_list (my_hash_table[bucket], some_data[i]) ;
			// should check for null!
		} else {
			add_to_list (my_hash_table[bucket], some_data[i]) ;
		}

	}

	// print out hash table
	//
	for (i = 0 ; i < BUCKETS ; i++ )
	{
		printf("\nHash Table bucket [%02d]=", i) ;
		print_list_simple (my_hash_table[i]) ;
	}
	printf("\nHash Table load factor = %d", elements/BUCKETS ) ;


	// find a particular data item in hash table
	//
	printf ("\n\nData Item to search for = %d", FINDME) ;
	bucket = FINDME % BUCKETS ;									// lookup key (aka apply hash function)
	printf ("\nData Item could be in bucket #[%d], searching underlying list...", bucket ) ; 	// apply hash

	if (search_list (my_hash_table[bucket], FINDME) ) 			// finding bucket is fast, search is slower
		printf ("FOUND IT") ; 								// but better than 1 long linked list!
	else
		printf ("NOT FOUND") ;



	// free memory
	//
	for (i = 0 ; i < BUCKETS ; i++ )
		delete_list(my_hash_table[i]) ;

	// this code could be better at checking for NULLs,
	// but kept it short to keep example readable

	return 0 ;
}