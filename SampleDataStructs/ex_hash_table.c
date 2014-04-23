#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ex_linked_list.h"
#include "ex_hash_table.h"


hash_table *create_hash_table (int num_of_buckets)
{
	int i ;
    hash_table *new_table;

    if (num_of_buckets<1) return NULL; /* invalid size for table */

    /* attempt to allocate memory for 1 hashtable structure */
    if ((new_table = malloc(sizeof(hash_table))) == NULL) {
        fprintf (stderr, "ERROR: malloc failed\n") ;
        return NULL;
    }

    /* attempt to allocate memory for each bucket*/
    if ((new_table->table = malloc(sizeof(struct_of_ints *) * num_of_buckets)) == NULL) {
		fprintf (stderr, "ERROR: malloc failed\n") ;
		free (new_table) ;
        return NULL;
    }

     /* initialize the elements of the table */
    for(i=0; i<num_of_buckets; i++) new_table->table[i] = NULL;

    /* set the table's size */
    new_table->num_of_buckets = num_of_buckets;

    return new_table;
}


/* determines which bucket # the "struct_of_ints" passed in, maps too */
unsigned int map (hash_table *hashtable, int value)
{
    unsigned int bucket ;

	bucket = value % hashtable->num_of_buckets ;
    return bucket ;

}


int add (hash_table *hashtable, int value)
{

	struct_of_ints *tmp_ints_struct = NULL ;
    unsigned int bucket ;

	/*  // uncomment if you want data to be unique in the table (That's called a Hashmap!)
	tmp_ints_struct = find(hashtable, value);
    if (tmp_ints_struct != NULL) {
		fprintf (stderr, "ERROR, integer with value = [%d] already in table", value) ;
		return 1;
	}
	*/

	// determine proper bucket to put value into
    bucket = map(hashtable, value) ;

	// traverse linked list at bucket and add value to the end of that linked list
	if (hashtable->table[bucket] == NULL)  // check if we're creating linked list for 1st time
		hashtable->table[bucket]= add_to_list ( hashtable->table[bucket], value ) ;
	else
		add_to_list ( hashtable->table[bucket], value ) ;

	return 0 ;

}

struct_of_ints* find (hash_table *hashtable, int value) {

	unsigned int bucket = map (hashtable, value) ;	// lookup key (aka apply hash function)
	struct_of_ints *tmp_ints_struct = NULL ;

	tmp_ints_struct = search_list (hashtable->table[bucket], value) ;

	return tmp_ints_struct ;  // could do it all in 1 line, but this is for school!
}




void delete_table (hash_table *hashtable)
{

	int i ;

	// go to each bucket, delete each linked list (node by node)
	for (i = 0 ; i < hashtable->num_of_buckets ; i++ )
		delete_list(hashtable->table[i]) ;

    // deallocate memory for table itself
    free(hashtable->table) ;

	// deallocate memory for structure holding table
    free(hashtable) ;


}

void print_table (hash_table *hashtable) {

	int i ;
	for (i=0 ; i < hashtable->num_of_buckets ; i++) {
		printf("\nHash Table bucket [%02d]=", i) ;
		print_list_simple (hashtable->table[i]) ;
	}
	printf ("\n") ;
}