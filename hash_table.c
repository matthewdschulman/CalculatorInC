#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash_table.h"


person_table *create_hash_table(int num_of_buckets)
{
	int i ;
    person_table *new_table;

    if (num_of_buckets<1) return NULL; /* invalid size for table */

    /* attempt to allocate memory for 1 hashtable structure */
    if ((new_table = malloc(sizeof(person_table))) == NULL) {
        fprintf (stderr, "ERROR: malloc failed\n") ;
        return NULL;
    }

    /* attempt to allocate memory for each bucket of people */
    if ((new_table->table = malloc(sizeof(person *) * num_of_buckets)) == NULL) {
		free (new_table) ;
		fprintf (stderr, "ERROR: malloc failed\n") ;
        return NULL;
    }

    /* initialize the elements of the table */
    for(i=0; i<num_of_buckets; i++) new_table->table[i] = NULL;

    /* set the table's size */
    new_table->num_of_buckets = num_of_buckets;

    return new_table;
}


/* converts 1st letter of last name to a number, ex: (A=0, Z=25) */
unsigned int map (person_table *hashtable, person *prsn)
{
    unsigned int hashval ;
    char ltr = prsn->lname[0] ;  // 1st letter of last name will be key

	if (prsn != NULL && ((ltr > 0x40 && ltr < 0x5B) || (ltr >0x60 && ltr < 0x7B)) )
	{
		// convert 1st character of last name to uppercase
		// subtract hex 41, returns 0 for A and 25 for Z
		hashval = toupper(ltr)-0x41 ;
	}

 	// this next line is the actual hash function
 	return hashval % hashtable->num_of_buckets;	// useless if buckets > 26
}


int add (person_table *hashtable, person *prsn)
{

	person *tmp_prsn = NULL ;
    unsigned int bucket ;

    /* does person already exist in table? */
    tmp_prsn = find(hashtable, prsn);
    if (tmp_prsn != NULL) {
	    /* item already exists, don't insert it again. */
		fprintf (stderr, "ERROR, person with lname = [%s], fname = [%s] already in table\n",
				 prsn->lname, prsn->fname) ;
		return 1;
	}

    /* otherwise, insert into appropriate bucket */
    bucket = map(hashtable, prsn) ;			 // map last name to hash value
    prsn->next = hashtable->table[bucket];   // incoming person will be new top of bucket
    hashtable->table[bucket] = prsn;		 // top of bucket is incoming person

	return 0 ;

}


person* find (person_table *hashtable, person *prsn)
{

	person *tmp_prsn = NULL ;
    unsigned int hashvalue ;

	// find bucket "prsn" would be in
    hashvalue = map(hashtable, prsn) ;

	// traverse linked list in bucket searching for "prsn"
	tmp_prsn = hashtable->table[hashvalue] ;	// get pointer to head pointer of LL

	while (tmp_prsn != NULL) {					// search LL nodes 1 by 1 until we find prsn
		if (strcmp (tmp_prsn->lname, prsn->lname) == 0
		 && strcmp (tmp_prsn->fname, prsn->fname) == 0) return tmp_prsn ;
		tmp_prsn = tmp_prsn->next ;				// advance to next node in the list
	}

	// if person isn't found, return NULL
	return NULL ;

}


void delete_table (person_table *hashtable)
{

	int i = 0 ; int y = 0 ;
	person *tmp_prsn = NULL ;

	// go through each bucket, free corresponding linked list nodes, & bucket itself
	for (i=0 ; i< hashtable->num_of_buckets ; i++) {

		while (hashtable->table[i] != NULL) {
			tmp_prsn = hashtable->table[i] ;
			hashtable->table[i] = tmp_prsn->next ;

			free (tmp_prsn->lname) ;	// don't forget we malloc'ed memory for strings
			free (tmp_prsn->fname) ;
			free (tmp_prsn) ;			// release memory for head pointer
		}
	}

	free (hashtable->table) ;	// free memory for table itself
	free (hashtable) ;	// free memory for strucutre that held table

}


void print_table (person_table *hashtable) {

	int i = 0 ;
	person *tmp_prsn = NULL ;

	for (i=0 ; i < hashtable->num_of_buckets ; i++) {
		tmp_prsn = hashtable->table[i] ;

		printf ("bucket[%02d]=", i) ;

		if (tmp_prsn == NULL) printf ("EMPTY\n") ;

		while (tmp_prsn != NULL) {
			printf ("{%s, %s}", tmp_prsn->lname, tmp_prsn->fname ) ;
			tmp_prsn = tmp_prsn->next ;
			if (tmp_prsn == NULL) printf ("\n") ; else printf (", ") ;

		}

	}

}
