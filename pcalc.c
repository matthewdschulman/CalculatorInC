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
int bucketCounter = 0;
struct struct_of_ints *stackOfInts;

int isNumeric (const char * s);
int load_commands (command_table *hashtable, char *filename);
void print_table (command_table *hashtable);
command* find (command_table *hashtable, command *cmnd);
int add (command_table *hashtable, command *cmnd);
unsigned int map (command_table *hashtable, command *cmnd);
void run_through_commands (command_table *hashtable);
void constInstr (char *reg, char *val, int n_spaces);
void pushInstr (char *curInt);
void popInstr(char *destReg);

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
		// allocate 1 element list to represent the stack of calculator ints
		stackOfInts = 
			malloc (sizeof (struct struct_of_ints) ) ;

		/* lined list node definition will store commands */	

		command_table *command_table_hash ;
		command_table_hash = create_hash_table(BUCKETS) ;

		//load instructions into hash table
		load_commands (command_table_hash, argv[1]) ;
		run_through_commands (command_table_hash);
		//print the table for testing purposes
		print_table (command_table_hash) ;
		intStack *current;
		current = stackOfInts;
	    while (current != NULL) {
	        printf("stack#: %d\n", current->value);
	        current = current->next;
	    }
	    printf("R4 = %d",R4);
	    printf("R5 = %d",R5);
	}
}

void print_table (command_table *hashtable) {
	int i = 0 ;
	command *tmp_cmnd = NULL ;

	for (i=0 ; i < hashtable->num_of_buckets ; i++) {
		tmp_cmnd = hashtable->table[i] ;

		if (tmp_cmnd != NULL) {
			printf ("bucket[%02d]=", i) ;
			while (tmp_cmnd != NULL) {
				printf ("%s", tmp_cmnd->instruction ) ;
				tmp_cmnd = tmp_cmnd->next ;
				if (tmp_cmnd == NULL) printf ("\n") ; else printf (", ") ;

			}
		}
	}
}

void run_through_commands (command_table *hashtable) {
	int i = 0 ;
	command *tmp_cmnd = NULL ;

	for (i=0 ; i < hashtable->num_of_buckets ; i++) {
		tmp_cmnd = hashtable->table[i] ;

		if (tmp_cmnd != NULL) {
			while (tmp_cmnd != NULL) {
				/* split instruction and append tokens to 'res' */
				char ** res  = NULL;
				char *  p    = strtok (tmp_cmnd->instruction, " ");
				int n_spaces = 0, i;			

				while (p) {
				    res = realloc (res, sizeof (char*) * ++n_spaces);

				    if (res == NULL)
				        exit (-1); /* memory allocation failed */

				    res[n_spaces-1] = p;

				    p = strtok (NULL, " ");
				}

				/* realloc one extra element for the last NULL */

				res = realloc (res, sizeof (char*) * (n_spaces+1));
				res[n_spaces] = 0;

				/* conduct the commands*/

				for (i = 0; i < (n_spaces+1); ++i) {
					if (i == 0) {
						//identify the current instruction
						if (strcmp(res[i],"CONST") == 0 ) {
							constInstr(res[1], res[2], n_spaces);
						}
						else if (strcmp(res[i],"PUSH") == 0 ) {
							pushInstr(res[i+1]);							
						}
						else if (strcmp(res[i],"POP") == 0) {
							popInstr(res[i+1]);
						}
					}
				}

				/* free the memory allocated */

				free (res);
				tmp_cmnd = tmp_cmnd->next;
			}
		}
	}
}

//functions for different commands...
void constInstr(char *reg, char *val, int n_spaces) {
	if (strcmp(reg,"R0") == 0) {
		R0 = atoi(val);
	}
	else if (strcmp(reg,"R1") == 0) {
		R1 = atoi(val);
	}
	else if (strcmp(reg,"R2") == 0) {
		R2 = atoi(val);
	}
	else if (strcmp(reg,"R3") == 0) {
		R3 = atoi(val);
	}
	else if (strcmp(reg,"R4") == 0) {
		R4 = atoi(val);
	}
	else if (strcmp(reg,"R5") == 0) {
		R5 = atoi(val);
	}
	else if (strcmp(reg,"R6") == 0) {
		R6 = atoi(val);
	}
	else if (strcmp(reg,"R7") == 0) {
		R7 = atoi(val);
	}
	else {
		printf("Error with the CONST syntax of the input file\n");
	}
}

void pushInstr(char *reg) {

	//get the register (first 2 chars of reg)
	char regis[3];
	strncpy(regis, reg, 2);
	regis[2] = '\0'; 

	//find the value to push
	int valueToPush;
	if (strcmp(regis,"R0") == 0) {
		valueToPush = R0;
	}
	else if (strcmp(regis,"R1") == 0) {
		valueToPush = R1;
	}
	else if (strcmp(regis,"R2") == 0) {
		valueToPush = R2;
	}
	else if (strcmp(regis,"R3") == 0) {
		valueToPush = R3;
	}
	else if (strcmp(regis,"R4") == 0) {
		valueToPush = R4;
	}
	else if (strcmp(regis,"R5") == 0) {
		valueToPush = R5;
	}
	else if (strcmp(regis,"R6") == 0) {
		valueToPush = R6;
	}
	else if (strcmp(regis,"R7") == 0) {
		valueToPush = R7;
	}
	else {
		printf("Error with the PUSH instruction for %s\n", reg);
	}
	//push res[i+1] to front of stack
	//create new node with the current value
	//function call: pushToFrontOfStack(struct_of_ints, curIntIfInt);
	//first check if the list is empty

	if (!stackOfInts->value) {
		//list is empty
		stackOfInts->value = valueToPush;
		stackOfInts->next = NULL;
	}
	else {
		//list has elements. add cur int to front of linked list
		intStack *curNode = 
			malloc (sizeof (struct struct_of_ints) ) ;
		curNode->value = valueToPush;
		curNode->next = stackOfInts;
		stackOfInts = curNode;
	}
}

void popInstr(char *destReg) {
	//first check that there is an element to pop
	if (stackOfInts == NULL) {
		printf("Error: Tried to pop with nothing on the stack of ints\n");
	}

	//get the register (first 2 chars of destReg)
	char regis[3];
	strncpy(regis, destReg, 2);
	regis[2] = '\0';

	int poppedInt;
	poppedInt = stackOfInts->value;
	stackOfInts = stackOfInts->next;

	//find which regsiter to place the poppedInt
	if (strcmp(regis,"R0") == 0) {
		R0 = poppedInt;
	}
	else if (strcmp(regis,"R1") == 0) {
		R1 = poppedInt;
	}
	else if (strcmp(regis,"R2") == 0) {
		R2 = poppedInt;
	}
	else if (strcmp(regis,"R3") == 0) {
		R3 = poppedInt;
	}
	else if (strcmp(regis,"R4") == 0) {
		R4 = poppedInt;
	}
	else if (strcmp(regis,"R5") == 0) {
		R5 = poppedInt;
	}
	else if (strcmp(regis,"R6") == 0) {
		R6 = poppedInt;
	}
	else if (strcmp(regis,"R7") == 0) {
		R7 = poppedInt;
	}
	else {
		printf("Error with the POP instruction for %s\n", destReg);
	}
}


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
		hashval = bucketCounter ;
		bucketCounter++;
	}

 	// this next line is the actual hash function
 	return ((hashval - 1) / 2) % hashtable->num_of_buckets;	// useless if buckets > 26
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
    bucket = map(hashtable, cmnd) ;			 // map command to hash value
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