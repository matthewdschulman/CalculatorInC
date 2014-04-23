#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash_table.h"

#define BUCKETS 26
#define MAX_LINE_LENGTH 80


int load_class_list (person_table *hashtable, char *filename) ;

int main () {

	person_table *class_list_table ;

	printf ("creating hash table of 'students' with [%d] buckets\n", BUCKETS) ;
	class_list_table = create_hash_table(BUCKETS) ;

	printf ("loading in CIS 240 class list\n") ;
	load_class_list (class_list_table, "class_list.txt") ;

	print_table (class_list_table) ;

	delete_table (class_list_table) ;

	return 0 ;
}



int load_class_list (person_table *hashtable, char *filename) {

	FILE *theFile;
	person *a_person ;
	char input[MAX_LINE_LENGTH];
	char fname[MAX_LINE_LENGTH];
	char lname[MAX_LINE_LENGTH];
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
	while (fgets (input, MAX_LINE_LENGTH, theFile)) {
		if (sscanf(input, "%s %s", lname, fname) == 2)
		{
			// allocate memory for person & its fields
			a_person = malloc(sizeof(person)) ;

			a_person->fname = malloc( strlen(fname) + 1 ) ;
			strcpy (a_person->fname, fname ) ;

			a_person->lname = malloc( strlen(lname) + 1 ) ;
			strcpy (a_person->lname, lname ) ;

			if (add (hashtable, a_person) != 0) {
				// if "add" fails, make certain to free this memory!
				free (a_person->fname) ;
				free (a_person->lname) ;
				free (a_person) ;
			}
			// if "add" doesn't fail, when hash table is "deleted" it will free memory

  		} else {
			fprintf (stderr, "ERROR: formatting error in file\n") ;
		}
  	}

	fclose (theFile);	// not closing a file...leaks memory too!

	return 0 ;
}