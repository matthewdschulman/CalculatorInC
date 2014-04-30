#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash_table.h"

#define BUCKETS 100
#define MAX_LINE_LENGTH 80

//global register ints
int R0;
int R1;
int R2;
int R3;
int R4;
int R5;
int R6;
int R7;

int isNumeric (const char * s);
int load_commands (command_table *hashtable, char *filename);
void print_table (command_table *hashtable);
command* find (command_table *hashtable, command *cmnd);
int add (command_table *hashtable, command *cmnd);
unsigned int map (command_table *hashtable, command *cmnd);


int main ( int argc, char *argv[] )
{

	//check that the user input is correct
    if ( argc != 2 ) /* argc should be 2 */
    {
    	//error...
    	printf("Error with the user input. Try again. Make sure to have one command line argument.");
    }

    else 
    {
    /*	struct struct_of_ints {
			int value ;
			struct struct_of_ints *next ;
		} ; 

		// allocate 1 element list to represent the stack of calculator ints
		struct struct_of_ints *stackOfInts = 
			malloc (sizeof (struct struct_of_ints) ) ;
*/
		/* lined list node definition will store commands */
		

		command_table *command_table_hash ;
		command_table_hash = create_hash_table(BUCKETS) ;

		//load instructions into hash table
		load_commands (command_table_hash, argv[1]) ;
		//print_table (command_table) ;*/
	}
}

/*void print_table (command_table *hashtable) {

	int i = 0 ;
	command *tmp_cmnd = NULL ;

	for (i=0 ; i < hashtable->num_of_buckets ; i++) {
		tmp_cmnd = hashtable->table[i] ;

		printf ("bucket[%02d]=", i) ;

		if (tmp_cmnd == NULL) printf ("EMPTY\n") ;

		while (tmp_cmnd != NULL) {
			printf ("{%s, %s}", tmp_cmnd->lname, tmp_cmnd->fname ) ;
			tmp_cmnd = tmp_cmnd->next ;
			if (tmp_cmnd == NULL) printf ("\n") ; else printf (", ") ;

		}

	}

}*/

command_table *create_hash_table(int num_of_buckets) {
	int i ;
    command_table *new_table;

    if (num_of_buckets<1) return NULL; /* invalid size for table */

    /* attempt to allocate memory for 1 hashtable structure */
    if ((new_table = malloc(sizeof(command_table))) == NULL) {
        fprintf (stderr, "ERROR: malloc failed\n") ;
        return NULL;
    }

    /* attempt to allocate memory for each bucket of people */
    if ((new_table->table = malloc(sizeof(command *) * num_of_buckets)) == NULL) {
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

int load_commands (command_table *hashtable, char *filename) {
	FILE *theFile;
	command *a_command ;
	char instruction[MAX_LINE_LENGTH];
	int y = 0 ;

	if (hashtable == NULL) {
		fprintf (stderr, "ERROR: hash table hasn't been allocated\n") ;
		return 1 ;
	}

	// Read the data from the file
	theFile = fopen (filename, "r");

	if (!theFile) {
		fprintf (stderr, "ERROR: trouble opening file\n") ;
		return 1 ;
	}

	// read a line from the file
	while (fgets (instruction, MAX_LINE_LENGTH, theFile)) {
		
			// allocate memory for command & its fields
			a_command = malloc(sizeof(command)) ;

			a_command->instruction = malloc( strlen(instruction) + 1 ) ;
			strcpy (a_command->instruction, instruction) ;

			if (add (hashtable, a_command) != 0) {
				// if "add" fails, make certain to free this memory!
				free (a_command->instruction) ;
				free (a_command) ;
			}
			/* if "add" doesn't fail, when hash table is "deleted" it will free memory

  		} else {
			fprintf (stderr, "ERROR: formatting error in file\n") ;
		}*/
  	}
	fclose (theFile);	// not closing a file...leaks memory too!
	return 0 ;
}

unsigned int map (command_table *hashtable, command *cmnd)
{
    int hashval ;
    
	if (cmnd != NULL )
	{
		hashval = 1 ;
	}

 	// this next line is the actual hash function
 	return hashval % hashtable->num_of_buckets;	// useless if buckets > 26
}

int add (command_table *hashtable, command *cmnd)
{

	command *tmp_cmnd = NULL ;
    unsigned int bucket ;

    /* does command already exist in table? */
    tmp_cmnd = find(hashtable, cmnd);
    if (tmp_cmnd != NULL) {
	    /* item already exists, don't insert it again. */
		fprintf (stderr, "ERROR, command with instruction = [%s] already in table\n",
				 cmnd->instruction) ;
		return 1;
	}

    /* otherwise, insert into appropriate bucket */
    bucket = map(hashtable, cmnd) ;			 // map last name to hash value
    cmnd->next = hashtable->table[bucket];   // incoming command will be new top of bucket
    hashtable->table[bucket] = cmnd;		 // top of bucket is incoming command

	return 0 ;

}

command* find (command_table *hashtable, command *cmnd)
{

	command *tmp_cmnd = NULL ;
    unsigned int hashvalue ;

	// find bucket "cmnd" would be in
    hashvalue = map(hashtable, cmnd) ;

	// traverse linked list in bucket searching for "cmnd"
	tmp_cmnd = hashtable->table[hashvalue] ;	// get pointer to head pointer of LL

	while (tmp_cmnd != NULL) {					// search LL nodes 1 by 1 until we find cmnd
		if (strcmp (tmp_cmnd->instruction, cmnd->instruction) == 0)
		    return tmp_cmnd ;
		tmp_cmnd = tmp_cmnd->next ;				// advance to next node in the list
	}

	// if command isn't found, return NULL
	return NULL ;

}